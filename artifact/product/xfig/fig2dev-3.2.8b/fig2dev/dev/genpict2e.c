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
 * genpict2e.c: convert fig to pict2e macro language for LaTeX
 *
 * Author: Thomas Loimer, Wien, Austria, 2014-2015
 * Based on the latex picture driver, genlatex.c
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
#include "bound.h"
#include "free.h"		/* free_linestorage() */
#include "messages.h"
#include "pi.h"
#include "psfonts.h"
#include "texfonts.h"		/* texfontnames[] */
#include "trans_spline.h"	/* create_line_with_spline() */

#undef M_PI_2
#undef M_PI_4
#define	M_PI_2	1.57079632679489661923
#define	M_PI_4	0.78539816339744830962

/* String arrays */
extern char	*ISO1toTeX[];	/* iso2tex.c */
extern char	*ISO2toTeX[];	/* iso2tex.c */
static char	*texfonts[] = {
	"",			/* default */
	"\\rmfamily",		/* roman */
	"\\bfseries",		/* bold */
	"\\itshape",		/* italic */
	"\\sffamily",		/* sans serif */
	"\\ttfamily",		/* typewriter */
};
static char	*texpsfonts[] = {
	"{T1}{ptm}{m}{n}",	/* Times-Roman, default */
	"{T1}{ptm}{m}{n}",	/* Times-Roman */
	"{T1}{ptm}{m}{it}",     /* Times-Italic */
	"{T1}{ptm}{b}{n}",      /* Times-Bold */
	"{T1}{ptm}{b}{it}",     /* Times-BoldItalic */
	"{T1}{pag}{m}{n}",      /* AvantGarde */
	"{T1}{pag}{m}{sl}",     /* AvantGarde-BookOblique */
	"{T1}{pag}{db}{n}",     /* AvantGarde-Demi */
	"{T1}{pag}{db}{sl}",    /* AvantGarde-DemiOblique */
	"{T1}{pbk}{l}{n}",      /* Bookman-Light */
	"{T1}{pbk}{l}{it}",     /* Bookman-LightItalic */
	"{T1}{pbk}{db}{n}",     /* Bookman-Demi */
	"{T1}{pbk}{db}{it}",    /* Bookman-DemiItalic */
	"{T1}{pcr}{m}{n}",      /* Courier */
	"{T1}{pcr}{m}{sl}",     /* Courier-Oblique */
	"{T1}{pcr}{b}{n}",      /* Courier-Bold */
	"{T1}{pcr}{b}{sl}",     /* Courier-BoldItalic */
	"{T1}{phv}{m}{n}",      /* Helvetica */
	"{T1}{phv}{m}{sl}",     /* Helvetica-Oblique */
	"{T1}{phv}{b}{n}",      /* Helvetica-Bold */
	"{T1}{phv}{b}{sl}",     /* Helvetica-BoldOblique */
	"{T1}{phv}{mc}{n}",     /* Helvetica-Narrow */
	"{T1}{phv}{mc}{sl}",    /* Helvetica-Narrow-Oblique */
	"{T1}{phv}{bc}{n}",     /* Helvetica-Narrow-Bold */
	"{T1}{phv}{bc}{sl}",    /* Helvetica-Narrow-BoldOblique */
	"{T1}{pnc}{m}{n}",      /* NewCenturySchlbk-Roman */
	"{T1}{pnc}{m}{it}",     /* NewCenturySchlbk-Italic */
	"{T1}{pnc}{b}{n}",      /* NewCenturySchlbk-Bold */
	"{T1}{pnc}{b}{it}",     /* NewCenturySchlbk-BoldItalic */
	"{T1}{ppl}{m}{n}",      /* Palatino-Roman */
	"{T1}{ppl}{m}{it}",     /* Palatino-Italic */
	"{T1}{ppl}{b}{n}",      /* Palatino-Bold */
	"{T1}{ppl}{b}{it}",     /* Palatino-BoldItalic */
	"{U}{psy}{m}{n}",       /* Symbol */
	"{T1}{pzc}{mb}{it}",    /* ZapfChancery-MediumItalic */
	"{U}{pzd}{m}{n}"	/* ZapfDingbats */
};

/* Variables */
static bool	nofontsize = false;
static bool	nofontname = false;
static bool	epiccompatible = true;
static bool	removesuffix = false;
static bool	usetexfonts = false;
static bool	allspecial = false;
static bool	pagemode = false;
static bool	allarrowsltx = false;
static char	*prepend = NULL;
static int	ltxarrow = -1;	/* arrow index to be replaced by a latex-vector */
static int	encoding = 1;
static int	verbose = 0;
static double	unitlength;
static int	cur_thickness = 0;
static int	saved_thickness = 0;
static int	cur_joinstyle = 0;
static int	cur_capstyle = 0;
static int	default_color = DEFAULT;
static int	cur_color = DEFAULT;
static int	cur_shade = NUMSHADES - 1;
static int	border_margin = 0;

/* Definitions */
struct pattern {		/* the dash pattern of non-solid lines */
#define PAT_ND_2 8
	int	d[2*PAT_ND_2];	/* length of dashes[even] and spaces[odd] */
	int	nd;		/* last element in d[] */
	int	length;		/* length of the entire dash-pattern */
};

struct pict2earrow {
	double	hfac;	/* the line should end at hfac times the arrow height */
	double	tfac;	/* plus tfac times arrow line thickness from the last point */
} pict2earrow[] = {
	/* type 0 */
	{ 0., 0.5},
	/* place holder for what would be type 0 filled */
	{ 0., 0. },
	/* type 1a simple triangle */
	{ 1., 0.5},
	/* type 1b filled simple triangle*/
	{ 1., 0.5},
	/* type 2a concave spearhead */
	{ 1., 0.5},
	/* type 2b filled concave spearhead */
	{ 1., 0.5},
	/* type 3a convex spearhead */
	{ 1., -0.5},
	/* type 3b filled convex spearhead */
	{ 1., -0.5},
	/* type 4a diamond */
	{ 1., -0.5},
	/* type 4b filled diamond */
	{ 1., -0.5},
	/* type 5a/b circle - handled in code */
	{ 1., 0.5},
	{ 1., 0.5},
	/* type 6a/b half circle - handled in code */
	{ 0.5, -0.5},
	{ 0.5, -0.5},
	/* type 7a square */
	{ 1., 0.5},
	/* type 7b filled square */
	{ 1., 0.5},
	/* type 8a reverse triangle */
	{ 1., -0.5},
	/* type 8b filled reverse triangle */
	{ 1., -0.5},
	/* type 9a top-half filled concave spearhead */
	{ 1., 0.5},
	/* type 9b bottom-half filled concave spearhead */
	{ 1., 0.5},
	/* type 10o top-half simple triangle */
	{ 1., 0.5},
	/* type 10f top-half filled simple triangle*/
	{ 1., 0.5},
	/* type 11o top-half concave spearhead */
	{ 1., 0.5},
	/* type 11f top-half filled concave spearhead */
	{ 1., 0.5},
	/* type 12o top-half convex spearhead */
	{ 1., -0.5},
	/* type 12f top-half filled convex spearhead */
	{ 1., -0.5},
	/* type 13a "wye" */
	{ 1., -0.5},
	/* type 13b bar */
	{ 0., 0.5},
	/* type 14a two-prong fork */
	{ 1., 0.5},
	/* type 14b backward two-prong fork */
	{ 0., 0.5}
};

/* Macros */
#define XCOORD(x)	((x) - llx)
#define YCOORD(y)	(ury - (y))
#define XDIR(x)		x
#define YDIR(y)		-(y)
#define EQUAL(p,q)	(p->x == q->x && p->y == q->y)
			/* cast to double, to not have the integers overflow */
#define LENGTH(p,q)	sqrt(((double) (q->x - p->x))*(q->x - p->x) \
			     + ((double)(q->y - p->y))*(q->y - p->y))
#define THICKNESS(T)	(T <= THICK_SCALE ? 0.5*T : T - THICK_SCALE)
			/* THICK_SCALE is of type float, see fig2dev.h */
/* #define round	(int)... see fig2dev.h */
#define PUTPOINT(p)	fprintf(tfp,"(%d,%d)", XCOORD(p->x), YCOORD(p->y))

#define	PURE_COLOR	0
#define	MITERJOIN	0
#define	BUTTCAP		0
#define	ROUNDCAP	1
#define SQUARECAP	2

static void	put_patternoval(F_point *p, F_point *q, F_line *l);

void
genpict2e_option(char opt, char *optarg)
{
    int i;

    switch (opt) {
    case 'b':			/* border margin around figure */
	border_margin = atoi(optarg);
	/* atoi() is slightly faster than sscanf(), but returns 0 if there
	 * is no int; Use atoi if the default value is 0 anyway. */
	/* sscanf(optarg,"%d",&border_margin); */
	break;

    case 'C':			/* default color */
	default_color = atoi(optarg);
	break;

    case 'e':
	epiccompatible = false;
	break;

    case 'F':
	nofontname = true;
	break;

    case 'i':	/* prepend this string to included graphics file */
	prepend = optarg;
	break;

    case 'f':			/* set default text font */
	for (i = 1; i <= MAX_FONT; ++i )
	    if (!strcmp(optarg,texfontnames[i]) || !strcmp(optarg,texfonts[i]))
		break;
	if (i <= MAX_FONT) {
	      texfonts[0] = texfonts[i];
	} else {
	    for (i = 1; i <= MAX_PSFONT; ++i )
		if (!strcmp(optarg, PSfontnames[i])) break;
	    if (i > MAX_PSFONT)
		fprintf(stderr, "warning: non-standard font name %s ignored\n",
			optarg);
	    else
		texpsfonts[0] = optarg;
	}
	break;

    case 'o':
	nofontsize = true;
	break;

    case 'T':
	usetexfonts = true;
	break;

    case 'O':
	allspecial = true;
	break;

    case 'P':
	pagemode = true;
	epiccompatible = false;
	break;

    case 'R':
	ltxarrow = atoi(optarg);
	if (ltxarrow <= 1)		/* types 0, 2, 3, etc. exist */
	    ltxarrow -= 1;
	break;

    case 'r':
	allarrowsltx = true;
	break;

    /* case 'l':			set thin/thick line threshold *
	thick_width = atoi(optarg);
	break;
    */

    case 'v':
	verbose = 1;		/* verbose mode */
	break;

    case 'w':		/* remove suffix from included graphics file */
	removesuffix = true;
	break;

    case 'E':
	sscanf(optarg,"%d",&encoding);
	if (encoding < 0 || encoding > 2)
	    encoding = 1;
	break;

    case 'G':
    case 'L':
	break;

    default:
	put_msg(Err_badarg, opt, "pict2e");
	exit(1);
    }
}

static void
set_linejoin(int j)
{
	if (j != cur_joinstyle) {
	    cur_joinstyle = j;
	    switch (j) {
	    case MITERJOIN:
		fputs("\\miterjoin%\n", tfp);
		break;
	    case 1:
		fputs("\\roundjoin%\n", tfp);
		break;
	    case 2:
		fputs("\\beveljoin%\n", tfp);
		break;
	    default:
		fprintf(stderr,"Undefined line join style %d.\n", j);
	    }
	}
}

static void
set_linecap(int j)
{
	if (j != cur_capstyle) {
	    cur_capstyle = j;
	    switch (j) {
	    case BUTTCAP:
		fputs("\\buttcap%\n", tfp);
		break;
	    case ROUNDCAP:
		fputs("\\roundcap%\n", tfp);
		break;
	    case SQUARECAP:
		fputs("\\squarecap%\n", tfp);
		break;
	    default:
		fprintf(stderr, "Undefined line cap style %d.\n", j);
	    }
	}
}

