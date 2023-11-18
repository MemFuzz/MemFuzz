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

#ifndef OBJECT_H
#define OBJECT_H

#include <limits.h>	/* INT_MIN, INT_MAX */

#define		BLACK_COLOR	0
#define		WHITE_COLOR	7

#define		DEFAULT		(-1)
/* for GIF files */
#define		MAXCOLORMAPSIZE	256

#define NUMSHADES	21
#define NUMTINTS	20
#define NUMPATTERNS	22
#define	NUMFILLS	40	/* for convenience, NUMSHADES + NUMTINTS - 1 */

typedef struct f_point {
	int			x, y;
	struct f_point		*next;
} F_point;

typedef struct f_pos {
	int			x, y;
} F_pos;
#define COORD_MIN	INT_MIN
#define COORD_MAX	INT_MAX

typedef struct f_arrow {
	int			type;
	int			style;
	double			thickness;
	double			wid;
	double			ht;
} F_arrow;

typedef struct f_comment {
	char			*comment;
	struct f_comment	*next;
} F_comment;

#define COMMON_PROPERTIES(o)						\
	o->style < SOLID_LINE || o->style > DASH_3_DOTS_LINE ||		\
	o->thickness < 0 || o->depth < 0 || o->depth > 999 ||		\
	o->fill_style < UNFILLED ||					\
	o->fill_style >= NUMSHADES + NUMTINTS + NUMPATTERNS ||		\
	o->style_val < 0.0

typedef struct f_ellipse {
	int			type;
#define		T_ELLIPSE_BY_RAD	1
#define		T_ELLIPSE_BY_DIA	2
#define		T_CIRCLE_BY_RAD		3
#define		T_CIRCLE_BY_DIA		4
	int			style;
	int			thickness;
	int			pen_color;
	int			fill_color;
	int			depth;
	int			pen;
	int			fill_style;
	double			style_val;
	int			direction;
	double			angle;
#define		UNFILLED	-1
#define		WHITE_FILL	0
#define		BLACK_FILL	20
	struct f_pos		center;
	struct f_pos		radiuses;
	struct f_pos		start;
	struct f_pos		end;
	struct f_comment	*comments;
	struct f_ellipse	*next;
} F_ellipse;

#define INVALID_ELLIPSE(e)	\
	e->type < T_ELLIPSE_BY_RAD || e->type > T_CIRCLE_BY_DIA ||	\
	COMMON_PROPERTIES(e) || (e->direction != 1 && e->direction != 0) || \
	e->radiuses.x == 0 || e->radiuses.y == 0 || \
	e->angle < -7. || e->angle > 7.

typedef struct f_arc {
	int			type;
#define		T_OPEN_ARC		1
#define		T_PIE_WEDGE_ARC		2
	int			style;
	int			thickness;
	int			pen_color;
	int			fill_color;
	int			depth;
	int			pen;
	int			fill_style;
	double			style_val;
	struct f_arrow		*for_arrow;
	struct f_arrow		*back_arrow;
	int			cap_style;
/* IMPORTANT: everything above this point must be in the same order
	      for ARC, LINE and SPLINE (LINE has join_style following cap_style */
	int			direction;
	struct {double x, y;}	center;
	struct f_pos		point[3];
	struct f_comment	*comments;
	struct f_arc		*next;
} F_arc;

#define INVALID_ARC(a)	\
	a->type < T_OPEN_ARC || a->type > T_PIE_WEDGE_ARC ||		\
	COMMON_PROPERTIES(a) || a->cap_style < 0 || a->cap_style > 2 ||	\
	a->center.x < COORD_MIN || a->center.x > COORD_MAX ||		\
	a->center.y < COORD_MIN || a->center.y > COORD_MAX ||		\
	(a->direction != 0 && a->direction != 1)

