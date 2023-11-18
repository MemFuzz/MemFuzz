/*
 * TransFig: Facility for Translating Fig code
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include <strings.h>

/*
 * converters program names
 */
#define FIG2DEV	"fig2dev"
#define PIC2FIG "pic2fig"
#define APG2FIG "apgto f"

/*
 * filename defaults
 */
#define MK "Makefile"
#define TX "transfig.tex"

/* if using LaTeX209, use "documentstyle", if using LaTeX2e use "usepackage" */
#ifdef LATEX2E
#define INCLFIG "usepackage"
#else
#define INCLFIG "documentstyle"
#endif

/* Warning - if this list is changed the lname[] array in transfig.c must be changed too */
/* Also, be sure to change MAXLANG if the list extends beyond the current lang */

enum language  {box, cgm, eepic, eepicemu, emf, epic, eps, gbx, gif,
	ibmgl, dxf, jpeg, latex, map, mf, mmp, mp, pcx, pdf, pdftex,
	pic, pict2e, pictex, png, ppm, ps, psfig, pstex, ptk, sld, svg,
	textyl, tiff, tikz, tk, tpic, xbm, xpm};
#define MAXLANG xpm

enum input {i_apg, i_fig, i_pic, i_ps, i_eps, i_pdf};
#define MAXINPUT xps

typedef struct argument{
	char *name, *interm, *f, *s, *m, *o, *tofig, *topic, *tops, *topdf;
	enum language tolang;
	enum input type;
	struct argument *next;
} argument ;

extern enum language str2lang();
extern char *lname[];
extern char *iname[];

extern char *sysls(), *mksuff();
extern argument *arglist;
extern char *txfile, *mkfile;

extern char *optarg;
extern int optind;
