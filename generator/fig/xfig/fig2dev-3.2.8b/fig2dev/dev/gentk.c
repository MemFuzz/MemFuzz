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
 * gentk: convert fig to Tk
 *
 * Author: Mike Markowski <mm@udel.edu>, U of Delaware, 4/98
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
#include "colors.h"	/* lookup_X_color() */
#include "messages.h"
#include "pi.h"
#include "readpics.h"
#include "tkpattern.h"

#define X(x) ((double)(x)/ppi)
#define Y(y) ((double)(y)/ppi)

#define NONE (0xffffff + 1)

int ReadFromBitmapFile(FILE *file, unsigned int *width, unsigned int *height,
		unsigned char **data_ret);	/* readxbm.c */

static void
	drawFilledShape(void (*)(), void *, int, int, int, int, int, double),
	drawBitmap(F_line *),
	tkLine(F_line *, int, int, int, double),
	tkArc(void *),
	tkEllipse(void *),
	tkPolygon(void *),
	tk_setstyle(int style, double v),
	niceLine(char *);

static unsigned int
	rgbColorVal(int);

static char *canvas = "$xfigCanvas";
static char *xbmPathVar = "$xbmPath";
/* the base name of the variable referring to the bitmap file */
static char *patname = "xfigp";

#define		TOP	8.5 /* inches */
static int	full_page = false;

/*
 * Create files containing the stipple bitmaps, if they do not yet exist.
 * For instance, create the file left30.xbm, and refer to it by $xfigp0.
 */
static void
define_pattern(int n)
{
	int	i;

	fprintf(tfp, "# %s\n", tkpattern[n].name);
	fprintf(tfp, "set %s%d [file join %s %s.xbm]\n",
			patname, n, xbmPathVar, tkpattern[n].name);
	fprintf(tfp, "if { [file exist $%s%d] == 0 } {\n", patname, n);
	fprintf(tfp, "    set fd [open $%s%d w]\n    puts $fd {", patname, n);
	fprintf(tfp, "#define %s_width %d\n#define %s_height %d\n",
			tkpattern[n].name, tkpattern[n].width,
			tkpattern[n].name, tkpattern[n].height);
	fprintf(tfp, "static unsigned char %s_bits[] = {\n\t0x%.2x",
			tkpattern[n].name, tkpattern[n].bits[0]);
	for (i = 1; i < ((tkpattern[n].width + 7) / 8) * tkpattern[n].height;
			++i) {
		if (i % 12 == 0)
			fputs(",\n\t", tfp);
		else
			fputs(", ", tfp);
		fprintf(tfp, "0x%.2x", tkpattern[n].bits[i]);
	}
	fputs("};}\nclose $fd\n}\n", tfp);
}

/*
 *   g e n T k O p t i o n ( )
 */

void
gentk_option(char opt, char *optarg)
{
	switch (opt) {
	case 'g':			/* background color */
		if (lookup_X_color(optarg,&background) >= 0) {
			bgspec = true;
		} else {
			fprintf(stderr,
			"Can't parse color '%s', ignoring background option\n",
					optarg);
		}
		break;

	case 'l':			/* landscape mode */
		landscape = true;	/* override the figure file setting */
		orientspec = true;	/* user-specified */
		break;

	case 'p':			/* portrait mode */
		landscape = false;	/* override the figure file setting */
		orientspec = true;	/* user-specified */
		break;

	case 'P':			/* use full page instead of bounding box */
		full_page = true;
		break;

	case 'z':			/* papersize */
		(void) strcpy (papersize, optarg);
		paperspec = true;	/* user-specified */
		break;

	case 'G':
	case 'L':
		break;

	default:
		put_msg(Err_badarg, opt, "tk");
		exit(EXIT_FAILURE);
	}

}

/*
 *   g e n T k S t a r t ( )
 *
 *   Any initialization garbage is taken care of here.
 */

