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
 *
 * gengbx.c: convert fig to GBX
 *
 * Author: Edward Grace <edward.grace@gmail.com>
 *
 *
 * Output Gerber files using the lowest common denominator.
 *
 * Gerber is a file format for the CAD of PCBs.  This code produces
 * output which (should) conform to the specification for RS-247-X
 * described in the following document.
 *
 * http://members.optusnet.com.au/~eseychell/rs274xrevd_e.pdf
 *
 * I have taken care to make sure that join styles and end caps are
 * honoured in the export to Gerber.  Many FIG primitives cannot be
 * faithfully reproduced in Gerber. For example.
 *
 *   -) Colour - Only black or "default" coloured items are exported.
 *   -) Ellipses - Ignored.
 *   -) Curved splies - Cannot be faithfully reproduced.
 *   -) Hatched or non uniform fills - Not supported.
 *   -) Dashed lines - Not suported.
 *   -) Fancy end caps (arrows etc.) - Not supported
 *   -) Multiple layers - These are flattened to one layer.  Gerber does
 *      support multiple layers, however there is currently no option
 *      to preserve these.
 *
 * It should be realised that Gerber is _not_ a well supported
 * standard and various output devices do not honour certain aspects
 * of it.  Good luck!
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
#include "alloc.h"
#include "creationdate.h"
#include "messages.h"

#define GBX_DRIVER_VERSION "0.1.1"
#define MAX_APERTURES 989
#define GBX_BUF_SIZE 1024

/* Enumeration for units to use in output.  Inches are natural to FIG. */
enum gbx_units { units_mm, units_inches };

/* Number of leading and trailing digits around the decimal point.*/
static unsigned int gbx_before = 3u;
static unsigned int gbx_after  = 5u;
/* Dimensions to assume for output */
static int gbx_dimensions = units_mm;
/* Scale factor to ascribe to the output image. */
static float gbx_scale_factor_a = 1;
static float gbx_scale_factor_b = 1;
/* Image polarity. 0->positive 1->negative. */
static int gbx_image_polarity = 1;
/* Offset in a and b axis */
static float gbx_offset_a = 0, gbx_offset_b = 0;
/* Should we include debug comments in GBX? */
static int gbx_debug_comments = 0;

/* Warning stack. */
enum warnings { warn=0, warn_square_join,
		warn_filled_poly_with_line,
		warn_open_filled_polygon,
		warn_open_filled_arc,
		warn_text_unsupported,
		warn_ellipse_unsupported,
		warn_spline_not_implemented,
		warn_arrow_not_implemented,
		warn_line_colour,
		warn_line_zero_width,
		warn_max };
static int warning_counts[warn_max];

/* TODO - These should be defined from FIG, as they may change */
enum pen_colours { p_colour_default = -1,
		   p_colour_black = 0,
		   p_colour_max };

/* TODO - These should be defined from FIG, as they may change */
enum fill_colours { f_colour_red = 0 };

/* Output a warning regarding a certain type of primative once,
   keeping track of the number of times the warning has been given. */
static void
warn_once(long int warning_type, const char *message)
{
	if (warning_counts[warning_type])
		return;

	fprintf(stderr, "Warning: %s\n",message);
	++warning_counts[warning_type];
}

/* bool to state if the plotter exposure is on or not. */
static unsigned long int is_exposure=1;

/* Return the length of a vector. */
static double
length (long int x1, long int y1, long int x2, long int y2)
{
	double deltax=(double)(x2-x1), deltay=(double)(y2-y1);
	double l=0;
	if (fabs(deltax) > fabs(deltay)) {
		l = fabs(deltax) * sqrt(1.0 + (deltay/deltax)*(deltay/deltax));
	} else {
		l = fabs(deltay) * sqrt(1.0 + (deltax/deltay)*(deltax/deltay));
	}
	return l;
}

/* enums describing FIG styles etc. */
enum cap_styles { cap_style_butt=0, cap_style_round, cap_style_square };

/* enums describing FIG fill styles. */
enum fill_styles { fill_style_none=-1 };

static unsigned long int gbx_scale_factor;

/* Fundemental scaling parameters. */
#define INCH2MM  25.4
#define WIDTH_FIG2IN  (1.0/1200.0)
#define WIDTH_FIG2MM  (25.4/1200.0)

#define XY_FIG2IN (1.0/1200.0)
#define XY_FIG2MM (XY_FIG2IN * INCH2MM)

static char outbuf[GBX_BUF_SIZE];

static void write_end_block(void);
void gengbx_line (F_line *l);

/* Parameter counts.  Used for internal validataion. */
// static unsigned long int count_begin_param=0;
// static unsigned long int count_end_param=0;
static unsigned long int count_data_block = 0;

/* Last code type - keeps track of the type of code last written. */
enum code_types { g_code=0, m_code=1, d_code=2 };
static unsigned long int last_code_type=-1;
static unsigned long int last_code_value=-1;

/*
 * Begin a parameter.
 */
/*
static void
begin_param(void)
{
	fputs("%%", tfp);
	++count_begin_param;
}
*/

/*
 * End a parameter.
 */
