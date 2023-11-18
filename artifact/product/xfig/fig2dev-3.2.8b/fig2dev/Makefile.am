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

# fig2dev/Makefile.am
# Author: Thomas Loimer, 2015-2020.


MAINTAINERCLEANFILES = Makefile.in
DISTCLEANFILES = config.vc
CLEANFILES = config.log

SUBDIRS = dev
if ENABLE_I18N
SUBDIRS += i18n
endif
SUBDIRS += tests

EXTRA_DIST = fig2ps2tex.csh config.vc config.vc.in Nmakefile

config.vc: $(srcdir)/config.vc.in $(top_builddir)/config.status
	$(top_builddir)/config.status --file=$@:"$(srcdir)/config.vc.in"

bin_PROGRAMS = fig2dev

fig2dev_SOURCES = alloc.h bool.h bound.h bound.c colors.h colors.c \
    creationdate.h creationdate.c drivers.h fig2dev.h fig2dev.c free.h free.c \
    iso2tex.c localmath.h localmath.c messages.h messages.c object.h read1_3.c \
    read.h read.c trans_spline.h trans_spline.c pi.h lib/getline.h

# CONFIG_HEADER is config.h, which contains PACKAGE_VERSION. If that
# changes, fig2dev should take up the new version string.
# other files also depend on PACKAGE_VERSION, see dev/Makefile.am and transfig
# config.h anyhow depends on all .m4-files
fig2dev.$(OBJEXT): $(CONFIG_HEADER)

## LIBOBJS may contain, e.g., strstr.o, since configure.ac contains
## AC_REPLACE_FUNCS(strstr) -- but usually LIBOBJS will be empty
fig2dev_LDADD = $(LIBOBJS) dev/libdrivers.a

dist_bin_SCRIPTS = fig2ps2tex pic2tpic

uninstall-hook:
	rmdir "$(DESTDIR)$(pkgdatadir)"
