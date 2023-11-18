#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#

AC_COPYRIGHT([FIG : Facility for Interactive Generation of figures
Copyright (c) 1985-1988 by Supoj Sutanthavibul
Parts Copyright (c) 1989-2015 by Brian V. Smith
Parts Copyright (c) 1991 by Paul King
Parts Copyright (c) 2016-2021 by Thomas Loimer

Any party obtaining a copy of these files is granted, free of charge, a
full and unrestricted irrevocable, world-wide, paid up, royalty-free,
nonexclusive right and license to deal in this software and documentation
files (the "Software"), including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense and/or sell copies
of the Software, and to permit persons who receive copies from any such
party to do so, with the only requirement being that the above copyright
and this permission notice remain intact.
])

# configure.ac
# Author: Thomas Loimer, 2016-2021

dnl The minimum autoconf version to process this file. In version 2.60,
dnl the directory variables changed, see info autoconf, section 4.8.3.
AC_PREREQ([2.60])

dnl Define XFIG_VERSION and RELEASEDATE in version.m4
m4_include([version.m4])

# Initialize
AC_INIT([xfig], [XFIG_VERSION], [thomas.loimer@tuwien.ac.at],
	[], [https://sourceforge.net/projects/mcj/])

# Define variables that are written into config.h.
dnl Need to double-quote (shell-)vars identical to m4-variables.
AC_DEFINE([PROTOCOL_VERSION], ["3.2"],
	[Define the fig file format. Identical to major.minor \
		substring of xfig version.])
AC_SUBST([RELEASE_DATE], ["RELEASEDATE"])dnl

dnl No success with "AC_SUBST(RELEASEYEAR, m4_shift(m4_split(RELEASEDATE)))".
m4_define([RELEASEYEAR], m4_split(RELEASEDATE))
AC_SUBST([RELEASE_YEAR], m4_shift(RELEASEYEAR))
AC_DEFINE_UNQUOTED([RELEASE_YEAR], ["$RELEASE_YEAR"],
	[Define the year of the release.])

# Set automake options.
dnl The options are written to AUTOMAKE_OPTIONS. A minimum version
dnl of automake, e.g., 1.6.1, can also be put into AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE([-Wall foreign dist-xz no-dist-gzip subdir-objects])
dnl  -Wall.....enable all (automake) warnings
dnl  -Werror...and report them as error
dnl  foreign...do no require the files ChangeLog COPYING AUTHORS NEWS
dnl		README INSTALL
dnl  subdir-objects...place objects into the dir where the corresponding
dnl		source file resides, not into the current build directory;
dnl		necessary to use LIBOBJS from /lib in /src

AC_CONFIG_MACRO_DIR([m4])

# Check whether ./configure resides in the correct directory.
AC_CONFIG_SRCDIR([src/main.c])

# Write the variables determined by ./configure into config.h.
# Therefore, make sure to #include "config.h" in each source file.
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CC
AC_C_INLINE
AC_PROG_FGREP
AC_PROG_LN_S
# Sets MKDIR_P - which is, however, set anyhow
AC_PROG_MKDIR_P
# ranlib and ar are needed to create the convenience library libxfig.a.
# Unit tests are linked to libxfig.a.
AC_PROG_RANLIB
AC_PROG_SED
AM_PROG_AR

# Search for pkg-config and set PKG_CONFIG to the path found, else empty.
# PKG_PROG_PKG_CONFIG
# On debian, pkg-config does not find xaw3d. On archlinux, pkg-config
# --libs xaw3d yields -lXaw3d -lXmu -lXt -lX11 -- but -lXmu is not
# strictly necessary. Use hard-coded paths instead of pkg-config.

dnl Not useful for packagers.
dnl AC_CHECK_PROG(XDG_ICON, [xdg-icon-resource], [xdg-icon-resource])
dnl AC_CHECK_PROG(XDG_MENU, [xdg-desktop-menu], [xdg-desktop-menu])


# Checks for libraries.
AC_SEARCH_LIBS([pow], [m])dnl
dnl AC_SEARCH_LIBS([deflate], [z])  # libz is not needed.


# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS_ONCE([sys/time.h])

# Get X header and library location.
# Simply add libraries to LIBS, x_includes to XCPPFLAGS
# and x_libraries to XLDFLAGS.
AC_SUBST([XLIBS])
AC_SUBST([XCPPFLAGS])
AC_SUBST([XLDFLAGS])
AC_PATH_X
AS_IF([test "x$no_x" != xyes],
    [AS_IF([test -n "$x_includes"],
	[XCPPFLAGS="-I$x_includes $XCPPFLAGS"])
     AS_IF([test -n "$x_libraries"],
	[XLDFLAGS="$XLDFLAGS -L$x_libraries"])])
# (1) Add "-lXt -lX11" to LIBS.
# The check below did not work on Darwin (quote in AC_PATH_X: Do not try a
# hair to link a X-program), therefore, use hard-coded XLIBS
# Further below, though, linking with -lXpm or -lXaw works.
XLIBS="-lXt -lX11"
# (2) Do not give up, check in unusual places.
#AC_SEARCH_LIBS([XBell], [X11])
#AC_SEARCH_LIBS([XtName], [Xt])
AC_CHECK_HEADER([X11/X.h])


# Check for libraries and header files
dnl First search for the header, only then search for the libs. The other way
dnl round, the found library would be prepended to LIBS, unnecessarily.
AC_CHECK_HEADER([jpeglib.h],
    [AC_SEARCH_LIBS([jpeg_read_header], [jpeg],
	[AC_DEFINE([HAVE_JPEG], 1,
	    [Define to 1 if you have the jpeg library and header files.])])],
    [], [AC_INCLUDES_DEFAULT])
AM_CONDITIONAL([HAVE_JPEG], [test $ac_cv_header_jpeglib_h = yes && \
	test "x$ac_cv_search_jpeg_read_header" != xno])dnl

AC_CHECK_HEADER([png.h],
    [AC_SEARCH_LIBS([png_read_info], [png],
	[AC_DEFINE([HAVE_PNG], 1,
	    [Define to 1 if you have the png library and header files.])])],
    [], [AC_INCLUDES_DEFAULT])
AM_CONDITIONAL([HAVE_PNG], [test $ac_cv_header_png_h = yes && \
	test "x$ac_cv_search_png_read_info" != xno])dnl

AC_CHECK_HEADER([tiffio.h],
    [AC_SEARCH_LIBS([TIFFOpen], [tiff],
	[AC_DEFINE([HAVE_TIFF], 1,
	    [Define to 1 if you have the tiff library and header files.])])],
    [], [AC_INCLUDES_DEFAULT])
AM_CONDITIONAL([HAVE_TIFF], [test $ac_cv_header_tiffio_h = yes && \
	test "x$ac_cv_search_TIFFOpen" != xno])dnl

# First check for jpeg, png and tiff-libraries, only then for ghostscript.
# One report indicated that, on Darwin, the other way round "-ljpeg -lpng
# -ltiff" was not added for the linker stage. See
# https://sourceforge.net/p/mcj/discussion/general/thread/36ff8854e8/
AC_CHECK_HEADER([ghostscript/iapi.h],
    [AC_SEARCH_LIBS([gsapi_revision], [gs],
	[AC_DEFINE([HAVE_GSLIB], 1,
	    [Define to 1 if you have the ghostscript library and header files.])])],
    [], [AC_INCLUDES_DEFAULT])
AS_IF([test $ac_cv_header_ghostscript_iapi_h = yes && \
	test "x$ac_cv_search_gsapi_revision" != xno],
    [gsman="This version of xfig links into the ghostscript library.
The ghostscript executable is not needed, it is only called as a fallback-solution."],
    [gsman="This is needed when importing PDF or Encapsulated
PostScript files. To disable calling ghostscript, set to the empty string,
.BR \"\-ghostscript \"\"\"\"\" ."])dnl
AC_SUBST([gsman])
AM_SUBST_NOTMAKE([gsman])


# Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN
AC_C_INLINE
AC_C_RESTRICT
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_CHECK_DECLS([S_IFDIR, S_IWRITE],[],[],[[#include <sys/stat.h>]])dnl
AC_CHECK_DECL([REG_NOERROR],[],
	[AC_DEFINE([REG_NOERROR], 0,dnl
		[Define to 0 if not provided by regex.h.])],dnl
	[[#include <regex.h>]])
# The option --allow-multiple-definition is aquivalent to -z muldefs.
# The latter would not error out, e.g., "-z NoTeXisting" does only
# produce a warning, not an error, on gnu ld.
# KEEP IN SYNC with the actual link flags in tests/Makefile.am!
AX_CHECK_LINK_FLAG([-Wl,--allow-multiple-definition])dnl
AM_CONDITIONAL([ALLOW_MULTIPLE_DEFINITION],
	[test "x$ax_cv_check_ldflags___Wl___allow_multiple_definition" = xyes])dnl

# Checks for library functions.
AC_FUNC_FORK
dnl AC_FUNC_STRTOD
# The setlocale seems to be broken, grep HAVE_SETLOCALE, setlocale
AC_CHECK_FUNCS_ONCE([getcwd setlocale strerror])
AC_REPLACE_FUNCS([isascii strstr strchr strrchr strcasecmp strncasecmp \
	strdup strndup])

AC_CONFIG_LIBOBJ_DIR([lib])

# Query user options
AC_ARG_ENABLE(versioning, [AS_HELP_STRING([--enable-versioning],
	[enable changing the version number, only useful for \
	 hacking (default: disable)])],
    [],[enableval=no])dnl
AM_CONDITIONAL([ENABLE_VERSIONING], [test "x$enableval" = xyes])dnl

AC_ARG_ENABLE(arrows4to14, [AS_HELP_STRING([--disable-arrows4to14],
	[disable arrow types 4 to 14 (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],
    [AC_DEFINE([ARROWS4TO14], 1,
	 [Define to use arrow types 4 to 14 (22 arrows).])])dnl

AC_ARG_ENABLE(i18n, [AS_HELP_STRING([--disable-i18n],
	[disable internationalization features (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],
    [AC_DEFINE([I18N], 1,
	[Define to enable internationalization features.])dnl
    AC_DEFINE([I18N_USE_PREEDIT], 1,
	[Define to use preediting with i18n.])])
AM_CONDITIONAL([I18N], [test "x$enableval" = xyes])dnl

AC_ARG_WITH(gsexe, [AS_HELP_STRING([--with-gsexe=<name>],
       [specify filename or path of the ghostscript executable (default: gs);
 empty string, "", to avoid calling the executable])],
    [AS_IF([test "x$withval" = xno], [withval=""])],
    [withval=yes])dnl
AS_IF([test "x$withval" = xyes], [withval="gs"])
AC_DEFINE_UNQUOTED([GSEXE], ["$withval"],
    [Define to the filename or path of the ghostscript executable.])dnl
AC_SUBST([GSEXE], ["$withval"])

dnl With # as comment, configure fails on the lines below!
dnl Currently only w_rottext.c includes CACHE_[XIMAGES|BITMAPS], logic there
dnl sets CACHE_BITMAPS if CACHE_XIMAGES is not set.
AC_ARG_ENABLE(ximages-cache, [AS_HELP_STRING([--enable-ximages-cache],
	[enable caching of x-images, instead of bitmaps, \
		in the X-server (default: disable, cache bitmaps)])],
    [],[enableval=no])dnl
AS_IF([test "x$enableval" != xno],
    [AC_DEFINE([CACHE_XIMAGES], 1,
	[Define to cache X-images, undefine to cache \
		bitmaps in the X-server.])])dnl

AC_ARG_ENABLE(cache-size, [AS_HELP_STRING([--enable-cache-size=<kB>],
	[set the maximum size of bitmaps (kB) \
		cached in the X-server (default: 20000)])],
    [], [enableval=20000])dnl
AS_IF([test "$enableval" -gt 0], [], [enableval=20000])dnl
AC_DEFINE_UNQUOTED([CACHE_SIZE_LIMIT], [$enableval],
    [Define to the maximum size of bitmaps (kB) cached in the X-server.])dnl

AC_ARG_ENABLE(xpm, [AS_HELP_STRING([--disable-xpm],
	[disable support for xpm color-bitmaps, internally and for import \
		(default: enable)])], [], [enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],
    [AC_SEARCH_LIBS([XpmFree], [Xpm],
	[AC_DEFINE([USE_XPM], 1, [Define to use xpm color-bitmaps and enable
	import of xpm files.])], [enableval=no])])
AM_CONDITIONAL([USE_XPM], [test "x$enableval" = xyes])dnl

AC_ARG_ENABLE(splash, [AS_HELP_STRING([--enable-splash],
	[enable splash screen (default: disable)])],
    [], [enableval=no])dnl
AS_IF([test "x$enableval" = xyes],
    [AC_DEFINE([USE_SPLASH], 1, [Define to show a splash screen.])])
AM_CONDITIONAL([USE_SPLASH], [test "x$enableval" = xyes])dnl

AC_ARG_WITH(xaw3d1_5e, [AS_HELP_STRING([--without-xaw3d1_5e],
	[do not use version Xaw3d >= 1.5e (default: use)])],
    [],[with_xaw3d1_5e=yes])dnl

AC_ARG_WITH(xaw3d, [AS_HELP_STRING([--without-xaw3d],
	[do not use X Athena Widget toolkit with 3D-effects (default: use)])],
    [],[withval=yes])dnl
dnl AS_IF([test -n "$PKG_CONFIG" && `$PKG_CONFIG --exists xaw3d`],dnl
dnl    [AS_IF([test "x$withval" = xyes],dnl
dnl	[PKG_CHECK_MODULES(XAW, xaw3d)],
dnl	[PKG_CHECK_MODULES(XAW, xaw7, [],
dnl	    [AC_MSG_WARN("$XAW_PKG_ERRORS")
dnl	     PKG_CHECK_MODULES(XAW, xaw6)])dnl

AS_IF([test "x$withval" = xyes],
    [AS_IF([test -z "$XCPPFLAGS"],
	[XCPPFLAGS="-DXAW_INTERNATIONALIZATION"],
	[XCPPFLAGS="$XCPPFLAGS -DXAW_INTERNATIONALIZATION"])
     AC_DEFINE([XAW3D], 1,
		[Define to use X Athena Widgets with 3D-effects.])
     AS_IF([test "x$with_xaw3d1_5e" = xyes],
	[XLIBS="-lXaw3d $XLIBS"
	AC_DEFINE([XAW3D1_5E], 1,
		[Define to use version Xaw3d >= 1.5e.])],
	[XLIBS="-lXaw3d -lXmu $XLIBS"])],
    [XLIBS="-lXmu $XLIBS"
     AC_SEARCH_LIBS([XawInitializeWidgetSet], [Xaw8 Xaw7 Xaw6], [], [],
	     [$XLIBS])])
AM_CONDITIONAL([XAW3D1_5E],
    [test "x$withval" = xyes && test "x$with_xaw3d1_5e" = xyes])dnl

AC_ARG_ENABLE(tablet, [AS_HELP_STRING([--enable-tablet],
	[enable support for tablet device (default: disable)])],
    [], [enableval=no])dnl
AS_IF([test "x$enableval" = xyes],
    [AC_SEARCH_LIBS([XFreeDeviceList], [Xi],
	    [AC_DEFINE([USE_TAB], 1, [Define for using an input tablet.])])])

AC_ARG_ENABLE(comp-led, [AS_HELP_STRING([--enable-comp-led=#],
    [turn on the compose indicator LED when entering \
		multi-key characters (default: 3)])],
    [],[enableval=3])dnl
AS_IF([test "$enableval" -ge 1 && test "$enableval" -le 4],
    [AC_DEFINE_UNQUOTED([COMP_LED], [$enableval],dnl
	[Define and set to a number (1-4) to turn on the compose indicator LED \
	 when entering multi-key characters.])])dnl

printcapfile="/etc/printcap"
AC_ARG_WITH(printcap, [AS_HELP_STRING([--with-printcap=<path>],
	[specify path to printcap file (default: /etc/printcap)])],
    [AS_IF([test "x$withval" = xno || test "x$withval" = xyes],
	[AC_MSG_NOTICE([using $printcapfile as printcap file])],
	[printcapfile=$withval])])
AC_DEFINE_UNQUOTED([PRINTCAP], ["$printcapfile"],
	[Define to the path of the printcap-file.])

dnl Nice idea, to set appdefaultdir using pkg-config.
dnl Alas, this results in a hard-coded path, which breaks the
dnl make distckeck target, because make distcheck _requires_
dnl user-writeable locations. Here is the attempt:
dnl    [PKG_CHECK_MODULES(APPDEFAULTDIR, xt)
dnl	AS_IF([test -n "$PKG_CONFIG"],dnl
dnl	[appdefaultdir="$($PKG_CONFIG --variable=appdefaultdir xt)"],dnl

default_appdefaultdir=
AC_ARG_WITH(appdefaultdir, [AS_HELP_STRING([--with-appdefaultdir=<path>],
	[specifiy directory for X resources file (default: \
		${datarootdir}/X11/app-defaults)])],
    [],[withval='${datarootdir}/X11/app-defaults'])dnl
AC_SUBST(appdefaultdir, ["$withval"])
# In addition, expand now, to substitute in xfig.man.
# First expand datarootdir, secondly prefix.
# Below, all variables for xfig.man are expanded together.
AS_IF([test "x$prefix" = xNONE],
    [prefix="$ac_default_prefix";
     APPDEFAULTDIR=`eval echo "$withval"`;
     APPDEFAULTDIR=`eval echo "$APPDEFAULTDIR"`; prefix=NONE],
    [APPDEFAULTDIR=`eval echo "$withval"`;
     APPDEFAULTDIR=`eval echo "$APPDEFAULTDIR"`;])dnl
AC_SUBST([APPDEFAULTDIR])dnl

AC_ARG_WITH(icondir, [AS_HELP_STRING([--with-icondir=<path>],
	[specify icon directory, to put xfig.png \
		(default: $datarootdir/pixmaps)])],
    [], [withval='${datarootdir}/pixmaps'])dnl
AC_SUBST(icondir, ["$withval"])dnl

AC_ARG_WITH(applicationsdir, AS_HELP_STRING([--with-applicationsdir=<path>],
	[specify directory for xfig.desktop file \
		(default: $datarootdir/applications)]),
    [], [withval='${datarootdir}/applications'])dnl
AC_SUBST(applicationsdir, ["$withval"])dnl

AC_ARG_WITH(compkeydb, [AS_HELP_STRING([--without-compkeydb],
	[do not use Compose Key database file \
		shipped with xfig (default: use)])],
    [], [withval=yes])dnl
AS_IF([test "x$withval" != xyes],dnl
    [AC_DEFINE([NO_COMPKEYDB], 1,dnl
	[Define to not use the Compose Key Database file shipped with xfig.])])

AC_ARG_WITH(compkeydbdir, [AS_HELP_STRING([--with-compkeydbdir=<path>],
	[specify directory for the compose key database file, CompKeyDB \
		(default: $datadir/xfig)])],
    [], [withval='${datadir}/xfig'])dnl
AC_SUBST(compkeydbdir, ["$withval"])dnl


# Set the variables for substitution in xfig.man
# This builds on the side-effect of the AC_SUBST above, to write, e.g.,
# compkeydbdir="$withval" into the ./configure script.
AS_IF([test "x$prefix" = xNONE],
	[prefix="$ac_default_prefix"
	 ICONDIR=`eval echo "$icondir"`
	 ICONDIR=`eval echo "$ICONDIR"`
	 APPLICATIONSDIR=`eval echo "$applicationsdir"`
	 APPLICATIONSDIR=`eval echo "$APPLICATIONSDIR"`
	 COMPKEYDBDIR=`eval echo "$compkeydbdir"`
	 COMPKEYDBDIR=`eval echo "$COMPKEYDBDIR"`
	 COMPKEYDBDIR=`eval echo "$COMPKEYDBDIR"`
	 HTMLDIR=`eval echo "$htmldir"`	# $docdir
	 HTMLDIR=`eval echo "$HTMLDIR"`	# $datarootdir/doc/$PACKAGE_TARNAME
	 HTMLDIR=`eval echo "$HTMLDIR"`	# $prefix/....
	 HTMLDIR=`eval echo "$HTMLDIR"`
	 DOCDIR=`eval echo "$docdir"`
	 DOCDIR=`eval echo "$DOCDIR"`
	 DOCDIR=`eval echo "$DOCDIR"`
	 # a kludge, set PKGDATADIR to what automake most probably would set it
	 PKGDATADIR=`eval echo ${datarootdir}/xfig`
	 PKGDATADIR=`eval echo $PKGDATADIR`
	 prefix=NONE],
	[ICONDIR=`eval echo "$icondir"`
	 ICONDIR=`eval echo "$ICONDIR"`
	 APPLICATIONSDIR=`eval echo "$applicationsdir"`
	 APPLICATIONSDIR=`eval echo "$APPLICATIONSDIR"`
	 COMPKEYDBDIR=`eval echo "$compkeydbdir"`
	 COMPKEYDBDIR=`eval echo "$COMPKEYDBDIR"`
	 COMPKEYDBDIR=`eval echo "$COMPKEYDBDIR"`
	 HTMLDIR=`eval echo "$htmldir"`	# $docdir
	 HTMLDIR=`eval echo "$HTMLDIR"`	# $datarootdir/doc/$PACKAGE_TARNAME
	 HTMLDIR=`eval echo "$HTMLDIR"`	# $prefix/....
	 HTMLDIR=`eval echo "$HTMLDIR"`
	 DOCDIR=`eval echo "$docdir"`
	 DOCDIR=`eval echo "$DOCDIR"`
	 DOCDIR=`eval echo "$DOCDIR"`
	 PKGDATADIR=`eval echo ${datarootdir}/xfig`
	 PKGDATADIR=`eval echo $PKGDATADIR`])dnl
AC_SUBST([ICONDIR])dnl
AC_SUBST([APPLICATIONSDIR])dnl
AC_SUBST([COMPKEYDBDIR])dnl
AC_SUBST([HTMLDIR])dnl
AC_SUBST([DOCDIR])dnl
AC_SUBST([PKGDATADIR])dnl

AC_ARG_WITH(xfig-libraries, AS_HELP_STRING([--without-xfig-libraries],
	[do not install xfig-Libraries (default: install)]),
    [], [withval=yes])dnl
AM_CONDITIONAL([XFIG_LIBRARIES],
    [test "x$withval" = xyes && test -d "$srcdir/Libraries"])dnl

# Autotest infrastructure.
AC_CONFIG_TESTDIR([tests], [src${PATH_SEPARATOR}tests])dnl
AM_MISSING_PROG([AUTOM4TE], [autom4te])dnl

dnl If doc/xfig_man.html.in is not present, simply touch it, e.g.
dnl touch -r doc/FORMAT1.3 doc/xfig_man.html.in

AC_CONFIG_FILES([Makefile
		app-defaults/Fig
		splash-image/spl_bckgnd.fig
		src/Makefile
		src/version.fig
		doc/html/images/xfig-title.fig
		doc/Makefile
		doc/xfig.man
		doc/xfig_man.html
		tests/Makefile
		tests/atlocal])dnl

AC_OUTPUT

AC_MSG_NOTICE([
  Compile, CC=$CC XCPPFLAGS=${XCPPFLAGS:-<empty>} \\
	CPPFLAGS=${CPPFLAGS:-<empty>} CFLAGS=${CFLAGS:-<empty>}
  Link, $CC CFLAGS=${CFLAGS:-<empty>} XLDFLAGS=${XLDFLAGS:-<empty>} \\
	LDFLAGS=${LDFLAGS:-<empty>} <object> \\
	XLIBS=${XLIBS:-<empty>} LIBS=${LIBS:-<empty>}

Installation locations:
  $APPDEFAULTDIR/ Fig	(--with-appdefaultdir)
  $APPLICATIONSDIR/ xfig.desktop	(--with-applicationsdir)
  $ICONDIR/ xfig.png	(--with-icondir)
  $PKGDATADIR/ Libraries (--datarootdir)
  $HTMLDIR/ html	(--htmldir)
  $DOCDIR/ doc-files	(--docdir)])