/*
static void
end_param(void)
{
	fputs("%%\n", tfp);
	++count_end_param;
}
*/


/*
 * Enumerate M codes (misc codes)
 */
// static unsigned long int total_m_code_count=0;
enum m_codes { program_stop = 0, optional_stop = 1, end_of_program = 2 };
static void
write_m_code(enum m_codes m)
{
	fprintf(tfp, "M%02u",m);
	last_code_type = m_code;
	last_code_value = m;
	write_end_block();
}

/*
 * Check to see if the supplied colour is ok to output.  This is
 * useful for ignoring construction lines. By default only output
 * black lines or lines with colour "default".
 *
 * Need to add a command line option to disable this.
 */
static int
is_pen_colour_ok(long int colour)
{
	switch (colour) {
	case p_colour_black:
	case p_colour_default:
		return 1;
	}

	warn_once(warn_line_colour,
		"By default only objects with line colour "
	        "of \"default\" or  \"black\" are output.");
	return 0;
}

/*
 * Enumerate D codes (draft codes) selects apertures and determine if
 * the feature to be drawn should be a line or "flashed".
 */
// static unsigned long int total_d_code_count=0;
enum d_codes { d_exposure_on = 1, d_exposure_off = 2,
	       d_flash = 3, d_select_aperture = 10 };

/** Define the maximum aperture index. */
#define MAX_D_CODE 999
#define MAX_APERTURE_INDEX (MAX_D_CODE - d_select_aperture)



/** Keeps count of the number of defined apertures. */
static unsigned long int count_apertures = 0;

/** Keeps count of the number of defined simple circular apertures. */
static unsigned long int count_circ_aperture = 0;
static unsigned long int count_square_aperture = 0;
// static unsigned long int count_ellipse_aperture = 0;

/** Simple structure to represent simple circular apertures. */
struct ap_circ {
	double dia;
};

/** Simple structure to represent elliptical apertures. */
struct ap_ellipse {
	double w,h;
};

/** Square apertures. */
struct ap_square {
	double width;
};

/** Define a buffer containing all the apertures to be defined. */
static struct ap_circ		aperture_circ_list[MAX_APERTURE_INDEX];
static struct ap_square		aperture_square_list[MAX_APERTURE_INDEX];
// static struct ap_ellipse	aperture_ellipse_list[MAX_APERTURE_INDEX];


/**
  Test two numbers for equality.
  Comparison happened by string representation.
*/
static int
is_double_equal(double a, double b)
{
	const double	diff = 1e-6;
	return (a - diff < b && a + diff > b) ? 1 : 0;
}

/**
    Returns the index of any simple circle if it already exists.

    -1 if it does not exists.
*/
static int
test_ap_circ(double outer_dia)
{
	unsigned long int n;
	for (n = 0; n < count_circ_aperture; ++n) {
		/*    fprintf(stderr, "%f, %f\n",
				aperture_circ_list[n].dia, outer_dia); */
		if (is_double_equal(aperture_circ_list[n].dia,outer_dia)) {
			return n;
		}
	}
	return -1;
}


/**
    Returns the index of an elliptical aperture if it already exists.

    -1 if it does not exists.
*/
/*
static int
test_ap_ellipse(double w, double h)
{
	unsigned long int n;
	for (n = 0; n < count_ellipse_aperture; ++n) {
		if (is_double_equal(aperture_ellipse_list[n].w,w) &&
				is_double_equal(aperture_ellipse_list[n].h,h))
			return n;
	}
	return -1;
}
*/

static int
test_ap_square(double width)
{
	unsigned long int n;
	for (n = 0; n < count_square_aperture; ++n) {
		/* fprintf(stderr, "%f, %f\n",
			aperture_square_list[n].width, width); */
		if (is_double_equal(aperture_square_list[n].width,width) ) {
			return n;
		}
	}
	return -1;
}


/** Returns 1 if the aperture is defined, zero if not defined. */
/*
static int
is_aperture_defined(unsigned long int index)
{
	return index < count_apertures ? 1 : 0;
}
*/

unsigned long int total_g_code_count = 0 ;
/* Enumerate G (general function) codes. */
enum g_codes { move = 00, line_interp_1x = 01,
	       circ_interp_clock = 02, circ_interp_anti = 03,
	       ignore_data_block = 04,
	       lin_interp_10x = 10,
	       lin_interp_01x = 11,
	       lin_interp_001x = 12,
	       poly_area_fill_on = 36, poly_area_fill_off = 37,
	       tool_prepare = 54,
	       dim_inches = 70, dim_mm = 71,
	       circ_interp_disable = 74, circ_interp_enable = 75,
	       abs_meas = 90, rel_meas = 91 };


/*
 * Mark end of data block.  Do this inteligently.
 *
 * e.g. If the most recent data block is a comment add a new line.
 */
static void
write_end_block(void)
{
	fputs("*\n", tfp);
	++count_data_block;
}


/** Print the G code padded with zeros to produce two characters.
    e.g. G03 */
static void
write_g_code(enum g_codes g)
{
	fprintf(tfp, "G%02u", g);
	total_g_code_count++;
	last_code_type = g_code;
	last_code_value = g;
}

