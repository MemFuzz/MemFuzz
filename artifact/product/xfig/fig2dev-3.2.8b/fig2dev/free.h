/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
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

#ifndef FREE_H
#define FREE_H

void free_arc(F_arc **list);
void free_compound(F_compound **list);
void free_ellipse(F_ellipse **list);
void free_line(F_line **list);
void free_text(F_text **list);
void free_spline(F_spline **list);
void free_splinestorage(F_spline *s);
void free_linestorage(F_line *l);
void free_comments(F_comment *c);

#endif /* FREE_H */
