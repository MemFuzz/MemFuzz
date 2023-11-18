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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_STRERROR
#include <errno.h>
#endif
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


char	Err_badarg[] = "Argument -%c unknown to %s driver.";
char	Err_mem[] = "Running out of memory.";

/*
 * err_msg() is basically a wrapper around
 *   sprintf(msg, fmt, ...);
 *   perror(msg);
 */
void
err_msg(char *fmt, ...)
{
	va_list	argptr;
#ifdef HAVE_STRERROR
	int	err = errno;

	va_start(argptr, fmt);
	if (fmt == NULL) {
		perror(NULL);
	} else {
		vfprintf(stderr, fmt, argptr);
		fprintf(stderr, ": %s\n", strerror(err));
	}
	va_end(argptr);
#else
	if (fmt) {
		va_start(argptr, fmt);
		vfprintf(stderr, fmt, argptr);
		va_end(argptr);
		fputs(".\n", stderr);
	}
#endif
}

void
put_msg(char *fmt, ...)
{
	va_list argptr;
	va_start(argptr, fmt);
	vfprintf(stderr, fmt, argptr);
	va_end(argptr);
	fputc('\n', stderr);
}