//extern long int  pagewidth, pageheight;

//int     vw, vh;

/** Convert the units from fig to gbx */
static double
width_fig2gbx(long int f)
{
	double conversion_factor =
		gbx_dimensions == units_mm ? XY_FIG2MM : XY_FIG2IN;
	return (double)(f * mag * conversion_factor);
}

/** Convert position units from fig to gbx */
static int
x_fig2gbx(long int f)
{
	double conversion_factor =
		gbx_dimensions == units_mm ? XY_FIG2MM : XY_FIG2IN;
	/* FIXIT Scaling by -ve number alters
	   clockwise -> anticlockwise and can screw up arcs. */
	return (int) (f * mag * conversion_factor * gbx_scale_factor);
}

/** Convert position units from fig to gbx */
static int
y_fig2gbx(long int f)
{
	double conversion_factor =
		gbx_dimensions == units_mm ? XY_FIG2MM : XY_FIG2IN;
	/* FIXIT - Scaling for y [b] axis, should be reversed. */
	return (int)(f * mag * conversion_factor * gbx_scale_factor);
}

/** Print a D code padded with zeros to produce two characters.

    e.g. D03 - Flash aperture.

    For D codes of 10 or greater this checks to see if an appropriate
    aperture has been defined and if it is in range.  If not it will
    produce an error and quit.
*/
static void
write_d_code(enum d_codes d)
{
	if (d < 10) {
		fprintf(tfp, "D%02u", d);
	} else {
		fprintf(tfp, "D%u", d);
	}
	last_code_type = d_code;
	last_code_value = d;
}

/** Switch off exposure of pen. */
static void
exposure_off(void)
{
	write_d_code(d_exposure_off);
	is_exposure = 0;
}

static void
exposure_on(void)
{
	write_d_code(d_exposure_on);
	is_exposure = 1;
}

/** Select an aperture to use for drawing. */
static void
use_aperture(long int aperture_index)
{
	write_g_code(tool_prepare);
	write_d_code((enum d_codes)(d_select_aperture + aperture_index));
	write_end_block();
}


/** Higher level functions for writing entities like comments,
    aperture declarations etc.
*/
static void
write_comment(const char *c)
{
	fprintf(tfp, "G%02i %s*\n", ignore_data_block, c);
}

/* Writes traceing output for the types of object */
static void
write_trace(const char *c)
{
	if (gbx_debug_comments)
		write_comment(c);
}

/** Output coordinate information to the file. */
static void
xy(long int x, long int y)
{
	fprintf(tfp, "X%iY%i", x_fig2gbx(x), y_fig2gbx(y));
}

/** Draw from the current point to the final point specified by x, y.
    Switches on the exposure if it is currently off. */
static void
draw_xy(long int x, long int y)
{
	xy(x,y);
	if (!is_exposure)
		exposure_on();
	write_end_block();
}

/** Go from current point to specified point with exposure off. */
static void
move_xy(long int x, long int y)
{
	xy(x,y);
	exposure_off();
	write_end_block();
}

/** Move to a point specified by x,y and flash the given aperture at
    this point. */
static void
flash_xy(long int x, long int y, int aperture_index )
{
	if (is_exposure)
		exposure_off();
	write_end_block();
	write_g_code(tool_prepare);
	write_d_code((enum d_codes)(d_select_aperture + aperture_index));
	write_end_block();
	xy(x,y);
	write_d_code(d_flash);
	write_end_block();
}


/** Abort if the maximum number of apertures is exceeded. */
static void
abort_too_many_apertures(long int ap_index)
{
	if (ap_index < MAX_APERTURE_INDEX)
		return;
	put_msg("Error: Maximum number of possible apertures (%d) exceeded.",
			MAX_APERTURE_INDEX);
	exit(EXIT_FAILURE);
}

/** Define a filled circular aperture given the diameter.

    Returns the corresponding aperture index.
*/
static unsigned long int
ad_aperture_define_circ(double outer_dia)
{
	/* Check to see if the aperture count is zero,
	   if so initialise the array*/
	long int index;
	long int ap_index;

	if (!count_circ_aperture)
		for (index = 0; index < MAX_APERTURE_INDEX; ++index)
			aperture_circ_list[index].dia = -1.0;

	/* Sanity check on aperture size */
	if (!(outer_dia > 0.0)) {
		fprintf(stderr, "Error: Something tried to define "
				"a circular aperture of zero size.\n");
		exit(1);
	}

	/* First check to see if the aperture is defined. */
	ap_index = test_ap_circ(outer_dia);

	/* If the aperture has not been defined, add it. */
	if (ap_index == -1) {
		abort_too_many_apertures(count_apertures);
		ap_index = count_apertures;
		fprintf(tfp, "%%ADD%liC,%f%%*\n",
				d_select_aperture + ap_index, outer_dia );
		aperture_circ_list[ap_index].dia = outer_dia;

		++count_circ_aperture;
		++count_apertures;
	}

	/* Return the index to this aperture. */
	return ap_index;
}

