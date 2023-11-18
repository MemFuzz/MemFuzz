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
 * readeps.c: import EPS into PostScript
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "messages.h"
#include "readpics.h"

int	read_eps(F_pic *pic, struct xfig_stream *restrict pic_stream,
		int *llx, int *lly);

/* for both procedures:
     return codes:  1 : success
		    0 : failure
*/

#ifdef GSEXE

/*
 * Call ghostscript.
 * Return an open file stream for reading,
 *   *out = popen({exenew, exeold}, "r");
 * The user must call pclose(out) after calling gsexe(&out,...).
 * Use exenew for gs > 9.49, exeold otherwise.
 * Return 0 for success, -1 on failure to call ghostscript.
 *
 * Copied from xfig/src/u_ghostscript.c.
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
		double		rev;
		char		*cmd = GSEXE " --version";

		/* get the ghostscript version */
		fp = popen(cmd, "r");
		if (fp == NULL)
			return failure;

		/* scan for the ghostscript version */
		/* Currently, gsexe() is only called from gsexe_mediabox(), and
		 * the locale is already set to C in read_pdf. If this changes,
		 * make sure to have here the C or POSIX locale. */
		n = fscanf(fp, "%lf", &rev);
		stat = pclose(fp);
		if (n != 1 || stat != 0)
			return stat == 0 ? failure : (WIFEXITED(stat) ?
						WEXITSTATUS(stat) : failure);

		if (rev > 9.49) {
			exe = exenew;
			version = new_version;
			*isnew = true;
		} else {
			exe = exeold;
			version = old_version;
			*isnew = false;
		}
	} else { /* version == no_version */
		if (version == new_version) {
			exe = exenew;
			*isnew = true;
		} else {
			exe = exeold;
			*isnew = false;
		}
	}
#undef new_version
#undef old_version
#undef no_version

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
 * Return 0 on success, -1 on failure, -2 for a ghostscript-error.
 *
 * Copied from xfig/src/u_ghostscript.c.
 */
