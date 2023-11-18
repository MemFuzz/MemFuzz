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

/*
 * Some of the following code is extracted from giftopnm.c,
 * from the netpbm package
 */

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
#include "config.h"		/* restrict */
#endif

#include <X11/Intrinsic.h>	/* Boolean */
#include <X11/Xlib.h>		/* True, False */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>		/* mkstemp */
#include <string.h>		/* mkstemp */
#include <unistd.h>		/* close, unlink */

#include "resources.h"		/* PATH_MAX */
#include "object.h"
#include "f_picobj.h"
#include "f_readpcx.h"
#include "w_msgpanel.h"


static Boolean	ReadColorMap(FILE *fd, unsigned int number, struct Cmap *cmap);
static Boolean	DoGIFextension(FILE *fd, int label);
static int	GetDataBlock(FILE *fd, unsigned char *buf);

#define LOCALCOLORMAP		0x80
#define	ReadOK(file,buffer,len)	\
	    (fread((void *)buffer, (size_t)len, (size_t)1, (FILE *)file) != 0)
#define BitSet(byte, bit)	(((byte) & (bit)) == (bit))

#define LM_to_uint(a,b)		(((b)<<8)|(a))

struct {
	unsigned int	Width;
	unsigned int	Height;
	struct	 Cmap	ColorMap[MAX_COLORMAP_SIZE];
	unsigned int	BitPixel;
	unsigned int	ColorResolution;
	unsigned int	Background;
	unsigned int	AspectRatio;
} GifScreen;

struct {
	int	transparent;
	int	delayTime;
	int	inputFlag;
	int	disposal;
} Gif89 = { -1, -1, -1, 0 };

/* return codes:  PicSuccess (1) : success
		  FileInvalid (-2) : invalid file
*/



