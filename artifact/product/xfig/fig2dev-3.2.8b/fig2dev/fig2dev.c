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
 * fig2dev.c: General Fig code translation program
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <locale.h>
/* In Windows, _setmode() is declared in <io.h>, O_BINARY in <fcntl.h>. It
 * accepts two arguments and sets file mode to text or binary. */
#ifdef HAVE__SETMODE
#include <io.h>
#include <fcntl.h>
#endif

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "alloc.h"
#include "bound.h"
#include "drivers.h"
#include "messages.h"
#include "read.h"

#ifndef HAVE_GETOPT
extern int	getopt(int argc, char *argv[], const char *ostr);
extern char	*optarg;
extern int	 optind;
#endif

const char	prog[] = PACKAGE_NAME;
char	*from = NULL, *to = NULL;
char	*name = NULL;
double	font_size = 0.0;
double	mag = 1.0;
double	fontmag = 1.0;
FILE	*tfp = NULL;

double	ppi;			/* Fig file resolution (e.g. 1200) */
int	llx = 0, lly = 0, urx = 0, ury = 0;
bool	landscape;
bool	center;
bool	multi_page = false;	/* multiple page option for PostScript */
bool	overlap = false;	/* overlap pages in multiple page output */
bool	orientspec = false;	/* set if the user specs. the orientation */
bool	centerspec = false;	/* set if the user specs. the justification */
bool	magspec = false;	/* set if the user specs. the magnification */
bool	transspec = false;	/* set if user specs. GIF transparent color */
bool	paperspec = false;	/* set if the user specs. the paper size (-z) */
bool	boundingboxspec = false;/* set if user specs. bounding box (-B or -R) */
bool	adjust_boundingbox = false; /* set if -K option was given */
bool	multispec = false;	/* set if the user specs. multiple pages */
bool	metric;			/* true if file specifies Metric */
bool	grayonly = false;	/* convert colors to grayscale (-N option) */
bool	bgspec = false;		/* flag to say -g was specified */
#ifdef I18N
bool support_i18n = false;
#endif
char	gif_transparent[]="\0"; /* GIF transp color hex name (e.g. #ff00dd) */
char	papersize[PAPERSZ_LEN];	/* paper size */
char	boundingbox[64];	/* boundingbox */
char	lang[12];		/* selected output language */
RGB	background;		/* background (if specified by -g) */
float	grid_minor_spacing = 0.0; /* grid minor spacing (if any) */
float	grid_major_spacing = 0.0; /* grid major spacing (if any) */
float	THICK_SCALE;		/* convert line thickness from screen resolution
					calculated in read_objects() */
char	gscom[1000];		/* to build up a command for ghostscript */

const char	*Fig_color_names[] = {	/* hex names for Fig colors */
	"#000000", "#0000ff", "#00ff00", "#00ffff",
	"#ff0000", "#ff00ff", "#ffff00", "#ffffff",
	"#000090", "#0000b0", "#0000d0", "#87ceff",
	"#009000", "#00b000", "#00d000", "#009090",
	"#00b0b0", "#00d0d0", "#900000", "#b00000",
	"#d00000", "#900090", "#b000b0", "#d000d0",
	"#803000", "#a04000", "#c06000", "#ff8080",
	"#ffa0a0", "#ffc0c0", "#ffe0e0", "#ffd700"
};
const struct paperdef paperdef[] = {
	{"Letter", 612, 792},		/*  8.5" x 11" */
	{"Legal", 612, 1008},		/*  8.5" x 14" */
	{"Tabloid", 792, 1224},		/*   11" x 17" */
	{"A",   612, 792},		/*  8.5" x 11" (letter) */
	{"B",   792, 1224},		/*   11" x 17" (tabloid) */
	{"C",  1224, 1584},		/*   17" x 22" */
	{"D",  1584, 2448},		/*   22" x 34" */
	{"E",  2448, 3168},		/*   34" x 44" */
	{"A9",  105, 148},		/*   37 mm x   52 mm */
	{"A8",  148, 210},		/*   52 mm x   74 mm */
	{"A7",  210, 297},		/*   74 mm x  105 mm */
	{"A6",  297, 420},		/*  105 mm x  148 mm */
	{"A5",  420, 595},		/*  148 mm x  210 mm */
	{"A4",  595, 842},		/*  210 mm x  297 mm */
	{"A3",  842, 1190},		/*  297 mm x  420 mm */
	{"A2", 1190, 1684},		/*  420 mm x  594 mm */
	{"A1", 1684, 2383},		/*  594 mm x  841 mm */
	{"A0", 2383, 3370},		/*  841 mm x 1189 mm */
	{"B10",  91,  127},		/*   32 mm x   45 mm */
	{"B9",  127,  181},		/*   45 mm x   64 mm */
	{"B8",  181,  258},		/*   64 mm x   91 mm */
	{"B7",  258,  363},		/*   91 mm x  128 mm */
	{"B6",  363,  516},		/*  128 mm x  182 mm */
	{"B5",  516,  729},		/*  182 mm x  257 mm */
	{"B4",  729, 1032},		/*  257 mm x  364 mm */
	{"B3", 1032, 1460},		/*  364 mm x  515 mm */
	{"B2", 1460, 2064},		/*  515 mm x  728 mm */
	{"B1", 2064, 2920},		/*  728 mm x 1030 mm */
	{"B0", 2920, 4127},		/* 1030 mm x 1456 mm */
	{NULL, 0, 0}
};