void
gentk_start(F_compound *objects)
{
	float		wid = -1., ht = -1., swap;
	const struct paperdef	*pd;

	fprintf(tfp, "# Produced by fig2dev Version %s\n", PACKAGE_VERSION);
	ppi = ppi / mag * 80/72.0;

	/* print any whole-figure comments prefixed with "#" */
	if (objects->comments) {
		fputs("#\n", tfp);
		print_comments("# ", objects->comments, "");
		fputs("#\n", tfp);
	}
	fputs(
"# The canvas name (\".c\") can be changed to anything you like.  It only\n"
"# occurs in the following line.  The canvas size can be changed as well.\n\n",
		tfp);

	if (!full_page) {
		/* get width and height in fig units */
		wid = urx - llx;
		ht = ury - lly;

		/* add 1% border around */
		llx -= round(wid/100.0);
		lly -= round(ht/100.0);
		urx += round(wid/100.0);
		ury += round(ht/100.0);

		/* recalculate new width and height in inches */
		wid = 1.0*(urx - llx)/ppi;
		ht = 1.0*(ury - lly)/ppi;
	} else {
		/* full page, get the papersize as the width and height
		   for the canvas */
		for (pd = paperdef; pd->name != NULL; ++pd)
			if (strcasecmp (papersize, pd->name) == 0) {
				/* width/height are in dpi, convert to inches */
				wid = pd->width / 80.0;
				ht = pd->height / 80.0;
				/* use the "nice" form */
				strcpy(papersize, pd->name);
				break;
			}

		if (wid < 0 || ht < 0) {
			(void) fprintf(stderr, "Unknown paper size `%s'\n",
					papersize);
			exit(EXIT_FAILURE);
		}

		fprintf(tfp, "# Page size specified: %s\n", papersize);

		/* swap for landscape */
		if (landscape) {
			fputs("# Landscape orientation\n", tfp);
			swap = wid;
			wid = ht;
			ht = swap;
		} else {
			fputs("# Portrait orientation\n", tfp);
		}
	}

	fprintf(tfp, "set %s [canvas .c -width %.2fi -height %.2fi]",
			canvas + 1, wid, ht);
	if (bgspec) {
		fprintf(tfp, " -bg #%02x%02x%02x", background.red/255,
				background.green/255, background.blue/255);
	}
	fputc('\n', tfp);

	fputs("$xfigCanvas config -xscrollincrement 1p -yscrollincrement 1p\n",
			tfp);
	if (!full_page) {
	    fputs("# Shift canvas by lower of bounding box\n", tfp);
	    fprintf(tfp, "$xfigCanvas xview scroll %d u\n",
			    round(llx/16.45*mag));
	    fprintf(tfp, "$xfigCanvas yview scroll %d u\n",
			    round(lly/16.45*mag));
	}

	fputs("pack $xfigCanvas\n\n", tfp);

	fputs("proc tint {color percent} {\n"
		"    foreach {red green blue} [winfo rgb . $color] {\n"
		"\tset red [expr {255 - ((65535-$red)/256)*$percent/100}]\n"
		"\tset green [expr {255 - ((65535-$green)/256)*$percent/100}]\n"
		"\tset blue [expr {255 - ((65535-$blue)/256)*$percent/100}]\n"
		"\t# break\n"
		"    }\n"
		"    return [format \"#%02x%02x%02x\" $red $green $blue]\n"
		"}\n\n", tfp);

	if (pats_used) {
		int	i;
		fputs(
"# If the files defining the stipple bitmaps should not be placed\n"
"# into the current directory, change the next line appropriately.\n", tfp);
		fprintf(tfp, "set %s .\n\n", xbmPathVar + 1);
		for (i = 0; i < NUMPATTERNS; ++i) {
			if (pattern_used[i])
				define_pattern(i);
		}

	}
	fputs("# The xfig objects begin here.\n", tfp);
}

/*
 *   g e n T k E n d ( )
 *
 *   Last call!...
 */

int
gentk_end()
{
	fprintf(tfp, "focus %s\n", canvas);

	/* all ok */
	return 0;
}

/*
 *   g e n T k A r c ( )
 *
 *   The Fig arc is one of the few objects that is only a subset of its
 *   equivalent Tk canvas object, since a Tk arc can be oval.  But that
 *   has no bearing on the code written here, so this is a pretty
 *   useless comment...
 */

void
gentk_arc(F_arc *a)
{
	/* print any comments prefixed with "#" */
	print_comments("# ",a->comments, "");

	if (a->type == T_OPEN_ARC) {
	       if (a->for_arrow || a->back_arrow)
		       fputs("gentk_arc: arc arrows not supported by Tk.\n",
					stderr);
	       if (a->fill_style != UNFILLED) {
		       /* (ab)use a->thickness to pass information to tkArc() */
		       int	save_thickness = a->thickness;
		       a->thickness = 0;
		       /* draw the fill without the outline*/
		       drawFilledShape(tkArc, (void *)a, 0, 0, a->fill_color,
					a->fill_style, 0, 0.0);
		       a->thickness = save_thickness;
	       }
	       /* draw the outline */
	       if (a->thickness > 0)
		       drawFilledShape(tkArc, (void *)a, a->thickness,
					a->pen_color, 0, UNFILLED, a->style,
					a->style_val);
	} else {
		drawFilledShape(tkArc, (void *)a, a->thickness, a->pen_color,
				a->fill_color, a->fill_style, a->style,
				a->style_val);
	}
}

/*
 *   g e n t T k E l l i p s e ( )
 */

void
gentk_ellipse(F_ellipse *e)
{
	/* print any comments prefixed with "#" */
	print_comments("# ", e->comments, "");

	drawFilledShape(tkEllipse, (void *)e, e->thickness, e->pen_color,
			e->fill_color, e->fill_style, e->style, e->style_val);
}

/*
 *   g e n T k L i n e ( )
 */

void
gentk_line(F_line *l)
{
	/* print any comments prefixed with "#" */
	print_comments("# ", l->comments, "");

	switch (l->type) {
	case T_POLYLINE:
		if (l->fill_style != UNFILLED && l->points->next &&
				l->points->next->next)
			/* Take care of filled regions first. */
			drawFilledShape(tkPolygon, (void *)l->points, 0, 0,
					l->fill_color, l->fill_style, 0, 0.0);
		/* Now draw line itself. */
		tkLine((void *)l, l->pen_color, l->thickness/15, l->style,
				l->style_val);
		break;
	case T_PIC_BOX:
		drawBitmap(l);
		break;
	case T_ARC_BOX:
		fprintf(stderr, "gentk_line: arc box not supported.\n");
		/* the comment below silences gcc's -Wimplicit-fallthrough */
		/* intentionally fall through */
	case T_BOX:
	case T_POLYGON:
		drawFilledShape(tkPolygon, (void *)l->points, l->thickness,
				l->pen_color, l->fill_color, l->fill_style,
				l->style, l->style_val);
		break;
	default:
		fprintf(stderr,"gentk_line: Whatchew talkin' 'bout, Willis?\n");
		break;
	}
}

/*
 *   d r a w B i t m a p ( )
 */

