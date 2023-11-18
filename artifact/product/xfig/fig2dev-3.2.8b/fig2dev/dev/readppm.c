/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2021 by Thomas Loimer
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
 * readppm.c: import ppm into PostScript
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdint.h>		/* INT16_MAX */
#include <stdlib.h>
#include <string.h>

#include "fig2dev.h"	/* includes <object.h> */
//#include "object.h"	/* F_pic */
#include "messages.h"
#include "readpics.h"
#include "xtmpfile.h"

extern	int	_read_pcx(FILE *pcxfile, F_pic *pic);	/* readpcx.c */

/*
 * Return codes are mostly, but unfortunately not always,
 *	1: success,
 *	0: failure
 */


static int
skip_comments_whitespace(FILE *file)
{
	int	c;

	while ((c = fgetc(file)) != EOF) {
		if (c == '#')
			while ((c = fgetc(file)) != EOF && c != '\n')
				;
		if (c != ' ' && c != '\n' && c != '\r' && c != '\f' &&
				c != '\t' && c != '\v')
			break;
	}
	if (c == EOF) {
		return EOF;
	} else {
		ungetc(c, file);
		return 0;
	}
}

static int
read_8bitppm(FILE *file, unsigned char *restrict dst, unsigned int width,
						unsigned int height)
{
	unsigned int	w;

	while (height-- > 0u) {
		w = width * 3u;
		while (w-- > 0u)
			*(dst++) = (unsigned char)fgetc(file);
		/* check error condition after each row */
		if (feof(file) || ferror(file))
			return 0;
	}
	return 1;
}

static void
scale_to_255(unsigned char *restrict byte, unsigned maxval, unsigned rowbytes,
		unsigned height)
{
	unsigned int	w;
	const unsigned	rnd = maxval / 2;

	while (height-- > 0u) {
		w = rowbytes;
		while (w-- > 0u) {
			*byte = (*byte * 255u + rnd) / maxval;
			++byte;
		}
	}
}

static int
read_16bitppm(FILE *file, unsigned char *restrict dst, unsigned int maxval,
		unsigned int width, unsigned int height)
{
	unsigned	w;
	unsigned	c;
	const unsigned	rnd = maxval / 2;

	while (height-- > 0u) {
		w = width * 3u;
		while (w-- > 0u) {
			c = ((((unsigned)fgetc(file) << 8) +
				(unsigned)fgetc(file)) * 255u + rnd) / maxval;
			if (c > 255u)
				c = 255u;
			*(dst++) = (unsigned char)c;
		}
		if (feof(file) || ferror(file))
			return 0;
	}
	return 1;
}

static int
read_asciippm(FILE *file, unsigned char *restrict dst, unsigned int width,
						unsigned int height)
{
	unsigned int	c;
	unsigned int	w;

	while (height-- > 0u) {
		w = width * 3u;
		while (w-- > 0u) {
			if (fscanf(file, "%u", &c) != 1)
				return 0;
			if (c > 255u)
				c = 255u;
			*(dst++) = (unsigned char)c;
		}
	}
	return 1;
}

/*
 * Read a ppm file encoded with ascii decimal numbers, and scale to
 * the range 0--255. The function above, read_asciippm(), does not scale.
 */
static int
read_ascii_max_ppm(FILE *file, unsigned char *restrict dst, unsigned int maxval,
			unsigned int width, unsigned int height)
{
	unsigned int	c;
	unsigned int	w;
	const unsigned	rnd = maxval / 2;

	while (height-- > 0u) {
		w = width * 3u;
		while (w-- > 0u) {
			if (fscanf(file, "%u", &c) != 1)
				return 0;
			/* scale to the range 0--255 */
			c = ((c * 255u) + rnd) / maxval;
			if (c > 255u)
				c = 255u;
			*(dst++) = (unsigned char)c;
		}
	}
	return 1;
}

