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

/* --------------------------------------------------------------------
 * jpeg2ps
 * convert JPEG files to compressed PostScript Level 2 or 3 EPS
 *
 * (C) Thomas Merz 1994-2002
 * Used with permission 19-03-2002
 * Adapted from Version 1.9 for fig2dev by Brian V. Smith 19-03-2002
 *
 * ------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE__SETMODE	/* see fig2dev.c */
#include <io.h>
#include <fcntl.h>
#endif

#include "fig2dev.h"	/* includes "bool.h" */
#include "object.h"
#include "encode.h"
#include "creationdate.h"
#include "messages.h"
#include "readpics.h"

/* data output mode: binary, ascii85, hex-ascii */
typedef enum { BINARY, ASCII85, ASCIIHEX } DATAMODE;

static struct imagedata {
	FILE	*fp;		/* file pointer for jpeg file		*/
	char	*filename;	/* name of image file			*/
	int	width;		/* pixels per line			*/
	int	height;		/* rows					*/
	int	components;	/* number of color components		*/
	int	bits_per_component; /* bits per color component		*/
	float	dpi;		/* image resolution in dots per inch	*/
	DATAMODE	mode;	/* output mode: 8bit, ascii, ascii85	*/
	bool	adobe;		/* image includes Adobe comment marker	*/
} image;

#define	DPI_IGNORE (float)(-1.0)  /* dummy value for imagedata.dpi	*/
#define DPI_USE_FILE ((float)0.0) /* dummy value for imagedata.dpi	*/

static	bool	AnalyzeJPEG(void);

/*
 * Read data from in, ascii85 encode it, and write to out.
 */
static int
write_ascii85(FILE *in, FILE *out)
{
	unsigned char	buf[65536];	/* MUST be a multiple of 4 */
	size_t		n;

	while (!feof(in)) {
		n = fread(buf, 1, sizeof buf, in);
		if (ferror(in)) {
			err_msg("Error reading jpg file");
			return -1;
		}
		if (ascii85encode(out, buf, n)) {
			put_msg("Error when writing jpeg data to "
					"PostScript output.");
			return -1;
		}
	}
	/* end of data marker */
	fputs("~>\n", out);
	return 0;
}


/*
 * read the jpeg file header to get the pertinent info and
 * put it in pic struct
 */
int
read_jpg(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	/* setup internal header */
	image.mode	= ASCII85;	/* we won't use the BINARY mode */
	image.dpi	= DPI_IGNORE;	/* ignore any DPI info from JPEG file */
	image.adobe	= false;
	image.fp	= pic_stream->fp;
	image.filename	= pic->file;

	/* read image parameters and fill image struct */
	if (!rewind_stream(pic_stream) || !AnalyzeJPEG())
		return 0;

	*llx = *lly = 0;
	pic->bit_size.x = image.width;
	pic->bit_size.y = image.height;

	/* output PostScript comment */
	fprintf(tfp, "%% Begin Imported JPEG File: %s\n\n", pic->file);

	/* number of colors, size and bitmap is put in by read_JPEG_file() */
	pic->subtype = P_JPEG;
	return 1;			/* all ok */
}

