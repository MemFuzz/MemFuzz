/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2007 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2018 by Thomas Loimer
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
 * dirstruct.h
 * Author: Thomas Loimer, 2016
 *
 */

#ifndef DIRSTRUCT

/* See info autoconf, AC_HEADER_DIRENT: All current systems have dirent.h
 * -- but, for ancient systems. See info autoconf AC_HEADER_DIRENT */
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#define DIRSTRUCT struct dirent
#else /* HAVE_DIRENT_H */
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif
#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif
#define DIRSTRUCT struct direct
#endif /* HAVE_DIRENT_H */

#endif
