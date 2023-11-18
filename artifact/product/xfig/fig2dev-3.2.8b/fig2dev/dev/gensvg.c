/*
 * Fig2dev: Translate Fig code to various Devices
 * Parts Copyright (c) 2002 by Anthony Starks
 * Parts Copyright (c) 2002-2006 by Martin Kroeker
 * Parts Copyright (c) 2002-2015 by Brian V. Smith
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
 *
 * gensvg.c: convert fig to SVG
 *
 *  from fig2svg -- convert FIG 3.2 to SVG
 *
 *  Original author:  Anthony Starks (ajstarks@home.com)
 *  Created: 17 May 2000
 *  Converted to gensvg by Brian Smith
 *  Further modified by Martin Kroeker (martin@ruby.chemie.uni-freiburg.de)
 *  incorporating changes by Philipp Hahn and Justus Piater
 *  Modified by Thomas Loimer
 *
 *  Changes:
 *
 *  by Thomas Loimer <thomas.loimer@tuwien.ac.at>
 *
 *  2019-05-11
 *	- Output utf8-encoded text
 *	- Parse and replace characters <, > and & in comments by &lt; &gt; &amp;
 *
 *  2017-01-04
 *	- Fix pattern definitions. Use clip paths when painting objects with
 *	  arrows instead of retracting the line. Let the viewer do any
 *	  magnification. Use properties instead of attributes (e.g.,
 *	  stroke="red" instead of style="stroke:red;"). Implement pie-wedge
 *	  arcs. Add a todo list, see below.
 *
 * Changes before 2006
 *
 *  PH: Philipp Hahn
 *  JP: Justus Piater
 *  MK: Martin Kroeker
 *  BS: Brian Smith
 *  RE: Russell Edwards
 *
 *  MK 04-Dec-02: partial support for the symbol font, bigger fontscale, text alignment,
 *  dashed and dotted lines, bugfix for missing % in stroke-color statement of arcs
 *  FIXME: lacks support for arrowheads; fill patterns; percent grayscale fills
 *  MK 08-Dec-02: rotated text; shades and tints of fill colors; filled circles
 *  MK 11-Dec-02: scaling;proper font/slant/weight support; changed arc code
 *  12-Dec-02: fixes by Brian Smith: scale factor, orientation, ellipse fills
 *  MK 14-Dec-02: arc code rewrite, simplified line style handling,
 *  arrowheads on arcs and lines (FIXME: not clipped), stroke->color command
 *  is simply 'stroke'
 *  MK 15-Dec-02: catch pattern fill flags, convert to tinted fills for now
 *  MK 18-Dec-02: fill patterns; fixes by BS: arrowhead scale & position,
 *  circle by diameter
 *  PH 03-Feb-03: Fix CIRCLE_BY_DIA, color/fill styles, update SVG DTD
 *  MK 10-Feb-03: do not encode space characters when in symbol font;
 *		  always encode characters '&', '<' and '>'. Leave non-
 *		  alphabetic characters in the lower half of the symbol
 *		  font unchanged.
 *  MK 12-Feb-03: Added complete character conversion tables for the symbol
 *		  and dingbat fonts (based on the information in Unicode
 *		  Inc.'s symbol.txt and zdingbat.txt tables, version 0.2)
 *  MK 18-Feb-03: Added cap and join style fields for line and arc
 *  MK 24-Feb-03: Symbol and Dingbat fonts are no longer translated to
 *		  font-family="Times" with both bold and italic flags set.
 *  MK 17-Jun-03: Fix for rotation angle bug. Correct rendering of 'tinted'
 *		  colors using code from www.cs.rit.edu. Added forgotten
 *		  pattern fill option for ellipses (circles).
 *  JP 21-Jan-04: Calculate proper bounding box instead of current paper
 *		  dimensions. Added missing semicolons in some property
 *		  strings, and proper linebreak characters in multi-line
 *		  format strings.
 *  MK 23-Jan-04: Pattern-filled objects are now drawn twice - painting the
 *		  pattern over the fill color (if any). This solves the problem
 *		  of missing color support in pattern fills (as reported by JP)
 *		  Corrected filling of ellipses, which was still B/W only.
 *		  Fixed bad tiling of diagonal patterns 1 - 3 (the old formula
 *		  favoured exact angles over seamless tiling). Updated DTD.
 *  MK 25-Jan-04: Endpoints of polylines are now truncated when arrowheads
 *		  are drawn. Corrected rendering of type 0 (stick) arrowheads.
 *  MK 28-Jan-04: Fix for arc arrowhead orientation.
 *  MK 31-Jan-04: Corrected arc angle calculation (this time for good ?)
 *  MK 22-Feb-04: Picture support
 *  JP	1-Mar-04: Closed arrowheads should use polygons instead of polylines
 *  JP	3-Mar-04: Corrected font family selection
 *  JP 26-Mar-04: Corrected (and simplified) calculation of white-tinted
 *		  fill colors (and removed the HSV/RGB conversion code)
 *  MK 29-Mar-04: Added code for rounded boxes (polyline subtype 4)
 *  MK 30-Mar-04: Added code for boxes, explicit support for polygons
 *  MK 10-Apr-04: Added xml-space:preserve qualifier on texts to preserve
 *		  whitespace. Rewrote fill pattern handling to generate
 *		  patterns as needed - adding support for penwidth and color.
 *		  Corrected tiling of all shingle patterns and reversal
 *		  of horizontal shingles.
 *  RE	6-May-04: Changed degrees() to double for more precision
 *		  Added linewidth() to transform all line widths in the
 *		   same way as genps.c : thin lines get thinner
 *		  Changed circle radius to use F_ellipse::radiuses.x instead
 *		   of start and end (which seemed not to work correctly)
 *		   Query: Is this broken for byradius or bydiameter??
 *		  Added rotation to ellipses
 *		  Changed back to mapping Symbol to Times, greeks look a bit
 *		   better. Ultimately embedding PS fonts would be better.
 *		  Removed newlines inside <text> printf, otherwise they get
 *		   rendered as spaces due to xml:space="preserve"
 *		  Removed extraneous comma between two halves of format
 *		   string in gensvg_arc, fixes Seg fault.
 *  MK	3-Aug-04  Split the multi-line format string in gensvg_arc in two to
 *		  get rid of (compiler version-dependant) segfaults for good.
 *  MK 11-Sep-05: Added explicit stroke color to text to prevent black outline
 *		  on colored text.
 *		  Added support for latex-special formatted text, converting
 *		  sub- and superscripts to either baseline-shift=sub/super
 *		  (the intended way of doing this in SVG) or "dy" offsets
 *		  (less elegant, but more likely to be supported by browsers
 *		  and editors) depending on the NOSUPER define below.
 *		  Tested with Batik-1.6, konqueror-3.4, firefox-1.5b1,
 *		  inkscape-0.41
 *  MK 15-Sep-05: Use a font-family list of "Times,Symbol" for symbol
 *		  characters - the Times fontface does not contain all
 *		  elements of the Symbol font on all platforms.
 *  MK	4-Nov-05: Corrected length and appearance of stick-type arrows.
 *  MK	2-Jan-06: Added support for filled arcs.
 *  MK 26-Feb-06: Added support for dashed circles, ellipses and arcs.
 *		  Dash/gap lengths are now drawn according to style_val.
 *		  Fixed several glitches uncovered by splint.
 *  MK 22-Apr-06: Corrected blue component of shaded colors (was always
 *		  zero due to missing parentheses around typecast). Corrected
 *		  arrowheads of large arrows by adding an increased miterlimit.
 *		  Corrected position of backward arrowheads on polylines with
 *		  both forward and backward arrows.
 *  MK	2-Jul-06: Patterns do not inherit their line width from the parent object
 *		  (which may be zero if no visible boundary is desired), so always
 *		  use linewidth:1
 *  MK 22-Oct-06: Changed unicode variant of lowercase phi to match its X11 Symbol
 *		  counterpart.
 *  *********************************************************************************
 *
 *  An excerpt from http://www.w3.org/TR/2011/REC-SVG11-20110816/:
 *  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
 *  W3 recommendations for
 *  1.3 SVG Namespace, Public Identifier and System Identifier
 *
 *  The following are the SVG 1.1 namespace, public identifier and system identifier:
 *
 *  SVG Namespace:
 *	http://www.w3.org/2000/svg
 *	xmlns:xlink="http://www.w3.org/1999/xlink"
 *  Public Identifier for SVG 1.1:
 *	PUBLIC "-//W3C//DTD SVG 1.1//EN"
 *  System Identifier for the SVG 1.1 Recommendation:
 *	http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd
 *
 *  The following is an example document type declaration for an SVG document:
 *
 *  <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
 *	     "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
 *
 *  Note that DTD listed in the System Identifier is a modularized DTD (ie. its
 *  contents are spread over multiple files), which means that a validator may have
 *  to fetch the multiple modules in order to validate. For that reason, there is
 *  a single flattened DTD available that corresponds to the SVG 1.1 modularized DTD.
 *  It can be found at http://www.w3.org/Graphics/SVG/1.1/DTD/svg11-flat.dtd.
 *
 *  While a DTD is provided in this specification, the use of DTDs for
 *  validating XML documents is known to be problematic.  In particular, DTDs
 *  do not handle namespaces gracefully.  It is not recommended that
 *  a DOCTYPE declaration be included in SVG documents.
 *  *********************************************************************************
 */

