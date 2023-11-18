/*
 * strrchr.c: Provide a strrchr() function.
 * Copyright (c) 2015, 2018 by Thomas Loimer
 *
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This file is offered as-is,
 * without any warranty.
 *
 */

/*
 * Modified from strchr.c.
 */

#include <stddef.h>

char *
strrchr(const char *s, int c)
{
	char	*val = (char *)NULL;
	while (*s++)
		if (c == *s) val = (char *)s;
	return (val);
}
