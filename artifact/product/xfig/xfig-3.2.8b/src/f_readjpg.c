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

/* The following code is from the example.c file in the JPEG distribution */

/* Here is their copyright notice:
 *
 * The authors make NO WARRANTY or representation, either express or implied,
 * with respect to this software, its quality, accuracy, merchantability, or
 * fitness for a particular purpose.  This software is provided "AS IS", and
 * you, its user, assume the entire risk as to its quality and accuracy.
 *
 * This software is copyright (C) 1991-1996, Thomas G. Lane.
 * All Rights Reserved except as specified below.
 *
 * Permission is hereby granted to use, copy, modify, and distribute this
 * software (or portions thereof) for any purpose, without fee, subject to these
 * conditions:
 * (1) If any part of the source code for this software is distributed, then
 * this README file must be included, with this copyright and no-warranty notice
 * unaltered; and any additions, deletions, or changes to the original files
 * must be clearly indicated in accompanying documentation.
 * (2) If only executable code is distributed, then the accompanying
 * documentation must state that "this software is based in part on the work of
 * the Independent JPEG Group".
 * (3) Permission for use of this software is granted only if the user accepts
 * full responsibility for any undesirable consequences; the authors accept
 * NO LIABILITY for damages of any kind.
 *
 * These conditions apply to any software derived from or based on the IJG code,
 * not just to the unmodified library.  If you use our work, you ought to
 * acknowledge us.
 *
 * Permission is NOT granted for the use of any IJG author's name or company
 * name in advertising or publicity relating to this software or products
 * derived from it.  This software may be referred to only as "the Independent
 * JPEG Group's software".
 *
 * We specifically permit and encourage the use of this software as the basis of
 * commercial products, provided that all warranty or liability claims are
 * assumed by the product vendor.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"	/* restrict */
#endif

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* jpeglib.h does not include some standard headers, but needs them */
#include <jpeglib.h>
#include <X11/X.h>	/* TrueColor, None */

#include "resources.h"
#include "object.h"
#include "f_picobj.h"
#include "f_util.h"
#include "w_msgpanel.h"


static void	error_exit(j_common_ptr cinfo);
static void	error_output(j_common_ptr cinfo);
static int	read_JPEG_file(FILE *file, F_pic *pic);


/* return codes:  PicSuccess (1) : success
		  FileInvalid (-2) : invalid file
*/
int
read_jpg(F_pic *pic, struct xfig_stream *restrict pic_stream)
{
	if (!rewind_stream(pic_stream))
		return FileInvalid;

	if (read_JPEG_file(pic_stream->fp, pic)) {
		return FileInvalid;
	}
	if (tool_cells <= 2 || appres.monochrome)
		map_to_mono(pic);

	return PicSuccess;
}


/*
 * Return codes: 0 - success, (-1) - failure
 */
