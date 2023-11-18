/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to use arrow types 4 to 14 (22 arrows). */
#define ARROWS4TO14 1

/* Define to the maximum size of bitmaps (kB) cached in the X-server. */
#define CACHE_SIZE_LIMIT 20000

/* Define to cache X-images, undefine to cache bitmaps in the X-server. */
/* #undef CACHE_XIMAGES */

/* Define and set to a number (1-4) to turn on the compose indicator LED when
   entering multi-key characters. */
#define COMP_LED 3

/* Define to the filename or path of the ghostscript executable. */
#define GSEXE "gs"

/* Define to 1 if you have the declaration of `S_IFDIR', and to 0 if you
   don't. */
#define HAVE_DECL_S_IFDIR 1

/* Define to 1 if you have the declaration of `S_IWRITE', and to 0 if you
   don't. */
#define HAVE_DECL_S_IWRITE 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the ghostscript library and header files. */
/* #undef HAVE_GSLIB */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isascii' function. */
#define HAVE_ISASCII 1

/* Define to 1 if you have the jpeg library and header files. */
#define HAVE_JPEG 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the png library and header files. */
#define HAVE_PNG 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

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

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the tiff library and header files. */
#define HAVE_TIFF 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to enable internationalization features. */
#define I18N 1

/* Define to use preediting with i18n. */
#define I18N_USE_PREEDIT 1

/* Define to not use the Compose Key Database file shipped with xfig. */
/* #undef NO_COMPKEYDB */

/* Name of package */
#define PACKAGE "xfig"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "thomas.loimer@tuwien.ac.at"

/* Define to the full name of this package. */
#define PACKAGE_NAME "xfig"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "xfig 3.2.8b"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "xfig"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://sourceforge.net/projects/mcj/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.2.8b"

/* Define to the path of the printcap-file. */
#define PRINTCAP "/etc/printcap"

/* Define the fig file format. Identical to major.minor substring of xfig
   version. */
#define PROTOCOL_VERSION "3.2"

/* Define to 0 if not provided by regex.h. */
/* #undef REG_NOERROR */

/* Define the year of the release. */
#define RELEASE_YEAR "2021"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to show a splash screen. */
/* #undef USE_SPLASH */

/* Define for using an input tablet. */
/* #undef USE_TAB */

/* Define to use xpm color-bitmaps and enable import of xpm files. */
#define USE_XPM 1

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

/* Define to use X Athena Widgets with 3D-effects. */
#define XAW3D 1

/* Define to use version Xaw3d >= 1.5e. */
#define XAW3D1_5E 1

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */
