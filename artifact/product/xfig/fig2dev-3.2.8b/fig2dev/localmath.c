/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2007 by Brian V. Smith
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

void
arc_tangent(double x1, double y1, double x2, double y2, int direction,
	double *x, double *y)
{
	if (direction) { /* counter clockwise  */
		*x = x2 - (y2 - y1);
		*y = y2 + (x2 - x1);
	} else {
		*x = x2 + (y2 - y1);
		*y = y2 - (x2 - x1);
	}
}

void
arc_tangent_int(double x1, double y1, double x2, double y2, int direction,
	int *x, int *y)
{
	if (direction) { /* counter clockwise  */
		*x = x2 - (y2 - y1);
		*y = y2 + (x2 - x1);
	} else {
		*x = x2 + (y2 - y1);
		*y = y2 - (x2 - x1);
	}
}
