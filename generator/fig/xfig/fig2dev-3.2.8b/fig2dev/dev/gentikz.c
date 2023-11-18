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
 * gentikz.c: convert fig to tikz macro language for TeX/LaTeX
 *
 * Author: Thomas Loimer
 *
 * BUGS:	o shades or tints of the default color may be incorrect
 *		o arrows on arcs and on very short lines may be different
 *		  from arcs produced by the postscript driver
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pi.h"

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "bound.h"
#include "gentikz.h"
#include "messages.h"
#include "psfonts.h"
#include "texfonts.h"		/* texfontnames[] */

/* String arrays and structs */
extern char	*ISO1toTeX[];	/* iso2tex.c */
extern char	*ISO2toTeX[];	/* iso2tex.c */
static const char	*texfonts[] = {
	"",			/* default */
	"\\rmfamily",		/* roman */
	"\\bfseries",		/* bold */
	"\\itshape",		/* italic */
	"\\sffamily",		/* sans serif */
	"\\ttfamily",		/* typewriter */
};
static const char	*texpsfonts[] = {
	"{T1}{ptm}{m}{n}",	/* Times-Roman, default */
	"{T1}{ptm}{m}{n}",	/* Times-Roman */
	"{T1}{ptm}{m}{it}",	/* Times-Italic */
	"{T1}{ptm}{b}{n}",	/* Times-Bold */
	"{T1}{ptm}{b}{it}",	/* Times-BoldItalic */
	"{T1}{pag}{m}{n}",	/* AvantGarde */
	"{T1}{pag}{m}{sl}",	/* AvantGarde-BookOblique */
	"{T1}{pag}{db}{n}",	/* AvantGarde-Demi */
	"{T1}{pag}{db}{sl}",	/* AvantGarde-DemiOblique */
	"{T1}{pbk}{l}{n}",	/* Bookman-Light */
	"{T1}{pbk}{l}{it}",	/* Bookman-LightItalic */
	"{T1}{pbk}{db}{n}",	/* Bookman-Demi */
	"{T1}{pbk}{db}{it}",	/* Bookman-DemiItalic */
	"{T1}{pcr}{m}{n}",	/* Courier */
	"{T1}{pcr}{m}{sl}",	/* Courier-Oblique */
	"{T1}{pcr}{b}{n}",	/* Courier-Bold */
	"{T1}{pcr}{b}{sl}",	/* Courier-BoldItalic */
	"{T1}{phv}{m}{n}",	/* Helvetica */
	"{T1}{phv}{m}{sl}",	/* Helvetica-Oblique */
	"{T1}{phv}{b}{n}",	/* Helvetica-Bold */
	"{T1}{phv}{b}{sl}",	/* Helvetica-BoldOblique */
	"{T1}{phv}{mc}{n}",	/* Helvetica-Narrow */
	"{T1}{phv}{mc}{sl}",	/* Helvetica-Narrow-Oblique */
	"{T1}{phv}{bc}{n}",	/* Helvetica-Narrow-Bold */
	"{T1}{phv}{bc}{sl}",	/* Helvetica-Narrow-BoldOblique */
	"{T1}{pnc}{m}{n}",	/* NewCenturySchlbk-Roman */
	"{T1}{pnc}{m}{it}",	/* NewCenturySchlbk-Italic */
	"{T1}{pnc}{b}{n}",	/* NewCenturySchlbk-Bold */
	"{T1}{pnc}{b}{it}",	/* NewCenturySchlbk-BoldItalic */
	"{T1}{ppl}{m}{n}",	/* Palatino-Roman */
	"{T1}{ppl}{m}{it}",	/* Palatino-Italic */
	"{T1}{ppl}{b}{n}",	/* Palatino-Bold */
	"{T1}{ppl}{b}{it}",	/* Palatino-BoldItalic */
	"{U}{psy}{m}{n}",	/* Symbol */
	"{T1}{pzc}{mb}{it}",	/* ZapfChancery-MediumItalic */
	"{U}{pzd}{m}{n}"	/* ZapfDingbats */
};
static const struct color_table {
	char name[9];
	float r, g, b;
} std_color[NUM_STD_COLS+1] = {	/* 33 = NUM_STD_COLS + 1 */
	{".",		0.  , 0.  , 0.	},
	{"black",	0.  , 0.  , 0.	},
	{"blue",	0.  , 0.  , 1.	},
	{"green",	0.  , 1.  , 0.	},
	{"cyan",	0.  , 1.  , 1.	},
	{"red",		1.  , 0.  , 0.	},
	{"magenta",	1.  , 0.  , 1.	},
	{"yellow",	1.  , 1.  , 0.	},
	{"white",	1.  , 1.  , 1.	},
	{"blue1",	0.  , 0.  , 0.56},
	{"blue2",	0.  , 0.  , 0.69},
	{"blue3",	0.  , 0.  , 0.82},
	{"blue4",	0.53, 0.81, 1.	},
	{"green1",	0.  , 0.56, 0.	},
	{"green2",	0.  , 0.69, 0.	},
	{"green3",	0.  , 0.82, 0.	},
	{"cyan1",	0.  , 0.56, 0.56},
	{"cyan2",	0.  , 0.69, 0.69},
	{"cyan3",	0.  , 0.82, 0.82},
	{"red1",	0.56, 0.  , 0.	},
	{"red2",	0.69, 0.  , 0.	},
	{"red3",	0.82, 0.  , 0.	},
	{"magenta1",	0.56, 0.  , 0.56},
	{"magenta2",	0.69, 0.  , 0.69},
	{"magenta3",	0.82, 0.  , 0.82},
	{"brown1",	0.50, 0.19, 0.	},
	{"brown2",	0.63, 0.25, 0.	},
	{"brown3",	0.75, 0.38, 0.	},
	{"pink1",	1.  , 0.50, 0.50},
	{"pink2",	1.  , 0.63, 0.63},
	{"pink3",	1.  , 0.75, 0.75},
	{"pink4",	1.  , 0.88, 0.88},
	{"gold",	1.  , 0.84, 0.	}
};

/* pgfarrow property flags */
/* CHANGE arrowflag[] below if HAS_FILL or HAS_SWAP is modified! */
#define	HAS_FILL	1
#define	HAS_SWAP	2
#define	HAS_WIDTH	4
/* HAS_WIDTH is currently equivalent to not-a-circle */
#define	NOT_CIRCLE	HAS_WIDTH
#define	HAS_LENGTH	8
#define	IS_HOOK		16	/* needs to be shifted to be flush with line */
/* a quick fix -  set a flag, STYLE_MEANS_FLAG 32, if arrows are added. */
#define	STYLE_MEANS_SWAP(ttype)	ttype == 9
/* CHANGE arrowflag if HAS_FILL or HAS_SWAP above is modified! */
static const char   *arrowflag[3] = {
	"open",
	"fill=.",	/* HAS_FILL == 1 */
	"swap"		/* HAS_SWAP == 2 */
};
/* Information for	obtained from
 * \pgfarrowsset-
 *  -tipend		arrow_shapes.tipmv
 *			struct pgfarrow...
 *  -backend		.backl*length - 0.5*linewidth (only wrong
 *					for backward two-prong fork)
 *  -visualbackend	.lendl*length - 0.5*linewidth
 *  -lineend		.lendl*length + lendt*linewidth (lendt
 *						is always != 0)
 * \pgfarrows-
 *  -hullpoint		.tiphull    true or false: if to use (0,0)
 *  -upperhullpoint	.nhull	    positive: number of upper hull points
 *				    negative: number of hull points
 *  -[upper]hullpoint	.hullp[]    upperhull (nhull > 0) or hull points (nhull < 0)
 *  -hullpoint		.endhull    true or false, if to use .lendl
 * The tipend is always at 0.
 * The backend is often at -1 (times length).
 * The backend could be computed from the minimum coordinate of
 * the hullpoints - but not for the circle or half circle.
 */