/* this should go into some data_read.h */
bool	pats_used, pattern_used[NUMPATTERNS];
bool	std_color_used[NUM_STD_COLS];
bool	arrows_used, arrow_used[NUMARROWS];

/* local */
struct obj_rec {
	void (*gendev)();
	char *obj;
	int depth;
};
static bool	maxdimspec = false; /* if max size of figure (-Z) was given */
static float	max_dimension;	/* max. dimension (-Z) of figure */
static float	mult;		/* multiplier for grid spacing */
static struct driver	*dev = NULL;
static int	depth_index = 0;
static char	depth_op;		/* '+' for skip all but those listed */

#define NUMDEPTHS 100
static struct depth_opts {
	int d1, d2;
} depth_opt[NUMDEPTHS + 1];

static char	Usage[] =
#ifdef I18N
"Usage:\n %1$s -hV\n %1$s -L language [-s size] [-m scale] [-j] [input [output]]\n";
#else
"Usage:\n %1$s -hV\n %1$s -L language [-s size] [-m scale] [input [output]]\n";
#endif

static int	 parse_gridspec(char *string, float *numer, float *denom,
				float *spacing, int *nchrs);
static void	 grid_usage(void);
static int	 gendev_objects(F_compound *objects, struct driver *dev);
static void	 help_msg(void);
static void	 depth_option(char *s);


/*
 * print comments to the output file preceded by string1 and
 * succeeded by string2
 */
void
print_comments(char *string1, F_comment *comment, char *string2)
{
	while (comment) {
		fprintf(tfp,"%s %s %s\n", string1, comment->comment, string2);
		comment = comment->next;
	}
}

/* all option letters must be in this string */
/* not in this string: HIJQUu and non-alphabetic chars */
#ifdef I18N
#define ARGSTRING	"AaB:b:C:cD:d:E:eFf:G:g:hi:jKkL:l:Mm:Nn:OoPp:q:R:rS:s:Tt:VvWwX:x:Y:y:Z:z:?"
#else
#define ARGSTRING	"AaB:b:C:cD:d:E:eFf:G:g:hi:KkL:l:Mm:Nn:OoPp:q:R:rS:s:Tt:VvWwX:x:Y:y:Z:z:?"
#endif

/* Options with `continue;' are not passed to drivers;
 * Therefore, only -L and -G remain to be cared for in drivers.
 * -L is needed in genepic and genmp while in genbitmaps, lang is used.
 * (TODO: either use lang in all, or -L in all)
 * -G is needed in genpstricks for an error message only */

