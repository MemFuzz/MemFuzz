/*
 * strstr.c: Provide a strstr() function.
 * Copyright (c) 2015 by Thomas Loimer
 *
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This file is offered as-is,
 * without any warranty.
 *
 */


#include <string.h>

/*
 * Find the first occurrence of s2 in s1.
 */

char *strstr(const char *s1, const char *s2)
{
	size_t		len2;
	const char	*stmp;

	len2 = strlen(s2);
	for (stmp = s1; *stmp != '\0'; ++stmp)
		if (strncmp(stmp, s2, len2) == 0)
			return (char *)stmp;
	return (char *)NULL;
}