/* TODO
 *	* identify pattern by number and color (int pattern[22], an
 *	  int has 32 bits, need 32 standard colors plus 512 user colors)
 *	* create nicer color commands ("white", "blue", etc. )
 *	  and "currentColor" for default
 *	* get put_precision from gentikz.c, prec 0 or 1
 *	  for, e.g., center of image, for rotation
 *	* ellipses: for dashed lines, put cap style "round"
 *	* need char *fig_color_names, or use int array?
 *	* image rotation - around center necessary?
 *	* check line stipples, compare with genps.c
 *	* see, if BLACK_FILL, WHITE_FILL can be replaced
 *	* use pdftocairo, where available?
 *      * defs until now: tile%d, p%d, cp%d
 *	* probably change to pattern%d, c%d (color)
 *
 *	* Correct color values;
 *	  hex codes see Fig_color_names in fig2dev.c, or, identical,
	  colorNames in xfig/src/resources.c
 *		colorNames	Fig_color_names	svg name
 *	0	"black"		"#000000"	black
 *	1	"blue"		"#0000ff"	blue
 *	2	"green"		"#00ff00"	lime
 *	3	"cyan"		"#00ffff"	cyan
 *	4	"red"		"#ff0000"	red
 *	5	"magenta"	"#ff00ff"	magenta
 *	6	"yellow"	"#ffff00"	yellow
 *	7	"white"		"#ffffff"	white
 *	8	"#000090"	"#000090" 144
 *	9	"#0000b0"	"#0000b0" 176
 *	10	"#0000d0"	"#0000d0" 208
 *	11	"#87ceff"	"#87ceff" 135 206
 *	12	"#009000"	"#009000"
 *	13	"#00b000"	"#00b000"
 *	14	"#00d000"	"#00d000"
 *	15	"#009090"	"#009090"
 *	16	"#00b0b0"	"#00b0b0"
 *	17	"#00d0d0"	"#00d0d0"
 *	18	"#900000"	"#900000"
 *	19	"#b00000"	"#b00000"
 *	20	"#d00000"	"#d00000"
 *	21	"#900090"	"#900090"
 *	22	"#b000b0"	"#b000b0"
 *	23	"#d000d0"	"#d000d0"
 *	24	"#803000"	"#803000" 128 48
 *	25	"#a04000"	"#a04000" 160 64
 *	26	"#c06000"	"#c06000" 192 96
 *	27	"#ff8080"	"#ff8080"
 *	28	"#ffa0a0"	"#ffa0a0"
 *	29	"#ffc0c0"	"#ffc0c0"
 *	30	"#ffe0e0"	"#ffe0e0"
 *	31	"gold"	        "#ffd700"	gold	(255, 215, 0)
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_STRINGS_H
#include <strings.h>
#endif
#include <math.h>

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "bound.h"
#include "creationdate.h"
#include "messages.h"
#include "pi.h"

static bool svg_arrows(int line_thickness, F_arrow *for_arrow, F_arrow *back_arrow,
	F_pos *forw1, F_pos *forw2, F_pos *back1, F_pos *back2, int pen_color);
static void generate_tile(int number, int colorIndex);
static void svg_dash(int, double);

#define PREAMBLE "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
#define	SVG_LINEWIDTH	76

static unsigned int symbolchar[256]=
{0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0x0020,0x0021,0x2200,0x0023,0x2203,0x0025,
0x0026,0x220B,0x0028,0x0029,0x2217,0x002B,0x002C,0x2212,0x002E,0x002F,0x0030,
0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,0x0039,0x003A,0x003B,
0x003C,0x003D,0x003E,0x003F,0x2245,0x0391,0x0392,0x03A7,0x0394,0x0395,
0x03A6,0x0393,0x0397,0x0399,0x03D1,0x039A,0x039B,0x039C,0x039D,0x039F,0x03A0,
0x0398,0x03A1,0x03A3,0x03A4,0x03A5,0x03C2,0x03A9,0x039E,0x03A8,0x0396,
0x005B,0x2234,0x005D,0x22A5,0x005F,0xF8E5,0x03B1,0x03B2,0x03C7,0x03B4,0x03B5,
0x03D5 /*0x03C6*/,0x03B3,0x03B7,0x03B9,0x03D5,0x03BA,0x03BB,0x03BC,0x03BD,0x03BF,
0x03C0,0x03B8,0x03C1,0x03C3,0x03C4,0x03C5,0x03D6,0x03C9,0x03BE,0x03C8,0x03B6,
0x007B,0x007C,0x007D,0x223C,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0, 0,0,
0,0,0x20AC,0x03D2,0x2032,0x2264,0x2044,0x221E,
0x0192,0x2663,0x2666,0x2665,0x2660,0x2194,0x2190,0x2191,0x2192,0x2193,0x00B0,
0x00B1,0x2033,0x2265,0x00D7,0x221D,0x2202,0x2022,0x00F7,0x2260,0x2261,0x2248,
0x2026,0xF8E6,0xF8E7,0x21B5,0x2135,0x2111,0x211C,0x2118,0x2297,0x2295,0x2205,
0x2229,0x222A,0x2283,0x2287,0x2284,0x2282,0x2286,0x2208,0x2209,0x2220,0x2207,
0xF6DA,0xF6D9,0xF6DB,0x220F,0x221A,0x22C5,0x00AC,0x2227,0x2228,0x21D4,0x21D0,
0x21D1,0x21D2,0x21D3,0x25CA,0x2329,0xF8E8,0xF8E9,0xF8EA,0x2211,0xF8EB,0xF8EC,
0xF8ED,0xF8EE,0xF8EF,0xF8F0,0xF8F1,0xF8F2,0xF8F3,0xF8F4,0,0x232A,0x222B,0x2320,
0xF8F5,0x2321,0xF8F6,0xF8F7,0xF8F8,0xF8F9,0xF8FA,0xF8FB,0xF8FC,0xF8FD,0xF8FE,0
};

