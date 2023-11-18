/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2020 by Thomas Loimer
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"		/* restrict */
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <X11/X.h>	/* TrueColor, None */
#include <X11/Xmd.h>	/* CARD32 */

#include "resources.h"
#include "object.h"
#include "f_picobj.h"
#include "f_util.h"
#include "w_msgpanel.h"


/* return codes:  PicSuccess (1) : success
		  FileInvalid (-2) : invalid file
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

#define THREE_BYTEPERPIXEL	(tool_vclass != TrueColor || image_bpp != 4 \
					|| appres.monochrome)

static int
read_8bitppm(FILE *file, unsigned char *restrict dst, unsigned int width,
						unsigned int height)
{
	int		c[3];
	unsigned int	w;

	if (THREE_BYTEPERPIXEL) {
		while (height-- > 0u) {
			w = width;
			while (w-- > 0u) {
				if ((c[0] = fgetc(file)) == EOF ||
						(c[1] = fgetc(file)) == EOF ||
						(c[2] = fgetc(file)) == EOF)
					return FileInvalid;
				/* map_to_palette expects BGR triples */
				*(dst++) = (unsigned char)c[2];
				*(dst++) = (unsigned char)c[1];
				*(dst++) = (unsigned char)c[0];
			}
		}
		return PicSuccess;
	}

	while (height-- > 0u) {
		w = width;
		while (w-- > 0u) {
			if ((c[0] = fgetc(file)) == EOF ||
					(c[1] = fgetc(file)) == EOF ||
					(c[2] = fgetc(file)) == EOF)
				return FileInvalid;
			*(CARD32 *)dst = ((CARD32)c[0] << 16) +
					((CARD32)c[1] << 8) + (CARD32)c[2];
			dst += sizeof(CARD32);
		}
	}
	return PicSuccess;
}

static void
scale_to_255(unsigned char *restrict byte, unsigned maxval, unsigned rowbytes,
		unsigned height)
{
	unsigned int	w;
	const unsigned	rnd = maxval / 2;

	/* This scales also the unused alpha channel for TrueColor visuals. One
	   would have to check endian-ness, to avoid the unecessary scaling */
	while (height-- > 0u) {
		w = rowbytes;
		while (w-- > 0u) {
			*byte = (*byte * 255u + rnd) / maxval;
			++byte;
		}
	}
}

/*
 * Read the next six bytes from file, which correspond to a rgb triplet with two
 * bytes for each channel, and return the values scaled into the range 0--255.
 */
static int
read6bytes(FILE *file, unsigned maxval, unsigned *r, unsigned *g, unsigned *b)
{
	int		c[6];
	const uint32_t	rnd = maxval / 2;

	if ((c[0] = fgetc(file)) == EOF || (c[1] = fgetc(file)) == EOF ||
		   (c[2] = fgetc(file)) == EOF || (c[3] = fgetc(file)) == EOF ||
		   (c[4] = fgetc(file)) == EOF || (c[5] = fgetc(file)) == EOF)
		return FileInvalid;

	/* scale to the range 0 - 255 */
	/* two-byte ppm files have the most significant byte first */
	*r = ((((uint32_t)c[0] << 8) + c[1]) * 255u + rnd) / maxval;
	*g = ((((uint32_t)c[2] << 8) + c[3]) * 255u + rnd) / maxval;
	*b = ((((uint32_t)c[4] << 8) + c[5]) * 255u + rnd) / maxval;

	if (*r > 255u)
		*r = 255u;
	if (*g > 255u)
		*g = 255u;
	if (*b > 255u)
		*b = 255u;

	return 0;
}