/** Define a filled elliptical aperture given the width and height.

    Returns the corresponding aperture index.
*/
#if 0
static unsigned long int
ad_aperture_define_ellipse(double w, double h)
{
	/* Check to see if the aperture count is zero,
	   if so initialise the array*/
	long int index;
	long int ap_index;

	if (!count_ellipse_aperture)
		for (index = 0; index < MAX_APERTURE_INDEX; ++index) {
			aperture_ellipse_list[index].w = -1.0;
			aperture_ellipse_list[index].h = -1.0;
		}

	/* Sanity check on aperture size */
	if (!(w > 0.0 && h > 0.0)) {
		fprintf(stderr, "Error: Something tried to define an "
				"elliptical aperture of zero size.\n");
		exit(1);
	}

	/* First check to see if the aperture is defined. */
	ap_index = test_ap_ellipse(w,h);

	/* If the aperture has not been defined, add it. */
	if (ap_index == -1) {
		ap_index = count_apertures;
		fprintf(tfp, "%%ADD%liO,%fX%f*%%\n",
				d_select_aperture + ap_index, w, h);
		aperture_ellipse_list[ap_index].w = w;
		aperture_ellipse_list[ap_index].h = h;

		++count_ellipse_aperture;
		++count_apertures;
	}

	/* Return the index to this aperture. */
	return ap_index;
}
#endif

/** Define a filled square aperture given the width.

    Returns the corresponding aperture index.
*/
static unsigned long int
ad_aperture_define_square(double width)
{
	/* Check to see if the aperture count is zero,
	   if so initialise the array*/
	long int index;
	long int ap_index;

	if (!count_square_aperture)
		for (index = 0; index < MAX_APERTURE_INDEX; ++index) {
			aperture_square_list[index].width = -1.0;
		}

	/* Sanity check on aperture size */
	if (!(width > 0.0)) {
		fprintf(stderr, "Error: Something tried to define "
				"a square aperture of zero size.\n");
		exit(1);
	}

	/* First check to see if the aperture is defined. */
	ap_index = test_ap_square(width);

	/* If the aperture has not been defined, add it. */
	if (ap_index == -1) {
		abort_too_many_apertures(count_apertures);
		ap_index = count_apertures;
		fprintf(tfp, "%%ADD%liR,%fX%f*%%\n",
				d_select_aperture + ap_index, width, width);
		aperture_square_list[ap_index].width = width;

		++count_square_aperture;
		++count_apertures;
	}
	return ap_index;
}


/** Given a pointer to a line this determines from the line what
    aperture to use, circular or rectangular.  If necessary it then
    defines it and returns the aperture index. */
static int
define_aperture_for_line(F_line *l)
{
	long int index;
	double width;
	width = width_fig2gbx(l->thickness);

	/*
	   The prevailing aperture style is set from the join style.
	 */
	if (l->join_style == 1)
		index=ad_aperture_define_circ(width);
	else  {
		index=ad_aperture_define_square(width);
		/* If there are more than two points in a line issue a warning.
		 */
		if (l->points && l->points->next && l->points->next->next
				&& l->points->next->next->next)
			warn_once(warn_square_join, "Join style of square does "
				"not translate well to intermediate points "
				"in Gerber format.");
	}
	return index;
}

/** Given a pointer to a line this determines from the line what
    aperture to use, circular or rectangular for the end caps..  If
    necessary it then defines it and returns the aperture index. */
static int
define_aperture_for_line_end(F_line *l)
{
	long int index;
	double width;
	width = width_fig2gbx(l->thickness);

	/*
	   The prevailing aperture style is set from the cap style.
	 */
	if (l->cap_style == 1)
		index = ad_aperture_define_circ(width);
	else  {
		index = ad_aperture_define_square(width);
	}
	return index;
}

static int
define_aperture_for_arc(F_arc *a)
{
	long int index;
	double width;
	width = width_fig2gbx(a->thickness);
	if (a->cap_style  == 1)
		index = ad_aperture_define_circ(width);
	else
		index = ad_aperture_define_square(width);
	return index;
}


//static char   *cctype[] = { "none", "black", "white" };

static F_point *p;

/** Used to generate sequence numbers. */
// static unsigned long int sequence_number=0;

/** Total count of data blocks that have been written. */
// static unsigned long int block_total_count=0;

/** Current count of the number of blocks written on a line.  Used for
    formatting purposes. */
// static unsigned long int block_horizontal_count=0;

/** Maximum number of data blocks to write horizontally. */
// static unsigned long int max_block_horizontal_count=10;