typedef struct f_line {
	int			type;
#define		T_POLYLINE	1
#define		T_BOX		2
#define		T_POLYGON	3
#define		T_ARC_BOX	4
#define		T_PIC_BOX	5
	int			style;
	int			thickness;
	int			pen_color;
	int			fill_color;
	int			depth;
	int			pen;
	int			fill_style;
	double			style_val;
	struct f_arrow		*for_arrow;
	struct f_arrow		*back_arrow;
	int			cap_style;
	struct f_point		*points;
/* IMPORTANT: everything above this point must be in the same order
	      for ARC, LINE and SPLINE (LINE has join_style following cap_style */
	int			join_style;
	int			radius;	/* for T_ARC_BOX */
	struct f_pos		last[2]; /* last and penultimate point */
	struct f_pic		*pic;
	struct f_comment	*comments;
	struct f_line		*next;
} F_line;

#define INVALID_LINE(l)	\
	l->type < T_POLYLINE || l->type > T_PIC_BOX || COMMON_PROPERTIES(l) || \
	l->cap_style < 0 || l->cap_style > 2 ||			\
	l->join_style < 0 || l->join_style > 2 ||		\
	(l->type == T_ARC_BOX && l->radius < 0)

/* for colormap */
#define		RED	0
#define		GREEN	1
#define		BLUE	2
/* transparency: an index into the colormap: num_transp > 0, otherwise */
#define		NO_TRANSPARENCY    0
#define		TRANSP_COLOR	 (-1)	/* transparent color given as
					   rgb triplet */
typedef struct f_pic {
	int			subtype;
#define		P_EPS	0		/* EPS picture type */
#define		P_XBM	1		/* X11 bitmap picture type */
#define		P_XPM	2		/* X11 pixmap (XPM) picture type */
#define		P_GIF	3		/* GIF picture type */
#define		P_JPEG	4		/* JPEG picture type */
#define		P_PCX	5		/* PCX picture type */
#define		P_PPM	6		/* PPM picture type */
#define		P_TIF	7		/* TIFF picture type */
#define		P_PNG	8		/* PNG picture type */
	char			*file;
	int			flipped;
	unsigned char		*bitmap;
	unsigned char		cmap[3][MAXCOLORMAPSIZE];
	int			numcols;	/* number of colors in cmap */
	/*
	 * Png images can have a number of color map entries, or one color,
	 * given as rgb triplet, that should be transparent. A full alpha
	 * channel with partial transparency cannot be handled.
	 */
	int			num_transp;
	unsigned char		transp_col[3];
	unsigned char		*transp_cols;
	float			hw_ratio;
	struct f_pos		bit_size;
#ifdef V4_0
	struct f_compound	*figure; /*ggstemme*/
#endif /* V4_0 */
} F_pic;

extern char EMPTY_PIC[];

typedef struct f_text {
	int			type;
#define		T_LEFT_JUSTIFIED	0
#define		T_CENTER_JUSTIFIED	1
#define		T_RIGHT_JUSTIFIED	2
	int			font;
#define		DEFAULT_FONT		0
#define		ROMAN_FONT		1
#define		BOLD_FONT		2
#define		ITALIC_FONT		3
#define		MODERN_FONT		4
#define		TYPEWRITER_FONT		5
#define		MAX_FONT		5
	double			size;	/* point size */
	int			color;
	int			depth;
	double			angle;	/* in radian */
	int			flags;
#define		RIGID_TEXT		1
#define		SPECIAL_TEXT		2
#define		PSFONT_TEXT		4
#define		HIDDEN_TEXT		8
	double			height;	/* pixels */
	double			length;	/* pixels */
	int			base_x;
	int			base_y;
	int			pen;
	char			*cstring;
	struct f_comment	*comments;
	struct f_text		*next;
} F_text;

#define		MAX_PSFONT	34
#define		MAXFONT(T) (psfont_text(T) ? MAX_PSFONT : MAX_FONT)

#define		rigid_text(t) \
			(t->flags == DEFAULT || (t->flags & RIGID_TEXT))
#define		special_text(t) \
			((t->flags != DEFAULT && (t->flags & SPECIAL_TEXT)))
#define		psfont_text(t) \
			(t->flags != DEFAULT && (t->flags & PSFONT_TEXT))
#define		hidden_text(t) \
			(t->flags != DEFAULT  && (t->flags & HIDDEN_TEXT))

