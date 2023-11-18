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
# Makefile.am
# Author: Thomas Loimer, 2016

# The default ARFLAGS are "cru". However, ar now outputs the warning
# "`u' modifier ignored since `D' is the default...".
ARFLAGS = cr
AM_CPPFLAGS = $(XCPPFLAGS) -DNDEBUG -DXFIGLIBDIR="\"$(compkeydbdir)\"" \
	-DOBJLIBDIR="\"$(pkgdatadir)/Libraries\"" -DXFIGDOCDIR="\"$(docdir)\""
AM_LDFLAGS = $(XLDFLAGS)
# LIBOBJS must be placed in LDADD or xfig_LDADD - otherwise, the
# lib-dir is not distributed
# LIBOBJS may contain the replacement functions from AC_REPLACE_FUNCS.
xfig_LDADD = $(LIBOBJS) $(XLIBS)
# xmkmf, in addition, sets the flag -DNEWARROWPROTO

DISTCLEANFILES = splash.xbm splash.xpm version.xbm

bin_PROGRAMS = xfig

xfig_SOURCES = d_arcbox.c d_arcbox.h d_arc.c d_arc.h d_box.c d_box.h \
	d_ellipse.c d_ellipse.h d_line.c d_line.h d_picobj.c d_picobj.h \
	d_regpoly.c d_regpoly.h d_spline.c d_spline.h d_subspline.c \
	d_subspline.h d_text.c d_text.h dirstruct.h e_addpt.c e_addpt.h \
	e_align.c e_align.h e_arrow.c e_arrow.h e_break.c e_break.h e_chop.c \
	e_chop.h e_compound.c e_compound.h e_convert.c e_convert.h e_copy.c \
	e_copy.h e_delete.c e_delete.h e_deletept.c e_deletept.h e_edit.c \
	e_edit.h e_flip.c e_flip.h e_glue.c e_glue.h e_joinsplit.c \
	e_joinsplit.h e_measure.c e_measure.h e_move.c e_move.h e_movept.c \
	e_movept.h e_placelib.c e_placelib.h e_rotate.c e_rotate.h e_scale.c \
	e_scale.h e_tangent.c e_tangent.h e_update.c e_update.h fig.h figx.h \
	f_load.c f_load.h f_neuclrtab.c f_neuclrtab.h f_picobj.c f_picobj.h \
	f_read.c f_readeps.c f_readgif.c f_read.h f_readold.c f_readpcx.c \
	f_readpcx.h f_readppm.c f_readxbm.c f_save.c f_save.h f_util.c \
	f_util.h f_wrpcx.c main.c main.h mode.c mode.h \
	object.c object.h paintop.h resources.c resources.h \
	u_bound.c u_bound.h u_create.c u_create.h u_drag.c u_drag.h u_draw.c \
	u_draw.h u_elastic.c u_elastic.h u_error.c u_error.h u_fonts.c \
	u_fonts.h u_free.c u_free.h u_geom.c u_geom.h u_ghostscript.c u_list.c \
	u_list.h u_markers.c u_markers.h u_pan.c u_pan.h u_print.c u_print.h \
	u_quartic.c u_quartic.h u_redraw.c u_redraw.h u_scale.c u_scale.h \
	u_search.c u_search.h u_smartsearch.c u_smartsearch.h u_translate.c \
	u_translate.h u_undo.c u_undo.h w_browse.c w_browse.h w_canvas.c \
	w_canvas.h w_capture.c w_capture.h w_cmdpanel.c w_cmdpanel.h w_color.c \
	w_color.h w_cursor.c w_cursor.h w_digitize.c w_digitize.h w_dir.c \
	w_dir.h w_drawprim.c w_drawprim.h w_export.c w_export.h w_file.c \
	w_file.h w_fontbits.c w_fontbits.h w_fontpanel.c w_fontpanel.h \
	w_grid.c w_grid.h w_help.c w_help.h w_icons.c w_icons.h w_indpanel.c \
	w_indpanel.h w_intersect.c w_intersect.h w_keyboard.c w_keyboard.h \
	w_layers.c w_layers.h w_library.c w_library.h w_listwidget.c \
	w_listwidget.h w_listwidgetP.h w_modepanel.c w_modepanel.h \
	w_mousefun.c w_mousefun.h w_msgpanel.c w_msgpanel.h w_print.c \
	w_print.h w_rottext.c w_rottext.h w_rulers.c w_rulers.h w_setup.c \
	w_setup.h w_snap.c w_snap.h w_srchrepl.c w_srchrepl.h w_style.c \
	w_style.h w_util.c w_util.h w_zoom.c w_zoom.h splash.xbm version.xbm \
	xfig_math.h