static void
set_linewidth(int w)
{
	if (w != cur_thickness) {
	    cur_thickness = w;
	    /* Set line-thickness compatible with genps.c.
	     * XFig line thickness 1 corresponds to
	     *   Imperial(Inches)	0.451 pt
	     *   Metric			0.474 pt
	     * LaTex
	     *   \thinlines		0.4 pt
	     */
	    fprintf(tfp, "\\linethickness{%g\\unitlength}",
		    THICKNESS(cur_thickness));
	    if (epiccompatible)
		fprintf(tfp, "\\XFigeepicthickness{%g\\unitlength}",
			THICKNESS(cur_thickness));
	    if (cur_thickness == THICK_SCALE)
		fputs("%\\thinlines\n", tfp);
	    else if (cur_thickness == 2*THICK_SCALE)
		fputs("%\\thicklines\n", tfp);
	    /* the % at the end is necessary, otherwise objects are shifted
	       by a space */
	    else fputs("%\n", tfp);
	}
}

static void
get_rgbcolor(int *c, RGB *rgb)
{
	if (*c < NUM_STD_COLS)
	    sscanf(Fig_color_names[*c], "#%2hx%2hx%2hx",
		   &(rgb->red), &(rgb->green), &(rgb->blue));
	else {
	    rgb->red = user_colors[*c - NUM_STD_COLS].r;
	    rgb->green = user_colors[*c - NUM_STD_COLS].g;
	    rgb->blue = user_colors[*c - NUM_STD_COLS].b;
	}
}

/*
 * Close a color scope. As a collateral, this also scopes the linethickness.
 * Therefore, save the graphics state. Graphics state is a bit of an euphemism,
 * only the line thickness must be saved and retrieved.
 *
 ****************************************************************
 *	Always call first set_color(), then set_linewidth()!	*
 ****************************************************************
 */
static void
close_scope(void)
{
	if (verbose)
	    fputs("}% close color scope, return to color of surrounding text\n",
		tfp);
	else
	    fputs("}%\n", tfp); /* put a %, otherwise pict2e puts a space */
	cur_thickness = saved_thickness;
}

static void
open_scope(void)
{
	if (verbose)
	    fputs("% open color scope\n{", tfp);
	else
	    fputs("{", tfp);
	saved_thickness = cur_thickness;
}

static void
set_color(int col)
{
	int	c;
	RGB	rgb;

	if (cur_shade == NUMSHADES - 1
	     && (col == cur_color
		 || ((col == DEFAULT || col == default_color)
			&& (cur_color == DEFAULT || cur_color == default_color)
		    )
		)
	   )
	    return;

	/* (col != cur_color || cur_shade != NUMSHADES - 1) */
	if (col == DEFAULT || col == default_color) {
	    close_scope();
	    cur_color = DEFAULT;
	    cur_shade = NUMSHADES - 1;
	    return;
	} else if (cur_color == DEFAULT || cur_color == default_color) {
	    open_scope();
	}

	cur_color = col;
	cur_shade = NUMSHADES - 1;

	if (col == DEFAULT)
	    c = default_color;
	else
	    c = col;

	switch (c) {
	case BLACK_COLOR:
	    fputs("\\color{black}\n", tfp);
	    break;
	case 1:
	    fputs("\\color{blue}\n", tfp);
	    break;
	case 2:
	    fputs("\\color{green}\n", tfp);
	    break;
	case 3:
	    fputs("\\color{cyan}\n", tfp);
	    break;
	case 4:
	    fputs("\\color{red}\n", tfp);
	    break;
	case 5:
	    fputs("\\color{magenta}\n", tfp);
	    break;
	case 6:
	    fputs("\\color{yellow}\n", tfp);
	    break;
	case WHITE_COLOR:
	    fputs("\\color{white}\n", tfp);
	    break;
	default:
	    get_rgbcolor(&c,&rgb);
	    fprintf(tfp, "\\color[rgb]{%.3g,%.3g,%.3g}\n",
		    rgb.red/255., rgb.green/255., rgb.blue/255.);
	}
}

static void
set_fillcolor(int col, int shade, int *pen_color)
{
	double	red, green, blue;
	RGB	rgb;
	/* A shade between 0 and NUMSHADES - 1 mixes the color with black,
	 * 0 = black, NUMSHADES - 1 = color at full saturation. Shades >
	 * NUMSHADE - 1 mix the color with white, i.e., tint the color.
	 * White and black have the tints and shades mapped to shades and tints,
	 * respectively.
	 */

	if (shade < 0)
	    fprintf(stderr,
		    "A color error occurred. Please report this bug.\n");

	if (shade >= NUMSHADES + NUMTINTS) {
	    if (col == *pen_color) {	/* solid fill */
		shade = NUMSHADES - 1;
	    } else {
		fputs("Patterns not supported. Filling with 25% pen color instead.\n",
			stderr);
		col = *pen_color;
		shade = NUMSHADES - 1 + 3 * NUMTINTS / 4;
	    }
	}

	/* pure colors */
	if (shade == NUMSHADES - 1) {
	    set_color(col);
	    cur_shade = shade;
	    return;
	}

	/* an unknown color can not be shaded or tinted */
	if (col == DEFAULT) {
	    if (default_color == DEFAULT)
		col = BLACK_COLOR;
	    else
		col = default_color;
	}

	/* black */
	if ((shade == 0 && col != BLACK_COLOR)
		|| (col == WHITE_COLOR && shade == NUMSHADES + NUMTINTS -1)) {
	    set_color(BLACK_COLOR);
	    cur_shade = NUMSHADES - 1;
	    return;
	}

	/* white */
	if ((shade == NUMSHADES + NUMTINTS - 1 && col != WHITE_COLOR)
		 || (col == BLACK_COLOR && shade == 0)) {
	    set_color(WHITE_COLOR);
	    cur_shade = NUMSHADES - 1;
	    return;
	}

	/* map shades to tints for black and tints to shades for white
	 *   white .... black .... white
	 *              white .... black
	 * to
	 *   black .... white
	 */
	if (col == BLACK_COLOR) {
	    col = WHITE_COLOR;
	    if (shade > NUMSHADES - 1)
		shade -= NUMSHADES - 1;
	    else /* shade < NUMSHADES - 1 */
		shade = NUMSHADES - 1 - shade;
	}

	if (cur_color == col && cur_shade == shade)
	    return;

	if ((cur_color == DEFAULT || cur_color == default_color)
		&& cur_shade == NUMSHADES - 1)
	    open_scope();

	/* grays */
	if (col == WHITE_COLOR) {
	    cur_color = col;
	    cur_shade = shade;
	    fprintf(tfp,"\\color[gray]{%.3g}\n", (double)shade/(NUMSHADES-1));
	    return;
	}

	/* shaded and tinted colors */
	cur_color = col;
	cur_shade = shade;
	get_rgbcolor(&col,&rgb);
							/* 4080 = 255 << 4 */
#define	SHADE(c,t)	(double)(c<<4)*t / (NUMSHADES-1) / 4080.
#define	TINT(c,t)	((c<<4) + ((double)((255-c)<<4) * (t-NUMSHADES+1) \
							/ NUMTINTS)) / 4080.
	if (shade < NUMSHADES) {
	    red = SHADE(rgb.red, shade);
	    green = SHADE(rgb.green, shade);
	    blue = SHADE(rgb.blue, shade);
	} else {
	    red = TINT(rgb.red, shade);
	    green = TINT(rgb.green, shade);
	    blue = TINT(rgb.blue, shade);
	}

	fprintf(tfp,"\\color[rgb]{%.3g,%.3g,%.3g}\n", red, green, blue);
}

/* static bool
colors_used(void)
{
	int i;
	for (i = 0; i < NUM_STD_COLS; ++i)
	    if (std_color_used[i] == true && i != default_color)
		return true;
	return false;
}
*/

void
genpict2e_start(F_compound *objects)
{
	texfontsizes[0] = texfontsizes[1]
	    = TEXFONTSIZE(font_size != 0.0? font_size : DEFAULT_FONT_SIZE);

	unitlength = mag/ppi;
	border_margin /= unitlength*72.0;

	/* adjust for any border margin */
	llx -= border_margin;
	lly -= border_margin;
	urx += border_margin;
	ury += border_margin;

	/* print any whole-figure comments prefixed with "%" */
	if (objects->comments) {
	    fputs("%\n", tfp);
	    print_comments("% ", objects->comments, "");
	    fputs("%\n", tfp);
	}
	if (pagemode) {
	    double	width, height;
	    char	unit[] = "in";

	    width = (urx - llx) * unitlength;
	    height = (ury - lly) * unitlength;
	    if (metric) {
		width *= 2.54;
		height *= 2.54;
		strcpy(unit,"cm");
	    }

	    fputs("\\documentclass{minimal}\n", tfp);
	    fprintf(tfp,
		"\\usepackage[papersize={%.4g%s,%.4g%s},margin=0pt]{geometry}\n",
		width, unit, height, unit);
	    fputs("\\usepackage{pict2e,graphics,color}\n", tfp);
	    /* Unconditionally include color.sty, because shaded black or
	     * tinted white needs it.
		if (num_usr_cols > 0 || colors_used())
		fputs(",color", tfp);
	     */
	    fputs("\\parindent0pt\n\\begin{document}\n", tfp);
	}

	/* round() is a macro that maps to int, see fig2dev.h */
	fprintf(tfp, "\\unitlength%lisp", (long) (4736286.72*unitlength + 0.5));
	if (metric)
	    fputs("% 4143.7 sp = (1/472.44) cm\n", tfp);
	else
	    fputs("% 3946.9 sp = (1/1200) in\n", tfp);

#ifdef SCALE_PICT2E
	if (!pagemode) {
	    fputs("\\ifx\\XFigheight\\undefined\\else\\ifdim\\XFigheight>0pt\n",
		tfp);
	    fprintf(tfp,
		"\\unitlength\\XFigheight\\divide\\unitlength by %d\\fi\\fi\n",
		ury - lly);
	    fputs("\\ifx\\XFigwidth\\undefined\\else\\ifdim\\XFigwidth>0pt\n",
		tfp);
	    fprintf(tfp,
		"\\unitlength\\XFigwidth\\divide\\unitlength by %d\\fi\\fi\n",
		 urx-llx);
	}
#endif

	fprintf(tfp, "\\begin{picture}(%d,%d)%%(0,0)\n",
					 urx-llx, ury-lly);/*, llx, lly); */
	if (epiccompatible)
	    /* \allinethickness is only defined in eepic.sty, not epic.sty. */
	    fputs("\\ifx\\allinethickness\\undefined\n"
		  "  \\def\\XFigeepicthickness#1{\\relax}\n\\else\n"
		  "  \\let\\XFigeepicthickness\\allinethickness\n\\fi\n", tfp);
}

int
genpict2e_end(void)
{
	/* close probably open color scope */
	set_color(DEFAULT);
	/* linecaps and -join run over } and \end{picture}, reset to default */
	set_linecap(BUTTCAP);
	set_linejoin(MITERJOIN);
	fputs("\\end{picture}%\n", tfp);
	if (pagemode)
	    fputs("\\end{document}", tfp);

	return 0;
}

/*
 * Set the pattern for non-solid lines.
 * For dotted lines, add an offset equal to the spacing between dots to h1.
 */