#define	ReadOK(file,buffer,len)	(fread(buffer, len, 1, file) != 0)

static void
drawBitmap(F_line *l)
{
	char			stfp[256];
	double			dx, dy;
	F_pic			*p;
	unsigned char		buf[16];
	int			stat;
	struct xfig_stream	pic_stream;

	p = l->pic;

	dx = l->points->next->next->x - l->points->x;
	dy = l->points->next->next->y - l->points->y;
	if (!(dx >= 0. && dy >= 0.))
		put_msg("Rotated images not supported by Tk.");

	/* see if GIF first */

	init_stream(&pic_stream);
	if (open_stream(p->file, &pic_stream) == NULL) {
		put_msg("Cannot open image file %s", p->file);
		free_stream(&pic_stream);
		return;
	}

	/* read header */
	stat = ReadOK(pic_stream.fp, buf, 7);
	if (!stat) {
		put_msg("Image file %s too short", p->file);
		close_stream(&pic_stream);
		free_stream(&pic_stream);
		return;
	}

	/* see if GIF or PPM (ASCII or binary) */
	if ((strncmp((char *) buf,"GIF",3) == 0) ||
			(strncmp((char *) buf,"P3\n",3) == 0) ||
			(strncmp((char *) buf,"P6\n",3) == 0)) {
		/* GIF or PPM allright, create the image command */
		/* first make a name without the suffix */
		char	*pname, *dot;

		pname = strdup(p->file);
		if ((dot=strchr(pname,'.')))
			*dot='\0';
		/* image create */
		fprintf(tfp, "image create photo %s -file %s\n\n",
				pname, p->file);
		/* now the canvas image */
		fprintf(tfp, "%s create image %fi %fi -anchor nw -image %s\n",
				canvas, X(l->points->x), Y(l->points->y),
				pname);
		free(pname);
	} else {
		/* Try for an X Bitmap file format. */
		unsigned int dummy;
		rewind_stream(&pic_stream);
		if (ReadFromBitmapFile(pic_stream.fp, &dummy, &dummy,
								&p->bitmap)) {
			sprintf(stfp, "%s create bitmap %fi %fi -anchor nw",
					canvas,
					X(l->points->x), Y(l->points->y));
			niceLine(stfp);
			sprintf(stfp, " -bitmap @%s", p->file);
			niceLine(stfp);
			if (l->pen_color != BLACK_COLOR &&
					l->pen_color != DEFAULT) {
				sprintf(stfp, " -foreground #%6.6x",
						rgbColorVal(l->pen_color));
				niceLine(stfp);
			}
			/* niceLine("\n"); wrong, I believe; T. Loimer, 2018 */
			if (l->fill_color != UNFILLED) {
				sprintf(stfp, " -background #%6.6x",
						rgbColorVal(l->fill_color));
				niceLine(stfp);
			}
			fputc('\n', tfp);
		} else
			put_msg("Only X bitmap and GIF picture objects "
					"are supported in Tk canvases.");
	}
	close_stream(&pic_stream);
	free_stream(&pic_stream);
}

/*
 *   g e n T k T e x t ( )
 */

/* define the latex fonts in terms of the postscript fonts */
#define latexFontDefault	0
#define latexFontRoman		1
#define latexFontBold		3
#define latexFontItalic		2
#define latexFontSansSerif	17
#define latexFontTypewriter	13

void
gentk_text(F_text * t)
{
	extern FILE	*tfp;
	size_t		i;

	/* I'm sure I'm just too dense to have seen a better way of doing this... */
	static struct {
		char	*prefix,
			*suffix;
	} fontNames[36] = {
		{"-adobe-times-medium-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-times-medium-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-times-medium-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-times-bold-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-times-bold-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc avant garde-medium-r-normal-sans-",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc avant garde-medium-o-normal-sans-",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc avant garde-demi-r-normal-sans-",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc avant garde-demi-o-normal-sans-",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc bookman-light-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc bookman-light-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc bookman-demi-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-urw-itc bookman-demi-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-courier-medium-r-normal--",
			"-0-0-0-m-0-iso8859-1"},
		{"-adobe-courier-medium-o-normal--",
			"-0-0-0-m-0-iso8859-1"},
		{"-adobe-courier-bold-r-normal--",
			"-0-0-0-m-0-iso8859-1"},
		{"-adobe-courier-bold-o-normal--",
			"-0-0-0-m-0-iso8859-1"},
		{"-adobe-helvetica-medium-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-medium-o-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-bold-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-bold-o-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-medium-r-narrow--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-medium-o-narrow--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-bold-r-narrow--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-helvetica-bold-o-narrow--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-new century schoolbook-medium-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-new century schoolbook-medium-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-new century schoolbook-bold-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-new century schoolbook-bold-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-palatino-medium-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-palatino-medium-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-palatino-bold-r-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-adobe-palatino-medium-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"--symbol-medium-r-normal--",
			"-0-0-0-p-0-*-*"},
		{"-*-itc zapf chancery-medium-i-normal--",
			"-0-0-0-p-0-iso8859-1"},
		{"-*-itc zapf dingbats-medium-r-normal--",
			"-0-0-0-p-0-*-*"}
	};

	/* print any comments prefixed with "#" */
	print_comments("# ",t->comments, "");

	if (t->angle != 0.)
	    fprintf(stderr, "gentk_text: rotated text not supported by Tk.\n");

	fprintf(tfp, "%s create text %fi %fi", canvas, X(t->base_x),
		Y(t->base_y));
	fputs(" -text \"", tfp);
	for (i = 0; i < strlen(t->cstring); ++i) {
		if (t->cstring[i] == '"')
			fputc('\\', tfp);
		fputc(t->cstring[i], tfp);
	}
	fputs("\" \\\n", tfp);
	switch (t->type) {
	case T_LEFT_JUSTIFIED:
	case DEFAULT:
		fprintf(tfp, " -anchor sw");
		break;
	case T_CENTER_JUSTIFIED:
		/* The Tk default. */
		fprintf(tfp, " -anchor s");
		break;
	case T_RIGHT_JUSTIFIED:
		fprintf(tfp, " -anchor se");
		break;
	default:
		fprintf(stderr, "gentk_text: Unknown text justification\n");
		t->type = T_LEFT_JUSTIFIED;
		break;
	}

	if (psfont_text(t)) {
		fprintf(tfp, " -font \"%s%d%s\"", fontNames[t->font+1].prefix,
			(int) (t->size*mag), fontNames[t->font+1].suffix);
	} else {	/* Rigid, special, and LaTeX fonts. */
		int fnum;

		switch (t->font) {
		case 0:	/* Default font. */
			fnum = latexFontDefault;
			break;
		case 1:	/* Roman. */
			fnum = latexFontRoman;
			break;
		case 2:	/* Bold. */
			fnum = latexFontBold;
			break;
		case 3:	/* Italic. */
			fnum = latexFontItalic;
			break;
		case 4:	/* Sans Serif. */
			fnum = latexFontSansSerif;
			break;
		case 5:	/* Typewriter. */
			fnum = latexFontTypewriter;
			break;
		default:
			fnum = latexFontDefault;
			fprintf(stderr, "gentk_text: unknown LaTeX font.\n");
			break;
		}
		fprintf(tfp, " -font \"%s%d%s\"", fontNames[fnum].prefix,
			(int) (t->size*mag), fontNames[fnum].suffix);
	}
	if (t->color != BLACK_COLOR && t->color != DEFAULT) {
		fprintf(tfp, " -fill #%6.6x", rgbColorVal(t->color));
	}

	fputc('\n', tfp);
}

