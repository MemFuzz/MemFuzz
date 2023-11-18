## Run automake on this file to produce Makefile.in

# TransFig: Facility for Translating Fig code
# Parts Copyright (c) 2016, 2017 by Thomas Loimer
#
# Any party obtaining a copy of these files is granted, free of charge, a
# full and unrestricted irrevocable, world-wide, paid up, royalty-free,
# nonexclusive right and license to deal in this software and documentation
# files (the "Software"), including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense and/or sell copies
# of the Software, and to permit persons who receive copies from any such
# party to do so, with the only requirement being that the above copyright
# and this permission notice remain intact.

# transfig/Makefile.am
# Author: Thomas Loimer, 2016, 2017.


MAINTAINERCLEANFILES = Makefile.in

# Additional libs are not needed for transfig (hopefully).
# Brute force, but otherwise -L/path/to/libs must also be provided.
LIBS =

# Silence some warnings
AM_CFLAGS = -Wno-parentheses

bin_PROGRAMS = transfig

transfig_SOURCES = transfig.c transfig.h txfile.c mkfile.c sys.c

transfig.$(OBJEXT): $(CONFIG_HEADER)

# transfig documentation is not installed, but only distributed
# with the source tarball
EXTRA_DIST = doc