static void
set_linestyle(
	int *s,			/* l->style */
	double *v,		/* l->style_val */
	struct pattern *pattern,
	double *h1		/* offset */)
{
	int i;

	*v /= 80.0 / ppi;
	if (*v <= 0.) {
	    fputs("Error: Set_linestyle with zero frequency called. "
		  "Please report this bug\n", tfp);
	    return;
	}

	if (*s == DASH_LINE) {
	    pattern->d[0] = round(*v);
	    pattern->d[1] = pattern->d[0];
	    pattern->nd = 2;
	} else if (*s == DOTTED_LINE) {
	    pattern->d[0] = round(ppi/80.);
	    pattern->d[1] = round(*v);
	    *h1 += (double) pattern->d[1];
	    pattern->nd = 2;
	} else if (*s == DASH_DOT_LINE) {
	    pattern->d[0] = round(*v);
	    pattern->d[1] = round(*v*0.5);
	    pattern->d[2] = round(ppi/80.);
	    pattern->d[3] = pattern->d[1];
	    pattern->nd = 4;
	} else if (*s == DASH_2_DOTS_LINE) {
	    pattern->d[0] = round(*v);
	    pattern->d[1] = round(*v*0.45);
	    pattern->d[2] = round(ppi/80.0);
	    pattern->d[3] = round(*v*0.333);
	    pattern->d[4] = pattern->d[2];
	    pattern->d[5] = pattern->d[1];
	    pattern->nd = 6;
	} else if (*s == DASH_3_DOTS_LINE) {
	    pattern->d[0] = round(*v);
	    pattern->d[1] = round(*v*0.4);
	    pattern->d[2] = round(ppi/80.0);
	    pattern->d[3] = round(*v*0.3);
	    pattern->d[4] = pattern->d[2];
	    pattern->d[5] = pattern->d[3];
	    pattern->d[6] = pattern->d[2];
	    pattern->d[7] = pattern->d[1];
	    pattern->nd = 8;
	}
	pattern->length = 0;
	for (i = 0; i < pattern->nd ; ++i) pattern->length += pattern->d[i];
}

/*
 * Write all points in a line, except the last. Return a pointer to the last point.
 * Does not write the terminating newline.
 */
static F_point *
put_points(char *type,		/* "\\polygon" or "\\polygon*" */
	   F_point *p)
{
	int	chars;
#define	LINEBREAK	76

	chars = fprintf(tfp, "%s", type);

	while (p->next != NULL) {
	    if (chars >= LINEBREAK) {
		fprintf(tfp,"\n");
		chars = 0;
	    }
	    chars += fprintf(tfp,"(%d,%d)", XCOORD(p->x), YCOORD(p->y));
	    p = p->next;
	}
	return p;
}

/*
 * Write a polyline. Return the penultimate point.
 */
static F_point *
put_polyline(F_point *p)
{
	int	chars;
	F_point	*q;

	if (p->next == NULL) {
	    fputs("Not enough points in the line, strange...\n", stderr);
	    return p;
	}

	chars = fputs("\\polyline", tfp);
	while (p->next != NULL) {
	    if (chars >= LINEBREAK) {
		fprintf(tfp,"\n");
		chars = 0;
	    }
	    chars += fprintf(tfp,"(%d,%d)", XCOORD(p->x), YCOORD(p->y));
	    q = p;
	    p = p->next;
	}
	fprintf(tfp,"(%d,%d)\n", XCOORD(p->x), YCOORD(p->y));
	return q;
}

/*
 * Compute greatest common divisor, assuming 0 < a <= b.
 * Copied (and modified slightly) from latex_line.c.
 */
static int
gcd(int a, int b)
{
	b = b % a;
	return b ? gcd(b, a) : a;
}

/*
 * Return the slope (sx, sy) and length lx between points p and q.
 */
static void
get_slope(F_point *p, F_point *q, int *sx, int *sy, int *lx)
{
	int	div, ax, ay;

	*sx = q->x - p->x;
	*sy = q->y - p->y;

	if (*sx == 0) {
	    if (*sy > 0) {
		*lx = *sy;
		*sy = 1;
	    } else {
		*lx = - *sy;
		*sy = -1;
	    }
	    return;
	}
	if (*sy == 0) {
	    if (*sx > 0) {
		*lx = *sx;
		*sx = 1;
	    } else {
		*lx = - *sx;
		*sx = -1;
	    }
	    return;
	}

	/* dx && dy */
	ax = abs(*sx);
	ay = abs(*sy);
	*lx = ax;
	div = (ax >= ay) ? gcd(ay,ax) : gcd(ax,ay);
	*sx /= div;
	*sy /= div;
}

/*
 * Compute the slope of a line between points p and q. Return the slope (sx,
 * sy), the length lx and the necessary precision precl to print the length.
 * The slope arguments should be integer numbers with an absolute value smaller
 * than 16384. Integer value, because eepic sets, e.g., with
 * \multiput(167,2574)(229.87,-69){28}{\line(1000,-300.16){115}},
 * the letters .16 at 28 locations.
 */
static void
get_lineslope(F_point *p, F_point *q, int *sx, int *sy, int *precl, double *lx)
{
	int	ax, ay;
	double	fac;

	get_slope(p, q, sx, sy, &ax); /* re-use ax as tmp integer */
	*lx = (double) ax;
	*precl = 0;
	ax = abs(*sx);
	ay = abs(*sy);
	if (ax < 16384 && ay < 16384)
	    return;

	/* TODO: search points with valid slopes in the immediate vicinity? */

	if (ax > ay) {
	    fac = 16383. / ax;
	    *sx = *sx > 0 ? 16383 : -16383;
	    *sy = round(*sy * fac);
	} else {
	    int digits;

	    fac = 16383. / ay;
	    *sy = *sy > 0 ? 16383 : -16383;
	    *sx = round(*sx * fac);
	    if (abs(*sx) < 3) {
		*lx = (double) abs(q->y - p->y);
		*sy = *sy > 0 ? 1 : -1;
		*sx = 0;
	    }

	    /* for a steep line, small lx, the length in y-direction shall stay
	     * the same, the length in x-direction may be modified by rounding */
	    fac  = fabs((double) *sy/ *sx);
	    *lx = abs(q->y - p->y) / fac;
	    ax = (int) fac;

	    for (digits = 1; *precl < 5 && digits < ax; digits *= 10)
		++(*precl);
	}
}

/*
 * Compute the slope of a vector.
 * Input: Start point p, end point q.
 * Output: slope (sx, sy), length lx.
 * If a slope with both slope arguments smaller than 1000 is not found, return
 * true and scale the arguments to 1000, round(arg). Return false on success.
 */
static bool
get_vectorslope(F_point *p, F_point *q, int *sx, int *sy, int *lx)
{
	int	ax, ay;

	get_slope(p, q, sx, sy, lx);

	ax = abs(*sx);
	ay = abs(*sy);
	if (ax > 1000 || ay > 1000) {
	    if (ax > ay) {
		*sy = round(*sy * 1000.0 / ax);
		*sx = *sx > 0 ? 1000 : -1000;
	    } else {
		*sx = round(*sx * 1000.0 / ay);
		*sy = *sy > 0 ? 1000 : -1000;
	    }
	    return true;
	}
	return false;
}

/*
 * Draw a line with a dash pattern, starting an offset h1 from point p.
 * If h1 is negative, (-h1) gives the offset into the dash number dstart.
 * After a call to put_patternline(), p and q point
 * to the penultimate and the ultimate point of the line.
 *   Warning: Terrible code ahead.
 */
static void
put_patternline(F_point *p, F_point *q, struct pattern *pattern, double h1,
		int dstart)
{
	int	i, j, numpatterns, dadd, precx, precy, din;
	int	dpl[PAT_ND_2];
	double	len, lenpq, dx, dy, cosl, sinl, digits, dlx[PAT_ND_2];
	F_pos	pstart, slope[PAT_ND_2];

	/* put a remaining dash */
	if (h1 < 0) {
	    len = pattern->d[dstart] + h1; /* the remaining length of the dash */
	    while ((lenpq = LENGTH(p,q)) <= len) {
		if (q->next == NULL)
		    return;
		len -= lenpq;
		p = q;
		q = q->next;
		PUTPOINT(p);
	    }
	    /* Now the length of the line is longer than the remaining dash length */
	    cosl = (q->x - p->x)/lenpq;
	    sinl = (q->y - p->y)/lenpq;
	    fprintf(tfp,"(%d,%d)\n", XCOORD(p->x + round(cosl*len)),
		    YCOORD(p->y + round(sinl*len)));
	    /* the new offset     x---           ---
	     *                    len d[start+1] |<-- offset to here
	     */
	    h1 = len + pattern->d[dstart+1];
	    dstart = dstart==pattern->nd - 2 ? 0: dstart+2;
	}
	/* there may be several line segments within h1
	 *  x--x-x---x--------------------------x
	 *  |offset|
	 * wind forward through the points which lie within the offset
	 */
	while ((lenpq = LENGTH(p,q)) <= h1) {
	    if (q->next == NULL) return;
	    h1 -= lenpq;
	    p = q;
	    q = q->next;
	}

	/* calculate the number of dash patterns
	 * ndp - the number of full dash patterns, that fit into this line segment */
	/* if (ndp > 1) --- well, do something nice for ndp == 1 */
	numpatterns = floor((lenpq-h1)/pattern->length);
	cosl = (q->x - p->x)/lenpq;
	sinl = (q->y - p->y)/lenpq;
	if (numpatterns > 0) {
	    F_point	o = {0,0,NULL}, a;
	    /* calculate the necessary precision */
	    dx = pattern->length*cosl;
	    dy = pattern->length*sinl;
	    /* round() is #def'd in fig2dev.h, casts its arg to int.
	     * do manually round here, the arg is always positive */
	    /* dx*numpatterns - round(dx*numpatterns*digits)/digits < 0.5 */
	    len = fabs(dx);	/* use len as temporary variable */
	    precx = 0;
	    for (digits = 1.; precx < 5
		 && fabs(len - floor(len*digits+0.5)/digits) >= 0.5/numpatterns;
		 digits *= 10.)
		++precx;
	    len = fabs(dy);
	    precy = 0;
	    for (digits = 1.; precy < 5
		 && fabs(len - floor(len*digits+0.5)/digits) >= 0.5/numpatterns;
		 digits *= 10.)
		++precy;

	    for (i = 0; i < pattern->nd/2; ++i) {
		a.x = round(cosl*pattern->d[2*i]);
		a.y = round(sinl*pattern->d[2*i]);
		get_lineslope(&o, &a, &slope[i].x, &slope[i].y, &dpl[i], &dlx[i]);
	    }
	}

	pstart.x = p->x + round(cosl*h1);
	pstart.y = p->y + round(sinl*h1);
	/* re-use len, check if single dashes fit into the remaining line */
	len = lenpq - numpatterns*pattern->length - h1;
	/* the dash pattern:
	 *		     d[0]  d[1] d[2] 3  d[4] 5   d[6]    d[7];  nd = 8;
	 *		   -------     -----   ----    --------      |
	 */
	dadd = 0; /* the number of additional dashes that fit into the line segment */
	i = dstart;
	while (len >= pattern->d[i]) {
	    len -= pattern->d[i] + pattern->d[i+1];
	    i =  i == pattern->nd - 2 ? 0 : i + 2;
	    ++dadd;
	}
	/*	d[dstart]  d[..+1]  ...   d[dstart+dadd]   d[i]
	 *	--------     ---     ---   ----------     ----X---  (len > 0)
	 *	                                       X  ----      (len > 0)
	 * Now dadd is the number of dashes, starting from dstart, that also fit
	 * into the segment. i is the index of the first dash that does not fit
	 * fully  on the line any more. If len > 0, a part of a dash is to be
	 * put into the remaining line; otherwise, an empty space
	 * for numpatterns == 0, dadd is the number of dash lines to put */

	din = 0;	/* the cumulated length into the dash pattern */
	j = 1;		/* count up the dashes */
	/* Put the additional dadd dashes */
	if (numpatterns == 0) {
	    for (i = dstart; j <= dadd; i = i==pattern->nd-2 ? 0 : i+2, ++j) {
		fprintf(tfp,"\\Line(%d,%d)(%d,%d)\n",
			XCOORD(pstart.x+round(din*cosl)),
			YCOORD(pstart.y+round(din*sinl)),
			XCOORD(pstart.x+round((din+pattern->d[i])*cosl)),
			YCOORD(pstart.y+round((din+pattern->d[i])*sinl)));
		din += pattern->d[i] + pattern->d[i+1];
	    }
	    dstart = i;	/* dstart for the next line segment */
	} else { /* numpatterns >= 1, at least 2 times the additional dashes */
	    for (i = dstart; j <= dadd; i = i==pattern->nd-2 ? 0 : i+2, ++j) {
		fprintf(tfp,"\\multiput(%d,%d)(%.*f,%.*f){%d}{\\line(%d,%d){%.*f}}\n",
			XCOORD(pstart.x+round(din*cosl)),
			YCOORD(pstart.y+round(din*sinl)),
			precx, XDIR(dx), precy, YDIR(dy),
			numpatterns + 1, XDIR(slope[i/2].x), YDIR(slope[i/2].y),
			dpl[i/2], dlx[i/2]);
		din += pattern->d[i] + pattern->d[i+1];
	    }
	    dstart = i;	/* dstart for the next line segment */
	    /* j = dadd + 1; i is the index od d[(dstart+dadd+1)%nd] */
	    /* Put the remaining dashes, those from dstart+dadd+1 until
	     * (dstart+nd/2) % nd, numpatterns times. */
	    if (numpatterns == 1) {
		for ( ; j <= pattern->nd/2; i = i==pattern->nd-2 ? 0 : i+2, ++j) {
		    fprintf(tfp,"\\Line(%d,%d)(%d,%d)\n",
			    XCOORD(pstart.x+round(din*cosl)),
			    YCOORD(pstart.y+round(din*sinl)),
			    XCOORD(pstart.x+round((din+pattern->d[i])*cosl)),
			    YCOORD(pstart.y+round((din+pattern->d[i])*sinl)));
		    din += pattern->d[i] + pattern->d[i+1];
		}
	    } else { /* numpatterns >= 1 */
		for ( ; j <= pattern->nd/2; i = i==pattern->nd-2 ? 0 : i+2, ++j) {
		    fprintf(tfp,"\\multiput(%d,%d)(%.*f,%.*f){%d}{\\line(%d,%d){%.*f}}\n",
			    XCOORD(pstart.x+round(din*cosl)),
			    YCOORD(pstart.y+round(din*sinl)),
			    precx, XDIR(dx), precy, YDIR(dy),
			    numpatterns, XDIR(slope[i/2].x), YDIR(slope[i/2].y),
			    dpl[i/2], dlx[i/2]);
		    din += pattern->d[i] + pattern->d[i+1];
		}
	    }
	} /* end numpatterns >= 1 */
	/* j is the index of the last put dash */

	/* For len > 0, put the inital length len of the last, incomplete dash
	 * len > 0:
	 *		----------        -----x-----
	 *		                  |len |
	 * For len < 0, the offset h1 for the next line segment is -len
	 * len <= 0:
	 *		----------        ---------     x    ----
	 *		                                |-len|
	 */

	if (q->next == NULL) {
	    if (len > 0) fprintf(tfp,"\\Line(%d,%d)(%d,%d)\n",
				 XCOORD(q->x - round(cosl*len)),
				 YCOORD(q->y - round(sinl*len)),
				 XCOORD(q->x), YCOORD(q->y));
	} else {
	    if (len > 0) fprintf(tfp,"\\polyline(%d,%d)(%d,%d)",
				 XCOORD(q->x - round(cosl*len)),
				 YCOORD(q->y - round(sinl*len)),
				 XCOORD(q->x), YCOORD(q->y));
	    put_patternline(q,q->next,pattern,-len,dstart);
	}
}

