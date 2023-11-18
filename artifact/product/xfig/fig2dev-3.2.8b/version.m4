dnl Fig2dev: Translate Fig code to various Devices
dnl Copyright (c) 1991 by Micah Beck
dnl Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
dnl Parts Copyright (c) 1989-2015 by Brian V. Smith
dnl Parts Copyright (c) 2015-2021 by Thomas Loimer
dnl
dnl Any party obtaining a copy of these files is granted, free of charge, a
dnl full and unrestricted irrevocable, world-wide, paid up, royalty-free,
dnl nonexclusive right and license to deal in this software and documentation
dnl files (the "Software"), including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense and/or sell copies
dnl of the Software, and to permit persons who receive copies from any such
dnl party to do so, with the only requirement being that the above copyright
dnl and this permission notice remain intact.

dnl
dnl version.m4: Version information for inclusion by configure.ac.
dnl

dnl The version information is kept separately from configure.ac.
dnl Thus, configure.ac can remain unchanged between different versions.
dnl The values in this file are set by update_version_m4 if
dnl ./configure is called with --enable_versioning.

m4_define([FIG_VERSION], [3.2.8b])

dnl AC_INIT does not have access to shell variables.
dnl Therefore, define RELEASEDATE as a macro.
m4_define([RELEASEDATE], [Aug 2021])