static struct pgfarrow {
	int props;	/* property flags */
			/* \pgfarrowsset */
	double backl;	/*  -backend, arrow length factor */
	double lendl;	/*  -lineend, arrow length factor */
	double lendt;	/*  -lineend, arrow line thickness factor */
	bool tiphull;	/* \pgfarrowshullpoint, if to use tip point */
	int nhull;	/*   number of upperhullpoints; hullpoints, if negative */
	struct d_pos hullp[3];	/*  -upperhullpoints */
	bool endhull;	/*  -hullpoint, if to use end point */
} pgfarrow[] = {
	/* type 0, ttype 0 */
	{12, -1., 0., -0.5, true, 1, {{-1.,0.5}}, false},
	/* type 1a, ttype 1, simple triangle */
	/* type 1b, ttype 1, filled simple triangle */
	{13, -1., -1., -0.45, true, 1, {{-1.,0.5}}, false},
	/* type 2a, ttype 2, concave spearhead */
	/* type 2b, ttype 2, filled concave spearhead */
	{13, -1.25, -1., -0.5, true, 1, {{-1.25,0.5}}, false},
	/* type 3a, ttype 3, convex spearhead */
	/* type 3b, ttype 3, filled convex spearhead */
	{13, -1., -1., 0.5, true, 1, {{-0.75,0.5}}, true},
	/* type 4a, ttype 4, diamond */
	/* type 4b, ttype 4, filled diamond */
	{13, -1., -1., 0.5, true, 1, {{-0.5,0.5}}, true},
	/* type 5a/b, ttype 5, circle - handled in code */
	{ 9, -1., -1., 0.45, true, 3, {{-0.25,0.35},{-0.5,0.5},{-0.75,0.35}}, true},
	/* type 6a/b, ttype 6, half circle - handled in code */
	{ 9, -0.5, -0.5, 0.45, false, 2, {{0.,0.5},{-0.25,0.35}}, true},
	/* type 7a, ttype 7, square */
	/* type 7b, ttype 7, filled square */
	{13, -1., -1., -0.45, false, 2, {{0.,0.5},{-1.,0.5}}, false},
	/* type 8a, ttype 8, reverse triangle */
	/* type 8b, ttype 8, filled reverse triangle */
	{13, -1., -1., 0.5, false, 1, {{0.,0.5}}, true},
	/* type 9a, ttype 9, top-half filled concave spearhead */
	/* type 9b, ttype 9, bottom-half filled concave spearhead */
	{14, -1.25, -1., -0.5, true, 1, {{-1.25,0.5}}, false},
	/* type 10o, ttype 10, top-half simple triangle */
	/* type 10f, ttype 10, top-half filled simple triangle*/
	{31, -1., -1., -0.45, true, -1, {{-1.,0.5}}, false},
	/* type 11o, ttype 11, top-half concave spearhead */
	/* type 11f, ttype 11, top-half filled concave spearhead */
	{31, -1.25, -1., -0.5, true, -1, {{-1.25,0.5}}, false},
	/* type 12o, ttype 12, top-half convex spearhead */
	/* type 12f, ttype 12, top-half filled convex spearhead */
	{31, -1., -1., 0.5, true, -1, {{-0.75,0.5}}, true},
	/* type 13a, ttype 13,	"wye" */
	{12, -1., -1., 0.5, false, 1, {{0.,0.5}}, true},
	/* type 13b, ttype 14, bar */
	{ 4, 0., 0., -0.45, false, 1, {{0.,0.5}}, false},
	/* type 14a, ttype 15, two-prong fork */
	{12, -1., -1., -0.45, false, 2, {{0.,0.5},{-1.,0.5}}, false},
	/* type 14b, ttype 16, backward two-prong fork */
	{12, -1., 0., -0.45, false, 2, {{0.,0.5},{-1.,0.5}}, false}
};
struct options {
	bool	has_options;
	double	thickness, wid, ht;
	int	flags;		/* property flags, see struct pgfarrow */
};
struct settings {
	bool	has_options;
	double	thickness, wid, ht;
	int	setflags, flags;	/* setflags: which flags must be set; */
					/* flags:    to what value	      */
};

struct tikzarrow {
	int	type;
	int	props;
	int	flags;
	struct settings	s;
};

/* Variables */
static bool	nofontsize = false;
static bool	nofontname = false;
static bool	removesuffix = false;
static bool	usetexfonts = false;
static bool	allspecial = false;
static bool	pagemode = false;
static bool	figscaling = true;
static char	*prepend = NULL;
static int	xshift = 0;		/* translate figure, if necessary */
static int	yshift = 0;		/* translate figure, if necessary */
static int	encoding = 1;
static int	verbose = 0;
static double	unitlength;
static int	default_color = DEFAULT;
/* static int	cur_color = DEFAULT; */
static int	cur_pencolor = DEFAULT;
static int	cur_patcolor = DEFAULT;
static int	cur_fillcolor = DEFAULT;
static int	cur_fillstyle = BLACK_FILL;	/* really, a solid color: NUMSHADES - 1 */
static int	border_margin = 0;
static struct options	default_options;
static struct options	alt_options;

/* Macros */
#define	PREC1(f)	floor(f) == f ? 0 : 1
#define	MINLINELENGTH	75
#define XCOORD(x)	(x + xshift)
#define YCOORD(y)	(-y + yshift)
#define XDIR(x)		x
#define YDIR(y)		-(y)
#define THICKNESS(T)	(T <= THICK_SCALE ? 0.5*T : T - THICK_SCALE)
			/* THICK_SCALE is of type float, see fig2dev.h */
/* #define round	(int)... see fig2dev.h */
#define PUT_POINT(p)	fprintf(tfp,"(%d,%d)", XCOORD(p->x), YCOORD(p->y))

#define	MITERJOIN	0
#define	BUTTCAP		0
#define	ROUNDCAP	1
#define SQUARECAP	2
#define	HAS_CAPS	1
#define	HAS_JOINS	2

#define	DEG_RAD		57.295779513082322865	/* = 180. / M_PI */


void
gentikz_option(char opt, char *optarg)
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

	case 'F':
	    nofontname = true;
	    break;

	case 'i':	/* prepend this string to included graphics file */
	    prepend = optarg;
	    break;

	case 'f':			/* set default text font */
	    for (i = 1; i <= MAX_FONT; ++i)
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
	    break;

	case 'v':
	    verbose = 1;		/* verbose mode */
	    break;

	case 'W':
	    figscaling = false;
	    break;

	case 'w':		/* remove suffix from included graphics file */
	    removesuffix = true;
	    break;

	case 'E':
	    sscanf(optarg,"%d", &encoding);
	    if (encoding < 0 || encoding > 2)
		encoding = 1;
	    break;

	case 'G':
	case 'L':
	    break;

	default:
	    put_msg(Err_badarg, opt, "tikz");
	    exit(1);
	}
}

/* Print a float number d with up to digits digits behind the comma.
 * Example: fprintf(tfp, %.*f, precision(4, d), d); */
static int
precision(int digits, double d)
{
	int i;
	for (i = 0; i <= digits && floor(d) != d; ++i) d *= 10.;
	return i;
}

static void
put_texdimen(double d, char *dimen)
{
	if (d == 0.) {
	    fputs("0pt", tfp);
	} else if (d == 1.) {
	    fputs(dimen, tfp);
	} else if (d == -1.) {
	    fputc('-', tfp);
	    fputs(dimen, tfp);
	} else {
	    fprintf(tfp, "%.*f%s", precision(3, d), d, dimen);
	}
}

/*
 * Return the tikz-arrowtype.
 * See bound.c, struct _arrow_shape arrow_shapes.
 */
static int
arrowtype(int type, int style)
{
	if (type < 13)
	    return type;
	else
	    return 2 * type + style - 13;
}

/* Define arrows.
 * Default arrow size: Could be scaled with the line width, e.g.,
 *   line width=\pgflinewidth, length=+0pt 8, width=+0pt 4,
 * but the factory configuration in xfig are absolute values,
 *   line width 1, length 8, width 4.
 * Implement the factory defaults. Note, that length and width are
 * calculated before the THICKNESS of line width is taken.
 * Quick path commands do not parse their arguments, hence an, e.g.,
 * \dimen4 is allowed: \pgfqpoint{\dimen4}{0.5\dimen4}.
 * Regular path commands parse their arguments and trip over a \dimen4.
 * To disable parsing, prepend the argument with a '+', e.g., +-0.5\dimen4.
 * Example output:
\pgfdeclarearrow{
  name = aaa,
  parameters = {
    \the\pgfarrowlinewidth,\the\pgfarrowlength,\the\pgfarrowwidth,%
    \ifpgfarrowopen o\fi},
  defaults = {
    line width=7.5\XFigu, length=+0pt 8, width=+0pt 4},
  setup code = {
    % miter protrusion = thk / (2.0 * wd / sqrt(wd*wd + tipmv*tipmv*len*len))
    % = thk  * sqrt(wd*wd + tipmv*tipmv*len*len) / (2 * wd)
    \dimen7 2.15\pgfarrowlength
    \pgfmathveclen{\the\dimen7}{\the\pgfarrowwidth}
    \dimen7 2\pgfarrowwidth
    \pgfmathdivide{\pgfmathresult}{\the\dimen7}
    % a space (or =) is necessary
    \dimen7 \pgfmathresult\pgfarrowlinewidth
    % argument MUST be in braces, the plus is optional
    \pgfarrowssettipend{+\dimen7}
    % Could be more precise - but what for?
    \pgfarrowssetbackend{+-\pgfarrowlength}
    \pgfarrowssetvisualbackend{+-\dimen7}
    % leave space for round caps
    \pgfarrowssetlineend{+-0.95\dimen7}
    \pgfarrowshullpoint{+\dimen7}{+0pt}
    \dimen7 +0.5\pgfarrowwidth\advance\dimen7 by\pgfarrowlinewidth
    \pgfarrowsupperhullpoint{+-\pgfarrowlinewidth}{+\dimen7}
    \pgfarrowssavethe\pgfarrowlinewidth
    \pgfarrowssavethe\pgfarrowlength
    \pgfarrowssavethe\pgfarrowwidth
  },
  drawing code = {\pgfsetdash{}{+0pt}
    \ifdim\pgfarrowlinewidth=\pgflinewidth\else\pgfsetlinewidth{+\pgfarrowlinewidth}\fi
% Only use quick path commands, if the arrows are not to be bent.
    \pgfpathmoveto{\pgfqpoint{-\pgfarrowlength}{0.5\pgfarrowwidth}}
    \pgfpathlineto{\pgfpointorigin}
    \pgfpathlineto{\pgfqpoint{-\pgfarrowlength}{-0.5\pgfarrowwidth}}
    \ifpgfarrowopen\pgfusepathqstroke\else\ifdim\pgfarrowlinewidth>0pt\pgfusepathqfillstroke\else\pgfusepathqfill\fi\fi
  }
}
 */
