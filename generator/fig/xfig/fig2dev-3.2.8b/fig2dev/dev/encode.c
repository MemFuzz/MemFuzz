/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2020 by Thomas Loimer
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies
 * of the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

/*
 * encode.c: ascii85 encoding and deflate data
 * Author: Thomas Loimer, 2020-12-14
 *
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "encode.h"

#include <limits.h>	/* UINT_MAX */
#include <stdio.h>
#ifdef HAVE_ZLIB_H
#include <zlib.h>
#define	ZLIB_IN_MAX	UINT_MAX	/* maximum size zlib can read at once */
#endif

#include "messages.h"


/*
 * convert the next four bytes to ascii85, writing five chars.
 */
static int
convertfourbytes(FILE *out, unsigned char *in)
{
	const unsigned long	power85[4] = {85L*85*85*85, 85L*85*85, 85L*85,
						85L};
	int			i, o;
	unsigned long		word;

	word = ((unsigned long)(((unsigned int)(*in) << 8) + *(in+1)) << 16) +
		(((unsigned int)(*(in+2)) << 8) + *(in+3));
	if (word == 0) {
		fputc('z', out);
		return 1;
	} else {
		for (i = 0; i < 4; ++i) {
			o = (int)(word / power85[i]);
			word -= o * power85[i];
			fputc(o + '!', out);
		}
		fputc(word + '!', out);
		return 5;
	}
}

/*
 * Convert the remaining 1 to 3 bytes.
 */
static void
convertremainder(FILE *out, unsigned char *in, unsigned len)
{
	const unsigned long	power85[4] = {85L*85*85*85, 85L*85*85, 85L*85,
						85L};
	int			o;
	unsigned		i;
	unsigned long		word;


	word = (unsigned long)(*in) << 24;
	for (i = 1; i < len; ++i)
		word += (unsigned long)(*(in+i)) << 8 * (3 - i);
	for (i = 0; i < len + 1; ++i) {
		o = (int)(word / power85[i]);
		word -= o * power85[i];
		fputc(o + '!', out);
	}
}

/*
 * Write data provided in in, of length len, ascii85-encoded to out.
 * If called multiple times, "len" should be a multiple of 4.
 * Otherwise, a remainder is written that ends an ascii85 encoded stream.
 * Return 0 on success, -1 on failure.
 * For -1, err_msg(), retrieving errno, is already called.
 */
int
ascii85encode(FILE *out, unsigned char *in, size_t len)
{
	size_t		i, n;
	size_t		lines;
				/* this yields 16 * 5 = 80 chars in a line */
	const size_t	bytes_per_line = 16 * 4;

	/* write full lines */
	lines = len / bytes_per_line;
	for (n = 0; n < lines; ++n) {
		for (i = 0; i < 16; ++i)
			convertfourbytes(out, in + n * bytes_per_line + i * 4);
		fputc('\n', out);
		if (ferror(out)) {
			err_msg("Error writing one line of encoded data");
			return -1;
		}
	}

	/* quick return */
	if ((n = len - lines * bytes_per_line) == 0)
		return 0;

	/* write remaining groups of four */
	for (i = 0; i < n / 4; ++i)
		convertfourbytes(out, in + lines * bytes_per_line + i * 4);

	/* write remainder */
	if ((n -= i * 4) > 0)
		convertremainder(out, in + lines * bytes_per_line + i * 4, n);

	if (ferror(out)) {
		err_msg("Error writing encoded data");
		return -1;
	}
	return 0;
}

#ifdef HAVE_ZLIB_H
/*
 * Write the deflated and ascii85 encoded bitmap data to out.
 */
int
deflate_ascii85encode(FILE *out, unsigned char *in, size_t len)
{
	int		ret;
	int		flush;
	z_stream	strm;
	unsigned char	buf[16384]; /* IMPORTANT, that this is a multiple of 4!
				     * Nice, if a multiple of 16*4, see above */

	/*
	 * Initialize the zlib state object.
	 * See zlib.h and the example zpipe.c.
	 */
	strm.zalloc = Z_NULL;	/* Have zlib use the standard system malloc().*/
	strm.zfree = Z_NULL;	/* Have zlib use the standard system free(). */
	strm.opaque = Z_NULL;	/* Not used, passed to zalloc() and zfree(). */
	ret = deflateInit2(&strm,
			Z_BEST_COMPRESSION,	/* 0 - 9, default 6 */
			Z_DEFLATED,		/* method, must be Z_DEFLATED */
			MAX_WBITS,		/* window size, max here */
			MAX_MEM_LEVEL,		/* allocated memory for
						   compression, use maximum */
			Z_RLE); /* compression strategy used for png data */
	if (ret != Z_OK) {
		put_msg("Unable to initialize compression.");
		if (strm.msg)
			put_msg("Zlib error: %s", strm.msg);
		else
			put_msg("Zlib error = %d", ret);
		return ret;
	}

	/* Assign input and output for compression. */
	strm.next_in = in;
	strm.next_out = buf;
	strm.avail_out = (unsigned) sizeof buf;

	/*
	 * strm.avail_in is of type unsigned int, hence it can hold a maximum
	 * number of UINT_MAX (= ZLIB_IN_MAX, see above) bytes, equal 4 GiB. */
	if (len > ZLIB_IN_MAX) {
		flush = Z_NO_FLUSH;
		strm.avail_in = ZLIB_IN_MAX;
		len -= strm.avail_in;
	} else {
		flush = Z_FINISH;
		strm.avail_in = len;
	}

	/*
	 * Start compression.
	 * Loop, as long as the output buffer can be completely filled.
	 * This rests on the assumption that deflate() writes a number of
	 * completely filled output buffers, and only the last one is probably
	 * partially filled.
	 */
	while ((ret = deflate(&strm, flush)) == Z_OK && strm.avail_out == 0){
		ascii85encode(out, buf, sizeof buf);
		strm.avail_out = (unsigned) sizeof buf;
		strm.next_out = buf;
		if (flush != Z_FINISH) {
			unsigned	possible = ZLIB_IN_MAX - strm.avail_in;
			if (possible > len) {
				strm.avail_in += len;
				flush = Z_FINISH;
			} else {
				strm.avail_in = ZLIB_IN_MAX;
				len -= possible;
			}
		}
	}
	if (ret == Z_STREAM_ERROR) {
		if (strm.msg)
			put_msg("Error while compressing image: %s", strm.msg);
		else
			put_msg("Error while compressing image.");
		return Z_STREAM_ERROR;
	}
	if (ret == Z_BUF_ERROR && strm.avail_out == 0) {
		put_msg("An unexpected error occurred, avail_out == 0 && "
			"ret == Z_BUF_ERROR.\nPlease report this error.");
	}
	/* output the remainder */
	if (ret == Z_STREAM_END && strm.avail_out != 0)
		ascii85encode(out, buf, sizeof buf - strm.avail_out);

	/* clean up */
	if (deflateEnd(&strm) != Z_OK) {
		if (strm.msg)
			put_msg("Error after compression of image: %s.",
					strm.msg);
		else
			put_msg("Error after compression of image.");
	}
	return 0;
}
#endif	/* HAVE_ZLIB_H */