/*
 *   b e z i e r S p l i n e ( )
 *
 *   We could use the "-smooth" option of Tk's "line" canvas object to
 *   get a Bezier spline.  But just to be sure everything is identical,
 *   we'll do it ourselves.  All spline routines were blatantly swiped
 *   from genibmgl.c with only non-mathematical mods.
 */

#define		THRESHOLD	.05	/* inch */

static void
bezierSpline(double a0, double b0, double a1, double b1, double a2, double b2,
	double a3, double b3)
{
	char	stfp[64];
	double	x0, y0, x3, y3;
	double	sx1, sy1, sx2, sy2, tx, ty, tx1, ty1, tx2, ty2, xmid, ymid;

	x0 = a0; y0 = b0;
	x3 = a3; y3 = b3;
	if (fabs(x0 - x3) < THRESHOLD && fabs(y0 - y3) < THRESHOLD) {
		sprintf(stfp, " %.4f %.4f", x3, y3);
		niceLine(stfp);
	} else {
		tx   = (a1  + a2 )/2.0;	ty   = (b1  + b2 )/2.0;
		sx1  = (x0  + a1 )/2.0;	sy1  = (y0  + b1 )/2.0;
		sx2  = (sx1 + tx )/2.0;	sy2  = (sy1 + ty )/2.0;
		tx2  = (a2  + x3 )/2.0;	ty2  = (b2  + y3 )/2.0;
		tx1  = (tx2 + tx )/2.0;	ty1  = (ty2 + ty )/2.0;
		xmid = (sx2 + tx1)/2.0;	ymid = (sy2 + ty1)/2.0;

		bezierSpline(x0, y0, sx1, sy1, sx2, sy2, xmid, ymid);
		bezierSpline(xmid, ymid, tx1, ty1, tx2, ty2, x3, y3);
	}
}

/*
 *   g e n T k I t p S p l i n e ( )
 */