static void
put_pointarray(F_pos pts[], int *npoints)
{
	int	i;
	int	chars = 9;	/* \polygon, \polygon* or \polyline is already
				 * printed on the first line */

	for (i=0; i < *npoints; ++i) {
	    if (chars >= LINEBREAK) {
		fputc('\n', tfp);
		chars = 0;
	    }
	    chars += fprintf(tfp, "(%d,%d)", XCOORD(pts[i].x),YCOORD(pts[i].y));
	}
	fputc('\n', tfp);
}

/* Put an arrow, from p to q. */
static void
put_arrow(F_point *p, F_point *q, F_arrow *a, int linethick)
{
	int	sx, sy, lx;
	F_pos	points[50], fillpoints[50], clippts[50];
	int	npoints, nfillpoints, nclippts;

#define	ISLTXARROW(a)	(allarrowsltx || ltxarrow == 2*a->type + a->style)
	if (ISLTXARROW(a)) {
	    /* the size of latex-vectors is specified by arrow->thickness */
	    if (a->thickness <= 0.) return;
	    set_linewidth(round(a->thickness));
	    get_vectorslope(p, q, &sx, &sy, &lx);
	    fprintf(tfp,"\\put(%d,%d){\\vector(%d,%d){0}}%%\n",
		    XCOORD(q->x), YCOORD(q->y), XDIR(sx), YDIR(sy));
	    return;
	}

	/* all other arrows */
	calc_arrow(p->x, p->y, q->x, q->y, linethick, a, points, &npoints,
		   fillpoints, &nfillpoints, clippts, &nclippts);
	/* reset line-style outside of put_arrow */

	/* fill filled arrows */
	if ((a->style || nfillpoints) && a->type < 13) {
	    fputs("\\polygon*", tfp);
	    if (nfillpoints == 0) {
		/* for a simple fill, the first and the last point coincide */
		/* ... except for a half circle */
		nfillpoints = a->type == 6 ? npoints : npoints - 1;
		put_pointarray(points, &nfillpoints);
	    } else {
		put_pointarray(fillpoints, &nfillpoints);
	    }
	}

	if (round(0.5 * a->thickness) == 0) return;
	set_linewidth(round(a->thickness));
	set_linejoin(MITERJOIN);
	set_linecap(BUTTCAP);

	if (points[0].x == points[npoints-1].x && points[0].y == points[npoints-1].y) {
	    npoints -= 1;
	    fputs("\\polygon", tfp);
	} else {
	    fputs("\\polyline", tfp);
	}
	put_pointarray(points, &npoints);
}

/*
 * Draw either an filled arc box, or an arc box with solid lines.
 */
static void
put_oval(
	F_point *p,		/* two points at an diagonal */
	F_point *q,
	int rad,		/* arc radius */
	char *c)		/* "strokepath" or "fillpath" */
{
	int	x1, x2, y1, y2, a, dx, dy, dir;

	dx = q->x - p->x;
	dy = q->y - p->y;
	if (MIN(abs(dx), abs(dy)) < 2*rad )
	    rad = MIN(abs(dx), abs(dy))/2;

	if (!epiccompatible && c[0] == 's') {
	    double cx, cy;
	    cx = (p->x + q->x) / 2.;
	    cy = (p->y + q->y) / 2.;
	    fprintf(tfp, "\\put(%.*f,%.*f){\\oval[%d](%d,%d)}\n",
		    cx == floor(cx) ? 0 : 1, XCOORD(cx),
		    cy == floor(cy) ? 0 : 1, YCOORD(cy), rad, abs(dx), abs(dy));
	    return;
	}

	/* epiccompatible */
	dx = XDIR(dx > 0 ? 1: -1);
	dy = YDIR(dy > 0 ? 1: -1);
	dir = dx*dy;
	x1 = XCOORD(p->x) + dx*rad;
	y1 = YCOORD(p->y) + dy*rad;
	x2 = XCOORD(q->x) - dx*rad;
	y2 = YCOORD(q->y) - dy*rad;
	a = dx < 0 ? 0 : 2;
	fprintf(tfp,"\\circlearc[1]{%d}{%d}{%d}{%d}{%d}",
		    x1, y1, rad, a*90, (a+dir)*90);
	a += dir;
	fprintf(tfp,"\\circlearc{%d}{%d}{%d}{%d}{%d}%%\n",
		    x2, y1, rad, a*90, (a+dir)*90);
	a += dir;
	fprintf(tfp,"\\circlearc{%d}{%d}{%d}{%d}{%d}",
		    x2, y2, rad, a*90, (a+dir)*90);
	a += dir;
	fprintf(tfp,"\\circlearc{%d}{%d}{%d}{%d}{%d}\\closepath\\%s\n",
		    x1, y2, rad, a*90, (a+dir)*90, c);
}

/*
 * The length of a latex-arrow, with an arrow->thickness t.
 */
static double
ltx_offset(double t)
{
	/* dimensions of the latex-arrow, see page 25 in pict2e.pdf,
	 *	wid == 3.2*linethickness + 1.5pt, 72.27 pt = 72 postscript point
	 *	ht  == 1.52*wid */
	/* 105*unitlength = 1.5*70*mag/ppi; with 70 h1 stays inside the arrow */
	t = THICKNESS(t);
	return 1.52*(3.2*t + 105.*unitlength);
}

/*
 * Get the length by which a line should be shortened if there is an arrow.
 * Returns 0.0 if there is no arrow, a == NULL. May also return 0.0 if the arrow
 * does not need to be drawn, i.e., an unfilled arrow with line thickness zero.
 */
static double
get_offset(F_arrow *a, int thickness, int capstyle)
{
	double	h;
	if (!a) return 0.;
	/* see line 173 in bound.c for the index into the arrow-array */
			/*  && proportion-check? */
	if (ISLTXARROW(a)) {
	    h = ltx_offset(a->thickness);
	} else {
	    int		indx;
	    double	thk;

	    /* code from line 923 in bound.c */
	    indx = 2*a->type + a->style;
	    h = arrow_shapes[indx].tipmv;		/* bound.h */
	    thk = THICKNESS(a->thickness);
	    if (h > 0.0)
		h = thk * sqrt(a->wid*a->wid + h*h*a->ht*a->ht) / 2.0 / a->wid;
	    else if (h == 0.0)
		h = thk / 2.0;	/* types which have blunt end */
	    else /* tipmv == -1, the tip is not moved */
		h = 0.0;
	    /* add the additional line_move */
	    h += a->ht*pict2earrow[indx].hfac + thk*pict2earrow[indx].tfac;
	    /* rounding */
	    if (pict2earrow[indx].tfac > 0.0)
		h -= 0.5;
	    else if (pict2earrow[indx].tfac < 0.0)
		h += 0.5;
	}

	if (capstyle == SQUARECAP)
	    h += THICKNESS(thickness)*0.5;

	return h;
}

/*
 * Compute the point a which lies a distance h from p on the line from p to q.
 * Return true if the line is too short, false on success.
 *	p         a            q
 *	+---------X------------+
 *	|<-- h -->|
 */
static bool
get_midpoint(F_point *p, F_point *q, F_point *a, double *h)
{
	double sx, sy, s;

	sx = q->x - p->x;
	sy = q->y - p->y;
	s = sqrt(sx*sx + sy*sy);

	if (s > *h) {
	    a->x = p->x + round(sx*(*h)/s);
	    a->y = p->y + round(sy*(*h)/s);
	    return false;
	} else {
	    return true;
	}
}

/*
 * Compute a point a located a distance h1 from p.
 * Return bool true if the line is too short, false otherwise.
 * In addition, if the line is too short, return the final two points.
 * Only call get_startpoint with h1 > 0.
 */