/*
  Process options for producing the Gerber file.
*/
void
gengbx_option(char opt, char *optarg)
{

	switch (opt) {
		/* Ignore language and grid. */
	case 'G':
	case 'L':
		break;

	case 'd':
		if (strcmp(optarg,"mm") == 0 )
			gbx_dimensions = units_mm;
		else if (strcmp(optarg,"in") == 0 )
			gbx_dimensions = units_inches;
		else
			fprintf(stderr,
				"Dimensions should be given in 'mm' for millimeters or 'in' for inches respectively\n");
		break;

	case 'p':
		/* Image polarity. [+,-] */
		if (strcmp(optarg,"pos") == 0 || strcmp(optarg,"+") == 0 )
			gbx_image_polarity = 0;
		else if (strcmp(optarg,"neg") == 0 || strcmp(optarg,"-") == 0)
			gbx_image_polarity = 1;
		else
			fprintf(stderr,
				"Polarity option should be [+,pos] for positive images (marks add material making it opaque) or [-,neg] for negative images (marks remove material, making it transparent)\n");
		break;

	case 'g':
		/* Scaling and offset,
		   form -s <double>x<double>+<double>+<double> */
		if ( sscanf(optarg, "%fx%f+%f+%f", &gbx_scale_factor_a,
				&gbx_scale_factor_b, &gbx_offset_a,
				&gbx_offset_b) == 0)
			fprintf(stderr,
				"Error in scaling format, expect <double>x<double>+<double>+<double> for X and Y scale and x, y offset respectively.\n");
		break;

	case 'f':
		/* Numerical format, ofrm -f <integer>.<integer> */
		if ( sscanf(optarg,"%u.%u", &gbx_before, &gbx_after) == 0 )
			fprintf(stderr,
				"Error in numeric format, expect form  <unsigned int>.<unsigned int> for degree of precision.\n");
		if (gbx_before > 4u)
			fprintf(stderr,
				"Warning: Having more than 4 digits before the decimal place is unusual\n");
		if (gbx_after > 5u)
			fprintf(stderr,
				"Warning: Having more than 5 digits after the decimal place is unusual\n");
		if (gbx_before + gbx_after > 9u)
			fprintf(stderr,
				"Warning: Having more than nine significant figures is usually unrealistic\n");
		break;

	case 'i':
		fputs("Warning: Option -i obsolete, use -v (verbose) instead.\n",
				stderr);
		/* Include debug comments? */
		if ( strcmp(optarg,"off") == 0)
			gbx_debug_comments = 0;
		else if ( strcmp(optarg,"on") == 0)
			gbx_debug_comments = 1;
		else
			fprintf(stderr,
				"Error: Debug comments option should be 'on' or 'off'\n");
		break;

	case 'v':
		gbx_debug_comments = 1;
		break;

	default:
		put_msg(Err_badarg, opt, "gbx");
		exit(1);
	}
}

void
gengbx_start(F_compound *objects)
{
	char    stime[CREATION_TIME_LEN];

	gbx_scale_factor=pow(10,gbx_after);

	write_comment("Gerber RS-274x file");

	sprintf(outbuf, "Creator: %s",prog);   write_comment(outbuf);
	sprintf(outbuf, "Version: %s", PACKAGE_VERSION); write_comment(outbuf);
	sprintf(outbuf, "Driver version: %s", GBX_DRIVER_VERSION);
	write_comment(outbuf);
	write_comment("Author: Edward Grace <edward.grace@gmail.com>");

	if (creation_date(stime)) {
		sprintf(outbuf, "Creation date: %s", stime);
		write_comment(outbuf);
	}

	if (objects->comments) {
		F_comment	*comment = objects->comments;
		while (comment) {
			write_comment(comment->comment);
			comment = comment->next;
		}
	}

	switch (gbx_dimensions) {
	case units_mm:
		fprintf(tfp, "%%MOMM*%%\n");
		break;
	case units_inches:
		fprintf(tfp, "%%MOIN*%%\n");
		break;
	default:
		fprintf(stderr, "Error: Do not know about the unit choice. "
				"%i internal error.\n",
				gbx_dimensions);
		exit(1);
	}

	fprintf(tfp, "%%OFA%fB%f*%%\n", gbx_offset_a, gbx_offset_b);
	fprintf(tfp, "%%FSLAX%u%uY%u%u*%%\n", gbx_before, gbx_after,
			gbx_before,gbx_after);
	fprintf(tfp, "%%SFA%fB%f%%\n", gbx_scale_factor_a, gbx_scale_factor_b);
	if (gbx_image_polarity)
		fprintf(tfp, "%%IPNEG*%%\n");
	else
		fprintf(tfp, "%%IPPOS*%%\n");
	fprintf(tfp, "%%LPD*%%\n");

	write_comment("The following is an aperture definition of width pi/10.  It should never be used.");
	ad_aperture_define_square(0.314159);
}

/** Output end of file marker. */
int
gengbx_end(void) {
	write_m_code(end_of_program);
	return 0;
}

/** Intenal math roughtine.  Determine the change in x and y required
    to move from point 1 to point 2 by a distance l joining the
    lines. */
static void
get_dx_dy(long int x1, long int y1, long int x2, long int y2, long int dist,
		double *dx, double *dy) {
	double l = length(x1, y1, x2, y2);
	*dx = (double)(dist*(x2-x1)/l);
	*dy = (double)(dist*(y2-y1)/l);
}

/** Insert points in a polyline after the given point, returning a
    pointer to the added points. This is used to manage different join
    styles in Gerber.*/
static F_point *
insert_after_point(F_point *p)
{
	F_point	*pnew;
	Point_malloc(pnew);
	pnew->x = p->x;
	pnew->y = p->y;
	pnew->next = p->next;
	p->next = pnew;
	return pnew;
}

