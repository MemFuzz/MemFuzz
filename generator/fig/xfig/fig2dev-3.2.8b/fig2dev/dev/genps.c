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
 * genps.c: convert fig to PostScript
 *
 * Modified by Herbert Bauer to support ISO-Characters,
 * multiple page output, color mode etc.
 * heb@regent.e-technik.tu-muenchen.de
 *
 * Modified by Eric Picheral to support the whole set of ISO-Latin-1
 * Modified by Herve Soulard to allow non-iso coding on special fonts
 * Herve.Soulard@inria.fr (8 Apr 1993)
 *
 * Development for new extensions at TU Darmstadt, Germany starting 2002
 * Allow to "build" pictures incrementally.
 * To achieve this we split the complete figure into layers in separate
 * ps-figures. The complete figure will be seen when overlapping all layers.
 * A layer is combined from adjacent depths in xfig. This makes it possible
 * to overlap items also when splitting into layers.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "genps.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>	/* struct stat */
#ifdef HAVE_GETPWUID
#include <pwd.h>
#endif
#include <locale.h>

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"	/* NUMSHADES, NUMTINTS */
#include "bound.h"
#include "colors.h"	/* lookup_X_color(), rgb2luminance() */
#include "creationdate.h"
#include "encode.h"
#include "messages.h"
#include "pi.h"
#include "psfonts.h"
#include "readpics.h"
#include "xtmpfile.h"

/* include the PostScript preamble, patterns etc */
#include "psprolog.h"

extern int	v2_flag, v21_flag, v30_flag;		/* read.c */
#ifdef I18N
extern bool	support_i18n;				/* fig2dev.c */
#endif

/* exported symbols */
bool		epsflag = false;	/* to distinguish PS and EPS */
bool		pdfflag = false;	/* to distinguish PDF and PS/EPS */

/*
 * The procedures to embed image files into ps code are defined in a number of
 * source files (readgif.c, readjpg.c, readeps.c,...). These procedures could
 * simply be included here in genps.c, which would result in an overwhelmingly
 * big file. Reading procedures are separated into their respective files, but
 * since they are used only here, the functions are declared here and separate
 * header files are not written.
 */
#define READ_SIGNATURE \
	F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx, int *lly
/* readeps.c */
extern int  read_eps(READ_SIGNATURE);
extern int  read_pdf(READ_SIGNATURE);
extern int  append_epsi(FILE *in, const char *filename, FILE *out);
extern int  pdftops(struct xfig_stream *restrict pic_stream, FILE *out);
/* readgif.c */
extern int  read_gif(READ_SIGNATURE);
/* readjpg.c */
extern int  read_jpg(READ_SIGNATURE);
extern void JPEGtoPS(FILE *f, FILE *PSfile);
/* readpcx.c */
extern int  read_pcx(READ_SIGNATURE);
/* readpng.c */
#ifdef HAVE_PNG_H
extern int  read_png(READ_SIGNATURE);
#endif
/* readppm.c */
extern int  read_ppm(READ_SIGNATURE);
/* readtif.c */
extern int  read_tif(READ_SIGNATURE);
/* readxbm.c */
extern int  read_xbm(READ_SIGNATURE);
/* readxpm.c */
extern int  read_xpm(READ_SIGNATURE);
#undef READ_SIGNATURE

#ifdef I18N
static bool	enable_composite_font = false;
static bool	append_find_composite(FILE *restrict out, FILE *restrict in);
#endif

#define		POINT_PER_INCH		72
#define		ULIMIT_FONT_SIZE	300
/* In order that gridlines have maximum depth */
#define		MAXDEPTH		999
#define		min(a, b)		(((a) < (b)) ? (a) : (b))
#define		SHADEVAL(F)		1.0*(F)/(NUMSHADES-1)
#define		TINTVAL(F)		1.0*(F-NUMSHADES+1)/NUMTINTS
#define		NEEDS_CLIPPING(obj)	((obj->for_arrow || obj->back_arrow) &&\
							obj->thickness > 0)

/* variables obtained from command line options */
static bool	anonymous = true;
static bool	asciipreview = false;	/* add ASCII preview? */
static bool	tiffpreview = false;	/* add a TIFF preview? */
static bool	tiffcolor = false;	/* color or b/w TIFF preview */
static int	border_margin = 0;
static bool	correct_font_size = false;
static int	pagewidth = -1;
static int	pageheight = -1;
static bool	useabsolutecoo = false;
static int	xoff=0;
static int	yoff=0;

static FILE	*saveofile; /* temp filename for eps when adding tiff preview */
static char	tmpeps_buf[128] = "f2depsXXXXXX"; /* temp filename for
						     ASCII or tiff preview */
static char	tmpprev_buf[128] = "f2dprevXXXXXX";
static char	*tmpeps = tmpeps_buf;
static char	*tmpprev = tmpprev_buf;
static int	width, height;
static double	cur_thickness = 0.0;
static int	cur_joinstyle = 0;
static int	cur_capstyle = 0;
static int	pages;
static int	no_obj = 0;
static float	fllx, flly, furx, fury;
static double	scalex, scaley;
static double	origx, origy;
static double	userorigx, userorigy;
static double	userwidthx, userwidthy;

/* arrowhead arrays */
static F_pos	bpoints[50], fpoints[50];
static int	nbpoints, nfpoints;
static F_pos	bfillpoints[50], ffillpoints[50], clippoints[50];
static int	nbfillpoints, nffillpoints, nclippoints;
static int	fpntx1, fpnty1;	/* first point of object */
static int	fpntx2, fpnty2;	/* second point of object */
static int	lpntx1, lpnty1;	/* last point of object */
static int	lpntx2, lpnty2;	/* second-to-last point of object */
/*
 *  Static variables for variant methods:
 *   fig_number has the "current" figure number which has been created.
 *   last_depth remembers the last level number processed
 *	   (we need a sufficiently large initial value)
*/
static int	fig_number = 0;
static int	last_depth = MAXDEPTH + 4;

/* local procedures */
static int	append(const char *restrict infilename, FILE *restrict outfile);
static void	appendhex(char *infilename,FILE *outfile,int width,int height);
static bool	approx_spline_exist(F_compound *ob);
static void	do_split(int actual_depth);/* split different depths' objects */
					   /* but only as comment */
static void	clip_arrows(F_line *obj, int objtype);
static void	draw_arrow(F_arrow *arrow, F_pos *points, int npoints,
				F_pos *fillpoints, int nfillpoints, int col);
static void	draw_gridline(float x1, float y1, float x2, float y2);
static bool	ellipse_exist(F_compound *ob);
static void	encode_all_fonts(F_compound *ob);
static void	fill_area(int fill, int pen_color, int fill_color);
static void	genps_ctl_spline(F_spline *s);
static void	genps_itp_spline(F_spline *s);
static void	genps_std_colors(void);
static void	genps_usr_colors(void);
static bool	iso_text_exist(F_compound *ob);
static void	putword(int word, FILE *file);
static void	set_linewidth(double w);

/* define the standard 32 colors */
struct	_rgb {
	double r, g, b;
} rgbcols[NUM_STD_COLS] = {
	{0.00, 0.00, 0.00},	/* black */
	{0.00, 0.00, 1.00},	/* blue */
	{0.00, 1.00, 0.00},	/* green */
	{0.00, 1.00, 1.00},	/* cyan */
	{1.00, 0.00, 0.00},	/* red */
	{1.00, 0.00, 1.00},	/* magenta */
	{1.00, 1.00, 0.00},	/* yellow */
	{1.00, 1.00, 1.00},	/* white */
	{0.00, 0.00, 0.56},	/* blue1 */
	{0.00, 0.00, 0.69},	/* blue2 */
	{0.00, 0.00, 0.82},	/* blue3 */
	{0.53, 0.81, 1.00},	/* blue4 */
	{0.00, 0.56, 0.00},	/* green1 */
	{0.00, 0.69, 0.00},	/* green2 */
	{0.00, 0.82, 0.00},	/* green3 */
	{0.00, 0.56, 0.56},	/* cyan1 */
	{0.00, 0.69, 0.69},	/* cyan2 */
	{0.00, 0.82, 0.82},	/* cyan3 */
	{0.56, 0.00, 0.00},	/* red1 */
	{0.69, 0.00, 0.00},	/* red2 */
	{0.82, 0.00, 0.00},	/* red3 */
	{0.56, 0.00, 0.56},	/* magenta1 */
	{0.69, 0.00, 0.69},	/* magenta2 */
	{0.82, 0.00, 0.82},	/* magenta3 */
	{0.50, 0.19, 0.00},	/* brown1 */
	{0.63, 0.25, 0.00},	/* brown2 */
	{0.75, 0.38, 0.00},	/* brown3 */
	{1.00, 0.50, 0.50},	/* pink1 */
	{1.00, 0.63, 0.63},	/* pink2 */
	{1.00, 0.75, 0.75},	/* pink3 */
	{1.00, 0.88, 0.88},	/* pink4 */
	{1.00, 0.84, 0.00}	/* gold */
};

static char	*psfontnames[] = {
	"Times-Roman", "Times-Roman",	/* default */
	"Times-Roman",			/* roman */
	"Times-Bold",			/* bold */
	"Times-Italic",			/* italic */
	"Helvetica",			/* sans serif */
	"Courier"			/* typewriter */
};

#define PS_FONTNAMES(T)	\
	(((v2_flag&&!(v21_flag||v30_flag)) || \
		psfont_text(T)) ? PSfontnames : psfontnames)

#define PSFONT(T) \
 ((T->font) <= MAXFONT(T) ? PS_FONTNAMES(T)[T->font+1] : PS_FONTNAMES(T)[0])

#define PSFONTMAG(T)  (((T->size) <= ULIMIT_FONT_SIZE ? \
		T->size :  ULIMIT_FONT_SIZE) \
		* ppi/(correct_font_size? (metric ? 72*80/76.2 : 72): 80))

/* define the fill patterns */
static char	*fill_def[NUMPATTERNS] = {
	FILL_PAT01,FILL_PAT02,FILL_PAT03,FILL_PAT04,
	FILL_PAT05,FILL_PAT06,FILL_PAT07,FILL_PAT08,
	FILL_PAT09,FILL_PAT10,FILL_PAT11,FILL_PAT12,
	FILL_PAT13,FILL_PAT14,FILL_PAT15,FILL_PAT16,
	FILL_PAT17,FILL_PAT18,FILL_PAT19,FILL_PAT20,
	FILL_PAT21,FILL_PAT22,
};

/* headers for various image files */
static	 struct hdr {
	    char	*type;
	    char	*bytes;
	    int		(*readfunc)();
	    bool	pipeok;
	    /* buf[12] below must be large enough for the file signature */
	} headers[] = {	{"GIF", "GIF",			read_gif,	false},
#ifdef V4_0
			{"FIG", "#FIG",			read_figure,	true},
#endif /* V4_0 */
			{"PCX", "\012\005\001",		read_pcx,	true},
			{"EPS", "%!",			read_eps,	true},
			{"EPSI", "\xc5\xd0\xd3\xc6",	read_eps,	true},
			{"PDF", "%PDF",			read_pdf,	true},
			{"PPM", "P3",			read_ppm,	true},
			{"PPM", "P6",			read_ppm,	true},
			{"TIFF", "II*\000",		read_tif,	false},
			{"TIFF", "MM\000*",		read_tif,	false},
			{"XBM", "#define",		read_xbm,	true},
#ifdef HAVE_PNG_H
			{"PNG", "\211\120\116\107\015\012\032\012",
							read_png,	true},
#endif
			{"JPEG", "\377\330\377\340",	read_jpg,	true},
			{"JPEG", "\377\330\377\341",	read_jpg,	true},
			{"XPM", "/* XPM */",		read_xpm,	false},
};

#define NUMHEADERS	(sizeof(headers)/sizeof(headers[0]))


/******************************/
/* various methods start here */
/******************************/

