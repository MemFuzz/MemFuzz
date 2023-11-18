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
# doc/Makefile.am
# Author: Thomas Loimer, 2016, 2021

dist_doc_DATA = FORMAT1.3 FORMAT1.4 FORMAT2.0 FORMAT2.1 FORMAT3.0 \
	FORMAT3.1 FORMAT3.2 xfig-howto.pdf

doc_DATA = xfig_man.html xfig_ref_en.pdf

man1_MANS = xfig.man

EXTRA_DIST  = html MAKEPS

CLEANFILES = html/images/xfig-title.fig

MAINTAINERCLEANFILES = Makefile.in

# Below, $< is not fully portable, see info autoconf "Portable Make",
# use $? instead. man is sensitive to spaces after the options.
# Probably, groff -Thtml -mman xfig.man > $@ is more portable?

# Some files are not created when running make, but are created by the
# maintainer at distribution time, when running make dist. Also, these files are
# placed into the distribution tarball, not into the source tree.
#
# However, the concept of discriminating between distribution tarball and
# source tree does not hold very well. Nowadays, sources are also retrieved
# via the publicly accessible git source tree, not only by the point releases.
#
# Therefore, for these files, provide rules to build them _in the source tree_,
# not in the build tree. Also, make sure that they are put into the distribution
# tarball. However, the rules to build them must be explicitly called by the
# user. For convenience, a target is defined that creates all of these files,
# make documentation.
#
# The reason for distributing these files, instead of providing make rules for
# all users, is that the creation of these files demands further dependencies.
# In addition, the documentation is probably not changed by users, hence the
# version information as provided by the maintainer should remain with
# the documentation.

# %-style patterns are a gnu make extension. Do not use.

# Create the logo, xfig-title.png, which is included at the top of each html
# page and which shows the version string.
$(srcdir)/html/images/xfig-title.png $(distdir)/html/images/xfig-title.png: \
		$(srcdir)/html/images/xfig-title.fig.in $(top_srcdir)/version.m4
	test -r html/images/xfig-title.fig ||				\
			$(MAKE) -C .. doc/html/images/xfig-title.fig
	fig2dev -L png -S4 html/images/xfig-title.fig "$@"

$(srcdir)/xfig_ref_en.pdf: $(srcdir)/html/images/xfig-title.png
	cd $(srcdir)/html && htmldoc -f ../xfig_ref_en.pdf	\
		--no-title --webpage --header ..c -t pdf14 --size a4	\
		contents.html $$($(FGREP) '<a href=' contents.html |	\
				$(SED) 's/.*a href="//;s/["#].*//;' |	\
				uniq | $(FGREP) -v japanese)

# copy-paste from above (sigh)
$(distdir)/xfig_ref_en.pdf: $(distdir)/html/images/xfig-title.png
	cd $(distdir)/html && htmldoc -f ../xfig_ref_en.pdf	\
		--no-title --webpage --header ..c -t pdf14 --size a4	\
		contents.html $$($(FGREP) '<a href=' contents.html |	\
				$(SED) 's/.*a href="//;s/["#].*//;' |	\
				uniq | $(FGREP) -v japanese)

# This file remains in the src tree and is updated if necessary.
$(srcdir)/xfig_man.html.in $(distdir)/xfig_man.html.in: $(srcdir)/xfig.man.in
	man -Thtml -l "$(srcdir)/xfig.man.in" >"$@"

.PHONY: documentation

documentation: $(srcdir)/html/images/xfig-title.png $(srcdir)/xfig_ref_en.pdf

dist-hook:
	chmod u+w "$(distdir)" "$(distdir)/html" "$(distdir)/html/images"
	-chmod u+w "$(distdir)/xfig_man.html.in"			\
		"$(distdir)/html/images/xfig-title.png"
	$(MAKE) $(distdir)/html/images/xfig-title.png
	$(MAKE) $(distdir)/xfig_ref_en.pdf
	$(MAKE) $(distdir)/xfig_man.html.in

install-data-hook:
	cp -Rp "$(srcdir)/html" "$(DESTDIR)$(htmldir)"		\
		&& chmod -R u+rwX "$(DESTDIR)$(htmldir)"
	cd "$(DESTDIR)$(htmldir)/html"				\
		&& rm -f ja_JP.ujis && $(LN_S) japanese ja_JP.ujis
	cd "$(DESTDIR)$(htmldir)/html/images"			\
		&& rm -f xfig-title.fig xfig-title.fig.in

uninstall-local:
	rm -rf "$(DESTDIR)$(htmldir)/html"