static int
gsexe_mediabox(char *file, int *llx, int *lly, int *urx, int *ury)
{
	bool	isnew;
	static bool has_gs = true;
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

	exenew = GSEXE " -q -dNODISPLAY '--permit-file-read=%s' -c '(%s) (r) "
		"file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit'";
	exeold = GSEXE " -q -dNODISPLAY -c '(%s) (r) "
		"file runpdfbegin 1 pdfgetpage /MediaBox pget pop == quit'";

	if (!has_gs)
		return -1;

	/* malloc() buffers for the command line, if necessary */
	fmt = exenew;
	len = strlen(exenew) + 2 * strlen(file) - 3;
	if (len > sizeof exenew_buf) {
		if ((exenew = malloc(len)) == NULL)
			return -1;
	} else {
		exenew = exenew_buf;
	}
	sprintf(exenew, fmt, file, file);

	fmt = exeold;
	len = strlen(exeold) + strlen(file) - 1;
	if (len > sizeof exeold_buf) {
		if ((exeold = malloc(len)) == NULL) {
			if (exenew != exenew_buf)
				free(exenew);
			return -1;
		}
	} else {
		exeold = exeold_buf;
	}
	sprintf(exeold, fmt, file);

	/* call ghostscript */
	stat = gsexe(&gs_output, &isnew, exenew, exeold);

	if (exenew != exenew_buf)
		free(exenew);
	if (exeold != exeold_buf)
		free(exeold);

	if (stat != 0) {
		if (stat == 127) {
			put_msg("Could not call ghostscript executable, " GSEXE
					".\nPlease install ghostscript to embed"
					" pdf files into a fig document.");
			has_gs = false;
			return -1;
		}
		err_msg("Cannot open pipe with command:\n%s",
				isnew ? exenew : exeold);
		return -1;
	}

	/* scan the output */
	n = fscanf(gs_output, "[%lf %lf %lf %lf]", bb, bb+1, bb+2, bb+3);
	stat = pclose(gs_output);
	if (n != 4 || stat != 0) {
		if (stat) {
			err_msg("Error calling ghostscript. Command:\n%s",
				isnew ? exenew : exeold);
			return -2;
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

#endif /* GSEXE */

/*
 * Scan a pdf-file for a /MediaBox specification. The FILE pointer file must
 * point to an open file-stream located close to the start of the file.
 * Return 0 on success, -1 on failure.
 *
 * Copied from xfig/src/u_ghostscript.c.
 */
static int
scan_mediabox(FILE *file, int *llx, int *lly, int *urx, int *ury)
{
	/*
	 * The line length of pdfs should not exceed 256 characters. However, in
	 * pdfs, the line end character might be a carriage return, while
	 * fgets() reads lines ended by newlines.
	 */
	char	buf[512];
	char	*s;
	int	ret = -1;	/* prime with failure */
	double	lx, ly, ux, uy;

	while (fgets(buf, sizeof buf, file) != NULL) {
		if ((s = strstr(buf, "/MediaBox"))) {
			s = strchr(s, '[');
			if (s && sscanf(s + 1, "%lf %lf %lf %lf",
						&lx, &ly, &ux, &uy) == 4) {
				*llx = (int)floor(lx);
				*lly = (int)floor(ly);
				*urx = (int)ceil(ux);
				*ury = (int)ceil(uy);
				ret = 0;
			}
			/* do not search for a second occurrence of /MediaBox */
			break;
		}
	}

	return ret;
}

/*
 * Get the bounding box of a PDF file.
 * Return codes: 1 - success,
 *		 0 - failure.
 */
int
read_pdf(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	int	urx, ury;

	/*
	 * read_pdf() is called from genps.c, where the first 12 bytes were
	 * read. Take the risk, do not rewind, and continue to search for the
	 * /MediaBox.
	 *	if (!rewind_stream(pic_stream))
	 *		return 0;
	 */

	pic->subtype = P_EPS;

	if (scan_mediabox(pic_stream->fp, llx, lly, &urx, &ury)) {
#ifdef GSEXE
		if (uncompressed_content(pic_stream))
			return 0;
		if (gsexe_mediabox(pic_stream->content, llx, lly, &urx, &ury))
			return 0;
		pic->bit_size.x = urx - *llx;
		pic->bit_size.y = ury - *lly;
#else
		return 0;
#endif
	} else {
		pic->bit_size.x = urx - *llx;
		pic->bit_size.y = ury - *lly;
	}
	fprintf(tfp, "%% Begin Imported PDF File, converted to EPS: %s\n",
			pic->file);
	fprintf(tfp, "%%%%BeginDocument: %s\n", pic->file);
	fputs("%\n", tfp);
	return 1;
}

/*
 * Read an EPS file.
 * Return codes: 1 - success,
 *		 0 - failure.
 */
int
read_eps(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	char	buf[300];
	int	nested;

	if (!rewind_stream(pic_stream))
		return 0;

	pic->bit_size.x = pic->bit_size.y = 0;
	pic->subtype = P_EPS;

	/* give some initial values for bounding box in case none is found */
	*llx = 0;
	*lly = 0;
	pic->bit_size.x = 10;
	pic->bit_size.y = 10;

	/* scan for the bounding box */
	nested = 0;
	while (fgets(buf, sizeof buf, pic_stream->fp) != NULL) {
		if (!nested && !strncmp(buf, "%%BoundingBox:", 14)) {
			/* make sure doesn't say (atend) */
			if (!strstr(buf, "(atend)")) {
				double       rllx, rlly, rurx, rury;

				if (sscanf(strchr(buf, ':') + 1,
						"%lf %lf %lf %lf", &rllx, &rlly,
						&rurx,&rury) < 4) {
					put_msg("Bad EPS file: %s", pic->file);
					return 0;
				}
				*llx = floor(rllx);
				*lly = floor(rlly);
				pic->bit_size.x = (int)(rurx - rlly);
				pic->bit_size.y = (int)(rury - rlly);
				break;
			}
		} else if (!strncmp(buf, "%%Begin", 7)) {
			++nested;
		} else if (nested && !strncmp(buf, "%%End", 5)) {
			--nested;
		}
	}

	fprintf(tfp, "%% Begin Imported EPS File: %s\n", pic->file);
	fprintf(tfp, "%%%%BeginDocument: %s\n", pic->file);
	fputs("%\n", tfp);
	return 1;
}

static int
has_pdftops(void)
{
	static int	res = -1;
	if (res != -1)
		return res;
	if (system("pdftops -v 2>/dev/null"))
		res = 0;
	else
		res = 1;
	return res;
}

static int
has_pdftocairo(void)
{
	static int	res = -1;
	if (res != -1)
		return res;
	if (system("pdftocairo -v 2>/dev/null"))
		res = 0;
	else
		res = 1;
	return res;
}

#ifdef GSEXE
static int
has_gs(void)
{
	static int	res = -1;
	if (res != -1)
		return res;
	if (system(GSEXE " -v >/dev/null"))
		res = 0;
	else
		res = 1;
	return res;
}
#endif

/*
 * Convert a pdf to eps, and write the resulting pdf to the output stream.
 * Return 0 on success, -1 on failure.
 */
int
pdftops(struct xfig_stream *restrict pic_stream, FILE *out)
{
	char	cmd_buf[256];
	char	*cmd = cmd_buf;
	char	buf[BUFSIZ];
	char	*cmd_fmt;
	int	ret = 0;
	size_t	size;
	FILE	*f;

	if (uncompressed_content(pic_stream))
		return -1;

	if (strchr(pic_stream->content, '\'')) {
		put_msg("Cannot read a pdf file containing an apostrophe (') "
				"in its name: %s\nPlease re-name the file.",
				pic_stream->content);
		return -1;
	}

	/*
	 * Convert a pdf to eps, using the first available of the following:
	 *   pdftops -q -f 1 -l 1 -eps in.pdf -
	 *   pdftocairo -q -f 1 -l 1 -eps in.pdf -
	 *   gs -q -dSAFER -sDEVICE=eps2write -sPageList=1 -o - in.pdf
	 * Only pdftops uses the original /MediaBox as the BoundingBox in the
	 * resulting pfd. The other two crop the BoundingBox to the smallest box
	 * containing all the ink on the paper.
	 */
	if (has_pdftops())
		cmd_fmt = "pdftops -q -f 1 -l 1 -eps '%s' -";
	else if (has_pdftocairo())
		cmd_fmt = "pdftocairo -q -f 1 -l 1 -eps '%s' -";
#ifdef GSEXE
	else if (has_gs())
		cmd_fmt = GSEXE
			" -q -dSAFER -sDEVICE=eps2write -sPageList=1 -o - '%s'";
#endif
	else {
		static bool	reported = false;
		if (!reported) {
			put_msg("Cannot convert a pdf to eps.\nPlease install "
	"either pdftops or pdftocairo from the poppler-utils package,\n"
#ifdef GSEXE
	"or the ghostscript program."
#endif
			);
			reported = true;
		}
		return -1;
	}

	size = sizeof cmd_fmt + strlen(pic_stream->content) - 2;
	if (size > sizeof cmd_buf && (cmd = malloc(size)) == NULL) {
		put_msg(Err_mem);
		return -1;
	}
	sprintf(cmd, cmd_fmt, pic_stream->content);
	if ((f = popen(cmd, "r")) == NULL) {
		err_msg("Cannot convert pdf to eps");
		put_msg("Command: %s", cmd);
		if (cmd != cmd_buf)
			free(cmd);
		return -1;
	}
	while ((size = fread(buf, 1, sizeof buf, f)) &&
			fwrite(buf, 1, size, out) == size)
		;
	if (ferror(f)) {
		err_msg("Could not read from pipe %s", cmd);
		ret = -1;
	}
	if (ferror(tfp)) {
		err_msg("Cannot write to output");
		ret = -1;
	}
	if (pclose(f)) {
		err_msg("Failed to convert pdf to eps");
		put_msg("Command: %s", cmd);
		ret = -1;
	}
	if (cmd != cmd_buf)
		free(cmd);

	return ret;
}


/*
 * Write the eps-part of the epsi-file pointed to by in to out.
 * return codes:	 0	success,
 *			-1	nothing written,
 *		   termination	on partial write
 */
int
append_epsi(FILE *in, const char *filename, FILE *out)
{
	size_t		l = 12;
	unsigned char	buf[BUFSIZ];
	int		i;
	unsigned int	start = 0;
	unsigned int	length = 0;

	if (fread(buf, 1, l, in) != l) {
		fprintf(stderr, "Cannot read EPSI file %s.\n", filename);
		return -1;
	}
	for (i = 0; i < 4; ++i) {
		/* buf must be unsigned, otherwise the left shift fails */
		start += buf[i+4] << i*8;
		length += buf[i+8] << i*8;
	}
	/* read forward to start of eps section.
	   do not use fseek, in might be a pipe */
	if (fread(buf, 1, start - l, in) != start - l)
		return -1;

#define	EPSI_ERROR(mode)	fprintf(stderr, "Error when " mode \
		" embedded EPSI file %s.\nAborting.\n", filename), \
		exit(EXIT_FAILURE)

	l = BUFSIZ;
	while (length > l) {
		if (fread(buf, 1, l, in) != l)
			EPSI_ERROR("reading");
		length -= l;
		if (fwrite(buf, 1, l, out) != l)
			EPSI_ERROR("writing");
	}
	/* length < BUFSIZ  ( = l)*/
	if (length > 0) {
		if (fread(buf, 1, length, in) != length)
			EPSI_ERROR("reading");
		if (fwrite(buf, 1, length, out) != length)
			EPSI_ERROR("writing");
	}
	return 0;
}