static void
write_data(FILE *out, char *name, unsigned char *in, size_t len)
{
#ifdef HAVE_ZLIB_H
	if (deflate_ascii85encode(out, in, len)) {
		put_msg("Could not compress image %s.", name);
		exit(EXIT_FAILURE);
	}
#else
	if (ascii85encode(out, in, len)) {
		put_msg("Could not embed image %s.", name);
		exit(EXIT_FAILURE);
	}
#endif
	/* Output end of data marker for the ascii85 encoded stream */
	fputs("~>\n", out);
}

/*
 * the image dictionary string is needed twice,
 * here and in indexed_image() below
 */
#ifdef HAVE_ZLIB_H
#define DATASOURCE	"    /DataSource Data /FlateDecode filter\n"
#else
#define DATASOURCE	"    /DataSource Data\n"
#endif

static void
write_rgbimage(FILE *out, F_pic *pic)
{
	fputs(		"/Data currentfile /ASCII85Decode filter def\n"
			"/DeviceRGB setcolorspace\n", out);

	if (pic->num_transp == NO_TRANSPARENCY ||
			/* != TRANSP_COLOR should not happen */
			pic->num_transp != TRANSP_COLOR) {
		fputs(	" << /ImageType 1\n", out);
	} else {			/* transparency by color key masking */
		fputs(	" << /ImageType 4\n", out);
		fprintf(out, "    /MaskColor [ %d %d %d ]\n",
				pic->transp_col[RED], pic->transp_col[GREEN],
				pic->transp_col[BLUE]);
	}
	/* gcc warned: %1$d not ISO C */
	fprintf(out,	"    /Width %d /Height %d\n"
			"    /ImageMatrix [ %d 0 0 -%d 0 %d ]\n",
				pic->bit_size.x, pic->bit_size.y,
			     pic->bit_size.x, pic->bit_size.y, pic->bit_size.y);
	fputs(		DATASOURCE
			"    /BitsPerComponent 8 /Decode [0 1 0 1 0 1]\n"
			" >> xfig_image\n", out);

	write_data(out, pic->file, pic->bitmap,
			(size_t)pic->bit_size.x * pic->bit_size.y * 3);
}

static void
indexed_image(FILE *out, F_pic *pic)
{
	int	i = 0;

	fprintf(out,
			"/Data currentfile /ASCII85Decode filter def\n"
			"[ /Indexed /DeviceRGB %d\n <", pic->numcols - 1);
	/* write the hex-encoded colormap */
	fprintf(out, "%.2hhx%.2hhx%.2hhx", pic->cmap[RED][i],
			pic->cmap[GREEN][i], pic->cmap[BLUE][i]);
	for (i = 1; i < pic->numcols; ++i) {
		if (i % 11 == 0)
			fputs("\n ", out);
		fprintf(out, " %.2hhx%.2hhx%.2hhx", pic->cmap[RED][i],
				pic->cmap[GREEN][i], pic->cmap[BLUE][i]);
	}
	fputs(		">\n] setcolorspace\n", out);
	/* continue with image dictionary */
	if (pic->num_transp == NO_TRANSPARENCY ||
			pic->num_transp == TRANSP_COLOR) { /* colormap only! */
		fputs(	" << /ImageType 1\n", out);
	} else {			/* transparent color */
		fputs(	" << /ImageType 4\n    /MaskColor [ ", out);
		for (i = 0; i < pic->num_transp; ++i)
			fprintf(out, "%d ", pic->transp_cols[i]);
		fputs("]\n", out);
	}
	fprintf(out,	"    /Width %d /Height %d\n"
			"    /ImageMatrix [ %d 0 0 -%d 0 %d ]\n",
				pic->bit_size.x, pic->bit_size.y,
			     pic->bit_size.x, pic->bit_size.y, pic->bit_size.y);
	fputs(		DATASOURCE
			"    /BitsPerComponent 8 /Decode [0 255]\n"
			" >> xfig_image\n", out);

	write_data(out, pic->file, pic->bitmap,
			(size_t)pic->bit_size.x * pic->bit_size.y);
}


/******************************/
/* main procedures start here */
/******************************/

void
geneps_option(char opt, char *optarg)
{
	static bool init = false;
	if (!init) {
		init = true;
		epsflag = true;
	}
	gen_ps_eps_option(opt, optarg);
}

void
genps_option(char opt, char *optarg)
{
	gen_ps_eps_option(opt, optarg);
}

void
gen_ps_eps_option(char opt, char *optarg)
{
	int i;

	switch (opt) {

	/* don't do anything for the following args (already parsed in main) */
	case 'G':		/* grid */
	case 'L':		/* language */
	/* option parsed in genpdf_option(), genpdf.c */
	case 'P':		/* pagemode */
		break;

	case 'a':		/* anonymous (don't output user name) */
	      anonymous = true;
	      break;

	case 'A':		/* add ASCII preview */
		asciipreview = true;
		break;

	case 'b':		/* border margin around figure */
		sscanf(optarg,"%d",&border_margin);
		break;

	case 'B':		/* bounding box in absolute coordinates */
		if (epsflag) {
		    (void) strcpy (boundingbox, optarg);
		    boundingboxspec = true;	/* user-specified */
		    useabsolutecoo = true;
		}
		break;

	case 'C':		/* add color TIFF preview (for MicroSloth) */
		tiffpreview = true;
		tiffcolor = true;
		break;

	case 'c':		/* center figure */
		if (!epsflag) {
		    center = true;
		    centerspec = true;	/* user-specified */
		}
		break;

	case 'e':		/* don't center ('e' means edge) figure */
		if (!epsflag) {
		    center = false;
		    centerspec = true;	/* user-specified */
		}
		break;
	case 'F':		/* fontsize */
		correct_font_size = true;
		break;

	case 'f':		/* default font name */
		for ( i = 1; i <= MAX_PSFONT; i++ )
			if (!strcmp(optarg, PSfontnames[i]))
				break;

		if ( i > MAX_PSFONT )
			fprintf(stderr, "warning: non-standard font name %s\n",
				optarg);

		psfontnames[0] = psfontnames[1] = optarg;
		PSfontnames[0] = PSfontnames[1] = optarg;
		break;

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
		if (!epsflag) {
		    landscape = true;	/* override the figure file setting */
		    orientspec = true;	/* user-specified */
		}
		break;

	case 'M':			/* multi-page option */
		if (!epsflag) {
		    multi_page = true;
		    multispec = true; /* user has overridden anything in file */
		}
		break;

	case 'n':			/* name to put in the "Title:" spec */
		name = optarg;
		break;

	case 'N':			/* convert colors to grayscale */
		grayonly = true;
		break;

	case 'O':			/* overlap multipage output */
		if (!epsflag)
			overlap = true;
		break;

	case 'o':			/* turn off multi-page option */
		if (!epsflag) {
		    multi_page = false;
		    multispec = true; /* user has overridden anything in file */
		}
		break;

	case 'p':			/* portrait mode */
		if (!epsflag) {
		    landscape = false;	/* override the figure file setting */
		    orientspec = true;	/* user-specified */
		}
		break;

	case 'R':		       /* boundingbox in relative coordinates */
		if (epsflag) {
		    (void) strcpy (boundingbox, optarg);
		    boundingboxspec = true;	/* user-specified */
		}
		break;

		case 'T':		/* add monochrome TIFF preview */
		tiffpreview = true;
		tiffcolor = false;
		break;

	case 'x':			/* x offset on page */
		if (!epsflag) {
		    xoff = atoi(optarg);
		}
		break;

	case 'y':			/* y offset on page */
		if (!epsflag) {
		    yoff = atoi(optarg);
		}
		break;

	case 'z':			/* papersize */
		if (!epsflag) {
		    (void) strcpy (papersize, optarg);
		    paperspec = true;	/* user-specified */
		}
		break;

	  default:
		put_msg(Err_badarg, opt, "ps");
		exit(1);
	}
}

