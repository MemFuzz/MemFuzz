## Run automake on this file to produce Makefile.in

# FIG : Facility for Interactive Generation of figures
# Copyright (c) 1985-1988 by Supoj Sutanthavibul
# Parts Copyright (c) 1989-2015 by Brian V. Smith
# Parts Copyright (c) 1991 by Paul King
# Parts Copyright (c) 2016-2021 by Thomas Loimer
#
# Any party obtaining a copy of these files is granted, free of charge, a
# full and unrestricted irrevocable, world-wide, paid up, royalty-free,
# nonexclusive right and license to deal in this software and documentation
# files (the "Software"), including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense and/or sell copies
# of the Software, and to permit persons who receive copies from any such
# party to do so, with the only requirement being that the above copyright
# and this permission notice remain intact.
#
#
# Makefile.am
# Author: Thomas Loimer, 2016-2021


SUBDIRS = src doc tests

dist_icon_DATA = xfig.png

appdefault_DATA = app-defaults/Fig

dist_applications_DATA = xfig.desktop

dist_compkeydb_DATA = CompKeyDB

EXTRA_DIST = CHANGES FIGAPPS HACKING update-version_m4			\
	app-defaults/Fig.in app-defaults/Fig-color.ad			\
	app-defaults/Fig-color.bisque app-defaults/Fig-color.blue.ad	\
	app-defaults/Fig-color.classic.ad splash-image/bluemarble.png	\
	splash-image/NOTES splash-image/spl_bckgnd.fig.in		\
	splash-image/xfig_splash_logo.png

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in config.h.in~ configure

# a fragment, to test compilation with different configure-flags
compile-check: distdir
	chmod u+w $(distdir)
	mkdir $(distdir)/_build $(distdir)/_build/sub
	cd $(distdir)/_build/sub \
	&& ../../configure --srcdir=../.. --without-xfig-libraries --disable-jpeg \
	&& $(MAKE) -j $(AM_MAKEFLAGS) \
	&& $(MAKE) $(AM_MAKEFLAGS) check \
	&& $(MAKE) $(AM_MAKEFLAGS) clean
	cd $(distdir)/_build/sub \
	../../configure --srcdir=../.. --without-xfig-libraries --disable-xpm --enable-xpm-icon \
	&& $(MAKE) -j $(AM_MAKEFLAGS) \
	&& $(MAKE) $(AM_MAKEFLAGS) check \
	&& $(MAKE) $(AM_MAKEFLAGS) clean

xfig_librariesdir = Libraries

if XFIG_LIBRARIES
EXTRA_DIST += $(xfig_librariesdir)

# do not distribute Maps/USA/assemble and Maps/Canada/assemble
# See info automake, 14.3 The dist Hook, for an example with chmod u+w.
dist-hook:
	test -d "$(distdir)/$(xfig_librariesdir)/Maps" \
	&& cd "$(distdir)/$(xfig_librariesdir)/Maps" && \
		for p in USA Canada; do \
			test -f "$$p/assemble" \
			&& { test -w "$$p" || chmod u+w "$$p"; } \
			&& rm -f "$$p/assemble" || :; \
		done || :

# Libraries might not be distributed - so test, whether the
# source is there, before trying to copy it to the destination.
install-data-hook:
	test -d "$(srcdir)/$(xfig_librariesdir)" && { \
		$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)" \
		&& cp -Rp "$(srcdir)/$(xfig_librariesdir)" "$(DESTDIR)$(pkgdatadir)" \
		&& chmod -R u+rwX "$(DESTDIR)$(pkgdatadir)" || exit 1; } \
		|| :

uninstall-local:
	test -d "$(DESTDIR)$(pkgdatadir)/$(xfig_librariesdir)" \
	&& rm -rf "$(DESTDIR)$(pkgdatadir)/$(xfig_librariesdir)" || :
endif
