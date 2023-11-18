/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2021 by Thomas Loimer
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
 * Call ghostscript to get the /MediaBox, and convert eps/pdf to bitmaps.
 * Autor: Thomas Loimer, 2020.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <inttypes.h>		/* includes stdint.h */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/X.h>		/* TrueColor */

#ifdef HAVE_GSLIB
#include <ghostscript/gdevdsp.h>
#include <ghostscript/gserrors.h>
#include <ghostscript/iapi.h>
#endif

#include "object.h"
#include "resources.h"
#include "f_util.h"		/* map_to_pattern(), map_to_mono() */
#include "w_msgpanel.h"		/* file_msg() */

/*
 * Exported functions: gs_mediabox(), gs_bitmap().
 * These are currently only used in f_readeps.c, hence
 * an extra header file is not provided.
 */

#define BITMAP_PPI	160	/* the resolution for rendering bitmaps */
#define GS_ERROR	(-2)

/*
 * Link into the ghostscript library.
 * If invoked via the library, ghostscript calls three callback functions when
 * wishing to read from stdin or write to stdout or stderr, respectively.
 * However, if a device is given, ghostscript writes directly to stdout. This
 * was found rather late, therefore some functions below are more modular than
 * necessary.
 * Here, set up calls to ghostscript and callback functions to read a pdf
 * file, scanning the output for the /MediaBox specification.
 *
 * If linking into the library by dlopen() fails, call the ghostscript
 * executable via popen("gs..", "r").
 */

#ifdef HAVE_GSLIB
/*
 * callback data struct
 * A pointer to this struct can be passed to ghostscript, which
 * is then passed to the callback functions.
 */
struct _callback_data {
	int	*bb;		/* for stdout_mediabox() callback function */
	char	*errbuf;	/* fixed buffer */
	int	errsize;
};

/* callback functions  */
static int
stdin_void(void *caller_handle, char *buf, int len)
{
	(void)caller_handle;
	(void)buf;

	return len;
}

static int
stderr_buf(void *caller_handle, const char *str, int len)
{
	struct _callback_data	*data = (struct _callback_data *)caller_handle;
	static int		pos = 0;

	/* buffer full, comparison for == should be sufficient */
	if (pos >= data->errsize - 1)
		return len;

	if (pos + len >= data->errsize)	/* leave space for a terminating '\0' */
		len = data->errsize - pos - 1;
	memcpy(data->errbuf + pos, str, (size_t)len);
	pos += len;
	data->errbuf[pos] = '\0';

	return len;
}

static int
stdout_mediabox(void *caller_handle, const char *str, int len)
{
	struct _callback_data	*data = (struct _callback_data *)caller_handle;
	int	err;
	double	fbb[4];

	/* This rests on the assumption that ghostscript writes the required
	   information all at once to str. Should use a buffer, instead. */

	/* gs always uses full stops as decimal character. The locale is already
	   set to C in read_pdf() */
	err = sscanf(str, "[%lf %lf %lf %lf]", fbb, fbb+1, fbb+2, fbb+3);
	if (err == 4) {
		data->bb[0] = (int)floor(fbb[0]);
		data->bb[1] = (int)floor(fbb[1]);
		data->bb[2] = (int)ceil(fbb[2]);
		data->bb[3] = (int)ceil(fbb[3]);
	} else {
		/* Either the pdf is corrupt, which yields a matching failure,
		 * or a read error occured or EOF is reached.
		 * Ghostscript returns with zero from a corrupt pdf, and writes
		 * error information to stdout.
		 * Use the bounding box to report a, most likely, corrupt pdf.
		 */
		data->bb[0] = data->bb[1] = data->bb[2] = 0;
		data->bb[3] = GS_ERROR;
	}

	return len;
}


/*
 * Link into the ghostscript library with argcnew and argvnew[] for gs >= 9.50,
 * argcold and argcold[] for gs < 9.50.
 * Return 0 on success, -1 if the library could not be called, -2 (GS_ERROR)
 * on a ghostscript error.
 */