void
genps_start(F_compound *objects)
{
	char		 host[256];
	char		 date_buf[CREATION_TIME_LEN];
	struct passwd	*who;
	int		 itmp, jtmp;
	int		 i;
	int		 cliplx, cliply, clipux, clipuy;
	int		 userllx, userlly, userurx, userury;
	const struct paperdef	*pd;
	char		 psize[20];

	char		*libdir;
	char		 filename[512];

	/* make sure user isn't asking for both TIFF and ASCII preview */
	if (tiffpreview && asciipreview) {
		put_msg("Only one type of preview allowed: -A or -T/-C");
		exit(EXIT_FAILURE);
	}

	/* if the user wants a TIFF preview, route the eps file
	   to a temporary one */
	if (tiffpreview) {
		saveofile = tfp;
		/* make name for temp output file */
		if ((tfp = xtmpfile(&tmpeps, sizeof tmpeps_buf)) == NULL) {
			put_msg("Can not create temporary file %s", tmpeps);
			put_msg("No preview will be produced.");
			if (tmpeps != tmpeps_buf)
				free(tmpeps);
			tfp = saveofile;
			tiffpreview = false;
		}
	}

	/* now that the file has been read,
	   turn off multipage mode if eps output */
	if (epsflag)
		multi_page = false;

	scalex = scaley = mag * POINT_PER_INCH / ppi;

	/* this seems to work around Solaris' cc optimizer bug */
	/* the problem was that llx had garbage in it - this "fixes" it */
	sprintf(host,"llx=%d\n",llx);

	/* convert to point unit */
	fllx = llx * scalex;
	flly = lly * scaley;
	furx = urx * scalex;
	fury = ury * scaley;

	/* adjust for any border margin */

	fllx -= border_margin;
	flly -= border_margin;
	furx += border_margin;
	fury += border_margin;

	/* convert ledger (deprecated) to tabloid */
	if (strcasecmp(papersize, "ledger") == 0)
		strcpy(papersize, "tabloid");
	for (pd = paperdef; pd->name != NULL; ++pd) {
		if (strcasecmp(papersize, pd->name) == 0) {
			pagewidth = pd->width;
			pageheight = pd->height;
			strcpy(papersize, pd->name);  /* use the "nice" form */
			break;
		}
	}

	if (pagewidth < 0 || pageheight < 0) {
		put_msg("Unknown paper size `%s'", papersize);
		exit (1);
	}

	if (epsflag) {
	    /* shift figure to 0,0 */
	    origx = -fllx;
	    origy =  fury;
	    if (boundingboxspec) {
		    jtmp = sscanf(boundingbox, "%lf %lf %lf %lf",
				    &userwidthx, &userwidthy,
				    &userorigx, &userorigy);
		    switch (jtmp) {
		    case 0:
			    userwidthx=(furx-fllx)/POINT_PER_INCH;
			    if (metric)
				    userwidthx *= 2.54;
			    /* the comment below silences gcc's
			       -Wimplicit-fallthrough warning */
			    /* intentionally fall through */
			    /* and set the other user... vars */
		    case 1:
			    userwidthy=(fury-flly)/POINT_PER_INCH;
			    if (metric)
				    userwidthy *= 2.54;
			    /* intentionally fall through */
			    /* and set the other user... vars */
		    case 2:
			    userorigx=0;
			    /* intentionally fall through */
			    /* and set the last user... var */
		    case 3:
			    userorigy=0;
		    }
		    if (userwidthx <= 0) {
			    userwidthx=(furx-fllx)/POINT_PER_INCH;
			    if (metric)
				    userwidthx *= 2.54;
		    }
		    if (userwidthy <= 0) {
			    userwidthy=(fury-flly)/POINT_PER_INCH;
			    if (metric)
				    userwidthy *= 2.54;
		    }

		    userorigx  *= POINT_PER_INCH;
		    userorigy  *= POINT_PER_INCH;
		    userwidthx *= POINT_PER_INCH;
		    userwidthy *= POINT_PER_INCH;

		    if (metric) {
			    userorigx  /= 2.54;
			    userorigy  /= 2.54;
			    userwidthx /= 2.54;
			    userwidthy /= 2.54;
		    }

		    userllx = (int) floor(userorigx);
		    userlly = (int) floor(userorigy);
		    userurx = (int) ceil(userorigx+userwidthx);
		    userury = (int) ceil(userorigy+userwidthy);

		    /* adjust for any border margin */
		    userllx -= border_margin;
		    userlly -= border_margin;
		    userurx += border_margin;
		    userury += border_margin;

		    if (useabsolutecoo) {
			    userllx += origx;
			    userurx += origx;
		    }
	    }
	} else {	/* postscript */
		if (landscape) {
			itmp = pageheight;
			pageheight = pagewidth;
			pagewidth = itmp;
		}
		if (center) {
			origx = (pagewidth - furx - fllx)/2.0;
			origy = (pageheight + fury + flly)/2.0;
		} else {
			origx = 0.0;
			origy = pageheight;
		}
	}

	/* finally, adjust by any offset the user wants */
	if (!epsflag) {
		origx += xoff;
		origy += yoff;
	}

	if (epsflag)
		fputs("%!PS-Adobe-3.0 EPSF-3.0\n", tfp);
	else
		fputs("%!PS-Adobe-3.0\n", tfp);

#ifdef HAVE_GETHOSTNAME
	if (gethostname(host, sizeof(host)) == -1)
#endif
		(void) strcpy(host, "unknown host");
	fprintf(tfp, "%%%%Title: %s\n",
		(name? name: ((from) ? from : "stdin")));
	fprintf(tfp, "%%%%Creator: %s Version %s\n",
		prog, PACKAGE_VERSION);
	if (creation_date(date_buf))
		fprintf(tfp, "%%%%CreationDate: %s\n", date_buf);
#ifdef HAVE_GETPWUID
	if (!anonymous) {
		who = getpwuid(getuid());
		if (who)
			fprintf(tfp, "%%%%For: %s@%s (%s)\n",
				who->pw_name, host, who->pw_gecos);
	}
#endif

	/* calc initial clipping area to size of the bounding box
	   (this is needed for later clipping by arrowheads) */
	cliplx = cliply = 0;
	if (epsflag) {
		clipux = (int) ceil(furx-fllx);
		clipuy = (int) ceil(fury-flly);
		pages = 1;
	} else {
		clipux = pagewidth;
		clipuy = pageheight;
		if (multi_page)
			/* account for overlap */
			pages = (int)(1.11111 * (furx - 0.1*pagewidth)
					/ pagewidth + 1) *
				(int)(1.11111 * (fury - 0.1*pageheight)
						/ pageheight + 1);
		else
			pages = 1;
		/*
		 * If the line %%Orientation: Landscape is included, then
		 *  - evince displays the page rotated by -90 degrees,
		 *  - the apple previewer (v8.1) displays it correctly,
		 *  - gs displays the ps-file correctly, but
		 *  - the pdf produced from this ps is rotated by -90 degrees
		 * Therefore, omit the %%Orientation comment. Although, I
		 * believe, evince and the pdf produced by gs do not get the
		 * %%Orientation comment right.
		 * The PostScript Language Document Structuring Conventions
		 * Specification, Version 3.0, says to %%Orientation:
		 * This comment indicates the orientation of the pages in the
		 * document. It can be used by previewing applications and
		 * post-processors to determine how to orient the viewing
		 * window. A portrait orientation indicates that the longest
		 * edge of the paper is parallel to the vertical (y) axis. A
		 * landscape orientation indicates that the longest edge of the
		 * paper is parallel to the horizontal (x) axis. If more than
		 * one orientation applies to the document, an individual page
		 * should specify its orientation by using the
		 * %%PageOrientation: comment.
		if (landscape)
			fputs("%%Orientation: Landscape\n", tfp);
		else
			fputs("%%Orientation: Portrait\n", tfp);
		 */
	}
	if (!epsflag) {
		/* only print Pages if PostScript or PDF */
		fprintf(tfp, "%%%%Pages: %d\n", pages );
	}
	if (!boundingboxspec) {
		fprintf(tfp, "%%%%BoundingBox: %d %d %d %d\n",
				cliplx, cliply, clipux, clipuy);
		/* width for tiff preview */
		width = clipux-cliplx+1;
		height = clipuy-cliply+1;
	} else {
		fprintf(tfp, "%%%%BoundingBox: %d %d %d %d\n",
				userllx, userlly, userurx, userury);
		/* width for tiff preview */
		width = userurx - userllx + 1;
		height = userury - userlly + 1;
	}

	/* only include a pagesize command if PS */
	if (!epsflag) {
		/* add comment for ghostview to recognize the page size */
		/* make sure to use the lowercase paper size name */
		strcpy(psize,papersize);
		for (i = strlen(psize)-1; i >= 0; --i)
			psize[i] = tolower(psize[i]);
		fprintf(tfp, "%%%%DocumentPaperSizes: %s\n", psize);
	}

	/* put in the magnification for information purposes */
	fprintf(tfp, "%%%%Magnification: %.4f\n",metric? mag*76.2/80.0 : mag);
	fputs("%%EndComments\n", tfp);

	/* This %%BeginSetup .. %%EndSetup has to occur after
	 * %%EndComments even though it includes comments, they are
	 * not header comments. The header comment block must be
	 * contiguous, with no non-comment lines in it.
	 */
	if (!epsflag && !pdfflag) {
		fputs("%%BeginSetup\n", tfp);
		fputs("[{\n", tfp);
		fprintf(tfp, "%%%%BeginFeature: *PageSize %s\n", papersize);
		fprintf(tfp, "<</PageSize [%d %d]>> setpagedevice\n",
				pagewidth, pageheight);
		fputs("%%EndFeature\n", tfp);
		fputs("} stopped cleartomark\n", tfp);
		fputs("%%EndSetup\n", tfp);
	} else if (pdfflag) {
		/* set the page size for PDF to the figure size */
		fprintf(tfp, "<< /PageSize [%d %d] >> setpagedevice\n",
			clipux - cliplx, clipuy - cliply);
	}

	/* if the user wants an ASCII preview,
	   route the rest of the eps to a temp file */
	if (asciipreview) {
	    saveofile = tfp;
	    /* make name for temp output file */
	    if ((tfp = xtmpfile(&tmpeps, sizeof tmpeps_buf)) == NULL) {
		fprintf(stderr, "Can not create temporary file %s.\n", tmpeps);
		fputs("No preview will be produced.\n", stderr);
		if (tmpeps != tmpeps_buf)
			free(tmpeps);
		asciipreview = false;
		tfp = saveofile;
	    }
	}

	/* print any whole-figure comments prefixed with "%" */
	if (objects->comments) {
		fputs("%\n", tfp);
		print_comments("% ",objects->comments, "");
		fputs("%\n", tfp);
	}

	/* insert PostScript codes to select paper size, if exist */
	libdir = getenv("FIG2DEV_LIBDIR");
#ifdef I18N_DATADIR
	if (libdir == NULL)
		libdir = I18N_DATADIR;
#endif
	if (libdir != NULL) {
		sprintf(filename, "%s/%s.ps", libdir, papersize);
		/* get filename like "/usr/local/lib/fig2dev/A3.ps" and
		   prepend it to the postscript code;
		   do not mind, if it does not work */
		(void)append(filename, tfp);
	}

	fputs("%%BeginProlog\n", tfp);
	if (pats_used)
		fprintf(tfp,"/MyAppDict 100 dict dup begin def\n");
	fprintf(tfp, "%s", BEGIN_PROLOG1);
	/* define the standard colors */
	genps_std_colors();
	/* define the user colors */
	genps_usr_colors();
	fputs("\nend\n", tfp);

	/* fill the Background now if specified */
	if (bgspec) {
		fprintf(tfp, "%% Fill background color\n");
		fprintf(tfp, "%d %d moveto %d %d lineto ",
				cliplx, cliply, clipux, cliply);
		fprintf(tfp, "%d %d lineto %d %d lineto\n",
				clipux, clipuy, cliplx, clipuy);
		if (grayonly)
			fprintf(tfp, "closepath %.2f setgray fill\n\n",
				rgb2luminance(background.red/65535.0,
						background.green/65535.0,
						background.blue/65535.0));
		else
			fprintf(tfp,
				"closepath %.2f %.2f %.2f setrgbcolor fill\n\n",
				background.red/65535.0,
				background.green/65535.0,
				background.blue/65535.0);
	}

	/* translate (in multi-page mode this is done at end of this proc) */
	/* (rotation and y flipping is done in %%BeginPageSetup area */
	if (pats_used) {
		int i;
		/* only define the patterns that are used */
		for (i=0; i<NUMPATTERNS; i++)
			if (pattern_used[i])
				fprintf(tfp, "\n%s", fill_def[i]);
	}
	fprintf(tfp, "\n%s", BEGIN_PROLOG2);
	if (iso_text_exist(objects)) {
		fprintf(tfp, "%s%s%s",
			SPECIAL_CHAR_1, SPECIAL_CHAR_2, SPECIAL_CHAR_3);
		encode_all_fonts(objects);
	}
	if (ellipse_exist(objects))
		fprintf(tfp, "%s\n", ELLIPSE_PS);
	if (approx_spline_exist(objects))
		fprintf(tfp, "%s\n", SPLINE_PS);
#ifdef I18N
	if (support_i18n && iso_text_exist(objects)) {
		char *libdir, *locale;
		char localefile_buf[128];
		char *localefile = localefile_buf;
		FILE *fp;
		libdir = getenv("FIG2DEV_LIBDIR");
#ifdef I18N_DATADIR
		if (libdir == NULL)
			libdir = I18N_DATADIR;
#endif
		locale = setlocale(LC_CTYPE, NULL);
		if (locale == NULL) {
			fprintf(stderr,
			      "fig2dev: LANG not defined; assuming C locale\n");
			locale = "C";
		}
		if (strlen(libdir) + strlen(locale) + 5 > sizeof localefile_buf)
			localefile = malloc(strlen(libdir) + strlen(locale) + 5);
		if (localefile != NULL) {
			sprintf(localefile, "%s/%s.ps", libdir, locale);
			/* get filename like
			   ``/usr/local/lib/fig2dev/japanese.ps'' */
			fp = fopen(localefile, "rb");
			if (fp == NULL) {
				fprintf(stderr, "fig2dev: can not open file: %s\n",
						localefile);
			} else {
				enable_composite_font =
					append_find_composite(tfp, fp);

				if (ferror(tfp)) {
					fputs("Error writing output file.\n",
							stderr);
					exit(EXIT_FAILURE);
				}
				if (ferror(fp)) {
					fprintf(stderr,
						"Error reading file %s.\n"
						"The output might be broken.\n",
						localefile);
				}
			fclose(fp);
			}
		}
		if (localefile != localefile_buf)
			free(localefile);
	}
#endif /* I18N */

	fprintf(tfp, "%s\n", END_PROLOG);

	fputs("/pageheader {\n", tfp);

	/* must specify translation/rotation
	   before definition of fill patterns */
	fputs("sa\n", tfp);

	/* now make the clipping path for the BoundingBox */
	fprintf(tfp, "n %d %d m %d %d l %d %d l %d %d l cp clip\n",
		cliplx,clipuy, cliplx,cliply, clipux,cliply, clipux,clipuy);
	if (!multi_page) {
		fprintf(tfp, "%.1f %.1f tr\n", origx, origy);
		if (epsflag)
			/* increasing y goes down */
			fprintf(tfp, "1 -1 sc\n");
	}

	fputs("$F2psBegin\n", tfp);

	fputs("10 setmiterlimit\n", tfp);  /* make like X server (11 degrees) */
	/* set initial join style to miter and cap to butt */
	fputs("0 slj 0 slc\n", tfp);
	if( !multi_page)
		fprintf(tfp, " %.5f %.5f sc\n", scalex, scaley );
	fputs("} bind def\n", tfp);


	fputs("/pagefooter {\n", tfp);
	fputs("$F2psEnd\n", tfp);
	fputs("restore\n", tfp);
	fputs("} bind def\n", tfp);


	if (multi_page) {
		/* reset the matrix for multipage mode */
		fputs("initmatrix\n", tfp);
	} else {
		fputs("%%EndProlog\n", tfp);
		if (!epsflag) {
			fputs("%%Page: 1 1\n", tfp);
			fputs("%%BeginPageSetup\n", tfp);
			fputs("pageheader\n", tfp);
			/* increasing y goes down */
			fputs("1 -1 scale\n", tfp);
			fputs("%%EndPageSetup\n", tfp);
		} else {
			fputs("pageheader\n", tfp);
		}
	}

	fputs("%\n", tfp);
	fputs("% Fig objects follow\n", tfp);
	fputs("%\n", tfp);
}

