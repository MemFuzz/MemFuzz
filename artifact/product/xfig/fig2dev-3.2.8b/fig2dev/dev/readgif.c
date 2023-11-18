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
 * readgif.c: import gif into PostScript
 *
 */

/* Some of the following code is extracted from giftoppm.c,
   from the pbmplus package */

/* +-------------------------------------------------------------------+ */
/* | Copyright 1990, David Koblas.                                     | */
/* |   Permission to use, copy, modify, and distribute this software   | */
/* |   and its documentation for any purpose and without fee is hereby | */
/* |   granted, provided that the above copyright notice appear in all | */
/* |   copies and that both that copyright notice and this permission  | */
/* |   notice appear in supporting documentation.  This software is    | */
/* |   provided "as is" without express or implied warranty.           | */
/* +-------------------------------------------------------------------+ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "fig2dev.h"	/* includes "bool.h" */
#include "object.h"
#include "messages.h"
#include "readpics.h"
#include "xtmpfile.h"

extern	int	 _read_pcx(FILE *pcxfile, F_pic *pic);		/* readpcx.c */

#define LOCALCOLORMAP		0x80
#define	ReadOK(file,buffer,len)	(fread(buffer, len, 1, file) != 0)
#define BitSet(byte, bit)	(((byte) & (bit)) == (bit))

#define LM_to_uint(a,b)			(((b)<<8)|(a))

struct _GifScreen {
	unsigned int	Width;
	unsigned int	Height;
	unsigned int	BitPixel;
	unsigned char	ColorMap[3][MAXCOLORMAPSIZE];
	unsigned int	ColorResolution;
	unsigned int	Background;
	unsigned int	AspectRatio;
};

struct _Gif89 {
	int	transparent;
	int	delayTime;
	int	inputFlag;
	int	disposal;
} Gif89;

static bool	 ReadColorMap(FILE *, unsigned int,
				unsigned char cmap[3][MAXCOLORMAPSIZE]);
static bool	 DoGIFextension(FILE *, struct _Gif89 *, int);
static int	 GetDataBlock(FILE *, unsigned char *);

/* return codes:  1 : success
		  0 : invalid file
*/

int
read_gif(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	char		buf[BUFSIZ];
	char		pcxname_buf[128] = "f2dpcxXXXXXX";
	char		*pcxname = pcxname_buf;
	char		*cmd = buf;
	static char	*cmd_fmt = NULL;
	int		 i, stat;
	int		 useGlobalColormap;
	unsigned int	 bitPixel;
	unsigned char	 c;
	size_t		size;
	char		 version[4];
	unsigned char    transp[3]; /* RGB of transparent color (if any) */
	FILE		*pcx;
	FILE		*giftopcx;
	struct _Gif89	Gif89 = { -1, -1, -1, 0};
	struct _GifScreen	GifScreen;

	if (!rewind_stream(pic_stream))
		return 0;

	/* command string to convert gif to pcx */

	if (cmd_fmt == NULL) {
		if (!system("{ giftopnm -version && ppmtopcx -version; } "
								"2>/dev/null"))
			cmd_fmt = "giftopnm -quiet | ppmtopcx -quiet >'%s'";
		else if (!system("convert -version >/dev/null"))
			cmd_fmt = "convert - pcx:'%s'";
		else if (!system("gm -version >/dev/null"))
			cmd_fmt = "gm convert - pcx:'%s'";
		else {
			cmd_fmt = "";
			put_msg("Cannot read gif files.\n"
	"To read gif files, install either the netpbm, or the imagemagick,\n"
	"or the graphicsmagick package.");
			return 0;
		}
	}
	if (*cmd_fmt == '\0')
		return 0;

	*llx = *lly = 0;

	/* first read header to look for any transparent color extension */
	if (! ReadOK(pic_stream->fp, buf, 6)) {
		return 0;
	}

	if (strncmp((char*)buf, "GIF", 3) != 0) {
		return 0;
	}

	strncpy(version, (char*)(buf + 3), 3);
	version[3] = '\0';

	if ((strcmp(version, "87a") != 0) && (strcmp(version, "89a") != 0)) {
		put_msg("Unknown GIF version %s", version);
		return 0;
	}

	if (! ReadOK(pic_stream->fp, buf, 7)) {
		return 0;		/* failed to read screen descriptor */
	}

	GifScreen.Width           = LM_to_uint(buf[0],buf[1]);
	GifScreen.Height          = LM_to_uint(buf[2],buf[3]);
	GifScreen.BitPixel        = 2<<(buf[4]&0x07);
	GifScreen.ColorResolution = (((((int)buf[4])&0x70)>>3)+1);
	GifScreen.Background      = (unsigned int) buf[5];
	GifScreen.AspectRatio     = (unsigned int) buf[6];

	if (BitSet(buf[4], LOCALCOLORMAP)) {	/* Global Colormap */
		if (!ReadColorMap(pic_stream->fp, GifScreen.BitPixel,
								pic->cmap)) {
			return 0;	/* error reading global colormap */
		}
	}

	/* assume no transparent color for now */
	Gif89.transparent =  -1;

	for (;;) {
		if (! ReadOK(pic_stream->fp, &c, 1)) {
			return 0;	/* EOF / read error on image data */
		}

		if (c == ';') {		/* GIF terminator, finish up */
			break;		/* all done */
		}

		if (c == '!') {		/* Extension */
		    if (! ReadOK(pic_stream->fp, &c, 1))
			fprintf(stderr,
				"GIF read error on extension function code\n");
		    (void)DoGIFextension(pic_stream->fp, &Gif89, c);
		    continue;
		}

		if (c != ',') {		/* Not a valid start character */
			continue;
		}

		if (! ReadOK(pic_stream->fp, buf, 9)) {
			return 0;      /* couldn't read left/top/width/height */
		}

		useGlobalColormap = ! BitSet(buf[8], LOCALCOLORMAP);

		bitPixel = 1<<((buf[8]&0x07)+1);

		if (! useGlobalColormap) {
		    if (!ReadColorMap(pic_stream->fp, bitPixel, pic->cmap)) {
			fprintf(stderr, "error reading local GIF colormap\n");
			return 0;
		    }
		}
		break;			/* image starts here, header is done */
	}

	/* output PostScript comment */
	fprintf(tfp, "%% Originally from a GIF File: %s\n\n", pic->file);

	/* save transparent indicator */
	if (Gif89.transparent != -1) {
		pic->num_transp = 1;
		pic->transp_cols = pic->transp_col; /* abuse transp_col array */
		pic->transp_cols[0] = Gif89.transparent;
		transp[RED]   = pic->cmap[RED][pic->transp_cols[0]];
		transp[GREEN] = pic->cmap[GREEN][pic->transp_cols[0]];
		transp[BLUE]  = pic->cmap[BLUE][pic->transp_cols[0]];
	} else {
		pic->num_transp = NO_TRANSPARENCY;
	}

	/* create a temporary file */
	if ((pcx = xtmpfile(&pcxname, sizeof pcxname_buf)) == NULL) {
		if (pcxname != pcxname_buf)
			free(pcxname);
		return 0;
	}
#define REMOVE_PCXFILE			\
	do {				\
		fclose(pcx);		\
		unlink(pcxname);	\
		if (pcxname != pcxname_buf) \
			free(pcxname);	\
	} while (0)


	/* now call giftopnm and ppmtopcx */
	if ((size = strlen(cmd_fmt) + strlen(pcxname) > sizeof buf) &&
			(cmd = malloc(size - 1)) == NULL) {
		REMOVE_PCXFILE;
		return 0;
	}
	sprintf(cmd, cmd_fmt, pcxname);

	giftopcx = popen(cmd, "w");
	if (giftopcx == NULL) {
		err_msg("Cannot convert gif to pcx, %s", cmd);
		REMOVE_PCXFILE;
		if (cmd != buf)
			free(cmd);
		return 0;
	}
	if (cmd != buf)
		free(cmd);

	/* rewind gif stream */
	if (!rewind_stream(pic_stream)) {
		REMOVE_PCXFILE;
		return 0;
	}
	while ((size = fread(buf, 1, sizeof buf, pic_stream->fp)) != 0)
		fwrite(buf, size, 1, giftopcx);

	if (pclose(giftopcx)) {
		err_msg("Could not read gif file '%s'", pic_stream->name);
		REMOVE_PCXFILE;
		return 0;
	}

	rewind(pcx);
	/* now call _read_pcx to read the pcx file */
	stat = _read_pcx(pcx, pic);

	REMOVE_PCXFILE;

	/* now match original transparent colortable index with possibly new
	   colortable from ppmtopcx */
	if (pic->num_transp != NO_TRANSPARENCY) {
	    for (i=0; i<pic->numcols; i++) {
		if (pic->cmap[RED][i]   == transp[RED] &&
		    pic->cmap[GREEN][i] == transp[GREEN] &&
		    pic->cmap[BLUE][i]  == transp[BLUE]) {
			pic->transp_cols[0] = i;
			break;
		}
	    }
	    if (i == pic->numcols)	/* not found? */
		pic->num_transp = NO_TRANSPARENCY;
	}

	return stat;
}