void
get_args(int argc, char *argv[])
{
	int	 c, i, nvals, nchars;
	char	*grid, *p;
	float	 numer, denom;

	if (argc == 1) {
		fprintf(stderr, Usage, prog);
		exit(EXIT_SUCCESS);
	}

	/* print the version, for the comfort of the autotest tests */
	if (!strcmp(argv[1], "--version")) {
		printf("fig2dev Version %s\n", PACKAGE_VERSION);
		exit(EXIT_SUCCESS);
	}

	/* Guess an output driver from the last argument */
	if ((p = strrchr(argv[argc - 1], '.'))) {
		++p;
		for (i = 0; *drivers[i].name; ++i) {
			if (!strcmp(p, drivers[i].name) || (drivers[i].alias &&
						!strcmp(p, drivers[i].alias))) {
				strcpy(lang, drivers[i].name);
				dev = drivers[i].dev;
				dev->option('L', optarg);
				break;
			}
		}
	}


	/* sum of all arguments */
	while ((c = getopt(argc, argv, ARGSTRING)) != EOF) {

	  /* global (all drivers) option handling */
	    switch (c) {

	    case 'h':	/* print version message for -h too */
	    case 'V':
		printf("fig2dev Version %s\n", PACKAGE_VERSION);
		if (c == 'h')
		    help_msg();
		exit(0);
		break;

	    case 'D':	                /* depth filtering */
		depth_option(optarg);
		/* options with "continue" are not passed to the driver */
		continue;

	    case 'K':
		/* adjust bounding box according to selected depth range
		   given with '-D RANGE' option above */
		adjust_boundingbox = true;
		continue;

	    case 'G':			/* Grid */
		/* if major AND minor are specified */
		if ((p = strchr(optarg,':'))) {
		    /* parse minor grid spec first */
		    if (p != optarg) {
			if ((nvals=parse_gridspec(optarg, &numer, &denom,
					&grid_minor_spacing, &nchars)) == 2)
			    grid_minor_spacing = numer/denom;
		    }
		    /* now parse major grid spec */
		    if ((nvals=parse_gridspec(p+1, &numer, &denom,
				    &grid_major_spacing, &nchars)) == 2)
			grid_major_spacing = numer/denom;
		} else {
		    /* only minor grid specified */
		    if ((nvals=parse_gridspec(optarg, &numer, &denom,
				    &grid_minor_spacing, &nchars)) == 2)
			grid_minor_spacing = numer/denom;
		    p = optarg-1;
		}
		/* now parse any units after grid spacing */
		if ((size_t)nchars < strlen(p+1)) {
		    grid = p+nchars+1;
		    if ((strcmp(grid,"i") && strcmp(grid,"in") &&
					strcmp(grid,"inch") &&
				strcmp(grid,"f") && strcmp(grid,"ft") &&
					strcmp(grid,"feet") &&
				strcmp(grid,"c") && strcmp(grid,"cm") &&
				strcmp(grid,"mm") && strcmp(grid,"m") )) {
			grid_usage();
			grid_major_spacing = grid_minor_spacing = 0.0;
			break;
		    }
		    if (!strcmp(grid,"i") || !strcmp(grid,"in") ||
				!strcmp(grid,"in"))
			mult =  1.0;
		    else if (!strcmp(grid,"f") || !strcmp(grid,"ft") ||
				!strcmp(grid,"feet"))
			mult = 12.0;
		    else if (strcmp(grid,"c") == 0 || strcmp(grid,"cm") == 0)
			mult = 1.0/2.54;
		    else if (strcmp(grid,"mm") == 0)
			mult = 1.0/25.4;
		    else if (strcmp(grid,"m") == 0)
			mult = 1.0/0.0254;
		} else {
		    mult = 1.0;	/* no units, 1:1 */
		}
		break;	/* error message given in genpstricks.c */

	    case 'L':			/* set output language */
		/* save language for gen{gif,jpg,pcx,xbm,xpm,ppm,tif} */
		strncpy(lang, optarg, sizeof(lang)-1);
		lang[sizeof lang - 1] = '\0';
		/* override if a language already was set above */
		dev = NULL;
		for (i = 0; *drivers[i].name; ++i)
		    if (!strcmp(lang, drivers[i].name))
			dev = drivers[i].dev;
		if (!dev) {
		    fprintf(stderr,
			    "Unknown graphics language %s\n", lang);
		    fprintf(stderr,"Known languages are:\n");
		    /* display available languages - 23/01/90 */
		    for (i=0; *drivers[i].name; i++)
			fprintf(stderr,"%s ",drivers[i].name);
		    fprintf(stderr,"\n");
		    exit(1);
		}
		break;	/* needed in genepic.c, genmp.c */

	    case 'm':			/* set magnification */
		fontmag = mag = atof(optarg);
		magspec = true;		/* user-specified */
		continue;

	    case 's':			/* set default font size */
		font_size = atof(optarg);
		/* max size is checked in respective drivers */
		if (font_size <= 0.0)
		    font_size = DEFAULT_FONT_SIZE;
		continue;

	    case 'Z':			/* scale to requested size (inches/cm)*/
		maxdimspec = true;
		max_dimension = atof(optarg);
		continue;

#ifdef I18N
	    case 'j':
		support_i18n = true;
		continue;
#endif /* I18N */

	    case '?':			/* usage		*/
		fprintf(stderr,Usage,prog,prog);
		exit(1);
	    }

	    /* pass options through to driver */
	    if (!dev) {
		fprintf(stderr, "No graphics language specified.\n");
		exit(1);
	    }
	    dev->option(c, optarg);
	}
	/* adjust font size after option loop to make sure we have any -m first,
	   which affects fontmag */
	font_size = font_size * fontmag;

	if (!dev) {
		fprintf(stderr, "No graphics language specified.\n");
		exit(1);
	}

	/* make sure user doesn't specify both mag and max dimension */
	if (magspec && maxdimspec) {
		fputs("Must specify only one of -m (magnification) "
				"and -Z (max dimension).\n",
			stderr);
		exit(1);
	}

	if (optind < argc)
		from = argv[optind++];	/*  from file  */
	if (optind < argc)
		to   = argv[optind];	/*  to file    */
}

int
parse_gridspec(char *string, float *numer,float *denom, float *spacing,
		int *nchrs)
{
	int  numvals;

	if ((numvals=sscanf(string,"%f/%f%n",numer,denom,nchrs)) == 2) {
	    if (*numer < 0.0 || *denom < 0.0 || *denom == 0.0)
		return 0;
	    else
		return numvals;
	} else if ((numvals=sscanf(string,"%f%n",spacing,nchrs)) == 1) {
	    if (*spacing < 0.0 || *spacing == 0.0)
		return 0;
	    else
		return numvals;
	}

	grid_usage();
	return 0;
}

static void
grid_usage(void)
{
     fputs("Can't parse grid spec. Format is -G [minor_tick][:major_tick]unit ",
	     stderr);
     fputs("e.g. -G .5:2cm or -G 1/16:1/2in\n", stderr);
     fputs("Allowable units are: ", stderr);
     fputs("'i', 'in', 'ft', 'feet', 'c', 'cm', 'mm', 'm'.", stderr);
     fputs("  Ignoring grid.\n", stderr);
}

