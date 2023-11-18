# ===========================================================================
#   tl_search_libs_source.m4
# ===========================================================================
#
# SYNOPSIS
#
#   TL_SEARCH_LIBS_SOURCE(FUNCTION, LIBRARIES,
#			[OTHER-LIBRARIES], [SOURCE])
#
#   Extend `AC_SEARCH_LIBS' by calling SOURCE, if given, to test for the
#   availability of FUNCTION.
#
#   Search for a library defining FUNCTION if it is not already
#   available.  If SOURCE is not given, this equates to calling
#   `AC_LINK_IFELSE([AC_LANG_CALL([], [FUNCTION])])' first with no
#   libraries, then for each library listed in LIBRARIES and with each
#   search path in SEARCH-PATHS.  If SOURCE is given, call
#   `AC_LINK_IFELSE([AC_LANG_SOURCE([$5])])'.
#
#   Prepend `-lLIBRARY' to `LIBS' for the first library found to contain
#   FUNCTION.
#
#   The result of this test is cached in the `tl_cv_search_source_FUNCTION'
#   variable as `none required' if FUNCTION is already available, as `no'
#   if no library containing FUNCTION was found, otherwise as the
#   `-lLIBRARY' option that needs to be prepended to `LIBS'.
#
#   Example:
#
#   On Darwin, iconv.h typedef's iconv() to libiconv(). Therefore, one
#   must include <iconv.h> in the test program to check for iconv().
#
#   TL_SEARCH_LIBS_SOURCE([iconv], [iconv], [],
#	[#include <iconv.h>
#	int main(void)
#	{char *a; return iconv(0, &a, (size_t*)a, &a, (size_t*)a);}])
#
#
# LICENSE
#
#   Copyright (c) 2018 Thomas Loimer <thomas.loimer@tuwien.ac.at>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.


#   TL_SEARCH_LIBS_SOURCE(FUNCTION, LIBRARIES,
#			[OTHER-LIBRARIES], [SOURCE])
#
AC_DEFUN([TL_SEARCH_LIBS_SOURCE],
[AS_VAR_PUSHDEF([tl_Search], [tl_cv_search_source_$1])dnl
AC_CACHE_CHECK([for library providing $1], [tl_Search],
[m4_ifval([$4],dnl AS_VAR_SET_IF expands to a shell construct
  [AC_LANG_CONFTEST([AC_LANG_SOURCE([$4])])],
  [AC_LANG_CONFTEST([AC_LANG_CALL([], [$1])])])
tl_libs_source_save_LIBS=$LIBS
for tl_lib in '' $2; do
  if test -z "$tl_lib"; then
    tl_res="none required"
  else
    tl_res=-l$tl_lib
    LIBS="-l$tl_lib $3 $tl_libs_source_save_LIBS"
  fi
  AC_LINK_IFELSE([], [AS_VAR_SET([tl_Search], [$tl_res])])
  AS_VAR_SET_IF([tl_Search], [break])
done
AS_VAR_SET_IF([tl_Search], , [AS_VAR_SET([tl_Search], [no])])
rm conftest.$ac_ext
LIBS=$tl_libs_source_save_LIBS])
AS_VAR_COPY([tl_res], [tl_Search])
AS_IF([test "$tl_res" != no],
  [test "$tl_res" = "none required" || LIBS="$tl_res $LIBS"])
AS_VAR_POPDEF([tl_Search])dnl
])
