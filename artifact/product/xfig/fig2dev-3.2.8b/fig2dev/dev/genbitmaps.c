/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2021 by Thomas Loimer
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
 * genbitmaps.c: convert fig to various bitmaps
 *
 * Author: Brian V. Smith
 *	Handles AutoCad Slide, GIF, JPEG, TIFF, PCX, PNG, XBM and XPM.
 *	Uses genps functions to generate PostScript output then calls
 *	ghostscript to convert it to the output language if ghostscript
 *	has a driver for that language, or to ppm if otherwise. If the
 *	latter, either ppmtoxx, convert or gm convert is then called to
 *	make the final xxx file.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "bool.h"
#include "fig2dev.h"	/* includes bool.h and object.h */
#include "colors.h"	/* lookup_X_color(), rgb2luminance() */
#include "genps.h"
#include "messages.h"
#include "xtmpfile.h"

/*
 * The command to convert from eps to various image formats is obtained by first
 * producing an appropriate format string. The format string expects the
 * arguments width, height, gsdev, out, errfname. Here, antialias is
 * ANTIALIAS printed to a string, and out points either to to, or to the empty
 * string. The ghostscript output might be the final image, or the output is
 * piped to various conversion commands.
 */
#ifdef GSEXE
#define GS_CMD		GSEXE " -q -dSAFER -r80 -g%dx%d -sDEVICE=%s"
#else
#define GS_CMD
#endif
/* will be printed to the string antialias */
#define ANTIALIAS	" -dTextAlphaBits=%d -dGraphicsAlphaBits=%d"
#define GS_TO		" -o '%s' -"
#define GS_OUT		" -o %s- -"	/* out must be the empty string */
#define GS_PIPE		" -o - -"
/* the longest conversion string */
#define CONVERT_MAX_LEN	81	/* make sure, the longest conversion pipe is
				   shorter than one linelength */
#define NET_TO		" >'%s'"
#define NET_OUT		"%s"		/* out must be the empty string */
#define ERR		" 2>%s"

/* file format might be:
 * |--------- GSCMD ----------|          | GS_TO  | ERR |
 * GSEXE -q -g%dx%d -sDEVICE=%s antialias -o '%s' - 2>%s
 *
 * |--------- GSCMD ----------|          | GS_OUT | ERR |
 * GSEXE -q -g%dx%d -sDEVICE=%s antialias -o %s- - 2>%s
 *
 * { |--------- GSCMD ----------|         |GS_PIPE| CONVERT|; }|NET_TO|ERR
 * { GSEXE -q -g%dx%d -sDEVICE=%s antialias -o - - | CONVERT; } >'%s' 2>%s
 *
 * { |--------- GSCMD ----------|         |GS_PIPE| CONVERT|; }|END_OUT|ERR
 * { GSEXE -q -g%dx%d -sDEVICE=%s antialias -o - - | CONVERT; }%s 2>%s
 */

static char	com_buf[sizeof GS_CMD ANTIALIAS GS_PIPE NET_TO ERR +
							CONVERT_MAX_LEN + 80];
static char	*com = com_buf;
#ifdef GSEXE
static FILE	*errfile;
#endif
static char	errfname_buf[128] = "f2derrorXXXXXX";
static char	*errfname = errfname_buf;
static int	jpeg_quality = 75;
static int	border_margin = 0;
static int	smooth = 0;