void
gengbx_line (F_line *l)
{
	double		dx, dy;
	long int	x1, x2, y1, y2;
	long int	is_same_place;
	long int	n_points, n_points_original;
	F_point		*p_penultimate;
	long int	circsquare;

	/* Always check. If the colour is not black or "default" then bail
	   out with a warning. */
	if (! is_pen_colour_ok(l->pen_color) ) return;

	/* If line thickness is less than or equal to zero, warn and don't
	   output. */
	if ( l->thickness <= 0 && l->fill_style == fill_style_none ) {
		warn_once(warn_line_zero_width,
				"Unfilled line of zero width, ignoring.");
		return;
	}

	/* Used to compare the start and end points of polygons. */
	x1=0; x2=0; y1=0; y2=0;

	/*
	   First check to see if the line has all points at the same place.
	   If they are all at the same place then this "line" should be
	   interpreted as a flashed aperture of the appropriate shape.
	 */
	is_same_place = 1;
	p = l->points; x1=p->x; y1=p->y;
	for (p = p->next; p; p = p->next) {
		is_same_place = p->x == x1 && p->y == y1 ? 1 : 0;
		if (!is_same_place)
			break;
		x1=p->x; y1=p->y;
	}
	if (is_same_place) {
		flash_xy(x1, y1, define_aperture_for_line(l));
		return;
	}

	/* Now determine if its a filled polygon. */
	if (l->fill_style == fill_style_none) {
		write_trace("## START:POLYGON:OPEN");
	} else {
		write_trace("## START:POLYGON:CLOSED");
	}


	/* Now find the penultimate point of the line by traversing the
	   list, also store the total number of points in n_points. */
	n_points = 0;
	n_points_original = 0;
	p_penultimate = l->points;
	for (p = l->points; p->next; p = p->next, ++n_points)
		p_penultimate = p;
	++n_points;
	n_points_original=n_points;

	/** The following evaluates to unity if the line has square ends and
	  circular join style, AND is long enough to actually mean
	  something. */
	circsquare = 0;

	if (l->join_style == 1 && ((l->cap_style == cap_style_butt )
				|| l->cap_style == cap_style_square))  {
		if (n_points > 2)
			circsquare=1;
		else
			l->join_style = 0;
	}

	/* Open polygon. */
	if (l->fill_style == fill_style_none) {
		if (l->type != T_BOX && l->type != T_ARC_BOX
				&& l->type !=  T_POLYGON ) {
			F_point		*p2, *pA, *pB;

			/* For a butt end cap move the first and last points
			   half the thickness of the line forward and backward
			   respectively.

			 *** Preprocess Line ****

			 */
			if (l->cap_style == cap_style_butt && l->points->next) {

				/* Go to start of line. */
				p = l->points;
				x1 = p->x;	y1 = p->y;
				p = p->next;
				x2 = p->x;	y2 = p->y;

				/* Shift the beginning point along by half the
				   line thickness. */
				get_dx_dy(x1, y1, x2, y2, l->thickness/2,
						&dx, &dy);
				p = l->points;
				p->x += round(dx);	p->y += round(dy);

				/* Set p to the penultimate point. */
				p = p_penultimate;
				x1 = p->x;	y1 = p->y;
				p = p->next;
				x2 = p->x;	y2 = p->y;

				/* Shift the end point back by half a line
				   thickness. */

				/* fprintf(stderr,
				   "***** HERE %li, %li, %li ****\n",
				   l->points,l->points->next,p_penultimate); */
				get_dx_dy(x1, y1, x2, y2, l->thickness/2,
						&dx, &dy);
				p->x -= round(dx);	p->y -= round(dy);
			}

			if ( circsquare ) {
				if (n_points_original >= 3) {
					/**Circular join style square end style.

					  Need to move second and third points
					  (if they exist) so that they are out
					  the way */
					p = l->points;
					p2 = p->next;

					pA = insert_after_point(p2); ++n_points;
					pB = insert_after_point(p2); ++n_points;

					/* Will move the second+3rd point back
					   to make way for the circular join. */
					p = l->points;
					p2 = p->next;
					x1 = p->x;	y1 = p->y;
					x2 = p2->x;	y2 = p2->y;
					get_dx_dy(x1, y1, x2, y2,
						l->thickness/2, &dx, &dy);
					p2->x -= round(dx);  p2->y -= round(dy);


					if (n_points_original == 3) {
						/* If there are just three
						   original points we want to
						   move the (now) 4th point
						   forward. */
						p = pA;
						p2 = p->next;
					} else {
						/* Similarly for the new point
						   after the original
						   second point. */
						p = pB->next;
						p2 = p->next;
					}
					x1 = p->x;	y1 = p->y;
					x2 = p2->x;	y2 = p2->y;
					get_dx_dy(x1, y1, x2, y2,
						l->thickness/2, &dx, &dy);
					p->x += round(dx);  p->y += round(dy);
				}

				if ( n_points_original > 3 ) {

					/* Insert a new penultimate point */
					pA = insert_after_point(p_penultimate);
					++n_points;

					/* Move the new penultimate point
					   forward slightly. */
					p = pA;
					p2 = p->next;
					x1 = p->x;	y1 = p->y;
					x2 = p2->x;	y2 = p2->y;
					get_dx_dy(x1, y1, x2, y2,
						l->thickness/2, &dx, &dy);
					p->x += round(dx);  p->y += round(dy);
				}
			}
		}


		/* If we have square ends with round joins we need to swap over
		   to a circular aperture for the main part of the line.

		   Draw the line.

		 */
		if (circsquare) {
			if (n_points_original == 3) {
				/* The line has been modified to have 5 points,
				   the first and last pair are line segments to
				   draw with square cross section.  The 3rd
				   point is an aperture to flash. */
				p = l->points;

				use_aperture(define_aperture_for_line_end(l));

				/* Move to start point */
				move_xy(p->x, p->y);

				/* Draw first segment with end cap style.*/
				p = p->next;
				draw_xy(p->x, p->y);

				/* Now flash the aperture at the corner. */
				p = p->next;
				flash_xy(p->x, p->y,
						define_aperture_for_line(l));

				/* Now draw the final line segment. */
				p = p->next;
				use_aperture(define_aperture_for_line_end(l));
				move_xy(p->x, p->y);

				p=p->next;
				draw_xy(p->x, p->y);
			} else if (n_points_original > 3) {
				/* The line has been modified to add end
				   sections to allow us to draw the end as a
				   square and the joining parts as circular
				   apertures. */


				/* Start to draw the line.
				   First move to the start point. */
				p = l->points;

				/* Set the aperture to the end cap aperture. */
				use_aperture(define_aperture_for_line_end(l));

				/* Move to start point of line */
				move_xy(p->x, p->y);

				/* Draw the first segment with the end cap
				   style. */
				p = p->next;
				draw_xy(p->x, p->y);

				/* Set the aperture to the join style */
				use_aperture(define_aperture_for_line(l));

				/* Move to end of square line */
				move_xy(p->x,p->y);
				p = p->next;
				/* Draw first part of circular line cross
				   section.*/
				draw_xy(p->x, p->y);
				p = p->next;
				draw_xy(p->x, p->y);
				/* This is probably not correct for
				   lines having 4 points. */
				if (p->next) {
					move_xy(p->x, p->y);
					/* Draw the remainder - using
					   the join style. */
					for (; p->next->next; p = p->next)
						draw_xy(p->x, p->y);

					/* Add end section of line. */
					use_aperture(
					       define_aperture_for_line_end(l));
					move_xy(p->x, p->y);
					p = p->next;
					draw_xy(p->x, p->y);
				}
			}
		}  else {
			/* All other lines get drawn like this. */
			p = l->points;
			use_aperture(define_aperture_for_line(l));
			move_xy(p->x, p->y);
			p = p->next;
			for (; p; p = p->next)
				draw_xy(p->x,p->y);
		}
		write_trace("## END:POLYGON:OPEN");
	} else {
		/* Ok.  Hold on to your hats.  If the polygon line thickness is
		   non zero and it's a filled polygon issue a warning, then set
		   the polygon fill style to -1 (no fill) and call this
		   function again.

		   That will result in the other branch of code being called.
		   i.e. A line will be generated with the same coordinates as
		   the polygon outlining this region.

		   Recursive behaviour.  See Recursive behaviour.
		 */
		if (l->thickness > 0.0 ) {
			warn_once(warn_filled_poly_with_line,
				"You have specified a filled polygon with a finite edge thickness.  Check this is what you want");


			l->fill_style = fill_style_none;
			/* Call myself, generating an outline around the polygon
			   of the appropriate line width */
			gengbx_line(l);
		}

		p = l->points;
		x1 = p->x;	y1 = p->y;
		move_xy(p->x, p->y);
		write_g_code(poly_area_fill_on); write_end_block();
		for  (p = l->points, p = p->next; p; p = p->next) {
			draw_xy(p->x, p->y);
			x2 = p->x;	y2 = p->y;
		}
		write_g_code(poly_area_fill_off); write_end_block();

		/* Finish with an explicit exposure off */
		exposure_off();

		/* The line surrounding the polygon is not closed.  Can lead to
		   misrepresentation errors. */
		if (x1 != x2 || y1 != y2 )
			warn_once(warn_open_filled_polygon,
				"A filled polygon is not closed.  This can appear different in the Gerber file.");
		write_trace("## END:POLYGON:FILLED");
	}
	if (l->for_arrow || l->back_arrow )
		warn_once(warn_arrow_not_implemented,
				"Arrows on lines are not yet implemented.");
}