static unsigned int dingbatchar[256]=
{0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0x0020,
0x2701,0x2702,0x2703,0x2704,0x260E,0x2706,0x2707,0x2708,0x2709,0x261B,
0x261E,0x270C,0x270D,0x270E,0x270F,0x2710,0x2711,0x2712,0x2713,0x2714,
0x2715,0x2716,0x2717,0x2718,0x2719,0x271A,0x271B,0x271C,0x271D,0x271E,
0x271F,0x2720,0x2721,0x2722,0x2723,0x2724,0x2725,0x2726,0x2727,0x2605,
0x2729,0x272A,0x272B,0x272C,0x272D,0x272E,0x272F,0x2730,0x2731,0x2732,
0x2733,0x2734,0x2735,0x2736,0x2737,0x2738,0x2739,0x273A,0x273B,0x273C,
0x273D,0x273E,0x273F,0x2740,0x2741,0x2742,0x2743,0x2744,0x2745,0x2746,
0x2747,0x2748,0x2749,0x274A,0x274B,0x25CF,0x274D,0x25A0,0x274F,0x2750,
0x2751,0x2752,0x25B2,0x25BC,0x25C6,0x2756,0x25D7,0x2758,0x2759,0x275A,
0x275B,0x275C,0x275D,0x275E,0,0xF8D7,0xF8D8,0xF8D9,0xF8DA,0xF8DB,
0xF8DC,0xF8DD,0xF8DE,0xF8DF,0xF8E0,0xF8E1,0xF8E2,0xF8E3,0xF8E4,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0x2761,0x2762,0x2763,
0x2764,0x2765,0x2766,0x2767,0x2663,0x2666,0x2665,0x2660,0x2460,0x2461,
0x2462,0x2463,0x2464,0x2465,0x2466,0x2467,0x2468,0x2469,0x2776,0x2777,
0x2778,0x2779,0x277A,0x277B,0x277C,0x277D,0x277E,0x277F,0x2780,0x2781,
0x2782,0x2783,0x2784,0x2785,0x2786,0x2787,0x2788,0x2789,0x278A,0x278B,
0x278C,0x278D,0x278E,0x278F,0x2790,0x2791,0x2792,0x2793,0x2794,0x2192,
0x2194,0x2195,0x2798,0x2799,0x279A,0x279B,0x279C,0x279D,0x279E,0x279F,
0x27A0,0x27A1,0x27A2,0x27A3,0x27A4,0x27A5,0x27A6,0x27A7,0x27A8,0x27A9,
0x27AA,0x27AB,0x27AC,0x27AD,0x27AE,0x27AF,0,0x27B1,0x27B2,0x27B3,0x27B4,
0x27B5,0x27B6,0x27B7,0x27B8,0x27B9,0x27BA,0x27BB,0x27BC,0x27BD,0x27BE,0
};

static int	tileno = -1;	/* number of current tile */
static int	pathno = -1;	/* number of current path */
static int	clipno = -1;	/* number of current clip path */

static void
put_capstyle(int c)
{
	if (c == 1)
	    fputs(" stroke-linecap=\"round\"", tfp);
	else if (c == 2)
	    fputs(" stroke-linecap=\"square\"", tfp);
}

static void
put_joinstyle(int j)
{
	if (j == 1)
	    fputs(" stroke-linejoin=\"round\"", tfp);
	else if (j == 2)
	    fputs(" stroke-linejoin=\"bevel\"", tfp);
}

static unsigned int
rgbColorVal(int colorIndex)
{				/* taken from genptk.c */
    unsigned int rgb;
    static unsigned int rgbColors[NUM_STD_COLS] = {
	0x000000, 0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff,
	0xffff00, 0xffffff, 0x00008f, 0x0000b0, 0x0000d1, 0x87cfff,
	0x008f00, 0x00b000, 0x00d100, 0x008f8f, 0x00b0b0, 0x00d1d1,
	0x8f0000, 0xb00000, 0xd10000, 0x8f008f, 0xb000b0, 0xd100d1,
	0x803000, 0xa14000, 0xb46100, 0xff8080, 0xffa1a1, 0xffbfbf,
	0xffe0e0, 0xffd600
    };

    if (colorIndex == DEFAULT)
	rgb = rgbColors[0];
    else if (colorIndex < NUM_STD_COLS)
	rgb = rgbColors[colorIndex];
    else
	rgb = ((user_colors[colorIndex - NUM_STD_COLS].r & 0xff) << 16)
	    | ((user_colors[colorIndex - NUM_STD_COLS].g & 0xff) << 8)
	    | (user_colors[colorIndex - NUM_STD_COLS].b & 0xff);
    return rgb;
}

static unsigned int
rgbFillVal(int colorIndex, int area_fill)
{
    unsigned int	rgb, r, g, b;
    double	t;
    short	tintflag = 0;

    if (colorIndex == BLACK_COLOR || colorIndex == DEFAULT) {
	if (area_fill > NUMSHADES - 1)
	    area_fill = NUMSHADES - 1;
	area_fill = NUMSHADES - 1 - area_fill;
	colorIndex = WHITE_COLOR;
    }

    rgb = rgbColorVal(colorIndex);

    if (area_fill > NUMSHADES - 1) {
	tintflag = 1;
	area_fill -= NUMSHADES - 1;
    }

    t = (double) area_fill / (NUMSHADES - 1);
    if (tintflag) {
	r = ((rgb & ~0xFFFF) >> 16);
	g = ((rgb & 0xFF00) >> 8);
	b = (rgb & ~0xFFFF00) ;

	r += t * (0xFF-r);
	g += t * (0xff-g);
	b += t * (0xff-b);

	rgb = ((r &0xff) << 16) + ((g&0xff) << 8) + (b&0xff);
    } else {
	rgb = (((int) (t * ((rgb & ~0xFFFF) >> 16)) << 16) +
		((int) (t * ((rgb & 0xFF00) >> 8)) << 8) +
		((int) (t * (rgb & ~0xFFFF00))) );
    }

    return rgb;
}

static double
degrees(double angle)
{
   return -angle / M_PI * 180.0;
}

static double
linewidth_adj(int linewidth)
{
   /* Adjustment as in genps.c */
   return linewidth <= THICK_SCALE ?
		linewidth / 2. : (double)(linewidth-THICK_SCALE);
}

