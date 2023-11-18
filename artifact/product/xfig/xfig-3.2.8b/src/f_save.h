/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2020 by Thomas Loimer
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

#ifndef F_SAVE_H
#define F_SAVE_H

#include <stdio.h>
#include "object.h"
#include <X11/Intrinsic.h>


extern int	emergency_save(char *file_name);
extern void	write_arc(FILE *fp, F_arc *a);
extern void	write_compound(FILE *fp, F_compound *com);
extern void	write_ellipse(FILE *fp, F_ellipse *e);
extern void	write_fig_header(FILE *fp);
extern int	write_file(char *file_name, Boolean update_recent);
extern void	write_line(FILE *fp, F_line *l);
extern void	write_spline(FILE *fp, F_spline *s);
extern void	write_text(FILE *fp, F_text *t);
extern void	end_write_tmpfile(void);
extern void	init_write_tmpfile(void);

#endif
