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
# version.m4: Version information. This file is included by configure.ac.
# Author: Thomas Loimer, 2017

dnl The version information is kept separately from configure.ac.
dnl Thus, configure.ac can remain unchanged between different versions.
dnl The values in this file are set by update_version_m4 if
dnl ./configure is called with --enable_versioning.

m4_define([XFIG_VERSION], [3.2.8b])

dnl AC_INIT does not have access to shell variables.
dnl Therefore, define RELEASEDATE as a macro.
m4_define([RELEASEDATE], [Aug 2021])
