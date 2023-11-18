/*
 * TransFig: Facility for Translating Fig code
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2002 by Brian V. Smith
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and
 * documentation files (the "Software"), including without limitation the
 * rights to use, copy, modify, merge, publish and/or distribute copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that this copyright
 * notice remain intact.
 *
 */

/*
 * strdup.c
 * Copied and modified by T. Loimer, 2015.
 * Copied from Phil, a portability library for Unices, see
 * http://phil.sourceforge.net
 * The phil license follows:
 */

/*********************************************************************
 *
 * Copyright (C) 1999  Gene Michael Stover
 *
 * This library is free software; you can redistribute it
 * and/or modify it under the terms of version 2.1 of the GNU
 * Lesser General Public License as published by the Free
 * Software Foundation.
 *
 * This library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 */

/*
 * By gene m. stover
 * Wednesday, 2 December 1998
 */

#include <stdlib.h>
#include <string.h>

char *
strdup(char const *str)
{
	char	*p;

	if (!str)
		return (char *)NULL;

	p = (char *) malloc(strlen(str) + 1);
	if (p != NULL) {
		strcpy(p, str);
	}
	return p;
}
