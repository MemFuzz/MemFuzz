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
 * genpdf.c: convert fig to pdf
 *
 * Author: Brian V. Smith
 *		Uses genps functions to generate PostScript output then
 *		calls ghostscript (device pdfwrite) to convert it to pdf.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "fig2dev.h"
#include "object.h"
#include "genps.h"
#include "messages.h"

/*
 * The ghostscript command line.
 * With -dAutoFilterColorImages=false,
 * -dColorImageFilter=/FlateEncode	produces a lossless but large image,
 * -dColorImageFilter=/DCTEncode	produces a lossy but much smaller image.
 * The default, -dAutoFilterColorImages=true is fine for e.g., png and jpg.
 * -o also sets -dBATCH -dNOPAUSE
 */
#ifdef GSEXE
#define	GSFMT	GSEXE " -q -dSAFER -dAutoRotatePages=/None -sDEVICE=pdfwrite " \
			"-dPDFSETTINGS=/prepress -o '%s' -"
#else
#define GSFMT	""
#endif

/* String buffer for the ghostscript command. 82 chars for the filename */
static char	com_buf[sizeof GSFMT + 80];
static char	*com = com_buf;


void
genpdf_option(char opt, char *optarg)
{
	static bool	init = false;
	if (!init) {
		epsflag = true; /* by default, generate eps, then pdf */
		pdfflag = true;
		init = true;
	}

	/* -P...pagemode, or a pagesize (-z) is given, implies -P */
	if (opt == 'z' || opt == 'P')
		epsflag = false;
	gen_ps_eps_option(opt, optarg);
}

static void
pdf_broken_pipe(int sig)
{
	(void)	sig;

	fputs("fig2dev: broken pipe when translating to pdf\n", stderr);
	fprintf(stderr, "command was: %s\n", com);
	exit(EXIT_FAILURE);
}

void
genpdf_start(F_compound *objects)
{
#ifdef GSEXE
	size_t	len;
	char	*ofile;

	/* divert output from ps driver to the pipe into ghostscript */
	/* but first close the output file that main() opened */
	if (tfp != stdout) {
		fclose(tfp);
		ofile = to;
	} else {
		ofile = "-";
	}

	/* write command for conversion to pdf */
	len = sizeof GSFMT + strlen(ofile) - 2;
	if (len > sizeof com_buf && (com = malloc(len)) == NULL) {
		put_msg(Err_mem);
		exit(EXIT_FAILURE);
	}
	if (sprintf(com, GSFMT, ofile) < 0) {
		err_msg("fig2dev: error when creating ghostscript command");
		exit(EXIT_FAILURE);
	}

	(void) signal(SIGPIPE, pdf_broken_pipe);
	if ((tfp = popen(com, "w")) == 0) {
		err_msg("fig2dev: Cannot open pipe to ghostscript");
		put_msg("Command was: %s", com);
		exit(EXIT_FAILURE);
	}
	genps_start(objects);
#else /* GSEXE */
	put_msg("This fig2dev is compiled without ghostscript support.\n"
			"Cannot create pdf output.");
	exit(EXIT_FAILURE);
#endif
}

int
genpdf_end(void)
{
	int	 status;

	/* wrap up the postscript output */
	if (genps_end() != 0) {
		pclose(tfp);
		if (com != com_buf)
			free(com);
		return -1;		/* error, return now */
	}

	status = pclose(tfp);
	/* we've already closed the original output file */
	tfp = 0;	/* so main() does not close tfp again */
	if (status != 0) {
		err_msg("Error in ghostcript command,\n  %s", com);
		status = -1;
	} else {
		(void)signal(SIGPIPE, SIG_DFL);
	}

	if (com != com_buf)
		free(com);
	return status;
}

struct driver dev_pdf = {
	genpdf_option,
	genpdf_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genps_text,
	genpdf_end,
	INCLUDE_TEXT
};