#define INVALID_TEXT(t)	\
	t->type < T_LEFT_JUSTIFIED || t->type > T_RIGHT_JUSTIFIED ||	\
	t->font < DEFAULT || t->font > MAX_PSFONT || t->size < 0.0 ||	\
	t->flags < DEFAULT || t->flags >= 2 * HIDDEN_TEXT ||		\
	t->height < 0 || t->length < 0 || t->angle < -7. || t->angle > 7.

typedef struct f_control {
	double			lx, ly, rx, ry;	/* used by older versions*/
	struct f_control	*next;
	double                  s;		/* used by 3.2 version */
} F_control;

#define		int_spline(s)		(s->type & 0x2)
#define		x_spline(s)	        (s->type & 0x4)
#define		approx_spline(s)	(!(int_spline(s)|x_spline(s)))
#define		closed_spline(s)	(s->type & 0x1)
#define		open_spline(s)		(!(s->type & 0x1))


#define		S_SPLINE_ANGULAR	0.0
#define		S_SPLINE_APPROX		1.0
#define		S_SPLINE_INTERP		(-1.0)


typedef struct f_spline {
	int			type;
#define		T_OPEN_APPROX		0
#define		T_CLOSED_APPROX		1
#define		T_OPEN_INTERPOLATED	2
#define		T_CLOSED_INTERPOLATED	3
#define		T_OPEN_XSPLINE		4
#define		T_CLOSED_XSPLINE	5
	int			style;
	int			thickness;
	int			pen_color;
	int			fill_color;
	int			depth;
	int			pen;
	int			fill_style;
	double			style_val;
	struct f_arrow		*for_arrow;
	struct f_arrow		*back_arrow;
	int			cap_style;
	struct f_point		*points;
/* IMPORTANT: everything above this point must be in the same order
	      for ARC, LINE and SPLINE (LINE has join_style following cap_style */
	struct f_control	*controls;
	struct f_comment	*comments;
	struct f_spline		*next;
} F_spline;

#define INVALID_SPLINE(s)	\
	s->type < T_OPEN_APPROX || s->type > T_CLOSED_XSPLINE ||	\
	COMMON_PROPERTIES(s) || s->cap_style < 0 || s->cap_style > 2

typedef struct f_compound {
	struct f_pos		nwcorner;
	struct f_pos		secorner;
	struct f_line		*lines;
	struct f_ellipse	*ellipses;
	struct f_spline		*splines;
	struct f_text		*texts;
	struct f_arc		*arcs;
	struct f_compound	*compounds;
	struct f_comment	*comments;
	struct f_compound	*next;
} F_compound;

#define		ARROW_SIZE		sizeof(struct f_arrow)
#define		POINT_SIZE		sizeof(struct f_point)
#define		CONTROL_SIZE		sizeof(struct f_control)
#define		ELLOBJ_SIZE		sizeof(struct f_ellipse)
#define		ARCOBJ_SIZE		sizeof(struct f_arc)
#define		LINOBJ_SIZE		sizeof(struct f_line)
#define		PIC_SIZE		sizeof(struct f_pic)
#define		TEXOBJ_SIZE		sizeof(struct f_text)
#define		SPLOBJ_SIZE		sizeof(struct f_spline)
#define		COMOBJ_SIZE		sizeof(struct f_compound)
#define		COMMENT_SIZE		sizeof(struct f_comment)

/**********************  object codes  **********************/

#define		OBJ_COLOR_DEF		0
#define		OBJ_ELLIPSE		1
#define		OBJ_POLYLINE		2
#define		OBJ_SPLINE		3
#define		OBJ_TEXT		4
#define		OBJ_ARC			5
#define		OBJ_COMPOUND		6
#define		OBJ_END_COMPOUND	(-OBJ_COMPOUND)
#define		OBJ_ALL_OBJECT		99

/************  object styles (except for f_text)  ************/

#define		SOLID_LINE		0
#define		DASH_LINE		1
#define		DOTTED_LINE		2
#define		DASH_DOT_LINE		3
#define		DASH_2_DOTS_LINE	4
#define		DASH_3_DOTS_LINE	5

#define		CLOSED_PATH		0
#define		OPEN_PATH		1

#endif /* OBJECT_H */