static void
define_arrow(int ttype, int indx)
{
	int	i;
	/* Information for	obtained from
	 * \pgfarrowsset-
	 *  -tipend		arrow_shapes.tipmv
	 *			struct pgfarrow...
	 *  -backend		.backl*length - 0.5*linewidth (only wrong
	 *					for backward two-prong fork)
	 *  -visualbackend	.lendl*length - 0.5*linewidth
	 *  -lineend		.lendl*length + lendt*linewidth (lendt
	 *						is always != 0)
	 * \pgfarrows-
	 *  -hullpoint		.tiphull    true or false: if to use (0,0)
	 *  -upperhullpoint	.nhull	    positive: number of upper hull points
	 *				    negative: number of hull points
	 *  -[upper]hullpoint	.hullp[]    upperhull (nhull > 0) or hull points (nhull < 0)
	 *  -hullpoint		.endhull    true or false, if to use .lendl
	 * The tipend is always at 0.
	 * The backend is often at -1 (times length).
	 * The backend could be computed from the minimum coordinate of
	 * the hullpoints - but not for the circle or half circle.
	 */

	fprintf(tfp, "\\pgfdeclarearrow{\n  name = xfiga%d,\n", ttype);
	fputs("  parameters = {\n    \\the\\pgfarrowlinewidth", tfp);
	if (HAS_LENGTH & pgfarrow[ttype].props)
	    fputs(" \\the\\pgfarrowlength", tfp);
	if (HAS_WIDTH & pgfarrow[ttype].props)
	    fputs(" \\the\\pgfarrowwidth", tfp);
	if (HAS_FILL & pgfarrow[ttype].props)
	    fputs("\\ifpgfarrowopen o\\fi", tfp);
	fputs("},\n  defaults = {\n", tfp);
	fprintf(tfp, "	  line width=+%.*f\\XFigu",
		PREC1(default_options.thickness), default_options.thickness);
	if (HAS_LENGTH & pgfarrow[ttype].props)
	    /* fputs(", length=+0pt 16", tfp); */
	    fprintf(tfp, ", length=+%.*f\\XFigu",
		    PREC1(default_options.ht), default_options.ht);
	if (NOT_CIRCLE & pgfarrow[ttype].props)
	    /* fputs(", width=+0pt 8", tfp); */
	    fprintf(tfp, ", width=+%.*f\\XFigu",
		    PREC1(default_options.wid), default_options.wid);
	fputs("},\n  setup code = {\n", tfp);

	if (arrow_shapes[indx].tipmv > 0) {
	    fputs("    % miter protrusion = thk * sqrt(wd^2 + (tipmv*len)^2) / (2 * wd)\n", tfp);
	    /* CHANGE the 2 below if any .tipmv has more than 2 digits precision! */
	    fprintf(tfp, "    \\dimen7 %.*f\\pgfarrowlength",
		    precision(2, arrow_shapes[indx].tipmv), arrow_shapes[indx].tipmv);
	    fputs("\\pgfmathveclen{\\the\\dimen7}{\\the\\pgfarrowwidth}\n", tfp);
	    fputs("    \\dimen7 2\\pgfarrowwidth\\pgfmathdivide{\\pgfmathresult}{\\the\\dimen7}\n",
		    tfp);
	    fputs("    \\dimen7 \\pgfmathresult\\pgfarrowlinewidth\n", tfp);
	} else if (arrow_shapes[indx].tipmv == 0.0) {
	    fputs("    \\dimen7 0.5\\pgfarrowlinewidth\n", tfp);
	} else {
	    fputs("    \\dimen7 0pt\n", tfp);
	}
	fputs("    \\pgfarrowssettipend{+\\dimen7}\n", tfp);

	fputs("    \\pgfarrowssetbackend{+", tfp);
	put_texdimen(pgfarrow[ttype].backl, "\\pgfarrowlength");
	fputs("}\n", tfp);

	if (pgfarrow[ttype].lendl == 0.) {
	    fputs("    \\dimen9 -0.5\\pgfarrowlinewidth\n", tfp);
	    fputs("    \\pgfarrowssetvisualbackend{+\\dimen9}\n", tfp);
	    fputs("    \\pgfarrowssetlineend{+", tfp);
	    put_texdimen(pgfarrow[ttype].lendt, "\\pgfarrowlinewidth");
	    fputs("}\n", tfp);
	} else {
	    fputs("    \\dimen9 ", tfp);
	    put_texdimen(pgfarrow[ttype].lendl, "\\pgfarrowlength");
	    fputs("\\advance\\dimen9 by", tfp);
	    put_texdimen(pgfarrow[ttype].lendt, "\\pgfarrowlinewidth");
	    fputc('\n', tfp);
	    fputs("    \\pgfarrowssetlineend{+\\dimen9}\n", tfp);
	    fputs("    \\dimen9 ", tfp);
	    put_texdimen(pgfarrow[ttype].lendl, "\\pgfarrowlength");
	    fputs("\\advance\\dimen9 by-0.5\\pgfarrowlinewidth\n", tfp);
	    fputs("    \\pgfarrowssetvisualbackend{+\\dimen9}\n", tfp);
	}

	if (pgfarrow[ttype].tiphull)
	    fputs("    \\pgfarrowshullpoint{+\\dimen7}{+0pt}\n", tfp);
	fputs("    ", tfp);
	if (pgfarrow[ttype].nhull > 0) {
	    for (i=0; i < pgfarrow[ttype].nhull; ++i) {
		fputs("\\pgfarrowsupperhullpoint{+", tfp);
		put_texdimen(pgfarrow[ttype].hullp[i].x, "\\pgfarrowlength");
		fputs("}{+", tfp);
		put_texdimen(pgfarrow[ttype].hullp[i].y, "\\pgfarrowwidth");
		fputc('}', tfp);
	    }
	} else { /* nhull == -1; CHANGE if nhull == 0 or nhull < -1 occurs */
	    fprintf(tfp,
		    "\\pgfarrowshullpoint{+%.3g\\pgfarrowlength}{+%.1f\\pgfarrowwidth}",
		    pgfarrow[ttype].hullp[0].x, YDIR(pgfarrow[ttype].hullp[0].y));
	}
	fputc('\n', tfp);
	if (pgfarrow[ttype].endhull)
	    fputs("    \\pgfarrowshullpoint{+\\dimen9}{+0pt}\n", tfp);

	if (IS_HOOK & pgfarrow[ttype].props) {
	    /* abuse \pgfarrowinset to hold the y-shift */
	    fputs("    \\pgfarrowinset 0.5\\pgfarrowlinewidth", tfp);
	    fputs("\\advance\\pgfarrowinset by -0.5\\pgflinewidth\n", tfp);
	    fputs("    \\pgfarrowssavethe\\pgfarrowinset\n", tfp);
	}

	fputs("    \\pgfarrowssavethe\\pgfarrowlinewidth\n", tfp);
	if (HAS_LENGTH & pgfarrow[ttype].props)
	    fputs("    \\pgfarrowssavethe\\pgfarrowlength\n", tfp);
	if (HAS_WIDTH & pgfarrow[ttype].props)
	    fputs("    \\pgfarrowssavethe\\pgfarrowwidth\n", tfp);

	fputs("  },\n  drawing code = {\\pgfsetdash{}{+0pt}\n", tfp);
	fputs("    \\ifdim\\pgfarrowlinewidth=\\pgflinewidth", tfp);
	fputs("\\else\\pgfsetlinewidth{+\\pgfarrowlinewidth}\\fi\n", tfp);
	if (NOT_CIRCLE & pgfarrow[ttype].props) {	/* neither circle nor half-circle */
	    if (IS_HOOK & pgfarrow[ttype].props)
					/* use "-" as long as YDIR = -() */
		fputs("    \\pgftransformyshift{-\\pgfarrowinset}\n", tfp);

	    fputs("    \\pgfpathmoveto{\\pgfqpoint{", tfp);
	    put_texdimen(arrow_shapes[indx].points[0].x, "\\pgfarrowlength");
	    fputs("}{", tfp);
	    put_texdimen(YDIR(arrow_shapes[indx].points[0].y), "\\pgfarrowwidth");
	    fputs("}}\n", tfp);
	    for (i = 1; i < arrow_shapes[indx].numpts - 1; ++i) {
		fputs("    \\pgfpathlineto{\\pgfqpoint{", tfp);
		put_texdimen(arrow_shapes[indx].points[i].x,
			"\\pgfarrowlength");
		fputs("}{", tfp);
		put_texdimen(YDIR(arrow_shapes[indx].points[i].y),
			"\\pgfarrowwidth");
		fputs("}}\n", tfp);
	    }
	    if (arrow_shapes[indx].points[i].x == arrow_shapes[indx].points[0].x
		    && arrow_shapes[indx].points[i].y == arrow_shapes[indx].points[0].y) {
		fputs("    \\pgfpathclose\n", tfp);
	    } else {
		fputs("    \\pgfpathlineto{\\pgfqpoint{", tfp);
		put_texdimen(arrow_shapes[indx].points[i].x, "\\pgfarrowlength");
		fputs("}{", tfp);
		put_texdimen(YDIR(arrow_shapes[indx].points[i].y), "\\pgfarrowwidth");
		fputs("}}\n", tfp);
	    }
	} else if (ttype == 5) {	/* circle */
	    fputs("    \\dimen3 0.5\\pgfarrowlength\n", tfp);
	    /* \pgfpathcircle needs the ... {+\dimen3}, but
	     * \pgfpathprecomputed needs ...{\the\dimen3}{\the\dimen3}
	     */
	    fputs("    \\pgfpathcircle{\\pgfqpoint{-\\dimen3}{0pt}}{+\\dimen3}\n", tfp);
	} else if (ttype == 6) {	/* half-circle */
	    fputs("    \\dimen3 0.5\\pgfarrowlength\n", tfp);
	    fputs("    \\pgfpathmoveto{\\pgfqpoint{0pt}{\\dimen3}}\n", tfp);
	    fputs("    \\pgfpatharctoprecomputed{\\pgfpointorigin}{90}{270}", tfp);
	    fputs("{\\pgfqpoint{0pt}{-\\dimen3}}{\\the\\dimen3}{\\the\\dimen3}{1}{1}\n", tfp);
	    /* \pgfpatharctoprecomputed{center point}{start angle}{end angle}{end point}
	     * {x-radius}{y-radius}{ratio x-radius/y-radius}{ratio y-radius/x-radius} */
	} else {
	    fprintf(stderr,
		    "The tikz-arrowtype %d does not exist. Please report this bug.\n",
		    ttype);
	}

	/* stroke command if open is possible
	 * \ifpgfarrowopen\pgfusepathqstroke\else\ifdim\pgfarrowlinewidth>0pt
	 *   \pgfusepathqfillstroke\else\pgfusepathqfill\fi\fi		*/
	/* stroke command for half-fills
	 * \pgfusepathqstroke ... and add the fill-path */
	if (arrow_shapes[indx].numfillpts) {	/* not a simple fill */
	    fputs("%%\n    \\pgfusepathqstroke\n  \\pgfpathmoveto{\\pgfqpoint{", tfp);
	    put_texdimen(arrow_shapes[indx].fillpoints[0].x, "\\pgfarrowlength");
	    fputs("}{", tfp);
	    put_texdimen(YDIR(arrow_shapes[indx].fillpoints[0].y), "\\pgfarrowwidth");
	    fputs("}}\n", tfp);
	    for (i = 1; i < arrow_shapes[indx].numfillpts; ++i) {
		fputs("    \\pgfpathlineto{\\pgfqpoint{", tfp);
		put_texdimen(arrow_shapes[indx].fillpoints[i].x, "\\pgfarrowlength");
		fputs("}{", tfp);
		put_texdimen(YDIR(arrow_shapes[indx].fillpoints[i].y), "\\pgfarrowwidth");
		fputs("}}\n", tfp);
	    }
	    fputs("    \\pgfusepathqfill\n", tfp);
	} else if (HAS_FILL & pgfarrow[ttype].props) {
	    fputs("    \\ifpgfarrowopen\\pgfusepathqstroke\\else\\pgfsetfillcolor{.}\n", tfp);
	    fputs("\t\\ifdim\\pgfarrowlinewidth>0pt\\pgfusepathqfillstroke", tfp);
	    fputs("\\else\\pgfusepathqfill\\fi\\fi\n", tfp);
	} else {
	    fputs("    \\pgfusepathqstroke\n", tfp);
	}

	fputs("  }\n}\n", tfp);
}

