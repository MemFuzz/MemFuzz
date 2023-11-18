/*
 * isascii.c: Provide an isascii() function.
 * Copyright (c) 2015 by Thomas Loimer
 *
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This file is offered as-is,
 * without any warranty.
 *
 */

int
isascii(int c)
{
	return ((c & ~0x7f) == 0);
}