static int
gslib(struct _callback_data *data, int (*gs_stdin)(void *, char*, int),
			int (*gs_stdout)(void *, const char*, int),
			int (*gs_stderr)(void *, const char*, int),
			int argcnew, int argcold,
			char *argvnew[], char *argvold[])
{
	int		i;
	int		code;
	const int	call_gsexe = -1;
	int		argc;
	char		**argv;
	struct gsapi_revision_s	rev;
	void		*minst = NULL;	/* must be initialized to NULL */


	/* get gs version */
	if (gsapi_revision(&rev, (int)(sizeof rev)))
		return call_gsexe;

	if (rev.revision >= 950) {
		argc = argcnew;
		argv = (char **)argvnew;
	} else {
		argc = argcold;
		argv = (char **)argvold;
	}
	if (appres.DEBUG) {
		fprintf(stderr, "Using ghostscript library, revision %ld\n",
				rev.revision);
		fputs("Arguments:", stderr);
		for (i = 0; i < argc; ++i)
			fprintf(stderr, " %s", argv[i]);
		fputc('\n', stderr);
	}

	code = gsapi_new_instance(&minst, (void *)data);
	if (code < 0) {
		return call_gsexe;
	}
	/* All gsapi_*() functions below return an int, but some
	   probably do not return an useful error code. */
	gsapi_set_stdio(minst, gs_stdin, gs_stdout, gs_stderr);
	code = gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
	if (code == 0)
		code = gsapi_init_with_args(minst, argc, argv);
	if (code == 0 || code == gs_error_Quit || code < 0 ||
			code <= gs_error_Fatal)
		code = gsapi_exit(minst);
	gsapi_delete_instance(minst);

	if (code == 0 || code == gs_error_Quit) {
		return 0;
	}

	/*
	 * Unfortunately, ghostscript does not report corrupt pdf files, but
	 * still returns zero.  Corrupt ps/eps input seems to be reported.
	 */
	file_msg("Error in ghostscript library, %s.\nOptions:", argv[0]);
	for (i = 1; i < argc; ++i)
		file_msg("  %s", argv[i]);
	if (data->errbuf[0] != '\0')
		file_msg("Ghostscript error message:\n%s", data->errbuf);
	return GS_ERROR;
}
#endif /* HAVE_GSLIB */

/*
 * Call ghostscript.
 * Return an open file stream for reading,
 *   *out = popen({exenew, exeold}, "r");
 * The user must call pclose(out) after calling gsexe(&out,...).
 * Use exenew for gs > 9.49, exeold otherwise.
 * Return 0 for success, -1 on failure to call ghostscript.
 */
static int
gsexe(FILE **out, bool *isnew, char *exenew, char *exeold)
{
#define	old_version	1
#define	new_version	2
#define no_version	0
	static int	version = no_version;
	const int	failure = -1;
	char		*exe;
	FILE		*fp;


	if (version == no_version) {
		int		n;
		int		stat;
		size_t		len;
		double		rev;
		char		cmd_buf[128];
		char		*cmd = cmd_buf;
		const char	version_arg[] = " --version";

		if (appres.DEBUG)
			fprintf(stderr,
				"Trying to call ghostscript executable %s...\n",
				appres.ghostscript);

		/* get the ghostscript version */
		/* allocate the command buffer, if necessary */
		len = strlen(appres.ghostscript) + sizeof version_arg;
		if (len > sizeof cmd_buf) {
			if ((cmd = malloc(len)) == NULL)
				return failure;
		}

		/* write the command string */
		sprintf(cmd, "%s%s", appres.ghostscript, version_arg);
		fp = popen(cmd, "r");
		if (cmd != cmd_buf)
			free(cmd);
		if (fp == NULL)
			return failure;

		/* scan for the ghostscript version */
		/* Currently, gsexe() is only called from gsexe_mediabox(), and
		 * the locale is already set to C in read_pdf. If this changes,
		 * make sure to have here the C or POSIX locale. */
		n = fscanf(fp, "%lf", &rev);
		while (fgetc(fp) != EOF)
			;
		stat = pclose(fp);
		if (n != 1 || stat != 0)
			return failure;

		if (rev > 9.49) {
			exe = exenew;
			version = new_version;
			*isnew = true;
		} else {
			exe = exeold;
			version = old_version;
			*isnew = false;
		}

		if (appres.DEBUG)
			fprintf(stderr, "...version %.2f\nCommand line: %s\n",
					rev, exe);
	} else { /* version == no_version */
		if (version == new_version) {
			exe = exenew;
			*isnew = true;
		} else {
			exe = exeold;
			*isnew = false;
		}
#undef new_version
#undef old_version
#undef no_version

		if (appres.DEBUG)
			fprintf(stderr,
				"Calling ghostscript.\nCommand line: %s\n",
				exe);
	}

	if ((*out = popen(exe, "r")) == NULL)
		return failure;

	return 0;
}

