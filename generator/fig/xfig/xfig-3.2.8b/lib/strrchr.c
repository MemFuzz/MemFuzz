/*
 * 2015-03-05:	Created, adapted from strchr.c.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

char *
strrchr(char const *s, int c)
{
#ifdef HAVE_RINDEX
	return rindex(s, c);
#else
	char	*val = NULL;
	while (*s++)
		if (c == *s) val = s;
	return (val);
#endif
}
