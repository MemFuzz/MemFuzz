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
 * xtmpfile.c: create a temporary file
 * Author: Thomas Loimer, 2017, 2020
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>	/* mkstemp(), rand(), getenv() */
#include <string.h>	/* strcpy(), strlen() */
#include <unistd.h>

#if ! defined(HAVE_MKSTEMP) || ! defined(HAVE_FDOPEN)
#include <time.h>
#include <limits.h>
#include "bool.h"
#endif

#include "messages.h"
#include "xtmpfile.h"


/*
 * Create and open an unique temporary file from *pattern. Return a file stream
 * open for reading and writing and return the path name in *pattern. If the
 * size of the string buffer pointed to by *pattern is not large enough,
 * malloc() and return a large enough buffer. *pattern must end with "XXXXXX".
 * Return NULL on error.
 * Usage:
 *   char    pattern_buf[128];
 *   char   *pattern = pattern_buf;
 *   FILE   *f:
 *   f = xtmpfile(&pattern, sizeof pattern_buf);
 *   ..
 *   if (pattern != pattern_buf)
 *       free(pattern);
 */
FILE *
xtmpfile(char **pattern, size_t len)
{
	const char	mode[] = "wb+";
	int		i;
	size_t		t;
	char		*p;
#if ! defined(HAVE_MKSTEMP) || ! defined(HAVE_FDOPEN)
	FILE		*f = NULL;
	static bool	seeded = false;
#endif


	/* find the temporary directory */
#ifdef P_tmpdir
	if (((p = getenv("XFIGTMPDIR")) && !access(p, W_OK | X_OK)) ||
			((p = getenv("TMPDIR")) && !access(p, W_OK | X_OK)) ||
			((p = P_tmpdir) && !access(p, W_OK | X_OK)))
		t = strlen(p);
	else
		p = NULL;
#else
	/*
	 * The GetTempPath function in Visual Studio uses the first path found
	 * in TMP, TEMP, USERPROFILE, then the Windows folder, see
	 * https://msdn.microsoft.com/en-us/library/aa364992(VS.85).aspx
	 * (retrieved 2018-03-04).
	 */
	if ((p = getenv("XFIGTMPDIR")) && !access(p, W_OK | X_OK) ||
			(p = getenv("TMP")) && !access(p, W_OK | X_OK) ||
			(p = getenv("TEMP")) && !access(p, W_OK | X_OK))
		t = strlen(p);
	else
		p = NULL;
#endif

	/* prepend the temporary directory */
	if (p) {
		char	str_buf[256];
		char	*str = str_buf;
		size_t	n;

		/* save pattern to str */
		n = strlen(*pattern);
		if (sizeof str_buf <= n && (str = malloc(n + 1)) == NULL) {
			put_msg(Err_mem);
			return NULL;
		}
		strcpy(str, *pattern);

		t += n + 1;

		if (len <= t && (*pattern = malloc(t + 1)) == NULL) {
			put_msg(Err_mem);
			if (str != str_buf)
				free(str);
			return NULL;
		}
		sprintf(*pattern, "%s/%s", p, str);
		if (str != str_buf)
			free(str);
	}

	/* Create and open a file that does not yet exist. */
#if defined(HAVE_MKSTEMP) && defined(HAVE_FDOPEN)
	if ((i = mkstemp(*pattern)) == -1)
		return NULL;
	return fdopen(i, mode);
#else
	/* check input pattern */
	t = strlen(*pattern);
	if (t <  7 || memcmp(p = *pattern + t - 6, "XXXXXX", 6))
		return NULL;

	/* write a random sequence to the six XXXXXX */
	if (!seeded) {
		srand((unsigned int)time(NULL));
		seeded = true;
	}
	/* check if such random file name, by incidence, already exists */
	for (i = 1; f == NULL && i < 9; ++i) {
		sprintf(p, "%.6x", (unsigned)(rand() & 0xffffff));
		if ((f = fopen(*pattern, "rb")) == NULL) {
			f = fopen(*pattern, mode);
		} else {
			fclose(f);
			f = NULL;
		}
	}
	return f;
#endif
}