static void
gentk_itpSpline(F_spline *s)
{
	char		dir[8], stfp[256];
	F_arrow		*a;
	F_point		*p1, *p2;
	F_control	*cp1, *cp2;
	double		x1, x2, y1, y2;

	p1 = s->points;
	cp1 = s->controls;
	x2 = p1->x/ppi; y2 = p1->y/ppi;

	sprintf(stfp, "%s create line %.4f %.4f", canvas, x2, y2);
	niceLine(stfp);
	for (p2 = p1->next, cp2 = cp1->next; p2 != NULL;
		p1 = p2, cp1 = cp2, p2 = p2->next, cp2 = cp2->next) {

		x1	 = x2;
		y1	 = y2;
		x2	 = p2->x/ppi;
		y2	 = p2->y/ppi;
		bezierSpline(x1, y1, (double)cp1->rx/ppi, cp1->ry/ppi,
			(double)cp2->lx/ppi, cp2->ly/ppi, x2, y2);
	}

	a = NULL;
	if (s->for_arrow && !s->back_arrow) {
		a = s->for_arrow;
		strcpy(dir, "last");
	} else if (!s->for_arrow && s->back_arrow) {
		a = s->back_arrow;
		strcpy(dir, "first");
	} else if (s->for_arrow && s->back_arrow) {
		a = s->back_arrow;
		strcpy(dir, "both");
	}
	if (a)
		switch (a->type) {
		case 0:	/* Stick type. */
			sprintf(stfp, " -arrow %s -arrowshape {0 %fi %fi}",
				dir, X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			fprintf(stderr, "Warning: stick arrows do not "
				"work well in Tk.\n");
			break;
		case 1:	/* Closed triangle. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		case 2:	/* Closed with indented butt. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, 0.8 * X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		case 3:	/* Closed with pointed butt. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, 1.2 * X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		default:
			fprintf(stderr, "tkLine: unknown arrow type.\n");
			break;
		}

	switch (s->cap_style) {
	case 0:	/* Butt (Tk default). */
		break;
	case 1:	/* Round. */
		sprintf(stfp, " -capstyle round");
		niceLine(stfp);
		break;
	case 2: /* Projecting. */
		sprintf(stfp, " -capstyle projecting");
		niceLine(stfp);
		break;
	default:
		fprintf(stderr, "tkLine: unknown cap style.\n");
		break;
	}

	if (s->thickness != 1) {
		sprintf(stfp, " -width %d", s->thickness);
		niceLine(stfp);
	}
	if (s->pen_color != BLACK_COLOR && s->pen_color != DEFAULT) {
		sprintf(stfp, " -fill #%6.6x", s->pen_color);
		niceLine(stfp);
	}
}

/*
 *   q u a d r a t i c S p l i n e ( )
 */

static void
quadraticSpline(double a1, double b1, double a2, double b2, double a3,
	double b3, double a4, double b4)
{
	char	stfp[64];
	double	x1, y1, x4, y4;
	double	xmid, ymid;

	x1	 = a1; y1 = b1;
	x4	 = a4; y4 = b4;
	xmid	 = (a2 + a3)/2.0;
	ymid	 = (b2 + b3)/2.0;
	if (fabs(x1 - xmid) < THRESHOLD && fabs(y1 - ymid) < THRESHOLD) {
		sprintf(stfp, " %.4f %.4f;\n", xmid, ymid);
		niceLine(stfp);
	} else {
		quadraticSpline(x1, y1, ((x1+a2)/2.0), ((y1+b2)/2.0),
			((3.0*a2+a3)/4.0), ((3.0*b2+b3)/4.0), xmid, ymid);
	    }

	if (fabs(xmid - x4) < THRESHOLD && fabs(ymid - y4) < THRESHOLD) {
		sprintf(stfp, " %.4f %.4f", x4, y4);
		niceLine(stfp);
	} else {
		quadraticSpline(xmid, ymid, ((a2+3.0*a3)/4.0),
			((b2+3.0*b3)/4.0), ((a3+x4)/2.0), ((b3+y4)/2.0),
			x4, y4);
	}
}

/*
 *   g e n T k C t l S p l i n e ( )
 */

static void
gentk_ctlSpline(F_spline *s)
{
	char	dir[8], stfp[256];
	double	cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4;
	double	x1, y1, x2, y2;
	F_arrow	*a;
	F_point	*p;

	p	 = s->points;
	x1	 = p->x/ppi;
	y1	 = p->y/ppi;
	p	 = p->next;
	x2	 = p->x/ppi;
	y2	 = p->y/ppi;
	cx1	 = (x1 + x2)/2.0;
	cy1	 = (y1 + y2)/2.0;
	cx2	 = (x1 + 3.0*x2)/4.0;
	cy2	 = (y1 + 3.0*y2)/4.0;

	if (closed_spline(s)) {
		sprintf(stfp, "%s create polygon %.4f %.4f", canvas, cx1, cy1);
		niceLine(stfp);
	} else {
		sprintf(stfp, "%s create line", canvas);
		niceLine(stfp);
	}

	for (p = p->next; p != NULL; p = p->next) {
		x1	 = x2;
		y1	 = y2;
		x2	 = p->x/ppi;
		y2	 = p->y/ppi;
		cx3	 = (3.0*x1 + x2)/4.0;
		cy3	 = (3.0*y1 + y2)/4.0;
		cx4	 = (x1 + x2)/2.0;
		cy4	 = (y1 + y2)/2.0;
		quadraticSpline(cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4);
		cx1	 = cx4;
		cy1	 = cy4;
		cx2	 = (x1 + 3.0*x2)/4.0;
		cy2	 = (y1 + 3.0*y2)/4.0;
	}
	x1	 = x2;
	y1	 = y2;
	p	 = s->points->next;
	x2	 = p->x/ppi;
	y2	 = p->y/ppi;
	cx3	 = (3.0*x1 + x2)/4.0;
	cy3	 = (3.0*y1 + y2)/4.0;
	cx4	 = (x1 + x2)/2.0;
	cy4	 = (y1 + y2)/2.0;
	if (closed_spline(s))
		quadraticSpline(cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4);

	if (closed_spline(s)) {
		if (s->pen_color == NONE) {
			sprintf(stfp, " -outline {}");
			niceLine(stfp);
		} else {
			sprintf(stfp, " -outline #%6.6x", s->pen_color);
			niceLine(stfp);
		}
		if (s->fill_color == NONE) {
			sprintf(stfp, " -fill {}");
			niceLine(stfp);
		} else {
			sprintf(stfp, " -fill #%6.6x", s->fill_color);
			niceLine(stfp);
		}
		if (s->fill_style != NONE) {
			sprintf(stfp, " -stipple @$%s%d",
				patname, s->fill_style - NUMSHADES - NUMTINTS);
			niceLine(stfp);
		}
		if (s->thickness != 1) {
			sprintf(stfp, " -width %d", s->thickness);
			niceLine(stfp);
		}
	} else {

		a = NULL;
		if (s->for_arrow && !s->back_arrow) {
			a = s->for_arrow;
			strcpy(dir, "last");
		} else if (!s->for_arrow && s->back_arrow) {
			a = s->back_arrow;
			strcpy(dir, "first");
		} else if (s->for_arrow && s->back_arrow) {
			a = s->back_arrow;
			strcpy(dir, "both");
		}
		if (a)
			switch (a->type) {
			case 0:	/* Stick type. */
				sprintf(stfp, " -arrow %s -arrowshape "
					"{0 %fi %fi}",
					dir, X(a->ht), X(a->wid)/2.);
				niceLine(stfp);
				fprintf(stderr, "Warning: stick arrows do not "
					"work well in Tk.\n");
				break;
			case 1:	/* Closed triangle. */
				sprintf(stfp, " -arrow %s -arrowshape "
					"{%fi %fi %fi}",
					dir, X(a->ht), X(a->ht), X(a->wid)/2.);
				niceLine(stfp);
				break;
			case 2:	/* Closed with indented butt. */
				sprintf(stfp, " -arrow %s -arrowshape "
					"{%fi %fi %fi}", dir, 0.8 * X(a->ht),
					X(a->ht), X(a->wid)/2.);
				niceLine(stfp);
				break;
			case 3:	/* Closed with pointed butt. */
				sprintf(stfp, " -arrow %s -arrowshape "
					"{%fi %fi %fi}", dir, 1.2 * X(a->ht),
					X(a->ht), X(a->wid)/2.);
				niceLine(stfp);
				break;
			default:
				fprintf(stderr, "tkLine: unknown arrow type.\n");
				break;
			}

		switch (s->cap_style) {
		case 0:	/* Butt (Tk default). */
			break;
		case 1:	/* Round. */
			sprintf(stfp, " -capstyle round");
			niceLine(stfp);
			break;
		case 2: /* Projecting. */
			sprintf(stfp, " -capstyle projecting");
			niceLine(stfp);
			break;
		default:
			fprintf(stderr, "tkLine: unknown cap style.\n");
			break;
		}

		if (s->thickness != 1) {
			sprintf(stfp, " -width %d", s->thickness);
			niceLine(stfp);
		}
		if (s->pen_color != BLACK_COLOR && s->pen_color != DEFAULT) {
			sprintf(stfp, " -fill #%6.6x", s->pen_color);
			niceLine(stfp);
		}
	}
}

/*
 *   g e n T k S p l i n e ( )
 */

void gentk_spline(F_spline *s)
{
	/* print any comments prefixed with "#" */
	print_comments("# ",s->comments, "");

	if (int_spline(s))
		gentk_itpSpline(s);
	else
		gentk_ctlSpline(s);
}

/*
 *   d r a w F i l l e d S h a p e ( )
 *
 *   Call (*tkShape)() and add the " -fill", " -stipple", " -outline" etc
 *   options as appropriate.
 */

static void
drawFilledShape(void (*tkShape)(), void *p, int thickness, int penColor,
	int fillColor, int fillStyle, int style, double style_val)
{
	char	sftp[256];

	/* Draw filled and/or stippled region enclosed by shape. */
	if (fillStyle >= NUMSHADES + NUMTINTS) { /* has a stipple pattern */
		/* Draw the shape, fill it with the background color. */
		tkShape(p);
		sprintf(sftp, " -fill #%.6x -outline {} -width 0\n",
				rgbColorVal(fillColor));
		niceLine(sftp);

		/* Again draw the shape and specify the pattern. */
		tkShape(p);
		sprintf(sftp, " -fill #%.6x -stipple @$%s%d",
				rgbColorVal(penColor), patname,
				fillStyle - NUMSHADES - NUMTINTS);
		niceLine(sftp);
		/* outline and width are specified further below */

	} else if (fillStyle != UNFILLED) {
		tkShape(p);
		/* fill with a shaded, tinted, or fully saturated color */
		if (fillStyle > WHITE_FILL && fillStyle < BLACK_FILL) {
			if (fillColor == BLACK_COLOR || fillColor == DEFAULT) {
				fillColor = WHITE_COLOR;
				fillStyle = BLACK_FILL - fillStyle;
			}
			sprintf(sftp, " -fill [::tk::Darken #%.6x %d]",
					rgbColorVal(fillColor), fillStyle * 5);
			niceLine(sftp);
		} else if (fillStyle > BLACK_FILL &&
				fillStyle < NUMSHADES + NUMTINTS - 1) {
			sprintf(sftp, " -fill [tint #%.6x %d]",
				rgbColorVal(fillColor),
				(NUMSHADES + NUMTINTS - 1 - fillStyle) * 5);
			niceLine(sftp);
		} else { /* fillStyle == WHITE_FILL || BLACK_FILL ||
					NUMSHADES + NUMTINTS - 1 */
			if (fillStyle == WHITE_FILL) {
				if (fillColor == BLACK_COLOR)
					fillColor = WHITE_COLOR;
				else
					fillColor = BLACK_COLOR;
			} else if (fillStyle == NUMSHADES + NUMTINTS - 1) {
				fillColor = WHITE_COLOR;
			} /* else, fillStyle == BLACK_FILL */
			sprintf(sftp, " -fill #%.6x", rgbColorVal(fillColor));
			niceLine(sftp);
		}
	} else {	/* fillStyle == UNFILLED */
		tkShape(p);
	}

	/* outline color and thickness */
	if (thickness > 0) {
		sprintf(sftp, " -outline #%.6x", rgbColorVal(penColor));
		niceLine(sftp);
		if (thickness != 15) {
			sprintf(sftp, " -width %d", thickness/15);
			niceLine(sftp);
		}

		/* dash pattern */
		tk_setstyle(style, style_val);
	} else {
		strcpy(sftp, " -outline {} -width 0");
		niceLine(sftp);
	}
	fputc('\n', tfp);
}


/*
 *   t k A r c ( )
 *
 *   Generate the Tk canvas item for an arc.  Xfig does not have a Tk chord
 *   style arc. Use either Tk arc style or Tk pieslice style for the outline
 *   and TK chord style for filling Tk arc style.
 */

void
tkArc(void *shape)
{
	char	stfp[256];
	double	cx, cy,	/* Center of circle containing arc. */
		sx, sy,	/* Start point of arc. */
		ex, ey,	/* Stop point of arc. */
		angle1, angle2, extent, radius, startAngle;
	F_arc	*a;

	a = (F_arc *)shape;
	cx = X(a->center.x);		/* Center. */
	cy = Y(a->center.y);
	sx = X(a->point[0].x) - cx;	/* Start point. */
	sy = cy - Y(a->point[0].y);
	ex = X(a->point[2].x) - cx;	/* End point. */
	ey = cy - Y(a->point[2].y);

	radius = sqrt(sy*sy + sx*sx);
	angle1 = atan2(sy, sx) * 180.0 / M_PI;
	if (angle1 < 0.)
		angle1 += 360.;
	angle2 = atan2(ey, ex) * 180.0 / M_PI;
	if (angle2 < 0.)
		angle2 += 360.;

	if (a->direction == 1) {	/* Counter-clockwise. */
		startAngle = angle1;
		extent = angle2 - angle1;
	} else {			/* Clockwise. */
		startAngle = angle2;
		extent = angle1 - angle2;
	}
	if (extent < 0.)		/* Sweep of arc. */
		extent += 360.;

	sprintf(stfp, "%s create arc", canvas);
	niceLine(stfp);
	/* Coords of bounding rectangle. */
	sprintf(stfp, " %.3fi %.3fi %.3fi %.3fi",
		cx-radius, cy-radius, cx+radius, cy+radius);
	niceLine(stfp);
	/* Start angle in degrees and its extent in degrees. */
	sprintf(stfp, " -start %f -extent %f", startAngle, extent);
	niceLine(stfp);

	switch (a->type) {
	case T_OPEN_ARC:
		if (a->thickness > 0)
			strcpy(stfp, " -style arc");
		else
			strcpy(stfp, " -style chord");
		niceLine(stfp);
		break;
	case T_PIE_WEDGE_ARC:
		strcpy(stfp, " -style pieslice");
		niceLine(stfp);
		break;
	default:
		fprintf(stderr, "tkArc: unknown arc type.\n");
		break;
	}
}

/*
 *   t k E l l i p s e ( )
 */

void
tkEllipse(void *shape)
{
	char		stfp[256];
	F_ellipse	*e;

	e = (F_ellipse *)shape;
	sprintf(stfp, "%s create oval %fi %fi %fi %fi",
			canvas,
			X(e->center.x - e->radiuses.x),
			Y(e->center.y - e->radiuses.y),
			X(e->center.x + e->radiuses.x),
			Y(e->center.y + e->radiuses.y));
	niceLine(stfp);
}

/*
 *   t k L i n e ( )
 */

static void
tkLine(F_line *l, int penColor, int thickness, int style, double style_val)
{
	char		dir[8], stfp[256];
	extern char	*canvas;	/* Tk canvas name. */
	F_arrow		*a;
	F_point		*p, *q;

	p = l->points;
	q = p->next;

	if (q == NULL) {
		/* Degenerate line (single point). */
		sprintf(stfp, "%s create line %fi %fi %fi %fi",
			canvas, X(p->x), Y(p->y), X(p->x), Y(p->y));
		niceLine(stfp);
	} else {
		sprintf(stfp, "%s create line", canvas);
		niceLine(stfp);
		sprintf(stfp, " %fi %fi", X(p->x), Y(p->y));
		niceLine(stfp);
		for ( /* No op. */ ; q != NULL; q = q->next) {
			sprintf(stfp, " %fi %fi", X(q->x), Y(q->y));
			niceLine(stfp);
		}
	}

	a = NULL;
	if (l->for_arrow && !l->back_arrow) {
		a = l->for_arrow;
		strcpy(dir, "last");
	} else if (!l->for_arrow && l->back_arrow) {
		a = l->back_arrow;
		strcpy(dir, "first");
	} else if (l->for_arrow && l->back_arrow) {
		a = l->back_arrow;
		strcpy(dir, "both");
	}
	if (a)
		switch (a->type) {
		case 0:	/* Stick type. */
			sprintf(stfp, " -arrow %s -arrowshape {0 %fi %fi}",
				dir, X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			fputs("Warning: stick arrows do not work well in Tk.\n",
					stderr);
			break;
		case 1:	/* Closed triangle. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		case 2:	/* Closed with indented butt. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, 0.8 * X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		case 3:	/* Closed with pointed butt. */
			sprintf(stfp, " -arrow %s -arrowshape {%fi %fi %fi}",
				dir, 1.2 * X(a->ht), X(a->ht), X(a->wid)/2.);
			niceLine(stfp);
			break;
		default:
			fputs("tkLine: unknown arrow type.\n", stderr);
			break;
		}

	/* set line style here */
	tk_setstyle(style, style_val);

	switch (l->join_style) {
	    case 0:	/* Miter (Tk default). */
		break;
	    case 1:	/* Round. */
		sprintf(stfp, " -joinstyle round");
		niceLine(stfp);
		break;
	    case 2:	/* Bevel. */
		sprintf(stfp, " -joinstyle bevel");
		niceLine(stfp);
		break;
	    default:
		fputs("tkLine: unknown join style.\n", stderr);
		break;
	}

	switch (l->cap_style) {
	    case 0:	/* Butt (Tk default). */
		break;
	    case 1:	/* Round. */
		sprintf(stfp, " -capstyle round");
		niceLine(stfp);
		break;
	    case 2: /* Projecting. */
		sprintf(stfp, " -capstyle projecting");
		niceLine(stfp);
		break;
	    default:
		fputs("tkLine: unknown cap style.\n", stderr);
		break;
	}

	if (thickness != 1) {
		sprintf(stfp, " -width %d", thickness);
		niceLine(stfp);
	}
	if (penColor != BLACK_COLOR && penColor != DEFAULT) {
		sprintf(stfp, " -fill #%6.6x", rgbColorVal(penColor));
		niceLine(stfp);
	}
	fputc('\n', tfp);
}

/*
 *   t k P o l y g o n ( )
 */

static void
tkPolygon(void *points)
{
	char		stfp[256];
	extern char	*canvas;	/* Tk canvas name. */
	F_point		*p, *q;

	p = (F_point *) points;

	sprintf(stfp, "%s create polygon %fi %fi", canvas, X(p->x), Y(p->y));
	niceLine(stfp);
	q = p->next;
	/* emit all but the last point */
	while (q->next != NULL) {
		sprintf(stfp, " %fi %fi", X(q->x), Y(q->y));
		niceLine(stfp);
		q = q->next;
	}
	/*
	 * tkPolygon may be used to fill a line, or to draw and optionally fill
	 * a polygon. Check, whether the last point must be emitted.
	 */
	if (q->x != p->x || q->y != p->y) {
		sprintf(stfp, " %fi %fi", X(q->x), Y(q->y));
		niceLine(stfp);
	}
}

static void
tk_setstyle(int style, double v)
{
	char		stfp[200];
	const int	one = 1;

	v *= 96./80.;		/* Assume 96 screen pixels to the inch. */

	if (style == SOLID_LINE) {
		return;
	} else if (style == DASH_LINE) {
		if (v > 0.0)
			sprintf(stfp, " -dash {%d %d}", round(v), round(v));
	} else if (style == DOTTED_LINE) {
		if (v > 0.0)
			sprintf(stfp, " -dash {%d %d}", one, round(v));
	} else if (style == DASH_DOT_LINE) {
		if (v > 0.0)
			sprintf(stfp, " -dash {%d %d %d %d}", round(v),
					round(v*0.5), one, round(v*0.5));
	} else if (style == DASH_2_DOTS_LINE) {
		if (v > 0.0)
			sprintf(stfp, " -dash {%d %d %d %d %d %d}",
					round(v), round(v*0.45), one,
					round(v*0.333), one, round(v*0.45));
	} else if (style == DASH_3_DOTS_LINE) {
		if (v > 0.0)
			sprintf(stfp, " -dash {%d %d %d %d %d %d %d %d}",
					round(v), round(v*0.4), one,
					round(v*0.3), one, round(v*0.3), one,
					round(v*0.4));
	} else {
		return;
	}

	niceLine(stfp);
}

/*
 *   r g b C o l o r V a l ( )
 *
 *   Given an indexi into either the standard color list or into the
 *   user defined color list, return the hex RGB value of the color.
 */

static unsigned int
rgbColorVal(int colorIndex)
{
	/* extern User_color	user_colors[];	declared in fig2dev.h	*/
	unsigned int	rgb;
	static unsigned int	rgbColors[NUM_STD_COLS] = {
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
		rgb = ((user_colors[colorIndex-NUM_STD_COLS].r & 0xff) << 16)
			| ((user_colors[colorIndex-NUM_STD_COLS].g & 0xff) << 8)
			| (user_colors[colorIndex-NUM_STD_COLS].b & 0xff);
	return rgb;
}

/*
 *   n i c e L i n e ( )
 *
 *   Instead of directly calling fprintf()'s, this routine is used so
 *   that lines are printed that are 80 characters long, give or take
 *   a handful.  Otherwise - spline routines in particular - will generate
 *   humongously long lines that are a pain in the butt to edit...
 */

static void
niceLine(char *s)
{
	extern FILE	*tfp;	/* File descriptor of Tk file. */
	int		i, len;
	static int	inQuote = 0;
	static int	pos = 0;

	len = strlen(s);
	for (i = 0; i < len; ++i) {
		if (s[i] == '"') {
			inQuote ^= 1;	/* Flip between 0/1. */
			putc(s[i], tfp);
			++pos;
		} else if (!inQuote && (pos > 80) && (s[i] == ' ')) {
			fprintf(tfp, " \\\n  ");
			pos = 2;
		} else {
			putc(s[i], tfp);
			if (s[i] == '\n')
				pos = 0;
			else
				++pos;
		}
	}
}

/*
 *   d e v _ t k
 *
 *   The wrapper used by fig2dev to
 *   isolate the device specific details.
 */

struct driver	dev_tk = {
	gentk_option,
	gentk_start,
	gendev_nogrid,
	gentk_arc,
	gentk_ellipse,
	gentk_line,
	gentk_spline,
	gentk_text,
	gentk_end,
	INCLUDE_TEXT
};
