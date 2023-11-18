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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "fig2dev.h"
#include "object.h"
#include "messages.h"
#include "readpics.h"

/* return codes:  1 : success
		  0 : invalid file
*/

int
read_png(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
    int    i;
    int		    bit_depth, color_type, interlace_type;
    int		    compression_type, filter_type;
    png_uint_32	    j, w, h;
    png_structp	    png_ptr;
    png_infop	    info_ptr;
    size_t	    row_bytes;
    png_bytep	   *row_pointers;
    double          gamma;

    if (!rewind_stream(pic_stream))
	return 0;
    *llx = *lly = 0;

    /* read the png file here */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		(png_voidp) NULL, NULL, NULL);
    if (!png_ptr)
	return 0;

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
	png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
	return 0;
    }

    /*
     * According to the png specification,
     * http://www.w3.org/TR/2003/REC-PNG-20031110, all chunks which are of
     * interest here must appear before the image data. Hence, a second info
     * pointer, end_info, is not needed. The latter would be created similarly
     * to info_ptr above,  end_info = png_create_info_struct(png_ptr),
     * but _after_ reading the image data, I believe.
     */

    /* set long jump here */
    if (setjmp(png_jmpbuf(png_ptr))) {
	/* if we get here there was a problem reading the file */
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
	return 0;
    }

    /* set up the input code */
    png_init_io(png_ptr, pic_stream->fp);

    /* now read the file info */
    png_read_info(png_ptr, info_ptr);

    /* get width, height etc */
    png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type,
	&interlace_type, &compression_type, &filter_type);

    if (png_get_gAMA(png_ptr, info_ptr, &gamma))
	png_set_gamma(png_ptr, 2.2, gamma);
    else
	png_set_gamma(png_ptr, 2.2, 0.45455);

    /* force to 8-bits per pixel if less than 8
       this works both for palette and rgb images */
    if (bit_depth < 8)
	png_set_packing(png_ptr);

    /* reduce 16 bit to 8 bit */
    if (bit_depth == 16)
#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
	png_set_scale_16(png_ptr);
#else
	png_set_strip_16(png_ptr);
