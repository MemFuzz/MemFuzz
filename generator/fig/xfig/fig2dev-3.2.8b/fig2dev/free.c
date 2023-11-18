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


#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "free.h"

void
free_arc(F_arc **list)
{
	F_arc	*a, *arc;

	for (a = *list; a != NULL;) {
	    arc = a;
	    a = a->next;
	    if (arc->for_arrow) free(arc->for_arrow);
	    if (arc->back_arrow) free(arc->back_arrow);
	    if (arc->comments) free_comments(arc->comments);
	    free(arc);
	}
	*list = NULL;
}

void
free_compound(F_compound **list)
{
	F_compound	*c, *compound;

	for (c = *list; c != NULL;) {
	    compound = c;
	    c = c->next;
	    free_arc(&compound->arcs);
	    free_compound(&compound->compounds);
	    free_ellipse(&compound->ellipses);
	    free_line(&compound->lines);
	    free_spline(&compound->splines);
	    free_text(&compound->texts);
	    if (compound->comments) free_comments(compound->comments);
	    free(compound);
	}
	*list = NULL;
}

void
free_ellipse(F_ellipse **list)
{
	F_ellipse	*e, *ellipse;

	for (e = *list; e != NULL;) {
	    ellipse = e;
	    e = e->next;
	    if (ellipse->comments) free_comments(ellipse->comments);
	    free(ellipse);
	}
	*list = NULL;
}

void
free_line(F_line **list)
{
	F_line	*l, *line;

	for (l = *list; l != NULL;) {
	    line = l;
	    l = l->next;
	    free_linestorage(line);
	}
	*list = NULL;
}

void
free_text(F_text **list)
{
	F_text	*t, *text;

	for (t = *list; t != NULL;) {
	    text = t;
	    t = t->next;
	    free(text->cstring);
	    if (text->comments) free_comments(text->comments);
	    free(text);
	}
	*list = NULL;
}

void
free_spline(F_spline **list)
{
	F_spline	*s, *spline;

	for (s = *list; s != NULL;) {
	    spline = s;
	    s = s->next;
	    free_splinestorage(spline);
	}
	*list = NULL;
}

void
free_splinestorage(F_spline *s)
{
	F_point		*p, *q;
	F_control	*a, *b;

	for (p = s->points; p != NULL; p = q) {
	    q = p->next;
	    free(p);
	}
	for (a = s->controls; a != NULL; a = b) {
	    b = a->next;
	    free(a);
	}
	if (s->for_arrow) free(s->for_arrow);
	if (s->back_arrow) free(s->back_arrow);
	if (s->comments) free_comments(s->comments);
	free(s);
}

void
free_linestorage(F_line *l)
{
	F_point	*p, *q;

	for (p = l->points; p != NULL; p = q) {
	    q = p->next;
	    free(p);
	    }
	if (l->for_arrow) free(l->for_arrow);
	if (l->back_arrow) free(l->back_arrow);
	if (l->pic) {
		free(l->pic->file);
		free(l->pic->bitmap);
#ifdef V4_0
		free_compound(l->pic->compound);
#endif
		free(l->pic);
	}
	if (l->comments) free_comments(l->comments);
	free(l);
}

void
free_comments(F_comment *c)
{
	F_comment	*d, *n;

	for (d = c; d != NULL; d = n) {
		n = d->next;
		free(d);
	}
}
