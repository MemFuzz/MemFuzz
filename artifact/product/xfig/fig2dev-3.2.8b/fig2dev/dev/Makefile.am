## Run automake on this file to produce Makefile.in

# Fig2dev: Translate Fig code to various Devices
# Copyright (c) 1991 by Micah Beck
# Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
# Parts Copyright (c) 1989-2015 by Brian V. Smith
# Parts Copyright (c) 2015-2020 by Thomas Loimer
#
# Any party obtaining a copy of these files is granted, free of charge, a
# full and unrestricted irrevocable, world-wide, paid up, royalty-free,
# nonexclusive right and license to deal in this software and documentation
# files (the "Software"), including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense and/or sell copies
# of the Software, and to permit persons who receive copies from any such
# party to do so, with the only requirement being that the above copyright
# and this permission notice remain intact.

# fig2dev/dev/Makefile.am
# Author: Thomas Loimer, 2015-2018.


MAINTAINERCLEANFILES = Makefile.in

## build a convenience library

## The default ar-flags are "cru", c .. create, r .. replace a member if found,
## u .. update, only replace a member if the object is newer
## Instead, use "cq", q .. quick, just append at the end
ARFLAGS = cq

## Use AM_PROG_AR and AC_PROG_RANLIB in configure.ac

noinst_LIBRARIES = libdrivers.a

## directory-wide CPPFLAGS;  -I../.. is set anyways
## if CPPFLAGS are set individually, like
##   libdrivers_a_CPPFLAGS = -I..
## objects like libdrivers_a-as85ec.o etc. are created
# i18ndir is defined and AC_SUBST'd in configure.ac
AM_CPPFLAGS = -I"$(top_srcdir)/fig2dev"
if ENABLE_I18N
AM_CPPFLAGS += -DI18N_DATADIR="\"$(i18ndir)\""
endif
## libraries do not need LDFLAGS - they need not be linked
## libdrivers_a_LIBADD is appended to the link-command

libdrivers_a_SOURCES = encode.c encode.h genbitmaps.c genbox.c gencgm.c \
    gendxf.c genemf.h genemf.c genepic.c gengbx.c genge.c genibmgl.c genlatex.h\
    genlatex.c genmap.c genmf.c genmp.c genpdf.c genpic.c genpict2e.c \
    genpictex.c genps.h genps.c genpstex.c genpstricks.c genptk.c genshape.c \
    gensvg.c gentextyl.c gentikz.h gentikz.c gentk.c gentpic.c picfonts.h \
    picpsfonts.h psfonts.h psfonts.c \
    psprolog.h readeps.c readgif.c readjpg.c readpcx.c readpics.h readpics.c \
    readppm.c readtif.c readxbm.c readxpm.c texfonts.h texfonts.c setfigfont.h \
    setfigfont.c tkpattern.h tkpattern.c xtmpfile.h xtmpfile.c

# These contain PACKAGE_VERSION, hence depend on $(CONFIG_HEADER) = config.h.
encode.h genps.$(OBJEXT) gensvg.$(OBJEXT) genemf.$(OBJEXT) gengbx.$(OBJEXT) \
genmp.$(OBJEXT) genpictex.$(OBJEXT) gentk.$(OBJEXT) readjpg.$(OBJEXT) \
readpics.$(OBJEXT): $(CONFIG_HEADER)

if WITH_PNG
libdrivers_a_SOURCES += readpng.c
endif