void
put_sanitized_char(int c)
{
	switch (c) {
	case '<':
		fputs("&lt;", tfp);
		break;
	case '>':
		fputs("&gt;", tfp);
		break;
	case '&':
		fputs("&amp;", tfp);
		break;
	default:
		fputc(c, tfp);
	}
}

void
print_svgcomments(char *s1, F_comment *comments, char *s2)
{
	unsigned char	*c;
	while (comments) {
		fputs(s1, tfp);
		for (c = (unsigned char *)comments->comment; *c; ++c)
			put_sanitized_char((int)*c);
		fputs(s2, tfp);
		comments = comments->next;
	}
}

void
gensvg_option(char opt, char *optarg)
{
    switch (opt) {
	case 'G':		/* ignore language and grid */
	case 'L':
	    break;
	case 'z':
	    (void) strcpy (papersize, optarg);
	    paperspec = true;
	    break;
	default:
	    put_msg (Err_badarg, opt, "svg");
	    exit (1);
    }
}

void
gensvg_start(F_compound *objects)
{
    const struct paperdef	*pd;
    int     pagewidth = -1, pageheight = -1;
    int     vw, vh;
    char    date_buf[CREATION_TIME_LEN];

    fprintf(tfp, "%s\n", PREAMBLE);
    fprintf(tfp, "<!-- Creator: %s Version %s -->\n",
		  prog, PACKAGE_VERSION);

    if (creation_date(date_buf))
	fprintf(tfp, "<!-- CreationDate: %s -->\n", date_buf);
    fprintf(tfp, "<!-- Magnification: %.3g -->\n", mag);


    if (paperspec) {
	/* convert paper size from ppi to inches */
	for (pd = paperdef; pd->name != NULL; ++pd)
	    if (strcasecmp(papersize, pd->name) == 0) {
		pagewidth = pd->width;
		pageheight = pd->height;
		strcpy(papersize, pd->name);	/* use the "nice" form */
		break;
	    }
	if (pagewidth < 0 || pageheight < 0) {
	    (void) fprintf(stderr, "Unknown paper size `%s'\n", papersize);
	    exit(1);
	}
	if (landscape) {
	    vh = pagewidth;
	    vw = pageheight;
	} else {
	    vw = pagewidth;
	    vh = pageheight;
	}
    } else {
	vw = ceil((urx - llx) * 72. * mag / ppi);
	vh = ceil((ury - lly) * 72. * mag / ppi);
    }
    fputs("<svg\txmlns=\"http://www.w3.org/2000/svg\"\n", tfp);
    fputs("\txmlns:xlink=\"http://www.w3.org/1999/xlink\"\n", tfp);
    fprintf(tfp,
	"\twidth=\"%dpt\" height=\"%dpt\"\n\tviewBox=\"%d %d %d %d\">\n",
	vw, vh, llx, lly, urx - llx , ury - lly);

    if (objects->comments)
	print_svgcomments("<desc>", objects->comments, "</desc>\n");
    fputs("<g fill=\"none\">\n", tfp);

}

int
gensvg_end(void)
{
    fprintf(tfp, "</g>\n</svg>\n");
    return 0;
}

/*
 *	paint objects without arrows
 *	****************************
 *
 *	PATTERN					FILL		UNFILLED
 * a|	<defs>
 *
 *	<path d="..				<path d="..	<path d="..
 *
 * b|	id="p%d"/>				fill="#fillcol"
 * b|	generate_tile(pen_color)
 * b|	</defs>
 * b|	<use xlink:href="#p%d" fill="#col"/>
 * b|	<use xlink:href="#p%d" fill="url(#tile%d)"
 *
 *	    -----------   ...continue with "stroke=..." etc.   -----------
 *	/>				/>				/>
 *
 *	a| INIT_PAINT,  b| continue_paint
 *
 *	paint objects with arrows
 *	*************************
 *
 *	has_clip = svg_arrows(..., INIT)
 *	if (UNFILLED && thickness == 0) {svg_arrows(..); return;}
 *
 *	PATTERN				FILL				UNFILLED
 * c|	<defs>				<defs>				<defs>
 * c|	    -----------------   svg_arrows(..., CLIP)    ---------------
 *									</defs>
 *	    -----------------   <path polyline points="...  ------------
 * d|	id="p%d"/>			id="p%d"/>
 * d|	generate_tile(pen_color)
 * d|	</defs>				</defs>
 * d|	<use ..#p%d fill="#col"/>	<use ..."#p%d" fill="#fillcol"/>
 * d|	<use ..#p%d fill="url(#tile%d)"/>
 * d|	<use ..#p%d			<use ..#p%d
 * d|	    -----------------   clip-path="#cp%d"   --------------------
 *	    -------------   ...continue with "stroke=..." etc.   -------
 *	/>				/>				/>
 *	    -----------------   svg_arrows(..., pen_color)   ------------
 *
 *	c| INIT_PAINT_W_CLIP,  d| continue_paint_w_clip
 */

#define	INIT	-9	/* Change this, if pen_color may be negative. */
#define	CLIP	-8

#define	INIT_PAINT(fill_style) \
		if (fill_style > NUMFILLS) fputs("<defs>\n", tfp)

#define	INIT_PAINT_W_CLIP(fill_style, thickness, for_arrow, back_arrow,	\
			  forw1, forw2, back1, back2)			\
	fputs("<defs>\n", tfp);					\
	(void) svg_arrows(thickness, for_arrow, back_arrow,	\
		forw1, forw2, back1, back2, CLIP);		\
	if (fill_style == UNFILLED)				\
		fputs("</defs>\n", tfp)

void
continue_paint(int fill_style, int pen_color, int fill_color)
{
    if (fill_style > NUMFILLS) {
	fprintf(tfp, " id=\"p%d\"/>\n", ++pathno);
	generate_tile(fill_style - NUMFILLS, pen_color);
	fputs("</defs>\n", tfp);
	fprintf(tfp, "<use xlink:href=\"#p%d\" fill=\"#%6.6x\"/>\n",
		pathno, rgbColorVal(fill_color));
	fprintf(tfp, "<use xlink:href=\"#p%d\" fill=\"url(#tile%d)\"",
		pathno, tileno);
    } else if (fill_style > UNFILLED) {	/* && fill_style <= NUMFILLS */
	fprintf(tfp, " fill=\"#%6.6x\"", rgbFillVal(fill_color, fill_style));
    }
}

void
continue_paint_w_clip(int fill_style, int pen_color, int fill_color)
{
    if (fill_style > UNFILLED) {
	fprintf(tfp, " id=\"p%d\"/>\n", ++pathno);
	if (fill_style > NUMFILLS) {
	    generate_tile(fill_style - NUMFILLS, pen_color);
	}
	fputs("</defs>\n", tfp);
	fprintf(tfp, "<use xlink:href=\"#p%d\" ", pathno);
	if (fill_style > NUMFILLS) {
	    fprintf(tfp, "fill=\"#%6.6x\"/>\n", rgbColorVal(fill_color));
	    fprintf(tfp, "<use xlink:href=\"#p%d\" fill=\"url(#tile%d)\"/> ",
		    pathno, tileno);
	} else {
	    fprintf(tfp, "fill=\"#%6.6x\"/>\n",
			rgbFillVal(fill_color, fill_style));
	}
	fprintf(tfp, "<use xlink:href=\"#p%d\"", pathno);
    }
    fprintf(tfp, " clip-path=\"url(#cp%d)\"", clipno);
}