/* Draw a grid on the figure */

void
genps_grid(float major, float minor)
{
	float	lx, ly, ux, uy;
	float	x, y;
	double	thick, thin;
	int	itick, ntick;
	float	m;

	/* see if grid specified */
	if (minor == 0.0 && major == 0.0)
		return;

	/* In case of multi postscript gridlines should be the
	   figure with maximum depth */
	do_split(MAXDEPTH+2);

	m = minor;
	if (minor == 0.0)
		m = major;

	/* start here */
	if (epsflag) {
		/* for eps, only do bounding area of figure */
		lx = floor((fllx / scalex) / m) * m;
		ly = floor((flly / scaley) / m) * m;
		ux = furx / scalex;
		uy = fury / scaley;
	} else {
		/* for pdf and PostScript, grid the whole page */
		lx = 0.0;
		ly = 0.0;
		ux = pagewidth / scalex;
		uy = pageheight / scaley;
	}
	thin = THICK_SCALE;
	thick = THICK_SCALE * 2.5;

	fputs("% Grid\n", tfp);
	fputs("0.5 setgray\n", tfp);
	/* adjust scale for difference in xfig/actual scale in metric mode */
	if (metric)
		fprintf(tfp,"gs 450 472 div dup scale\n");
	/* first the vertical lines */
	fputs("% Vertical\n", tfp);
	for (x = lx; x <= ux; x += m) {
		if (major > 0.0) {
			itick = (int)(x/major)*major;
			/* if on a major tick, or if next minor tick is beyond
			   major tick, make a major tick */
			if (itick == x)
				set_linewidth(thick);
			else {
				/* not exactly on a major tick, see if next
				   minor would be beyond a major */
				ntick = (int)((x+minor)/major)*major;
				if (ntick < x+minor) {
					/* yes, draw the major */
					set_linewidth(thick);
					draw_gridline((float)ntick, ly,
							(float)ntick, uy);
				}
				/* reset to draw the thin grid line */
				set_linewidth(thin);
			}
		} else {
			set_linewidth(thin);
		}
		draw_gridline(x, ly, x, uy);
	}
	/* now the horizontal */
	fputs("% Horizontal\n", tfp);
	for (y = ly; y <= uy; y += m) {
		if (major > 0.0) {
			itick = (int)(y/major)*major;
			/* if on a major tick, or if next minor tick is beyond
			   major tick, make a major tick */
			if (itick == y)
				set_linewidth(thick);
			else {
				/* not exactly on a major tick, see if next
				   minor would be beyond a major */
				ntick = (int)((y+minor)/major)*major;
				if (ntick < y+minor) {
					/* yes, draw the major */
					set_linewidth(thick);
					draw_gridline(lx, (float)ntick, ux,
							(float)ntick);
				}
				/* reset to draw the thin grid line */
				set_linewidth(thin);
			}
		} else {
			set_linewidth(thin);
		}
		draw_gridline(lx, y, ux, y);
	}
	/* restore original scale */
	if (metric)
		fprintf(tfp,"gr\n");
}

static void
draw_gridline(float x1, float y1, float x2, float y2)
{
	fprintf(tfp, "n %.1f %.1f m %.1f %.1f l s\n", x1, y1, x2, y2);
}


int
genps_end(void)
{
	double	dx, dy, mul;
	int		i, page;
	const int	h = pageheight, w = pagewidth;
	int		epslen, tiflen;
	struct stat	fstat;

	/* for multipage, translate and output objects for each page */
	if (multi_page) {
		fputs("%%EndProlog\n", tfp);
		page = 1;
		if (overlap)
			mul = 0.9;
		else
			mul = 1.0;

		for (dy=0; (dy < (fury-h*0.1)) || (page == 1); dy += h*mul) {
			for (dx=0; (dx < (furx-w*0.1)) || (page == 1);
					dx += w*mul) {
				fprintf(tfp, "%%%%Page: %d %d\n", page, page);

				fputs("pageheader\n", tfp);
				/* do page rotation here */
				fputs("%%BeginPageSetup\n", tfp);
				/* increasing y goes down */
				fputs(" 1 -1 sc\n", tfp);
				fputs("%%EndPageSetup\n", tfp);

				fputs("gs\n", tfp);
				fprintf(tfp, "%.1f %.1f tr\n", -dx,-(dy+h*mul));
				fprintf(tfp, " %.3f %.3f sc\n", scalex, scaley);
				for (i=0; i<no_obj; ++i) {
					fprintf(tfp, "o%d ", i);
					if (!(i%20))
						fputc('\n', tfp);
				}
				fputs("gr\n", tfp);
				fputs("pagefooter\n", tfp);
				fputs("showpage\n", tfp);
				++page;
			}
		}
	}
	/* Close the (last) figure */
	do_split(-10);

	/* add showpage if requested */
	if (!multi_page) {
		fputs("pagefooter\n", tfp);
		fputs("showpage\n", tfp);
	}

	/* does the user want an ASCII or TIFF preview? */
	if (tiffpreview || asciipreview) {
		/* close temp eps file */
		fclose(tfp);
		/* revert original file back to tfp */
		tfp = saveofile;

		/* make name for temp output file */
		if ((saveofile = xtmpfile(&tmpprev, sizeof tmpprev_buf)) ==
				NULL) {
			put_msg("Can not create temporary file %s.", tmpprev);
			put_msg("No preview will be produced.");
			if (tmpprev != tmpprev_buf)
				free(tmpprev);
			/* Output the eps stored in tmpeps */
			if (append(tmpeps, tfp) == -1) {
				put_msg("Cannot open temp file %s.", tmpeps);
				remove(tmpeps);
				/* unnecessary:
				   if (tmpeps != tmpeps_buf) free(tmpeps); */
				exit(EXIT_FAILURE);
			}
			remove(tmpeps);
			if (tmpeps != tmpeps_buf)
				free(tmpeps);
			asciipreview = tiffpreview = false;
		} else {
#ifdef GSEXE
			/* make the ghostscript command to generate the ASCII
			   or TIFF file from the temp eps file */
			sprintf(gscom, "%s -q -dSAFER -sDEVICE=%s -r72 -g%dx%d "
					"-o \'%s\' %s",
					GSEXE, asciipreview ? "bit" :
					(tiffcolor ? "tiff24nc" : "tifflzw"),
					width, height, tmpprev, tmpeps);
			if (system(gscom) != 0) {
				fprintf(stderr,
					     "Error calling ghostscript: %s\n",
					     gscom);
#else
				fputs("Ghostscript not available. ", stderr);
#endif
				fprintf(stderr,"No preview will be produced\n");
				remove(tmpprev);
				if (tmpprev != tmpprev_buf)
					free(tmpprev);
				/* append the eps */
				if (append(tmpeps, tfp) == -1) {
					put_msg("Cannot open temp file %s.",
							tmpeps);
					remove(tmpeps);
					exit(EXIT_FAILURE);
				}
				remove(tmpeps);
				if (tmpeps != tmpeps_buf)
					free(tmpeps);
				/* and cancel the preview */
				asciipreview = tiffpreview = false;
#ifdef GSEXE
			}
#endif
			fclose(saveofile);
		}
		if (asciipreview) {
			--width;
			--height;
			/* now attach the preview after the prolog
			   then attach the rest of the eps */
			fprintf(tfp, "%%%%BeginPreview: %d %d %d %d\n",
					width, height, 1, height);
			appendhex(tmpprev, tfp, width, height);
			remove(tmpprev);
			fputs("%%EndPreview\n", tfp);
			if (append(tmpeps, tfp) == -1) {
				put_msg("Cannot open temp file %s.", tmpeps);
				remove(tmpeps);
				exit(EXIT_FAILURE);
			}
			remove(tmpeps);

		} else if (tiffpreview) {
			/*  now make the binary header in the final output file
			    and append the eps and tiff files */

			stat(tmpeps, &fstat);
			epslen = fstat.st_size;	/* size of eps file */

			stat(tmpprev, &fstat);
			tiflen = fstat.st_size;	/* size of tif file */

			/* write header ident C5D0D3C6 */
			putc(0xC5, tfp);
			putc(0xD0, tfp);
			putc(0xD3, tfp);
			putc(0xC6, tfp);
			/* put byte offset of the EPS part
			   (always 30 - immediately after the header) */
			putword(30, tfp);
			/* now size of eps part */
			putword(epslen, tfp);
			/* no Metafile */
			putword(0, tfp);
			putword(0, tfp);
			/* byte offset of TIFF part */
			putword(epslen+30, tfp);
			/* and length of TIFF part */
			putword(tiflen, tfp);
			/* finally, FFFF (no checksum) */
			putc(0xFF, tfp);
			putc(0xFF, tfp);
			/* now copy eps out */
			if (append(tmpeps, tfp) == -1) {
				put_msg("Cannot open temp file %s.", tmpeps);
				remove(tmpprev);
				remove(tmpeps);
				exit(EXIT_FAILURE);
			}
			remove(tmpeps);
			/* and finally, the tiff file */
			if (append(tmpprev, tfp) == -1) {
				put_msg("Cannot open temp file %s.", tmpprev);
				remove(tmpprev);
				remove(tmpeps);
				exit(EXIT_FAILURE);
			}
			remove(tmpprev);
			putc('\n', tfp);

		}
		if (tmpeps != tmpeps_buf)
			free(tmpeps);
		if (tmpprev != tmpprev_buf)
			free(tmpprev);
	}
	/* put any cleanup between %%Trailer and %EOF */
	fputs("%%Trailer\n", tfp);
	if (pats_used)
		fputs("end\n", tfp);		/* close off MyAppDict */
	/* final DSC comment for eps output (EOF = end of document) */
	fputs("%EOF\n", tfp);

	/* all ok */
	return 0;
}

/* write a 32-bit value LSB first to file */

static void
putword(int word, FILE *file)
{
	register int i;

	for (i=0; i<4; i++) {
		putc((unsigned char) word & 0xff, file);
		word >>= 8;
	}
}

/*
 * append file named in "infilename" to already open FILE "outfile"
 * Return 0 on sucess, -1 if "infilename" cannot be opened.
 */

static int
append(const char *restrict infilename, FILE *outfile)
{
	FILE	*infile;
	char	buf[BUFSIZ];
	size_t	buf_len = sizeof buf;
	size_t	chars;

	if ((infile = fopen(infilename, "rb")) == 0)
		return -1;

	while ((chars = fread(buf, (size_t)1, buf_len, infile)) == buf_len &&
			buf_len == fwrite(buf, (size_t)1, buf_len, outfile))
		;
	if (!ferror(outfile) && chars > 0)
		fwrite(buf, (size_t)1, chars, outfile);

	fclose(infile);
	return 0;
}

#ifdef I18N
/*
 * Append open file in to open file out while searching for the string
 * "CompositeRoman".  Return true if found, false otherwise.
 */
static bool
append_find_composite(FILE *restrict out, FILE *restrict in)
{
	/*
	 * Initially, the needle was passed as a function parameter. However,
	 * Visual Studio cannot create an array of a size depending on a
	 * function parameter (str[], below). Therefore, use the fixed needle
	 * "CompositeRoman". Moreover, Visual Studio does not accept a const
	 * qualified parameter as array size, but "sizeof ...".
	 */
	bool		found = false;
	const char	needle[] = "CompositeRoman";
	char		str[BUFSIZ + sizeof needle];
	const size_t	needle_len = sizeof needle - 1;
	const size_t	str_len = (size_t)BUFSIZ;
	size_t		chars;

	/* The needle could be split up between two consecutive buffers.
	   Keep some margin and initialize it with spaces. */
	for (chars = 0; chars < needle_len; ++chars)
		str[chars] = ' ';
	/* 0-terminate str, otherwise strstr() scans into unknown territory. */
	str[BUFSIZ + needle_len] = '\0';

	while ((chars = fread(str + needle_len, (size_t)1, str_len, in)) ==
			str_len) {
		if (!found && strstr(str, needle))
			found = true;
		memcpy(str, str + str_len, needle_len);
		if (fwrite(str + needle_len, (size_t)1, str_len, out) !=
				str_len)
			break;
	}
	/* Copy the last, incomplete read. */
	if (!ferror(out) && chars > 0) {
		if (!found) {
			str[needle_len + chars] = '\0';
			if (strstr(str, needle))
				found = true;
		}
		fwrite(str + needle_len, (size_t)1, chars, out);
	}
	return found;
}
#endif /* I18N */


