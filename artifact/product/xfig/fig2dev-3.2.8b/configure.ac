#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_COPYRIGHT([Fig2dev: Translate Fig code to various Devices
Copyright (c) 1991 by Micah Beck
Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
Parts Copyright (c) 1989-2015 by Brian V. Smith
Parts Copyright (c) 2015-2020 by Thomas Loimer

Any party obtaining a copy of these files is granted, free of charge, a
full and unrestricted irrevocable, world-wide, paid up, royalty-free,
nonexclusive right and license to deal in this software and documentation
files (the "Software"), including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense and/or sell copies
of the Software, and to permit persons who receive copies from any such
party to do so, with the only requirement being that the above copyright
and this permission notice remain intact.
])

#
# configure.ac
# Author: Thomas Loimer, 2015-2020.
#

dnl Define m4 variables for use in AC_INIT and AC_DEFINE below.
dnl VERS=3.2 and AC_INIT(...,$VERS..) does not work. (These variables
dnl are probably only expanded when ./configure is run.) See also
dnl info automake, section 16 "Rebuilding Makefiles".
dnl defines m4-variables FIG_VERSION and RELEASEDATE
m4_include([version.m4])

dnl The minimum autoconf version to process this file. In version 2.60,
dnl the directory variables changed, see info autoconf, section 4.8.3.
AC_PREREQ([2.60])

#
# Initialize.
#
AC_INIT([fig2dev], [FIG_VERSION], [thomas.loimer@tuwien.ac.at],[],
	[https://sourceforge.net/projects/mcj])
dnl AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS],
dnl	[TARNAME], [URL])
dnl TARNAME defaults to FULL-PACKAGE-NAME, converted to lower case
dnl and all characters other than alphanumerics and _ changed to -.
dnl defines PACKAGE_NAME, PACKAGE_TARNAME, PACKAGE_VERSION, PACKAGE_STRING,
dnl PACKAGE_BUGREPORT and PACKAGE_URL

# Set automake options.
dnl The options are written to AUTOMAKE_OPTIONS. A minimum version
dnl of automake, e.g., 1.6.1, can also be put into AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE([-Wall foreign dist-xz no-dist-gzip subdir-objects])
dnl AM_INIT_AUTOMAKE([-Wall -Werror foreign])
dnl  -Wall.....enable all (automake) warnings
dnl  -Werror...and report them as error
dnl  foreign...do no require the files ChangeLog COPYING AUTHORS NEWS
dnl		README INSTALL
dnl  subdir-objects...place objects into the dir where the corresponding
dnl		source file resides, not into the current build directory

AC_CONFIG_MACRO_DIR([m4])

# Check whether ./configure resides in the correct directory
AC_CONFIG_SRCDIR([CHANGES])

# Write the variables determined by ./configure into config.h.
# Therefore, make sure to #include "config.h" in each source file.
AC_CONFIG_HEADERS([config.h])

AC_SUBST([RELEASE_DATE], "RELEASEDATE")

#
# Checks for programs.
#
AC_PROG_CC
# Needed to pack the convenience library fig2dev/dev/fig2dev.a
AC_PROG_RANLIB
AM_PROG_AR

# Define LN_S for use in the Makefiles
AC_PROG_LN_S
# For use in the testsuite.
# Need to take over the variables in fig2dev/tests/atlocal.in
AC_PROG_FGREP
AC_PROG_SED

# Ghostscript 7.10 says, the executable for Windows 95/98 is called
# gswin32, for Dos or Windows 3 it is called gs386. Ancient enough.
AC_CHECK_PROGS([GSEXE],[gs gswin32c gsos2 gswin32 gs386])
AC_ARG_VAR([GSEXE], [ghostscript command])
# If ghostscript is not found, GSEXE is set to the empty string.
# However, we do "#ifdef GSEXE" etc., hence undef GSEXE, if empty.
AS_IF([test "x$GSEXE" != x],dnl
    [AC_DEFINE_UNQUOTED([GSEXE], ["$GSEXE"],
	[Define to the name of the ghostscript command.])])dnl

#
# Checks for libraries.
#
AC_SEARCH_LIBS([cos], [m])


#
# Checks for header files.
#