/*
 * Call ghostscript to extract the /MediaBox from the pdf given in file.
 * Command line, for gs >= 9.50,
 *    gs -q -dNODISPLAY --permit-file-read=in.pdf -c \
 *	"(in.pdf) (r) file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit"
 * gs < 9.50:
 *    gs -q -dNODISPLAY -dNOSAFER -c \
 *	"(in.pdf) (r) file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit"
 * The command line was found, and modified a bit, at
 *https://stackoverflow.com/questions/2943281/using-ghostscript-to-get-page-size
 * Beginning with gs 9.50, "-dSAFER" is the default, and permission to access
 * files must be explicitly given with the --permit-file-{read,write,..}
 * options. Before gs 9.50, "-dNOSAFER" is the default.
 *
 * Return 0 on success, -1 on failure, -2 (GS_ERROR) for a ghostscript-error,
 * -3 if the path to the ghostscript executable is not given.
 */
static int
gsexe_mediabox(char *file, int *llx, int *lly, int *urx, int *ury)
{
	bool	isnew;
	int	n;
	int	stat;
	size_t	len;
	char	*fmt;
	char	exenew_buf[256];
	char	exeold_buf[sizeof exenew_buf];
	char	*exenew;
	char	*exeold;
	double	bb[4] = { 0.0, 0.0, -1.0, -1.0 };
	FILE	*gs_output;

	if (*appres.ghostscript == '\0')
		return -3;

	exenew = "%s -q -dNODISPLAY \"--permit-file-read=%s\" -c \"(%s) (r) "
		"file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit\"";
	exeold = "%s -q -dNODISPLAY -c \"(%s) (r) "
		"file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit\"";

	/* malloc() buffers for the command line, if necessary */
	fmt = exenew;
	len = strlen(exenew) + 2*strlen(file) + strlen(appres.ghostscript) - 5;
	if (len > sizeof exenew_buf) {
		if ((exenew = malloc(len)) == NULL)
			return -1;
	} else {
		exenew = exenew_buf;
	}
	sprintf(exenew, fmt, appres.ghostscript, file, file);

	fmt = exeold;
	len = strlen(exeold) + strlen(file) + strlen(appres.ghostscript) - 3;
	if (len > sizeof exeold_buf) {
		if ((exeold = malloc(len)) == NULL) {
			if (exenew != exenew_buf)
				free(exenew);
			return -1;
		}
	} else {
		exeold = exeold_buf;
	}
	sprintf(exeold, fmt, appres.ghostscript, file);

	/* call ghostscript */
	stat = gsexe(&gs_output, &isnew, exenew, exeold);

	if (exenew != exenew_buf)
		free(exenew);
	if (exeold != exeold_buf)
		free(exeold);

	if (stat != 0) {
		file_msg("Cannot open pipe with command:\n%s",
				isnew ? exenew : exeold);
		return -1;
	}

	/* scan the output */
	n = fscanf(gs_output, "[%lf %lf %lf %lf]", bb, bb+1, bb+2, bb+3);
	while (fgetc(gs_output) != EOF)
		;
	stat = pclose(gs_output);
	if (n != 4 || stat != 0) {
		if (stat) {
			file_msg("Error calling ghostscript. Command:\n%s",
				isnew ? exenew : exeold);
			return GS_ERROR;
		} else {
			return -1;
		}
	}

	*llx = (int)floor(bb[0]);
	*lly = (int)floor(bb[1]);
	*urx = (int)ceil(bb[2]);
	*ury = (int)ceil(bb[3]);

	return 0;
}

#ifdef HAVE_GSLIB
/*
 * Return codes: 0..success, -1..within the function, an error occured,
 *  GS_ERROR..the ghostscript interpreter returned an error
 */