static int
read_16bitppm(FILE *file, unsigned char *restrict dst, unsigned int maxval,
		unsigned int width, unsigned int height)
{
	unsigned int	w;
	unsigned int	r, g, b;

	if (THREE_BYTEPERPIXEL) {
		while (height-- > 0u) {
			w = width;
			while (w-- > 0u) {
				if (read6bytes(file, maxval, &r, &g, &b))
					return FileInvalid;

				/* map_to_palette expects BGR triples */
				*(dst++) = (unsigned char)b;
				*(dst++) = (unsigned char)g;
				*(dst++) = (unsigned char)r;
			}
		}
		return PicSuccess;
	}

	while (height-- > 0u) {
		w = width;
		while (w-- > 0u) {
			if (read6bytes(file, maxval, &r, &g, &b))
				return FileInvalid;
			*(CARD32 *)dst = ((CARD32)r << 16) + ((CARD32)g << 8) +
						(CARD32)b;
			dst += sizeof(CARD32);
		}
	}
	return PicSuccess;
}

static int
read_asciippm(FILE *file, unsigned char *restrict dst, unsigned int width,
						unsigned int height)
{
	int		c[3];
	unsigned int	w;

	if (THREE_BYTEPERPIXEL) {
		while (height-- > 0u) {
			w = width;
			while (w-- > 0u) {
				if (fscanf(file, " %u %u %u", c, c+1, c+2) != 3)
					return FileInvalid;

				if (c[0] > 255) c[0] = 255;
				if (c[1] > 255) c[1] = 255;
				if (c[2] > 255) c[2] = 255;

				/* map_to_palette expects BGR triples */
				*(dst++) = (unsigned char)c[2];
				*(dst++) = (unsigned char)c[1];
				*(dst++) = (unsigned char)c[0];
			}
		}
		return PicSuccess;
	}

	/* four bytes per pixel */
	while (height-- > 0u) {
		w = width;
		while (w-- > 0u) {
			if (fscanf(file, " %u %u %u", c, c + 1, c + 2) != 3)
				return FileInvalid;

			if (c[0] > 255) c[0] = 255;
			if (c[1] > 255) c[1] = 255;
			if (c[2] > 255) c[2] = 255;

			*(CARD32 *)dst = ((CARD32)c[0] << 16) +
					((CARD32)c[1] << 8) + (CARD32)c[2];
			dst += sizeof(CARD32);
		}
	}
	return PicSuccess;
}

/*
 * Read a ppm file encoded with ascii decimal numbers, and scale to
 * the range 0--255. The function above, read_asciippm(), does not scale.
 */
static int
read_ascii_max_ppm(FILE *file, unsigned char *restrict dst, unsigned int maxval,
			unsigned int width, unsigned int height)
{
	int		c[3];
	unsigned int	w;
	const uint32_t	rnd = maxval / 2;

	if (THREE_BYTEPERPIXEL) {
		while (height-- > 0u) {
			w = width;
			while (w-- > 0u) {
				if (fscanf(file, " %u %u %u", c, c+1, c+2) != 3)
					return FileInvalid;

				/* scale to the range 0--255 */
				c[0] = ((uint32_t)c[0] * 255u + rnd) / maxval;
				c[1] = ((uint32_t)c[1] * 255u + rnd) / maxval;
				c[2] = ((uint32_t)c[2] * 255u + rnd) / maxval;
				if (c[0] > 255) c[0] = 255;
				if (c[1] > 255) c[1] = 255;
				if (c[2] > 255) c[2] = 255;

				/* map_to_palette expects BGR triples */
				*(dst++) = (unsigned char)c[2];
				*(dst++) = (unsigned char)c[1];
				*(dst++) = (unsigned char)c[0];
			}
		}
		return PicSuccess;
	}

	/* four bytes per pixel */
	while (height-- > 0u) {
		w = width;
		while (w-- > 0u) {
			if (fscanf(file, " %u %u %u", c, c + 1, c + 2) != 3)
				return FileInvalid;

			/* scale to the range 0--255 */
			c[0] = ((uint32_t)c[0] * 255u + rnd) / maxval;
			c[1] = ((uint32_t)c[1] * 255u + rnd) / maxval;
			c[2] = ((uint32_t)c[2] * 255u + rnd) / maxval;
			if (c[0] > 255) c[0] = 255;
			if (c[1] > 255) c[1] = 255;
			if (c[2] > 255) c[2] = 255;

			*(CARD32 *)dst = ((CARD32)c[0] << 16) +
					((CARD32)c[1] << 8) + (CARD32)c[2];
			dst += sizeof(CARD32);
		}
	}
	return PicSuccess;
}