int
main(int argc, char *argv[])
{
	F_compound	objects;
	int		status;

	setlocale(LC_CTYPE, "");
#ifdef HAVE__SETMODE
	_setmode(1,O_BINARY); /* stdout is binary */
#endif

	/* get the options */
	get_args(argc, argv);

	/* read the Fig file */

	if (from && strcmp(from, "-"))
		status = read_fig(from, &objects);
	else
		status = readfp_fig(stdin, &objects);
	if (status != 0) {
		if (status == -3) {
			if (from && strcmp(from, "-"))
				err_msg("File \"%s\" is not accessible", from);
			else
				err_msg("Input error");
		}
		exit(EXIT_FAILURE);
	}

	/* multiply grid spacing by unit and scale to get FIG units */
	grid_minor_spacing = mult * grid_minor_spacing * ppi;
	grid_major_spacing = mult * grid_major_spacing * ppi;

	if (to == NULL || !strcmp(to, "-"))
		tfp = stdout;
	else {
		if (strcmp(to + strlen(to) - 4, ".fig") == 0 ){
			fprintf(stderr, "Outfile is a .fig file, aborting\n");
			exit(1);
		}
		if ((tfp = fopen(to, "wb")) == NULL) {
			fprintf(stderr, "Couldn't open %s\n", to);
			exit(1);
		}
	}

	/* Compute bounding box of objects, supressing texts if indicated */
	compound_bound(&objects, &llx, &lly, &urx, &ury, dev->text_include);

	/* make sure bounding box has width and height (if there is only latex
	   special text, it may be 0 width */
	if (urx-llx == 0)
		urx = llx + 100;
	if (ury-lly == 0)
		ury = lly + 100;

	/* if user has specified the maximum dimension,
	   adjust mag to produce that */
	if (maxdimspec) {
		float maxdim;

		if (metric)
			max_dimension /= 2.54;
		/* find larger of width and height */
		maxdim = MAX(urx - llx, ury - lly)/ppi;
		/* override any mag specified in the Fig file */
		mag = max_dimension/maxdim;
	}
	/*
	 * If metric, adjust scale for difference between FIG PIX/CM (450) and
	 * actual (472.44)
	 * NOTE: we don't adjust font sizes by this amount because they are in
	 * points, not inches or cm
	 */
	if (metric)
		mag *= 80.0/76.2;

	status = gendev_objects(&objects, dev);
	if ((tfp != stdout) && (tfp != 0))
		(void)fclose(tfp);
	exit(status);
}

