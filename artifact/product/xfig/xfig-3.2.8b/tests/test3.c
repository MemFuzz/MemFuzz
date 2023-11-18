/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2007 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2021 by Thomas Loimer
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
 *	test3.c: Read the /MediaBox from a pdf file
 *	Author: Thomas Loimer, 2020
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include "resources.h"

/* u_ghostscript.c */
extern int	gs_mediabox(char *file, int *llx, int *lly, int *urx, int *ury);

int
main(int argc, char *argv[])
{
	(void)	argc;
	int	llx, lly, urx, ury;

	appres.ghostscript = GSEXE;
	/* On error, gs_mediabox calls file_msg(), which tries to open a Widget
	   if update_figs is False. Set update_figs to True. */
	update_figs = 1;

	if (gs_mediabox(argv[1], &llx, &lly, &urx, &ury) == -3)
		return 77;

	if (llx == -1 && lly == -1 && urx == 73 && ury == 73)
		return 0;
	else
		return 1;
}
