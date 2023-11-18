/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2019 by Thomas Loimer
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
 *	I got this off net.sources from Henry Spencer.
 *	It is a public domain getopt(3) like in System V.
 *	I have made the following modifications:
 *
 *	index(s,c) was added because too many people could
 *	not compile getopt without it.
 *						(Brian V. Smith)
 *
 * Changes:
 *
 * 2015-03-05 -	Rename optopt to optc to have mips/mipsel link properly
 *		Replace index(s,c) by strchr(s,c).
 *		Create fig2dev/lib/strchr.c.	(Thomas Loimer)
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <string.h>

#define	ARGCH    (int)':'
#define BADCH	 (int)'?'
#define EMSG	 ""
#define	ENDARGS  "--"

/*
 * get option letter from argument vector
 */
/* int	opterr = 1 */		/* useless, never set or used */
int	optind = 1;		/* index into parent argv vector */
char	*optarg;		/* argument associated with option */

#define tell(s)	fputs(*nargv,stderr); fputs(s,stderr); \
		fputc(optc,stderr); fputc('\n',stderr); return BADCH

int
getopt(int nargc, char **nargv, const char *ostr)
{
	static char	*place = EMSG;	/* option letter processing */
	char		*oli;		/* option letter list index */
	int		optc;		/* character checked for validity */

	if(!*place) {			/* update scanning pointer */
		if(optind >= nargc || *(place = nargv[optind]) != '-' ||
				!*++place)
			return(EOF);
		if (*place == '-') {	/* found "--" */
			++optind;
			return(EOF);
		}
	}				/* option letter okay? */
	if ((optc = (int)*place++) == ARGCH || !(oli = strchr(ostr,optc))) {
		if(!*place) ++optind;
		tell(": illegal option -- ");
	}
	if (*++oli != ARGCH) {		/* don't need argument */
		optarg = NULL;
		if (!*place) ++optind;
	}
	else {				/* need an argument */
		if (*place) optarg = place;	/* no white space */
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
			tell(": option requires an argument -- ");
		}
		else optarg = nargv[optind];	/* white space */
		place = EMSG;
		++optind;
	}
	return optc;			/* dump back option letter */
}
