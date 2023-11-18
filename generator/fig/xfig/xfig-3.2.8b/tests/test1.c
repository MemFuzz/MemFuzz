/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2021 by Thomas Loimer
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

/*
 *	test1.c: Test {floor,ceil}_coords_[xy](), defined in src/u_bound.c.
 *	Author: Thomas Loimer, 2017-12-26
 *
 * Test, whether the "smaller than zero inverts problem"-lines in the
 * {floor,ceil}_coords_[xy]() functions do not cause overflow.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <limits.h>

extern int floor_coords_x();		/* from "u_bound.h" */
extern int floor_coords_y();		/* from "u_bound.h" */
extern int ceil_coords_x();		/* from "u_bound.h" */
extern int ceil_coords_y();		/* from "u_bound.h" */
extern int cur_pointposn;		/* mode.h */

/* stubs */
void
round_coords(int *x, int *y)
{
	(void) x; (void) y;
}

int
main(void)
{
	int errcode = 0;

	cur_pointposn = 2;	/* == P_GRID1, see mode.h */

	/* Since round_coords() is replaced by the no-op above, the
	   expected results are as below. */
	if (floor_coords_x(INT_MIN, 0) != INT_MIN)
		errcode |= 0x1;
	if (floor_coords_y(0, INT_MIN) != INT_MIN)
		errcode |= 0x2;
	if (ceil_coords_x(INT_MIN, 0) != -INT_MAX)
		errcode |= 0x4;
	if (ceil_coords_y(0, INT_MIN) != -INT_MAX)
		errcode |= 0x8;
	return errcode;
}
