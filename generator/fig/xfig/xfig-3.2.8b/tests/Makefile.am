## Run automake on this file to produce Makefile.in

# FIG : Facility for Interactive Generation of figures
# Copyright (c) 1985-1988 by Supoj Sutanthavibul
# Parts Copyright (c) 1989-2015 by Brian V. Smith
# Parts Copyright (c) 1991 by Paul King
# Parts Copyright (c) 2016-2020 by Thomas Loimer
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
# tests/Makefile.am
# Author: Thomas Loimer, 2016

# testsuite and package.m4 must be distributed, hence they are
# written into the source tree
TESTSUITE = $(srcdir)/testsuite
# list here all files contributing to testsuite.at
TESTSUITE_AT = testsuite.at
EXTRA_DIST = interactive testsuite package.m4 $(TESTSUITE_AT) atlocal.in data

DISTCLEANFILES = atconfig
MAINTAINERCLEANFILES = Makefile.in $(TESTSUITE) $(srcdir)/package.m4

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:;{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [@PACKAGE_NAME@])'; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [@PACKAGE_TARNAME@])'; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [@PACKAGE_VERSION@])'; \
	  echo 'm4_define([AT_PACKAGE_STRING], [@PACKAGE_STRING@])'; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	  echo 'm4_define([AT_PACKAGE_URL], [@PACKAGE_URL@])'; \
	} >'$(srcdir)/package.m4'

AM_CPPFLAGS = -I$(top_srcdir)/src $(XCPPFLAGS)

if ALLOW_MULTIPLE_DEFINITION
AM_LDFLAGS = -Wl,--allow-multiple-definition $(XLDFLAGS)
LDADD = $(top_builddir)/src/libxfig.a $(XLIBS)

check_PROGRAMS = test1 test2 test3

$(top_builddir)/src/libxfig.a:
	cd $(top_builddir)/src && $(MAKE) $(AM_MAKEFLAGS) libxfig.a
endif

check-local: atconfig $(TESTSUITE) atlocal
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig $(TESTSUITE) atlocal
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOTEST = $(AUTOM4TE) --language=autotest

$(TESTSUITE): $(srcdir)/package.m4 $(TESTSUITE_AT)
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@