void
gengbx_spline (F_spline *s)
{
	(void)	s;

	warn_once(warn_spline_not_implemented,
			"Splines are not directly implemented.");
}

void
gengbx_arc (F_arc *a)
{
	long int clockwise;

	/* Always check. If the colour is not black or "default" then bail
	   out with a warning. */
	if (! is_pen_colour_ok(a->pen_color) )  return;


	/* If line thickness is less than or equal to zero, warn and don't
	   output. */
	if ( a->thickness <= 0 && a->fill_style == fill_style_none ) {
		warn_once(warn_line_zero_width,
				"Unfilled arc of zero width, ignoring.");
		return;
	}


	if (a->fill_style == fill_style_none) {
		/** We want to draw an unfilled arc. */
		write_trace("## START:ARC:OPEN");
	} else {
		write_trace("## START:ARC:FILLED");
	}


	if (a->fill_style == fill_style_none)
		use_aperture(define_aperture_for_arc(a));


	move_xy(a->point[0].x, a->point[0].y);
	write_g_code(circ_interp_enable);  write_end_block();


	/* If this is to be filled switch on fill */
	if (a->fill_style != fill_style_none) {
		write_g_code(poly_area_fill_on);
		write_end_block();
	}

	/* Need to interpret clockwise and anticlockwise relative to the
	   applied x & y axis scaling */
	clockwise = 1;
	/* We now need to determine if this is clockwise or anticlockwise.*/
	if (a->direction == clockwise )
		write_g_code(circ_interp_clock);
	else
		write_g_code(circ_interp_anti);
	write_end_block();

	fprintf(tfp, "X%iY%iI%iJ%iD01*\n",
			x_fig2gbx(a->point[2].x), y_fig2gbx(a->point[2].y),
			x_fig2gbx(a->center.x-a->point[0].x),
			y_fig2gbx(a->center.y-a->point[0].y));

	if (a->fill_style != fill_style_none) {
		write_g_code(poly_area_fill_off);
		write_end_block();
	}
	write_g_code(circ_interp_disable); write_end_block();
	write_g_code(line_interp_1x); write_end_block();
	exposure_off();

	/* If the line has thickness and is filled switch off fill, and call
	   myself to draw the line arc. */
	if (a->thickness > 0  && a->fill_style != fill_style_none) {
		write_trace("## START:ARC:OUTLINE:CURVE");
		a->fill_style = fill_style_none;
		gengbx_arc(a);

		/* Issue a warning. We are about to add a border. */
		warn_once(warn_open_filled_arc,
			"Polygon fill on an arc with finite line thickness.  "
			"Check this is what you want.");

		/* Draw a line from start to end point. */
		/*use_aperture(define_aperture_for_arc(a));*/
		write_trace("## START:ARC:OUTLINE:LINE");

		move_xy(a->point[0].x,a->point[0].y);
		draw_xy(a->point[2].x,a->point[2].y);
		write_trace("## END:ARC:OUTLINE:LINE");
		write_trace("## END:ARC:OUTLINE:CURVE");
	}


	if (a->fill_style == fill_style_none) {
		/** We want to draw an unfilled arc. */
		write_trace("## END:ARC:OPEN");
	} else {
		write_trace("## END:ARC:FILLED");
	}


}