# Check for iconv.h. If found, try to compile and link a custom-made
# test program. On Darwin, iconv.h typedef's iconv() to libiconv(). Therefore,
# one cannot use AC_SEARCH_LIBS to search for the iconv symbol, but must use a
# test program that includes iconv.h.
AC_CHECK_HEADER([iconv.h],
    [TL_SEARCH_LIBS_SOURCE([iconv], [iconv], [],
	[#include <iconv.h>
	int main(void)
	{char *a; return iconv(0, &a, (size_t*)a, &a, (size_t*)a);}])dnl
    AS_IF([test "$tl_cv_search_source_iconv" != no],
	[AC_DEFINE([HAVE_ICONV], 1,
	    [Define to 1 if you have the <iconv.h> header and libiconv.])])],
    [], [AC_INCLUDES_DEFAULT])

# Check for headers, but do not define preprocessor-variables in config.h.
# If the headers below are missing, the program will not compile.
AS_VAR_SET([headers_missing], [no])
AC_CHECK_HEADER([limits.h], [], [headers_missing=yes
    AC_MSG_WARN(limits.h is missing!)], [AC_INCLUDES_DEFAULT])
AC_CHECK_HEADER([netinet/in.h], [], [headers_missing=yes
    AC_MSG_WARN(netinet/in.h is missing!)], [AC_INCLUDES_DEFAULT])
AC_CHECK_HEADER([sys/file.h], [], [headers_missing=yes
    AC_MSG_WARN(sys/file.h is missing!)], [AC_INCLUDES_DEFAULT])
AC_CHECK_HEADER([sys/param.h], [], [headers_missing=yes
    AC_MSG_WARN(sys/param.h is missing!)], [AC_INCLUDES_DEFAULT])
# AC_INCLUDES_DEFAULT anyhow requires stdio.h and checks for
# sys/types.h, sys/stat.h, stdlib.h, string.h, strings.h, inttypes.h,
# stdint.h, unistd.h, and optionally stddef.h and memory.h. The
# variables HAVE_SYS_TYPES_H, HAVE_SYS_STAT_H, HAVE_STDLIB_H etc. are
# defined in config.h.

# Some headers are checked implicitly by testing for functions provided
# by them: <pwd.h> by getpwuid(), <errno.h> by strerror(). Really,
# strerror() is not defined in errno.h, but it is save to assume that
# errno.h exists if strerror() is found.

# Check for header files and libraries
dnl First search for the header, only then search for the libs. The other way
dnl round, the library found would be prepended to LIBS, unnecessarily.
AC_CHECK_HEADER([zlib.h],
    [AC_SEARCH_LIBS([deflate], [z],
	[AC_DEFINE([HAVE_ZLIB_H], 1,
	    [Define to 1 if you have the zlib library and <zlib.h> header.])])],
    [], [AC_INCLUDES_DEFAULT])


#
# Check user options.
#
AC_ARG_ENABLE(versioning, [AS_HELP_STRING([--enable-versioning],
	[enable changing the version number, only useful for \
	 hacking (default: disable)])],
    [],[enableval=no])dnl
AM_CONDITIONAL([ENABLE_VERSIONING], [test "x$enableval" = xyes])dnl

AC_ARG_ENABLE(transfig, [AS_HELP_STRING([--enable-transfig],
	[build the transfig program (default: do not build)])],
    [],[enableval=no])dnl
AM_CONDITIONAL([ENABLE_TRANSFIG],[test "x$enableval" = xyes])

AC_ARG_ENABLE(letterpaper, [AS_HELP_STRING([--enable-letterpaper],
	[set default papersize to letter for dxf \
		and ibmgl-drivers (default: A4)])],
    [],[enableval=no])dnl
AS_IF([test "x$enableval" = xno || test "x$enableval" = xA4 || \
	test "x$enableval" = xa4],dnl
    [AC_DEFINE([A4], 1,dnl
	[Define to 1 if the default papersize for the dxf- \
		and ibmgl-drivers is A4, not letter.])dnl
# Used in fig2dev.1.in
     AC_SUBST(DEFAULT_PAPERSIZE, ["ISO A4"])dnl
     AC_SUBST(ALTERNATE_PAPERSIZE, ["ANSI A"])],dnl
    [AC_SUBST(DEFAULT_PAPERSIZE, ["ANSI A"])dnl
     AC_SUBST(ALTERNATE_PAPERSIZE, ["ISO A4"])])dnl

AC_ARG_ENABLE([i18n], [AS_HELP_STRING([--disable-i18n],
	[disable internationalization of text input \
		for some drivers (default: enable)])],
    [i18nman="/dev/null"],
    [enableval=yes; i18nman="$srcdir/man/i18n.man"])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([I18N], 1,dnl
	[Define to 1 to use internationalization of text input \
		for some drivers.])dnl