/* read file named in "infilename", converting the binary to hex and
   append to already open FILE "outfile".
   width is the number of hex values per line that should be written
   and height is the number of lines total. */

static void
appendhex(char *infilename, FILE *outfile, int width, int height)
{
	FILE		*infile;
	unsigned char	byte;
	int		len, i, j;

	if ((infile = fopen(infilename, "r")) == 0) {
		fprintf(stderr, "Can't open temp file %s\n", infilename);
		exit(1);
	}
	len = (width+7)/8;
	for (j=0; j<height; ++j) {
		fputs("% ", outfile);
		for (i=0; i<len; ++i) {
			if (fread(&byte, 1, 1, infile) == 0)
				break;
			fprintf(outfile, "%02X", byte);
		}
		fputc('\n', outfile);
	}
	fclose(infile);
}


static void
set_style(int s, double v)
{
	v /= 80.0 / ppi;
	if (s == DASH_LINE) {
		if (v > 0.0) fprintf(tfp, " [%d] 0 sd\n", round(v));
	} else if (s == DOTTED_LINE) {
		if (v > 0.0) fprintf(tfp, " [%d %d] %d sd\n",
				round(ppi/80.0), round(v), round(v));
	} else if (s == DASH_DOT_LINE) {
		if (v > 0.0) fprintf(tfp, " [%d %d %d %d] 0 sd\n",
				round(v), round(v*0.5),
				round(ppi/80.0), round(v*0.5));
	} else if (s == DASH_2_DOTS_LINE) {
		if (v > 0.0) fprintf(tfp, " [%d %d %d %d %d %d] 0 sd\n",
				round(v), round(v*0.45),
				round(ppi/80.0), round(v*0.333),
				round(ppi/80.0), round(v*0.45));
	} else if (s == DASH_3_DOTS_LINE) {
		if (v > 0.0) fprintf(tfp,
				" [%d %d %d %d %d %d %d %d ] 0 sd\n",
				round(v), round(v*0.4),
				round(ppi/80.0), round(v*0.3),
				round(ppi/80.0), round(v*0.3),
				round(ppi/80.0), round(v*0.4));
	}
}

static void
reset_style(int s, double v)
{
	if (v > 0.0 && s >= DASH_LINE && s <= DASH_3_DOTS_LINE)
		fputs(" [] 0 sd\n", tfp);
}

static void
set_linejoin(int j)
{
	if (j != cur_joinstyle) {
		cur_joinstyle = j;
		fprintf(tfp, "%d slj\n", cur_joinstyle);
	}
}

static void
set_linecap(int j)
{
	if (j != cur_capstyle) {
		cur_capstyle = j;
		fprintf(tfp, "%d slc\n", cur_capstyle);
	}
}

static void
set_linewidth(double w)
{
	if (w != cur_thickness) {
		cur_thickness = w;
		fprintf(tfp, "%.3f slw\n",     /* make lines a little thinner */
				cur_thickness <= THICK_SCALE ?
				0.5* cur_thickness :
				cur_thickness - THICK_SCALE);
	}
}

void
genps_line(F_line *l)
{
	F_point		*p, *q;
	int		 radius;
	int		 i;
	int		 xmin,xmax,ymin,ymax;
	int		 pic_w, pic_h, img_w, img_h;
	float		 hf_wid;

	do_split(l->depth);

	if (multi_page)
	   fprintf(tfp, "/o%d {", no_obj++);

	/* print any comments prefixed with "%" */
	print_comments("% ",l->comments, "");

	fputs("% Polyline\n", tfp);
	if (l->type != T_PIC_BOX) {  /* pic object has no line thickness */
		set_linejoin(l->join_style);
		set_linecap(l->cap_style);
		set_linewidth((double)l->thickness);
	}
	p = l->points;
	q = p->next;
	if (q == NULL) { /* A single point line */
		if (l->cap_style > 0)
			hf_wid = 1.0;
		else if (l->thickness <= THICK_SCALE)
			hf_wid = l->thickness/4.0;
		else
			hf_wid = (l->thickness-THICK_SCALE)/2.0;
		fprintf(tfp, "n %d %d m %d %d l gs col%d s gr\n",
				round(p->x-hf_wid), p->y, round(p->x+hf_wid),
				p->y, l->pen_color);
		if (multi_page)
			fputs("} bind def\n", tfp);
		return;
	}
	if (l->type != T_PIC_BOX) {
		set_style(l->style, l->style_val);
	}

	xmin = xmax = p->x;
	ymin = ymax = p->y;
	while (p->next != NULL) { /* find lower left and upper right corners */
		p=p->next;
		if (xmin > p->x)
			xmin = p->x;
		else if (xmax < p->x)
			xmax = p->x;
		if (ymin > p->y)
			ymin = p->y;
		else if (ymax < p->y)
			ymax = p->y;
	}

	if (l->type == T_ARC_BOX) {
		/* ARC BOX */
		radius = l->radius;		/* radius of the corner */
		/* limit the radius to the smaller of the two sides or
		   postscript crashes; from T.Sato */
		if ((xmax - xmin) / 2 < radius)
			radius = (xmax - xmin) / 2;
		if ((ymax - ymin) / 2 < radius)
			radius = (ymax - ymin) / 2;
		fprintf(tfp, "n %d %d m",xmin+radius, ymin);
		fprintf(tfp, " %d %d %d %d %d arcto 4 {pop} repeat\n",
				xmin, ymin, xmin, ymax-radius, radius);
		/* arc through bl to br */
		fprintf(tfp, "  %d %d %d %d %d arcto 4 {pop} repeat\n",
				xmin, ymax, xmax-radius, ymax, radius);
		/* arc through br to tr */
		fprintf(tfp, "  %d %d %d %d %d arcto 4 {pop} repeat\n",
				xmax, ymax, xmax, ymin+radius, radius);
		/* arc through tr to tl */
		fprintf(tfp, "  %d %d %d %d %d arcto 4 {pop} repeat\n",
				xmax, ymin, xmin+radius, ymin, radius);
	} else if (l->type == T_PIC_BOX) {  /* imported picture */
	  /* PICTURE OBJECT */
		int		dx, dy, rotation;
		int		pllx, plly, purx, pury;
		int		i, j;
		char		buf[12];
		FILE		*picf;
		struct xfig_stream	pic_stream;

		dx = l->points->next->next->x - l->points->x;
		dy = l->points->next->next->y - l->points->y;
		rotation = 0;
		if (dx < 0 && dy < 0)
			   rotation = 180;
		else if (dx < 0 && dy >= 0)
			   rotation = 90;
		else if (dy < 0 && dx >= 0)
			   rotation = 270;

		fputs("%\n", tfp);

		fputs("% pen to black in case this eps object doesn't set "
			"color first\n", tfp);
		if (grayonly)
		    fputs("0 setgray\n", tfp);
		else
		    fputs("0 0 0 setrgbcolor\n", tfp);

		init_stream(&pic_stream);

		/* open the file and read a few bytes of the header
		   to see what it is */
		if ((picf = open_stream(l->pic->file, &pic_stream)) == NULL) {
			put_msg("No such picture file: %s", l->pic->file);
			free_stream(&pic_stream);
			return;
		}

		for (i = 0; i < (int)(sizeof buf); ++i) {
			int	c;
			if ((c = getc(picf)) == EOF)
				break;
			buf[i] = (char)c;
		}

		/* now find which header it is */
		for (i = 0; i < (int)(sizeof(headers)/sizeof(headers[0])); ++i)
			if (!memcmp(buf, headers[i].bytes,
						strlen(headers[i].bytes)))
				break;

		if (i == sizeof(headers) / sizeof(headers[0])) {
			/* not found */
			put_msg("%s: Unknown image format", l->pic->file);
			close_stream(&pic_stream);
			free_stream(&pic_stream);
			return;
		}
		/* found */
		/*
		 * readfunc() expects an open file stream, positioned not at the
		 * start of the stream. The stream remains open after returning.
		 */
		if (!headers[i].readfunc(l->pic, &pic_stream, &pllx, &plly)) {
			put_msg("%s: Bad %s format", l->pic->file,
					headers[i].type);
			close_stream(&pic_stream);
			free_stream(&pic_stream);
			return;
		}

		/* width, height of image bits (unrotated) */
		img_w = l->pic->bit_size.x;
		img_h = l->pic->bit_size.y;

		/* calc upper-right from size and lower-left */
		/* pllx, plly may not be (0,0) from some image formats */

		purx = img_w+pllx;
		pury = img_h+plly;

		fputs("n gs\n", tfp);

		/* pic_w, pic_h are the width, height of the Fig pic object,
		   possibly rotated */
		if (((rotation == 90 || rotation == 270) && !l->pic->flipped) ||
		    (rotation != 90 && rotation != 270 && l->pic->flipped)) {
			pic_w = pury - plly;
			pic_h = purx - pllx;
		} else {
			pic_w = purx - pllx;
			pic_h = pury - plly;
		}

		/* translate the pic stuff to the right spot on the page */
		fprintf(tfp, "%d %d tr\n", xmin, ymin);

		/* scale the pic stuff to fit into the bounding box */
		/* Note: the origin for fig is in the upper-right corner;
		 *	 for postscript its in the lower right hand corner.
		 *	 To fix it, we use a "negative"-y scale factor, then
		 *	 translate the image up on the page
		 */
		fprintf(tfp, "%f %f sc\n", fabs((double)(xmax-xmin)/pic_w),
					-1.0*(double)(ymax-ymin)/pic_h);

		/* flip the pic stuff.  Always translate it back so that the
		 * lower-left corner is at the origin.
		 * note: fig measures rotation clockwise;
		 * postscript is counter-clockwise
		 */
		switch (rotation) {
		case 0:
			if (l->pic->flipped) {
				fprintf(tfp, "%d 0 tr\n", pic_w);
				fprintf(tfp, "%d rot\n", 270);
				fputs("1 -1 sc\n", tfp);
			} else {
				fprintf(tfp, "0 %d tr\n", -pic_h);
			}
			break;
		case 90:
			if (l->pic->flipped) {
				fprintf(tfp, "%d %d tr\n", pic_w, -pic_h);
				fputs("-1 1 sc\n", tfp);
			} else {
				fprintf(tfp, "%d rot\n", 270);
			}
			break;
		case 180:
			if (l->pic->flipped) {
				fprintf(tfp, "0 %d tr\n", -pic_h);
				fprintf(tfp, "%d rot\n", 270);
				fputs("-1 1 sc\n", tfp);
			} else {
				fprintf(tfp, "%d 0 tr\n", pic_w);
				fprintf(tfp, "%d rot\n", 180);
			}
			break;
		case 270:
			if (l->pic->flipped) {
				fputs("1 -1 sc\n", tfp);
			} else {
				fprintf(tfp, "%d %d tr\n", pic_w, -pic_h);
				fprintf(tfp, "%d rot\n", 90);
			}
			break;
		}

		/* translate the pic stuff so that the lower-left corner is at
		   the origin */
		fprintf(tfp, "%d %d tr\n", -pllx, -plly);
		/* save vm so pic file won't change anything */
		fputs("sa\n", tfp);

		/* if PIC object is EPS file, set up clipping rectangle to BB
		 * and prepare to clean up stacks and dicts of included EPS file
		 */
		if (l->pic->subtype == P_EPS) {
			fprintf(tfp,
				"n %d %d m %d %d l %d %d l %d %d l cp clip n\n",
				pllx,plly, purx,plly, purx,pury, pllx,pury);
			fputs("countdictstack\n", tfp);
			fputs("mark\n", tfp);
			/* if user wants grayscale (-N) then redefine
			   setrgbcolor to setgray in imported figure */
			if (grayonly)
				fputs("/setrgbcolor { 0.11 mul exch 0.59 mul "
					  "add exch 0.3 mul add setgray} def\n",
					tfp);

			/* undefine showpage - and setpagedevice. Some ps-files,
			 * e.g., produced by latex, may be included this way
			 */
			fputs("/showpage {} def\n/setpagedevice {pop} def\n",
					tfp);
		}


		/* embed the image */
		if (l->pic->subtype == P_XBM) {
			unsigned char	*bit;
			int		 cwid;

			fprintf(tfp, "col%d\n ", l->pen_color);
			fputs("% Bitmap image follows:\n", tfp);
			/* scale for size in bits */
			fprintf(tfp, "%d %d sc\n", purx, pury);
			fprintf(tfp, "/pix %d string def\n", (int)((purx+7)/8));
			/* width, height and paint 0 bits */
			fprintf(tfp, "%d %d false\n", purx, pury);
			/* transformation matrix */
			fprintf(tfp, "[%d 0 0 %d 0 %d]\n", purx, -pury, pury);
			/* function for reading bits */
			fputs("{currentfile pix readhexstring pop}\n", tfp);
			/* use imagemask to draw in color */
			fputs("imagemask\n", tfp);
			bit = l->pic->bitmap;
			cwid = 0;
			for (i=0; i<pury; ++i) {	/* for each row */
				/* for each byte */
				for (j=0; j<(int)((purx+7)/8); ++j) {
					fprintf(tfp,"%02x",
						     (unsigned char) ~(*bit++));
					cwid+=2;
					if (cwid >= 80) {
						fputs("\n", tfp);
						cwid=0;
					}
				}
				fputs("\n", tfp);
			}

		} else if (l->pic->subtype == P_GIF || l->pic->subtype == P_PNG
				|| l->pic->subtype == P_JPEG
				|| l->pic->subtype == P_PCX
				|| l->pic->subtype == P_PPM
				|| l->pic->subtype == P_XPM) {
			if (l->pic->subtype == P_GIF)
				fputs("% GIF", tfp);
			else if (l->pic->subtype == P_PNG)
				fputs("% PNG", tfp);
			else if (l->pic->subtype == P_JPEG)
				fputs("% JPEG", tfp);
			else if (l->pic->subtype == P_PCX)
				fputs("% PCX", tfp);
			else if (l->pic->subtype == P_XPM)
				fputs("% XPM", tfp);
			else
				fputs("% PPM", tfp);

			fputs(" image follows:\n", tfp);
			/* scale for size in bits */
			fprintf(tfp, "%d %d sc\n", purx, pury);
			if (l->pic->subtype == P_JPEG) {
				/* read and format the jpeg file for PS */
				rewind_stream(&pic_stream);
				JPEGtoPS(pic_stream.fp, tfp);
			} else {
				if (l->pic->numcols > 256)
					write_rgbimage(tfp, l->pic);
				else
					indexed_image(tfp, l->pic);
			}

		/* EPS file */
		} else if (l->pic->subtype == P_EPS &&
				strcmp(headers[i].type, "PDF")) {
		    fputs("% EPS file follows:\n", tfp);
		    if (!rewind_stream(&pic_stream)) {
			    err_msg("Unable to open EPS file '%s'");
			    fputs("gr\n", tfp);
			    return;
		    }

		    /* flush buffer first */
		    fflush(tfp);
		    if (strcmp(headers[i].type, "EPSI") == 0) {
			    /* currently, if append_epsi() returns with
			       an error, it did not write anything */
			    if (append_epsi(pic_stream.fp, l->pic->file, tfp))
				    put_msg("Could not embed EPSI file %s.",
						    l->pic->file);
		    } else {
			    size_t	len;
			    char	buffer[BUFSIZ];

			    while ((len = fread(buffer, 1, sizeof buffer,
							    pic_stream.fp)))
				    fwrite(buffer, 1, len, tfp);
		    }
		} else if (!strcmp(headers[i].type, "PDF")) {
			fputs("% PDF file converted to EPS follows:\n", tfp);
			fflush(tfp);
			pdftops(&pic_stream, tfp);
		}

		close_stream(&pic_stream);
		free_stream(&pic_stream);

		/* if PIC object is EPS file, clean up stacks and dicts
		 * before 'restore'ing vm
		 */
		if (l->pic->subtype == P_EPS) {
			fputs("\ncleartomark\n", tfp);
			fputs("countdictstack exch sub { end } repeat\n", tfp);
		}

		/* restore vm and gsave */
		fputs("rs gr\n", tfp);
		fputs("%\n", tfp);
		fprintf(tfp, "%% End Imported PIC File: %s\n", l->pic->file);
		if (l->pic->subtype == P_EPS)
			fputs("%%EndDocument\n", tfp);
		fputs("%\n", tfp);
	} else {
		/* POLYLINE */
		p = l->points;
		q = p->next;
		/* first point */
		fpntx1 = p->x;
		fpnty1 = p->y;
		/* second point */
		fpntx2 = q->x;
		fpnty2 = q->y;
		/* go through the points to get the last two */
		while (q->next != NULL) {
			p = q;
			q = q->next;
		}
		/* next to last point */
		lpntx2 = p->x;
		lpnty2 = p->y;
		/* last point */
		lpntx1 = q->x;
		lpnty1 = q->y;
		/* set clipping for any arrowheads */
		if (NEEDS_CLIPPING(l)) {
			fprintf(tfp, "gs ");
			clip_arrows(l, OBJ_POLYLINE);
		}

		/* now output the points */
		p = l->points;
		q = p->next;
		fprintf(tfp, "n %d %d m", p->x, p->y);
		i=1;
		while (q->next != NULL) {
			p = q;
			q = q->next;
			fprintf(tfp, " %d %d l", p->x, p->y);
			if (i%5 == 0)
				fputs("\n", tfp);
			++i;
		}
		fputs("\n", tfp);
	}

	/* now fill it, draw the line and/or draw arrow heads */
	if (l->type != T_PIC_BOX) {  /* make sure it isn't a picture object */
		if (l->type == T_POLYLINE) {
			fprintf(tfp, " %d %d l ", q->x, q->y);
			if (fpntx1==lpntx1 && fpnty1==lpnty1)
				fputs(" cp ", tfp);
			/* endpoints are coincident, close path
			   so that line join is used */
		} else {
			fputs(" cp ", tfp);	/* polygon, close path */
		}
		/* fill it if there is a fill style */
		if (l->fill_style != UNFILLED)
			fill_area(l->fill_style, l->pen_color, l->fill_color);
		/* stroke if there is a line thickness */
		if (l->thickness > 0)
		     fprintf(tfp, "gs col%d s gr ", l->pen_color);

		/* reset clipping */
		if (l->type == T_POLYLINE && NEEDS_CLIPPING(l))
			fputs("gr\n", tfp);
		reset_style(l->style, l->style_val);

		if (l->back_arrow && l->thickness > 0)
			draw_arrow(l->back_arrow, bpoints, nbpoints,
					bfillpoints, nbfillpoints,l->pen_color);
		if (l->for_arrow && l->thickness > 0)
			draw_arrow(l->for_arrow, fpoints, nfpoints, ffillpoints,
					nffillpoints, l->pen_color);
	}
	if (multi_page)
		fputs("} bind def\n", tfp);
}

