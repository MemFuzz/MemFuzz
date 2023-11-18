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
 * test2.c: Check, whether read_pdf() finds the bounding box of a pdf file.
 * Author: Thomas Loimer, 2019-12-14
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bool.h"
#include "object.h"
#include "readpics.h"

/* the function to be tested, in $(top_srcdir)/fig2dev/dev/readeps.c */
extern int	read_pdf(F_pic *pic, struct xfig_stream *restrict pic_stream,
			int *llx, int *lly);

/* symbols that are needed when calling read_pdf() */
int		urx = 0;
int		ury = 0;
int		metric = 0;
FILE		*tfp;
const struct _paperdef		/* from fig2dev.h */
{
	char	*name;
	int	width;
	int	height;
}	paperdef[1] = {{"letter", 8, 12}};


int
main(int argc, char *argv[])
{
	(void)	argc;
	int	llx = -1;
	int	lly = -1;
	FILE	*file;
	struct xfig_stream	f;
	F_pic	pic;

	tfp = stdout;
	pic.file = argv[1];

	init_stream(&f);
	file = open_stream(argv[1], &f);
	if (file == NULL) {
		fprintf(stderr, "Test file %s not found.\n", argv[1]);
		close_stream(&f);
		free_stream(&f);
		exit(EXIT_FAILURE);
	}

	if (read_pdf(&pic, &f, &llx, &lly) == 1 &&
			pic.bit_size.x != 10 && pic.bit_size.y != 10) {
		fprintf(stdout, "read_pdf found: width = %d, height = %d\n",
				pic.bit_size.x, pic.bit_size.y);
		close_stream(&f);
		free_stream(&f);
		exit(EXIT_SUCCESS);
	} else {
		close_stream(&f);
		free_stream(&f);
		exit(EXIT_FAILURE);
	}
}
