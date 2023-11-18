/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2018 by Thomas Loimer
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
 * test1.c: Try to read RGB_FILE and a file in I18N_DATADIR.
 * Author: Thomas Loimer, 2018-03-08
 *
 * Installation test.
 * Check, whether installation in strange paths, for instance
 * containing a backslash after configure --prefix='/tmp/strange\dir', works.
 * The STRINGIZE(S) is not used any longer, strange paths are not possible.
 * This is of more relevance for installation in, e.g.,
 * C:\Program Files (x86)\fig2dev\i18n.
 * The code below really mocks the code in genps.c and colors.c and
 * therefore must be kept in sync with the code there.
 * Integration tests would be to fragile: I18N_DATADIR depends on the locale
 * to be present.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRINGIZE(S) _STRINGIZE(S)
#define _STRINGIZE(S) #S

int
main(void)
{
	const char mode[] = "rb";
	int err = 0;
	char buf[BUFSIZ];
	char *filepath = buf;
//	char i18ndir[] = STRINGIZE(I18N_DATADIR);
	char i18ndir[] = I18N_DATADIR;
	size_t	n;

#ifdef I18N_DATADIR
	n = strlen(i18ndir);
	if (n + 10 > BUFSIZ) {
		printf("File path too long, %zd > %d.\n", n + 10, BUFSIZ);
		return -2;
	}
	memcpy(filepath, i18ndir, n);
	memcpy(filepath + n, "/cs_CZ.ps", (size_t)10);
	if (fopen(filepath, mode) == NULL) {
		printf("Cannot open file: %s\n", filepath);
		err += 1;
	}
#endif

	return err;
}