static bool
get_startpoint(
	F_point	*p,	/* first point of the initial line */
	F_point	*a,	/* start to stroke from here, a for alpha */
	F_point	*f[],	/* final two points, if too_short */
	double	h1)
{
	/* Plus-signs are existing points, X is calculated point a.
	 *
	 *				or too_short:
	 *	+-----+------+--X-----+--             +-----+----+---+
	 *	p    t->next-^  a                     p        f[0] f[1]
	 *	|<----- h1 ---->|                     |<-----  h1  ----->|
	 */
	double	sx, sy, s;

	while (p->next != NULL && (sx = p->next->x - p->x,
				   sy = p->next->y - p->y,
				   s = sqrt(sx*sx + sy*sy),
	       s <= h1) ) {
	    h1 -= s;
	    f[0] = p;
	    p = p->next;
	    f[1] = p;
	}
	if (p->next == NULL)	/* end reached - the line is shorter than h1 */
	    return true;

	/* now h1 < s */
	a->x = p->x + round(h1 * sx / s);
	a->y = p->y + round(h1 * sy / s);
	a->next = p->next;
	return false;
}

/*
 * Insert an end point located an offset h2 from the end of the line; Also,
 * return the last two points of the original line, f[0] and f[1]. If the line
 * is too short, return true, otherwise return false and let t[0] and t[1] point
 * to those points necessary to restore the original point sequence.
 * Only call insert_endpoint() with p->next != NULL.
 * To restore the original point sequence, do
 *	t[0] = NULL;	insert_endpoint(...);
 *	if (t[0]) t[0]->next = t[1];
 */
static bool
insert_endpoint(
	F_point	*p,	/* first point */
	F_point	*o,	/* end point, omega, finish to stroke here */
	F_point	*f[2],	/* final points*/
	F_point	*t[2],	/* restore original point sequence*/
	double	h2)
{
	/* Plus-signs are existing points, X is the calculated point o.
	 *
	 *	-----+----------+-----X--------+--- -+----+
	 *	               t[0]   o       t[1]  f[0] f[1]
	 *	                      |<------- h2 ------>|
	 */

	double	sx, sy, s;
	int	i = 0, n = 0;
#define	MAXREVERSE	100
	F_point	*r[MAXREVERSE+1];

	/* A simpler solution is to walk once through the line, recording the
	 * length, and walking a second time through the line to set the
	 * endpoint. Conceptually, but probably not practically, that could be
	 * more inaccurate, though.
	 */

	/* save the line points into the r-array; cycle around, if necessary */
	r[i] = p;
	while (p->next != NULL) {
	    if (++i == MAXREVERSE+1) {
		i = 1;
		r[0] = r[MAXREVERSE]; /* needed below */
		n = MAXREVERSE;
	    }
	    p = p->next;
	    r[i] = p;
	}

	if (!n) n = i+1;

	/* assign the last and next-to-last point */
	f[0] = r[i-1];
	f[1] = r[i];

	/* now walk back through the r-array */
	while (n > 1 && (i == 0 ? i = MAXREVERSE: i,
			 sx = r[i-1]->x - r[i]->x,
			 sy = r[i-1]->y - r[i]->y,
			 s = sqrt((double)sx*sx + (double)sy*sy),
			 s <= h2) ) {
	    --n;
	    --i;
	    h2 -= s;
	}
	/* either, the line is shorter than h2, there are more than MAXREVERSE
	 * points within h2, or h2 < s */
	if (n > 1 ) { /* h2 < s */
	    o->x = r[i]->x + round(h2 * sx / s);
	    o->y = r[i]->y + round(h2 * sy / s);
	    r[i-1]->next = o;
	    o->next = NULL;
	    /* store the original line sequence */
	    t[0] = r[i-1];
	    t[1] = r[i];
	} else if (i == 0 && r[0] != r[MAXREVERSE]) { /* the line is too short.
	    * After the first cycle, r[0] == r[MAXREVERSE], hence there were
	    * more points. TODO - check that? */
	    return true;
	} else { /* may occur very rarely, more than MAXREVERSE points within h2.
		  * Return the point farthest away from u */
	    o = r[i];
	    o->next = NULL;
	    t[0] = o;
	    t[1] = r[i]->next;
	}

	return false;
}

/*
 * Draw a latex-vector from p to q, or a latex-arrow and probably a line.
 * Return false for a vector, true if an arrow is drawn.
 * Only return the vector-slope between p and q if true.
 */
static bool
put_vector(F_point *p, F_point *q, F_arrow *backarrow, int *thickness,
		int *capstyle, int *sx, int *sy)
{
	bool too_short = false;
	int	lx;
	double	h;
	F_point	a, o;

	if (backarrow && (h = get_offset(backarrow, *thickness, *capstyle)) > 0.5)
	    too_short = get_midpoint(p, q, &a, &h);
	else
	    a = *p;

#define	PUTVECTOR(p,sx,sy,l)	fprintf(tfp, \
					"\\put(%d,%d){\\vector(%d,%d){%d}}\n", \
					XCOORD(p->x), YCOORD(p->y), \
					XDIR(sx), YDIR(sy), l)
#define	PUTLINE(a,o)	fprintf(tfp,"\\Line(%d,%d)(%d,%d)\n", \
				XCOORD(a.x),YCOORD(a.y),XCOORD(o.x),YCOORD(o.y))
	if (!too_short && !get_vectorslope(&a, q, sx, sy, &lx)) {
	    fprintf(tfp, "\\put(%d,%d){\\vector(%d,%d){%d}}\n",
		    XCOORD(a.x), YCOORD(a.y), XDIR(*sx), YDIR(*sy), lx);
	    return false;
	} else {
	    if (!too_short && (h = ltx_offset((double) *thickness))
			   && !get_midpoint(q, &a, &o, &h))
		PUTLINE(a, o);
	    get_vectorslope(p, q, sx, sy, &lx);
	    PUTVECTOR(q, *sx, *sy, 0);
	    return true;
	}
}

static void
put_poly_or_patternline(F_point *p, F_point *q, F_line *l)
{
	bool too_short;
	double	h;
	F_point	a, o;
	F_point	*f[2];		/* final two points, to draw a forward arrow */
	F_point	*t[2];		/* pointers for insert_endpoint */
	struct pattern	pattern;

	/* get the start point, if there is a line */
	if (l->thickness > 0 && l-> back_arrow
			     && (h = get_offset(l->back_arrow, l->thickness,
						l->cap_style)) > 0.5) {
	    /* Returns f, if too_short */
	    too_short = get_startpoint(p, &a, f, h);
	} else {
	    a = *p;
	    too_short = false;
	}

	if (!too_short) {
	    /* insert the end point for drawing a line; get the final two points
	     * for drawing the forward arrow */
	    t[0] = NULL;
	    if (l->for_arrow) {
		h = get_offset(l->for_arrow, l->thickness, l->cap_style);
		if (l->thickness == 0 || h <= 0.5) {
		    /* simply wind forward through the line */
		    f[1] = q;
		    while (f[1]->next != NULL) {
			f[0] = f[1];
			f[1] = f[1]->next;
		    }
		} else {
		    insert_endpoint(&a, &o, f, t, h);
		}
	    }

	    /* Draw the line */
	    set_linewidth(l->thickness);
	    set_linecap(l->cap_style);
	    set_linejoin(l->join_style);
	    if (l->style == SOLID_LINE || l->style_val <= 0.) {
		put_polyline(&a);
	    } else {
		set_linestyle(&(l->style), &(l->style_val), &pattern, &h);
		put_patternline(&a,a.next,&pattern,0.,0);
	    }
	    if (t[0] != NULL)		/* insert_endpoint was called */
		t[0]->next = t[1];	/* restore original l->points sequence */
	}

	if (l->for_arrow) {
	    if (verbose) fputs("% Forward Arrow\n", tfp);
	    put_arrow(f[0], f[1], l->for_arrow, l->thickness);
	}

	if (l->back_arrow) {
	    if (verbose) fputs("% Backward Arrow\n", tfp);
	    put_arrow(q, p, l->back_arrow, l->thickness);
	}
}

static void
put_line_or_vector(F_point *p, F_point *q, F_line *l)
{
	bool too_short = false;
	int	sx, sy;
	F_point	a, o;
	double h;

	if (l->for_arrow && ISLTXARROW(l->for_arrow)
			&& l->thickness == round(l->for_arrow->thickness)) {
	    /* At least an arrow is drawn. The linecap might be set uselessly */
	    set_linewidth(l->thickness);
	    set_linecap(l->cap_style);
	    if (put_vector(p, q, l->back_arrow, &(l->thickness),
			   &(l->cap_style), &sx, &sy)
			&& l->back_arrow && ISLTXARROW(l->back_arrow)
			&& l->back_arrow->thickness > 0.5) {
		set_linewidth(round(l->back_arrow->thickness));
		PUTVECTOR(p, -sx, -sy, 0);
	    } else if (l->back_arrow) {
		put_arrow(q, p, l->back_arrow, l->thickness);
	    }
	} else if (l->back_arrow && ISLTXARROW(l->back_arrow)
			&& l->thickness == round(l->back_arrow->thickness)) {
	    set_linewidth(l->thickness);
	    set_linecap(l->cap_style);
	    put_vector(q, p, l->for_arrow, &(l->thickness), &(l->cap_style),
								&sx, &sy);
	    if (l->for_arrow)
		put_arrow(p, q, l->for_arrow, l->thickness);
	} else {
	    if (l->back_arrow && (h = get_offset(l->back_arrow, l->thickness,
						 l->cap_style)) > 0.5)
		too_short = get_midpoint(p, q, &a, &h);
	    else
		a = *p;

	    if (!too_short && l->for_arrow
			   && (h = get_offset(l->for_arrow, l->thickness,
					      l->cap_style)) > 0.5)
		too_short = get_midpoint(q, &a, &o, &h);
	    else
		o = *q;

	    if (!too_short) {
		set_linewidth(l->thickness);
		set_linecap(l->cap_style);
		PUTLINE(a, o);
	    }
	    if (l->for_arrow)
		put_arrow(p, q, l->for_arrow, l->thickness);
	    if (l->back_arrow)
		put_arrow(q, p, l->back_arrow, l->thickness);
	}
}