/*
 * TeX cannot handle numbers larger than 16383. However, coordinate numbers
 * larger than 16383 are ok, while numbers smaller than -16383 yield a
 * "dimension too large" error. Presumably, positive numbers are handled
 * directly by tikz, while negative numbers involve a pass to TeX. Hence,
 * shift the figure such that all coordinates are larger than -16383.
 */

/* Compute a shift to translate coordinates to values larger than -16383 */
int
shift_coordinate(int ll)
{
	const int	ippi = (int)ppi;
	const int	min_number = -16383;
	int		shift;

	if (ll >= min_number) {
		shift = 0;
	} else {
		shift = min_number - ll;
		shift = ((shift / ippi) + 1) * ippi;
	}
	return shift;
}

void
gentikz_start(F_compound *objects)
{
	int	i;
	double	splength;   /* unitlength expressed in TeX scaled points */

	texfontsizes[0] = texfontsizes[1]
	    = TEXFONTSIZE(font_size != 0.0? font_size : DEFAULT_FONT_SIZE);

	unitlength = mag/ppi;
	border_margin /= unitlength*72.0;
	splength = 4736286.72*unitlength;	/* 1 in = 72.27 x 65536 sp */

	/* adjust for any border margin */
	llx -= border_margin;
	lly -= border_margin;
	urx += border_margin;
	ury += border_margin;

	xshift = shift_coordinate(llx);
	yshift = shift_coordinate(-ury);

	/* print any whole-figure comments prefixed with "%" */
	if (objects->comments) {
	    fprintf(tfp,"%%\n");
	    print_comments("% ", objects->comments, "");
	    fprintf(tfp,"%%\n");
	}
	if (pagemode) {
	    double	width, height;
	    char	unit[] = "in";

	    /* add a tiny extra margin ( + 1), otherwise 2 pages result */
	    width = (urx - llx + 1) * unitlength;
	    height = (ury - lly + 1) * unitlength;
	    if (metric) {
		width *= 2.54;
		height *= 2.54;
		strcpy(unit,"cm");
	    }

	    fputs("\\documentclass{minimal}\n", tfp);
	    fprintf(tfp,
		    "\\usepackage[papersize={%.4g%s,%.4g%s},margin=0pt]{geometry}\n",
		    width, unit, height, unit);
	    fputs("\\usepackage{tikz}\n", tfp);
	    if (arrows_used)
		fputs("\\usetikzlibrary{arrows.meta,bending}\n", tfp);
	    if (pats_used)
		fputs("\\usetikzlibrary{patterns}\n", tfp);
	    fputs("\\parindent0pt\n\\begin{document}\n", tfp);
	}
	if (!pagemode)
		fputs("{\\pgfkeys{/pgf/fpu/.try=false}%\n", tfp);
	if (pagemode || !figscaling) {
/*	if (metric)	fprintf(tfp, "%% 4143.7 sp = (1/472.44) cm\n");
 *	else		fprintf(tfp, "%% 3946.9 sp = (1/1200) in\n");	*/
	    fprintf(tfp, "\\tikzpicture[x=+%lisp, y=+%lisp]\n",
		    (long) splength,	/* intentionally do not round	*/
		    (long) splength);	/* like (splength + 0.5)	*/
	    fprintf(tfp, "\\newdimen\\XFigu\\XFigu%lisp\n", (long)splength);
	} else {
	    fputs("\\ifx\\XFigwidth\\undefined\\dimen1=0pt", tfp);
	    fputs("\\else\\dimen1\\XFigwidth\\fi\n", tfp);
	    fprintf(tfp, "\\divide\\dimen1 by %d\n", urx-llx);
	    fputs("\\ifx\\XFigheight\\undefined\\dimen3=0pt", tfp);
	    fputs("\\else\\dimen3\\XFigheight\\fi\n", tfp);
	    fprintf(tfp, "\\divide\\dimen3 by %d\n", ury-lly);
	    fputs("\\ifdim\\dimen1=0pt\\ifdim\\dimen3=0pt", tfp);
	    fprintf(tfp, "\\dimen1=%lisp\\dimen3\\dimen1\n", (long)splength);
	    fputs("  \\else\\dimen1\\dimen3\\fi", tfp);
	    fputs("\\else\\ifdim\\dimen3=0pt\\dimen3\\dimen1\\fi\\fi\n", tfp);
	    fputs("\\tikzpicture[x=+\\dimen1, y=+\\dimen3]\n", tfp);
	}
	if (pagemode) {
	    fprintf(tfp, "\\newdimen\\XFigu\\XFigu%lisp\n", (long)splength);
	} else {
	    fputs("{\\ifx\\XFigu\\undefined\\catcode`\\@11\n", tfp);
		/* \newdimen can only be used in \outer mode */
		/* define \temp like \newdimen in plain.tex, without \outer */
	    fputs("\\def\\temp{\\alloc@1\\dimen\\dimendef\\insc@unt}", tfp);
	    fputs("\\temp\\XFigu\\catcode`\\@12\\fi}\n", tfp);
	    fprintf(tfp, "\\XFigu%lisp\n", (long) splength);
	    if (figscaling) {
	        fputs("% Uncomment to scale line thicknesses with the same\n",
				tfp);
	        fputs("% factor as width of the drawing.\n", tfp);
	        fputs("%\\pgfextractx\\XFigu{\\pgfqpointxy{1}{1}}\n", tfp);
	        fputs("\\ifdim\\XFigu<0pt\\XFigu-\\XFigu\\fi\n", tfp);
	    }
	}

	if (pats_used) {
	    const char *patterndef[] = {PATTERNS};

	    if (pagemode) {
		for (i=0; i<NUMPATTERNS; ++i)
		    if (pattern_used[i])
			fputs(patterndef[i], tfp);
	    } else {
		fputs("\\catcode`\\@11\n", tfp);
		for (i=0; i<NUMPATTERNS; ++i)
		    if (pattern_used[i]) {
			fprintf(tfp,
				"\\pgfutil@ifundefined{pgf@pattern@name@xfigp%d}{\n",
				i);
			fputs(patterndef[i], tfp);
			fputs("}{}\n", tfp);
		    }
		fputs("\\catcode`\\@12\n", tfp);
	    }
	}
	default_options.thickness = 0.5*THICK_SCALE; /* == THICKNESS(THICK_SCALE) */
	default_options.wid = 4*THICK_SCALE;
	default_options.ht = 8*THICK_SCALE;
	default_options.flags = HAS_FILL;
	alt_options.thickness = default_options.thickness;
	alt_options.wid = default_options.wid;
	alt_options.ht = default_options.ht;
	alt_options.flags = default_options.flags;
	if (arrows_used) {
	    for (i=0; i<NUMARROWS; i+=2) {
		int ttype;
		if (arrow_used[i]) {
		    ttype = arrowtype(i/2, 0);
		    define_arrow(ttype, i);
		    if (arrow_used[i+1] && ++ttype == arrowtype(i/2, 1))
			define_arrow(ttype, i+1);
		} else if (arrow_used[i+1]) {
		    define_arrow(arrowtype(i/2, 1), i+1);
		}
	    }
	}

	for (i=9; i<=NUM_STD_COLS; ++i)
	    if (std_color_used[i-1]) /* i-1: no default color in std_color_used */
		fprintf(tfp, "\\definecolor{%s}{rgb}{%.2g,%.2g,%.2g}\n",
			std_color[i].name, std_color[i].r, std_color[i].g,
			std_color[i].b);
	for (i=0; i<num_usr_cols; ++i)
	    fprintf(tfp, "\\definecolor{xfigc%d}{rgb}{%.3f,%.3f,%.3f}\n",
		    i+NUM_STD_COLS, user_colors[i].r/255.,
		    user_colors[i].g/255., user_colors[i].b/255.);
	/* fprintf(tfp, "\\clip (0,0) rectangle (%d,%d);\n", urx-llx, ury-lly); */
	fprintf(tfp, "\\clip(%d,%d) rectangle (%d,%d);\n",
		XCOORD(llx), YCOORD(ury), XCOORD(urx), YCOORD(lly));

	fputs("\\tikzset{inner sep=+0pt, outer sep=+0pt}\n", tfp);
}

