/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2019 by Thomas Loimer
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
 * genpstex.c: convert fig to psTeX and psTeX_t
 *
 * Author: Jose Alberto Fernandez R /Maryland CP 9/90
 *
 *
 * It uses the LaTeX and PostScript drivers to generate
 * LaTeX processed text for a Postscript figure.
 *
 * The pstex_t driver is like a latex driver that only translates
 * text defined in the default font.
 *
 * The pstex driver is like a PostScript driver that translates
 * everything except for text in the default font.
 *
 * The pdftex_t and pdftex are drivers for combined PDF/LaTeX.
 *
 * The option '-p file' added to the pstex_t translator specifies
 * the name of the PostScript file to be called in the psfig macro.
 * If not set or its value is null then no PS file will be inserted.
 *
 * Jose Alberto.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>

#include "fig2dev.h"
#include "object.h"

extern double rad2deg;

extern void
	genlatex_start(F_compound *objects),
	geneps_option(char opt, char *optarg),
	genps_start(F_compound *objects),
	genps_arc(F_arc *a),
	genps_ellipse(F_ellipse *e),
	genps_line(F_line *l),
	genps_spline(F_spline *s),
	genlatex_option(char opt, char *optarg),
	genlatex_text(F_text *t),
	genps_text(F_text *t);
extern int
	genlatex_end(void),
	genps_end(void);

extern void	genpdf_option(char opt, char *optarg);	/* genpdf.c */
extern void	genpdf_start(F_compound *objects);	/* genpdf.c */
extern int	genpdf_end(void);			/* genpdf.c */
extern void	genps_grid(float major, float minor);

static char pstex_file[1000] = "";

void
genpstex_t_option(char opt, char *optarg)
{
       if (opt == 'p')
	   strcpy(pstex_file, optarg);
       else
	   genlatex_option(opt, optarg);
}


void
genpstex_t_start(F_compound *objects)
{
	/* Put PostScript Image if any*/
	if (pstex_file[0] != '\0') {
		fprintf(tfp, "\\begin{picture}(0,0)%%\n");
/* newer includegraphics directive suggested by Stephen Harker 1/13/99 */
#ifdef LATEX2E_GRAPHICS
		fprintf(tfp, "\\includegraphics{%s}%%\n",pstex_file);
#else
		fprintf(tfp, "\\special{psfile=%s}%%\n",pstex_file);
#endif
		fprintf(tfp, "\\end{picture}%%\n");
	}
	genlatex_start(objects);

}

void
genpstex_t_text(F_text *t)
{
	if (special_text(t))
		genlatex_text(t);
}

void
genpstex_text(F_text *t)
{
	if (!special_text(t))
		genps_text(t);
}

void
genpstex_option(char opt, char *optarg)
{
       if (opt != 'p')
	   genlatex_option(opt, optarg);
}

struct driver dev_pstex_t = {
	genpstex_t_option,
	genpstex_t_start,
	gendev_nogrid,
	(void (*)(F_arc *))gendev_null,
	(void (*)(F_ellipse *))gendev_null,
	(void (*)(F_line *))gendev_null,
	(void (*)(F_spline *))gendev_null,
	genpstex_t_text,
	genlatex_end,
	INCLUDE_TEXT
};

struct driver dev_pdftex_t = {
	genpstex_t_option,
	genpstex_t_start,
	gendev_nogrid,
	(void (*)(F_arc *))gendev_null,
	(void (*)(F_ellipse *))gendev_null,
	(void (*)(F_line *))gendev_null,
	(void (*)(F_spline *))gendev_null,
	genpstex_t_text,
	genlatex_end,
	INCLUDE_TEXT
};

struct driver dev_pstex = {
	geneps_option,	/* use eps so always exported in Portrait mode */
	genps_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genpstex_text,
	genps_end,
	INCLUDE_TEXT
};

struct driver dev_pdftex = {
	genpdf_option,
	genpdf_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genpstex_text,
	genpdf_end,
	INCLUDE_TEXT
};