static int
_read_ppm(FILE *file, F_pic *pic)
{
	int		c;
	int		magic;
	int		stat = 0;		/* prime with failure */
	unsigned int	height = 0u;
	unsigned int	width = 0u;
	unsigned int	rowbytes;
	unsigned int	maxval = 0u;

	/* get the magic number */
	if ((c = fgetc(file)) == EOF || c != 'P')
		return stat;
	if ((magic = fgetc(file)) == EOF || (magic != '6' && magic != '3'))
		return stat;

	if (skip_comments_whitespace(file))
		return stat;

	if (fscanf(file, "%u", &width) != 1)
		return stat;

	if (skip_comments_whitespace(file))
		return stat;

	if (fscanf(file, "%u", &height) != 1 || width == 0u || height == 0u)
		return stat;

	if (skip_comments_whitespace(file))
		return stat;

	if (fscanf(file, "%u", &maxval) != 1 || maxval > 65535u || maxval == 0u)
		return stat;

	if (skip_comments_whitespace(file))
		return stat;

	if (width > INT16_MAX || height > INT16_MAX) { /* large enough */
		fprintf(stderr, "fig2dev: PPM file %u x %u too large.\n",
				width, height);
		return stat;
	}

	rowbytes = width * 3u;
	pic->bitmap = malloc(height * rowbytes);
	if (pic->bitmap == NULL) {
		fputs("fig2dev: Out of memory, could not read PPM file.\n",
				stderr);
		return stat;
	}

	if (magic == '6') {
		if (maxval < 256u) {
			stat = read_8bitppm(file, pic->bitmap, width, height);
			if (maxval != 255u)
				scale_to_255(pic->bitmap, maxval, rowbytes,
						height);
		} else {
			stat = read_16bitppm(file, pic->bitmap, maxval,
					width, height);
		}
	} else { /* magic == '3' */
		if (maxval == 255u)
			stat = read_asciippm(file, pic->bitmap, width, height);
		else
			stat = read_ascii_max_ppm(file, pic->bitmap, maxval,
					width, height);
	}

	if (stat != 1) {
		free(pic->bitmap);
	} else {
		pic->subtype = P_PPM;
		pic->numcols = 1 << 24;
		pic->bit_size.x = width;
		pic->bit_size.y = height;
	}

	return stat;
}

/*
 * Read a ppm by first calling ppmtopcx via popen(). If ppmtopcx does not exist,
 * read the ppm in code, using _read_ppm(). Skip trying ImageMagick's convert or
 * gm convert, because these do not optimize image files. ppmtopcx counts colors
 * and, if possible, writes a file with a small color palette.
 * filetype: 0 - real file, 1 - pipe
 * Return: 0 failure, 1 success.
 */
int
read_ppm(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	int	stat;
	size_t	size;
	FILE	*f;
	char	buf[BUFSIZ];
	char	*cmd = buf;
	char	*const cmd_fmt = "ppmtopcx -quiet >%s 2>/dev/null";
	char	pcxname_buf[128] = "f2dpcxXXXXXX";
	char	*pcxname = pcxname_buf;

	*llx = *lly = 0;

	if (!rewind_stream(pic_stream))
		return 0;

	/* make name for temp output file */
	if ((f = xtmpfile(&pcxname, sizeof pcxname_buf)) == NULL) {
		fprintf(stderr, "Cannot create temporary file %s\n", pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return 0;
	}

	/* write the command for the pipe to cmd */
	size = sizeof cmd_fmt + strlen(pcxname) - 2;
	if (size > sizeof buf && (cmd = malloc(size)) == NULL) {
		put_msg(Err_mem);
		remove(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return 0;
	}
	if (sprintf(cmd, cmd_fmt, pcxname) < 0) {
		err_msg("fig2dev, I/O error");
		remove(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return 0;
	}

	/* pipe to ppmtopcx */
	if ((f = popen(cmd, "w"))) {
		while ((size=fread(buf, 1, sizeof buf, pic_stream->fp)) != 0)
			fwrite(buf, size, 1, f);

		/* close pipe */
		stat = pclose(f);
	} else {	/* f = NUll */
		remove(pcxname);
		stat = -1;
	}

	/* ppmtopcx succeeded */
	if (stat == 0) {
	       if ((f = fopen(pcxname, "rb"))) {
		       fprintf(tfp, "%% Originally from a PPM File: %s\n\n",
				       pic->file);
		       stat = _read_pcx(f, pic);
		       fclose(f);
	       } else {	/* f == NULL */
		       fprintf(stderr, "Cannot open temporary output file %s\n",
				       pcxname);
		       stat = -1;
	       }
	       remove(pcxname);
	} else {
		stat = -1;
	}

	if (pcxname != pcxname_buf)
		free(pcxname);

	if (stat == 1) {
		return stat;
	} else {	/* ppmtopcx failed */
		f = rewind_stream(pic_stream);
		if (f == NULL)
			return stat;
		return _read_ppm(f, pic);
	}
}