static void
put_picture(F_point *p, F_point *q, F_point *r, F_point *s, F_line *l)
{
	/*
	 * unflipped box, angle == 0:       flipped, angle == 90:
	 *	point 1, p +-----------+ 2, q        1 +------+ 4
	 *	           | .____     |               | ...  |
	 *	           | :         |               | |    |
	 *	           |           |               | |    |
	 *	      s, 4 +-----------+ 3, r          |      |
	 *	                                       |      |
	 *	                                       |      |
	 *	                                     2 +------+ 3
	 */
	int	n, dx, dy, rot;
	char	*c;
	F_point	*ll;

	if (removesuffix) {
	    c = strrchr(l->pic->file,'.');
	    n =  c == NULL ? (int) strlen(l->pic->file) : c - l->pic->file;
	} else {
	    n = strlen(l->pic->file);
	}
	dx = r->x - p->x;
	dy = r->y - p->y;
	/* get the rotation, and write the height and width to dx and dy */
	rot = 0;
	ll = s; /* only for !flipped */
	if (dx < 0 && dy < 0) {
	    rot = 180;
	    ll = s;
	    dx = -dx;
	    dy = -dy;
	}
	else if (dx < 0 && dy >= 0) {
	    rot = dy;
	    dy = -dx;
	    dx = rot;
	    rot = 270;
	    ll = q;
	}
	else if (dy < 0 && dx >= 0) {
	    rot = dx;
	    dx = -dy;
	    dy = rot;
	    rot = 90;
	    ll = q;
	}

#define PREPEND prepend ? prepend : "\0"
	if (!l->pic->flipped) {
	    if (rot == 0)
		fprintf(tfp,
			"\\put(%d,%d){\\resizebox{%d\\unitlength}{%d\\unitlength}"
			"{\\includegraphics{%s%.*s}}}\n", XCOORD(ll->x),
			YCOORD(ll->y), dx, dy, PREPEND, n, l->pic->file);
	    else
		fprintf(tfp, "\\put(%d,%d){\\rotatebox{%d}{\\smash{\\rlap{"
			"\\resizebox*{%d\\unitlength}{%d\\unitlength}{"
			"\\includegraphics{%s%.*s}}}}}}\n", XCOORD(ll->x),
			YCOORD(ll->y), rot, dx, dy, PREPEND, n, l->pic->file);
	    return;
	}
	/* flipped */
	rot += 90;
	if (rot == 360)
	    fprintf(tfp,
		    "\\put(%d,%d){\\resizebox*{-%d\\unitlength}{%d\\unitlength}"
		    "{\\includegraphics{%s%.*s}}}\n",
		    XCOORD(r->x), YCOORD(r->y), dy, dx, PREPEND, n, l->pic->file);
	else
	    fprintf(tfp,
		    "\\put(%d,%d){\\rotatebox{%d}{\\smash{\\rlap{\\resizebox*"
		    "{-%d\\unitlength}{%d\\unitlength}{\\includegraphics{%s%.*s}}}}}}\n",
		    XCOORD(r->x), YCOORD(r->y), rot, dy, dx, PREPEND, n, l->pic->file);
	return;
}


void
genpict2e_line(F_line *l)
{
	F_point		*p[5];		/* the first non-coincident points */
	struct pattern	pattern;
	int		npts = 0;	/* number of unique points */
	double		h1;

	if (verbose)
	    fputs("%\n% Fig POLYLINE object\n%\n", tfp);

	/* print any comments prefixed with "%" */
	print_comments("% ", l->comments, "");

	/* count the number of non-concident points: 1, 2, ..., 5, infinity */
	p[0] = l->points;
	while (npts < 4 && p[npts]->next != NULL) {
	    p[npts+1] = p[npts]->next;	/* p[++npts] = p[npts]->next */
	    ++npts;			/* gave segmentation fault?? */
	}
	++npts;

	if (l->type == T_PIC_BOX) {
	    if (npts < 4)
		fputs(
		    "A picture box with less than four unique points. Omitting.\n",
		    stderr);
	    else
		put_picture(p[0], p[1], p[2], p[3], l);
	    return;
	}

	/* fill */
	if (l->fill_style != UNFILLED && npts > 2) {
	    if (verbose) fputs("% Fill\n", tfp);
	    set_fillcolor(l->fill_color, l->fill_style, &(l->pen_color));
	    if (l->type == T_POLYLINE) {
		p[4] = put_points("\\polygon*", p[0]);
		if (!(EQUAL(p[0], p[4])))
		    PUTPOINT(p[4]);
		fprintf(tfp,"\n");
	    } else if (l->type == T_POLYGON || l->type == T_BOX) {
		put_points("\\polygon*", p[0]);
		fputc('\n', tfp);
	    /* else { .. would be sufficient, no other possibilities remain */
	    } else if (l->type == T_ARC_BOX) {
		put_oval(p[0], p[2], l->radius, "fillpath");
	    }
	}

	if (l->thickness == 0 && l->for_arrow == NULL && l->back_arrow == NULL)
	    return;

	/* a single point */
	if (npts == 1) {
	    F_pos	o;
	    if (l->thickness == 0)
		return;
	    set_color(l->pen_color);
	    set_linewidth(l->thickness);
	    o.x = XCOORD(p[0]->x);
	    o.y = YCOORD(p[0]->y);
	    if (l->cap_style == ROUNDCAP) {
		set_linecap(ROUNDCAP);
		fprintf(tfp, "\\Line(%d,%d)(%d,%d)%%\n", o.x, o.y, o.x, o.y);
	    } else {
		set_linecap(BUTTCAP);
		h1 = l->thickness <= THICK_SCALE ?
		    l->thickness/4.0 : (l->thickness-THICK_SCALE)/2.0;
		fprintf(tfp, "\\Line(%d,%d)(%d,%d)%%\n",
		    round(o.x-h1), o.y, round(o.x+h1), o.y);
	    }
	    return;
	}

	/* two or more points */
	/* the color might be set uselessly, if a too short line with arrowheads
	 * with zero line thickness is to be drawn. We pay that price */
	set_color(l->pen_color);

	if (l->type == T_POLYGON || l->type == T_BOX) {
	    set_linewidth(l->thickness);
	    if (l->style == SOLID_LINE || l->style_val <= 0.) {
		set_linejoin(l->join_style);
		put_points("\\polygon", p[0]);
		fputc('\n', tfp);
	    } else {
		set_linestyle(&(l->style), &(l->style_val), &pattern, &h1);
		set_linecap(l->cap_style);
		set_linejoin(l->join_style);
		put_patternline(p[0],p[1],&pattern,0.,0);
	    }
	    return;
	}

	if (l->type == T_ARC_BOX) {
	    if (npts < 3 || EQUAL(p[0],p[2])) return;
	    if (l->style == SOLID_LINE) {
		set_linewidth(l->thickness);
		put_oval(p[0], p[2], l->radius, "strokepath");
	    } else {
		put_patternoval(p[0], p[2], l);
	    }
	    return;
	}

	/* Below here, l->type must be a T_POLYLINE */
	if (l->type != T_POLYLINE) {
	    fprintf(stderr, "Unknown line style %d. Please, report this bug.\n",
		    l->type);
	    return;
	}

	if (npts > 2 || l->style != SOLID_LINE)
	    put_poly_or_patternline(p[0], p[1], l);
	else	/* two points, solid line */
	    put_line_or_vector(p[0], p[1], l);
}

void
genpict2e_spline(F_spline *s)
{
	print_comments("% ", s->comments, "");
	fputs("Can't generate spline; omitting object\n", stderr);
}

/*
 * Return the coordinates of an octagon on the unit circle, scaled by s.
 * In addition, return the control points for creation of a X-spline.
 * Use s = 1.0258210 if the resulting polyline shall oscillate around the unit
 * circle. Use s = 1.0278126 if the polyline shall have a radius equal to one on
 * the vertical and horizontal, and a slightly larger radius everywhere else.
 *
 * With s = 1, the horizontal and vertical radii are 0.972939 (measured by
 * drawing a circle with R = 10^5 Fig units). With s = 1/0.972939 = 1.0278137
 * the minimum radii come out as 1.000001. The maxima, measured by rotating the
 * circle by pi/8, are 1.003884. Dividing s by the mean of these two yields s =
 * 1.0258210. Dividing 1.0278137 by 1.000001 yields s = 1.0278126. Controlled by
 * drawing a circle with R = 10^6 Fig units.
 */
static void
get_xsplinepoints(F_control c[8], struct d_pos p[8], double s)
{
	int	i;
	double	x = 1, y = 0.41421356;	/* y = tan(pi/8) ( = sqrt(2) - 1 ) */

	for (i = 0; i < 8; ++i) {
	    c[i].lx = 0.;
	    c[i].ly = 0.;
	    c[i].rx = 0.;
	    c[i].ry = 0.;
	    c[i].next = &(c[i+1]);
	    c[i].s = S_SPLINE_APPROX;
	}
	c[i-1].next = NULL;

	x *= s;
	y *= s;
	/* The points of an octagon on the unit circle.                       */
	                           /*                                         */
	                           /*                   y ^                   */
	p[0].x = -y; p[0].y =  x;  /*                     |                   */
	p[1].x =  y; p[1].y =  x;  /*         (-0.41,1)   |   (0.41,1)        */
	p[2].x =  x; p[2].y =  y;  /*                 .#--|--#                */
	p[3].x =  x; p[3].y = -y;  /*               .'  0 | 1 `.              */
	p[4].x =  y; p[4].y = -x;  /*   (-1,0.41)  # 7    |     `# (1,0.41)   */
	p[5].x = -y; p[5].y = -x;  /*              |      |    2 |            */
	p[6].x = -x; p[6].y = -y;  /*           ----------+-------------> x   */
	p[7].x = -x; p[7].y =  y;  /*              |      |      |            */
	                           /*  (-1,-0.41)  # 6    |    3 # (1,-0.41)  */
	                           /*               `.  5 | 4  .'             */
	                           /*                 `#--|--#'               */
	                           /*        (-0.41,-1)      (0.41,-1)        */
}

/*
 * Draw an ellipse by constructing a X-spline, create a polyline that
 * approximates that X-spline and draw the polyline. The polyline might be
 * dashed, dotted or patterned in any other way. The control points of the
 * X-spline lie in the vertices of an octagon.
 */
static void
put_patternellipse(F_ellipse *e)
{
	F_spline s;
	F_line *l;
	F_point p[8];		/* octagon points in int x, y coordinates */
	F_control c[8];
	struct d_pos exi[8];	/* octagon points on the unit circle */
	int	i;
	double	angle, cosa, sina;

	/* The stretch for the octagon such that the final polyline oscillates
	 * around the circle is 1.0258210. */
	get_xsplinepoints(c, exi, 1.0258210);
	/* reduce the angle to -pi/2 <= angle <= pi/2 */
	angle = e->angle;
	while (angle > M_PI_2) angle -= M_PI;
	while (angle < -M_PI_2) angle += M_PI;
	angle = -angle;
	cosa = cos(angle);
	sina = sin(angle);
	/* scale, rotate and move the unit circle*/
	for (i = 0; i < 8; ++i) {
	    p[i].x = e->center.x + round(cosa * e->radiuses.x * exi[i].x
					  - sina * e->radiuses.y * exi[i].y);
	    p[i].y = e->center.y + round(sina * e->radiuses.x * exi[i].x
					  + cosa * e->radiuses.y * exi[i].y);
	    p[i].next = &(p[i+1]);
	}
	p[i-1].next = NULL;

	s.type = T_CLOSED_XSPLINE;
	s.style = e->style;
	s.thickness = e->thickness;
	s.pen_color = e->pen_color;
	s.depth = e->depth;
	s.fill_style = UNFILLED;
	s.style_val = e->style_val;
	s.for_arrow = NULL;
	s.back_arrow = NULL;
	s.cap_style = BUTTCAP; /* no e->cap_style */
	s.points = &(p[0]);
	s.controls = &(c[0]);
	s.comments = NULL;
	s.next = NULL;
	l = create_line_with_spline(&s);
	l->join_style = 1; /* ROUND_JOIN */
	i = verbose;
	verbose = 0;
	genpict2e_line(l);
	verbose = i;
	free_linestorage(l);
}

/*
 * Draw an arc box by creating a polyline that approximates a circle and move
 * the four quadrants of the circle into the corners of the arc box.
 */
