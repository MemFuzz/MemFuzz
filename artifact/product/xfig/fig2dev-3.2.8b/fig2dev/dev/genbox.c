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

/*
 * genbox.c: convert fig to empty box, for inclusion by LaTeX
 *
*/

#include <stdio.h>
#include <stdlib.h>

#include "fig2dev.h"	/* includes bool.h and object.h */
//#include "object.h"
#include "messages.h"

void
genbox_option(char opt, char *optarg)
{
	(void)	optarg;

	switch (opt) {

	case 'G':
	case 'L':
		break;

	default:
		put_msg(Err_badarg, opt, "box");
		exit(1);
	}
}

void
genbox_start(F_compound *objects)
{
	/* print any whole-figure comments prefixed with "%" */
	if (objects->comments)
		print_comments("% ",objects->comments, "");

	/* draw box */
	fprintf(tfp, "\\makebox[%.3fin]{\\rule{0in}{%.3fin}}\n",
		(urx-llx)*mag/ppi, (ury-lly)*mag/ppi);
	}

int
genbox_end(void)
{
	/* all OK */
	return 0;
}

struct driver dev_box = {
	genbox_option,
	genbox_start,
	gendev_nogrid,
	(void (*)(F_arc *))gendev_null,
	(void (*)(F_ellipse *))gendev_null,
	(void (*)(F_line *))gendev_null,
	(void (*)(F_spline *))gendev_null,
	(void (*)(F_text *))gendev_null,
	genbox_end,
	INCLUDE_TEXT
};