void
genps_spline(F_spline *s)
{
	do_split(s->depth);

	if (multi_page)
		fprintf(tfp, "/o%d {", no_obj++);

	/* print any comments prefixed with "%" */
	print_comments("% ",s->comments, "");

	if (closed_spline(s)) {
		if (s->style == DOTTED_LINE)
			set_linecap(1);		/* round dots for dotted line */
	} else {		/* open splines can explicitely set capstyle */
		set_linecap(s->cap_style);
	}
	/* set the line thickness */
	set_linewidth((double)s->thickness);
	if (int_spline(s))
		genps_itp_spline(s);
	else
		genps_ctl_spline(s);
	if (multi_page)
		fputs("} bind def\n", tfp);
}

static void
genps_itp_spline(F_spline *s)
{
	F_point		*p, *q;
	F_control	*a, *b;
	int		 xmin, ymin;

	fprintf(tfp, "%% Interp Spline\n");

	a = s->controls;
	p = s->points;
	/* first point */
	fpntx1 = p->x;
	fpnty1 = p->y;
	/* second point */
	fpntx2 = round(a->rx);
	fpnty2 = round(a->ry);
	/* go through the points to find the last two */
	for (q = p->next; q != NULL; p = q, q = q->next) {
		b = a->next;
		a = b;
	}
	/* next to last point */
	lpntx2 = round(b->lx);
	lpnty2 = round(b->ly);
	/* last point */
	lpntx1 = p->x;
	lpnty1 = p->y;
	/* set clipping for any arrowheads */
	if (NEEDS_CLIPPING(s)) {
		fprintf(tfp, "gs ");
		clip_arrows((F_line *)s, OBJ_SPLINE);
	}

	a = s->controls;
	p = s->points;
	set_style(s->style, s->style_val);
	fprintf(tfp, "n %d %d m\n", p->x, p->y);
	xmin = 999999;
	ymin = 999999;
	for (q = p->next; q != NULL; p = q, q = q->next) {
		xmin = min(xmin, p->x);
		ymin = min(ymin, p->y);
		b = a->next;
		fprintf(tfp, "\t%.1f %.1f %.1f %.1f %d %d curveto\n",
				a->rx, a->ry, b->lx, b->ly, q->x, q->y);
		a = b;
	}
	if (closed_spline(s)) fprintf(tfp, " cp ");
	if (s->fill_style != UNFILLED)
		fill_area(s->fill_style, s->pen_color, s->fill_color);
	if (s->thickness > 0) {
		fprintf(tfp, " gs col%d s gr\n", s->pen_color);
		/* reset clipping */
		if (NEEDS_CLIPPING(s))
			fprintf(tfp," gr\n");
	}
	reset_style(s->style, s->style_val);

	/* draw arrowheads after spline for open arrow */
	if (s->back_arrow && s->thickness > 0)
		draw_arrow(s->back_arrow, bpoints, nbpoints,
				bfillpoints, nbfillpoints, s->pen_color);

	if (s->for_arrow && s->thickness > 0)
		draw_arrow(s->for_arrow, fpoints, nfpoints,
				ffillpoints, nffillpoints, s->pen_color);
}