int
read_ppm(F_pic *pic, struct xfig_stream *restrict pic_stream)
{
	int		c;
	int		magic;
	int		stat = FileInvalid;
	unsigned int	height = 0u;
	unsigned int	width = 0u;
	unsigned int	rowbytes;
	unsigned int	maxval = 0u;

	if (!rewind_stream(pic_stream))
		return FileInvalid;

	/* get the magic number */
	if ((c = fgetc(pic_stream->fp)) == EOF || c != 'P')
		return stat;
	if ((magic = fgetc(pic_stream->fp)) == EOF ||
			(magic != '6' && magic != '3'))
		return stat;

	if (skip_comments_whitespace(pic_stream->fp))
		return stat;

	if (fscanf(pic_stream->fp, "%u", &width) != 1)
		return stat;

	if (skip_comments_whitespace(pic_stream->fp))
		return stat;

	if (fscanf(pic_stream->fp, "%u", &height) != 1 ||
			width == 0u || height == 0u)
		return stat;

	if (skip_comments_whitespace(pic_stream->fp))
		return stat;

	if (fscanf(pic_stream->fp, "%u", &maxval) != 1 ||
			maxval > 65535u || maxval == 0u)
		return stat;

	if (skip_comments_whitespace(pic_stream->fp))
		return stat;

	if (width > INT16_MAX || height > INT16_MAX) { /* large enough */
		file_msg("PPM file %u x %u too large.", width, height);
		return stat;
	}

	rowbytes = width * (THREE_BYTEPERPIXEL ? 3u : sizeof(CARD32));
	pic->pic_cache->bitmap = malloc(height * rowbytes);
	if (pic->pic_cache->bitmap == NULL) {
		file_msg("Out of memory, could not read PPM file.");
		return stat;
	}

	if (magic == '6') {
		if (appres.DEBUG)
			fprintf(stderr, "Reading raw PPM file, %u x %u, max. "
					"value %u.\n", width, height, maxval);
		if (maxval < 256u) {
			stat = read_8bitppm(pic_stream->fp,
					pic->pic_cache->bitmap, width, height);
			if (maxval != 255u)
				scale_to_255(pic->pic_cache->bitmap, maxval,
						rowbytes, height);
		} else {
			stat = read_16bitppm(pic_stream->fp,
					pic->pic_cache->bitmap, maxval,
					width, height);
		}
	} else { /* magic == '3' */
		if (appres.DEBUG)
			fprintf(stderr, "Reading ascii PPM file, %u x %u, max. "
					"value %u.\n", width, height, maxval);
		if (maxval == 255u)
			stat = read_asciippm(pic_stream->fp,
					pic->pic_cache->bitmap, width, height);
		else
			stat = read_ascii_max_ppm(pic_stream->fp,
					pic->pic_cache->bitmap, maxval,
					width, height);
	}

	if (stat != PicSuccess) {
		free(pic->pic_cache->bitmap);
		return stat;
	}

	/* stat == PicSuccess) */
	pic->pic_cache->bit_size.x = width;
	pic->pic_cache->bit_size.y = height;
	pic->hw_ratio = (float)height / width;
	pic->pic_cache->size_x = width * PIC_FACTOR + 0.5;
	pic->pic_cache->size_y = height * PIC_FACTOR + 0.5;
	pic->pixmap = None;
	pic->pic_cache->subtype = T_PIC_PPM;

	if (THREE_BYTEPERPIXEL) {
		if (map_to_palette(pic)) {
			stat = PicSuccess;
		} else {
			file_msg("Cannot create colormapped PPM image.");
			stat = FileInvalid;
		}
		if (appres.monochrome || tool_cells <= 2)
			map_to_mono(pic);
	} else {
		/* tell pic_create_pixmap() that this is a TrueColor pixmap */
		pic->pic_cache->numcols = -1;
	}

	return stat;
}