#endif

    /*
     * Image data is transformed to 8 bit rgb data, or to indexed data with
     * maximum 256 color map entries. The data always has 1 byte per pixel,
     * regardless of bit_depth. Alpha channels are removed by compositing
     * with a background. For the application of transformations, the matrix at
     * line 1800 of file libpng-manual.txt was most useful. We are interested in
     * conversions to, as is denoted there, "0" - grayscale, "2" - rgb color.
     * Palette images are basically not transformed (except transparency color
     * blending?).
     */

    /* color png */
    if (color_type & PNG_COLOR_MASK_COLOR) {
	/* strip 16-bit RGB values down to 8-bit
	   pngs with a palette have a maximum bit_depth of 8 */
	if (bit_depth == 16)
#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
		png_set_scale_16(png_ptr);
#else
		png_set_strip_16(png_ptr);
#endif

	/* user wants grayscale, map to gray */
	if (grayonly) {

	    /* this works for palette as well as rgb image data;
	       creates 8 bit grayscale data */
	    png_set_rgb_to_gray(png_ptr, 1, 0.3, 0.59);
	    /* default is: 0.2126 * r + 0.7152 * g + 0.0722 * b */

	    /* add a grayscale palette */
	    for (i = 0; i < 256; ++i)
		pic->cmap[RED][i] = pic->cmap[GREEN][i] = pic->cmap[BLUE][i] =
			(unsigned char)i;
	    pic->numcols = 256;
	/* else, copy a color palette */
	} else if (color_type & PNG_COLOR_MASK_PALETTE) {
	    int		num_palette;
	    png_colorp	palette;

	    if (png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette)) {
		for (i = 0; i < num_palette; ++i) {
		    pic->cmap[RED][i]   = palette[i].red;
		    pic->cmap[GREEN][i] = palette[i].green;
		    pic->cmap[BLUE][i]  = palette[i].blue;
		}
		pic->numcols = num_palette;
	    } else {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		put_msg("Could not read color palette of png image %s.",
			pic->file);
		return 0;
	    }
	} else {
	    /* RGB png images can have bit_depths of 8 or 16 */
	    pic->numcols = 1 << 24;
	}

    /* grayscale images */
    } else { /* color_type & PNG_COLOR_MASK_COLOR */

	/* write the grayscale as indexed image, produce the colormap */
	for (i = 0; i < 1<<bit_depth; ++i)
		pic->cmap[RED][i] = pic->cmap[GREEN][i] = pic->cmap[BLUE][i] =
			(unsigned char)(i * 255 / ((1<<bit_depth) - 1));
		/* (1<<bit_depth) - 1 is either 1, 3, 15 or 255 for bit depths
						of 1, 2, 4 or 8, respectively */
	pic->numcols = 1 << bit_depth;
    }

    /* transparency */
    /* transparency given as color value in a tRNS chunk */
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
	    unsigned char	*trans_alpha;
	    int			num_trans;
	    png_color_16p	trans_color;

	    png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans,
			    &trans_color);

	    if (color_type && PNG_COLOR_MASK_PALETTE) {
		    pic->transp_cols = pic->transp_col;
		    if (num_trans > 3 && (pic->transp_cols = malloc(num_trans))
				    == NULL)
			    num_trans = 3;
		    for (i = 0; i < num_trans; ++i)
			    pic->transp_cols[i] = trans_alpha[i];
		    pic->num_transp = num_trans;
	    } else { /* tRNS must have returned a RGB value */
		    if (color_type & PNG_COLOR_MASK_COLOR) {
			    if (bit_depth == 16) {
				    pic->transp_col[RED] =
					    ((int)trans_color->red + 0x80) >> 8;
				    pic->transp_col[GREEN] =
					    ((int)trans_color->green + 0x80)>>8;
				    pic->transp_col[BLUE] =
					    ((int)trans_color->blue + 0x80) >>8;
			    } else {
				    pic->transp_col[RED] = trans_color->red;
				    pic->transp_col[GREEN] = trans_color->green;
				    pic->transp_col[BLUE] = trans_color->blue;
			    }
		    } else { /* GRAYSCALE */
			    if (bit_depth == 16) {
				    pic->transp_col[RED] =
					    pic->transp_col[GREEN] =
					    pic->transp_col[BLUE] =
						    trans_color->gray >> 8;
			    } else { /* 1, 2, 4, or 8 bit_depth; */
				    int      mul = 255 / ((1 << bit_depth) - 1);
				    pic->transp_col[RED] =
					    pic->transp_col[GREEN] =
					    pic->transp_col[BLUE] =
						    trans_color->gray * mul;
			    }
		    }
		    pic->num_transp = TRANSP_COLOR;
	    }
    /* Full transparency, a png with an alpha channel. Composite with an
     * background, and set the background color as the transparent color. */
    } else if (color_type & PNG_COLOR_MASK_ALPHA) {
	    png_color_16p	file_background;
	    png_color_16	png_background;

	    if (png_get_bKGD(png_ptr, info_ptr, &file_background)) {
		    /* use the background supplied in the png file */
		    png_set_background(png_ptr, file_background,
				    PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
		    pic->transp_col[RED] = file_background->red;
		    pic->transp_col[GREEN] = file_background->green;
		    pic->transp_col[BLUE] = file_background->blue;
	    } else if (bgspec) {
		    /* blend with the user-supplied background color */
		    png_background.red   = pic->transp_col[RED] =
			    background.red >> 8;
		    png_background.green = pic->transp_col[GREEN] =
			    background.green >> 8;
		    png_background.blue  = pic->transp_col[BLUE] =
			    background.blue >> 8;
		    png_background.gray  = 0;
		    png_set_background(png_ptr, &png_background,
				    PNG_BACKGROUND_GAMMA_SCREEN, 0, 2.2);
	    } else {
		/* use white */
		    png_background.red = png_background.green =
			    png_background.blue = png_background.gray =
			    pic->transp_col[RED] = pic->transp_col[GREEN] =
			    pic->transp_col[BLUE] = 255;
		    png_set_background(png_ptr, &png_background,
				    PNG_BACKGROUND_GAMMA_SCREEN, 0, 2.2);
	    }
	    pic->num_transp = TRANSP_COLOR;
    }

    /* done with transformations */

    /* allocate memory for the image */
    png_read_update_info(png_ptr, info_ptr);	/* re-compute row_bytes */
    row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    if (h > PNG_UINT_32_MAX / sizeof(png_byte)) {
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	put_msg("PNG image %s is too tall to process in memory.", pic->file);
	return 0;
    }
    if (row_bytes > PNG_UINT_32_MAX) {
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	put_msg("PNG image %s is too wide to process in memory.", pic->file);
	return 0;
    }
    if (h > PNG_SIZE_MAX / row_bytes) {
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	put_msg("PNG image %s would be too large.", pic->file);
	return 0;
    }

    pic->bitmap = malloc(h * row_bytes);
    if (pic->bitmap == NULL) {
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	put_msg(Err_mem);
	return 0;
    }
    row_pointers = malloc(h * sizeof(png_bytep));
    for (j = 0; j < h; ++j)
	row_pointers[j] = pic->bitmap + j * row_bytes;

    /* finally, read the file */
    png_read_image(png_ptr, row_pointers);

    /* clean up */
    png_read_end(png_ptr, (png_infop)NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    free(row_pointers);

    /* put in width, height */
    pic->subtype = P_PNG;
    pic->bit_size.x = w;
    pic->bit_size.y = h;
    pic->hw_ratio = (float) pic->bit_size.y / pic->bit_size.x;

    return 1;
}
