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

#include <stdlib.h>
#include <X11/Intrinsic.h>	/* Boolean */
#include <png.h>

#include "resources.h"		/* IMAGE_PALETTE */

/*
 * Write PNG file from rgb data
 *
 * Call with:
 *
 * file - handle opened for writing
 * data - pointer to data (index values for IMAGE_PALETTE,
 *			   rgb triples for IMAGE_RGB)
 * type - IMAGE_PALETTE, IMAGE_RGB
 * Red, Green, Blue - colormap values for IMAGE_PALETTE type
 * numcols - number of colors for IMAGE_PALETTE type
 * width, height of image
 */

Boolean
write_png(FILE *file, unsigned char *data, int type, unsigned char *Red, unsigned char *Green, unsigned char *Blue, int numcols, int width, int height)
{
    register int    i;
    png_structp	    png_ptr;
    png_infop	    info_ptr;
    int		    bit_depth, color_type, interlace_type;
    int		    bytes_per_pixel;
    png_colorp	    palette;

    /* create the png structure */

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
		(png_voidp) NULL, NULL, NULL);
    if (!png_ptr)
	return False;

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
	png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	return False;
    }

    /* set long jump recovery here */
    if (setjmp(png_jmpbuf(png_ptr))) {
	/* if we get here there was a problem reading the file */
	png_destroy_write_struct(&png_ptr, &info_ptr);
	return False;
    }

    /* set up the output code */
    png_init_io(png_ptr, file);

    /* set info for the header */
    bit_depth = 8;
    interlace_type = PNG_INTERLACE_NONE;
    if (type == IMAGE_PALETTE) {
	color_type = PNG_COLOR_TYPE_PALETTE;
	bytes_per_pixel = 1;
    } else {
	color_type = PNG_COLOR_TYPE_RGB;
	bytes_per_pixel = 3;
    }

    /* set best compression */
    png_set_compression_level(png_ptr, 6);

    /* write the header info */
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
		 interlace_type, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    if (type == IMAGE_PALETTE) {
	palette = (png_color *) malloc(sizeof(png_color)*numcols);
	for (i=0; i<numcols; i++) {
	    palette[i].red = Red[i];
	    palette[i].green = Green[i];
	    palette[i].blue = Blue[i];
	}
	png_set_PLTE(png_ptr, info_ptr, palette, numcols);
    }

    /* write the info */
    png_write_info(png_ptr, info_ptr);

    /* finally, write the file a row at a time */
    for (i=0; i<height; i++) {
	png_write_row(png_ptr, data);
	data += width*bytes_per_pixel;
    }

    /* close the write */
    png_write_end(png_ptr, info_ptr);

    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);

    if (type == IMAGE_PALETTE) {
	/* free the palette */
	free(palette);
    }

    return True;
}
