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

#ifndef FIG2DEV_H
#define FIG2DEV_H

#include <stdio.h>
#include "bool.h"
#include "object.h"

#define DEFAULT_FONT_SIZE 11

/* defined in <sys/param.h> */
#undef MIN
#undef MAX
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define round(x)	((int) ((x) + ((x >= 0)? 0.5: -0.5)))

#define NUM_STD_COLS	32
#define MAX_USR_COLS	512
#define PAPERSZ_LEN	16

#define NUMARROWS	30	/* Synchronize with arrow_shapes[] in bound.c */

#ifndef RGB_H
#define RGB_H
typedef struct _RGB {
		unsigned short red, green, blue;
	} RGB;
#endif /* RGB_H */

/*
 * Device driver interface structure
 */
struct driver {
	void (*option)(char opt, char *optarg);	/* interpret
						 * driver-specific options */
	void (*start)(F_compound *);		/* output file header */
	void (*grid)(float major, float minor);	/* draw grid */
	void (*arc)(F_arc *);			/* object generators */
	void (*ellipse)(F_ellipse *);
	void (*line)(F_line *);
	void (*spline)(F_spline *);
	void (*text)(F_text *);
	int (*end)(void);	/* output file trailer (returns status) */
	int text_include;	/* include text length in bounding box */
#define INCLUDE_TEXT 1
#define EXCLUDE_TEXT 0
};

extern void	gendev_null(void);
extern void	gendev_nogrid(float major, float minor);
extern void	print_comments(char *string1, F_comment *comment,char *string2);
extern int	depth_filter(int obj_depth);

extern const char	prog[];
extern char	*from, *to;
extern char	*name;
extern double	font_size;
extern double	mag, fontmag;
extern FILE	*tfp;

extern double	ppi;		/* Fig file resolution (e.g. 1200) */
extern int	llx, lly, urx, ury;
extern bool	landscape;
extern bool	center;
extern bool	multi_page;	/* multiple page option for PostScript */
extern bool	overlap;	/* overlap pages in multiple page output */
extern bool	orientspec;	/* true if the command-line args specified land or port */
extern bool	centerspec;	/* true if the command-line args specified -c or -e */
extern bool	magspec;	/* true if the command-line args specified -m */
extern bool	transspec;	/* set if the user specs. the GIF transparent color */
extern bool	paperspec;	/* true if the command-line args specified -z */
extern bool	boundingboxspec;/* true if the command-line args specified -B or -R */
extern bool	adjust_boundingbox; /* set if -K option was given */
extern bool	multispec;	/* true if the command-line args specified -M */
extern bool	metric;		/* true if the file contains Metric specifier */
extern bool	grayonly;	/* convert colors to grayscale (-N option) */
extern bool	bgspec;		/* flag to say -g was specified */
#ifdef I18N
extern bool support_i18n;
#endif
extern char	gif_transparent[8];/* GIF transp color hex name (e.g. #ff00dd)*/
extern char	papersize[PAPERSZ_LEN];	/* paper size */
extern char	boundingbox[];	/* boundingbox */
extern char	lang[];		/* selected output language */
extern const char	*Fig_color_names[]; /* hex names for Fig colors */
extern RGB	background;	/* background (if specified by -g) */
extern float	grid_minor_spacing; /* grid minor spacing (if any) */
extern float	grid_major_spacing; /* grid major spacing (if any) */
extern float	THICK_SCALE;	/* convert line thickness from screen res. */
extern char	gscom[];	/* to build up a command for ghostscript */

struct paperdef
{
	char *name;		/* name for paper size */
	int width;		/* paper width in points */
	int height;		/* paper height in points */
};

/* #define NUMPAPERSIZES 29  * not used in fig2dev, but in xfig/resources.h */
extern const struct paperdef paperdef[];

/* user-defined colors */
typedef	struct{
	int c,r,g,b;
} User_color;

/* TODO: this should probably go into some read.h, or read_info.h */
extern User_color	user_colors[MAX_USR_COLS];
extern int	user_col_indx[MAX_USR_COLS];
extern int	num_usr_cols;
extern bool	pats_used, pattern_used[NUMPATTERNS];
extern bool	std_color_used[NUM_STD_COLS];
extern bool	arrows_used, arrow_used[NUMARROWS];

#endif /* FIG2DEV_H */
