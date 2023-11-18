#!/bin/csh -f
#
# Fig2ps2tex - generate a TeX file for including a PostScript file
#		 involves calculating the bounding box from fig2ps output
#
# Copyright 1994 Micah Beck
#
# The X Consortium, and any party obtaining a copy of these files from
# the X Consortium, directly or indirectly, is granted, free of charge, a
# full and unrestricted irrevocable, world-wide, paid up, royalty-free,
# nonexclusive right and license to deal in this software and
# documentation files (the "Software"), including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons who receive
# copies from any such party to do so, with the only requirement being
# that this copyright notice remain intact.  This license includes without
# limitation a license to do the foregoing actions under any patents of
# the party supplying this software to the X Consortium.
#
# Changes
#
# 2016-07-07  Thomas Loimer
#	* use here-document, instead of echo
#

set bbox = `grep "^%%BoundingBox:" $1`

set xsp = `echo "3k $bbox[4] $bbox[2] - 72 / p" | dc`
set ysp = `echo "3k $bbox[5] $bbox[3] - 72 / p" | dc`

cat <<EOF
\\makebox[${xsp}in][l]{
  \\vbox to ${ysp}in{
    \\vfill
    \\special{psfile=$1}
  }
  \\vspace{-\\baselineskip}
}
EOF