# The directory where internationalization data is installed to.
# fig2dev/dev/Makefile.am defines -DI18N_DATADIR
# i18ndir is used in fig2dev/i18n/Makefile.am
     AC_SUBST([i18ndir],['$(pkgdatadir)/i18n'])])
AM_CONDITIONAL([ENABLE_I18N],[test "x$enableval" = xyes])
dnl Substitute the file fragment named by i18nman, defined above,
dnl into man/fig1dev.1 (or not)
AC_SUBST_FILE([i18nman])

AC_ARG_ENABLE([NFSS], [AS_HELP_STRING([--disable-NFSS],
	[disable LaTeX New Font Selection Scheme (default: enable)])],
    [nfssman="/dev/null"],[enableval=yes; nfssman="$srcdir/man/nfss.man"])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([NFSS], 1,dnl
	 [Define to 1 to use the New Font Selection Scheme for LaTeX.])])dnl
AC_SUBST_FILE([nfssman])

AC_ARG_ENABLE([latex2e_graphicx], [AS_HELP_STRING([--disable-latex2e_graphicx],
	[disable LaTeX2e-graphics commands in pstex- \
		and latex-drivers (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([LATEX2E_GRAPHICS], 1,dnl
	[Define to 1 to use LaTeX2e-graphics in pstex- \
		and latex-drivers.])])dnl

AC_ARG_ENABLE([scale-pict2e], [AS_HELP_STRING([--enable-scale-pic2t2e],
	[enable scaling of pict2e-graphics, e.g., \
		with \XFigwidth (default: disable)])],
    [],[enableval=no])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([SCALE_PICT2E], 1,dnl
	 [Define to 1 if pict2e-graphics should honor \
		\XFigwidth or \XFigheight.])])dnl

AC_ARG_ENABLE([IBM-GEC], [AS_HELP_STRING([--disable-IBM-GEC],
	[disable instruction set for IBM Graphics Enhancement \
		Cartridge (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([IBMGEC], 1,dnl
	[Define to 1 if the ibmgl-driver should create instructions \
		for the IBM Graphics Enhancement Cartridge.])dnl
     AC_SUBST([WITH_IBMGEC],[without])],dnl
    [AC_SUBST([WITH_IBMGEC],[with])])dnl

AC_ARG_ENABLE([baseline-shift], [AS_HELP_STRING([--disable-baseline-shift],
	[disable use of baseline-shift in the svg-driver (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" != xyes],dnl
    [AC_DEFINE([NOSUPER], 1,dnl
	 [Define to 1 to not use baseline-shift sub/superscripts \
		in the svg-driver])])dnl

AC_ARG_ENABLE([round-box], [AS_HELP_STRING([--disable-round-box],
	[disable use of boxes with rounded corners \
		in the tpic-driver (default: enable)])],
    [],[enableval=yes])dnl
AS_IF([test "x$enableval" = xyes],dnl
    [AC_DEFINE([TPIC_ARC_BOX], 1,dnl
	 [Define to 1 to use boxes with rounded corners \
		in the tpic-driver.])])dnl

AC_ARG_WITH(png,
    [AS_HELP_STRING([--without-png],
		[disable reading png-images (default: enable)])],
    [],[with_png=try])dnl

AS_IF([test "x$with_png" != xno],
    [# -lz is not necessary for shared libraries
    # AC_SEARCH_LIBS([deflate], [z])dnl
    AC_SEARCH_LIBS([png_read_info], [png],
	[AC_CHECK_HEADER([png.h],
	    [AC_DEFINE([HAVE_PNG_H], 1,dnl
		[Define to 1 if you have the <png.h> header file.])],
	    [], [AC_INCLUDES_DEFAULT])])])dnl

AM_CONDITIONAL([WITH_PNG], [test "$ac_cv_header_png_h" = yes])

AC_ARG_WITH(rgbfile, [AS_HELP_STRING([--with-rgbfile=<path>],
	[specify full path of X color file (default: /etc/X11/rgb.txt)])],
	[],[withval=/etc/X11/rgb.txt])
AC_DEFINE_UNQUOTED([RGB_FILE], ["$withval"],dnl
	[Define to the full path of the X color database file.])


#
# Checks for typedefs, structures, and compiler characteristics.
#
AC_C_CONST
AC_C_INLINE
dnl to silence a warning on calling iconv() from genemf.c
dnl see the commit after 2b3711d
dnl AC_C_RESTRICT
AC_C_BIGENDIAN

dnl  Check for declarations. In any case defines, e.g., HAVE_DECL_M_PI.
dnl  Sets it to 0 if not found, to 1 if found.
dnl AC_CHECK_DECLS([M_PI, M_PI_2, M_PI_4], [], [], [#include <math.h>])
dnl Just provide our own pi

# Check, whether sdtbool.h exists and whether the type _Bool is defined.
# Defines HAVE_STDBOOL_H and HAVE__BOOL. See info autoconf for a usage
# example.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

#
# Checks for library functions.
#

# Check for functions and set, e.g., HAVE_STRERROR if found.
# Assume that errno.h exists if strerror() is available. Otherwise, do
# not use strerror() at all. Do not try to replace strerror() with the
# obsolete sys_nerr, sys_errlist and the declaration "int errno".
# If getpwuid() is found, <pwd.h> is assumed to exist.
AC_CHECK_FUNCS_ONCE([gethostname strerror getpwuid mkstemp fdopen])

# Under Windows, the _setmode() function is defined in io.h. It accepts two
# arguments and sets the file access mode to text or binary. O_TEXT and O_BINARY
# are defined in fcntl.h. Under BSD, another _setmode() function exists, that
# accepts one argument. Here, define HAVE__SETMODE, if (i) _setmode() compiles
# and links with two arguments given, and (ii) <io.h> and <fcntl.h> can be
# #included. As long as Windows does not have sh, this test probably only
# succeeds under cygwin.
AC_CACHE_CHECK([for _setmode],[tl_cv_func__setmode],
	[AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <io.h>
#include <fcntl.h>]],[[_setmode(1, O_BINARY);]])],
		[tl_cv_func__setmode=yes],[tl_cv_func__setmode=no])])
AS_IF([test "$tl_cv_func__setmode" = yes],
	[AC_DEFINE([HAVE__SETMODE], 1, [Define to 1 if you are under Windows \
		and have _setmode() to set file modes to text or binary.])])

# Check for functions and, if not found, use the corresponding
# replacement, e.g., strstr.c, in the top srcdir. Sets, e.g.,
# HAVE_STRSTR. Except possibly getopt(), any modern system should have these
# functions, so all except one are obsolete checks.
AC_REPLACE_FUNCS([getline getopt isascii strstr strchr strrchr \
	strcasecmp strncasecmp strdup])

# Place the replacement functions into this dir.
AC_CONFIG_LIBOBJ_DIR([fig2dev/lib])

#
# Autotest infrastructure.
#
AC_CONFIG_TESTDIR([fig2dev/tests])
AM_MISSING_PROG([AUTOM4TE], [autom4te])

# Create these files from the Makefile.in templates. The Makefile.in, in
# turn, is created from Makefile.am with automake or just autoreconf.
AC_CONFIG_FILES([Makefile
		man/Makefile
		man/fig2dev.1
		fig2dev/Makefile
		fig2dev/dev/Makefile
		fig2dev/i18n/Makefile
		fig2dev/tests/Makefile
		fig2dev/tests/atlocal
		fig2dev/tests/data/patterns.svg
		fig2dev/tests/data/fillswclip.svg
		transfig/Makefile])

AC_OUTPUT

#
# Diagnostic output
#
# TODO: Add a hint for unusual search paths.
# Macports by default installs under /opt/local, fink under /sw.
# Cygwin may install under /usr/include/noX (/X11), /lib/noX.
# Therefore, libpaths may be /opt/local/lib /sw/lib /opt/X11/lib /lib/noX
# Include paths may be /opt/local/include /sw/include /opt/X11/include
# if with-png!=no && ac_cv_search_png_read_info = no;
#	missingfuncs = "png_read_info " # $missingfuncs
#	missinglibs = "-lpng " # $missinglibs
#	if ac_cv_header_png_h != yes
#		missingheaders = "png.h "
# test "$tl_cv_search_source_iconv" = no],
# test "x$with_xpm" != xno &&
#    ac_cv_search_XpmReadFileToXpmImage], [Xpm],
#  [test "x$ac_cv_header_X11_xpm_h" = xyes])

AS_IF([test "$headers_missing" = yes],dnl
	[AC_MSG_WARN([headers are missing!
	*** The program will not compile.    ***
	*** Look for WARNING-messages above. ***])])
AC_MSG_NOTICE([Results:
  preprocessor		CPP:		$CPP
  preprocessor flags	CPPFLAGS:	${CPPFLAGS:-<empty>}
  compiler		CC:		$CC
  compiler flags	CFLAGS:		${CFLAGS:-<empty>}
  linker flags		LDFLAGS:	${LDFLAGS:-<empty>}
  libraries		LIBS:		${LIBS:-<empty>}
  install location	prefix:		$prefix

Files will be installed under $prefix.])
