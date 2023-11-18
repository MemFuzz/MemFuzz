/*
 * strchr.c: Provide a strchr() function.
 * Copyright (c) 2015, 2018 by Thomas Loimer
 *
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This file is offered as-is,
 * without any warranty.
 *
 */

/*
 * Copied from getopt.c.
 */

#include <stddef.h>

char *
strchr(const char *s, int c)
{
	while (*s)
		if (c == *s) return ((char *)s);
		else ++s;
	return ((char *)NULL);
}
