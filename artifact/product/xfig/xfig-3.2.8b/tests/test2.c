/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2019 by Thomas Loimer
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
 *	test2.c: Test round_coords(), defined in src/w_canvas.c.
 *	Author: Thomas Loimer, 2017-12-27
 *
 * Check, whether points close to, but not exact half-way between two grid
 * points are rounded correctly. Half-way points need not be overly correct.
 * For instance, the interval around (0,0) may be two units shorter than
 * other intervals. The user would have to be very accurate to notice.
 * Also, check for overflow at INT_MIN, INT_MAX.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <limits.h>
#include <math.h>

#include "fig.h"
#include "resources.h"	/* must come before mode.h; struct appres */
#include "mode.h"

extern void round_coords(int *x, int *y);		/* w_canvas.h */

/*
 * defined in mode.h:
 *	cur_gridunit		MM_UNIT, FRACT_UNIT, TENTH_UNIT
 *	cur_pointposn		P_ANY, P_MAGNET, P_GRID1, ..., P_GRID4
 *	cur_gridtype		GRID_ISO, GRID_SQUARE
 *	anypointposn		True or False
 */

static void
printmsg(int x, int y, int xr, int yr)
{
	printf("%s grid, spacing %d, grid_unit (mm, frac, tenth) = %d:\n",
			cur_gridtype == GRID_SQUARE ? "Square": "Isometric",
			posn_rnd[cur_gridunit][cur_pointposn], cur_gridunit);
	printf("    Point (%d, %d) rounded to (%d, %d).\n", x, y, xr, yr);
}

int
compare(int xc, int yc, int n, int pts[n][2])
{
	int i, x, y;
	int error = 0;

	for (i = 0; i < n; ++i) {
		x = pts[i][0];
		y = pts[i][1];
		round_coords(&x, &y);
		if (x != xc || y != yc) {
			printmsg(pts[i][0], pts[i][1], x, y);
			error += 1;
		}
	}
	return error;
}

int
main(void)
{
	int x, y, yspacing, xc, yc, dist, xdist;
	int error = 0;
	int pts_square[2][2];
	int pts_iso[4][2];
	const double cos30 = sqrt(0.75);

	/* avoid division by zero in point_spacing() in w_canvas.c */
	appres.userscale = 1.0f;
	anypointposn = 0;
	for (cur_pointposn = P_MAGNET; cur_pointposn <= P_GRID4;
					++cur_pointposn) {
		for (cur_gridunit = MM_UNIT; cur_gridunit <= TENTH_UNIT;
						++cur_gridunit) {
			cur_gridtype = GRID_SQUARE;
			yspacing = posn_rnd[cur_gridunit][cur_pointposn];
			yc = 0;
			dist = yspacing/2 - 2;
			pts_square[0][0] = pts_square[0][1] = yc - dist;
			pts_square[1][0] = pts_square[1][1] = yc + dist;
			error += compare(yc, yc, 2, pts_square);

			yc = -8 * yspacing;
			pts_square[0][0] = pts_square[0][1] = yc - dist;
			pts_square[1][0] = pts_square[1][1] = yc + dist;
			error += compare(yc, yc, 2, pts_square);

			yc = (INT_MAX / yspacing - 1) * yspacing;
			pts_square[0][0] = pts_square[0][1] = yc - dist;
			pts_square[1][0] = pts_square[1][1] = yc + dist;
			error += compare(yc, yc, 2, pts_square);

			yc = (-(INT_MAX / yspacing) + 1) * yspacing;
			pts_square[0][0] = pts_square[0][1] = yc - dist;
			pts_square[1][0] = pts_square[1][1] = yc + dist;
			error += compare(yc, yc, 2, pts_square);

			/* Test for overflow. */
			x = y = yc = INT_MIN;
			round_coords(&x, &y);
			if (x > INT_MIN + yspacing || y > INT_MIN + yspacing) {
				printmsg(yc, yc, x, y);
				error += 1;
			}

			x = y = yc = INT_MAX;
			round_coords(&x, &y);
			if (x < INT_MAX - yspacing || y < INT_MAX - yspacing) {
				printmsg(yc, yc, x, y);
				error += 1;
			}


			cur_gridtype = GRID_ISO;
			yc = xc = 0;
			xdist = cos30 * yspacing / 2 - 1;;
			dist = yspacing/2 - 1;
			pts_iso[0][0] = xc - xdist;  pts_iso[0][1] = yc + dist;
			pts_iso[1][0] = xc - xdist;  pts_iso[1][1] = yc - dist;
			pts_iso[2][0] = xc + xdist;  pts_iso[2][1] = yc + dist;
			pts_iso[3][0] = xc + xdist;  pts_iso[3][1] = yc - dist;
			error += compare(xc, yc, 4, pts_iso);

			yc = -8 * yspacing;
			xc = 2 * yc * cos30;
			pts_iso[0][0] = xc - xdist;  pts_iso[0][1] = yc + dist;
			pts_iso[1][0] = xc - xdist;  pts_iso[1][1] = yc - dist;
			pts_iso[2][0] = xc + xdist;  pts_iso[2][1] = yc + dist;
			pts_iso[3][0] = xc + xdist;  pts_iso[3][1] = yc - dist;
			error += compare(xc, yc, 4, pts_iso);

			/* Test for overflow. */
			x = y = yc = INT_MIN;
			round_coords(&x, &y);
			if (x > INT_MIN + yspacing * cos30 + 1 ||
					y > INT_MIN + yspacing) {
				printmsg(yc, yc, x, y);
				error += 1;
			}

			x = y = yc = INT_MAX;
			round_coords(&x, &y);
			if (x < INT_MAX - yspacing * cos30 - 1 ||
					y < INT_MAX - yspacing) {
				printmsg(yc, yc, x, y);
				error += 1;
			}

		}
	}
	return error;
}
