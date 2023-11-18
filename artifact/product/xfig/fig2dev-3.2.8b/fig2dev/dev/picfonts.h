/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2019 by Thomas Loimer
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

#ifndef PICFONTS_H
#define PICFONTS_H

/*  The selection of font names may be site dependent */

char		*picfontnames[] = {
			"R", "R",		/* default */
			"R",			/* roman */
			"B",			/* bold */
			"I",			/* italic */
			"H",			/* sans serif */
			"C"			/* typewriter */
		};

#define MAXFONTSIZE 108

#define PICFONT(F)	(picfontnames[((F) <= MAX_FONT) ? (F)+1 : MAX_FONT])
#define PICFONTSIZE(S)  ((S) > 0 ? \
				((S) <= MAXFONTSIZE ? (int)round(S) : \
					MAXFONTSIZE) : (int)font_size)
#define PICFONTMAG(T)	\
		PICFONTSIZE((int)(T->size*(rigid_text(T) ? 1.0 : fontmag)))

#endif /* PICFONTS_H */