void
gensvg_line(F_line *l)
{
    char	chars;
    int		px,py;
    int		px2,py2,width,height,rotation;
    F_point	*p;


    if (l->type == T_PIC_BOX ) {
	fprintf(tfp,"<!-- Image -->\n");
	fprintf(tfp,
	    "<image xlink:href=\"file://%s\" preserveAspectRatio=\"none\"\n",
	    l->pic->file);
	p = l->points;
	px = p->x;
	py = p->y;
	px2 = p->next->next->x;
	py2 = p->next->next->y;
	width = px2 - px;
	height = py2 - py;
	rotation = 0;
	if (width<0 && height < 0)
		rotation = 180;
	else if (width < 0 && height >= 0)
		rotation = 90;
	else if (width >= 0 && height <0)
		rotation = 270;
	if (l->pic->flipped) rotation -= 90;
	if (width < 0) {
	    px = px2;
	    width = -width;
	}
	if (height < 0) {
	    py = py2;
	    height = -height;
	}
	px2 = px + width/2;
	py2 = py + height/2;
	if (l->pic->flipped) {
	    fprintf(tfp,
		"transform=\"rotate(%d %d %d) scale(-1,1) translate(%d,%d)\"\n",
		rotation, px2, py2, -2*px2, 0);
	} else if (rotation !=0) {
	fprintf(tfp,"transform=\"rotate(%d %d %d)\"\n",rotation,px2,py2);
	}

	fprintf(tfp,"x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"/>\n",
	px, py, width, height);
    return;
    }

    if (l->thickness <= 0 && l->fill_style == UNFILLED &&
			!l->for_arrow && !l->back_arrow)
	return;

    /* l->type == T_BOX, T_ARC_BOX, T_POLYGON or T_POLYLINE */
    fprintf(tfp, "<!-- Line -->\n");
    print_svgcomments("<!-- ", l->comments, " -->\n");

    if (l->type == T_BOX || l->type == T_ARC_BOX || l->type == T_POLYGON) {

	INIT_PAINT(l->fill_style);

	if (l->type == T_POLYGON) {
	    chars = fputs("<polygon points=\"", tfp);
	    for (p = l->points; p->next; p = p->next) {
		chars += fprintf(tfp, " %d,%d", p->x , p->y);
		if (chars > SVG_LINEWIDTH) {
		    fputc('\n', tfp);
		    chars = 0;
		}
	    }
	    fputc('\"', tfp);
	} else {	/* T_BOX || T_ARC_BOX */
	    px = l->points->next->next->x;
	    py = l->points->next->next->y;
	    width = l->points->x - px;
	    height = l->points->y - py;
	    if (width < 0) {
		px = l->points->x;
		width = -width;
	    }
	    if (height < 0) {
		py = l->points->y;
		height = -height;
	    }

	    fprintf(tfp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",
			px, py, width, height);
	    if (l->type == T_ARC_BOX)
		fprintf(tfp, " rx=\"%d\"", l->radius);
	}

    continue_paint(l->fill_style, l->pen_color, l->fill_color);

    /* http://jwatt.org/SVG Authoring Guidelines.html recommends to
       use px unit for stroke width */
    if (l->thickness) {
	fprintf(tfp, "\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\"",
		rgbColorVal(l->pen_color),
		(int) ceil(linewidth_adj(l->thickness)));
	put_joinstyle(l->join_style);
	put_capstyle(l->cap_style);
	if (l->style > SOLID_LINE)
	    svg_dash(l->style, l->style_val);
    }
    fputs("/>\n", tfp);

    return;
    }

    if (l->type == T_POLYLINE) {
	bool	has_clip = false;

	if (l->for_arrow || l->back_arrow) {
	    has_clip = svg_arrows(l->thickness, l->for_arrow, l->back_arrow,
			    &(l->last[1]), l->last, (F_pos *)l->points->next,
			    (F_pos *)l->points, INIT);
	    if (l->fill_style == UNFILLED && l->thickness <= 0) {
		(void) svg_arrows(l->thickness, l->for_arrow, l->back_arrow,
			    &(l->last[1]), l->last, (F_pos *)l->points->next,
			    (F_pos *)l->points, l->pen_color);
		return;
	    }
	}

	if (has_clip) {
	    INIT_PAINT_W_CLIP(l->fill_style, l->thickness, l->for_arrow,
		    l->back_arrow, &(l->last[1]), l->last,
		    (F_pos *)l->points->next, (F_pos *)l->points);
	} else {
	    INIT_PAINT(l->fill_style);
	}

	chars = fputs("<polyline points=\"", tfp);
	for (p = l->points; p; p = p->next) {
	    chars += fprintf(tfp, " %d,%d", p->x , p->y);
	    if (chars > SVG_LINEWIDTH) {
		fputc('\n', tfp);
		chars = 0;
	    }
	}
	fputc('\"', tfp);

	if (has_clip)
	    continue_paint_w_clip(l->fill_style, l->pen_color, l->fill_color);
	else
	    continue_paint(l->fill_style, l->pen_color, l->fill_color);

	if (l->thickness) {
	    fprintf(tfp, "\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\"",
		    rgbColorVal(l->pen_color),
		    (int) ceil(linewidth_adj(l->thickness)));
	    put_joinstyle(l->join_style);
	    put_capstyle(l->cap_style);
	    if (l->style > SOLID_LINE)
		svg_dash(l->style, l->style_val);
	}

	fputs("/>\n", tfp);
	if (l->for_arrow || l->back_arrow)
	    (void) svg_arrows(l->thickness, l->for_arrow, l->back_arrow,
			&(l->last[1]), l->last, (F_pos *)l->points->next,
			(F_pos *)l->points, l->pen_color);
    }	/* l->type == T_POLYLINE */
}

void
gensvg_spline( /* not used by fig2dev */
	F_spline *s)
{
    F_point *p;
    fprintf(tfp, "<!-- Spline -->\n");
    print_svgcomments("<!-- ", s->comments, " -->\n");

    fprintf(tfp, "<path style=\"stroke:#%6.6x;stroke-width:%d\" d=\"",
	     rgbColorVal(s->pen_color), (int) ceil (linewidth_adj(s->thickness)));
    fprintf(tfp, "M %d,%d\n C", s->points->x , s->points->y );
    for (p = s->points++; p; p = p->next) {
	fprintf(tfp, "%d,%d\n", p->x , p->y );
    }
    fprintf(tfp, "\"/>\n");
}

