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

#include <stdarg.h>
#include <stdlib.h>
#include <tiffio.h>

#include "resources.h"
#include "object.h"
#include "f_picobj.h"		/* image_size() */
#include "f_util.h"		/* map_to_palette(), map_to_mono() */
#include "w_msgpanel.h"


static void
error_handler(const char *module, const char *fmt, va_list ap)
{
	char	buffer[510];	/* usable size of tmpstr[] in w_msgpanel.c */

	vsnprintf(buffer, sizeof buffer, fmt, ap);
	file_msg("%s: %s", module, buffer);
}

/* return codes:  PicSuccess (1) : success
		  FileInvalid (-2) : invalid file
*/
int
read_tif(F_pic *pic, struct xfig_stream *restrict pic_stream)
{
	int		stat = FileInvalid;
	uint16		unit;
	uint32		w, h;
	float		res_x, res_y;
	TIFF		*tif;

	if (uncompressed_content(pic_stream))
		return FileInvalid;

	/* re-direct TIFF errors to file_msg() */
	(void)TIFFSetErrorHandler(error_handler);
	/* ignore warnings */
	(void)TIFFSetWarningHandler(NULL);

	if ((tif = TIFFOpen(pic_stream->content, "r")) == NULL)
		return stat;

	/* read image width and height */
	if (TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w) != 1) {
		TIFFClose(tif);
		return stat;
	}
        if (TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h) != 1) {
		TIFFClose(tif);
		return stat;
	}
	if (w == 0 || h == 0) {
		TIFFClose(tif);
		return stat;
	}

	/* allocate memory for image data */
	if ((pic->pic_cache->bitmap = malloc(w * h * sizeof(uint32))) == NULL) {
		file_msg("Out of memory");
		TIFFClose(tif);
		return stat;
	}

	/* get image resolution, alias density */
	if (TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &unit) != 1)
		unit = 1;
        if (TIFFGetField(tif, TIFFTAG_XRESOLUTION, &res_x) != 1 ||
			TIFFGetField(tif, TIFFTAG_XRESOLUTION, &res_y) != 1) {
		res_x = 0.0f;		/* image_size() will use a default */
		res_y = 0.0f;
		unit = 1;	/* 1 - none, 2 - per inch, 3 - per cm */
	}
	/* set pixmap properties */
	pic->pixmap = None;
	pic->pic_cache->subtype = T_PIC_TIF;
	pic->pic_cache->bit_size.x = (int)w;	/* needed in */
	pic->pic_cache->bit_size.y = (int)h;	/* map_to_palette() below */
	pic->hw_ratio = (float)h / w;
	image_size(&pic->pic_cache->size_x, &pic->pic_cache->size_y,
			pic->pic_cache->bit_size.x, pic->pic_cache->bit_size.y,
			unit == 2u ? 'i': (unit == 3u ? 'c': 'u'), res_x,res_y);

	if (appres.DEBUG)
		fprintf(stderr, "Reading TIFF image, size %d x %d, resolution "
				"%.0f x %.0f%s.\n", pic->pic_cache->bit_size.x,
				pic->pic_cache->bit_size.y, res_x, res_y,
				unit == 2u ? " pixel per inch" :
					(unit == 3u ? " pixel per cm" : "" ));

	/* read the image */
	stat = TIFFReadRGBAImageOriented(tif, w, h,
		      (uint32 *)pic->pic_cache->bitmap, ORIENTATION_TOPLEFT, 0);
	TIFFClose(tif);
	if (stat == 0) {
		if (pic->pic_cache->bitmap)
			free(pic->pic_cache->bitmap);
		return FileInvalid;
	}

	/* provide the pixmap */
	if (tool_vclass == TrueColor && image_bpp == 4 && !appres.monochrome) {
		/* either a full-color pixmap, format ARGB */
		unsigned char	*p;
		unsigned char	tmp;
#ifdef WORDS_BIGENDIAN
		/* change RGBA to ARGB */
		/* as long as the alpha channel is not used, the fastest would
		   be to read the image with an offset of one */
		p = pic->pic_cache->bitmap;
		while (p < pic->pic_cache->bitmap + w * h * sizeof(uint32)) {
			/* tmp = *(p + 3); alpha channel not used */
			*(p + 3) = *(p + 2);
			*(p + 2) = *(p + 1);
			*(p + 1) = *p;
			p += sizeof(uint32);	/* must be 4 */
		}
#else
		/* swap RGBA to BGRA */
		p = pic->pic_cache->bitmap;
		while (p < pic->pic_cache->bitmap + w * h * sizeof(uint32)) {
			tmp = *p;  *p = *(p + 2);  *(p + 2) = tmp;
			p += sizeof(uint32);	/* must be 4 */
		}
#endif
		/* indicate, that this is a TrueColor pixmap */
		pic->pic_cache->numcols = -1;

	} else { /* tool_vclass != TrueColor || .. */
		/* or a pixmap with a colormap, one byte per pixel */
		/* write BGR triples for map_to_palette */
		unsigned char	*src;
		unsigned char	*dst;
		unsigned char	tmp;

		/* write the first two triples */
		tmp = *pic->pic_cache->bitmap;
		*pic->pic_cache->bitmap = *(pic->pic_cache->bitmap + 2);
		*(pic->pic_cache->bitmap + 2) = tmp;

		src = pic->pic_cache->bitmap + 4;	/* RGBA RGBA */
		dst = pic->pic_cache->bitmap + 3;	/* BGRB GR   */
		tmp = *src;
		*dst++ = *(src + 2);
		*dst++ = *(src + 1);
		*dst++ = tmp;
		src += 4;		/* sizeof(uint32) */
		while (src < pic->pic_cache->bitmap + w * h * sizeof(uint32)) {
			*dst++ = *(src + 2);
			*dst++ = *(src + 1);
			*dst++ = *src;
			src += 4;	/* sizeof(uint32) */
		}
		pic->pic_cache->bitmap = realloc(pic->pic_cache->bitmap,
						w * h * 3 * sizeof(char));

		/* map_to_palette() reduces to 256 colors */
		pic->pic_cache->numcols = 256;
		if (!map_to_palette(pic)) {
			/* map_to_palette() frees pic->pic_cache->bitmap */
			return FileInvalid;
		}
		if (tool_cells <= 2 || appres.monochrome)
			map_to_mono(pic);
	}

	return PicSuccess;
}