void
help_msg(void)
{
	int i, n;

	fputs(	"General Options (all drivers):\n"
"  -L language	choose output language (this must be first, if the language\n"
"                cannot be inferrred from the suffix of the output file)\n"
"                Available languages are:\n"
"                   ",
		stdout);
	for (i = 0, n = 20; *drivers[i].name; ++i) {
		if (n > 72) {
			fputs("\n                   ", stdout);
			n = 20;
		}
		n += printf(" %s",drivers[i].name);
	}
	puts(
"\n  -h          print this message, fig2dev version number and exit\n"
"  -V          print fig2dev version number and exit\n"
"  -D +/-list  include or exclude depths listed\n"
"  -K          adjust bounding box according to selected depths\n"
"                      given with '-D +/-list' option.\n"
"  -G minor[:major][unit]    draw light gray grid with thin/thick lines at\n"
"                minor/major units (e.g., -G .25:1cm)\n"
#ifdef I18N
"  -j          enable i18n facility\n"
#endif
"  -m mag      set magnification.  This may not be used with the -Z option\n"
"  -s size     set default font size in points\n"
"  -Z maxdim   Scale the figure so that the maximum dimension (width or height)\n"
"                is maxdim inches/cm.  This may not be used with the -m option"
	);

	/* Vector formats */
	if (dev == NULL || !strcmp(lang, "cgm") || !strcmp(lang, "dxf") ||
			!strcmp(lang, "eepic") || !strcmp(lang, "eepicemu") ||
			!strcmp(lang, "emf") || !strcmp(lang, "epic") ||
			!strcmp(lang, "eps") || !strcmp(lang, "gbx") ||
			!strcmp(lang, "ibmgl") || !strcmp(lang, "latex") ||
			!strcmp(lang, "map") || !strcmp(lang, "mf") ||
			!strcmp(lang, "mp") || !strcmp(lang, "pdf") ||
			!strcmp(lang, "pdftex") || !strcmp(lang, "pdftex_t") ||
			!strcmp(lang, "pic") || !strcmp(lang, "pict2e") ||
			!strcmp(lang, "pictex") || !strcmp(lang, "ps") ||
			!strcmp(lang, "pstex") || !strcmp(lang, "pstex_t") ||
			!strcmp(lang, "pstricks") || !strcmp(lang, "ptk") ||
			!strcmp(lang, "shape") || !strcmp(lang, "svg") ||
			!strcmp(lang, "textyl") || !strcmp(lang, "tikz") ||
			!strcmp(lang, "tk") || !strcmp(lang, "tpic")) {
		puts(
"\n--------------------------------------------------------------------------------\n"
"Vector formats:");

		if (dev == NULL || !strcmp(lang, "cgm")) {
			puts(
"CGM Options:\n"
"  -a          call the ralcgm program to generate binary output\n"
"  -r          position arrowheads for CGM viewers that use rounded arrowheads"
			);
		}

		if (dev == NULL || !strcmp(lang, "dxf")) {
			puts(
"DXF Options:\n"
#ifdef A4
"  -a          select ANSI A paper size instead of the default ISO A4\n"
#else
"  -a          select ISO A4 paper size instead of the default ANSI A\n"
#endif
#ifdef IBMGEC
"  -c          generate instructions for IBM 6180 plotter without IBM-GEC\n"
#else
"  -c          generate instructions for IBM 6180 plotter with IBM-GEC\n"
#endif
"  -d xll,yll,xur,yur    restrict plotting to area specified by coords\n"
"  -f fontfile load text character specs from table in file\n"
"  -l pattfile load patterns for pattern fill from file\n"
"  -P          rotate figure to portrait (default is landscape)\n"
"  -p penfile  load plotter pen specs from file\n"
"  -v          print figure upside-down in portrait or backwards in landscape"
			);
		}

		if (dev == NULL || !strcmp(lang, "emf")) {
			puts(
"EMF Options:\n"
"  -l lang     set compatibility level to win95, win98 or winnt, default winnt\n"
"  -r          position arrowheads for EMF viewers that use rounded arrowheads"
			);
		}

		if (dev == NULL || !strcmp(lang,"eps") || !strcmp(lang,"pdf") ||
				!strcmp(lang,"pdftex") || !strcmp(lang,"pstex"))
			{
			puts(
"EPS, PDFTEX, PSTEX and PDF (if -P is not given) Options:\n"
"  -A          add ASCII preview (produce EPSI file; not for PDF output)\n"
"  -a          do not output user's login name (anonymous)\n"
"  -B \"Wx [Wy X0 Y0]\"    force width, height and origin in absolute coordinates\n"
"  -b width    specify width of blank border around figure (points, 1/72 inch)\n"
"  -C dummyarg add color TIFF preview (for Microsoft apps; not for PDF output)\n"
"  -F          use correct font sizes (points instead of 1/80inch)\n"
"  -f font     set default font\n"
"  -g color    set background color\n"
"  -N          convert all colors to grayscale\n"
"  -n name     set title part of PostScript output to name\n"
"  -R \"Wx [Wy X0 Y0]\"    force width, height and origin in relative\n"
"                coordinates (relative to lower-left of figure bounds)\n"
"  -T          add monochrome TIFF preview (for Microsoft apps; not for PDF)"
			);
		}

		if (dev == NULL || !strcmp(lang, "epic") ||
				!strcmp(lang, "eepic") ||
				!strcmp(lang, "eepicemu")) {
			puts(
"EPIC, EEPIC and EEPICEMU Options:\n"
"  -d scale    divide size of arrowheads by scale\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
#ifdef NFSS
"  -F          do not set font family, series or shape\n"
#endif /* NFSS */
"  -f font     set default font\n"
"  -l lwidth   use \"thicklines\" when width of line is > lwidth\n"
"  -P          generate a complete LaTeX file\n"
#ifdef NFSS
"  -R dummyarg allow rotated text (uses \\rotatebox)\n"
#endif /* NFSS */
"  -S scale    scale figure to scale/12, scale must be between 8 and 12\n"
"  -t stretch  set the stretch of dashed lines (default = 30)\n"
"  -v          include comments in the output\n"
"  -W          enable variable line width\n"
"  -w          disable variable line width"
			);
		}

		if (dev == NULL || !strcmp(lang, "gbx")) {
			puts(
"GBX (Gerber, RS-247-X) Options:\n"
"  -d [mm|in]  output dimensions assumed to be millimeters or inches\n"
"  -p [pos|neg]    image Polarity - positive results in lines being drawn,\n"
"                negative results in lines erasing background\n"
"  -g <x scale>x<y scale>+<x offset>+<y offset>    scale and shift output.\n"
"                Typically, use -g 1x-1+0+0, mirroring about the x axis.\n"
"  -f <n digits>.<n digits>    digits of precision before and\n"
"                after the implied decimal point.\n"
"  -v          include comments in the output"
			);
		}

		if (dev == NULL || !strcmp(lang, "ibmgl")) {
			puts(
"IBM-GL Options:\n"
#ifdef A4
"  -a          select ANSI A paper size instead of the default ISO A4\n"
#else
"  -a          select ISO A4 paper size instead of the default ANSI A\n"
#endif
#ifdef IBMGEC
"  -c          generate instructions for IBM 6180 plotter without IBM-GEC\n"
#else
"  -c          generate instructions for IBM 6180 plotter with IBM-GEC\n"
#endif
"  -d xll,yll,xur,yur    restrict plotting to area specified by coords\n"
"  -f fontfile load text character specs from table in file\n"
"  -k          precede output with PCL command to use HP/GL\n"
"  -l pattfile load patterns for pattern fill from file\n"
"  -P          rotate figure to portrait (default is landscape)\n"
"  -p penfile  load plotter pen specs from file\n"
"  -S speed    set pen speed in cm/sec\n"
"  -v          print figure upside-down in portrait or backwards in landscape\n"
"  -x offset   shift figure left by offset inches\n"
"  -y offset   shift figure up by offset inches"
			);
		}

		if (dev == NULL || !strcmp(lang, "latex")) {
			puts(
"LaTeX Options:\n"
"  -b width    specify width of blank border around figure (1/72 inch)\n"
"  -d dmag     set separate magnification for length of line dashes to dmag\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
#ifdef NFSS
"  -F          do not set font family/series/shape\n"
#endif
"  -f font     set default font\n"
"  -l lwidth   set threshold between thin and thick lines to lwidth\n"
"  -v          verbose mode"
			);
		}

		if (dev == NULL || !strcmp(lang, "map")) {
			puts(
"MAP (HTML image map) Options:\n"
"  -b width    specify width of blank border around figure (points, 1/72 inch)"
			);
		}

		if (dev == NULL || !strcmp(lang, "mf")) {
			puts(
"METAFONT Options:\n"
"  -C code     specifies the starting METAFONT font code\n"
"  -n name     name to use in the output file\n"
"  -p pen_mag  linewidth magnification compared to the original figure\n"
"  -t top      specifies the top of the coordinate system\n"
"  -x xmin     specifies minimum x coordinate of figure (inches)\n"
"  -y ymin     specifies minimum y coordinate of figure (inches)\n"
"  -X xmax     specifies maximum x coordinate of figure (inches)\n"
"  -Y xmax     specifies maximum y coordinate of figure (inches)"
			);
		}

		if (dev == NULL || !strcmp(lang, "mp")) {
			puts(
"METAPOST Options:\n"
"  -d file     add file content as additional header\n"
"  -i file     include file content via \\input-command\n"
"  -M          multipage, make one figure for each depth\n"
"  -o          old mode (no latex)\n"
"  -p number   add the line \"prologues:=number\""
			);
		}

		if (dev == NULL || !strcmp(lang, "pic")) {
			puts(
"PIC Options:\n"
"  -f font     set default font\n"
"  -p ext      enables certain PIC extensions (see man pages)");
		}

		if (dev == NULL || !strcmp(lang, "pictex")) {
			puts(
"PICTeX Options:\n"
"  -a          don't output user's login name (anonymous)\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
"  -f font     set default font\n"
"  -l dimen    set line thickness to TeX dimen\n"
"  -p symbol   set plot symbol (default \\tencirc\\symbol{'160})\n"
"  -r          do not use dvips"
			);
		}

		if (dev == NULL || !strcmp(lang, "pict2e")) {
			puts(
"PICT2E Options:\n"
"  -b width    specify width of blank border around figure (points, 1/72 inch)\n"
"  -C num      do not issue color commands for color num (0 = black,\n"
"                1 = blue, etc., see xfig color chooser)\n"
"  -e          do not try to be compatible with epic/eepic\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
"  -F          do not set font family/series/shape\n"
"  -f font     set default font\n"
"  -i dir      prepend the string \"dir\" to included graphics files\n"
"  -o          do not set the font size\n"
"  -O          do not quote characters special to TeX/LaTeX\n"
"                (effectively, set the text-flag \"special-text\" for all text)\n"
"  -P          pagemode, generate stand-alone LaTeX-file\n"
"  -R num      use LaTeX-arrows for arrow-type num\n"
"  -r          use LaTeX-arrows for all arrows\n"
"  -T          only use TeX fonts (even when PS-fonts are specified)\n"
"  -v          verbose mode, include comments in the output\n"
"  -w          remove suffix from included graphics-files"
			);
		}

		if (dev == NULL || !strcmp(lang,"ps") || !strcmp(lang,"pdf")) {
			puts(
"PostScript and PDF (if -P is given) Options:\n"
"  -A          add ASCII (EPSI) preview, not for PDF output\n"
"  -a          do not output user's login name (anonymous)\n"
"  -b width    specify width of blank border around figure (1/72 inch)\n"
"  -C dummyarg add color TIFF preview (for Microsoft apps), not for PDF output\n"
"  -c          center figure on page\n"
"  -e          put figure at left edge of page\n"
"  -F          use correct font sizes (points instead of 1/80inch)\n"
"  -f font     set default font\n"
"  -g color    set background color\n"
"  -l dummyarg landscape mode (dummy argument required after \"-l\")\n"
"  -M          generate multiple pages for large figure\n"
"  -N          convert all colors to grayscale\n"
"  -n name     set title part of PostScript output to name\n"
"  -O          overlap pages in multiple page mode (-M)\n"
"  -o          generate single page output\n"
"  -P          honor page size, do not crop to bounding box; PDF output only\n"
"  -p dummyarg portrait mode (dummy argument required after \"-p\")\n"
"  -T          add monochrome TIFF preview (for Microsoft apps), not for PDF\n"
"  -x offset   shift figure left/right by offset units (1/72 inch)\n"
"  -y offset   shift figure up/down by offset units (1/72 inch)\n"
"  -z papersize    set the papersize (see man pages for available sizes)"
			);
		}

		if (dev == NULL || !strcmp(lang, "pstricks")) {
			puts(
"PSTricks Options:\n"
"  -f fontname set default font\n"
"  -G dummyarg draw pstricks standard grid (sizes ignored)\n"
"  -l weight   set line weight factor 0 to 2.0 (default 0.5 matches PS driver)\n"
"  -M          generate multiple pages for large figure\n"
"  -N          convert all colors to grayscale\n"
"  -n mode     page mode (0, 1, 2, or 3)\n"
"  -O          overlap pages in multiple page mode (-M)\n"
"  -P          generate complete {document}; scale to fit one page\n"
"  -p dir      turn on auto picture conversion to EPS; dir is repository\n"
"  -R 0|1|2    arrow style (default 0 = Fig, 1 = PST with Fig sizes,\n"
"                 2 = PST default, ignore Fig sizes)\n"
"  -S scale    hard scale factor, scale must be between 8 and 12 inclusively\n"
"  -t version  set PSTricks version\n"
"  -v          verbose warnings and comments in output file\n"
"  -x marginsize    add margin on left and right (default is tight bounding box)\n"
"  -y marginsize    add margin on over and under (default is tight bounding box)\n"
"  -z 0|1|2    font handling (default 0=full, 1=size only, 2=none,PST default)\n"
"  -S dummyarg generate single page"
			);
		}

		if (dev == NULL || !strcmp(lang, "pstex_t") ||
				!strcmp(lang, "pdftex_t")) {
			puts(
"PSTEX_T and PDFTEX_T Options:\n"
"  -b width    specify width of blank border around figure (1/72 inch)\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
#ifdef NFSS
"  -F          do not set font family, series or shape, so you can\n"
"                set it from latex\n"
#endif /* NFSS */
"  -f font     set default font\n"
"  -p name     name of the PostScript or PDF file to be overlaid\n"
"  -v          verbose mode"
			);
		}

		if (dev == NULL || !strcmp(lang, "shape")) {
			puts(
"SHAPE (ShapePar driver) Options:\n"
"  -n name     Set basename of the macro\n"
"                (e.g. \"face\" gives faceshape and facepar)"
			);
		}

		if (dev == NULL || !strcmp(lang, "tk") || !strcmp(lang,"ptk")) {
			puts(
"Tcl/Tk (tk) and Perl/Tk (ptk) Options:\n"
"  -g color    set background color (Tcl/Tk only)\n"
"  -l dummyarg landscape mode (dummy argument required after \"-l\")\n"
"  -p dummyarg portrait mode (dummy argument required after \"-p\")\n"
"  -P          generate canvas of full page size instead of figure bounds\n"
"  -w          add wrapper to generate complete perl file\n"
"  -z papersize        set the papersize (see man pages for available sizes)"
			);
		}

		if (dev == NULL || !strcmp(lang, "tikz")) {
			puts(
"TIKZ Options:\n"
"  -b width    specify width of blank border around figure (1/72 inch)\n"
"  -C num      do not issue color commands for color num (0 = black,\n"
"                1 = blue, etc., see xfig color chooser)\n"
"  -E num      set encoding for text translation (0 = no translation,\n"
"                1 = ISO-8859-1, 2 = ISO-8859-2; default 1)\n"
"  -F          do not set font family/series/shape\n"
"  -i dir      prepend the string \"dir\" to included graphics files\n"
"  -O          do not quote characters special to TeX/LaTeX\n"
"                (effectively, set the text-flag \"special-text\" for all text)\n"
"  -o          do not set the font size\n"
"  -P          pagemode, generate stand-alone LaTeX-file\n"
"  -T          only use TeX fonts (even when PS-fonts are specified)\n"
"  -v          verbose mode, include comments in the output\n"
"  -W          disable code that enables scaling of figure from TeX file\n"
"  -w          remove suffix from included graphics-files"
			);
		}

		if (dev == NULL || !strcmp(lang, "textyl")) {
			puts(
"TEXTYL Options:\n"
"  -f font     set default font\n"
"  -l width    set line width, width must be between 1 and 12 inclusively"
			);
		}

		if (dev == NULL || !strcmp(lang, "tpic")) {
			puts(
"TPIC Options:\n"
"  -f font     set default font"
			);
		}
	} /* if vector formats */

	/* Bitmap formats */
	if (dev == NULL || !strcmp(lang, "gif") || !strcmp(lang, "jpeg") ||
			!strcmp(lang, "pcx") || !strcmp(lang, "png") ||
			!strcmp(lang, "ppm") || !strcmp(lang, "sld") ||
			!strcmp(lang, "tiff") || !strcmp(lang, "xbm") ||
			!strcmp(lang, "xpm")) {
		puts(
"\n--------------------------------------------------------------------------------\n"
"Bitmap formats:\nOptions common to all bitmap formats:\n"
"  -b width    specify width of blank border around figure (pixels)\n"
"  -F          use correct font sizes (points instead of 1/80inch)\n"
"  -g color    set background color\n"
"  -N          convert all colors to grayscale\n"
"  -S smooth   specify smoothing factor (1 = none, 2 = some, 4 = more)"
		);


		if (dev == NULL || !strcmp(lang, "gif"))
			puts(
"GIF Options:\n"
"  -t color    specify GIF transparent color in hexadecimal (e.g. #ff0000=red)"
			);

		if (dev == NULL || !strcmp(lang, "jpeg"))
			puts(
"JPEG Options:\n"
"  -q quality  specify image quality factor (0-100)"
			);
	}
}