void
gensvg_arc(F_arc *a)
{
    bool    has_clip = false;
    double  radius;
    double  x, y, angle, dx, dy;
    F_pos   forw1, forw2, back1, back2;

    if (a->fill_style == UNFILLED && a->thickness <= 0 &&
	    !a->for_arrow && !a->back_arrow)
	return;

    fputs("<!-- Arc -->\n", tfp);
    print_svgcomments("<!-- ", a->comments, " -->\n");

    if (a->for_arrow || a->back_arrow) {
	if (a->for_arrow) {
	    forw2.x = a->point[2].x;
	    forw2.y = a->point[2].y;
	    compute_arcarrow_angle(a->center.x, a->center.y,
		    (double) forw2.x, (double) forw2.y, a->direction,
		    a->for_arrow, &(forw1.x), &(forw1.y));
	}
	if (a->back_arrow) {
	    back2.x = a->point[0].x;
	    back2.y = a->point[0].y;
	    compute_arcarrow_angle(a->center.x, a->center.y,
		    (double) back2.x, (double) back2.y, a->direction ^ 1,
		    a->back_arrow, &(back1.x), &(back1.y));
	}
	has_clip = svg_arrows(a->thickness, a->for_arrow, a->back_arrow,
				&forw1, &forw2, &back1, &back2, INIT);
	if (a->fill_style == UNFILLED && a->thickness <= 0) {
	    (void) svg_arrows(a->thickness, a->for_arrow, a->back_arrow,
				&forw1, &forw2, &back1, &back2, a->pen_color);
	    return;
	}
    }

    dx = a->point[0].x - a->center.x;
    dy = a->point[0].y - a->center.y;
    radius = sqrt(dx * dx + dy * dy);

    x = (a->point[0].x-a->center.x) * (a->point[2].x-a->center.x) +
		(a->point[0].y-a->center.y) * (a->point[2].y-a->center.y);
    y = (a->point[0].x-a->center.x) * (a->point[2].y-a->center.y) -
		(a->point[0].y-a->center.y) * (a->point[2].x-a->center.x);

    if (x == 0.0 && y == 0.0)
	angle=0.0;
    else
	angle = atan2(y,x);
    if (angle < 0.0) angle += 2.*M_PI;
    angle *= 180./M_PI;
    if (a->direction == 1)
	angle = 360. - angle;

    if (has_clip) {
	INIT_PAINT_W_CLIP(a->fill_style, a->thickness, a->for_arrow,
		a->back_arrow, &forw1, &forw2, &back1, &back2);
    } else {
	INIT_PAINT(a->fill_style);
    }

    /* paint the object */
    fputs("<path d=\"M", tfp);
    if (a->type == T_PIE_WEDGE_ARC)
		fprintf(tfp, " %ld,%ld L",
			lround(a->center.x), lround(a->center.y));
    fprintf(tfp, " %d,%d A %ld %ld %d %d %d %d %d",
	     a->point[0].x , a->point[0].y ,
	     lround(radius), lround(radius), 0,
	     (fabs(angle) > 180.) ? 1 : 0,
	     (fabs(angle) > 0. && a->direction == 0) ? 1 : 0,
	     a->point[2].x , a->point[2].y );
    if (a->type == T_PIE_WEDGE_ARC)
	fputs(" z", tfp);
    fputc('\"', tfp);

    if (has_clip)
	continue_paint_w_clip(a->fill_style, a->pen_color, a->fill_color);
    else
	continue_paint(a->fill_style, a->pen_color, a->fill_color);

    if (a->thickness) {
	fprintf(tfp, "\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\"",
		rgbColorVal(a->pen_color),
		(int) ceil(linewidth_adj(a->thickness)));
	put_capstyle(a->cap_style);
	if (a->style > SOLID_LINE)
	    svg_dash(a->style, a->style_val);
    }

    fputs("/>\n", tfp);
    if (a->for_arrow || a->back_arrow)
	(void) svg_arrows(a->thickness, a->for_arrow, a->back_arrow,
			&forw1, &forw2, &back1, &back2, a->pen_color);
}

void
gensvg_ellipse(F_ellipse *e)
{
    int cx = e->center.x ;
    int cy = e->center.y ;

    if (e->type == T_CIRCLE_BY_RAD || e->type == T_CIRCLE_BY_DIA) {
	int r = e->radiuses.x ;
	fputs("<!-- Circle -->\n", tfp);
	print_svgcomments("<!-- ", e->comments, " -->\n");

	INIT_PAINT(e->fill_style);

	/* paint the object */
	fprintf(tfp, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\"", cx, cy, r);

    } else { /* T_ELLIPSE_BY_RAD or T_ELLIPSE_BY_DIA */
	int rx = e->radiuses.x ;
	int ry = e->radiuses.y ;
	fputs("<!-- Ellipse -->\n", tfp);
	print_svgcomments("<!-- ", e->comments, " -->\n");

	INIT_PAINT(e->fill_style);

	/* now paint object */
	if (e->angle == 0.0)
	    fprintf(tfp, "<ellipse cx=\"%d\" cy=\"%d\"", cx, cy);
	else
	    fprintf(tfp,
		    "<ellipse transform=\"translate(%d,%d) rotate(%.0f)\"",
		    cx, cy, degrees(e->angle));
	fprintf(tfp, " rx=\"%d\" ry=\"%d\"", rx, ry);
    } /* end T_CIRCLE... or T_ELLIPSE... */

    continue_paint(e->fill_style, e->pen_color, e->fill_color);

    if (e->thickness) {
	fprintf(tfp, "\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\"",
		rgbColorVal(e->pen_color),
		(int) ceil(linewidth_adj(e->thickness)));
	if (e->style > SOLID_LINE)
	    svg_dash(e->style, e->style_val);
    }
    fputs("/>\n", tfp);
}

void
gensvg_text(F_text *t)
{
	unsigned char *cp;
	int ch;
	const char *anchor[3] = { "start", "middle", "end" };
	const char *family[9] = { "Times", "AvantGarde",
		"Bookman", "Courier", "Helvetica", "Helvetica Narrow",
		"New Century Schoolbook", "Palatino", "Times,Symbol"
	};
	int x = t->base_x ;
	int y = t->base_y ;
#ifdef NOSUPER
	int dy = 0;
#endif

	fprintf(tfp, "<!-- Text -->\n");
	print_svgcomments("<!-- ", t->comments, " -->\n");

	if (t->angle != 0.) {
		fprintf(tfp,
			"<g transform=\"translate(%d,%d) rotate(%.0f)\" >\n",
			x, y, degrees(t->angle));
	x = y = 0;
	}
	fputs("<text xml:space=\"preserve\" ", tfp);
	fprintf(tfp, "x=\"%d\" y=\"%d\" fill=\"#%6.6x\" font-family=\"%s\" ",
			x, y, rgbColorVal(t->color), family[t->font / 4]);
	fprintf(tfp,
		"font-style=\"%s\" font-weight=\"%s\" font-size=\"%d\" text-anchor=\"%s\">",
		((t->font % 2 == 0 || t->font > 31) ? "normal" : "italic"),
		((t->font % 4 < 2 || t->font > 31) ? "normal" : "bold"),
		(int)ceil(t->size * 12), anchor[t->type]);

	if (t->font == 32) {
		for (cp = (unsigned char *)t->cstring; *cp; ++cp) {
			ch = *cp;
			fprintf(tfp, "&#%d;", symbolchar[ch]);
		}
	} else if (t->font == 34) {
		for (cp = (unsigned char *)t->cstring; *cp; ++cp) {
			ch = *cp;
			fprintf(tfp, "&#%d;", dingbatchar[ch]);
		}
	} else if (special_text(t)) {
		int supsub = 0;
#ifdef NOSUPER
		int old_dy=0;
#endif
		for (cp = (unsigned char *)t->cstring; *cp; cp++) {
			ch = *cp;
			if ((supsub == 2 && ch == '}') || supsub==1) {
#ifdef NOSUPER
				fprintf(tfp,"</tspan><tspan dy=\"%d\">",-dy);
				old_dy=-dy;
#else
				fprintf(tfp,"</tspan>");
#endif
				supsub = 0;
				if (ch == '}') {
					++cp;
					ch = *cp;
				}
			}
			if (ch == '_' || ch == '^') {
				if (*(cp + 1) == '\0')
					break;
				supsub=1;
#ifdef NOSUPER
				if (dy != 0)
					fprintf(tfp,"</tspan>");
				if (ch == '_')
					dy = 35.;
				if (ch == '^')
					dy = -50.;
				fprintf(tfp,
					"<tspan font-size=\"%d\" dy=\"%d\">",
					(int)ceil(t->size * 8), dy + old_dy);
				old_dy = 0;
#else
				fprintf(tfp,
					"<tspan font-size=\"%d\" baseline-shift=\"",
					(int)ceil(t->size * 8));
				if (ch == '_')
					fprintf(tfp,"sub\">");
				if (ch == '^')
					fprintf(tfp,"super\">");
#endif
				++cp;
				ch = *cp;
				if (ch == '{' ) {
					if (*(cp + 1) == '\0')
						break;
					supsub=2;
					++cp;
					ch = *cp;
				}
			}
#ifdef NOSUPER
			else old_dy=0;
#endif
			if (ch != '$')
				put_sanitized_char(ch);
		}
	} else {
		for (cp = (unsigned char *)t->cstring; *cp; ++cp)
			put_sanitized_char((int)*cp);
	}
#ifdef NOSUPER
	if (dy != 0)
		fprintf(tfp,"</tspan>");
#endif
	fprintf(tfp, "</text>\n");
	if (t->angle != 0)
		fprintf(tfp, "</g>");
}