void
gengbx_ellipse (F_ellipse *e)
{
	if (e->type == T_CIRCLE_BY_RAD || e->type == T_CIRCLE_BY_DIA) {
		F_arc	*a;

		/* Always check. If the colour is not black or "default"
		   then bail out with a warning. */
		if (!is_pen_colour_ok(e->pen_color))
			return;

		write_trace("## START:CIRCLE");
		if (NULL == (Arc_malloc(a))) {
			put_msg(Err_mem);
			exit (2);
		}
		a->pen = e->pen;
		a->fill_style = e->fill_style;
		a->for_arrow = NULL;
		a->back_arrow = NULL;
		a->next = NULL;

		/* FIXIT - Warning the /sqrt(2.0) incurrs potential rounding
		   errors.  Find a better way to write a circle in Gerber. */
		a->point[0].x = e->center.x + e->radiuses.x/sqrt(2.0);
		a->point[0].y = e->center.y + e->radiuses.y/sqrt(2.0);
		a->point[2].x = e->center.x + e->radiuses.x/sqrt(2.0);
		a->point[2].y = e->center.y + e->radiuses.y/sqrt(2.0);
		a->point[1].x = e->center.x - e->radiuses.x/sqrt(2.0);
		a->point[1].x = e->center.y - e->radiuses.y/sqrt(2.0);
		a->center.x = e->center.x;
		a->center.y = e->center.y;
		a->thickness = e->thickness;
		gengbx_arc(a);
	} else
		warn_once(warn_ellipse_unsupported,
				"Ellipse output is currently unsupported.");
	/** To implement the ellipse consider it described parametrically.
	  We want to represent the curve as a set of lines such that the
	  angle between lines is smaller than a predescribed limit.  This
	  requrires knowing the curvature at each point. */
	write_trace("## END:CIRCLE");
}

void
gengbx_text (F_text *t)
{
	(void)	t;

	warn_once(warn_text_unsupported,
			"Text output is currently unsupported.");
	/* Messy!  Done with a LUT for 0-9 A-Z a-z . - _ /

	   Or, can I translate the PS Type 1 fonts in to polylines?

	   Alternatively use some sort of external program like
	   autotrace as an intermediate stage.

	 */
}

/* driver defs */
struct driver dev_gbx = {
	gengbx_option,
	gengbx_start,
	gendev_nogrid,
	gengbx_arc,
	gengbx_ellipse,
	gengbx_line,
	gengbx_spline,
	gengbx_text,
	gengbx_end,
	INCLUDE_TEXT
};