void
gentikz_grid(float major, float minor)
{
	if (minor == 0.0 && major == 0.0)
	    return;

	if (metric) {
	    /* Cancel out the factor by which the figure is multiplied,
	       if metric. 3.81/4 = 450 * 2.54 / 1200	*/
/* TODO: Search for 80/76.2, and 76.2/80, replace */
	    minor *= 3.81/4.;
	    major *= 3.81/4.;
	}
/* TODO: repair the precision, precision(3,minor) and (1,T) below */
#define	GRIDLINE	\
	"\\draw[black!30, line width=%.*f\\XFigu] (%d,%d) grid[step=%.2f\\XFigu] (%d,%d);\n"

	/* first the minor grid */
	if (minor != 0.0)
	    fprintf(tfp, GRIDLINE, PREC1(0.5*THICK_SCALE), 0.5*THICK_SCALE,
		    XCOORD(llx), YCOORD(ury), minor, XCOORD(urx), YCOORD(lly));

	if (major != 0.0)
	    fprintf(tfp, GRIDLINE, PREC1(1.25*THICK_SCALE), 1.25*THICK_SCALE,
		    XCOORD(llx), YCOORD(ury), major, XCOORD(urx), YCOORD(lly));
}

int
gentikz_end()
{
	fputs("\\endtikzpicture", tfp);
	if (pagemode)
	    fputs("%\n\\end{document}", tfp);
	else
	    fputs("}%\n", tfp);

	return 0;
}

static void
points_all(F_point *p)
{
	int len = 6;	/* "\draw " is 6 chars */
	while (p != NULL) {
	    if (len > MINLINELENGTH) {
		fputs("\n  ", tfp);
		len = 2;
	    }
	    len += fprintf(tfp, "--(%d,%d)", XCOORD(p->x), YCOORD(p->y));
	    p = p->next;
	}
	fputs(";\n", tfp);
}

static void
points_penultimate(F_point *p)
{
	int len = 6;	/* "\draw " is 6 chars */
	while (p->next != NULL) {
	    if (len > MINLINELENGTH) {
		fputs("\n  ", tfp);
		len = 2;
	    }
	    len += fprintf(tfp, "--(%d,%d)", XCOORD(p->x), YCOORD(p->y));
	    p = p->next;
	}
}

static void
put_picture(F_point *p, F_point *r, F_pic *pic)
{
	/*
	 * unflipped box, angle == 0:	    flipped, angle == 90:
	 *	point 1, p +-----------+ 2, q	     1 +------+ 4
	 *		   | .____     |	       | ...  |
	 *		   | :	       |	       | |    |
	 *		   |	       |	       | |    |
	 *	      s, 4 +-----------+ 3, r	       |      |
	 *					       |      |
	 *					       |      |
	 *					     2 +------+ 3
	 */
	int	n, dx, dy, rot = 0;
	char	*c;

	dx = r->x - p->x;
	dy = r->y - p->y;
	/* get the rotation, and write the height and width to dx and dy */
	if (dx < 0 && dy < 0) {
	    dx = -dx;
	    dy = -dy;
	    rot = 180;
	} else if (dx < 0 && dy >= 0) {
	    rot = dy;
	    dy = -dx;
	    dx = rot;
	    rot = 270;
	} else if (dy < 0 && dx >= 0) {
	    rot = dx;
	    dx = -dy;
	    dy = rot;
	    rot = 90;
	} /* else dx >= 0 && dy >= 0: rot = 0 */

	if (pic->flipped) {
	    rot += 90;
	    n = dx;
	    dx = dy;
	    dy = n;
	}

#define PREPEND prepend ? prepend : ""

	if (removesuffix) {
	    c = strrchr(pic->file,'.');
	    n =  c == NULL ? (int)strlen(pic->file) : c - pic->file;
	} else {
	    n = strlen(pic->file);
	}

/* A failed attempt to use \pgftext:
   \pgftext[top,left,at=\pgfqpoint{x}{y},rotate=%d]
     {\pgflowlevelob{pgftransformxscale=-1}{\pgfimage[height=,width=]{%s}}};
   Probably, the image is first flipped by xscale=-1 and only afterwards scaled
   to width and height. \pgftext does not allow a cannvas transformation, such
   as xscale=-1. */

/* \node[below right,rotate=90,xscale=-1] at (3,0) {\pgfimage[width=,heigth=]{g}};
   Order of rotate=90,xscale=-1 matters! */
	fputs("\\node[below right", tfp);
	if (rot != 0 && rot != 360)
	    fprintf(tfp, ",rotate=%d", rot);
	if (pic->flipped)
	    fputs(",xscale=-1", tfp);
	fprintf(tfp,	/* width and height must be given as dimen */
		"] at (%d,%d) {\\pgfimage[width=+%d\\XFigu,height=+%d\\XFigu]{%s%.*s}};\n",
		XCOORD(p->x), YCOORD(p->y), dx, dy, PREPEND, n, pic->file);
}

static void
set_width(int w)
{
	static int	cur_thickness = 0;
	int	l;
	double	v;

	if (w == cur_thickness)
	    return;
	cur_thickness = w;
	v = THICKNESS(w);
	if (v  == (int) v)
	    l = 0;
	else
	    l = 1;
	fprintf(tfp, "\\pgfsetlinewidth{+%.*f\\XFigu}\n", l, v);
}

static void
set_stipple(int s, double v)
{
	static int	cur_style = SOLID_LINE;
	static double	cur_styleval = 0.;
	int	l;

	if (s == cur_style && v == cur_styleval)
	    return;

	cur_style = s;
	cur_styleval = v;

	if (s == SOLID_LINE || v <= 0.) {
	    fputs("\\pgfsetdash{}{+0pt}\n", tfp);
	    if (v <= 0)
		cur_styleval = 0.;
	    return;
	}

	v *= ppi / 80.;
	switch (s) {
	case DASH_LINE:
	    l = round(v);
	    fprintf(tfp, "\\pgfsetdash{{+%d\\XFigu}{+%d\\XFigu}}{++0pt}\n", l, l);
	    break;
	case DOTTED_LINE:
	    l = round(ppi/80.);
	    fprintf(tfp, "\\pgfsetdash{{+%d\\XFigu}{+%d\\XFigu}}{+%d\\XFigu}\n",
		    l, round(v), l);
	    break;
	case DASH_DOT_LINE:
	    l = round(v*0.5);
	    fprintf(tfp,
		    "\\pgfsetdash{{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}}{+0pt}\n",
		    round(v), l, round(ppi/80.), l);
	    break;
	case DASH_2_DOTS_LINE:
	    l = round(ppi/80.);
	    fprintf(tfp,
		    "\\pgfsetdash{{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}}{+0pt}\n",
		    round(v), round(v*0.45), l, round(v*0.333), l, round(v*0.45));
	    break;
	case DASH_3_DOTS_LINE:
	    l = round(ppi/80.);
	    fprintf(tfp,
		    "\\pgfsetdash{{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}{+%d\\XFigu}}{+0pt}\n",
		    round(v), round(v*0.4), l, round(v*0.3),
		    l, round(v*0.3), l, round(v*0.4));
	    break;
	default:
	    fprintf(stderr,"Undefined line style %d.\n", s);
	}
}

static void
set_capstyle(int c)
{
	static int	cur_capstyle = 0;
	const char	*capcmd[] = {
		"\\pgfsetbuttcap\n",
		"\\pgfsetroundcap\n",
		"\\pgfsetrectcap\n"
	};

	if (c == cur_capstyle)
	    return;

	cur_capstyle = c;
	fputs(capcmd[c], tfp);
}

static void
set_joinstyle(int j)
{
	static int	cur_joinstyle = 0;
	const char	*joincmd[] = {
		"\\pgfsetmiterjoin\n",
		"\\pgfsetroundjoin\n",
		"\\pgfsetbeveljoin\n"
		/* pgfsetmiterlimit{miter limit factor} */
	};

	if (j == cur_joinstyle)
	    return;

	cur_joinstyle = j;
	fputs(joincmd[j], tfp);
}

static int
put_colorname(int c)
{
	if (c < NUM_STD_COLS)
	    return fputs(std_color[c+1].name, tfp);/* std_color[0] is DEFAULT */
	else
	    return fprintf(tfp, "xfigc%d", c);
}