static int
gslib_mediabox(char *file, int *llx, int *lly, int *urx, int *ury)
{
	int		stat;
	int		bb[4] = { 0, 0, -1, -1};
	char		*fmt;
	size_t		len;
#define argc	6
	char		errbuf[256] = "";
	char		*argnew[argc];
	char		*argold[argc];
	char		permit_buf[sizeof errbuf];
	char		cmd_buf[sizeof errbuf];
	struct _callback_data	data = {
		bb,		/* bb */
		errbuf,		/* errbuf */
		sizeof errbuf	/* errsize */
	};

	/* write the argument list and command line */
	argnew[0] = "libgs";
	argnew[1] = "-q";
	argnew[2] = "-dNODISPLAY";
	argnew[3] = "--permit-file-read=%s";	/* file */
	argnew[4] = "-c";
	argnew[5] =
	    "(%s) (r) file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit";

	argold[0] = argnew[0];
	argold[1] = argnew[1];
	argold[2] = argnew[2];
	argold[3] = "-dNOSAFER";
	argold[4] = argnew[4];
	/* argold[5] = argnew[5], assigned below */

	/* write and, if necessary, malloc() argument strings */
	fmt = argnew[3];
	len = strlen(file) + strlen(fmt) - 1;
	if (len > sizeof permit_buf) {
	       if ((argnew[3] = malloc(len)) == NULL)
		       return -1;
	} else {
		argnew[3] = permit_buf;
	}
	sprintf(argnew[3], fmt, file);

	fmt = argnew[5];
	len = strlen(file) + strlen(fmt) - 1;
	if (len > sizeof cmd_buf) {
	       if ((argnew[5] = malloc(len)) == NULL) {
		       if (argnew[3] != permit_buf)
			       free(argnew[3]);
		       return -1;
	       }
	} else {
		argnew[5] = cmd_buf;
	}
	sprintf(argnew[5], fmt, file);
	argold[5] = argnew[5];

	/* call into the ghostscript library */
	stat = gslib(&data, stdin_void, stdout_mediabox, stderr_buf,
				argc, argc, argnew, argold);
	if (argnew[3] != permit_buf)
		free(argnew[3]);
	if (argnew[5] != cmd_buf)
		free(argnew[5]);
#undef argc

	if (stat == 0) {
		if (data.bb[1] == 0 && data.bb[3] == GS_ERROR)
			return GS_ERROR;
		*llx = data.bb[0];
		*lly = data.bb[1];
		*urx = data.bb[2];
		*ury = data.bb[3];
	}

	return stat;
}
#endif /* HAVE_GSLIB */

/*
 * Call ghostscript to extract the /MediaBox from the pdf given in file.
 * Return 0 on success, -1 on failure, GS_ERROR (-2) for a ghostscript error.
 */
int
gs_mediabox(char *file, int *llx, int *lly, int *urx, int *ury)
{
	int	stat;

#ifdef HAVE_GSLIB
	stat = gslib_mediabox(file, llx, lly, urx, ury);
	if (stat == -1)
#endif
		stat = gsexe_mediabox(file, llx, lly, urx, ury);
	if (stat == GS_ERROR) {
		file_msg("Could not parse file '%s' with ghostscript.", file);
		file_msg("If available, error messages are displayed above.");
	}
	return stat;
}

/*
 * Invoke (approximately) the command
 *
 *   gs [..] -sDEVICE=bitrgb -dRedValues=256 -r<ppi> -g<widht>x<height> \
 *	-o- <file>,
 *
 * to obtain a 24bit bitmap of RGB-Values. (It is sufficient to give one out of
 * -dGreenValues=256, -dBlueValues=256 or -dRedValues=256.)
 * For monochrome images, invoke
 *
 *   gs [..] -sDEVICE=bit -r<ppi> -g<widht>x<height> -o- <file>.
 *
 * The neural net that reduces the bitmap to a colormapped image of 256 colors
 * expects BGR triples. Hence, swap the red and blue values.
 * Return 0 on success, -1 for failure, or GS_ERROR if ghostscript returned with
 * a non-zero exit code.
 *
 */