static void
arrow_path(F_arrow *arrow, F_pos *arrow2, int pen_color, int npoints,
	F_pos points[], int nfillpoints, F_pos *fillpoints
#ifdef DEBUG
	, int nclippoints, F_pos clippoints[]
#endif
	)
{
    int	    i, chars;

    fprintf(tfp, " to point %d,%d -->\n", arrow2->x, arrow2->y);
    chars = fprintf(tfp, "<%s points=\"",
	    (points[0].x == points[npoints-1].x &&
	     points[0].y == points[npoints-1].y ? "polygon" : "polyline"));
    for (i = 0; i < npoints; ++i) {
	chars += fprintf(tfp, " %d,%d", points[i].x ,
		points[i].y );
	if (chars > SVG_LINEWIDTH) {
	    fputc('\n', tfp);
	    chars = 0;
	}
    }
    fprintf(tfp,
	"\"\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\" stroke-miterlimit=\"8\"",
	rgbColorVal(pen_color),
	(int) ceil(linewidth_adj((int)arrow->thickness)));
    if (arrow->type < 13 && (arrow->style != 0 || nfillpoints != 0)) {
	if (nfillpoints == 0)
	    fprintf(tfp, " fill=\"#%6.6x\"/>\n", rgbColorVal(pen_color));
	else { /* fill the special area */
	    fprintf(tfp, "/>\n<path d=\"M ");
	    for (i = 0; i < nfillpoints; ++i) {
		fprintf(tfp, "%d,%d ", fillpoints[i].x ,
			fillpoints[i].y );
	    }
	    fprintf(tfp, "z\"\n\tstroke=\"#%6.6x\" stroke-width=\"%dpx\"",
		    rgbColorVal(pen_color),
		    (int) ceil(linewidth_adj((int)arrow->thickness)));
	    fprintf(tfp, " stroke-miterlimit=\"8\" fill=\"#%6.6x\"/>\n",
		    rgbColorVal(pen_color));
	}
    } else
      fprintf(tfp, "/>\n");
#ifdef DEBUG
    /* paint the clip path */
    if (nclippoints) {
	fputs("<!-- clip path -->\n<path d=\"M", tfp);
	for (i = 0; i < nclippoints; ++i)
	    fprintf(tfp,"%d,%d ", clippoints[i].x, clippoints[i].y);
	fputs("z\"\n\tstroke=\"red\" opacity=\"0.5\" stroke-width=\"10px\" stroke-miterlimit=\"8\"/>\n", tfp);
    }
#endif
}

static bool
svg_arrows(int line_thickness, F_arrow *for_arrow, F_arrow *back_arrow,
	F_pos *forw1, F_pos *forw2, F_pos *back1, F_pos *back2, int pen_color)
{
    static int		fnpoints, fnfillpoints, fnclippoints;
    static int		bnpoints, bnfillpoints, bnclippoints;
    static F_pos	fpoints[50], ffillpoints[50], fclippoints[50];
    static F_pos	bpoints[50], bfillpoints[50], bclippoints[50];
    int			i;

    if (pen_color == INIT) {
	if (for_arrow) {
	    calc_arrow(forw1->x, forw1->y, forw2->x, forw2->y,
		    line_thickness, for_arrow, fpoints, &fnpoints,
		    ffillpoints, &fnfillpoints, fclippoints, &fnclippoints);
	}
	if (back_arrow) {
	    calc_arrow(back1->x, back1->y, back2->x, back2->y,
		    line_thickness, back_arrow, bpoints, &bnpoints,
		    bfillpoints, &bnfillpoints, bclippoints, &bnclippoints);
	}
	if (fnclippoints || bnclippoints)
	    return true;
	else
	    return false;
    }

    if (pen_color == CLIP) {
	fprintf(tfp, "<clipPath id=\"cp%d\">\n", ++clipno);
	fprintf(tfp,
		"\t<path clip-rule=\"evenodd\" d=\"M %d,%d H %d V %d H %d z",
		llx, lly, urx, ury, llx);
	if (fnclippoints) {
	    fprintf(tfp, "\n\t\tM %d,%d", fclippoints[0].x,fclippoints[0].y);
	    for (i = 1; i < fnclippoints; ++i)
		fprintf(tfp, " %d,%d", fclippoints[i].x, fclippoints[i].y);
	    fputc('z', tfp);
	}
	if (bnclippoints) {
	    fprintf(tfp, "\n\t\tM %d,%d", bclippoints[0].x,bclippoints[0].y);
	    for (i = 1; i < bnclippoints; ++i)
		fprintf(tfp, " %d,%d", bclippoints[i].x, bclippoints[i].y);
	    fputc('z', tfp);
	}
	fputs("\"/>\n</clipPath>\n", tfp);
	return true;
    }

    if (for_arrow && fnpoints > 1) {
	fputs("<!-- Forward arrow", tfp);
	arrow_path(for_arrow, forw2, pen_color, fnpoints, fpoints,
		fnfillpoints, ffillpoints
#ifdef DEBUG
		, fnclippoints, fclippoints
#endif
		);
    }
    if (back_arrow && bnpoints > 1) {
	fputs("<!-- Backward arrow", tfp);
	arrow_path(back_arrow, back2, pen_color, bnpoints, bpoints,
		bnfillpoints, bfillpoints
#ifdef DEBUG
		, bnclippoints, bclippoints
#endif
		);
    }
    return true;
}

