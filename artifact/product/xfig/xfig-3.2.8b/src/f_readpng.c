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

#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>		/* TrueColor, None */
#include <X11/Xlib.h>		/* XColor */

#include "resources.h"
#include "object.h"
#include "f_picobj.h"
#include "f_util.h"		/* map_to_mono(), map_to_palette() */
#include "w_msgpanel.h"		/* file_msg() */
#include "w_setup.h"		/* PIX_PER_INCH */


int
read_png(F_pic *pic, struct xfig_stream *restrict pic_stream)
{
	int		bpp;
	int		bit_depth, color_type, interlace_type;
	int		compression_type, filter_type;
	int		num_palette;
	double		scale;
	png_uint_32	i, w, h;
	png_uint_32	res_x, res_y;
	png_uint_32	row_bytes;
	png_bytep	*row_pointers;
	png_structp	png_ptr;
	png_infop	info_ptr;
	png_color_16	background;
	png_colorp	palette;

	if (!rewind_stream(pic_stream))
		return FileInvalid;

	/* read the png file here */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
			(png_voidp)NULL, NULL, NULL);
	if (!png_ptr) {
		return FileInvalid;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL,
					(png_infopp)NULL);
		return FileInvalid;
	}
	/*
	 * According to the png specification,
	 * http://www.w3.org/TR/2003/REC-PNG-20031110, all chunks which we are
	 * interested in must appear before the image data. Hence, we do not
	 * need a second info pointer, end_info. The latter would be created
	 * like info_ptr above,  end_info = png_create_info_struct(png_ptr),
	 * but _after_ reading the image data, I believe.
	 */

	/* set long jump recovery here */
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* if we get here there was a problem reading the file */
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		if (pic->pic_cache->bitmap)
			free(pic->pic_cache->bitmap);
		return FileInvalid;
	}

	/* set up the input code */
	png_init_io(png_ptr, pic_stream->fp);

	/* now read the file info */
	png_read_info(png_ptr, info_ptr);

	/* get width, height etc */
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type,
			&interlace_type, &compression_type, &filter_type);
	if (appres.DEBUG)
		fprintf(stderr, "Reading PNG image %u x %u, bit depth %d, %s "
			"alpha channel, %s, %s color map.\n", w, h, bit_depth,
			color_type & PNG_COLOR_MASK_ALPHA ? "with" : "without",
			color_type & PNG_COLOR_MASK_COLOR? "color": "grayscale",
			color_type & PNG_COLOR_MASK_PALETTE ? "with" : "no");

	/* get resolution, pixels per meter! */
	if (png_get_pHYs(png_ptr, info_ptr, &res_x, &res_y, &bpp) == 0 ||
			bpp != PNG_RESOLUTION_METER) {
		/* default is 72 pixels per inch */
		res_x = 2835U; /* round(72. * 100. / 2.54); */
		res_y = res_x;
	}

	/* bitmaps */
	/*
	 * For bitmaps with different colors than white and black, one would
	 * (i) have to pass the color information into the pic object, and
	 * (ii) process this information also for all other bitmap image types.
	 * Therefore, currently only process black / white bitmaps as bitmaps.
	 */
	if (bit_depth == 1 &&
		/* For black/white, a 0 bit refers to black and 1 to white.
		   Otherwise, use png_set_invert_mono(png_ptr). */
		png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette) &&
		num_palette == 2 && palette[0].red == 0 && palette[0].green == 0
		&& palette[0].blue == 0 && palette[1].red == 255 &&
		palette[1].green == 255 && palette[1].blue == 255) {
		/* swap the order of bits packed into bytes
		   - this is probably necessary for big-endian platforms */
		/* png_set_packswap(png_ptr); */

		row_bytes = (w + 7) / 8;
		bpp = 1;	/* not true, but good enough for the overflow
				   checking further below */

		pic->pic_cache->numcols = 0;

	/* grayscale or full color images */
	} else {
		if (appres.DEBUG)
			fputs("Convert png to a full color pixmap.\n", stderr);

		double gamma = 0.45455;
		png_get_gAMA(png_ptr, info_ptr, &gamma);
		png_set_gamma(png_ptr, 2.2, gamma);

		/* remove the alpha channel and provide a background */
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_bKGD)) {
			/* set the background to the one supplied */
			png_color_16p	bkgd;
			png_get_bKGD(png_ptr, info_ptr, &bkgd);
			png_set_background(png_ptr, bkgd,
					PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
		} else {
			/* blend the canvas background using the alpha channel*/
			background.red   = x_bg_color.red >> 8;
			background.green = x_bg_color.green >> 8;
			background.blue  = x_bg_color.blue >> 8;
			background.gray  = 0;
			png_set_background(png_ptr, &background,
					PNG_BACKGROUND_GAMMA_SCREEN, 0, 2.2);
		}

		/* strip 16-bit RGB values down to 8-bit */
		if (bit_depth == 16)
#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
			png_set_scale_16(png_ptr);
#else
		png_set_strip_16(png_ptr);
#endif

		/* force to 8-bits per pixel if less than 8 */
		if (bit_depth < 8) {
			png_set_packing(png_ptr);
			bit_depth = 8;
		}

		/* convert grayscale to RGB */
		if (!(color_type & PNG_COLOR_MASK_COLOR))
			png_set_gray_to_rgb(png_ptr);

		/* expand paletted colors to RGB triplets */
		if (color_type & PNG_COLOR_MASK_PALETTE)
			png_set_palette_to_rgb(png_ptr);
		/* png_set_palette_to_rgb() and png_set_tRNS_to_alpha() are
		   aliases to png_set_expand() */

		/* swap rgb to bgr triples */
		/* this is probably not correct for big-endian architectures */
		png_set_bgr(png_ptr);

		if (tool_vclass == TrueColor && image_bpp == 4 &&
						!appres.monochrome) {
			/* write BGRA quadruplets, with fully opaque alpha */
			png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
			/* one can not use png_set_add_alpha(), or
			   png_set_tRNS_to_alpha(), because those would be
			   contradictory to removing the alpha channel with
			   png_set_background() above. */

			bpp = 4;
			pic->pic_cache->numcols = -1;
		} else {
			bpp = 3;
			/* map_to_palette() reduces to 256 colors */
			pic->pic_cache->numcols = 256;
		}
		row_bytes = w * bpp;

	} /* end if bitmap or color */

	/* allocate memory for the image */
	if (h > PNG_UINT_32_MAX / sizeof(png_byte)) {
		file_msg("PNG image is too tall to process in memory.");
		return FileInvalid;
	}
	if (w > PNG_UINT_32_MAX / bpp) {
		file_msg("PNG image is too wide to process in memory.");
		return FileInvalid;
	}
	if (h > PNG_SIZE_MAX / row_bytes) {
		file_msg("PNG image would be too large.");
		return FileInvalid;
	}

	pic->pic_cache->bitmap = malloc(h * row_bytes);
	if (pic->pic_cache->bitmap == NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		file_msg("Out of memory.");
		return FileInvalid;
	}
	row_pointers = malloc(h * sizeof(png_bytep));
	for (i = 0; i < h; ++i)
		row_pointers[i] = pic->pic_cache->bitmap + i * row_bytes;

	/* finally, read the file */
	png_read_image(png_ptr, row_pointers);

	/* clean up */
	png_read_end(png_ptr, (png_infop)NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

	/* assign width, height and other information to pic object */
	/* bit_size is needed in map_to_palette() below */
	pic->pic_cache->bit_size.x = (int)w;
	pic->pic_cache->bit_size.y = (int)h;
	pic->pic_cache->subtype = T_PIC_PNG;
	pic->pixmap = None;
	pic->hw_ratio = (float)pic->pic_cache->bit_size.y /
			pic->pic_cache->bit_size.x;

	if (appres.INCHES)
		scale = PIX_PER_INCH * 100. / 2.54;
	else
		scale = PIX_PER_CM * 100.;
	pic->pic_cache->size_x = w * scale / res_x + 0.5;
	pic->pic_cache->size_y = h * scale / res_y + 0.5;

	if (bit_depth != 1) {
		/* use neural net to reduce to 256 colors with palette */
		if (tool_vclass != TrueColor || image_bpp != 4 ||
				appres.monochrome) {
			if (!map_to_palette(pic))
				return FileInvalid;
		}
		/* map_to_mono() needs an image with palette */
		if (tool_cells <= 2 || appres.monochrome)
			map_to_mono(pic);
	}

	return PicSuccess;
}
