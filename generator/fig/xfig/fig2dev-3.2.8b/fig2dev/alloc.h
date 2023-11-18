/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1985 by  Supoj Sutantavibul
 * Copyright (c) 1991 by Micah Beck
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

#ifndef ALLOC_H
#define ALLOC_H

#define		Line_malloc(z)		z = malloc(LINOBJ_SIZE)
#define		Pic_malloc(z)		z = malloc(PIC_SIZE)
#define		Spline_malloc(z)	z = malloc(SPLOBJ_SIZE)
#define		Ellipse_malloc(z)	z = malloc(ELLOBJ_SIZE)
#define		Arc_malloc(z)		z = malloc(ARCOBJ_SIZE)
#define		Compound_malloc(z)	z = malloc(COMOBJ_SIZE)
#define		Text_malloc(z)		z = malloc(TEXOBJ_SIZE)
#define		Point_malloc(z)		z = malloc(POINT_SIZE)
#define		Control_malloc(z)	z = malloc(CONTROL_SIZE)
#define		Arrow_malloc(z)		z = malloc(ARROW_SIZE)

#endif /* ALLOC_H */