static int
gsexe_bitmap(char *file, F_pic *pic, int llx, int lly, int urx, int ury)
{
#define string_of(ppi)	#ppi
#define	rgb_fmt(ppi)	"%s -q -dSAFER -sDEVICE=bitrgb -dBlueValues=256 -r" \
	string_of(ppi) " -g%dx%d -sPageList=1 -o- -c '%d %d translate' -f %s"
#define	bw_fmt(ppi)	"%s -q -dSAFER -sDEVICE=bit -r" string_of(ppi)	    \
			" -g%dx%d -sPageList=1 -o- -c '%d %d translate' -f %s"
/*
 * Instead of -llx -lly translate, the commands passed to ghostscript used to
 * be:
 *  -llx -lly translate
 *  % mark dictionary (otherwise fails for tiger.ps (e.g.):
 *  % many ps files don't 'end' their dictionaries)
 *  countdictstack
 *  mark
 *  /oldshowpage {showpage} bind def
 *  /showpage {} def
 *  /initgraphics {} def	<<< this nasty command should never be used!
 *  /initmmatrix {} def		<<< this one too
 *  (psfile) run
 *  oldshowpage
 *  % clean up stacks and dicts
 *  cleartomark
 *  countdictstack exch sub { end } repeat
 *  quit
 */
	int		stat;
	int		w, h;
	const int	failure = -1;
	size_t		len;
	size_t		len_bitmap;
	char		*fmt;
	char		*exe;
	unsigned char	*pos;
	char		exe_buf[256];
	FILE		*gs_output;

	if (*appres.ghostscript == '\0')
		return failure;

	/* This is the size, to which a pixmap is rendered for display
	   on the canvas, at a magnification of 2.
	   The +1 is sometimes correct, sometimes not */
	w = (urx - llx) * BITMAP_PPI / 72 + 1;
	h = (ury - lly) * BITMAP_PPI / 72 + 1;
	if (tool_cells <= 2 || appres.monochrome) {
		fmt = bw_fmt(BITMAP_PPI);
		len_bitmap = (w + 7) / 8 * h;
		pic->pic_cache->numcols = 0;
	} else {
		fmt = rgb_fmt(BITMAP_PPI);
		if (tool_vclass == TrueColor && image_bpp == 4)
			len_bitmap = w * h * image_bpp;
		else
			len_bitmap = w * h * 3;
	}
	pic->pic_cache->bit_size.x = w;
	pic->pic_cache->bit_size.y = h;

	/* malloc() buffer for the command line, if necessary; The "+ 80" allows
	   four integers of 20 digits each. */
	len = strlen(fmt) + strlen(file) + strlen(appres.ghostscript) + 80;
	if (len > sizeof exe_buf) {
		if ((exe = malloc(len)) == NULL)
			return failure;
	} else {
		exe = exe_buf;
	}

	/* still check for overflow, because of the integers */
	if (len <= sizeof exe_buf)
		len = sizeof exe_buf;
	stat = snprintf(exe, len, fmt, appres.ghostscript, w, h, -llx, -lly,
			file);
	if ((size_t)stat >= len) {
		if (exe == exe_buf) {
			if ((exe = malloc((size_t)(stat + 1))) == NULL)
				return failure;
		} else {
			if ((exe = realloc(exe, (size_t)(stat + 1))) == NULL) {
				free(exe);
				return failure;
			}
		}
		sprintf(exe, fmt, appres.ghostscript, w, h, -llx, -lly, file);
	}
#undef rgb_fmt
#undef bw_fmt

	if (appres.DEBUG)
		fprintf(stderr, "Calling ghostscript. Command:\n  %s\n", exe);

	gs_output = popen(exe, "r");
	if (gs_output == NULL)
		file_msg("Cannot open pipe with command:\n%s", exe);
	if (exe != exe_buf)
		free(exe);
	if (gs_output == NULL)
		return failure;

	if ((pic->pic_cache->bitmap = malloc(len_bitmap)) == NULL) {
		file_msg("Out of memory.\nCannot create pixmap for %s.", file);
		return failure;
	}

	/* write result to pic->pic_cache->bitmap */
	pos = pic->pic_cache->bitmap;
	if (tool_cells <= 2 || appres.monochrome) {
		int	c;
		while ((c = fgetc(gs_output)) != EOF &&
			(size_t)(pos - pic->pic_cache->bitmap) < len_bitmap) {
			*(pos++) = (unsigned char)c;
		}
		pic->pic_cache->numcols = 0;

	} else if (tool_vclass == TrueColor && image_bpp == 4) {
		int	c[3];
		while ((c[0] = fgetc(gs_output)) != EOF &&
				(c[1] = fgetc(gs_output)) != EOF &&
				(c[2] = fgetc(gs_output)) != EOF &&
				(size_t)(pos - pic->pic_cache->bitmap) <
								len_bitmap) {
			/* this should take care of endian-ness */
			*(unsigned int *)pos = ((unsigned int)c[0] << 16) +
				((unsigned int)c[1] << 8) + (unsigned int)c[2];
			pos += image_bpp;
		}
		pic->pic_cache->numcols = -1;	/* no colormap */

	} else {
		int	c[3];
		/* map_to_palette() expects BGR triples, swap the RGB triples */
		while ((c[0] = fgetc(gs_output)) != EOF &&
				(c[1] = fgetc(gs_output)) != EOF &&
				(c[2] = fgetc(gs_output)) != EOF &&
				(size_t)(pos - pic->pic_cache->bitmap) <
								len_bitmap) {
			*(pos++) = (unsigned char)c[2];
			*(pos++) = (unsigned char)c[1];
			*(pos++) = (unsigned char)c[0];
		}
	}
	stat = pclose(gs_output);
	/* if reading stops just at the last byte in the file, then
	   neither is c[?] == EOF, nor does feof() necessarily return true. */
	if ((size_t)(pos - pic->pic_cache->bitmap) != len_bitmap) {
		free(pic->pic_cache->bitmap);
		pic->pic_cache->bitmap = NULL;
		file_msg("Error reading pixmap to render %s.", file);
		return failure;
	}
	if (stat) {
		free(pic->pic_cache->bitmap);
		pic->pic_cache->bitmap = NULL;
		return GS_ERROR;
	}

	if (tool_vclass != TrueColor && tool_cells > 2 && !appres.monochrome) {
		if (!map_to_palette(pic)) {
			file_msg("Cannot create colormapped image for %s.",
					file);
			return failure;
		}
	}

	return 0;
}

