/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if the default papersize for the dxf- and ibmgl-drivers is A4,
   not letter. */
#define A4 1

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to the name of the ghostscript command. */
#define GSEXE "gs"

/* Define to 1 if you have the `fdopen' function. */
#define HAVE_FDOPEN 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `getline' function. */
#define HAVE_GETLINE 1

/* Define to 1 if you have the `getopt' function. */
#define HAVE_GETOPT 1

/* Define to 1 if you have the `getpwuid' function. */
#define HAVE_GETPWUID 1

/* Define to 1 if you have the <iconv.h> header and libiconv. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isascii' function. */
#define HAVE_ISASCII 1

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the <png.h> header file. */
#define HAVE_PNG_H 1

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the zlib library and <zlib.h> header. */
#define HAVE_ZLIB_H 1

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Define to 1 if you are under Windows and have _setmode() to set file modes
   to text or binary. */
/* #undef HAVE__SETMODE */

/* Define to 1 to use internationalization of text input for some drivers. */
#define I18N 1

/* Define to 1 if the ibmgl-driver should create instructions for the IBM
   Graphics Enhancement Cartridge. */
#define IBMGEC 1

/* Define to 1 to use LaTeX2e-graphics in pstex- and latex-drivers. */
#define LATEX2E_GRAPHICS 1

/* Define to 1 to use the New Font Selection Scheme for LaTeX. */
#define NFSS 1

/* Define to 1 to not use baseline-shift sub/superscripts in the svg-driver */
/* #undef NOSUPER */

/* Name of package */
#define PACKAGE "fig2dev"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "thomas.loimer@tuwien.ac.at"

/* Define to the full name of this package. */
#define PACKAGE_NAME "fig2dev"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "fig2dev 3.2.8b"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "fig2dev"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://sourceforge.net/projects/mcj"

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.2.8b"

/* Define to the full path of the X color database file. */
#define RGB_FILE "/etc/X11/rgb.txt"

/* Define to 1 if pict2e-graphics should honor \XFigwidth or \XFigheight. */
/* #undef SCALE_PICT2E */

/* Define to 1 if all of the C90 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Define to 1 to use boxes with rounded corners in the tpic-driver. */
#define TPIC_ARC_BOX 1

/* Version number of package */
#define VERSION "3.2.8b"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */
