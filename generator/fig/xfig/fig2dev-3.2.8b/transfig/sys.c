/*
 * TransFig: Facility for Translating Fig code
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>	/* link() */
#endif
#include "transfig.h"

#define MAXSYS 10000
static char sysbuf[MAXSYS];

char *
sysls(void)
{
  FILE *ls;
  int i;
  int c;

  ls = popen("/bin/ls *.fig", "r");
  i = 0;
  c = fgetc(ls);
  while (c != EOF & i < MAXSYS-1)
  {
	sysbuf[i] = (char) c;
	i += 1;
	c = fgetc(ls);
  }
  pclose(ls);
  sysbuf[i] = '\0';
  return sysbuf;
}


void
sysmv(char *file)
{
  sprintf(sysbuf, "%s~", file);
  unlink(sysbuf);
  if (!link(file, sysbuf)) {
	fprintf(stderr, "Renaming %s to %s~\n", file, file);
	unlink(file);
  }
}

char *
strip(char *str, char *suf)
{
  char *p1, *p2;

  for (p1 = &str[strlen(str)-1], p2 = &suf[strlen(suf)-1];
	(p1 >= str && p2 >= suf) && (*p1 == *p2);
	--p1, --p2);

  if (p2 < suf)
  {
	*(p1+1) = '\0';
	return str;
  } else
	return NULL;
}

char *
mksuff(char *name, char *suff)
{
  char *temp;

  temp = (char *)malloc(strlen(name)+strlen(suff)+1);
  strcpy(temp, name);
  strcat(temp, suff);
  return temp;
}