int
read_gif(F_pic *pic, struct xfig_stream *restrict pic_stream)
{
	char		buf[BUFSIZ];
	const char 	pcxname_fmt[] = "%s/xfig-pcx.XXXXXX";
	char		pcxname_buf[128];
	char		*pcxname = pcxname_buf;
	char		*cmd_fmt;
	char		*cmd = buf;
	FILE		*giftopcx;
	struct Cmap	localColorMap[MAX_COLORMAP_SIZE];
	int		i, stat, fd;
	int		useGlobalColormap;
	unsigned int	bitPixel, red, green, blue;
	unsigned char	c;
	char		version[4];
	size_t		size;
	struct xfig_stream	pcx;

	if (!rewind_stream(pic_stream))
		return FileInvalid;

	/* command string to convert gif to pcx */
	if (!system("{ giftopnm -version && ppmtopcx -version; } 2>/dev/null"))
		cmd_fmt = "giftopnm -quiet | ppmtopcx -quiet >'%s'";
	else if (!system("convert -version >/dev/null"))
		cmd_fmt = "convert - pcx:'%s'";
	else if (!system("gm -version >/dev/null"))
		cmd_fmt = "gm convert - pcx:'%s'";
	else {
		file_msg("Cannot read gif files.");
		file_msg("To read gif files, install either the netpbm, or the "
				"imagemagick, or the graphicsmagick package.");
		return FileInvalid;
	}

	/* first read header to look for any transparent color extension */
	if (!ReadOK(pic_stream->fp, buf, 6)) {
		return FileInvalid;
	}

	if (strncmp((char*)buf, "GIF", 3) != 0) {
		return FileInvalid;
	}

	strncpy(version, (char*)(buf + 3), 3);
	version[3] = '\0';

	if ((strcmp(version, "87a") != 0) && (strcmp(version, "89a") != 0)) {
		file_msg("Unknown GIF version %s", version);
		return FileInvalid;
	}

	if (!ReadOK(pic_stream->fp, buf, 7)) {
		return FileInvalid;	/* failed to read screen descriptor */
	}

	GifScreen.Width           = LM_to_uint(buf[0],buf[1]);
	GifScreen.Height          = LM_to_uint(buf[2],buf[3]);
	GifScreen.BitPixel        = 2<<(buf[4]&0x07);
	GifScreen.ColorResolution = (((((int)buf[4])&0x70)>>3)+1);
	GifScreen.Background      = (unsigned int) buf[5];
	GifScreen.AspectRatio     = (unsigned int) buf[6];

	if (BitSet(buf[4], LOCALCOLORMAP)) {	/* Global Colormap */
		if (!ReadColorMap(pic_stream->fp, GifScreen.BitPixel,
					GifScreen.ColorMap)) {
			return FileInvalid;  /* error reading global colormap */
		}
	}

	if (GifScreen.AspectRatio != 0 && GifScreen.AspectRatio != 49) {
		if (appres.DEBUG)
			fprintf(stderr, "warning - non-square pixels\n");
	}

	/* assume no transparent color for now */
	Gif89.transparent = TRANSP_NONE;

	/* read the full header to get any transparency information */
	for (;;) {
		if (!ReadOK(pic_stream->fp, &c, 1)) {
			return FileInvalid;	/* EOF / read error on image data */
		}

		if (c == ';') {			/* GIF terminator, finish up */
			return PicSuccess;	/* all done */
		}

		if (c == '!') {			/* Extension */
			if (!ReadOK(pic_stream->fp, &c, 1))
				file_msg("GIF read error on extension function code");
			(void)DoGIFextension(pic_stream->fp, c);
			continue;
		}

		if (c != ',') {			/* Not a valid start character*/
			continue;
		}

		if (!ReadOK(pic_stream->fp, buf, 9)) {
			/* couldn't read left/top/width/height */
			return FileInvalid;
		}

		useGlobalColormap = !BitSet(buf[8], LOCALCOLORMAP);

		bitPixel = 1<<((buf[8]&0x07)+1);

		if (!useGlobalColormap) {
			if (!ReadColorMap(pic_stream->fp, bitPixel,
						localColorMap)) {
				file_msg("error reading local GIF colormap" );
				return PicSuccess;
			}
		}
		break;			/* image starts here, header is done */
	}

	/* save transparent indicator */
	pic->pic_cache->transp = Gif89.transparent;

	/* now call giftopnm and ppmtopcx */

	/* make name for temp output file */
	size = sizeof pcxname_fmt + strlen(TMPDIR) - 2;
	if (size > sizeof pcxname_buf && (pcxname = malloc(size)) == NULL) {
		file_msg("Out of memory.");
		return FileInvalid;
	}
	if (sprintf(pcxname, pcxname_fmt, TMPDIR) < 0) {
		i = errno;
		file_msg("Unable to write temporary file path to string");
		file_msg("Error: %s", strerror(i));
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}
	if ((fd = mkstemp(pcxname)) == -1) {
		file_msg("Cannot create temporary file\n");
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}
	close(fd);

	/* make command to convert gif to pcx */
	size += strlen(cmd_fmt) - 2;	/* from above, size == sizeof pcxname */
	if (size > sizeof buf && (cmd = malloc(size)) == NULL) {
		file_msg("Out of memory.");
		unlink(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}
	if (sprintf(cmd, cmd_fmt, pcxname) < 0) {
		i = errno;
		file_msg("Cannot write command to convert gif to pcx.");
		file_msg("Error: %s", strerror(i));
		unlink(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}

	giftopcx = popen(cmd, "w");
	if (giftopcx == NULL) {
		i = errno;
		file_msg("Cannot open pipe to convert gif to pcx\n");
		file_msg("Command: %s", cmd);
		file_msg("Error: %s", strerror(i));
		if (cmd != buf)
			free(cmd);
		unlink(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}

	/* write the temporary pcx file */
	rewind_stream(pic_stream);
	while ((size = fread(buf, 1, sizeof buf, pic_stream->fp)) != 0)
		fwrite(buf, size, 1, giftopcx);

	if (pclose(giftopcx)) {
		i = errno; 
		file_msg("Cannot convert gif to pcx\n");
		file_msg("Command: %s", cmd);
		file_msg("Error: %s", strerror(i));
		if (cmd != buf)
			free(cmd);
		unlink(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}

	if (cmd != buf)
		free(cmd);

	/*
	 * Construct a rudimentary struct xfig_stream that can be passed to
	 * read_pcx(). Tell read_pcx() that the FILE pointer is positioned at
	 * the start (*name == '\0') and that it is a regular file
	 * (*uncompress == '\0').
	 * ATTENTION, requires knowledge of fields of struct xfig_stream.
	 */
	pcx.name_buf[0] = '\0';
	pcx.name = pcx.name_buf;
	pcx.uncompress = pcx.name_buf;

	if ((pcx.fp = fopen(pcxname, "rb")) == NULL) {
		file_msg("Cannot open temporary output file\n");
		perror("Error");
		unlink(pcxname);
		if (pcxname != pcxname_buf)
			free(pcxname);
		return FileInvalid;
	}

	/* now call read_pcx to read the pcx file */
	stat = read_pcx(pic, &pcx);

	/* remove temp file */
	fclose(pcx.fp);
	unlink(pcxname);
	if (pcxname != pcxname_buf)
		free(pcxname);

	pic->pic_cache->subtype = T_PIC_GIF;
	/* now match original transparent colortable index with possibly new
	   colortable from ppmtopcx */
	if (pic->pic_cache->transp != TRANSP_NONE) {
	    if (useGlobalColormap) {
		red = GifScreen.ColorMap[pic->pic_cache->transp].red;
		green = GifScreen.ColorMap[pic->pic_cache->transp].green;
		blue = GifScreen.ColorMap[pic->pic_cache->transp].blue;
	    } else {
		red = localColorMap[pic->pic_cache->transp].red;
		green = localColorMap[pic->pic_cache->transp].green;
		blue = localColorMap[pic->pic_cache->transp].blue;
	    }
	    for (i = 0; i < pic->pic_cache->numcols; ++i) {
		if (pic->pic_cache->cmap[i].red == red &&
		    pic->pic_cache->cmap[i].green == green &&
		    pic->pic_cache->cmap[i].blue == blue)
			break;
	    }
	    if (i < pic->pic_cache->numcols)
		pic->pic_cache->transp = i;
	}

	return stat;
}

static Boolean
ReadColorMap(FILE *fd, unsigned int number, struct Cmap *cmap)
{
	unsigned int	i;
	unsigned char	rgb[3];

	for (i = 0; i < number; ++i) {
	    if (! ReadOK(fd, rgb, sizeof(rgb))) {
		file_msg("bad GIF colormap" );
		return False;
	    }
	    cmap[i].red   = rgb[0];
	    cmap[i].green = rgb[1];
	    cmap[i].blue  = rgb[2];
	}
	return True;
}

static Boolean
DoGIFextension(FILE *fd, int label)
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
		return False;
	case 0xf9:		/* Graphic Control Extension */
		str = "Graphic Control Extension";
		(void) GetDataBlock(fd, (unsigned char*) buf);
		Gif89.disposal    = (buf[0] >> 2) & 0x7;
		Gif89.inputFlag   = (buf[0] >> 1) & 0x1;
		Gif89.delayTime   = LM_to_uint(buf[1],buf[2]);
		if ((buf[0] & 0x1) != 0)
			Gif89.transparent = buf[3];

		while (GetDataBlock(fd, buf) != 0)
			;
		return False;
	default:
		str = (char *) buf;
		sprintf(str, "UNKNOWN (0x%02x)", label);
		break;
	}

	if (appres.DEBUG)
		fprintf(stderr,"got a '%s' extension\n", str );

	while (GetDataBlock(fd, buf) != 0)
		;

	return False;
}

int	ZeroDataBlock = False;

static int
GetDataBlock(FILE *fd, unsigned char *buf)
{
	unsigned char	count;

	/* error in getting DataBlock size */
	if (! ReadOK(fd,&count,1)) {
		return -1;
	}

	ZeroDataBlock = count == 0;

	/* error in reading DataBlock */
	if ((count != 0) && (! ReadOK(fd, buf, count))) {
		return -1;
	}

	return count;
}