static void
put_patternoval(F_point *p, F_point *q, F_line *l)
{
	int		i, x1, x2, y1, y2, dx, dy, rad;
	F_spline	s;
	F_line		*b;
	F_point		*r[4];	/* pointer to points on the axes */
	F_point		o[8];	/* octagon points scaled to box radius */
	F_control	c[8];
	struct d_pos	u[8];	/* octagon points on the unit circle */

	dx = q->x - p->x;
	dy = q->y - p->y;
	rad = l->radius;
	if (MIN(abs(dx), abs(dy)) < 2*rad )
	    rad = MIN(abs(dx), abs(dy))/2;

	dx = dx > 0 ? 1: -1;
	dy = dy > 0 ? 1: -1;

	x1 = p->x + dx*rad;
	y1 = p->y + dy*rad;
	x2 = q->x - dx*rad;
	y2 = q->y - dy*rad;

	get_xsplinepoints(c, u, 1.0278126);
	/* scale the control points for the unit circle */
	for (i = 0; i < 8; ++i) {
	    o[i].x = round(rad * u[i].x);
	    o[i].y = round(rad * u[i].y);
	    o[i].next = &(o[i+1]);
	}
	o[i-1].next = NULL;

	s.type = T_CLOSED_XSPLINE;
	s.style = l->style;
	s.thickness = l->thickness;
	s.pen_color = l->pen_color;
	s.depth = l->depth;
	s.fill_style = UNFILLED;
	s.style_val = l->style_val;
	s.for_arrow = NULL;
	s.back_arrow = NULL;
	s.cap_style = l->cap_style;
	s.points = &(o[0]);
	s.controls = &(c[0]);
	s.comments = NULL;
	s.next = NULL;

	b = create_line_with_spline(&s);
	b->join_style = l->join_style;

	p = b->points;
	if (p == NULL)
	    return;
/* the octagon is drawn in tex coordinate direction, therefore -dy. */
#define MOVE(x1,y1)	p->x = x1 + dx * p->x;	\
			p->y = y1 - dy * p->y;	\
			p = p->next
/* Insert points at the axes into the polyline, such that the lines connecting
 * the four quadrants of the circle are exactly horizontal or vertical. */
#define INSERT(x1,y1,x2,y2)	o[i] = *p;			\
				r[i] = p;			\
				p->next = &(o[i]);		\
				p->x = x1 + dx * p->x;		\
				p->y = y1 - dy * p->y;		\
				o[i].x = x2 + dx * o[i].x;	\
				o[i].y = y2 - dy * o[i].y;	\
				p = o[i].next;			\
				++i
	while (p->y > 0) {
	    MOVE(x2,y1);
	}
	i = 0;
	if (p->y == 0) {
	    INSERT(x2,y1,x2,y2);
	}
	while (p->x > 0) {
	    MOVE(x2,y2);
	}
	if (p->x == 0) {
	    INSERT(x2,y2,x1,y2);
	}
	while (p->y < 0) {
	    MOVE(x1,y2);
	}
	if (p->y == 0) {
	    INSERT(x1,y2,x1,y1);
	}
	while (p->x < 0) {
	    MOVE(x1,y1);
	}
	if (p->x == 0) {
	    INSERT(x1,y1,x2,y1);
	}
	while (p != NULL) {
	    MOVE(x2,y1);
	}

	x1 = verbose;
	verbose = 0;
	genpict2e_line(b);
	verbose = x1;
	/* restore the original point sequence */
	while (i--)
	    r[i]->next = o[i].next;
	free_linestorage(b);
}

/*
 * Draw an ellipse by approxmating it with four cubic Bezier-splines.
 * Write \fillpath or \strokepath after a call to put_ellipse.
 */
static void
put_ellipse(F_ellipse *e)
{
/*
 * Approximate a circle by four cubic Bezier-splines. The Bezier splines have
 * two end-points and two control-points. The start-and end points are located
 * in the vertices of the ellipse (or on the horizontal and vertical axis of a
 * circle, respectively. On the unit circle, the control points are located at
 * (1,MAGIC) or (MAGIC, 1). The MAGIC number is 0.551784, see
 * http://www.tinaja.com/glib/ellipse4.pdf. The splines then exactly fit the
 * circle every 30 degrees, and oscillate around the circle otherwise. With
 * 0.55228475 the splines exactly fit the circle every 45 degrees, and are
 * otherwise always outside of the circle.
 *
 * Here is a sketch of one Bezier spline on a unit quarter-circle, from (1,0)
 * over (1,MAGIC) and (MAGIC,1) to (0,1).
 *
 *	   xi ^
 *	      |
 *	(0,1) #      o (MAGIC, 1)
 *	      |
 *	      |
 *	      |            o (1,MAGIC)
 *	      |
 *	      |
 *	      +------------#--->
 *	    (0,0)        (1,0)  eta
 *
 * Fig- and pict2e coordinate system differ - start on the top, going clockwise,
 * which will end up starting on the bottom, advancing counter-clockwise.
 */
	int	i, j;
	double	angle, cosa, sina;
#define	MAGIC	0.551784
	struct etaxi {
	    double x, y;
	} exi[13] = { /* initial and final point coincide */
	    {	 0.,	-1.	},
	    { MAGIC,	-1.	},
	    {	 1.,	-MAGIC	},
	    {	 1.,	 0.	},
	    {	 1.,	 MAGIC	},
	    { MAGIC,	 1.	},
	    {	 0.,	 1.	},
	    {-MAGIC,	 1.	},
	    {	-1.,	 MAGIC	},
	    {	-1.,	 0.	},
	    {	-1.,	-MAGIC	},
	    {-MAGIC,	-1.	},
	    {	 0.,	-1.	}
	};

	angle = e->angle;
	while (angle > M_PI_2) angle -= M_PI;
	while (angle < -M_PI_2) angle += M_PI;
	/* correct for the coordinate transform */
	angle = -angle;
	cosa = cos(angle);
	sina = sin(angle);

	fprintf(tfp,"\\moveto(%d,%d)",			     /* exi[0].x == 0 */
		XCOORD(round(e->center.x - sina * e->radiuses.y * exi[0].y)),
		YCOORD(round(e->center.y + cosa * e->radiuses.y * exi[0].y)));
	for (i = 1; i < 13; i = j) {
	    fputs("\\curveto", tfp);
	    for (j = i; j < i + 3; ++j)
		   fprintf(tfp,"(%d,%d)",
			XCOORD(round(e->center.x + cosa * e->radiuses.x * exi[j].x
					   - sina * e->radiuses.y * exi[j].y)),
			YCOORD(round(e->center.y + sina * e->radiuses.x * exi[j].x
					   + cosa * e->radiuses.y * exi[j].y)));
	    if (j == 7) fputc('\n', tfp);
	}
	fputs("\\closepath", tfp);
}

void
genpict2e_ellipse(F_ellipse *e)
{
	/*
	 * For compatibility with eepic, viz., \usepackage{pict2e,epic,eepic},
	 * avoid \circle*. Pict2e ignores the line-thickness and just fills the
	 * circle, while eepic fills the circle and strokes the outline. XeTeX
	 * seems to have problems setting the color for the eepic-macros, thus
	 * also avoid \circle.
	 */

	if (verbose)
	    fputs("%\n% Fig ELLIPSE object\n%\n", tfp);

	/* print any comments prefixed with "%" */
	print_comments("% ", e->comments, "");

	if (e->fill_style != UNFILLED) {
	    set_fillcolor(e->fill_color, e->fill_style, &(e->pen_color));

	    /* fill the ellipse */
	    if (e->radiuses.x == e->radiuses.y) { /* filled circle */
		if (epiccompatible)
		    fprintf(tfp,
			"\\circlearc[1]{%d}{%d}{%d}{0}{360}\\closepath\\fillpath\n",
			XCOORD(e->center.x), YCOORD(e->center.y), e->radiuses.x);
		else
		    fprintf(tfp, "\\put(%d,%d){\\circle*{%d}}\n",
			    XCOORD(e->center.x), YCOORD(e->center.y),
			    2*e->radiuses.x);
	    } else {
		put_ellipse(e);
		fputs("\\fillpath\n", tfp);
	    }
	}

	if (e->thickness == 0) return;

	set_color(e->pen_color);
	set_linewidth(e->thickness);

	if (e->style == SOLID_LINE) {
	    if (e->radiuses.x == e->radiuses.y) { /* circle outline */
		if (epiccompatible)
		    fprintf(tfp,
			"\\circlearc[1]{%d}{%d}{%d}{0}{360}\\closepath\\strokepath\n",
			XCOORD(e->center.x), YCOORD(e->center.y), e->radiuses.x);
		else
		    fprintf(tfp, "\\put(%d,%d){\\circle{%d}}\n",
			    XCOORD(e->center.x), YCOORD(e->center.y),
			    2*e->radiuses.x);
	    } else {
		put_ellipse(e);
		fputs("\\strokepath\n", tfp);
	    }
	} else {
	    put_patternellipse(e);
	}
}

/*
 * Write font and font size selection commands.
 */
static void
put_font(F_text *t)
{
	int texsize, bprec;
	double baselineskip;

	/* tex-drivers by default use the correct font size, a bit different
	 * from the size on the screen */
	if (nofontsize) {
	    if (nofontname) return;
	} else {
	    /* the line below is really
	     * TEXFONTMAG (texfonts.h), but see also PSFONTMAG (psfonts.h) */
	    texsize = round(t->size * (rigid_text(t) ? 1.0 : fontmag));
	    baselineskip = (texsize * 1.2);
	    if (baselineskip == floor(baselineskip))
		bprec = 0;
	    else
		bprec = 1;

	    fprintf(tfp, "\\fontsize{%d}{%.*f}", texsize, bprec, baselineskip);

	    if (nofontname) {
		fputs("\\selectfont ", tfp);
		return;
	    }
	}

	if (usetexfonts && psfont_text(t)) {
	    unpsfont(t);
	    t->flags -= PSFONT_TEXT;
	}

	if (psfont_text(t))
		fprintf(tfp, "\\usefont%s", texpsfonts[t->font <= MAX_PSFONT ?
				t->font + 1 : 0]);
	else
		/* Default psfont is -1, default texfont 0, also accept -1. */
		fprintf(tfp, "\\normalfont%s ", texfonts[t->font <= MAX_FONT ?
				(t->font >= 0 ? t->font : 0) : MAX_FONT - 1]);
}

void
genpict2e_text(F_text *t)
{
	int	x, y;
	char	*tpos;
	unsigned char	*cp;

	if (verbose)
	    fputs("%\n% Fig TEXT object\n%\n", tfp);

	/* print any comments prefixed with "%" */
	print_comments("% ", t->comments, "");

	x = XCOORD(t->base_x);
	y = YCOORD(t->base_y);

	switch (t->type) {

	    case T_LEFT_JUSTIFIED:
	    case DEFAULT:
		tpos = "[lb]";
		break;

	    case T_CENTER_JUSTIFIED:
		tpos = "[b]";
		break;

	    case T_RIGHT_JUSTIFIED:
		tpos = "[rb]";
		break;

	    default:
		fputs("Text incorrectly positioned\n", stderr);
		tpos = "[lb]";	/* make left in this case */
	    }

	set_color(t->color);

	fprintf(tfp, "\\put(%d,%d){", x, y);

        if(t->angle)
          fprintf(tfp, "\\rotatebox{%.1f}{", t->angle*180/M_PI);

	/* smash is used to position text at baseline */
	fprintf(tfp, "\\makebox(0,0)%s{\\smash{", tpos);

	put_font(t);

	/* Zapf Dingbats is written with \char%u, otherwise latex interprets
	 * some characters */
	if (t->font == MAX_PSFONT) /* && psfont_text(t) - true anyway */
	    for (cp = (unsigned char*)t->cstring; *cp; ++cp)
		fprintf(tfp, "\\char%hhu", *cp);
	else if (!(special_text(t) || allspecial)) {
	    char *c;
	    /* This loop escapes characters "$&%#_{}" and "~^\". */
	    for (cp = (unsigned char*)t->cstring; *cp; ++cp) {
		if (strchr("$&%#_{}", *cp))
		    fputc('\\', tfp);
		if ((c = strchr("~^\\", *cp))) {
		    if (*c == '\\')
			fputs("\\textbackslash ", tfp);
		    else
			fprintf(tfp,"\\%c{}", *c);
		} else
		    fputc(*cp, tfp);
	    }
	} else for (cp = (unsigned char*)t->cstring; *cp; ++cp) {
#ifdef I18N
	    extern bool support_i18n;
	    if (support_i18n && (t->font <= 2))
		fputc(*cp, tfp);
	    else
#endif
	    if (*cp >= 0xa0) {
		switch (encoding) {
		   case 0: /* no escaping */
			fputc(*cp, tfp);
			break;
		   case 1: /* iso-8859-1 */
			fprintf(tfp, "%s", ISO1toTeX[(int)*cp-0xa0]);
			break;
		   case 2: /* iso-8859-2 */
			fprintf(tfp, "%s", ISO2toTeX[(int)*cp-0xa0]);
			break;
		}
	    } else
		fputc(*cp, tfp);
	}

        if(t->angle)
             fputc('}', tfp);
	fputs("}}}\n", tfp);
}

