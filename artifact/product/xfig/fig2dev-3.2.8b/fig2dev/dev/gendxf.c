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
 *  gendxf.c: experimental dxf driver for fig2dev
 *
 *  Author: Oluf Bagger, Nokia Mobile Phones, March 2003 (ob@ieee.org)
 *
 *	  adapted from:
 *
 *  genibmgl.c:	IBMGL driver for fig2dev
 *		  IBM 6180 Color Plotter with
 *		  IBM Graphics Enhancement Cartridge
 *   Author E. Robert Tisdale, University of California, 1/92
 *  (edwin@cs.ucla.edu)
 *
 *	  adapted from:
 *
 *  genpictex.c:	PiCTeX driver for fig2dev
 *   Author Micah Beck, Cornell University, 4/88
 *  Color, rotated text and ISO-chars added by Herbert Bauer 11/91
 *  PCL job control option added Brian V. Smith 1/2001
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "localmath.h"
#include "messages.h"
#include "pi.h"

static void set_style(int style, double length);

#define FONTS		35
#define COLORS		8
#define PATTERNS	21
#define DPR		180.0/M_PI	/* degrees/radian */
#define DELTA		M_PI/36.0	/* radians */
#define POINT_PER_INCH	72.27		/* points/inch */
#define CMPP		254.0/7227.0	/* centimeters/point */
#define UNITS_PER_INCH	1016.0		/* plotter units/inch */
#define HEIGHT		7650.0		/* plotter units */
#define ISO_A4		10900.0		/* plotter units */
#define ANSI_A		10300.0		/* plotter units */
#define SPEED_LIMIT	128.0		/* centimeters/second */

#ifdef IBMGEC
static int	ibmgec = true;
#else
static int	ibmgec = false;
#endif

static bool	reflected = false;
static int	fonts = FONTS;
static int	colors = COLORS;
static int	patterns = PATTERNS;
static int	line_style = SOLID_LINE;
static int	fill_pattern = DEFAULT;
static double	dash_length = DEFAULT;		/* in pixels */
#ifdef A4
static double	pagelength = ISO_A4/UNITS_PER_INCH;
#else
static double	pagelength = ANSI_A/UNITS_PER_INCH;
#endif
static double	pageheight = HEIGHT/UNITS_PER_INCH;
static double	xl =  0.0;		/* inches */
static double	yl =  0.0;		/* inches */
static double	xu = 32.25;		/* inches */
static double	yu = 32.25;		/* inches */

static int	pen_number[] = { 1, 2, 3, 4, 5, 6, 7, 8, 1};
static double	pen_thickness[] = {.3,.3,.3,.3,.3,.3,.3,.3,.3};

static int	line_type[] =
	{1, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6,-1,-1,-1,-1,-1,-1,-1,-1};
static double	line_space[] =
	{.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.5,.3,.3};
static int	fill_type[] =
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 1, 2};
static double	fill_space[] =
	{.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1};
static double	fill_angle[] =
	{0,-45,0,45,90,-45,0,45,90,-45,0,45,90,-45,0,45,90, 0, 0, 0, 0};

