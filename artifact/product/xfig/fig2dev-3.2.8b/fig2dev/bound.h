/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1985 Supoj Sutanthavibul
 * Copyright (c) 1991 Micah Beck
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
 * Changes:
 *
 * 2016-12-09	Thomas Loimer <thomas.loimer@tuwien.ac.at>
 *	- Add int startclip, remove bool clip in struct _arrow_shape.
 *
 */

#ifndef BOUND_H
#define BOUND_H

extern void arc_bound(F_arc *arc, int *xmin, int *ymin, int *xmax, int *ymax);
extern void compound_bound(F_compound *compound, int *xmin, int *ymin,
			int *xmax, int *ymax, int include);
extern void ellipse_bound(F_ellipse *e, int *xmin, int *ymin,
			int *xmax, int *ymax);
extern void line_bound(F_line *l, int *xmin, int *ymin, int *xmax, int *ymax);
extern void spline_bound(F_spline *s, int *xmin,int *ymin,int *xmax,int *ymax);
extern void text_bound(F_text *t, int *xmin, int *ymin, int *xmax, int *ymax,
			int inc_text);
extern void compute_arcarrow_angle(double x1, double y1, double x2, double y2,
			int direction, F_arrow *arrow, int *x, int *y);
extern void calc_arrow(int x1, int y1, int x2, int y2, int linethick,
			F_arrow *arrow, F_pos points[], int *npoints,
			F_pos fillpoints[], int *nfillpoints, F_pos clippts[],
			int *nclippts);

struct d_pos {
	double x, y;
};

extern struct _arrow_shape {
	int	numpts;		/* number of points in arrowhead */
	int	tipno;		/* which point contains the tip */
	int	numfillpts;	/* number of points to fill */
	int	startclip;	/* point at which clip region starts */
	bool	simplefill;	/* if true, use points array to fill otherwise
				   use fill_points array */
	bool	half;		/* if true, arrowhead is half-wide and must be
				   shifted to cover the line */
	double	tipmv;		/* acuteness of tip (smaller angle, larger tipmv) */
	struct	d_pos points[6]; /* points in arrowhead */
	struct	d_pos fillpoints[6]; /* points to fill if not "simple" */
} arrow_shapes[];

#endif /* BOUND_H */
