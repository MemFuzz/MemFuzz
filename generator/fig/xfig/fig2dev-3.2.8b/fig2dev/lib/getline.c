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
 * Author: Thomas Loimer, 2020
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_SYS_TYPES_H		/* ssize_t; MacOS 10.6 does not include  */
#include <sys/types.h>		/* sys/types.h, if stdio.h is included.  */
#endif

ssize_t
getline(char **restrict line, size_t *restrict n, FILE *restrict fp)
{
	char	*new;
	int	c;
	ssize_t	i = 0;

	/*
	 * The standard is not specific about *line != NULL and *n == 0.
	 * The GNU implementation of getline() allocates, regardless.
	 */
	if (*n == 0) {
		*n = 256;
		if ((*line = malloc(*n)) == NULL) {
			*n = 0;
			return -1;
		}
	}

	new = *line;

	while (new) {
		for (; i < *n - 1; ++i) {
			c = fgetc(fp);
			if (c == '\n') {
				(*line)[i] = c;
				(*line)[++i] = '\0';
				return i;
			} else if (c == EOF) {
				if (i == 0) {
					return -1;
				} else {
					(*line)[i] = '\0';
					return i;
				}
			}
			(*line)[i] = c;
		}

		/* i == *n - 1; */
		c = fgetc(fp);
		if (c == EOF) {
			(*line)[i] = '\0';
			return i;
		} else {
			(*line)[i++] = c;
		}

		new = realloc(*line, *n *= 2);
		if (new == NULL)
			return -1;
		else
			*line = new;
	}
	(*line)[i] = '\0';
	return -1;
}
