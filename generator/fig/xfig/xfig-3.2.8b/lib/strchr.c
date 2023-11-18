/* this is included because index is not on some UNIX systems */
/*
 * 2015-03-05:	Created, cut from getopt.c.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

char *
strchr(char const *s, register int c)
{
#ifdef HAVE_INDEX
	return index(s, c);
#else
	while (*s)
		if (c == *s) return (s);
		else ++s;
	return (NULL);
#endif
}