static void
genps_ctl_spline(F_spline *s)
{
	double		a, b, c, d, x1, y1, x2, y2, x3, y3;
	F_point		*p, *q;
	int		xmin, ymin;

	if (closed_spline(s))
		fprintf(tfp, "%% Closed spline\n");
	else
		fprintf(tfp, "%% Open spline\n");

	p = s->points;
	x1 = p->x;
	y1 = p->y;
	p = p->next;
	c = p->x;
	d = p->y;
	x3 = a = (x1 + c) / 2;
	y3 = b = (y1 + d) / 2;

	/* first point */
	fpntx1 = round(x1);
	fpnty1 = round(y1);
	/* second point */
	fpntx2 = round(x3);
	fpnty2 = round(y3);

	/* in case there are only two points in this spline */
	x2=x1; y2=y1;
	/* go through the points to find the last two */
	for (q = p->next; q != NULL; p = q, q = q->next) {
		x1 = x3;
		y1 = y3;
		x2 = c;
		y2 = d;
		c = q->x;
		d = q->y;
		x3 = (x2 + c) / 2;
		y3 = (y2 + d) / 2;
	}
	/* next to last point */
	lpntx2 = round(x2);
	lpnty2 = round(y2);
	/* last point */
	lpntx1 = round(c);
	lpnty1 = round(d);
	/* set clipping for any arrowheads */
	if (NEEDS_CLIPPING(s)) {
		fprintf(tfp, "gs ");
		clip_arrows((F_line *)s, OBJ_SPLINE);
	}

	/* now output the points */
	set_style(s->style, s->style_val);
	xmin = 999999;
	ymin = 999999;

	p = s->points;
	x1 = p->x;
	y1 = p->y;
	p = p->next;
	c = p->x;
	d = p->y;
	x3 = a = (x1 + c) / 2;
	y3 = b = (y1 + d) / 2;
	/* in case there are only two points in this spline */
	x2=x1; y2=y1;
	if (closed_spline(s))
		fprintf(tfp, "n %.1f %.1f m\n", a, b);
	else
		fprintf(tfp, "n %.1f %.1f m %.1f %.1f l\n", x1, y1, x3, y3);

	for (q = p->next; q != NULL; p = q, q = q->next) {
		xmin = min(xmin, p->x);
		ymin = min(ymin, p->y);
		x1 = x3;
		y1 = y3;
		x2 = c;
		y2 = d;
		c = q->x;
		d = q->y;
		x3 = (x2 + c) / 2;
		y3 = (y2 + d) / 2;
		fprintf(tfp,
			  "\t%.1f %.1f %.1f %.1f %.1f %.1f DrawSplineSection\n",
				x1, y1, x2, y2, x3, y3);
	}
	/*
	 * At this point, (x2,y2) and (c,d) are the position of the
	 * next-to-last and last point respectively, in the point list
	 */
	if (closed_spline(s)) {
		fprintf(tfp, "\t%.1f %.1f %.1f %.1f %.1f %.1f DrawSplineSection"
				" closepath ", x3, y3, c, d, a, b);
	} else {
		fprintf(tfp, "\t%.1f %.1f l ", c, d);
	}
	if (s->fill_style != UNFILLED)
		fill_area(s->fill_style, s->pen_color, s->fill_color);
	if (s->thickness > 0) {
		fprintf(tfp, " gs col%d s gr\n", s->pen_color);
		/* reset clipping */
		if (NEEDS_CLIPPING(s))
			fprintf(tfp," gr\n");
	}
	reset_style(s->style, s->style_val);

	/* draw arrowheads after spline */
	if (s->back_arrow && s->thickness > 0)
		draw_arrow(s->back_arrow, bpoints, nbpoints,
				bfillpoints, nbfillpoints, s->pen_color);
	if (s->for_arrow && s->thickness > 0)
		draw_arrow(s->for_arrow, fpoints, nfpoints,
				ffillpoints, nffillpoints, s->pen_color);
}

void
genps_arc(F_arc *a)
{
	double		angle1, angle2, dx, dy, radius;
	double		cx, cy, sx, sy, ex, ey;
	int		direction;

	do_split(a->depth);

	/* print any comments prefixed with "%" */
	print_comments("% ",a->comments, "");

	fprintf(tfp, "%% Arc\n");

	if (multi_page)
		fprintf(tfp, "/o%d {", no_obj++);

	cx = a->center.x; cy = a->center.y;
	sx = a->point[0].x; sy = a->point[0].y;
	ex = a->point[2].x; ey = a->point[2].y;

	direction = a->direction;
	set_linewidth((double)a->thickness);
	set_linecap(a->cap_style);
	dx = cx - sx;
	dy = cy - sy;
	radius = sqrt(dx*dx+dy*dy);
	if (cx==sx)
		angle1 = (sy-cy > 0? 90.0: -90.0);
	else
		angle1 = atan2(sy-cy, sx-cx) * 180.0 / M_PI;
	if (cx==ex)
		angle2 = (ey-cy > 0? 90.0: -90.0);
	else
		angle2 = atan2(ey-cy, ex-cx) * 180.0 / M_PI;

	/* workaround for arcs with start point = end point;
	   make angles slightly different */
	if (fabs(angle1 - angle2) < 0.001)
		angle2 = angle1 + 0.01;

	if (a->type == T_OPEN_ARC && NEEDS_CLIPPING(a)) {
		/* set clipping for any arrowheads */
		fprintf(tfp, "gs ");
		if (a->for_arrow || a->back_arrow)
			clip_arrows((F_line *)a, OBJ_ARC);
	}

	set_style(a->style, a->style_val);

	/* draw the arc now */
	/* direction = 1 -> Counterclockwise */
	fprintf(tfp, "n %.1f %.1f %.1f %.4f %.4f %s\n",
			cx, cy, radius, angle1, angle2,
			((direction == 1) ? "arcn" : "arc"));

	if (a->type == T_PIE_WEDGE_ARC)
		fprintf(tfp,"%.1f %.1f l %.1f %.1f l ",cx,cy,sx,sy);

	/******	The upper-left values (dx, dy) aren't really correct so	  *****/
	/******	the fill pattern alignment between a filled arc and other *****/
	/******	filled objects will not be correct			  *****/
	if (a->fill_style != UNFILLED)
		fill_area(a->fill_style, a->pen_color, a->fill_color);
	if (a->thickness > 0)
		fprintf(tfp, "gs col%d s gr\n", a->pen_color);

	if (a->type == T_OPEN_ARC && NEEDS_CLIPPING(a)) {
		/* reset clipping */
		fprintf(tfp," gr\n");
	}
	reset_style(a->style, a->style_val);

	/* now draw the arrowheads, if any */
	if (a->type == T_OPEN_ARC) {
		if (a->back_arrow && a->thickness > 0)
			draw_arrow(a->back_arrow, bpoints, nbpoints,
					bfillpoints, nbfillpoints,a->pen_color);
		if (a->for_arrow && a->thickness > 0)
			draw_arrow(a->for_arrow, fpoints, nfpoints,
					ffillpoints, nffillpoints,a->pen_color);
	}
	if (multi_page)
		fprintf(tfp, "} bind def\n");
}

void
genps_ellipse(F_ellipse *e)
{
	do_split(e->depth);

	fprintf(tfp, "%% Ellipse\n");

	/* print any comments prefixed with "%" */
	print_comments("% ",e->comments, "");

	if (multi_page)
		fprintf(tfp, "/o%d {", no_obj++);

	set_linewidth((double)e->thickness);
	set_style(e->style, e->style_val);
	if (e->style == DOTTED_LINE)
		set_linecap(1);	/* round dots */
	else
		set_linecap(0);
	if (e->angle == 0) {
		fprintf(tfp, "n %d %d %d %d 0 360 DrawEllipse ",
				e->center.x, e->center.y, e->radiuses.x,
				e->radiuses.y);
	} else {
		fprintf(tfp, "gs\n");
		fprintf(tfp, "%d %d tr\n",e->center.x, e->center.y);
		fprintf(tfp, "%6.3f rot\n",-e->angle*180.0/M_PI);
		fprintf(tfp, "n 0 0 %d %d 0 360 DrawEllipse ",
				e->radiuses.x, e->radiuses.y);
		/* rotate back so any fill pattern will come out correct */
		fprintf(tfp, "%6.3f rot\n",e->angle*180.0/M_PI);
	}
	if (e->fill_style != UNFILLED)
		fill_area(e->fill_style, e->pen_color, e->fill_color);
	if (e->thickness > 0)
		fprintf(tfp, "gs col%d s gr\n", e->pen_color);
	if (e->angle != 0)
		fprintf(tfp, "gr\n");
	reset_style(e->style, e->style_val);
	if (multi_page)
		fprintf(tfp, "} bind def\n");
}


#define	TEXT_PS		"\
/%s%s ff %.2f scf sf\n\
"
void
genps_text(F_text *t)
{
	unsigned char		*cp;
#ifdef I18N
#define LINE_LENGTH_LIMIT 200
	bool composite = false;
	bool state_gr = false;
	int chars = 0;
	int gr_chars = 0;
	unsigned char ch;
#endif /* I18N */

	do_split(t->depth);

	/* ignore hidden text (new for xfig3.2.3/fig2dev3.2.3) */
	if (hidden_text(t))
		return;

	if (multi_page)
		fprintf(tfp, "/o%d {", no_obj++);

	/* print any comments prefixed with "%" */
	print_comments("% ",t->comments, "");

#ifdef I18N
	if (enable_composite_font && ((t->flags & PSFONT_TEXT) ?
				(t->font <= 0 || t->font == 2) :
				(t->font <= 2))) {
		composite = true;
		if (t->font <= 0)
			fprintf(tfp, TEXT_PS, "CompositeRoman", "",
					PSFONTMAG(t));
		else
			fprintf(tfp, TEXT_PS, "CompositeBold", "",PSFONTMAG(t));
	} else
#endif /* I18N */
		if (PSisomap[t->font+1] == true)
			fprintf(tfp, TEXT_PS, PSFONT(t), "-iso", PSFONTMAG(t));
		else
			fprintf(tfp, TEXT_PS, PSFONT(t), "", PSFONTMAG(t));

	fprintf(tfp, "%d %d m\ngs ", t->base_x,  t->base_y);
	fprintf(tfp, "1 -1 sc ");

	if (t->angle != 0.0)
		fprintf(tfp, " %.1f rot ", t->angle*180.0/M_PI);
	/* this loop escapes characters '(', ')', and '\' */
	fputc('(', tfp);
#ifdef I18N
	for(cp = (unsigned char *)t->cstring; *cp; cp++) {
		if (LINE_LENGTH_LIMIT < chars) {
			fputs("\\\n", tfp);
			chars = 0;
		}
		ch = *cp;
		if (enable_composite_font && composite) {
			if (ch & 0x80) {	/* GR */
				if (!state_gr) {
					fprintf(tfp, "\\377\\001");
					chars += 8;
					state_gr = true;
					gr_chars = 0;
				}
				gr_chars++;
			} else {	/* GL */
				if (state_gr) {
					if (gr_chars % 2) {
						put_msg("warning: incomplete "
							"multi-byte text: %s",
								t->cstring);
						fputc('?', tfp);
					}
					fprintf(tfp, "\\377\\000");
					chars += 8;
					state_gr = false;
				}
			}
		}
		if (strchr("()\\", ch)) {
			fputc('\\', tfp);
			chars += 1;
		}
		if (ch>=0x80) {
			fprintf(tfp,"\\%o", ch);
			chars += 4;
		} else {
			fputc(ch, tfp);
			chars += 1;
		}
	}
	if (enable_composite_font && composite && state_gr) {
		if (gr_chars % 2) {
			put_msg("warning: incomplete multi-byte text: %s",
					t->cstring);
			fputc('?', tfp);
		}
	}
#else
	for(cp = (unsigned char *)t->cstring; *cp; cp++) {
		if (strchr("()\\", *cp))
			fputc('\\', tfp);
		if (*cp>=0x80)
			fprintf(tfp,"\\%o", *cp);
		else
			fputc(*cp, tfp);
	}
#endif /* I18N */
	fputc(')', tfp);

	if ((t->type == T_CENTER_JUSTIFIED) || (t->type == T_RIGHT_JUSTIFIED)){

		fprintf(tfp, " dup sw pop ");
		if (t->type == T_CENTER_JUSTIFIED) fprintf(tfp, "2 div ");
		fprintf(tfp, "neg 0 rm ");
	}

	else if ((t->type != T_LEFT_JUSTIFIED) && (t->type != DEFAULT))
		fprintf(stderr, "Text incorrectly positioned\n");

	fprintf(tfp, " col%d sh gr\n", t->color);

	if (multi_page)
		fprintf(tfp, "} bind def\n");
}

/* draw arrow from the points array */