/* count primitive objects & create pointer array */
static int compound_dump(F_compound *com, struct obj_rec *array,
			int count, struct driver *dev)
{
	F_arc		*a;
	F_compound	*c;
	F_ellipse	*e;
	F_line		*l;
	F_spline	*s;
	F_text		*t;

	for (c = com->compounds; c != NULL; c = c->next)
	  count = compound_dump(c, array, count, dev);
	for (a = com->arcs; a != NULL; a = a->next) {
	  if (array) {
		array[count].gendev = dev->arc;
		array[count].obj = (char *)a;
		array[count].depth = a->depth;
	  }
	  count += 1;
	}
	for (e = com->ellipses; e != NULL; e = e->next) {
	  if (array) {
		array[count].gendev = dev->ellipse;
		array[count].obj = (char *)e;
		array[count].depth = e->depth;
	  }
	  count += 1;
	}
	for (l = com->lines; l != NULL; l = l->next) {
	  if (array) {
		array[count].gendev = dev->line;
		array[count].obj = (char *)l;
		array[count].depth = l->depth;
	  }
	  count += 1;
	}
	for (s = com->splines; s != NULL; s = s->next) {
	  if (array) {
		array[count].gendev = dev->spline;
		array[count].obj = (char *)s;
		array[count].depth = s->depth;
	  }
	  count += 1;
	}
	for (t = com->texts; t != NULL; t = t->next) {
	  if (array) {
		array[count].gendev = dev->text;
		array[count].obj = (char *)t;
		array[count].depth = t->depth;
	  }
	  count += 1;
	}
	return count;
}