/* here's where we read the rest of the jpeg file and format for PS */
void
JPEGtoPS(FILE *f, FILE *PSfile) {
	size_t	 n;
	int		 i;
	char		 date_buf[CREATION_TIME_LEN];
	char		buffer[BUFSIZ];
	char *const	ColorSpaceNames[] = {"", "Gray", "", "RGB", "CMYK" };


	/* produce EPS header comments */
	fprintf(PSfile, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(PSfile, "%%%%Creator: jpeg2ps by Thomas Merz in fig2dev %s\n",
			PACKAGE_VERSION);
	fprintf(PSfile, "%%%%Title: %s\n", image.filename);
	if (creation_date(date_buf))
		fprintf(PSfile, "%%%%CreationDate: %s\n", date_buf);
	fprintf(PSfile, "%%%%BoundingBox: %d %d %d %d\n",
			0, 0, image.width, image.height);
	fprintf(PSfile, "%%%%DocumentData: %s\n",
			image.mode == BINARY ? "Binary" : "Clean7Bit");
	fprintf(PSfile, "%%%%LanguageLevel: 2\n");
	fprintf(PSfile, "%%%%EndComments\n");
	fprintf(PSfile, "%%%%BeginProlog\n");
	fprintf(PSfile, "%%%%EndProlog\n");

	fprintf(PSfile, "/languagelevel where {pop languagelevel 2 lt}");
	fprintf(PSfile, "{true} ifelse {\n");
	fprintf(PSfile, "  (JPEG file '%s' needs PostScript Level 2!",
			image.filename);
	fprintf(PSfile, "\\n) dup print flush\n");
	fprintf(PSfile, "  /Helvetica findfont 20 scalefont setfont ");
	fprintf(PSfile, "100 100 moveto show showpage stop\n");
	fprintf(PSfile, "} if\n");

	fprintf(PSfile, "save\n");
	fprintf(PSfile, "/RawData currentfile ");

	if (image.mode == ASCIIHEX)		 /* hex representation... */
		fprintf(PSfile, "/ASCIIHexDecode filter ");
	else if (image.mode == ASCII85)	 /* ...or ASCII85	  */
		fprintf(PSfile, "/ASCII85Decode filter ");
	/* else binary mode: don't use any additional filter! */

	fprintf(PSfile, "def\n");

	fprintf(PSfile, "/Data RawData << ");
	fprintf(PSfile, ">> /DCTDecode filter def\n");

	fprintf(PSfile, "/Device%s setcolorspace\n",
			ColorSpaceNames[image.components]);
	fprintf(PSfile, "{ << /ImageType 1\n");
	fprintf(PSfile, "	/Width %d\n", image.width);
	fprintf(PSfile, "	/Height %d\n", image.height);
	fprintf(PSfile, "	/ImageMatrix [ %d 0 0 %d 0 %d ]\n",
			image.width, -image.height, image.height);
	fprintf(PSfile, "	/DataSource Data\n");
	fprintf(PSfile, "	/BitsPerComponent %d\n",
			image.bits_per_component);

	/* workaround for color-inverted CMYK files produced by Adobe Photoshop:
	 * compensate for the color inversion in the PostScript code
	 */
	if (image.adobe && image.components == 4) {
		/* fprintf(stderr, "Note: Adobe-conforming CMYK file - applying"
		   " workaround for color inversion.\n"); */
		fprintf(PSfile, "	  /Decode [1 0 1 0 1 0 1 0]\n");
	}else {
		fprintf(PSfile, "	  /Decode [0 1");
		for (i = 1; i < image.components; i++)
			fprintf(PSfile," 0 1");
		fprintf(PSfile, "]\n");
	}

	fprintf(PSfile, "  >> image\n");
	fprintf(PSfile, "  Data closefile\n");
	fprintf(PSfile, "  RawData flushfile\n");
	fprintf(PSfile, "  restore\n");
	fprintf(PSfile, "} exec");

	switch (image.mode) {
	case BINARY:
		/* important: ONE blank and NO newline */
		fputc(' ', PSfile);
#ifdef HAVE__SETMODE
		fflush(PSfile);	  /* up to now we have CR/NL mapping */
		_setmode(fileno(PSfile), O_BINARY);  /* binary mode */
#endif
		/* copy data without change */
		while ((n = fread(buffer, 1, sizeof(buffer), f)) != 0)
			fwrite(buffer, 1, n, PSfile);
#ifdef HAVE__SETMODE
		fflush(PSfile);				/* binary yet */
		_setmode(fileno(PSfile), O_TEXT);	/* text mode */
#endif
		break;

	case ASCII85:
		fputc('\n', PSfile);
		if (write_ascii85(f, PSfile))
			exit(EXIT_FAILURE);
		break;

	case ASCIIHEX:	/* this code is never called */
		fputc('\n', PSfile);
		while (!feof(f)) {
			int		j;
			n = fread(buffer, 1, sizeof buffer, f);
			for (i = 0; i < (int)(n / 80); ++i) {
				int	j = 0;
				while (j++ < 80)
					fprintf(PSfile, "%.2hhx",
							*(buffer + i * 80 + j));
				fputc('\n', PSfile);
			}
			while ((j = i * 80) < (int)n)
				fprintf(PSfile, "%.2hhx", *(buffer + j));
		}
		/* end of data marker */
		fputs(">\n", PSfile);
		break;
	}
}

/* The following enum is stolen from the IJG JPEG library
 * Comments added by tm
 */

typedef enum {		/* JPEG marker codes			*/
	M_SOF0  = 0xc0,		/* baseline DCT				*/
	M_SOF1  = 0xc1,		/* extended sequential DCT		*/
	M_SOF2  = 0xc2,		/* progressive DCT			*/
	M_SOF3  = 0xc3,		/* lossless (sequential)		*/

	M_SOF5  = 0xc5,		/* differential sequential DCT		*/
	M_SOF6  = 0xc6,		/* differential progressive DCT		*/
	M_SOF7  = 0xc7,		/* differential lossless		*/

	M_SOF9  = 0xc9,		/* extended sequential DCT		*/
	M_SOF10 = 0xca,		/* progressive DCT			*/
	M_SOF11 = 0xcb,		/* lossless (sequential)		*/

	M_SOF13 = 0xcd,		/* differential sequential DCT		*/
	M_SOF14 = 0xce,		/* differential progressive DCT		*/
	M_SOF15 = 0xcf,		/* differential lossless		*/

	M_RST0  = 0xd0,		/* restart				*/
	M_RST1  = 0xd1,		/* restart				*/
	M_RST2  = 0xd2,		/* restart				*/
	M_RST3  = 0xd3,		/* restart				*/
	M_RST4  = 0xd4,		/* restart				*/
	M_RST5  = 0xd5,		/* restart				*/
	M_RST6  = 0xd6,		/* restart				*/
	M_RST7  = 0xd7,		/* restart				*/

	M_SOI   = 0xd8,		/* start of image			*/
	M_EOI   = 0xd9,		/* end of image				*/

	M_APP0  = 0xe0,		/* application marker, used for JFIF	*/
	M_APP14 = 0xee,		/* application marker, used by Adobe	*/

	M_TEM   = 0x01,		/* temporary use			*/

	M_ERROR = 0x100		/* dummy marker, internal use only	*/
} JPEG_MARKER;

/*
 * The following routine used to be a macro in its first incarnation:
 *  #define get_2bytes(fp) ((unsigned int) (getc(fp) << 8) + getc(fp))
 * However, this is bad programming since C doesn't guarantee
 * the evaluation order of the getc() calls! As suggested by
 * Murphy's law, there are indeed compilers which produce the wrong
 * order of the getc() calls, e.g. the Metrowerks C compilers for BeOS
 * and Macintosh.
 * Since there are only few calls we don't care about the performance
 * penalty and use a simplistic C function.
 */

/* read two byte parameter, MSB first */
static unsigned int
get_2bytes(FILE *fp) {
	unsigned int	val;
	val = (unsigned int)(getc(fp) << 8);
	val += (unsigned int)(getc(fp));
	return val;
}

static int
next_marker(FILE *fp) {	/* look for next JPEG Marker  */
	int c, nbytes = 0;

	if (feof(fp))
		return M_ERROR;		    /* dummy marker		  */

	do {
		do {			    /* skip to FF		  */
			nbytes++;
			c = getc(fp);
		} while (c != 0xFF);
		do {			    /* skip repeated FFs	  */
			c = getc(fp);
		} while (c == 0xFF);
	} while (c == 0);		    /* repeat if FF/00		  */

	return c;
}

/* analyze JPEG marker */

static bool
AnalyzeJPEG() {
	int b, c, unit;
	unsigned long i, length = 0;
#define APP_MAX 255
	unsigned char appstring[APP_MAX];
	bool SOF_done = false;

	/* process JPEG markers */
	while (!SOF_done && (c = next_marker(image.fp)) != M_EOI) {
		switch (c) {
		case M_ERROR:
			put_msg("Error: unexpected end of JPEG file!");
			return false;

		/* The following are not officially supported in
		   PostScript level 2 */
		case M_SOF2:
		case M_SOF3:
		case M_SOF5:
		case M_SOF6:
		case M_SOF7:
		case M_SOF9:
		case M_SOF10:
		case M_SOF11:
		case M_SOF13:
		case M_SOF14:
		case M_SOF15:
			/* this below is supported in PostScript level 2 */
		case M_SOF0:
		case M_SOF1:
			length = get_2bytes(image.fp); /* read segment length */

			image.bits_per_component = getc(image.fp);
			image.height		  = (int) get_2bytes(image.fp);
			image.width		  = (int) get_2bytes(image.fp);
			image.components	  = getc(image.fp);

			SOF_done = true;
			break;

		case M_APP0:	/* check for JFIF marker with resolution */
			length = get_2bytes(image.fp);

			for (i = 0; i < length-2; i++) {
				/* get contents of marker */
				b = getc(image.fp);
				if (i < APP_MAX)
					/* store marker in appstring */
					appstring[i] = (unsigned char) b;
			}

			/*
			 * Check for JFIF application marker and read density
			 * values per JFIF spec version 1.02. We only check X
			 * resolution, assuming X and Y resolution are equal.
			 * Use values only if resolution not preset by user or
			 * to be ignored.
			 */

#define ASPECT_RATIO	0	/* JFIF unit byte: aspect ratio only */
#define DOTS_PER_INCH	1	/* JFIF unit byte: dots per inch     */
#define DOTS_PER_CM	2	/* JFIF unit byte: dots per cm	     */

			if (image.dpi == DPI_USE_FILE && length >= 14 &&
					!strncmp((char *)appstring, "JFIF", 4)){
				unit = appstring[7];	/* resolution unit */
				/* resolution value */
				image.dpi = (float)((appstring[8]<<8) +
						appstring[9]);

				if (image.dpi == 0.0) {
					image.dpi = DPI_USE_FILE;
					break;
				}

				switch (unit) {
				/* tell the caller we didn't find a
				   resolution value */
				case ASPECT_RATIO:
					image.dpi = DPI_USE_FILE;
					break;

				case DOTS_PER_INCH:
					break;

				case DOTS_PER_CM:
					image.dpi *= (float) 2.54;
					break;

				default:		/* unknown ==> ignore */
					image.dpi = DPI_IGNORE;
					break;
				}
			}
			break;

		case M_APP14:			/* check for Adobe marker */
			length = get_2bytes(image.fp);

			for (i = 0; i < length-2; i++) {
				/* get contents of marker */
				b = getc(image.fp);
				if (i < APP_MAX)
					/* store marker in appstring */
					appstring[i] = (unsigned char) b;
			}

			/*
			 * Check for Adobe application marker. It is known (per
			 * Adobe's TN5116) to contain the string "Adobe" at the
			 * start of the APP14 marker.
			 */
			if (length >= 12 && !strncmp((char *) appstring,
						"Adobe", 5))
				image.adobe = true;	/* set Adobe flag */

			break;

		case M_SOI:		/* ignore markers without parameters */
		case M_EOI:
		case M_TEM:
		case M_RST0:
		case M_RST1:
		case M_RST2:
		case M_RST3:
		case M_RST4:
		case M_RST5:
		case M_RST6:
		case M_RST7:
			break;

		default:		/* skip variable length markers */
			length = get_2bytes(image.fp);
			for (length -= 2; length > 0; length--)
				(void) getc(image.fp);
			break;
		}
	}

	/* do some sanity checks with the parameters */
	if (image.height <= 0 || image.width <= 0 || image.components <= 0) {
		put_msg("Error: DNL marker not supported in "
				"PostScript Level 2!");
		return false;
	}

	/* some broken JPEG files have this but they print anyway... */
	/* if (length != (unsigned int) (image.components * 3 + 8))
		fprintf(stderr,
		      "Warning: SOF marker has incorrect length - ignored!\n");
	 */

	if (image.components!=1 && image.components!=3 && image.components!=4) {
		put_msg("Error: unknown color space (%d components)!\n",
				image.components);
		return false;
	}

	return true;
}