/* Colors are set when they are declared and may stay active without being
 * needed, e.g., when using \pattern or \fill. Therefore, e.g.,
 *   \tikzset{every path/.style={draw=red}}
 * can not be used, because as a side effect all paths would also be drawn. */
static void
set_linecolor(int c)
{
	if (c == default_color)
	    c = DEFAULT;
	if (c == cur_pencolor)
	    return;

	cur_pencolor = c;
	fputs("\\pgfsetstrokecolor{", tfp);
	put_colorname(c);
	fputs("}\n", tfp);
}

static void
set_linefillcolor(int c)
{
	if (c == default_color)
	    c = DEFAULT;
	if (c == cur_pencolor && c == cur_fillcolor && cur_fillstyle == NUMSHADES - 1)
	    return;

	cur_pencolor = cur_fillcolor = c;
	cur_fillstyle = NUMSHADES - 1;
	fputs("\\pgfsetcolor{", tfp);
	put_colorname(c);
	fputs("}\n", tfp);
}

static void
set_fillcolor(int c, int s)
{
	if (c == default_color)
	    c = DEFAULT;
	if (c != cur_fillcolor || s != cur_fillstyle) {
	    cur_fillcolor = c;
	    cur_fillstyle = s;
	    fputs("\\pgfsetfillcolor{", tfp);
	    put_colorname(c);
	    /* A shade between 0 and NUMSHADES - 1 mixes the color with black,
	     * 0 = black, NUMSHADES - 1 = color at full saturation. Shades >
	     * NUMSHADE - 1 mix the color with white, i.e., tint the color. */
	    if (s == NUMSHADES - 1)
		fputs("}\n", tfp);
	    else if (s < NUMSHADES)
		fprintf(tfp, "!%d!black}\n", 100*s/(NUMSHADES-1));
	    else
		fprintf(tfp, "!%d}\n", 100*(NUMTINTS-s+NUMSHADES-1)/NUMTINTS);
	}
}

/*
 * Normalize fill colors: (i) A fully shaded color is black,
 * (ii) a fully tinted color is white.
 * Exception: Black. Shades of black are really tints. E.g., fully shaded
 * black is white. XFig treats the "default color" as black.
 * TODO: Do this in read.c!
 */
static void
normalize(int *fill_color, int *fill_style)
{
	if (*fill_style >= NUMSHADES + NUMTINTS || *fill_style == NUMSHADES - 1)
	    return;

	if (*fill_style == NUMSHADES + NUMTINTS - 1
		|| (*fill_color == WHITE_COLOR && *fill_style >= NUMSHADES - 1)) {
	    *fill_color = WHITE_COLOR;
	    *fill_style = NUMSHADES - 1;
	    return;
	} else if (*fill_color == WHITE_COLOR) { /* *fill_style < NUMSHADES - 1 */
	    *fill_color = BLACK_COLOR;
	    *fill_style += NUMSHADES - 1;
	} else if ((*fill_color == BLACK_COLOR || *fill_color == DEFAULT)
			&& *fill_style < NUMSHADES - 1) {
	    if (*fill_style == 0) {
		*fill_color = WHITE_COLOR;
		*fill_style = NUMSHADES - 1;
	    } else {
		*fill_style = NUMSHADES + NUMTINTS - 1 - *fill_style;
	    }
	} else if (*fill_style == 0) {
	    *fill_color = BLACK_COLOR;
	    *fill_style = NUMSHADES - 1;
	}
}

static void
set_pattern(int pen_color, int fill_style)
{
	if (pen_color == cur_patcolor && fill_style == cur_fillstyle)
	    return;

	cur_patcolor = pen_color;
	cur_fillstyle = fill_style;
	fprintf(tfp, "\\pgfsetfillpattern{xfigp%d}{",
		fill_style - NUMSHADES - NUMTINTS);
	put_colorname(pen_color);
	fputs("}\n", tfp);
}

#define	PUT_DRAWCMD(obj,has_endcaps,cap_style) \
	put_drawcmd(obj->style, obj->thickness, obj->pen_color, obj->fill_color, \
		    obj->fill_style, obj->style_val, has_endcaps, cap_style)

static void
put_drawcmd(int style, int thickness, int pen_color, int fill_color,
	    int fill_style, double style_val, bool has_endcaps, int cap_style)
{
#define	FILLED	fill_style > UNFILLED && fill_style < NUMSHADES + NUMTINTS
#define	PATTERN	fill_style >= NUMSHADES + NUMTINTS

	if (thickness > 0 ) {
	    if (has_endcaps || (style != SOLID_LINE && style_val > 0.))
		set_capstyle(cap_style);

	    set_width(thickness);
	    set_stipple(style, style_val);

	    if (FILLED) {
		normalize(&fill_color, &fill_style);
		if (fill_color == pen_color && fill_style == NUMSHADES-1) {
		    set_linefillcolor(pen_color);
		} else {
		    set_linecolor(pen_color);
		    set_fillcolor(fill_color, fill_style);
		}
		fputs("\\filldraw ", tfp);
	    } else if (PATTERN) {
		set_linecolor(pen_color);
		set_pattern(pen_color, fill_style);
		fputs("\\draw[pattern,preaction={fill=", tfp);
		put_colorname(fill_color);	/* TODO */
		fputs("}] ", tfp);
		/* if patterns without background color are possible:
#define	TRANSPARENT -2
		 * .. \draw[pattern
		 * if (fill_color == TRANSPARENT) fputs("] ", tfp); else {
		 *	fputs(", preaction={fill=", tfp; put_colorname(fill_color);
		 *	fputs("}] ", tfp); }	*/
	    } else {	/* UNFILLED */
		set_linecolor(pen_color);
		fputs("\\draw ", tfp);
	    }

	} else {	/* thickness <= 0 */

	    if (FILLED) {
		normalize(&fill_color, &fill_style);
		set_fillcolor(fill_color, fill_style);
		fputs("\\fill ", tfp);
	    } else if (PATTERN) {
		set_pattern(pen_color, fill_style);
		fputs("\\pattern[preaction={fill=", tfp);
		put_colorname(fill_color);	/* TODO */
		fputs("}] ", tfp);
		/* See above if for unfilled (TRANSPARENT) pattern fills. */
	    } else {	/* fill_style == UNFILLED */
		fputs("A non-existing object was processed. Please report this bug.\n",
			stderr);
	    }
	}
}

/* Return the settings s necessary to change the arrow-options
 * from o to those demanded by a, a_flags and a_props. */
static void
get_settings(F_arrow *a, int a_flags, int a_props, struct options o,
	     struct settings *s)
{
#define	UNSET	-1

	if (a->thickness != o.thickness)
	    s->thickness = a->thickness;
	else
	    s->thickness = UNSET;
	if (a_props & HAS_WIDTH && a->wid != o.wid)
	    s->wid = a->wid;
	else
	    s->wid = UNSET;
	if (a_props & HAS_LENGTH && a->ht != o.ht)
	    s->ht = a->ht;
	else
	    s->ht = UNSET;
	if (a_props & HAS_FILL &&
		(a_flags & HAS_FILL) != (o.flags & HAS_FILL)) {
	    s->setflags = HAS_FILL;
	    s->flags = a_flags & HAS_FILL;
	} else {
	    s->setflags = 0;
	    s->flags = 0;
	}
	if (a_props & HAS_SWAP &&
		(a_flags & HAS_SWAP) != (o.flags & HAS_SWAP)) {
	    s->setflags += HAS_SWAP;
	    s->flags += a_flags & HAS_SWAP;
	}
	if (s->thickness == UNSET && s->wid == UNSET && s->ht == UNSET
		&& s->setflags == 0)
	    s->has_options = false;
	else
	    s->has_options = true;
}

static struct options
combine(struct settings *s, struct options *o)
{
	struct options	c;

	if (s->has_options == false) {
	    c = *o;
	    return c;
	}

	if (s->thickness == UNSET)
	    c.thickness = o->thickness;
	else
	    c.thickness = s->thickness;
	if (s->wid == UNSET)
	    c.wid = o->wid;
	else
	    c.wid = s->wid;
	if (s->ht == UNSET)
	    c.ht = o->ht;
	else
	    c.ht = s->ht;
	if (s->setflags)
	    c.flags = s->flags | (o->flags & ~s->setflags);
	else
	    c.flags = o->flags;
	return c;
}

/* To care for \dimen in arrow options:
 * Default options set with \pgfsetarrows{[line width=30\\XFigu, ...]} do work, but
 * \pgfsetarrows{XFig0[line width=30\XFigu]-XFig11} does not work, must be
 * \pgfsetarrows{XFig0[line width=30*\the\XFigu]-XFig11}. Notably, as expected,
 * \pgfsetlinewidth{7.5\XFigu}, ..{+7.5\XFigu}, {7.5*\XFigu} and {7.5*\the\XFigu}
 * all work, but \pgfsetlinewidth{+7.5*\XFigu} does not.
 * All combinations with + in \pgfsetarrows do not work.
 * Options to specific arrows are only written by get_changes() below.
 */
/*
 * Print the default options, e.g., \pgfsetarrows{[width=3\XFigu, swap]}
 * demanded by a and a_open. Only the options which are different from the
 * current options must be printed.
 * Also, update default_options.
 */