static int
rec_comp(struct obj_rec *r1, struct obj_rec *r2)
{
	return (r2->depth - r1->depth);
}

/*Modification Begin*/

int
write_objects(FILE *fp, F_compound objects)
{
    F_arc	   *a;
    F_compound	   *c;
    F_ellipse	   *e;
    F_line	   *l;
    F_spline	   *s;
    F_text	   *t;

    /*
     * A 2 for the orientation means that the origin (0,0) is at the upper
     * left corner of the screen (2nd quadrant).
     */

#ifdef I18N
    /* set the numeric locale to C so we get decimal points for numbers */
    setlocale(LC_NUMERIC, "C");
#endif  /* I18N */
    write_fig_header(fp);
    for (a = objects.arcs; a != NULL; a = a->next) {
	num_object++;
	write_arc(fp, a);
    }
    for (c = objects.compounds; c != NULL; c = c->next) {
	num_object++;
	write_compound(fp, c);
    }
    for (e = objects.ellipses; e != NULL; e = e->next) {
	num_object++;
	write_ellipse(fp, e);
    }
    for (l = objects.lines; l != NULL; l = l->next) {
	num_object++;
	write_line(fp, l);
    }
    for (s = objects.splines; s != NULL; s = s->next) {
	num_object++;
	write_spline(fp, s);
    }
    for (t = objects.texts; t != NULL; t = t->next) {
	num_object++;
	write_text(fp, t);
    }
#ifdef I18N
    /* reset to original locale */
    setlocale(LC_NUMERIC, "");
#endif  /* I18N */
    if (ferror(fp)) {
	fclose(fp);
	return (-1);
    }
    if (fclose(fp) == EOF)
	return (-1);


    return (0);
}
/*Modification End*/