static int	standard[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int	alternate[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static double	slant[] = { 0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0,10,
	0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0,10, 0, 0};
static double	wide[] = {.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,
	.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6,.6};
static double	high[] = {.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,
	.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8,.8};

static void
gendxf_option(char opt, char *optarg)
{
	// (void)	optarg;
	FILE	*ffp;
	int	font;
	int	pattern;

	switch (opt) {
	case 'a':				/* paper size */
#ifdef A4
		pagelength = ANSI_A/UNITS_PER_INCH;
#else
		pagelength = ISO_A4/UNITS_PER_INCH;
#endif
		break;

	case 'c':		/* Graphics Enhancement Cartridge emulation */
		ibmgec = !ibmgec;
		break;

	case 'd':				/* position and window, inches*/
		sscanf(optarg, "%lf,%lf,%lf,%lf", &xl,&yl,&xu,&yu);
		break;

	case 'f':				/* user's characters */
		if ((ffp = fopen(optarg, "r")) == NULL)
			fprintf(stderr, "Couldn't open %s\n", optarg);
		else
			for (font = 0; font <= fonts; ++font)
				fscanf(ffp, "%d%d%lf%lf%lf",
					&standard[font],  /* 0-4 6-9 30-39*/
					&alternate[font], /* 0-4 6-9 30-39*/
					&slant[font],	  /* degrees */
					&wide[font],	  /* ~1.0 */
					&high[font]);	  /* ~1.0 */
		fclose(ffp);
		break;

	case 'l':				/* user's fill patterns */
		if ((ffp = fopen(optarg, "r")) == NULL)
			fprintf(stderr, "Couldn't open %s\n", optarg);
		else
			for (pattern = 0; pattern < patterns; pattern++)
				fscanf(ffp, "%d%lf%d%lf%lf",
					&line_type[pattern],	/*  -1-6  */
					&line_space[pattern],	/* inches */
					&fill_type[pattern],	/*  1-5   */
					&fill_space[pattern],	/* inches */
					&fill_angle[pattern]);	/* degrees */
		fclose(ffp);
		break;

	case 'G':
	case 'L':				/* language */
		break;

	case 'p':				/* user's colors */
		{
			FILE	*ffp;
			int	color;
			if ((ffp = fopen(optarg, "r")) == NULL)
				fprintf(stderr, "Couldn't open %s\n", optarg);
			else
				for (color = 0; color <= colors; color++)
					fscanf(ffp, "%d%lf",
						&pen_number[color],    /* 1-8 */
						&pen_thickness[color]); /* mm */
			fclose(ffp);
		}
		break;

	case 'P':				/* portrait mode */
		landscape = false;
		orientspec = true; /* user-specified */
		break;

	case 'v':
		reflected = true;		/* mirror image */
		break;

	default:
		put_msg(Err_badarg, opt, "dxf");
		exit(1);
	}
}

static double	cpi;		/* cent/inch */
static double	cpp;		/* cent/pixel */
static double	hcmpp = CMPP;	/* centimeter/point */

void
gendxf_start(F_compound *objects)
{
	(void)	objects;

	if (fabs(mag) < 1.0/2048.0){
	    fprintf(stderr, "|mag| < 1/2048\n");
	    exit(1);
	    }

	if (xl < xu)
	    if (0.0 < xu)
		if (xl < pagelength) {
		    xl = (0.0 < xl) ? xl: 0.0;
		    xu = (xu < pagelength) ? xu: pagelength;
		    }
		else {
		    fprintf(stderr, "xll >= %.2f\n", pagelength);
		    exit(1);
		    }
	    else {
		fprintf(stderr, "xur <= 0.0\n");
		exit(1);
		}
	else {
	    fprintf(stderr, "xur <= xll\n");
	    exit(1);
	    }

	if (yl < yu)
	    if (0.0 < yu)
		if (yl < pageheight) {
		    yl = (0.0 < yl) ? yl: 0.0;
		    yu = (yu < pageheight) ? yu: pageheight;
		    }
		else {
		    fprintf(stderr, "yll >= %.2f\n", pageheight);
		    exit(1);
		    }
	    else {
		fprintf(stderr, "yur <= 0.0\n");
		exit(1);
		}
	else {
	    fprintf(stderr, "yur <= yll\n");
	    exit(1);
	    }

	cpi = mag*100.0/sqrt((xu-xl)*(xu-xl) + (yu-yl)*(yu-yl));
	cpp = cpi/ppi;

	/* dxf start */
	fprintf(tfp, "	0\nSECTION\n  2\nHEADER\n");
	fprintf(tfp, "	0\nENDSEC\n");

	fprintf(tfp, "999\n generated by gen_dxf v0.03\n");

	fprintf(tfp, "	0\nSECTION\n  2\nTABLES\n");
	fprintf(tfp, "	0\nTABLE\n");
	fprintf(tfp, "	2\nVPORT\n");
	fprintf(tfp, "	70\n	 0\n");
	fprintf(tfp, "	0\nENDTAB\n");
	fprintf(tfp, "	0\nTABLE\n");
	fprintf(tfp, "	2\nLTYPE\n");
	fprintf(tfp, "	70\n	 7\n");

	fprintf(tfp, "	0\nLTYPE\n");		/* xfig Solid Line */
	fprintf(tfp, "	2\nSolid\n");		/* Line-type name */
	fprintf(tfp, "	70\n	 0\n");
	fprintf(tfp, "	3\nSolid line\n");	/* Description */
	fprintf(tfp, "	72\n	65\n");		/* Adjustment code */
	fprintf(tfp, "	73\n	 0\n");		/* Number of vertices */
	fprintf(tfp, "	40\n0.0\n");		/* Total Patern length */

	fprintf(tfp, "	0\nLTYPE\n");		/* xfig Solid Line */
	fprintf(tfp, "	2\nDashed\n");		/* Line-type name */
	fprintf(tfp, "	70\n	64\n");
						/* Description */
	fprintf(tfp, "	3\n__ __ __ __ __ __ __ __ __ __ __ __ __ __ __\n");
	fprintf(tfp, "	72\n	65\n");		/* Adjustment code */
	fprintf(tfp, "	73\n	 2\n");		/* Number of vertices */
	fprintf(tfp, "	40\n0.75\n");		/* Total Patern length */
	fprintf(tfp, "	49\n0.5\n");		/* Line Length */
	fprintf(tfp, "	49\n-0.25\n");		/* Line Length */

	fprintf(tfp, "	0\nLTYPE\n");		/* xfig Solid Line */
	fprintf(tfp, "	2\nDotted\n");		/* Line-type name */
	fprintf(tfp, "	70\n	64\n");
						/* Description */
	fprintf(tfp, "	3\n. . . . . . . . . . . . . . . . . . . . . .\n");
	fprintf(tfp, "	72\n	65\n");		/* Adjustment code */
	fprintf(tfp, "	73\n	 2\n");		/* Number of vertices */
	fprintf(tfp, "	40\n0.25\n");		/* Total Patern length */
	fprintf(tfp, "	49\n0.0\n");		/* Line Length */
	fprintf(tfp, "	49\n-0.25\n");		/* Line Length */

	fprintf(tfp, "	0\nLTYPE\n");		/* xfig Solid Line */
	fprintf(tfp, "	2\nDashdot\n");		/* Line-type name */
	fprintf(tfp, "	70\n	64\n");
						/* Description */
	fprintf(tfp, "	3\n__ . __ . __ . __ . __ . __ . __ . __ . __ .\n");
	fprintf(tfp, "	72\n	65\n");		/* Adjustment code */
	fprintf(tfp, "	73\n	 4\n");		/* Number of vertices */
	fprintf(tfp, "	40\n1.0\n");		/* Total Patern length */
	fprintf(tfp, "	49\n0.5\n");		/* Line Length */
	fprintf(tfp, "	49\n-0.25\n");		/* Line Length */
	fprintf(tfp, "	49\n0.0\n");		/* Line Length */
	fprintf(tfp, "	49\n-0.25\n");		/* Line Length */

	fprintf(tfp, "	0\nENDTAB\n");
	fprintf(tfp, "	0\nENDSEC\n");
	fprintf(tfp, "	0\nSECTION\n  2\nBLOCKS\n");
	fprintf(tfp, "	0\nENDSEC\n");
	fprintf(tfp, "	0\nSECTION\n  2\nENTITIES\n");

	if (!landscape) {			 /* portrait mode */
	    if (reflected)			  /* upside-down text */
		hcmpp	= -hcmpp;
	}

}

/*	  draw arrow heading from (x1, y1) to (x2, y2) */

static void
draw_arrow_head(double x1, double y1, double x2, double y2)
{
	int style;
	double length;

	/* save line style and set to solid */
	style = line_style;
	length = dash_length;
	set_style(SOLID_LINE, 0.0);

	fprintf(tfp, "999\nPrint an arrow from (%f;%f) to (%f;%f)\n",
		x1, y1, x2, y2);

	/* restore line style */
	set_style(style, length);
	}

/*
 * set_style - issue line style commands as appropriate
 */
static void
set_style(int style, double length)
{
	if (style == line_style)
	    switch (line_style) {
		case SOLID_LINE:
		    break;

		case DASH_LINE:
		    if (dash_length != length && length > 0.0) {
			dash_length = length;
			fprintf(tfp, "LT2,%.4f;\n", dash_length*2.0*cpp);
			}
		    break;

		case DOTTED_LINE:
		    if (dash_length != length && length > 0.0) {
			dash_length = length;
			fprintf(tfp, "LT1,%.4f;\n", dash_length*2.0*cpp);
			}
		    break;
		}
	else {
	    line_style = style;
	    switch (line_style) {
		case SOLID_LINE:
		    fprintf(tfp, "LT;\n");
		    break;

		case DASH_LINE:
		    if (dash_length != length && length > 0.0)
			dash_length = length;
		    if (dash_length > 0.0)
			fprintf(tfp, "LT2,%.4f;\n", dash_length*2.0*cpp);
		    else
			fprintf(tfp, "LT2,-1.0;\n");
		    break;

		case DOTTED_LINE:
		    if (dash_length != length && length > 0.0)
			dash_length = length;
		    if (dash_length > 0.0)
			fprintf(tfp, "LT1,%.4f;\n", dash_length*2.0*cpp);
		    else
			fprintf(tfp, "LT1,-1.0;\n");
		    break;
		}
	    }
}

/*
 * set_width - issue line width commands as appropriate
 *		  NOTE: for HP plotters we can't do anything
 */
/*
static void
set_width(int w)
{
}
*/

static void
fill_polygon(int pattern)
{
	if (0 < pattern && pattern < patterns) {
	    int		       style;
	    double	  length;

	    if (fill_pattern != pattern) {
		fill_pattern  = pattern;
		fprintf(tfp, "FT%d,%.4f,%.4f;", fill_type[pattern],
			fill_space[pattern],
			reflected ? -fill_angle[pattern]: fill_angle[pattern]);
		}
	    /*	  save line style */
	    style	  = line_style;
	    length	   = dash_length;
	    fprintf(tfp, "LT%d,%.4f;FP;\n",
		    line_type[pattern], line_space[pattern]*cpi);
	    /* restore line style */
	    line_style	       = DEFAULT;
	    dash_length		= DEFAULT;
	    set_style(style, length);
	    }
}

void
dxf_arc(double sx, double sy, double cx, double cy, double theta, double delta)
{
  fprintf(tfp, "999\n !! found dxf_arc\n");
  if (1 == 0) {
	if (ibmgec)
	    if (delta == M_PI/36.0)		   /* 5 degrees */
		fprintf(tfp, "AA%.4f,%.4f,%.4f;",
			cx, cy, theta*DPR);
	    else
		fprintf(tfp, "AA%.4f,%.4f,%.4f,%.4f;",
			cx, cy, theta*DPR, delta*DPR);
	else {
	    double	  alpha;
	    if (theta < 0.0)
		delta = -fabs(delta);
	    else
		delta = fabs(delta);
	    for (alpha = delta; fabs(alpha) < fabs(theta); alpha += delta) {
		fprintf(tfp, "PA%.4f,%.4f;\n",
			    cx + (sx - cx)*cos(alpha) - (sy - cy)*sin(alpha),
			    cy + (sy - cy)*cos(alpha) + (sx - cx)*sin(alpha));
		}
	    fprintf(tfp, "PA%.4f,%.4f;\n",
			cx + (sx - cx)*cos(theta) - (sy - cy)*sin(theta),
			cy + (sy - cy)*cos(theta) + (sx - cx)*sin(theta));
	    }
  }
}

void
gendxf_arc(F_arc *a)
{
  fprintf(tfp, "999\n !! found gendxf_arc\n");
  if (1 == 0) {
	if (a->thickness != 0 ||
		(ibmgec && 0 <= a->fill_style && a->fill_style < patterns)) {
	    double	  x, y;
	    double	  cx, cy, sx, sy, ex, ey;
	    double	  dx1, dy1, dx2, dy2, theta;


	    set_style(a->style, a->style_val);
/*	    set_width(a->thickness);	*/

	    cx = a->center.x/ppi;
	    cy = a->center.y/ppi;
	    sx = a->point[0].x/ppi;
	    sy = a->point[0].y/ppi;
	    ex = a->point[2].x/ppi;
	    ey = a->point[2].y/ppi;

	    dx1 = sx - cx;
	    dy1 = sy - cy;
	    dx2 = ex - cx;
	    dy2 = ey - cy;

	    theta = atan2(dy2, dx2) - atan2(dy1, dx1);
	    if (a->direction) {
		if (theta > 0.0)
		    theta -= 2.0*M_PI;
	    } else {
		if (theta < 0.0)
		    theta += 2.0*M_PI;
	    }

	    if (a->type == T_OPEN_ARC && a->thickness != 0 && a->back_arrow) {
		arc_tangent(cx, cy, sx, sy, !a->direction, &x, &y);
		draw_arrow_head(x, y, sx, sy);
		}

	    fprintf(tfp, "PA%.4f,%.4f;PM;PD;", sx, sy);
	    dxf_arc(sx, sy, cx, cy, theta, DELTA);
	    fprintf(tfp, "PU;PM2;\n");

	    if (a->thickness != 0)
		fprintf(tfp, "EP;\n");

	    if (a->type == T_OPEN_ARC && a->thickness != 0 && a->for_arrow) {
		arc_tangent(cx, cy, ex, ey, a->direction, &x, &y);
		draw_arrow_head(x, y, ex, ey);
		}

	    if (0 < a->fill_style && a->fill_style < patterns)
		fill_polygon(a->fill_style);
	    }
  }
}

void
gendxf_ellipse(F_ellipse *e)
{
  /* This is a quick fix to use polylines rather than dxf ellipses */
  /* This might be a compatibility option also in the future. */
  if (e->thickness != 0 ||
	    (ibmgec && 0 <= e->fill_style && e->fill_style < patterns)) {
    int		       j;
    double	  alpha;
    double	  angle;
    double	  delta;
    double	  x0, y0;
    double	  a,  b;
    double	  x,  y;

    set_style(e->style, e->style_val);
/*    set_width(e->thickness);	*/

    a	  = e->radiuses.x/ppi;
    b	  = e->radiuses.y/ppi;
    x0	  = e->center.x/ppi;
    y0	  = e->center.y/ppi;
    angle = -e->angle;
    delta = -DELTA;

    x = x0 + cos(angle)*a;
    y = y0 + sin(angle)*a;

    fprintf(tfp, "999\n !! found ellipse\n");

    fprintf(tfp, "  0\nPOLYLINE\n");
    fprintf(tfp, "  6\nSolid\n");
    fprintf(tfp, "  8\n%3i\n",e->depth);
    fprintf(tfp, " 66\n1\n");
    fprintf(tfp, " 62\n%6i\n",e->pen_color);
    fprintf(tfp, " 10\n0.0\n");
    fprintf(tfp, " 20\n0.0\n");
    fprintf(tfp, " 30\n0.0\n");
    fprintf(tfp, " 70\n  1\n");

    for (j = 1; j <= 72; j++) {
      alpha = j*delta;
      x     = x0 + cos(angle)*a*cos(alpha) - sin(angle)*b*sin(alpha);
      y     = y0 + sin(angle)*a*cos(alpha) + cos(angle)*b*sin(alpha);
      fprintf(tfp, "  0\nVERTEX\n");
      fprintf(tfp, "  8\n%3i\n",e->depth);
      fprintf(tfp, "  6\nSolid\n");
      fprintf(tfp, " 10\n%f\n",x);
      fprintf(tfp, " 20\n%f\n",y);
      fprintf(tfp, " 30\n0.0\n");
      fprintf(tfp, " 70\n  0\n");
    }
    fprintf(tfp, "  0\nSEQEND\n");
  }
}

void
gendxf_line(F_line *l)
{
  if (l->thickness != 0 || (ibmgec && 0 <= l->fill_style &&
					l->fill_style < patterns))
  {
    F_point	   *p, *q, *r;

    set_style(l->style, l->style_val);
/*    set_width(l->thickness);	*/

    p = l->points;
    q = p->next;

    switch (l->type) {
      case	  T_POLYLINE:
      case	  T_POLYGON:
      case	  T_BOX:
	switch (l->type) {
	  case	      T_POLYLINE:
	    fprintf(tfp, "999\n !! found polyline\n");
	    break;
	  case	      T_POLYGON:
	    fprintf(tfp, "999\n !! found polygon\n");
	    break;
	  case	      T_BOX:
	    fprintf(tfp, "999\n !! found box\n");
	    break;
	}
	if (q == NULL) {	  /* A single point line */
	  fprintf(tfp, "  0\nPOINT\n");
	  fprintf(tfp, "  8\n%3i\n",l->depth);
	  fprintf(tfp, "  6\nSolid\n");
	  fprintf(tfp, " 62\n%6i\n",l->pen_color);
	  fprintf(tfp, " 10\n%f\n",p->x/ppi);
	  fprintf(tfp, " 20\n%f\n",p->y/ppi);
	} else {
	  if (l->thickness != 0 && l->back_arrow)
	      draw_arrow_head(q->x/ppi, q->y/ppi, p->x/ppi, p->y/ppi);

	  fprintf(tfp, "  0\nPOLYLINE\n");
	  fprintf(tfp, "  6\nSolid\n");
	  fprintf(tfp, "  8\n%3i\n",l->depth);
	  fprintf(tfp, " 66\n1\n");
	  fprintf(tfp, " 62\n%6i\n",l->pen_color);
	  fprintf(tfp, " 10\n0.0\n");
	  fprintf(tfp, " 20\n0.0\n");
	  fprintf(tfp, " 30\n0.0\n");
	  if (l->type == T_POLYLINE) {
	    fprintf(tfp, " 70\n  0\n");
	  } else {
	    fprintf(tfp, " 70\n  1\n");
	  }

	  r = q = p;
	  while (p != NULL) {
	    fprintf(tfp, "  0\nVERTEX\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, " 10\n%f\n",p->x/ppi);
	    fprintf(tfp, " 20\n%f\n",p->y/ppi);
	    fprintf(tfp, " 30\n0.0\n");
	    fprintf(tfp, " 70\n  0\n");
	    r = q;
	    q = p;
	    p = p->next;
	  }

	  if (l->thickness != 0 && l->for_arrow)
	    draw_arrow_head(r->x/ppi, r->y/ppi, q->x/ppi, q->y/ppi);

/*	  if (0 < l->fill_style && l->fill_style < patterns)
	    fill_polygon((int)l->fill_style, l->fill_color);	*/

	  fprintf(tfp, "  0\nSEQEND\n");
	}
	break;

      case	  T_ARC_BOX: {
	  int		     llx, lly, urx, ury;
	  double	 x0,  y0,  x1,	y1;
	  double	dx, dy;

	  llx	      = urx	   = p->x;
	  lly	      = ury	   = p->y;
	  while ((p = p->next) != NULL) {
	    if (llx > p->x) llx = p->x;
	    if (urx < p->x) urx = p->x;
	    if (lly > p->y) lly = p->y;
	    if (ury < p->y) ury = p->y;
	  }

	  x0 = llx/ppi;
	  x1 = urx/ppi;
	  dx = l->radius/ppi;
	  y0 = ury/ppi;
	  y1 = lly/ppi;
	  dy = -dx;

	  fprintf(tfp, "999\n !! found arc-box\n");

	  if (q == NULL) {	    /* A single point line */
	    fprintf(tfp, "  0\nPOINT\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, " 62\n%6i\n",l->pen_color);
	    fprintf(tfp, " 10\n%f\n",p->x/ppi);
	    fprintf(tfp, " 20\n%f\n",p->y/ppi);
	  } else {
	    fprintf(tfp, "  0\nLINE\n");
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, " 66\n1\n");
	    fprintf(tfp, " 62\n%6i\n",l->pen_color);
	    fprintf(tfp, " 10\n%f\n",x0);
	    fprintf(tfp, " 20\n%f\n",y0 + dy);
	    fprintf(tfp, " 11\n%f\n",x0);
	    fprintf(tfp, " 21\n%f\n",y1 - dy);

	    fprintf(tfp, "  0\nLINE\n");
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, " 66\n1\n");
	    fprintf(tfp, " 62\n%6i\n",l->pen_color);
	    fprintf(tfp, " 10\n%f\n",x1);
	    fprintf(tfp, " 20\n%f\n",y0 + dy);
	    fprintf(tfp, " 11\n%f\n",x1);
	    fprintf(tfp, " 21\n%f\n",y1 - dy);

	    fprintf(tfp, "  0\nLINE\n");
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, " 66\n1\n");
	    fprintf(tfp, " 62\n%6i\n",l->pen_color);
	    fprintf(tfp, " 10\n%f\n",x0 + dx);
	    fprintf(tfp, " 20\n%f\n",y0);
	    fprintf(tfp, " 11\n%f\n",x1 - dx);
	    fprintf(tfp, " 21\n%f\n",y0);

	    fprintf(tfp, "  0\nLINE\n");
	    fprintf(tfp, "  6\nSolid\n");
	    fprintf(tfp, "  8\n%3i\n",l->depth);
	    fprintf(tfp, " 66\n1\n");
	    fprintf(tfp, " 62\n%6i\n",l->pen_color);
	    fprintf(tfp, " 10\n%f\n",x0 + dx);
	    fprintf(tfp, " 20\n%f\n",y1);
	    fprintf(tfp, " 11\n%f\n",x1 - dx);
	    fprintf(tfp, " 21\n%f\n",y1);


	  }

/*
 *	  fprintf(tfp, "PA%.4f,%.4f;PM;PD;\n",	x0, y0 + dy);
 *	  dxf_arc(x0, y0 + dy, x0 + dx, y0 + dy, angle, DELTA);
 *	  fprintf(tfp, "PA%.4f,%.4f;\n", x1 - dx, y0);
 *	  dxf_arc(x1 - dx, y0, x1 - dx, y0 + dy, angle, DELTA);
 *	  fprintf(tfp, "PA%.4f,%.4f;\n", x1, y1 - dy);
 *	  dxf_arc(x1, y1 - dy, x1 - dx, y1 - dy, angle, DELTA);
 *	  fprintf(tfp, "PA%.4f,%.4f;\n", x0 + dx, y1);
 *	  dxf_arc(x0 + dx, y1, x0 + dx, y1 - dy, angle, DELTA);
 *	  fprintf(tfp, "PA%.4f,%.4f;PU;PM2;\n", x0, y0 + dy);
 *
 *	  if (l->thickness != 0) fprintf(tfp, "EP;\n");
 */

	}

	break;

      case	  T_PIC_BOX:
	fprintf(stderr,"Warning: Pictures not supported in IBMGL language\n");
	break;
    }
  }
}

#define		       THRESHOLD	.05	   /* inch */

static void
bezier_spline(double a0, double b0, double a1, double b1, double a2, double b2, double a3, double b3)
{
	double	      x0, y0, x3, y3;
	double	      sx1, sy1, sx2, sy2, tx, ty, tx1, ty1, tx2, ty2, xmid, ymid;

	x0 = a0; y0 = b0;
	x3 = a3; y3 = b3;
	if (fabs(x0 - x3) < THRESHOLD && fabs(y0 - y3) < THRESHOLD)
	    fprintf(tfp, "PA%.4f,%.4f;\n", x3, y3);

	else {
	    tx	 = (a1	+ a2 )/2.0;	   ty	= (b1  + b2 )/2.0;
	    sx1  = (x0	+ a1 )/2.0;	   sy1	= (y0  + b1 )/2.0;
	    sx2  = (sx1 + tx )/2.0;	   sy2	= (sy1 + ty )/2.0;
	    tx2  = (a2	+ x3 )/2.0;	   ty2	= (b2  + y3 )/2.0;
	    tx1  = (tx2 + tx )/2.0;	   ty1	= (ty2 + ty )/2.0;
	    xmid = (sx2 + tx1)/2.0;	   ymid = (sy2 + ty1)/2.0;

	    bezier_spline(x0, y0, sx1, sy1, sx2, sy2, xmid, ymid);
	    bezier_spline(xmid, ymid, tx1, ty1, tx2, ty2, x3, y3);
	    }
}

static void
gendxf_itp_spline(F_spline *s)
{
	F_point		       *p1, *p2;
	F_control	 *cp1, *cp2;
	double		      x1, x2, y1, y2;

	p1 = s->points;
	cp1 = s->controls;
	x2 = p1->x/ppi; y2 = p1->y/ppi;

	if (s->thickness != 0 && s->back_arrow)
	    draw_arrow_head(cp1->rx/ppi, cp1->ry/ppi, x2, y2);

	fprintf(tfp, "PA%.4f,%.4f;PD;\n", x2, y2);
	for (p2 = p1->next, cp2 = cp1->next; p2 != NULL;
		p1 = p2, cp1 = cp2, p2 = p2->next, cp2 = cp2->next) {
	    x1	       = x2;
	    y1	       = y2;
	    x2	       = p2->x/ppi;
	    y2	       = p2->y/ppi;
	    bezier_spline(x1, y1, (double)cp1->rx/ppi, cp1->ry/ppi,
		(double)cp2->lx/ppi, cp2->ly/ppi, x2, y2);
	    }
	fprintf(tfp, "PU;\n");

	if (s->thickness != 0 && s->for_arrow)
	    draw_arrow_head(cp1->lx/ppi, cp1->ly/ppi, x2, y2);
	}

static void
quadratic_spline(double a1, double b1, double a2, double b2, double a3, double b3, double a4, double b4)
{
	double	      x1, y1, x4, y4;
	double	      xmid, ymid;

	x1	= a1; y1 = b1;
	x4	= a4; y4 = b4;
	xmid	= (a2 + a3)/2.0;
	ymid	= (b2 + b3)/2.0;
	if (fabs(x1 - xmid) < THRESHOLD && fabs(y1 - ymid) < THRESHOLD)
	    fprintf(tfp, "PA%.4f,%.4f;\n", xmid, ymid);
	else {
	    quadratic_spline(x1, y1, ((x1+a2)/2.0), ((y1+b2)/2.0),
		((3.0*a2+a3)/4.0), ((3.0*b2+b3)/4.0), xmid, ymid);
	    }

	if (fabs(xmid - x4) < THRESHOLD && fabs(ymid - y4) < THRESHOLD)
	    fprintf(tfp, "PA%.4f,%.4f;\n", x4, y4);
	else {
	    quadratic_spline(xmid, ymid, ((a2+3.0*a3)/4.0), ((b2+3.0*b3)/4.0),
			((a3+x4)/2.0), ((b3+y4)/2.0), x4, y4);
	    }
	}

static void
gendxf_ctl_spline(F_spline *s)
{
	F_point	*p;
	double	cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4;
	double	x1, y1, x2, y2;

	p = s->points;
	x1 = p->x/ppi;
	y1 = p->y/ppi;
	p = p->next;
	x2 = p->x/ppi;
	y2 = p->y/ppi;
	cx1 = (x1 + x2)/2.0;
	cy1 = (y1 + y2)/2.0;
	cx2 = (x1 + 3.0*x2)/4.0;
	cy2 = (y1 + 3.0*y2)/4.0;

	if (closed_spline(s))
	    fprintf(tfp, "PA%.4f,%.4f;PD;\n ", cx1, cy1);
	else {
	    if (s->thickness != 0 && s->back_arrow)
		draw_arrow_head(cx1, cy1, x1, y1);
	    fprintf(tfp, "PA%.4f,%.4f;PD%.4f,%.4f;\n",
		    x1, y1, cx1, cy1);
	    }

	for (p = p->next; p != NULL; p = p->next) {
	    x1 = x2;
	    y1 = y2;
	    x2 = p->x/ppi;
	    y2 = p->y/ppi;
	    cx3 = (3.0*x1 + x2)/4.0;
	    cy3 = (3.0*y1 + y2)/4.0;
	    cx4 = (x1 + x2)/2.0;
	    cy4 = (y1 + y2)/2.0;
	    quadratic_spline(cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4);
	    cx1 = cx4;
	    cy1 = cy4;
	    cx2 = (x1 + 3.0*x2)/4.0;
	    cy2 = (y1 + 3.0*y2)/4.0;
	    }
	x1 = x2;
	y1 = y2;
	p = s->points->next;
	x2 = p->x/ppi;
	y2 = p->y/ppi;
	cx3 = (3.0*x1 + x2)/4.0;
	cy3 = (3.0*y1 + y2)/4.0;
	cx4 = (x1 + x2)/2.0;
	cy4 = (y1 + y2)/2.0;
	if (closed_spline(s)) {
	    quadratic_spline(cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4);
	    fprintf(tfp, "PU;\n");
	    }
	else {
	    fprintf(tfp, "PA%.4f,%.4f;PU;\n", x1, y1);
	    if (s->thickness != 0 && s->for_arrow)
		    draw_arrow_head(cx1, cy1, x1, y1);
	    }
	}

void
gendxf_spline(F_spline *s)
{
  fprintf(tfp, "999\n !! found spline FIX \n");
	if (s->thickness != 0) {
	    set_style(s->style, s->style_val);
/*	    set_width(s->thickness);	*/

	    if (int_spline(s))
		gendxf_itp_spline(s);
	    else
		gendxf_ctl_spline(s);

	    }
	if (0 < s->fill_style && s->fill_style < patterns)
	    fprintf(stderr, "Spline area fill not implemented\n");
}

#define FONT(T) ((-1 < (T) && (T) < fonts) ? (T): fonts)

void
gendxf_text(F_text *t)
{
  static int font = DEFAULT;	    /* font */
  static int size = DEFAULT;	    /* font size	in points */
  double height;		    /* character height in centimeters */

  fprintf(tfp, "999\n !! found text %s\n",t->cstring);


  font	= FONT(t->font);

  fprintf(tfp, "  0\nTEXT\n");
  fprintf(tfp, "  8\n%3i\n",t->depth);
  fprintf(tfp, "  6\nSolid\n");
  fprintf(tfp, " 62\n%6i\n",t->color);
  fprintf(tfp, " 10\n%f\n",t->base_x/ppi);
  fprintf(tfp, " 11\n%f\n",t->base_x/ppi);
  fprintf(tfp, " 20\n%f\n",t->base_y/ppi);
  fprintf(tfp, " 21\n%f\n",t->base_y/ppi);
  fprintf(tfp, " 50\n%f\n",DPR * t->angle);
  fprintf(tfp, " 72\n%3i\n",t->type);

  size = t->size;
  height = size*hcmpp*high[font];
  fprintf(tfp, " 40\n%f\n",height);

  fprintf(tfp, "  1\n%s\n",t->cstring);

}

int
gendxf_end(void)
{
  /* DXF ending */
  fprintf(tfp, "  0\nENDSEC\n");
  fprintf(tfp, "  0\nEOF\n");

  /* all ok */
  return 0;
}

struct driver dev_dxf = {
	gendxf_option,
	gendxf_start,
	gendev_nogrid,
	gendxf_arc,
	gendxf_ellipse,
	gendxf_line,
	gendxf_spline,
	gendxf_text,
	gendxf_end,
	EXCLUDE_TEXT
};