void
genbitmaps_option(char opt, char *optarg)
{
	switch (opt) {

	case 'b':			/* border margin around bitmap */
		sscanf(optarg, "%d", &border_margin);
		break;

	case 'F':
		gen_ps_eps_option(opt, optarg);
		break;

	case 'g':		/* background color (handled in ps driver) */
		if (lookup_X_color(optarg, &background) >= 0) {
			bgspec = true;
		} else {
			fprintf(stderr, "Can't parse color '%s', ignoring "
					"background option\n", optarg);
		}
		break;

	case 'N':			/* convert colors to grayscale */
		grayonly = 1;
		break;

	case 'q':			/* jpeg image quality */
		if (strcmp(lang, "jpeg") != 0)
			fputs("-q option only allowed for jpeg quality; "
				"ignored\n", stderr);
		sscanf(optarg, "%d", &jpeg_quality);
		if (jpeg_quality < 1)
			jpeg_quality = 1;
		else if (jpeg_quality > 100)
			jpeg_quality = 100;
		break;

	case 't':			/* GIF transparent color */
		if (strcmp(lang, "gif") != 0)
			fputs("-t option only allowed for GIF transparent "
				"color; ignored\n", stderr);
		if (strlen(optarg) >= sizeof gif_transparent) {
			fprintf(stderr,
				"fig2dev: invalid color specification %s\n",
				gif_transparent);
			fputs("         specify gif transparent color in "
					"the form #rrggbb\n", stderr);
			exit(EXIT_FAILURE);
		}
		(void)strcpy(gif_transparent, optarg);
		transspec = true;
		break;

	case 'S':			/* smoothing factor */
		sscanf(optarg, "%d", &smooth);
		if (smooth != 0 && smooth != 1 && smooth != 2 && smooth != 4) {
			fprintf(stderr, "fig2dev: bad value for -S option: %s, "
					"should be 1, 2 or 4\n", optarg);
			exit(1);
		}
		break;

	case 'G':
	case 'L':
		break;

	default:
		put_msg(Err_badarg, opt, lang);
		break;
	}
}

#ifdef GSEXE
/*
 * Check functioning of netpbm programs with a 2x2 test image consisting of a
 * white, a red, a blue, and a black pixel.
 * Return value: true success, false failure.
 */
static bool
has_netpbm(const char *cmd)
{
	FILE	      *f;
	unsigned char img[] = "P6 2 2 255 \xff\xff\xff\xff\0\0\0\0\xff\0\0\0\n";

	f = popen(cmd, "w");
	if (f == NULL)
		return false;

	/* the terminating '\0' does not need to be written */
	if (fwrite(img, sizeof img - 1, 1, f) != 1)
		return false;

	if (pclose(f) == 0)
		return true;
	else
		return false;
}

static bool
has_ImageMagick(void)
{
	if (system("convert -version >/dev/null") == 0)
		return true;
	else
		return false;
}

static bool
has_GraphicsMagick(void)
{
	if (system("gm version >/dev/null") == 0)
		return true;
	else
		return false;
}

static void
bitmaps_broken_pipe(int sig)
{
	(void)	sig;

	fputs("fig2dev: broken pipe when trying to create image\n", stderr);
	fprintf(stderr, "command was: %s\n", com);
	exit(EXIT_FAILURE);
}
#endif /* GSEXE */