static void
draw_arrow(F_arrow *arrow, F_pos *points, int npoints,
		F_pos *fillpoints, int nfillpoints, int col)
{
	int i, type;

	fprintf(tfp,"%% arrowhead\n");
	set_linecap(0);			/* butt line cap for arrowheads */
	set_linejoin(0);		/* miter join for sharp points */
	set_linewidth(arrow->thickness);
	fprintf(tfp, "n ");
	for (i=0; i<npoints; i++) {
		fprintf(tfp, "%d %d ",points[i].x,points[i].y);
		if (i==0)
			fprintf(tfp, "m ");
		else
			fprintf(tfp, "l ");
		if ((i+1)%5 == 0)
			fprintf(tfp,"\n");
	}

	type = arrow->type;
	if (type != 0 && type != 6 && type < 13) /* old heads, close the path */
		fprintf(tfp, " cp ");
	if (type == 0) {
		/* stroke */
		fprintf(tfp, " col%d s\n",col);
	} else {
		if (arrow->style == 0 && nfillpoints == 0) {
			/* hollow, fill with white */
			fill_area(NUMSHADES-1, WHITE_COLOR, WHITE_COLOR);
			/* stroke */
			fprintf(tfp, " col%d s\n",col);
		} else {
			if (nfillpoints == 0) {
				if (type < 13) {
					if (arrow->style == 0)
						/* fill with white */
						fill_area(NUMSHADES-1,
								WHITE_COLOR,
								WHITE_COLOR);
					else
						/* fill with color */
						fill_area(NUMSHADES-1, col,col);
				}
				/* stroke */
				fprintf(tfp, " col%d s\n",col);
			} else {
				/* special fill, first fill whole head
				   with white */
				fill_area(NUMSHADES-1, WHITE_COLOR,WHITE_COLOR);
				/* stroke */
				fprintf(tfp, " col%d s\n",col);
				/* now describe the special fill area */
				fprintf(tfp, "n ");
				for (i=0; i<nfillpoints; i++) {
					fprintf(tfp, "%d %d ", fillpoints[i].x,
							fillpoints[i].y);
					if (i==0)
						fprintf(tfp, "m ");
					else
						fprintf(tfp, "l ");
					if ((i+1)%5 == 0)
						fprintf(tfp,"\n");
				}
				/* then fill special fill area */
				fill_area(NUMSHADES-1, col, col);
			}
		}
	}
}

/****************************************************************

 clip_arrows - calculate a clipping region which is the current
	clipping area minus the polygons at the arrowheads.

 This will prevent the object (line, spline etc.) from protruding
 on either side of the arrowhead Also calculate the arrowheads
 themselves and put the polygons in fpoints[nfpoints] for forward
 arrow and bpoints[nbpoints] for backward arrow.
 The calling routine should first do a "gs" (graphics state save)
 so that it can restore the original clip area later.

****************************************************************/

static void
clip_arrows(F_line *obj, int objtype)
{
	int		    i;

	/* get current clip area */
	fprintf(tfp," clippath\n");
	/* get points for any forward arrowhead */
	if (obj->for_arrow) {
		if (objtype == OBJ_ARC) {
			F_arc  *a = (F_arc *) obj;
			/* last point */
			lpntx1 = a->point[2].x;
			lpnty1 = a->point[2].y;
			compute_arcarrow_angle(a->center.x, a->center.y,
					(double)lpntx1, (double)lpnty1,
					a->direction, a->for_arrow,
					&lpntx2, &lpnty2);
		}
		calc_arrow(lpntx2, lpnty2, lpntx1, lpnty1, obj->thickness,
				obj->for_arrow, fpoints, &nfpoints, ffillpoints,
				&nffillpoints, clippoints, &nclippoints);
		/* set the clipping area */
		for (i=nclippoints-1; i>=0; i--) {
			fprintf(tfp,"%d %d %c ", clippoints[i].x,
					clippoints[i].y,
					i == nclippoints - 1 ? 'm' : 'l');
		}
		fprintf(tfp, "cp\n");
	}

	/* get points for any backward arrowhead */
	if (obj->back_arrow) {
		if (objtype == OBJ_ARC) {
			F_arc  *a = (F_arc *) obj;
			/* first point */
			fpntx1 = a->point[0].x;
			fpnty1 = a->point[0].y;
			compute_arcarrow_angle(a->center.x, a->center.y,
					(double)fpntx1, (double)fpnty1,
					a->direction ^ 1, a->back_arrow,
					&fpntx2, &fpnty2);
		}
		calc_arrow(fpntx2, fpnty2, fpntx1, fpnty1, obj->thickness,
				obj->back_arrow, bpoints, &nbpoints,bfillpoints,
				&nbfillpoints, clippoints, &nclippoints);
		/* set the clipping area */
		for (i=nclippoints-1; i>=0; i--) {
			fprintf(tfp,"%d %d %c ",clippoints[i].x,clippoints[i].y,
					i == nclippoints - 1 ? 'm' : 'l');
		}
		fprintf(tfp, "cp\n");
	}
	/* intersect the arrowhead clip path(s) with current clip path */
	/* use eoclip so that the intersection with the current path
	   guarantees the correct clip path */
	fprintf(tfp, "eoclip\n");
}

/* uses eofill (even/odd rule fill) */
/* ulx and uly define the upper-left corner of the object for pattern alignment */

static void
fill_area(int fill, int pen_color, int fill_color)
{
	double pen_r, pen_g, pen_b, fill_r, fill_g, fill_b;

	/* get the rgb values for the fill pattern (if necessary) */
	if (fill_color < NUM_STD_COLS) {
		fill_r=rgbcols[fill_color>0? fill_color: 0].r;
		fill_g=rgbcols[fill_color>0? fill_color: 0].g;
		fill_b=rgbcols[fill_color>0? fill_color: 0].b;
	} else {
		fill_r=user_colors[fill_color-NUM_STD_COLS].r/255.0;
		fill_g=user_colors[fill_color-NUM_STD_COLS].g/255.0;
		fill_b=user_colors[fill_color-NUM_STD_COLS].b/255.0;
	}
	if (pen_color < NUM_STD_COLS) {
		pen_r=rgbcols[pen_color>0? pen_color: 0].r;
		pen_g=rgbcols[pen_color>0? pen_color: 0].g;
		pen_b=rgbcols[pen_color>0? pen_color: 0].b;
	} else {
		pen_r=user_colors[pen_color-NUM_STD_COLS].r/255.0;
		pen_g=user_colors[pen_color-NUM_STD_COLS].g/255.0;
		pen_b=user_colors[pen_color-NUM_STD_COLS].b/255.0;
	}

	if (fill_color <= 0 && fill < NUMSHADES+NUMTINTS)
		/* use gray levels for default and black shades and tints */
		fprintf(tfp, "gs %.2f setgray ef gr ", 1.0 - SHADEVAL(fill));

	else if (fill < NUMSHADES)
		/* a shaded color (not black) */
		fprintf(tfp, "gs col%d %.2f shd ef gr ", fill_color,
				SHADEVAL(fill));

	else if (fill < NUMSHADES+NUMTINTS)
		/* a tint */
		fprintf(tfp, "gs col%d %.2f tnt ef gr ", fill_color,
				TINTVAL(fill));

	else {
		/* one of the patterns */
		int patnum = fill-NUMSHADES-NUMTINTS+1;
		char colorspace[13], pencolor[25], fillcolor[25];

		if (grayonly) {
			double grayfill, graypen;
			grayfill = rgb2luminance(fill_r, fill_g, fill_b);
			graypen  = rgb2luminance(pen_r, pen_g, pen_b);
			sprintf(colorspace, "/DeviceGray");
			sprintf(fillcolor, "%.2f", grayfill);
			sprintf(pencolor, "%.2f", graypen);
		} else {
			sprintf(colorspace, "/DeviceRGB");
			sprintf(fillcolor, "%.2f %.2f %.2f",
					fill_r, fill_g, fill_b);
			sprintf(pencolor, "%.2f %.2f %.2f",pen_r, pen_g, pen_b);
		}

		fprintf(tfp, "\n%% Fill with pattern background color\n");
		fprintf(tfp, "gs %s setcolorspace %s setcolor fill gr\n",
				colorspace, fillcolor);
		fprintf(tfp, "\n%% Fill with pattern pen color\n");
		fprintf(tfp,"gs %s setcolorspace %s P%d setpattern fill gr\n\n",
				colorspace, pencolor, patnum);
	}
}

/* define standard colors as "col##" where ## is the number */
static void
genps_std_colors(void)
{
	int i;
	for (i=0; i<NUM_STD_COLS; i++) {
		/* hollow arrows are filled with white */
		if (i == WHITE_COLOR || std_color_used[i]) {
			if (grayonly)
				fprintf(tfp, "/col%d {%.3f setgray} bind def\n",
						i, rgb2luminance(rgbcols[i].r,
								rgbcols[i].g,
								rgbcols[i].b));
			else
				fprintf(tfp, "/col%d {%.3f %.3f %.3f srgb} "
						"bind def\n", i, rgbcols[i].r,
						rgbcols[i].g, rgbcols[i].b);
		}
	}
}

/* define user colors as "col##" where ## is the number */
static void
genps_usr_colors(void)
{
	int i;
	for (i=0; i<num_usr_cols; i++) {
		if (grayonly)
			fprintf(tfp, "/col%d {%.3f setgray} bind def\n",
					i+NUM_STD_COLS,
					rgb2luminance(user_colors[i].r/255.0,
						user_colors[i].g/255.0,
						user_colors[i].b/255.0));
		else
			fprintf(tfp, "/col%d {%.3f %.3f %.3f srgb} bind def\n",
					i+NUM_STD_COLS, user_colors[i].r/255.0,
					user_colors[i].g/255.0,
					user_colors[i].b/255.0);
	}
}

static bool
iso_text_exist(F_compound *ob)
{
	F_compound	*c;
	F_text	    *t;
	unsigned char   *s;

	if (ob->texts != NULL) {
		for (t = ob->texts; t != NULL; t = t->next) {
			/* look for any ISO (non-ASCII) chars in
			   non-special text except for pstex */
			if (!strcmp(lang,"pstex") && special_text(t))
				continue;
			for (s = (unsigned char*)t->cstring; *s != '\0'; s++) {
				/* look for characters >= 128 or ASCII '-' */
				if ((*s>127) || (*s=='-'))
					return true;
			}
		}
	}

	for (c = ob->compounds; c != NULL; c = c->next) {
		if (iso_text_exist(c))
			return true;
	}
	return false;
}

static void
encode_all_fonts(F_compound *ob)
{
	F_compound *c;
	F_text     *t;

	if (ob->texts != NULL) {
		for (t = ob->texts; t != NULL; t = t->next)
			if (PSisomap[t->font+1] == false) {
				fprintf(tfp, "/%s /%s-iso isovec ReEncode\n",
						PSFONT(t), PSFONT(t));
				PSisomap[t->font+1] = true;
			}
	}

	for (c = ob->compounds; c != NULL; c = c->next) {
		encode_all_fonts(c);
	}
}

static bool
ellipse_exist(F_compound *ob)
{
	F_compound	*c;

	if (NULL != ob->ellipses)
		return true;

	for (c = ob->compounds; c != NULL; c = c->next) {
		if (ellipse_exist(c))
			return true;
	}

	return false;
}

static bool
approx_spline_exist(F_compound *ob)
{
	F_spline	*s;
	F_compound	*c;

	for (s = ob->splines; s != NULL; s = s->next) {
		if (approx_spline(s))
			return true;
	}

	for (c = ob->compounds; c != NULL; c = c->next) {
		if (approx_spline_exist(c))
			return true;
	}

	return false;
}

/*
 * We must start new figure if the current
 * depth and the last_depth differ by more than one.
 * Depths will be seen with decreasing values.
 * Only comments will be output */
static void
do_split(int actual_depth)
{
	if (actual_depth+1 < last_depth) {
		/* depths differ by more than one */
		if (fig_number > 0) {
			/* end the current figure, if we already had one */
			fprintf(tfp,"%% here ends figure;\n");
		}
		if (actual_depth >= 0) {
			/* start a new figure with a comment */
			fprintf(tfp,"%% \n");
			fprintf(tfp,"%% here starts figure with depth %d\n",
					actual_depth);
			fig_number++;
			/* reset cur_values for multi-postscript. So a new
			   image gets values being set */
			/* This forces the procs that emit the codes to reset
			 * their current values because these sections of code
			 * may be rearranged */
			cur_thickness = -1;
			cur_capstyle = -1;
			cur_joinstyle = -1;
		}
	}
	last_depth = actual_depth;
}

/* driver defs */

struct
driver dev_ps = {
	genps_option,
	genps_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genps_text,
	genps_end,
	INCLUDE_TEXT
};

/* eps is just like ps except with no: pages, pagesize, orientation, offset */

struct
driver dev_eps = {
	geneps_option,
	genps_start,
	genps_grid,
	genps_arc,
	genps_ellipse,
	genps_line,
	genps_spline,
	genps_text,
	genps_end,
	INCLUDE_TEXT
};