static void
generate_tile(int number, int colorIndex)
{
    static const struct pattern {
	char*	size;
	char*	code;
    }	pattern[NUMPATTERNS] = {
	/* 0	30 degrees left diagonal */
	{"width=\"134\" height=\"67\">",
	 "\"M -7,30 73,70 M 61,-3 141,37\""},
	/* 1 	30 degrees right diagonal */
	{"width=\"134\" height=\"67\">",
	 /* M 0 33.5 67 0 M 67 67 134 33.5 */
	 "\"M -7,37 73,-3 M 61,70 141,30\""},
	 /* 2	30 degrees crosshatch */
	{"width=\"134\" height=\"67\">",
	 "\"M -7,30 73,70 M 61,-3 141,37 M -7,37 73,-3 M 61,70 141,30\""},
	 /* 3	45 degrees left diagonal */
	{"width=\"134\" height=\"134\">",
	 "\"M -4,63 71,138 M 63,-4 138,71\""},
	 /* 4	45 degrees right diagonal */
	{"width=\"134\" height=\"134\">",
	 "\"M -4,71 71,-4 M 63,138 138,63\""},
	 /* 5	45 degrees crosshatch */
	{"width=\"134\" height=\"134\">",
	 "\"M-4,63 71,138 M63,-4 138,71 M-4,71 71,-4 M63,138 138,63\""},
	 /* 6	horizontal bricks */
	{"width=\"268\" height=\"268\">",
	 "\"M-1,67 H269 M-1,201 H269 M67,-1 V67 M67,201 V269 M201,67 V201\""},
	 /* 7	vertical bricks */
	{"width=\"268\" height=\"268\">",
	 "\"M67,-1 V269 M201,-1 V269 M-1,67 H67 M201,67 H269 M67,201 H201\""},
	 /* 8	horizontal lines */
	{"width=\"268\" height=\"67\">",
	 "\"M -1,30 H 269\""},
	 /* 9	vertical lines */
	{"width=\"67\" height=\"268\">",
	 "\"M 30,-1 V 269\""},
	 /* 10	crosshatch */
	{"width=\"67\" height=\"67\">",
	 "\"M -1,30 H 68 M 30,-1 V 68\""},
	 /* 11	left-pointing shingles */
	{"width=\"402\" height=\"402\">",
	 "\"M-1,30 H403 M-1,164 H403 M-1,298 H403 M238,30 l-67,134 M372,164 l-67,134 M104,298 l-60,120 M37,30 l20,-40\""},
	 /* 12	right-pointing shingles */
	{"width=\"402\" height=\"402\">",
	 "\"M-1,30 H403 M-1,164 H403 M-1,298 H403 M164,30 l67,134 M30,164 l67,134 M298,298 l60,120 M365,30 l-20,-40\""},
	 /* 13  vertical left-pointing shingles */
	{"width=\"402\" height=\"402\">",
	 "\"M30,-1 V403 M164,-1 V403 M298,-1 V403 M30,164 l134,67 M164,30 l134,67 M298,298 l120,60 M30,365 l-40,-20\""},
	 /* 14	vertical right-pointing shingles */
	{"width=\"402\" height=\"402\">",
	 "\"M30,-1 V403 M164,-1 V403 M298,-1 V403 M30,238 l134,-67 M164,372 l134,-67 M298,104 l120,-60 M30,37 l-40,20\""},
	 /* 15	fish scales */
	{"width=\"268\" height=\"140\">",
	 "\"M-104,-30 a167.5,167.5 0 0,0 268,0 a167.5,167.5 0 0,0 134,67 m0,3 a167.5,167.5 0 0,1 -268,0 a167.5,167.5 0 0,1 -134,67 m134,70 a167.5,167.5 0 0,0 134,-67 a167.5,167.5 0 0,0 134,67\""},
	 /* 16	small fish scales */
	{"width=\"134\" height=\"134\">",
	 "\"M164,-30 a67,67 0 0,1 -134,0 a67,67 0 0,1 -67,67 a67,67 0 0,0 134,0 a67,67 0 0,0 67,67 a67,67 0 0,1 -134,0 a67,67 0 0,1 -67,67\""},
	 /* 17	circles */
	{"width=\"268\" height=\"268\">",
	 "\"M0,134 a134,134 0 0,0 134,-134 a134,134 0 0,0 134,134 a134,134 0 0,0 -134,134 a134,134 0 0,0 -134,-134\""},
	 /* 18	hexagons */
	{"width=\"402\" height=\"232\">",
	 "\"m97,-86 -67,116 67,116 -67,116 M231,-86 l67,116 l-67,116 l67,116 M-1,30 h31 m268,0 h105 M97,146 h134\""},
	 /* 19	octagons */
	{"width=\"280\" height=\"280\">",
	 "\"m-1,140 59,0 82,-82 82,82 -82,82 -82,-82 m82,82 v59 m0,-282 v59 m82,82 h59\""},
	 /* 20	horizontal sawtooth */
	{"width=\"134\" height=\"134\">",
	 "\"m-4,63 67,67 67,-67 20,20\""},
	 /* 21	vertical sawtooth */
	{"width=\"134\" height=\"134\">",
	 "\"m63,-4 67,67 -67,67 20,20\""},
    };

    fprintf(tfp,
	    "<pattern id=\"tile%d\" patternUnits=\"userSpaceOnUse\"\n",
	    ++tileno);
    fputs("\tx=\"0\" y=\"0\" ", tfp);
    fputs(pattern[number - 1].size, tfp);
    /* Draw pattern lines with a width of .45 bp ( = 7.5 Fig units at
       ppi = 1200), consistent with line widths in gentikz.c.
       In genps.c, patterns are drawn with a linewidth of 1 bp
       ( = 16.6 Fig units, at 1200 ppi), or .7 bp ( = 11.7 Fig units). */
    fprintf(tfp,
	    "\n<g stroke-width=\"%.2g\" stroke=\"#%6.6x\" fill=\"none\">\n",
	    0.5*ppi/80., rgbColorVal(colorIndex));
    fputs("<path d=", tfp);
    fputs(pattern[number - 1].code, tfp);
    fputs("/>\n</g>\n</pattern>\n", tfp);
}

static void
svg_dash(int style, double val)
{
	fprintf(tfp, " stroke-dasharray=\"");
	switch(style) {
	case 1:
	default:
		fprintf(tfp,"%ld %ld\"", lround(val*10), lround(val*10));
		break;
	case 2:
		fprintf(tfp,"10 %ld\"", lround(val*10));
		break;
	case 3:
		fprintf(tfp,"%ld %ld 10 %ld\"", lround(val*10),
			lround(val*5), lround(val*5));
		break;
	case 4:
		fprintf(tfp,"%ld %ld 10 %ld 10 %ld\"", lround(val*10),
			lround(val*3), lround(val*3), lround(val*3));
		break;
	case 5:
		fprintf(tfp,"%ld %ld 10 %ld 10 %ld 10 %ld\"", lround(val*10),
			lround(val*3), lround(val*3), lround(val*3),
			lround(val*3));
		break;
	}
}

/* driver defs */

struct driver dev_svg = {
	gensvg_option,
	gensvg_start,
	gendev_nogrid,
	gensvg_arc,
	gensvg_ellipse,
	gensvg_line,
	gensvg_spline,
	gensvg_text,
	gensvg_end,
	INCLUDE_TEXT
};
