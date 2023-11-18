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
 * bool.h:  provide bool, as proposed by info autoconf
 * Written by Thomas Loimer, 2016-08-13
 *
 */

/* config.h must be read, before bool.h is included */

#ifndef _BOOL_H
#define _BOOL_H

#if defined HAVE_CONFIG_H && !defined VERSION
#include "config.h"
#endif

/* proposed by info autoconf */
#ifdef HAVE_STDBOOL_H
#include <stdbool.h>
#else
#ifndef HAVE__BOOL
#ifdef __cplusplus
typedef bool	_Bool;
#else
#define	_Bool	signed char
#endif
#endif
#define	bool	_Bool
#define	false	0
#define	true	1
#define __bool_true_false_are_defined	1
#endif
#endif /* _BOOL_H */
