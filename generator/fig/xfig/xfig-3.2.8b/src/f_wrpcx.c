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

#include <stdio.h>

/* structure of a PCX header */
typedef struct _pcxhead
{
	unsigned char	id;		/* 00h Manufacturer ID */
	unsigned char	vers;		/* 01h version */
	unsigned char	format;		/* 02h Encoding Scheme */
	unsigned char	bppl;		/* 03h Bits/Pixel/Plane */
	unsigned short	xmin;		/* 04h X Start (upper left) */
	unsigned short	ymin;		/* 06h Y Start (top) */
	unsigned short	xmax;		/* 08h X End (lower right) */
	unsigned short	ymax;		/* 0Ah Y End (bottom) */
	unsigned short	hdpi;		/* 0Ch Horizontal Res. */
	unsigned short	vdpi;		/* 0Eh Vertical Res. */
	unsigned char	egapal[48];	/* 10h 16-Color EGA Palette */
	unsigned char	reserv;		/* 40h reserv */
	unsigned char	nplanes;	/* 41h Number of Color Planes */
	unsigned short	blp;		/* 42h Bytes/Line/Plane */
	unsigned short	palinfo;	/* 44h Palette Interp. */
	unsigned short	hscrnsiz;	/* 46h Horizontal Screen Size */
	unsigned short	vscrnsiz;	/* 48h Vertical Screen Size */
	unsigned char	fill[54];	/* 4Ah reserv */
} pcxheadr;


static void	create_pcx_head(pcxheadr *pcxhead, int width, int height);
static void	write_pcx_head(FILE *file, pcxheadr *pcx_hd);
static void	pcx_enc_scan(FILE *file, unsigned char *inbuffer, int bufsize);

void _write_pcx(FILE *file, unsigned char *data, unsigned char *Red, unsigned char *Green, unsigned char *Blue, int numcols, int width, int height)
{
    pcxheadr	    pcxhead;
    int		    i;

    /* create the pcx header */
    create_pcx_head(&pcxhead,width,height);
    /* now write the header */
    write_pcx_head(file, &pcxhead);
    /* encode and write each scanline out */
    for (i=0; i<height; i++) {
        pcx_enc_scan(file, &data[i*width], width);
    }

    /* append a VGA palette to the output file */

    /* id for VGA palette */
    fputc(0x0c, file);

    /* Write the VGA palette */
    for (i = 0; i < numcols; i++) {
	putc(Red[i], file);
	putc(Green[i], file);
	putc(Blue[i], file);
    }
    /* fill out palette to 256 entries with 0s */
    for (i = numcols; i < 256; i++) {
	putc(0, file);
	putc(0, file);
	putc(0, file);
    }
}

/* create the pcx header */

static void
create_pcx_head(pcxheadr *pcxhead, int width, int height)
{
    int		i;

    pcxhead->id = 0x0a;		/* always 0x0a */
    pcxhead->vers = 5;		/* includes VGA plaette */
    pcxhead->format = 1;	/* 1 = RLE */
    pcxhead->bppl = 8;		/* 8 bits per pixel per plane (we'll use one plane) */
    pcxhead->xmin = 0;		/* this is stupid, make it relative to 0 */
    pcxhead->xmax = width-1;
    pcxhead->ymin = 0;
    pcxhead->ymax = height-1;
    pcxhead->hdpi = 100;	/* horiz. dpi (not really used) */
    pcxhead->vdpi = 100;	/* vert. dpi (not really used) */
    for (i=0; i<48; i++)
	pcxhead->egapal[i] = 0;	/* zero the EGA palette */
    pcxhead->nplanes = 1;	/* use one plane of 8-bits per pixel */
    pcxhead->blp = width;	/* bytes per scanline */
    pcxhead->palinfo = 1;	/* color */
    pcxhead->hscrnsiz = 0;	/* don't worry about horizontal/vertical screen size */
    pcxhead->vscrnsiz = 0;
    for (i=0; i<54; i++)
	pcxhead->fill[0]=0;
}


static void
putword(short unsigned int w, FILE *file)
{
    putc((unsigned char) (w&255), file);
    putc((unsigned char) ((w>>8)&255), file);
}

static void
write_pcx_head(FILE *file, pcxheadr *pcx_hd)
{
    register int i;

    putc(pcx_hd->id, file);
    putc(pcx_hd->vers, file);
    putc(pcx_hd->format, file);
    putc(pcx_hd->bppl, file);
    putword(pcx_hd->xmin, file);
    putword(pcx_hd->ymin, file);
    putword(pcx_hd->xmax, file);
    putword(pcx_hd->ymax, file);
    putword(pcx_hd->hdpi, file);
    putword(pcx_hd->vdpi, file);

    /* Write the EGA Palette */
    for (i = 0; i < (int)sizeof(pcx_hd->egapal); i++)
        putc(pcx_hd->egapal[i], file);

    putc(pcx_hd->reserv, file);
    putc(pcx_hd->nplanes, file);
    putword(pcx_hd->blp, file);
    putword(pcx_hd->palinfo, file);
    putword(pcx_hd->hscrnsiz, file);
    putword(pcx_hd->vscrnsiz, file);

    /* Write the reserved area at the end of the header */
    for (i = 0; i < (int)sizeof(pcx_hd->fill); i++)
        putc(pcx_hd->fill[i], file);
}

static void
pcx_enc_scan(FILE *file,
	unsigned char *inbuffer,/* Pointer to buffer holding unencoded data */
	int bufsize)		/* Size of buffer holding unencoded data */
{
    register int index = 0;	/* Index into uncompressed data buffer */
    unsigned char runcount;	/* Length of encoded pixel run */
    unsigned char runvalue;	/* Value of encoded pixel run */

    while (index < bufsize)
    {
	/*
	** Get the run count of the next pixel value run.
	**
	** Pixel value runs are encoded until a different pixel value
	** is encountered, the end of the scan line is reached, or 63
	** pixel values have been counted.
	*/
	for (runcount = 1, runvalue = inbuffer[index];
	     runvalue == inbuffer[index + runcount] &&
		    index + runcount < bufsize && runcount < 63;
	     runcount++)
		;

	/*
	** Encode the run into a one or two-byte code.
	**
	** Multiple pixel runs are stored in two-byte codes.  If a single
	** pixel run has a value of less than 64 then it is stored in a
	** one-byte code.  If a single pixel run has a value of 64 to 255
	** then it is stored in a two-byte code.
	*/
	if (runcount > 1) {			/* Multiple pixel run */
	    putc(runcount | 0xC0, file);
	    putc(runvalue, file);
	} else {                                /* Single pixel run   */
	    if (inbuffer[index] < 64) {		/* Value is 0 to 63   */
		putc(runvalue, file);
	    } else {				/* Value is 64 to 255 */
		putc(runcount | 0xC0, file);
		putc(runvalue, file);
	    }
	}
	index += runcount;  /* Jump ahead to next pixel run value */
    }
}