void
genbitmaps_start(F_compound *objects)
{
#ifdef GSEXE /* bracket the entire function */
	char	*gsdev;
	char	fmt[sizeof GS_CMD ANTIALIAS GS_PIPE NET_TO ERR +
							CONVERT_MAX_LEN + 6];
	char	antialias[sizeof ANTIALIAS];
	char	*gscmd = GS_CMD;
	char	*gspipe = GS_PIPE;
	char	*err;
	char	*out;
	char	*gsend;
	char	*netend;
	char	*gimend;	/* GrapicsMagick, ImageMagick End */
	int	n;
	int	width;
	int	height;

	n = (int)(border_margin * THICK_SCALE + 0.9);
	llx -= n;	lly -= n;
	urx += n;	ury += n;
	width = (int)(mag * (urx - llx) / THICK_SCALE + 0.9),
	height = (int)(mag * (ury - lly) / THICK_SCALE + 0.9);


	/* set the format strings of the final output, depending on
	   whether it goes to a file or to stdout */
	if (tfp != stdout) {
		if (strchr(to, '\'')) {
			fprintf(stderr, "Cannot write to a file containing an "
					"apostrophe (') in its name: %s\n", to);
			exit(EXIT_FAILURE);
		}
		fclose(tfp);	/* close the output file that main() opened */
		out = to;
		gsend = GS_TO;
		netend = NET_TO;
		gimend = "'%s'";
	} else {
		out = "";
		gsend = GS_OUT;
		netend = NET_OUT;
		gimend = "%s-";
	}

	if (smooth)
		sprintf(antialias, ANTIALIAS, smooth, smooth);
	else
		*antialias = '\0';

	/* create a temporary file to catch standard error */
	if ((errfile = xtmpfile(&errfname, sizeof errfname_buf)) == NULL) {
		fprintf(stderr, "Can't create error log file %s\n",
				errfname);
		if (errfname != errfname_buf)
			free(errfname);
		err = "%s";	/* display errors on the terminal */
		*errfname = '\0';
	} else {
		fclose(errfile);
		err = ERR;
	}
#define BITMAP_EXIT_FAILURE	if (*errfname) remove(errfname);	\
				if (errfname != errfname_buf) free(errfname); \
				exit(EXIT_FAILURE)

	/* create the format string to produce the command string */
	/*
	 * The netpbm programs seem to count the colors, and produce the
	 * smallest files. Therefore, prefer netpbm programs, then either
	 * GraphicsMagick or Imagemagick, last ghostscript.
	 */
	if (!strcmp(lang, "ppm")) {
		gsdev = "ppmraw";
		sprintf(fmt, "%s%s%s%s", gscmd, antialias, gsend, err);
	} else if (!strcmp(lang, "jpeg")) {
		gsdev = "jpeg";
		sprintf(fmt, "%s -dJPEGQ=%d%s%s%s", gscmd, jpeg_quality,
				antialias, gsend, err);
	} else if (!strcmp(lang, "gif")) {
		/*
		 * netpbm programs are rather verbose, hence they receive the
		 * -quiet option. convert or gm convert are less verbose.
		 * With -quiet they would suppress informational warning
		 * messages. We keep those, they might be interesting.
		 */
		gsdev = "ppmraw";
		/* ppmquant and ppmtogif both report the number of colors
		   - keep them -quiet */
		if (has_netpbm("{ ppmquant -quiet 256 | ppmtogif -quiet; } "
					">/dev/null 2>&1")){
			if (*gif_transparent)
				sprintf(fmt, "{ %s%s%s | ppmquant -quiet 256 | "
					   "ppmtogif -quiet -transparent==\\%s;"
					   " }%s%s", gscmd, antialias, gspipe,
					gif_transparent, netend, err);
			else
				sprintf(fmt, "{ %s%s%s | ppmquant -quiet 256 | "
						"ppmtogif -quiet; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		} else if (has_ImageMagick()) {
			if (*gif_transparent)
				sprintf(fmt, "{ %s%s%s | convert - -transparent"
						" \\%s gif:%s; }%s", gscmd,
						antialias, gspipe,
						gif_transparent, gimend, err);
			else
				sprintf(fmt, "{ %s%s%s | convert - gif:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else if (has_GraphicsMagick()) {
			if (*gif_transparent)
				sprintf(fmt, "{ %s%s%s | gm convert - "
						"-transparent \\%s gif:%s; }%s",
						gscmd, antialias, gspipe,
						gif_transparent, gimend, err);
			else
				sprintf(fmt,
					"{ %s%s%s | gm convert - gif:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else {
			fputs("fig2dev: Cannot write gif image.\n    Please "
				"install one of the netpbm, GraphicsMagick or "
				"ImageMagick packages.\n", stderr);
			BITMAP_EXIT_FAILURE;
		}
	} else if (!strcmp(lang, "xbm")) {
		gsdev = "ppmraw";
		if (has_netpbm("{ ppmtopgm | pgmtopbm | pbmtoxbm; } "
					">/dev/null 2>&1"))
			sprintf(fmt,
			     "{ %s%s%s | ppmtopgm | pgmtopbm | pbmtoxbm; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		else if (has_GraphicsMagick())
			sprintf(fmt, "{ %s%s%s | gm convert - xbm:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		else if (has_ImageMagick())
			sprintf(fmt, "{ %s%s%s | convert - xbm:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		else {
			fputs("fig2dev: Cannot write xbm image.\n    Please "
				"install one of the netpbm, GraphicsMagick or "
				"ImageMagick packages.\n", stderr);
			BITMAP_EXIT_FAILURE;
		}
	} else if (!strcmp(lang, "xpm")) {
		gsdev = "ppmraw";
		/* ppmtoxpm reports the number of colors, keep -quiet */
		if (has_netpbm("ppmtoxpm -quiet >/dev/null 2>&1"))
			sprintf(fmt,
			     "{ %s%s%s | ppmtoxpm -quiet; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		else if (has_GraphicsMagick())
			sprintf(fmt, "{ %s%s%s | gm convert - xpm:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		else if (has_ImageMagick())
			sprintf(fmt, "{ %s%s%s | convert - xpm:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		else {
			fputs("fig2dev: Cannot write xpm image.\n    Please "
				"install one of the netpbm, GraphicsMagick or "
				"ImageMagick packages.\n", stderr);
			BITMAP_EXIT_FAILURE;
		}
	} else if (!strcmp(lang, "sld")) {
		if (has_netpbm("ppmtoacad -quiet >/dev/null 2>&1")) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | ppmtoacad -quiet; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		} else {
			fputs("fig2dev: Need the ppmtoacad program to be able "
					"to write sld output file.\n", stderr);
			fputs("         Please install the netpbm package.\n",
					stderr);
			BITMAP_EXIT_FAILURE;
		}
	} else if (!strcmp(lang, "pcx")) {
		/* ppmtopcx reports the number of colors */
		if (has_netpbm("ppmtopcx -quiet >/dev/null 2>&1")) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | ppmtopcx -quiet; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		} else if (has_ImageMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | convert - pcx:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else if (has_GraphicsMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | gm convert - pcx:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else {
			gsdev = "pcx24b";
			sprintf(fmt, "%s%s%s%s", gscmd, antialias, gsend, err);
		}
	} else if (!strcmp(lang, "png")) {
		if (has_netpbm("pnmtopng >/dev/null 2>&1")) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | pnmtopng; }%s%s",
					gscmd, antialias, gspipe, netend, err);
		} else if (has_ImageMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | convert - png:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else if (has_GraphicsMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | gm convert - png:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else {
			gsdev = "png16m";
			sprintf(fmt, "%s%s%s%s", gscmd, antialias, gsend, err);
		}
	} else if (!strcmp(lang, "tiff")) {
#define	NEW_PNMTOTIFF	"pnmtotiff -quiet -flate -output %s >/dev/null 2>&1"
		char	netcmd[strlen(errfname) + sizeof NEW_PNMTOTIFF];
		/* In netpbm 10.67 and later, pnmtotiff has the "-output"
		   option and accepts a pipe. */
		if (*errfname && sprintf(netcmd, NEW_PNMTOTIFF, errfname) &&
				has_netpbm(netcmd)) {
			gsdev = "ppmraw";
			if (to)
				sprintf(fmt, "{ %s%s%s | pnmtotiff -quiet "
						"-flate -output '%%s'; }%s",
						gscmd, antialias, gspipe, err);
			else
				sprintf(fmt, "{ %s%s%s | pnmtotiff -flate "
						"-quiet; }%%s%s",
						gscmd, antialias, gspipe, err);
		/* netpbm before 10.67 cannot write to a pipe */
		} else if (to && sprintf(netcmd, "pnmtotiff -quiet -flate >%s "
						"2>/dev/null", errfname) &&
				has_netpbm(netcmd)) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | pnmtotiff -quiet -flate %s; }%s",
					gscmd, antialias, gspipe, netend, err);
		} else if (has_ImageMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | "
					"convert - -compress Zip tiff:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else if (has_GraphicsMagick()) {
			gsdev = "ppmraw";
			sprintf(fmt, "{ %s%s%s | gm convert - -compress Zip "
					"tiff:%s; }%s",
					gscmd, antialias, gspipe, gimend, err);
		} else {
			if (!to) {
				fputs("Cannot write tiff output to a pipe. "
					"Please specify an output file.\n",
					stderr);
				BITMAP_EXIT_FAILURE;
			}
			gsdev = "tiff24nc";
			sprintf(fmt, "%s -sCompression=lzw%s%s%s",
					gscmd, antialias, gsend, err);
		}
	} else {
		fprintf(stderr, "fig2dev: unsupported image format: %s\n",
				lang);
			BITMAP_EXIT_FAILURE;
	}

	/* write the command */
	n = snprintf(com, sizeof com_buf, fmt,
			width, height, gsdev, out, errfname);
	if (n >= (int)(sizeof com_buf)) {
		if ((com = malloc((size_t)(n + 1))) == NULL) {
			put_msg(Err_mem);
			BITMAP_EXIT_FAILURE;
		}
		n = sprintf(com, fmt, width, height, gsdev, out, errfname);
	}
	if (n < 0) {
		err_msg("Cannot write command for conversion to bitmap");
		BITMAP_EXIT_FAILURE;
	}

	(void) signal(SIGPIPE, bitmaps_broken_pipe);
	if ((tfp = popen(com, "w")) == NULL) {
		fprintf(stderr, "fig2dev: Cannot open pipe to ghostscript\n");
		fprintf(stderr, "command was: %s\n", com);
		if (com != com_buf)
			free(com);
		BITMAP_EXIT_FAILURE;
	}

	/* generate eps and not ps */
	epsflag = true;
	genps_start(objects);
#else
	fputs("Ghostscript command not available. Cannot create bitmaps.\n",
		stderr);
	exit(EXIT_FAILURE);
#endif	/* #ifdef GSEXE */
}

int
genbitmaps_end(void)
{
	int	status;

	/* wrap up the postscript output */
	if (genps_end() != 0) {
		/* but genps_end() does not return anything else than 0! */
		pclose(tfp);
		if (com != com_buf)
			free(com);
		if (*errfname) {
			remove(errfname);
			if (errfname != errfname_buf)
				free(errfname);
		}
		return -1;
	}

	status = pclose(tfp);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = -1;
	tfp = NULL;	/* Otherwise main() tries to close tfp again */
	(void) signal(SIGPIPE, SIG_DFL);

	if (status != 0) {
		FILE	*f;

		fputs("Error when creating bitmap output\n", stderr);
		fprintf(stderr, "command was: %s\n", com);

		if (*errfname && (f = fopen(errfname, "rb"))) {
			char	buf[256];
			size_t	buf_len = sizeof buf;
			size_t	chars;

			fputs("Messages resulting:\n", stderr);
			while ((chars = fread(buf, 1, buf_len, f)) == buf_len &&
					buf_len == fwrite(buf, 1, buf_len,
									stderr))
				;
						/* stderr might be diverted */
			if (chars > 0 && !ferror(stderr))
				fwrite(buf, (size_t)1, chars, stderr);

			fclose(f);
		}
	}

	if (com != com_buf)
		free(com);
	if (*errfname)
		remove(errfname);
	if (errfname != errfname_buf)
		free(errfname);

	return status;
}

struct driver dev_bitmaps = {
	genbitmaps_option,
	genbitmaps_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genps_text,
	genbitmaps_end,
	INCLUDE_TEXT
};