int
gendev_objects(F_compound *objects, struct driver *dev)
{
	int	obj_count;
	int	status;
	struct	obj_rec *rec_array, *r;

	/* dump object pointers to an array */
	obj_count = compound_dump(objects, 0, 0, dev);
	if (!obj_count) {
	    fprintf(stderr, "fig2dev: No objects in Fig file\n");
	    return -1;
	}
	rec_array = (struct obj_rec *)malloc(obj_count*sizeof(struct obj_rec));
	(void)compound_dump(objects, rec_array, 0, dev);

	/* sort object array by depth */
	qsort(rec_array, obj_count, sizeof(struct obj_rec),
			(int (*)(const void *, const void *))rec_comp);

	/* generate header */
	(*dev->start)(objects);

	/* draw any grid specified */
	(*dev->grid)(grid_major_spacing, grid_minor_spacing);

	/* generate objects in sorted order */
	for (r = rec_array; r<rec_array+obj_count; r++)
	  if (depth_filter(r->depth))
	    (*(r->gendev))(r->obj);

	/* generate trailer */
	status = (*dev->end)();

	free(rec_array);

	return status;
}

/* null operations */
void
gendev_null(void)
{ ; }

void
gendev_nogrid(float major, float minor)
{
	(void)major;
	(void)minor;
}

/*
 * depth_options:
 *  +range[,range...]
 *  -range[,range...]
 *  where range is:
 *  d       include/exclude this depth
 *  d1:d2   include/exclude this range of depths
 */

static void
depth_usage(void)
{
    fprintf(stderr,"%s: help for -D option:\n",prog);
    fprintf(stderr,"  -D +rangelist  means keep only depths in rangelist.\n");
    fprintf(stderr,"  -D -rangelist  means keep all depths but those in rangelist.\n");
    fprintf(stderr,"  Rangelist can be a list of numbers or ranges of numbers, e.g.:\n");
    fprintf(stderr,"    10,40,55,60:70,99\n");
    exit(1);
}

void
depth_option(char *s)
{
	struct depth_opts *d;

	switch (depth_op = *s++) {
	case '+':
	case '-':
		break;
	default:
		depth_usage();
	}

	for (d = depth_opt; depth_index < NUMDEPTHS && *s; ++depth_index, d++) {
	    if (*s == ',') ++s;
	    d->d1 = d->d2 = -1;
	    d->d1 = strtol(s,&s,10);
	    if (d->d1 < 0)
		depth_usage();
	    switch(*s) {		/* what's the delim? */
	    case ':':			/* parse a range */
		d->d2 = strtol(s+1,&s,10);
		if (d->d2 < d->d1)
		    depth_usage();
		break;
	    case ',':			/* just start the next one */
		s++;
		break;
	    }
	}
	if (depth_index >= NUMDEPTHS) {
	    fprintf(stderr,"%s: Too many -D values!\n",prog);
	    exit(1);
	}
	d->d1 = -1;
}

int
depth_filter(int obj_depth)
{
	struct depth_opts *d;

	if (depth_index <= 0)		/* no filters were set up */
	    return 1;
	for (d = depth_opt; d->d1 >= 0; d++)
	    if (d->d2 >= 0) {		/* it's a range comparison */
		if (obj_depth >= d->d1 && obj_depth <= d->d2)
		    return (depth_op=='+')? 1:0;
	    } else {			/* it's a single-value comparison */
		if (d->d1 == obj_depth)
		    return (depth_op=='+')? 1:0;
	    }
	return (depth_op=='-')? 1:0;
}
