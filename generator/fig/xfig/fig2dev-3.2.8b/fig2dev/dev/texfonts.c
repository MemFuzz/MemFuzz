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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "object.h"
#include "texfonts.h"

#ifdef NFSS
const char	*texfontfamily[] = {
	"\\familydefault",	/* default */
	"\\rmdefault",		/* roman */
	"\\rmdefault",		/* bold */
	"\\rmdefault",		/* italic */
	"\\sfdefault",		/* sans serif */
	"\\ttdefault"		/* typewriter */
};

const char	*texfontseries[] = {
	"\\mddefault",		/* default */
	"\\mddefault",		/* roman */
	"\\bfdefault",		/* bold */
	"\\mddefault",		/* italic */
	"\\mddefault",		/* sans serif */
	"\\mddefault"		/* typewriter */
};

const char	*texfontshape[] = {
	"\\updefault",		/* default */
	"\\updefault",		/* roman */
	"\\updefault",		/* bold */
	"\\itdefault",		/* italic */
	"\\updefault",		/* sans serif */
	"\\updefault"		/* typewriter */
};
#endif

const char	*texfontnames[] = {
	"rm",			/* default */
	"rm",			/* roman */
	"bf",			/* bold */
	"it",			/* italic */
	"sf",			/* sans serif */
	"tt"			/* typewriter */
};

/* The selection of font names may be site dependent.
 * Not all fonts are preloaded at all sizes.
 */

char	texfontsizes[] = {
	11,			/* default */
	5, 5, 5, 5,		/* 1-4: small fonts */
	5,			/* five point font */
	6, 7, 8,		/* etc */
	9, 10, 11,
	12, 12, 14,
	14, 14, 17,
	17, 17, 20,
	20, 20, 20, 20, 25,
	25, 25, 25, 29,
	29, 29, 29, 29,
	34, 34, 34, 34,
	34, 34, 34, 41,
	41, 41
};