static struct tikzarrow
create_arrow(F_arrow *a, struct options *o)
{
	struct tikzarrow t;

	t.type = arrowtype(a->type, a->style);
	t.props = pgfarrow[t.type].props;
	if (a->style && t.props & (HAS_FILL + HAS_SWAP))
	    t.flags = STYLE_MEANS_SWAP(t.type) ? HAS_SWAP : HAS_FILL;
	else
	    t.flags = 0;
	get_settings(a, t.flags, t.props, *o, &(t.s));

	return t;
}

/* Return the number of changed options. */
static int
changes(struct settings *s)
{
	int	n;

	if (s->thickness != UNSET)
	    n = 1;
	else
	    n = 0;
	if (s->wid != UNSET)
	    ++n;
	if (s->ht != UNSET)
	    ++n;
	if (s->setflags & HAS_FILL)
	    ++n;
	if (s->setflags & HAS_SWAP)
	    ++n;
	return n;
}

/* Return the set with minimum changes to the default options.
 * Return NULL if default_options can remain unchanged. */
static struct settings *
choose_default(int b_type, struct settings *b_s, int f_type, struct settings *f_s)
{
	int nb, nf;

	if (b_s->has_options == false)
	   if (f_s->has_options == false)
	       return NULL;
	   else
	       return b_s;
	else if (f_s->has_options == false)
	    return f_s;

	nb = changes(b_s);
	nf = changes(f_s);
	/* a shortcut TODO: is this really useful?*/
	if (nb == nf && b_s->setflags == f_s->setflags && b_type == f_type)
	    return b_s;
	if (nb < nf)
	    return b_s;
	if (nf < nb)
	    return f_s;
	if (b_s->setflags < f_s->setflags)
	    return b_s;
	if (f_s->setflags < b_s->setflags)
	    return f_s;
	if (b_s->flags < f_s->flags)
	    return b_s;
	if (f_s->flags < b_s->flags)
	    return f_s;
	if (f_type < b_type)
	    return f_s;
	return b_s;
}

/* Output the options string, including the square brackets;
 * Use "\XFigu" or "\the\XFigu", depending on whether the
 * boolean "the" is false or true.
 * Only call put_options() if s->has_options is true.		*/
static void
put_options(struct settings *s, bool the)
{
	bool	sep;
	char	*xfigu;

	if (the)
	    xfigu = "*\\the\\XFigu";
	else
	    xfigu = "\\XFigu";

	fputc('[', tfp);

	if (s->thickness != UNSET) {
	    double thk = THICKNESS(s->thickness);
	    fprintf(tfp,"line width=%.*f", PREC1(thk), thk);
	    fputs(xfigu, tfp);
	    sep = true;
	} else {
	    sep = false;
	}
	if (s->wid != UNSET) {
#define SEPARATOR   if (sep) fputs(", ", tfp); else sep = true
	    SEPARATOR;
	    fprintf(tfp, "width=%.0f", s->wid);
	    fputs(xfigu, tfp);
	}
	if (s->ht != UNSET) {
	    SEPARATOR;
	    fprintf(tfp, "length=%.0f", s->ht);
	    fputs(xfigu, tfp);
	}
	if (s->setflags) {
	    if (s->setflags & HAS_FILL) {
		SEPARATOR;
		fputs(arrowflag[s->flags & HAS_FILL], tfp);
	    }
	    if (s->setflags & HAS_SWAP) {
		if (sep)
		    fputs(", ", tfp);
		fputs(arrowflag[HAS_SWAP], tfp);	/* swap is a toggle switch */
	    }
	}
	fputc(']', tfp);
}

/* Assign the settings s to the options o. */
static void
assign_settings(struct settings *s, struct options *o)
{
	if (s->thickness != UNSET)
	    o->thickness = s->thickness;
	if (s->wid != UNSET)
	    o->wid = s->wid;
	if (s->ht != UNSET)
	    o->ht = s->ht;
	if (s->setflags)
	    o->flags = s->flags | (o->flags & ~s->setflags);
}

#define	NOARROW	    -1

static void
assign_arrow(struct tikzarrow *a, struct tikzarrow *o)
{
	o->type = a->type;
	if (a->type == NOARROW)
	    return;
	o->props = a->props;
	o->flags = a->flags;
	if (!(o->s.has_options = a->s.has_options))
	    return;
	o->s.thickness = a->s.thickness;
	o->s.wid = a->s.wid;
	o->s.ht = a->s.ht;
	if ((o->s.setflags = a->s.setflags) != 0)
	    o->s.flags = a->s.flags;
}

/* \pgfsetarrows{[width=...,length=...]} sets the default options for both
 * arrows. All other commands set the currently active arrow type, together with
 * its distinct set of options, if given, e.g.:
 *   \pgfsetarrows{<[length=8bp]-Latex} or
 *   \pgfsetarrowsstart{Latex[width=8bp,...]} */
static void
set_arrows(F_arrow *back, F_arrow *forw)
{
	static struct tikzarrow      cur_b = {NOARROW,0,0,{0,0.0,0.0,0.0,0,0}};
	static struct tikzarrow      cur_f = {NOARROW,0,0,{0,0.0,0.0,0.0,0,0}};
	struct tikzarrow    b, f;
	struct settings	    *d = NULL;
	bool		    set_back, set_forw;

	if (back && forw) {
	    b = create_arrow(back, &default_options);
	    /* a shortcut for back == forw */
	    if (back->type == forw->type && back->style == forw->style
		    && back->thickness == forw->thickness
		    && back->wid == forw->wid && back->ht == forw->ht) {
		d = &(b.s);
		f.type = b.type;
		f.props = b.props;
		f.flags = b.flags;
		f.s.has_options = false;
	    } else {
		f = create_arrow(forw, &default_options);
		d = choose_default(b.type, &(b.s), f.type, &(f.s));

		if (d != NULL) {
		    if (d == &(b.s))
			get_settings(forw, f.flags, f.props,
				     combine(&(b.s), &default_options), &(f.s));
		    else
			get_settings(back, b.flags, b.props,
				     combine(&(f.s), &default_options), &(b.s));
		}
	    }
	} else if (back) {
	    b = create_arrow(back, &default_options);
	    d = &(b.s);
	    f.type = NOARROW;
	} else if (forw) {
	    f = create_arrow(forw, &default_options);
	    d = &(f.s);
	    b.type = NOARROW;
	} else {
	    b.type = NOARROW;
	    f.type = NOARROW;
	}

	/* Output the command to set the default options,
	 * \pgfsetarrows{[...]} */
	if (d && d->has_options) {
	    fputs("\\pgfsetarrows{", tfp);
	    put_options(d, false);
	    fputs("}\n", tfp);
	    assign_settings(d, &default_options);
	    d->has_options=false;
	}

#define	OPTIONS_EQUAL(a,b)	a.has_options == b.has_options && \
		(a.has_options == false || (a.thickness == b.thickness \
			&& a.wid == b.wid && a.ht == b.ht \
			&& a.setflags == b.setflags && a.flags == b.flags))

	/* Which arrows must be set */
	if (!(b.type == NOARROW && cur_b.type == NOARROW)
		&& (b.type != cur_b.type
		    || b.s.has_options != cur_b.s.has_options
		    || (b.s.has_options && cur_b.s.has_options
			&& !(OPTIONS_EQUAL(b.s, cur_b.s))))) {
	    set_back = true;
	    assign_arrow(&b, &cur_b);
	} else {
	    set_back = false;
	}
	if (!(f.type == NOARROW && cur_f.type == NOARROW)
		&& (f.type != cur_f.type
		    || f.s.has_options != cur_f.s.has_options
		    || (f.s.has_options && cur_f.s.has_options
			&& !(OPTIONS_EQUAL(f.s, cur_f.s))))) {
	    set_forw = true;
	    assign_arrow(&f, &cur_f);
	} else {
	    set_forw = false;
	}

	/* Output the command to set the arrows */
	if (set_back || set_forw) {
	    fputs("\\pgfsetarrows", tfp);
	    if (!set_forw)
		fputs("start{", tfp);
	    else if (!set_back)
		fputs("end{", tfp);
	    else
		fputc('{', tfp);
	}

	if (set_back && b.type != NOARROW) {
		fprintf(tfp, "xfiga%d", b.type);
		if (b.s.has_options)
		    put_options(&(b.s), true);
	}

	if (set_back && set_forw)
	    fputc('-', tfp);

	if (set_forw && f.type != NOARROW) {
		fprintf(tfp, "xfiga%d", f.type);
		if (f.s.has_options)
		    put_options(&(f.s), true);
	}

	if (set_back || set_forw)
	    fputs("}\n", tfp);
}