static bool
ReadColorMap(FILE *fd, unsigned int number,
		unsigned char cmap[3][MAXCOLORMAPSIZE])
{
	unsigned int	i;
	unsigned char	rgb[3];

	for (i = 0; i < number; ++i) {
		if (! ReadOK(fd, rgb, sizeof(rgb))) {
			fprintf(stderr,"bad GIF colormap\n" );
			return false;
		}
		cmap[RED][i]   = rgb[RED];
		cmap[GREEN][i] = rgb[GREEN];
		cmap[BLUE][i]  = rgb[BLUE];
	}
	return true;
}

static bool
DoGIFextension(FILE *fd, struct _Gif89 *Gif89, int label)
{
	static unsigned char buf[256];
	char	    *str;

	switch (label) {
	case 0x01:		/* Plain Text Extension */
		str = "Plain Text Extension";
		break;
	case 0xff:		/* Application Extension */
		str = "Application Extension";
		break;
	case 0xfe:		/* Comment Extension */
		str = "Comment Extension";
		while (GetDataBlock(fd, buf) != 0) {
			; /* GIF comment */
		}
		return false;
	case 0xf9:		/* Graphic Control Extension */
		str = "Graphic Control Extension";
		(void) GetDataBlock(fd, (unsigned char*) buf);
		Gif89->disposal    = (buf[0] >> 2) & 0x7;
		Gif89->inputFlag   = (buf[0] >> 1) & 0x1;
		Gif89->delayTime   = LM_to_uint(buf[1],buf[2]);
		if ((buf[0] & 0x1) != 0)
			Gif89->transparent = buf[3];

		while (GetDataBlock(fd, buf) != 0)
			;
		return false;
	default:
		str = (char *) buf;
		sprintf(str, "UNKNOWN (0x%02x)", label);
		break;
	}

	while (GetDataBlock(fd, buf) != 0)
		;

	return false;
}

static int
GetDataBlock(FILE *fd, unsigned char *buf)
{
	unsigned char	count;

	/* error in getting DataBlock size */
	if (! ReadOK(fd,&count,1)) {
		return -1;
	}

	/* error in reading DataBlock */
	if ((count != 0) && (! ReadOK(fd, buf, count))) {
		return -1;
	}

	return count;
}
