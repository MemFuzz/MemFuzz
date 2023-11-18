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

/*******************************************************************/
/***************       Read version 1.3 format       ***************/
/*******************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fig2dev.h"	/* includes object.h */
#include "alloc.h"
//#include "object.h"
#include "free.h"
#include "messages.h"

/*******    Fig 1.3 subtype of objects    *******/
#define DRAW_ELLIPSE_BY_RAD	1
#define DRAW_ELLIPSE_BY_DIA	2
#define DRAW_CIRCLE_BY_RAD	3
#define DRAW_CIRCLE_BY_DIA	4
#define DRAW_CIRCULAR_ARC	5
#define DRAW_POLYLINE		6
#define DRAW_BOX		7
#define DRAW_POLYGON		8
#define DRAW_TEXT		9
#define DRAW_SPLINE		10
#define DRAW_CLOSEDSPLINE	11
#define DRAW_COMPOUND		13

extern int		figure_modified;

static F_ellipse	*read_ellipseobject(FILE *fp);
static F_line		*read_lineobject(FILE *fp);
static F_text		*read_textobject(FILE *fp);
static F_spline		*read_splineobject(FILE *fp);
static F_arc		*read_arcobject(FILE *fp);
static F_compound	*read_compoundobject(FILE *fp);
static F_arrow		*forward_arrow(void);
static F_arrow		*backward_arrow(void);

static char		Err_invalid[] = "Invalid %s object.";

#ifdef V4_0
extern int              suppress_error;/*ggstemme*/
#endif /* V4_0 */

int
read_1_3_objects(FILE *fp, F_compound *obj)
{
	F_ellipse	*e, *le = NULL;
	F_line		*l, *ll = NULL;
	F_text		*t, *lt = NULL;
	F_spline	*s, *ls = NULL;
	F_arc		*a, *la = NULL;
	F_compound	*c, *lc = NULL;
	int		 n;
	int		 object, pixperinch, canvaswid, canvasht, coord_sys;

	n = fscanf(fp,"%d%d%d%d\n",
			&pixperinch, &coord_sys, &canvaswid, &canvasht);
	if (n != 4){
#ifdef V4_0
	  if (!suppress_error)
#endif /* V4_0 */
	     put_msg("Incorrect format in the first line in input file");
	  return(-1);
	}
	if (pixperinch <= 0) {
		put_msg("Invalid resolution information (%d).", pixperinch);
		return -1;
	}
	ppi = pixperinch;
	obj->nwcorner.x = pixperinch;
	obj->nwcorner.y = coord_sys;
	while (fscanf(fp, "%d", &object) == 1) {
	    switch (object) {
		case OBJ_POLYLINE :
		    if ((l = read_lineobject(fp)) == NULL) return(-1);
		    if (ll)
			ll = (ll->next = l);
		    else
			ll = obj->lines = l;
		    break;
		case OBJ_SPLINE :
		    if ((s = read_splineobject(fp)) == NULL) return(-1);
		    if (ls)
			ls = (ls->next = s);
		    else
			ls = obj->splines = s;
		    break;
		case OBJ_ELLIPSE :
		    if ((e = read_ellipseobject(fp)) == NULL) return(-1);
		    if (le)
			le = (le->next = e);
		    else
			le = obj->ellipses = e;
		    break;
		case OBJ_ARC :
		    if ((a = read_arcobject(fp)) == NULL) return(-1);
		    if (la)
			la = (la->next = a);
		    else
			la = obj->arcs = a;
		    break;
		case OBJ_TEXT :
		    if ((t = read_textobject(fp)) == NULL) return(-1);
		    if (lt)
			lt = (lt->next = t);
		    else
			lt = obj->texts = t;
		    break;
		case OBJ_COMPOUND :
		    if ((c = read_compoundobject(fp)) == NULL) return(-3);
		    if (lc)
			lc = (lc->next = c);
		    else
			lc = obj->compounds = c;
		    break;
		default:
		    put_msg("Incorrect object code %d", object);
		    return(-1);
		} /*  switch */
	    } /*  while */
	if (feof(fp))
		return 0;
	else
		return -3;
}

static F_arc *
read_arcobject(FILE *fp)
{
	F_arc	*a;
	int	f, b, h, w, n;

	Arc_malloc(a);
	a->pen_color = a->fill_color = BLACK_COLOR;
	a->depth = 0;
	a->pen = 0;
	a->for_arrow = NULL;
	a->back_arrow = NULL;
	a->comments = NULL;
	a->next = NULL;
	n = fscanf(fp,
		" %d %d %d %lf %d %d %d %d %d %lf %lf %d %d %d %d %d %d\n",
		&a->type, &a->style, &a->thickness,
		&a->style_val, &a->direction, &f, &b,
		&h, &w, &a->center.x, &a->center.y,
		&a->point[0].x, &a->point[0].y,
		&a->point[1].x, &a->point[1].y,
		&a->point[2].x, &a->point[2].y);
	a->type = T_OPEN_ARC;
	if (n != 17) {
		put_msg("incomplete arc data");
		free(a);
		return NULL;
	}
	if (INVALID_ARC(a)) {
		put_msg(Err_invalid, "arc");
		free(a);
		return NULL;
	}
	if (f) {
		a->for_arrow = forward_arrow();
		a->for_arrow->wid = w;
		a->for_arrow->ht = h;
	}
	if (b) {
		a->back_arrow = backward_arrow();
		a->back_arrow->wid = w;
		a->back_arrow->ht = h;
	}
	return a;
}