void
gentikz_line(F_line *l)
{
	F_point		*p, *q;

	if (verbose)
	    fprintf(tfp, "%%\n%% Fig POLYLINE object\n%%\n");

	/* print any comments prefixed with "%" */
	print_comments("% ", l->comments, "");

	p = l->points;
	q = p->next;

	/* One or two points; Be strict, only draw a line if it is a POLYLINE. */
	if (p->next == NULL || q->next == NULL) {
	    if (l->thickness <= 0 || l->type != T_POLYLINE)
		return;
	    set_width(l->thickness);
	    set_linecolor(l->pen_color);
	    if (p->next == NULL) {	/* a single point */
		if (l->cap_style == ROUNDCAP) {
		    set_capstyle(l->cap_style);
		    fprintf(tfp, "\\draw (%d,%d);\n",
			    XCOORD(p->x), YCOORD(p->y));
		} else {
		    double	h;
		    set_capstyle(BUTTCAP);
		    set_arrows((F_arrow *) NULL, (F_arrow *) NULL);
		    h = THICKNESS(l->thickness)/2.;
		    fprintf(tfp, "\\draw (%d,%d)--(%d,%d);\n",
			    XCOORD(round(p->x - h)), YCOORD(p->y),
			    XCOORD(round(p->x + h)), YCOORD(p->y));
		}
	    } else { /* q->next == NULL, two points */
		set_capstyle(l->cap_style);
		set_stipple(l->style, l->style_val);
		set_arrows(l->back_arrow, l->for_arrow);
		fprintf(tfp, "\\draw (%d,%d)--(%d,%d);\n",
			XCOORD(p->x), YCOORD(p->y), XCOORD(q->x), YCOORD(q->y));
	    }
	    return;
	}
	/* three or more points, from here on below */

	/*--------------- genpict2e.c -------------------*/
	if (l->type == T_PIC_BOX) {
	    put_picture(p, q->next, l->pic);
	    return;
	}

	/* T_POLYLINE, T_BOX, T_POLYGON or T_ARC_BOX from here on below */
	if (l->thickness <= 0 && l->fill_style == UNFILLED &&
			!l->for_arrow && !l->back_arrow)
	    return;

	if (l->type == T_BOX || l->type == T_POLYGON || l->type == T_POLYLINE)
	    set_joinstyle(l->join_style);

	if (l->type == T_BOX || l->type == T_POLYGON || l->type == T_ARC_BOX) {
	    PUT_DRAWCMD(l, false, l->cap_style);

	    PUT_POINT(p);
	    if (l->type == T_POLYGON) {
		points_penultimate(q);
		fputs("--cycle;\n", tfp);
	    } else { /* l->type == T_BOX || l->type == T_ARC_BOX */
		if (l->type == T_ARC_BOX)
		    fprintf(tfp, " [rounded corners=+%d\\XFigu]", l->radius);
		fprintf(tfp, " rectangle (%d,%d);\n",
			XCOORD(q->next->x), YCOORD(q->next->y));
	    }
	} else { /* l->type == T_POLYLINE */
	    set_arrows(l->back_arrow, l->for_arrow);
	    PUT_DRAWCMD(l, true, l->cap_style);
	    PUT_POINT(p);
	    points_all(q);
	}
	/* fprintf(stderr, "Unknown line style %d. Please report this bug.\n", */
}

void
gentikz_spline(F_spline *s)
{
	print_comments("% ", s->comments, "");
	fprintf(stderr, "Can't generate spline; omitting object\n");
}

void
gentikz_ellipse(F_ellipse *e)
{
	if (verbose)
	    fputs("%%\n%% Fig ELLIPSE object\n%%\n", tfp);

	print_comments("% ", e->comments, "");

	if (e->thickness <= 0 && e->fill_style == UNFILLED) return;

	PUT_DRAWCMD(e, false, ROUNDCAP);

	if (e->radiuses.x == e->radiuses.y) {
	    fprintf(tfp, " (%d,%d) circle [radius=+%d];\n",
		    XCOORD(e->center.x), YCOORD(e->center.y), e->radiuses.x);
	} else {
	    fprintf(tfp, " (%d,%d) ellipse [x radius=+%d,y radius=+%d",
		    XCOORD(e->center.x), YCOORD(e->center.y), e->radiuses.x, e->radiuses.y);
	    if (e->angle != 0)
		fprintf(tfp, ",rotate=+%.0f];\n", e->angle * DEG_RAD);
	    else
		fputs("];\n", tfp);
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
		fprintf(tfp, "\\selectfont ");
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

/*
 * Put the text, e.g.,
 *   \pgfsetfillcolor{blue}   % \pgftext obeys \pgfsetfillcolor
 *   \pgftext[base,left,at=\pgfqpointxy{3}{2},rotate=45] {Text here!}
 * Order ist important! First at=..., then rotate=... !
 */
void
gentikz_text(F_text *t)
{
	unsigned char	*cp;

	if (verbose)
	    fprintf(tfp, "%%\n%% Fig TEXT object\n%%\n");

	/* print any comments prefixed with "%" */
	print_comments("% ", t->comments, "");

	set_fillcolor(t->color, NUMSHADES - 1);

	fputs("\\pgftext[base", tfp);
	switch (t->type) {
	case (T_LEFT_JUSTIFIED):
	    fputs(",left", tfp);
	    break;
	case (T_RIGHT_JUSTIFIED):
	    fputs(",right", tfp);
	}
	fprintf(tfp, ",at=\\pgfqpointxy{%d}{%d}",
		XCOORD(t->base_x), YCOORD(t->base_y));
	if(t->angle) {
	    double  a = t->angle*180/M_PI;
	    int	    aprec;
	    if (round(a*10) == round(a)*10)
		aprec = 0;
	    else
		aprec = 1;
	    fprintf(tfp, ",rotate=+%.*f", aprec, a);
	}
	fputs("] {", tfp);

	put_font(t);

	/* For Zapf Dingbats, some characters are written as \char%u, e.g.,
	 * \char35 instead of # (\char`\# would also be possible), otherwise
	 * latex interprets these characters.
	 * For latex-fonts, \char%u would not always work, because the
	 * appropriate glyphs are stored in different places (or even taken from
	 * a different font?). The characters \_`{} must be replaced by
	 * \textbackslash, \_, \`{}, \{ and \}.	*/
	if (t->font == MAX_PSFONT) /* && psfont_text(t) - true anyway */
	    for (cp = (unsigned char*)t->cstring; *cp; ++cp) {
		/* an excerpt from the ascii table:
		 *   35 #   36 $   37 %   38 &	 39 '	92 \  94 ^  95 _  96 `
		 *  123 {  125 }  126 ~
		 * pdftex and xetex or luatex treat chars > 127 differently -
		   therefore, for safety, also escape these
		   \#, \% and \& would also work */
		if (strchr("#$%&'\\^_`{}~", *cp) || *cp >= 125)
		    fprintf(tfp, "\\char%hhu", *cp);
		else
		    fputc(*cp, tfp);
	    }
	else if (!(special_text(t) || allspecial)) {
	    char *c;
	    /* This loop escapes characters "$&%#_{}" and "~^\". */
	    for (cp = (unsigned char*)t->cstring; *cp; ++cp) {
		if (strchr("$&%#_{}", *cp))
		    fputc('\\', tfp);
		if ((c = strchr("~^\\", *cp))) {
		    if (*c == '\\')
			fprintf(tfp,"\\textbackslash ");
		    else
			fprintf(tfp,"\\%c{}", *c);
		} else
		    fputc(*cp, tfp);
	    }
	} else for (cp = (unsigned char*)t->cstring; *cp; ++cp) {
#ifdef I18N
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
	fputs("}\n", tfp);
}

void
gentikz_arc(F_arc *a)
{
	int	preca;
	double	da, d, d1x, d1y, d2x, d2y;
	double	rad, angle1, angle2;

	if (verbose)
	    fprintf(tfp, "%%\n%% Fig ARC object\n%%\n");

	/* print any comments prefixed with "%" */
	print_comments("% ", a->comments, "");

	if (a->thickness <= 0 && a->fill_style == UNFILLED &&
			!a->for_arrow && !a->back_arrow)
	    return;

	/* compute the angles in tikz-coordinate system */
	d1x =  a->point[0].x - a->center.x;
	d1y =  a->point[0].y - a->center.y;
	d2x =  a->point[2].x - a->center.x;
	d2y =  a->point[2].y - a->center.y;
	angle1 = atan2(YDIR(d1y), XDIR(d1x)) * 180. / M_PI;
	angle2 = atan2(YDIR(d2y), XDIR(d2x)) * 180. / M_PI;
	rad = 0.5*(sqrt(d1x*d1x + d1y*d1y) + sqrt(d2x*d2x + d2y*d2y));
	/* how precise must the angle be given?  1/rad is the view angle of one pixel */
	da = 180.0 / M_PI / rad;
	preca = 0;
	for (d = 1.0; da < 1.0/d; d *= 10.) ++preca;

	/* direction == 0 clockwise, 1 counterclockwise */
	if (a->direction) {	/* counter-clockwise */
	    if (angle1 > angle2) {
		if (angle1 > 180.)
		    angle1 -= 360.;
		else
		    angle2 += 360.;
	    }
	} else {	/* !a->direction, clockwise */
	    if (angle1 < angle2) {
		if (angle1 > 180.)
		    angle2 -= 360.;
		else
		    angle1 += 360.;
	    }
	}

	if (a->thickness > 0 && a->type == T_PIE_WEDGE_ARC)
	    set_joinstyle(MITERJOIN);
	set_arrows(a->back_arrow, a->for_arrow);
	PUT_DRAWCMD(a, a->type != T_OPEN_ARC && !(a->for_arrow && a->back_arrow),
		a->cap_style);
	fprintf(tfp,
		"(%d,%d) arc[start angle=+%.*f, end angle=+%.*f, radius=+%.*f]",
		XCOORD(a->point[0].x), YCOORD(a->point[0].y), preca, angle1,
		preca, angle2, round(rad) == round(10.*rad)/10. ? 0 : 1, rad);
	if (a->type == T_PIE_WEDGE_ARC)
	    fprintf(tfp, "--(%.0f,%.0f)--cycle;\n",
		    XCOORD(a->center.x), YCOORD(a->center.y));
	else	/* T_OPEN_ARC or unknown */
	    fputs(";\n", tfp);
}

struct driver dev_tikz = {
	gentikz_option,
	gentikz_start,
	gentikz_grid,
	gentikz_arc,
	gentikz_ellipse,
	gentikz_line,
	gentikz_spline,
	gentikz_text,
	gentikz_end,
	INCLUDE_TEXT
};