#ifdef HAVE_GSLIB

struct _stdio_data {
	size_t	errsize;
	size_t	errpos;
	size_t	outsize;
	size_t	outpos;
	char	*outbuf;
	char	*errbuf;
};

static int
bitmap_stderr(void *data_handle, const char *str, int len)
{
	struct _stdio_data	*data = (struct _stdio_data *)data_handle;
	char	*buf = data->errbuf;
	size_t	*pos = &(data->errpos);
	size_t	*size = &(data->errsize);

	/* buffer full, comparison for == should be sufficient */
	if (*pos >= *size - 1)
		return len;

	if (*pos + len >= *size)	/* leave space for terminating '\0' */
		len = *size - *pos - 1;
	memcpy(buf + *pos, str, (size_t)len);
	*pos += len;
	buf[*pos] = '\0';

	return len;
}

static int
bitmap_stdout(void *data_handle, const char *str, int len)
{
	struct _stdio_data	*data = (struct _stdio_data *)data_handle;
	char	*buf = data->outbuf;
	size_t	*pos = &(data->outpos);
	size_t	*size = &(data->outsize);

	/* buffer full, comparison for == should be sufficient */
	if (*pos >= *size - 1)
		return len;

	if (*pos + len >= *size)	/* leave space for terminating '\0' */
		len = *size - *pos - 1;
	memcpy(buf + *pos, str, (size_t)len);
	*pos += len;
	buf[*pos] = '\0';

	return len;
}

/* Data provided to the callback functions */
struct calldata {
	int		width;
	int		height;
	int		raster;
	unsigned char	*img;
};


/*
 * Callback functions for the ghostscript display device.
 * The functions are sorted in the order they are called.
 * See ghostscript/gdevdsp.h.
 */
static int
display_open(void *handle, void *device)
{
	(void) device;
	(void) handle;

	return 0;
}

static int
display_presize(void *handle, void *device, int width, int height,
        int raster, unsigned int format)
{
	(void) device;
	(void) raster;
	(void) format;
	struct calldata	*data = (struct calldata *)handle;

	if (width == data->width && height == data->height) {
		return 0;
	} else {
		if (appres.DEBUG)
			fputs("display_presize: Wrong image dimensions.\n",
					stderr);
		return -1;
	}
}

static void *
display_memalloc(void *handle, void *device, unsigned long size)
{
	(void) device;
	struct calldata	*data = (struct calldata *)handle;

	data->img = malloc((size_t)size);

	if (appres.DEBUG && data->img == NULL)
		fputs("gslib_bitmap() - display_memalloc(): Out of memory.\n",
				stderr);

	return (void *)data->img;
}

static int
display_size(void *handle, void *device, int width, int height,
        int raster, unsigned int format, unsigned char *pimage)
{
	(void) device;
	(void) raster;
	(void) format;
	(void) pimage;
	struct calldata	*data = (struct calldata *)handle;

	if (width == data->width && height == data->height) {
		data->raster = raster;
		return 0;
	} else {
		if (appres.DEBUG)
			fputs("display_size: Wrong image dimensions.\n",
					stderr);
		return -1;
	}
}

static int
display_sync(void *handle, void *device)
{
	(void) handle;
	(void) device;

	return 0;
}

static int
display_page(void *handle, void *device, int copies, int flush)
{
	(void) handle;
	(void) device;
	(void) copies;
	(void) flush;

	/* Other error codes cause messages from ghostscript on stderr. */
	return gs_error_InterpreterExit;
}

static int
display_preclose(void *handle, void *device)
{
	(void) handle;
	(void) device;

	return 0;
}

static int
display_memfree(void *handle, void *device, void *mem)
{
	(void) handle;
	(void) device;
	(void) mem;

	return 0;
}

static int
display_close(void *handle, void *device)
{
	(void) handle;
	(void) device;

	return 0;
}