static int
read_JPEG_file(FILE *file, F_pic *pic)
{
	int				i;
	size_t				bitmap_row;	/* row size of bitmap */
	static jmp_buf			setjmp_buffer;
	struct jpeg_decompress_struct	cinfo;
	struct jpeg_error_mgr		jerr;		/* error handler */

	/* Step 1: allocate and initialize JPEG decompression object */

	/* Set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = error_exit;
	jerr.output_message = error_output;
	cinfo.client_data = (void *)&setjmp_buffer;

	/* Establish the setjmp return context for error_exit to use. */
	if (setjmp(setjmp_buffer)) {
		/* an error has occured */
		jpeg_destroy_decompress(&cinfo);
		if (pic->pic_cache->bitmap != NULL)
			free(pic->pic_cache->bitmap);
		return -1;
	}
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (i.e. our file) */

	jpeg_stdio_src(&cinfo, file);

	/* Step 3: read file parameters with jpeg_read_header() */

	(void)jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	 *   (a) suspension is not possible with the stdio data source, and
	 *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	 * See libjpeg.doc for more info.
	 */

	if (tool_vclass == TrueColor && image_bpp == 4 && !appres.monochrome) {
#ifdef JCS_EXTENSIONS
#ifdef WORDS_BIGENDIAN
		cinfo.out_color_space = JCS_EXT_XRGB;
#else
		cinfo.out_color_space = JCS_EXT_BGRX;
#endif
#else
		cinfo.out_color_space = JCS_RGB;
#endif
		bitmap_row = 4 * cinfo.image_width;
	} else {
		/* colormapped color space */
		cinfo.quantize_colors = TRUE;
		/*
		 * Defaults:
		 * cinfo.two_pass_quantize = TRUE;  (Use a custom colormap by
		 *			making an extra pass over the image.)
		 * cinfo.desired_number_of_colors = 256;
		 */
		bitmap_row = cinfo.image_width;
	}


	/* Now fill in the pic parameters */

	pic->pic_cache->bitmap = malloc(bitmap_row * cinfo.image_height);
	if (pic->pic_cache->bitmap == NULL) {
		file_msg("Can't alloc memory for JPEG image");
		jpeg_destroy_decompress(&cinfo);
		return -1;
	}

	/* Step 4: set parameters for decompression */

	/* Step 5: Start decompressor */

	jpeg_start_decompress(&cinfo);

	/*
	 * We may need to do some setup of our own at this point before reading
	 * the data.  After jpeg_start_decompress() we have the correct scaled
	 * output image dimensions available, as well as the output colormap
	 * if we asked for color quantization.
	 */

	/*
	 * Step 6: Read the image into the bitmap:
	 *	while (scan lines remain to be read)
	 *		jpeg_read_scanlines(...);
	 */
	if (tool_vclass == TrueColor && image_bpp == 4 && !appres.monochrome) {
#ifdef JCS_EXTENSIONS	/* cinfo.output_components == 4, BGRX color space */
		JSAMPROW	one_row;

		while (cinfo.output_scanline < cinfo.output_height) {
			one_row = pic->pic_cache->bitmap +
					cinfo.output_scanline * bitmap_row;
			/* slow modes (the default) return only one scanline at
			   a time, even if more are requested */
			(void)jpeg_read_scanlines(&cinfo, &one_row, 1);
		}
#else	/* cinfo.output_components == 3 */
		JSAMPARRAY	buffer;
		JSAMPLE		*src;
		unsigned char	*pos = pic->pic_cache->bitmap;
		buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo,
				JPOOL_IMAGE, cinfo.output_width *
						cinfo.output_components, 1);
		while (cinfo.output_scanline < cinfo.output_height) {
			(void)jpeg_read_scanlines(&cinfo, buffer, 1);
			src = buffer[0];
			for (i = 0; (unsigned)i < cinfo.output_width; ++i) {
#ifdef WORDS_BIGENDIAN
				*pos++ = *src++;
				*pos++ = *src++;
				*pos++ = *src++;
				++pos;
#else
				*(pos + 2) = *src++;
				*(pos + 1) = *src++;
				*pos = *src++;
				pos += image_bpp;
#endif
			}
		}
#endif
		/* indicate, that this is a TrueColor bitmap */
		pic->pic_cache->numcols = -1;

	} else { /* tool_vclass != TrueColor || .. */
		/* colormapped jpeg */
		int	r, g, b;

		/* this here below is the same code as for TrueColor visuals
		   with BGRX color space above */
		JSAMPROW	one_row;
		while (cinfo.output_scanline < cinfo.output_height) {
			one_row = pic->pic_cache->bitmap +
				cinfo.output_scanline * bitmap_row;
			/* slow modes (the default) return only one scanline at
			 * a time, even if more are requested */
			(void)jpeg_read_scanlines(&cinfo, &one_row, 1);
		}


		/* Step 7: fill up the colortable in the pic object */

		pic->pic_cache->numcols = cinfo.actual_number_of_colors;

		if (cinfo.out_color_components == 3) {
			r = 0;
			g = 1;
			b = 2;
		} else { /* cinfo.out_color_components == 1 */
			r = 0;
			g = 0;
			b = 0;
		}
		for (i = 0; i < pic->pic_cache->numcols; ++i) {
			pic->pic_cache->cmap[i].red = cinfo.colormap[r][i];
			pic->pic_cache->cmap[i].green = cinfo.colormap[g][i];
			pic->pic_cache->cmap[i].blue = cinfo.colormap[b][i];
		}

	}	/* if (tool_vlass == TrueColor && .. */

	/* Step 8: Finish decompression */

	(void)jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	 * with the stdio data source.
	 */

	/* Step 9: Release JPEG decompression object */

	jpeg_destroy_decompress(&cinfo);

	/* At this point you may want to check to see whether any corrupt-data
	 * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	 */
	/* jpeglib anyhow calls error_output(), see below, for warnings,
	   hence warnings are already displayed. The code below is useless. */
	/*
	 * if (jerr.num_warnings > 0) {
	 *	file_msg("Probably invalid jpeg file, message:");
	 *	error_output((j_common_ptr)&cinfo);
	 * }
	 */

	/* fill the pic struct */
	pic->pixmap = None;
	pic->pic_cache->subtype = T_PIC_JPEG;
	pic->pic_cache->bit_size.x = (int)cinfo.image_width;
	pic->pic_cache->bit_size.y = (int)cinfo.image_height;
	pic->hw_ratio = (float)cinfo.image_height / cinfo.image_width;
	image_size(&pic->pic_cache->size_x, &pic->pic_cache->size_y,
			pic->pic_cache->bit_size.x, pic->pic_cache->bit_size.y,
			cinfo.density_unit == 1u ? 'i' :
					(cinfo.density_unit == 2u ? 'c': 'u'),
			(float)cinfo.X_density, (float)cinfo.Y_density);

	return 0;
}


/*
 * The standard error_exit() method of libjpeg calls exit(). Replace the
 * standard error_exit() method with this routine here, which
 * returns control to the caller.
 */

static void
error_exit (j_common_ptr cinfo)
{
	char	buffer[JMSG_LENGTH_MAX];

	/* Display the message if it is NOT "Not a JPEG file" */
	/* However, since the error number is not public, parse the string */

	/* Format the message */
	(*cinfo->err->format_message)(cinfo, buffer);

	if (strncmp(buffer, "Not a JPEG file", 15) != 0)
		file_msg("%s", buffer);

	/* Return control to the setjmp point */
	longjmp(*(jmp_buf *)cinfo->client_data, 1);
}

static void
error_output(j_common_ptr cinfo)
{
	char	buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message)(cinfo, buffer);
	file_msg("%s", buffer);
}