/*
 * Draw an arc by creating and drawing a polyline that approximates a circle.
 */
static void
put_patternarc(
	F_pos *c,		/* center point */
	double rad,		/* radius */
	double da,		/* arc angle */
	double angle1,		/* start angle */
	F_arc *a)
{
	int		i, cosa2, sina2, px;
	double		a1, a2, rot, cosr, sinr;
	F_spline	s;
	F_line		*l;
	F_point		*p;
	F_point		o[8];	/* octagon points scaled to the arc radius */
	F_control	z[8];
	struct d_pos	u[8];	/* octagon points on the unit circle */

	get_xsplinepoints(z,u,1.025821);
	/* scale the control points */
	for (i = 0; i < 8; ++i) {
	    o[i].x = round(rad * u[i].x);
	    o[i].y = round(rad * u[i].y);
	    o[i].next = &(o[i+1]);
	}
	o[i-1].next = NULL;

	s.type = T_CLOSED_XSPLINE;
	s.style = a->style;
	s.thickness = a->thickness;
	s.pen_color = a->pen_color;
	s.depth = a->depth;
	s.fill_style = UNFILLED;
	s.style_val = a->style_val;
	s.for_arrow = a->for_arrow;
	s.back_arrow = a->back_arrow;
	s.cap_style = a->cap_style;
	s.points = &(o[0]);
	s.controls = &(z[0]);
	s.comments = NULL;
	s.next = NULL;

	l = create_line_with_spline(&s);
	l->join_style = MITERJOIN;

	p = l->points;
	if (p == NULL)
	    return;

	/* the octagon runs in clockwise direction.
	 * a1 is approx. 3*pi/8 (strangely, the control points for the octagon
	 * start at 5*pi/8). If create_line_with_splines() changes, the
	 * following breaks! */
	a1 = atan2(p->y, p->x);
	a2 = a1 - da;
	sinr = sin(a2);
	cosr = cos(a2);
	sina2 = round(rad*sinr);
	cosa2 = round(rad*cosr);
	if (a2 >= M_PI_4)
	    while (p->x < cosa2) {
		o[3].next = p;
		p = p->next;
	    }
	else
	    while (p->y > sina2) {
		o[3].next = p;
		p = p->next;
	    }
	if (a2 < -M_PI_4)
	    while (p->x > cosa2) {
		o[3].next = p;
		p = p->next;
	    }
	if (a2 < -3. * M_PI_4)
	    while (p->y < sina2) {
		o[3].next = p;
		p = p->next;
	    }
	if (a2 < -5. * M_PI_4)
	    while (p->x < cosa2) {
		o[3].next = p;
		p = p->next;
	    }
	/* re-use the octagon points o[]; o[0] might be the center point for
	 * pie-wedge arcs, o[1] is the point on the arc exactly at angle a2,
	 * o[2] is again the center point. Use o[3].next and o[4].next to
	 * restore the original point sequence, see below */
	/* the polyline-circle wobbles around the real radius, so get the
	 * current radius */
	rot = sqrt((double) o[3].next->x * o[3].next->x
		    + (double) o[3].next->y * o[3].next->y);
	o[1].x = round(rot*cosr);
	o[1].y = round(rot*sinr);
	o[1].next = NULL;
	o[4].next = p;
	o[3].next->next = &(o[1]);

	/* rotate and move the arc into place,
	 * direction == 0 clockwise, 1 counterclockwise,
	 * YDIR in the following for Xfig to pict2e coordinate converson
	 * TODO: get that right, the YDIR here and below, less convoluted
	 */
	if (a->direction) {
	    i = -1;
	    rot = YDIR(angle1 - M_PI + a1);
	} else {
	    i = 1;
	    rot = YDIR(angle1 - a1);
	}
	cosr = cos(rot);
	sinr = sin(rot);

	p = l->points;
	while (p != NULL) {
	    px = i * p->x;
	    p->x = c->x + round(cosr * px - YDIR(sinr * p->y));
	    p->y = c->y + round(sinr * px + YDIR(cosr * p->y));
	    p = p->next;
	}

	if (a->type == T_PIE_WEDGE_ARC) {
	    l->type = T_POLYGON;
	    /* xfig closes polygons */
	    o[0].x = c->x;
	    o[0].y = c->y;
	    o[0].next = l->points;
	    o[1].next = &(o[2]);
	    o[2].x = c->x;
	    o[2].y = c->y;
	    o[2].next = NULL;
	    l->points = &(o[0]);
	} else {
	    l->type = T_POLYLINE;
	}

	i = verbose;
	genpict2e_line(l);
	verbose = i;
	/* restore the original point sequence */
	o[3].next->next = o[4].next;
	if (a->type == T_PIE_WEDGE_ARC)
	    l->points = o[0].next;
	free_linestorage(l);
}

void
genpict2e_arc(F_arc *a)
{
	F_pos	c;
	F_point	p, q;
	int	d1x, d1y, d2x, d2y, preca;
	double	da, d;
	double	rad, angle1, angle2, offa1 = 0., offa2 = 0.;

	if (verbose)
	    fputs("%\n% Fig ARC object\n%\n", tfp);

	/* print any comments prefixed with "%" */
	print_comments("% ", a->comments, "");

	/* nothing to do; return; */
	if (a->fill_style == UNFILLED && a->thickness == 0
	    && !a->for_arrow && !a->back_arrow) return;

	c.x = round(a->center.x);
	c.y = round(a->center.y);
	/* compute the angles in pict2e-coordinate direction;
	 * pict2e expects angles in degrees */
	d1x =  a->point[0].x - a->center.x;
	d1y =  a->point[0].y - a->center.y;
	d2x =  a->point[2].x - a->center.x;
	d2y =  a->point[2].y - a->center.y;
	angle1 = atan2(YDIR(d1y), XDIR(d1x)) * 180. / M_PI;
	angle2 = atan2(YDIR(d2y), XDIR(d2x)) * 180. / M_PI;
	/* The radius is the mean of the two radii - they can not differ by more
	 * than one pixel. Round the radius to the nearest tenth */
	rad = 0.5*(sqrt((double)d1x*d1x + (double)d1y*d1y)
		   + sqrt((double)d2x*d2x + (double)d2y*d2y));
	rad = round(rad*10.0) / 10.0;
	/* how precise must the angle be given?  1/rad is the view angle of one pixel */
	da = 180.0 / M_PI / rad;
	preca = 0;
	for (d = 1.0; da < 1.0/d; d *= 10.) ++preca;

	/* prepare the angles for pict2e */
	/* direction == 0 clockwise, 1 counterclockwise */
	if (a->direction) { /* counter-clockwise */
	    if (angle1 > angle2)
		angle2 += 360.;
	    da = angle2 - angle1;
	} else { /* !a->direction, clockwise */
	    if (angle1 < angle2)
		angle1 += 360.;
	    da = angle1 - angle2;
	}
	while (da > 360.) da -= 360.;

	/* Fill the arc */
	if (a->fill_style != UNFILLED && da > 0.) {
	    set_fillcolor(a->fill_color, a->fill_style, &(a->pen_color));
	    fprintf(tfp, "\\circlearc[1]{%d}{%d}{%g}{%.*f}{%.*f}", XCOORD(c.x),
		    YCOORD(c.y), rad, preca, angle1, preca, angle2);
	    switch (a->type) {
		case T_PIE_WEDGE_ARC:
		    fprintf(tfp,"\\lineto(%d,%d)\\closepath\\fillpath\n",
			    XCOORD(c.x), YCOORD(c.y) );
		    break;
		default:
		    fputs("Unknown arc type - please report this bug.", stderr);
		    /* the comment below silences gcc's warning
		       -Wimplicit-fallthrough */
		    /* intentionally fall through */
		case T_OPEN_ARC:
		    fputs("\\closepath\\fillpath\n", tfp);
	    }
	}

	if (a->style != SOLID_LINE && a->thickness != 0) {
	    put_patternarc(&c, rad, da*M_PI/180., angle1*M_PI/180, a);
	    return;
	}

	set_color(a->pen_color);

	/* Draw possible arrows and compute the new start and end angles */
	if (a->back_arrow) {
	    p.x = a->point[0].x;
	    p.y = a->point[0].y;
	    compute_arcarrow_angle((double)c.x, (double)c.y, (double)p.x,
		    (double)p.y, !a->direction, a->back_arrow, &(q.x), &(q.y));
	    put_arrow(&q, &p, a->back_arrow, a->thickness);
	    d = get_offset(a->back_arrow, round(a->thickness), a->cap_style);
	    if (d) {
		offa1 = atan(d/rad) * 180. / M_PI;
		angle1 = angle1 + (a->direction ? offa1 : (-offa1) );
		if (offa1 >= da)
		    return;
	    }
	}

	if (a->for_arrow) {
	    p.x = a->point[2].x;
	    p.y = a->point[2].y;
	    compute_arcarrow_angle((double)c.x, (double)c.y, (double)p.x,
		    (double)p.y, a->direction, a->for_arrow, &(q.x), &(q.y));
	    put_arrow(&q, &p, a->for_arrow, a->thickness);
	    d = get_offset(a->for_arrow, round(a->thickness), a->cap_style);
	    if (d) {
		offa2 = atan(d/rad) * 180. / M_PI;
		angle2 = angle2 - (a->direction ? offa2 : (-offa2) );
		if (offa2 >= da)
		    return;
	    }
	}

	if ((a->for_arrow || a->back_arrow) && offa1 + offa2 >= da)
	    return;

	if (a->thickness == 0) return;

	set_linewidth(a->thickness);

	/* Arcs do not have a join_style, but pie-wedge arcs should have one. */
	/* set_linejoin(a->join_style) */
	fprintf(tfp, "\\circlearc[1]{%d}{%d}{%g}{%.*f}{%.*f}",
		XCOORD(c.x), YCOORD(c.y), rad, preca, angle1, preca, angle2);
	switch (a->type) {
	    case T_PIE_WEDGE_ARC:
		fprintf(tfp, "\\lineto(%d,%d)\\closepath\\strokepath\n",
			XCOORD(c.x), YCOORD(c.y) );
		break;
	    case T_OPEN_ARC:
		fputs("\\strokepath\n", tfp);
		break;
	    default:
		fputs("\\strokepath\n", tfp);
		fputs("Unknown arc type - please report this bug.", stderr);
	}
}

struct driver dev_pict2e = {
	genpict2e_option,
	genpict2e_start,
	gendev_nogrid,
	genpict2e_arc,
	genpict2e_ellipse,
	genpict2e_line,
	genpict2e_spline,
	genpict2e_text,
	genpict2e_end,
	INCLUDE_TEXT
};