if HAVE_JPEG
xfig_SOURCES += f_readjpg.c
endif

if HAVE_PNG
xfig_SOURCES += f_readpng.c f_wrpng.c
endif

if HAVE_TIFF
xfig_SOURCES += f_readtif.c
endif

if USE_XPM
xfig_SOURCES += f_readxpm.c
endif

if USE_SPLASH
xfig_SOURCES += splash.xpm
endif

if I18N
xfig_SOURCES += w_i18n.c w_i18n.h
endif

if !XAW3D1_5E
xfig_SOURCES += w_menuentry.c w_menuentry.h w_menuentryP.h \
	SmeBSB.h SmeCascade.c SmeCascade.h SmeCascadeP.h \
	SimpleMenu.c SmeBSB.c SmeBSBP.h
endif

EXTRA_DIST = u_draw_spline.c

# Create a convenience library. Unit tests are linked with libxfig.a.
check_LIBRARIES = libxfig.a
libxfig_a_SOURCES = $(xfig_SOURCES)
libxfig_a_LIBADD = $(LIBOBJS)

# These files depend on PACKAGE_VERSION, which is
# defined in config.h ( = $(CONFIG_HEADER))
f_save.$(OBJEXT) main.$(OBJEXT) u_error.$(OBJEXT): $(CONFIG_HEADER)

if USE_SPLASH
w_icons.$(OBJEXT): version.xbm splash.xbm splash.xpm
else
w_icons.$(OBJEXT): version.xbm splash.xbm
endif

MAINTAINERCLEANFILES = Makefile.in

# pgmtopbm might fail and produce an all-white image, see
# https://sourceforge.net/p/mcj/tickets/70
# The -threshold option to pgmtopbm should fix this issue. Nevertheless, check
# and try again (the line with $(FGREP)), using ImageMagick's convert-program.
version.xbm: version.fig.in $(top_srcdir)/version.m4
	-fig2dev -L ppm version.fig | ppmtopgm | pgmtopbm -threshold | pnmcrop \
	| pbmtoxbm | sed '1,3 s/noname_/letters_/; 3 s/char/unsigned &/' >$@
	$(FGREP) -q 0xff $@ || fig2dev -L ppm version.fig | \
		convert ppm:- -trim xbm:- | \
		$(SED) '1,3 s/-_/letters_/; 3 s/char/unsigned &/' >$@

if ENABLE_VERSIONING
# The Makefile generated in $top_srcdir lets configure and config.h.in
# depend on configure.ac and on all .m4-files.
$(top_srcdir)/version.m4: $(top_srcdir)/configure.ac $(top_srcdir)/Makefile.am \
			  $(srcdir)/Makefile.am $(srcdir)/*.c $(srcdir)/*.h
	cd $(top_srcdir) && ./update-version_m4
endif

splash.xpm: $(top_srcdir)/splash-image/spl_bckgnd.fig.in \
		$(top_srcdir)/version.m4
	fig2dev -L xpm ../splash-image/spl_bckgnd.fig \
	| sed '2 {s/static //; s/noname/spl_bckgnd_xpm/}' > $@

splash.xbm: $(top_srcdir)/splash-image/spl_bckgnd.fig.in \
		$(top_srcdir)/version.m4
	fig2dev -L ppm -S 4 ../splash-image/spl_bckgnd.fig \
	| ppmtopgm | pgmtopbm -d8 | pbmtoxbm \
	| sed '1,3 s/noname/spl_bckgnd/; 3 s/char/unsigned &/' > $@
