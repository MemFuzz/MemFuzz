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


extern void	free_Fonts(void);
extern void	free_GCs(void);
extern void	free_arc(F_arc **list);
extern void	free_compound(F_compound **list);
extern void	free_ellipse(F_ellipse **list);
extern void	free_line(F_line **list);
extern void	free_linestorage(F_line *l);
extern void	free_linkinfo(F_linkinfo **list);
extern void	free_picture_entry(struct _pics *picture);
extern void	free_points(F_point *first_point);
extern void	free_sfactors(F_sfactor *sf);
extern void	free_spline(F_spline **list);
extern void	free_splinestorage(F_spline *s);
extern void	free_text(F_text **list);