/*
 * Link into the ghostscript library, writing to the display device.
 * Return 0 on success, -1 on failure, or GS_ERROR for a ghostscript error.
 * TODO: With a corrupt pdf, ghostscript will write messages to stdout and
 * return 0. A stdout callback should be used to catch these messages.
 * Warning messages seem to be directed to stderr.
 * TODO: After gs 9.52, ghostscript uses a callout function for registering the
 * callback functions. Implement that interface.
 */
static int
gslib_bitmap(char *file, F_pic *pic, int llx, int lly, int urx, int ury)
{
	int		code;
	int		w, h;
	int		format;
	int		rowstride;
	const int	failure = -1;
	const int	argc = 14;
	char		*arg[14];
			/* the digits in a hexadezimal number are 2 * sizeof */
	char		arg6[20 + 2 * sizeof(uintptr_t)];
			/* the number of digits in a decimal number are less
			 * than ((sizeof(int) / 2) * 3 + sizeof(int)) + 2,
			 * see https://stackoverflow.com/questions/43787672
			 */
#define	DIGITS_IN_INT	(((sizeof(int)/ 2) * 3 + sizeof(int)) + 2)
	char		arg7[17 + DIGITS_IN_INT];
	char		arg8[3 + DIGITS_IN_INT];
	char		arg9[4 + 2 * DIGITS_IN_INT];
	char		arg11[12 + 2 * DIGITS_IN_INT];
#undef DIGITS_IN_INT
	void		*minst = NULL;	/* must be initialized to NULL */
	char		errbuf[BUFSIZ];
	char		outbuf[BUFSIZ];
	struct calldata handle;		/* passed to the callback functions */

	struct _stdio_data stdio_data = {
		sizeof errbuf,		/* errsize */
		(size_t) 0,		/* errpos */
		sizeof outbuf,		/* outsize */
		(size_t) 0,		/* outpos */
		outbuf,
		errbuf
	};

	/* callback structure for "display" device */
	struct display_callback_s callback_functions = {
		sizeof(struct display_callback_s),
		DISPLAY_VERSION_MAJOR,
		DISPLAY_VERSION_MINOR,
		display_open,
		display_preclose,
		display_close,
		display_presize,
		display_size,
		display_sync,
		display_page,
		NULL,	/* display_update */
		display_memalloc,
		display_memfree,
		NULL	/* display_separation */
	};


	/* This should be the size to which a pixmap is rendered for display
	   on the canvas, at a magnification of 2.
	   The +1 is sometimes correct, sometimes not */
	w = (urx - llx) * BITMAP_PPI / 72 + 1;
	h = (ury - lly) * BITMAP_PPI / 72 + 1;
	handle.width = w;
	handle.height = h;

	/* Set the format flags for -dDisplayFormat=%d. */
	/* DISPLAY_ROW_ALIGN_x must be equal or greater than
	   the size of a pointer */
	format = DISPLAY_TOPFIRST | DISPLAY_ROW_ALIGN_8;
	if (tool_cells <= 2 || appres.monochrome) {
		format |= DISPLAY_COLORS_NATIVE | /*  DISPLAY_ALPHA_NONE */
			DISPLAY_DEPTH_1;

		rowstride = (w + 7) / 8;
		/* size = (size_t)((w + 7) / 8 * h); */
		pic->pic_cache->numcols = 0;
	} else {
		format = DISPLAY_COLORS_RGB | DISPLAY_DEPTH_8 |
#ifdef WORDS_BIGENDIAN
				DISPLAY_BIGENDIAN;	/* RGB */
#else
				DISPLAY_LITTLEENDIAN;	/* BGR */
#endif
		if (tool_vclass == TrueColor && image_bpp == 4) {
#ifdef WORDS_BIGENDIAN
			format |= DISPLAY_UNUSED_FIRST;	/* xRGB */
#else
			format |= DISPLAY_UNUSED_LAST;	/* BGRX */
#endif
			rowstride = w * image_bpp;
			/* size = (size_t)(w * h * image_bpp); */
			pic->pic_cache->numcols = -1;
		} else {
			/* DISPLAY_ALPHA_NONE ... == 0, not necessary */
			rowstride = w * 3;
			/* size = (size_t)(w * h * 3); */
			/* not necessary to set pic->pic_cache->numcols */
		}
	}

	/*
	 * Options to ghostscript: It was not possible to use switches from the
	 * family of -dLastPage=1 or -sPageList=1, because these resulted in an
	 * all white pixmap. Therefore, interrupt the interpreter by having the
	 * display_page() callback return gs_error_InterpreterExit. For this
	 * error code, ghostscript returns 0 and does not write messages to
	 * stderr.
	 */
	arg[0] = "libgs";
	arg[1] = "-q";
	arg[2] = "-dSAFER";	/* default for gs >= 9.50; for gs < 9.50,
				   default is -dNOSAFER */
	arg[3] = "-dBATCH";
	arg[4] = "-dNOPAUSE";
	arg[5] = "-sDEVICE=display";
	arg[6] = "-sDisplayHandle=16#%" PRIxPTR;
	arg[7] = "-dDisplayFormat=%d";
	arg[8] = "-r%d";	/* resolution */
	arg[9] = "-g%dx%d";	/* width x height */
	arg[10] = "-c";
	arg[11] = "%d %d translate";
	arg[12] = "-f";		/* terminate list of tokens for the -c switch */
	arg[13] = file;

	sprintf(arg6, arg[6], (uintptr_t)&handle);
	arg[6] = arg6;
	sprintf(arg7, arg[7], format);
	arg[7] = arg7;
	sprintf(arg8, arg[8], BITMAP_PPI);
	arg[8] = arg8;
	sprintf(arg9, arg[9], w, h);
	arg[9] = arg9;
	sprintf(arg11, arg[11], -llx, -lly);
	arg[11] = arg11;

	if (appres.DEBUG) {
		int	i;
		fputs("Using ghostscript library, arguments:\n ", stderr);
		for (i = 0; i < argc; ++i) {
			fputc(' ', stderr);
			fputs(arg[i], stderr);
		}
		fputc('\n', stderr);
	}

	/* call ghostscript */
	code = gsapi_new_instance(&minst, (void *)&stdio_data);
	if (code == 0)
		code = gsapi_set_stdio(minst,NULL,bitmap_stdout,bitmap_stderr);
	else
		return gsexe_bitmap(file, pic, llx, lly, urx, ury);

	if (code == 0)
		code = gsapi_set_display_callback(minst, &callback_functions);
	if (code == 0)
		code = gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
	if (code == 0)
		code = gsapi_init_with_args(minst, argc, arg);
	if (code != 0 && code != gs_error_Quit)
		gsapi_exit(minst);
	else
		code = gsapi_exit(minst);

	gsapi_delete_instance(minst);

	if (stdio_data.outpos > (size_t)0)
		file_msg("Message from ghostscript when creating pixmap:\n%s",
				stdio_data.outbuf);
	if (stdio_data.errpos > (size_t)0)
		file_msg("Error message from ghostscript when creating pixmap:\n%s",
				stdio_data.errbuf);

	if (code != 0 && code != gs_error_Quit) {
		free(handle.img);
		return GS_ERROR;
	}
	/* code == 0 || code == gs_error_Quit */
	if (rowstride > handle.raster) {
		if (appres.DEBUG)
			fputs("The pixmap rendered by ghostscript is larger "
					"than xfig expected.\n", stderr);
		free(handle.img);
		return failure;
	} else if (rowstride < handle.raster) {
		/* Move pixmap data to the alignment expected by xfig. */
		int		i;
		unsigned char	*src;
		unsigned char	*dst;

		for (i = 1; i < h; ++i) {
			src = handle.img + i * handle.raster;
			dst = handle.img + i * rowstride;
			for (src = handle.img + i * handle.raster;
			     src < handle.img + i * handle.raster + rowstride;
					) {
				*(dst++) = *(src++);
			}
		}
		handle.img = realloc(handle.img, (size_t)(dst - handle.img));
	}

	pic->pic_cache->bit_size.x = w;
	pic->pic_cache->bit_size.y = h;
	pic->pic_cache->bitmap = handle.img;

	if (tool_vclass != TrueColor && tool_cells > 2 && !appres.monochrome) {
		if (!map_to_palette(pic)) {
			file_msg("Cannot create colormapped image for %s.",
					file);
			return failure;
		}
	}

	return 0;
}
#endif /* HAVE_GSLIB */

/*
 * Create a pixmap in pic->pic_cache->bitmap from the ps/eps/pdf file "file"
 * having the bounding box llx lly urx ury.
 * Return 0 on success, -1 on failure, or GS_ERROR for a ghostscript error.
 */
int
gs_bitmap(char *file, F_pic *pic, int llx, int lly, int urx, int ury)
{
	int	stat;

#ifdef HAVE_GSLIB
	stat = gslib_bitmap(file, pic, llx, lly, urx, ury);
#else
	stat = gsexe_bitmap(file, pic, llx, lly, urx, ury);
#endif
	if (stat == GS_ERROR) {
		file_msg("Could not create pixmap from '%s' with ghostscript.",
				file);
	}
	return stat;
}