static F_compound *
read_compoundobject(FILE *fp)
{
	F_arc		*a, *la = NULL;
	F_ellipse	*e, *le = NULL;
	F_line		*l, *ll = NULL;
	F_spline	*s, *ls = NULL;
	F_text		*t, *lt = NULL;
	F_compound	*com, *c, *lc = NULL;
	int		 n, object;

	Compound_malloc(com);
	com->arcs = NULL;
	com->ellipses = NULL;
	com->lines = NULL;
	com->splines = NULL;
	com->texts = NULL;
	com->compounds = NULL;
	com->comments = NULL;
	com->next = NULL;
	n = fscanf(fp, " %d %d %d %d\n", &com->nwcorner.x, &com->nwcorner.y,
		&com->secorner.x, &com->secorner.y);
	if (n != 4) {
	    put_msg("Incorrect compound object format");
	    free(com);
	    return(NULL);
	    }
	while (fscanf(fp, "%d", &object) == 1) {
	    switch (object) {
		case OBJ_POLYLINE :
		    if ((l = read_lineobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (ll)
			ll = (ll->next = l);
		    else
			ll = com->lines = l;
		    break;
		case OBJ_SPLINE :
		    if ((s = read_splineobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (ls)
			ls = (ls->next = s);
		    else
			ls = com->splines = s;
		    break;
		case OBJ_ELLIPSE :
		    if ((e = read_ellipseobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (le)
			le = (le->next = e);
		    else
			le = com->ellipses = e;
		    break;
		case OBJ_ARC :
		    if ((a = read_arcobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (la)
			la = (la->next = a);
		    else
			la = com->arcs = a;
		    break;
		case OBJ_TEXT :
		    if ((t = read_textobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (lt)
			lt = (lt->next = t);
		    else
			lt = com->texts = t;
		    break;
		case OBJ_COMPOUND :
		    if ((c = read_compoundobject(fp)) == NULL) {
			free_compound(&com);
			return(NULL);
			}
		    if (lc)
			lc = (lc->next = c);
		    else
			lc = com->compounds = c;
		    break;
		case OBJ_END_COMPOUND :
		    return(com);
		} /*  switch */
	    }
	if (feof(fp)) {
		return com;
	} else {
		put_msg("Fig 1.3 format error.");
		free_compound(&com);
		return NULL;
	}
}

static F_ellipse *
read_ellipseobject(FILE *fp)
{
	F_ellipse	*e;
	int		n, t;

	Ellipse_malloc(e);
	e->pen_color = e->fill_color = BLACK_COLOR;
	e->angle = 0.0;
	e->depth = 0;
	e->pen = 0;
	e->fill_style = UNFILLED;
	e->comments = NULL;
	e->next = NULL;
	n = fscanf(fp," %d %d %d %lf %d %d %d %d %d %d %d %d %d\n",
			&t, &e->style,
			&e->thickness, &e->style_val, &e->direction,
			&e->center.x, &e->center.y,
			&e->radiuses.x, &e->radiuses.y,
			&e->start.x, &e->start.y,
			&e->end.x, &e->end.y);
	if (n != 13) {
		put_msg("incomplete ellipse data");
		free(e);
		return NULL;
	}
	if (t == DRAW_ELLIPSE_BY_RAD)
		e->type = T_ELLIPSE_BY_RAD;
	else if (t == DRAW_ELLIPSE_BY_DIA)
		e->type = T_ELLIPSE_BY_DIA;
	else if (t == DRAW_CIRCLE_BY_RAD)
		e->type = T_CIRCLE_BY_RAD;
	else
		e->type = T_CIRCLE_BY_DIA;
	if (INVALID_ELLIPSE(e)) {
		put_msg(Err_invalid, "ellipse");
		free(e);
		return NULL;
	}
	return e;
}

static F_line *
read_lineobject(FILE *fp)
{
	F_line	*l;
	F_point	*p, *q;
	int	f, b, h, w, n, t, x, y;

	Line_malloc(l);
	l->pen_color = l->fill_color = BLACK_COLOR;
	l->depth = 0;
	l->pen = 0;
	l->fill_style = UNFILLED;
	l->cap_style = 0;
	l->join_style = 0;
	l->for_arrow = NULL;
	l->back_arrow = NULL;
	l->next = NULL;
	l->points = Point_malloc(p);
	l->points->next = NULL;
	l->pic = NULL;
	l->comments = NULL;
	n = fscanf(fp, " %d %d %d %lf %d %d %d %d %d %d", &t,
			&l->style, &l->thickness, &l->style_val,
			&f, &b, &h, &w, &p->x, &p->y);
	if (n != 10) {
		put_msg("incomplete line data");
		free_linestorage(l);
		return NULL;
	}
	if (t == DRAW_POLYLINE)
		l->type = T_POLYLINE;
	else if (t == DRAW_POLYGON)
		l->type = T_POLYGON;
	else
		l->type = T_BOX;
	if (INVALID_LINE(l)) {
		put_msg(Err_invalid, "line");
		free_linestorage(l);
		return NULL;
	}
	if (f) {
		l->for_arrow = forward_arrow();
		l->for_arrow->wid = w;
		l->for_arrow->ht = h;
	}
	if (b) {
		l->back_arrow = backward_arrow();
		l->back_arrow->wid = w;
		l->back_arrow->ht = h;
	}
	for (;;) {
		if (fscanf(fp, " %d %d", &x, &y) != 2) {
			put_msg("incomplete line object");
			free_linestorage(l);
			return(NULL);
		}
		if (x == 9999) break;
		Point_malloc(q);
		q->x = x;
		q->y = y;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	return l;
}

static F_spline *
read_splineobject(FILE *fp)
{
	F_spline	*s;
	F_point		*p, *q;
	int		f, b, h, w, n, t, x, y;

	Spline_malloc(s);
	s->pen_color = s->fill_color = BLACK_COLOR;
	s->depth = 0;
	s->pen = 0;
	s->fill_style = UNFILLED;
	s->cap_style = 0;
	s->for_arrow = NULL;
	s->back_arrow = NULL;
	s->controls = NULL;
	s->comments = NULL;
	s->next = NULL;
	s->points = Point_malloc(p);
	s->points->next = NULL;
	n = fscanf(fp, " %d %d %d %lf %d %d %d %d %d %d",
			&t, &s->style, &s->thickness, &s->style_val,
			&f, &b,
			&h, &w, &p->x, &p->y);
	if (n != 10) {
		put_msg("incomplete spline data");
		free_splinestorage(s);
		return NULL;
	}
	if (t == DRAW_CLOSEDSPLINE)
		s->type = T_CLOSED_APPROX;
	else
		s->type = T_OPEN_APPROX;
	if (INVALID_SPLINE(s)) {
		put_msg(Err_invalid, "spline");
		free_splinestorage(s);
		return NULL;
	}
	if (f) {
		s->for_arrow = forward_arrow();
		s->for_arrow->wid = w;
		s->for_arrow->ht = h;
	}
	if (b) {
		s->back_arrow = backward_arrow();
		s->back_arrow->wid = w;
		s->back_arrow->ht = h;
	}
	for (;;) {
		if (fscanf(fp, " %d %d", &x, &y) != 2) {
			put_msg("incomplete spline object");
			free_splinestorage(s);
			return NULL;
		};
		if (x == 9999) break;
		Point_malloc(q);
		q->x = x;
		q->y = y;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	if (s->points->next == NULL) {
		put_msg("spline with a single point");
		free_splinestorage(s);
		return NULL;
	}
	return(s);
}

static F_text *
read_textobject(FILE *fp)
{
	F_text	*t;
	int	n;
	char	buf[128];

	Text_malloc(t);
	t->type = T_LEFT_JUSTIFIED;
	t->flags = 0;
	t->color = BLACK_COLOR;
	t->depth = 0;
	t->pen = 0;
	t->angle = 0.0;
	t->comments = NULL;
	t->next = NULL;
	n = fscanf(fp," %d %lf %d %lf %lf %d %d %127[^\n]", &t->font,
		&t->size, &t->flags, &t->height, &t->length,
		&t->base_x, &t->base_y, buf);
	if (n != 8) {
		put_msg("incomplete text data");
		free((char*)t);
		return(NULL);
	}
	if (INVALID_TEXT(t)) {
		put_msg(Err_invalid, "text");
		free(t);
		return NULL;
	}
	t->cstring = (char *) calloc((unsigned)(strlen(buf)+1), sizeof(char));
	if (t->cstring == NULL) {
		put_msg(Err_mem);
		free(t);
		return NULL;
	}
	(void)strcpy(t->cstring, buf);
	if (t->size == 0)
		t->size = 18;
	return t;
}

static F_arrow *
forward_arrow(void)
{
	F_arrow		*a;

	if (NULL == (Arrow_malloc(a))) {
		put_msg(Err_mem);
		return(NULL);
	}
	a->type = 0;
	a->style = 0;
	a->thickness = THICK_SCALE;
	a->wid = 4.0;
	a->ht = 8.0;
	return a;
}

static F_arrow *
backward_arrow(void)
{
	F_arrow		*a;

	if (NULL == (Arrow_malloc(a))) {
		put_msg(Err_mem);
		return(NULL);
	}
	a->type = 0;
	a->style = 0;
	a->thickness = THICK_SCALE;
	a->wid = 4.0;
	a->ht = 8.0;
	return a;
}
