/*
 * Fig2dev: Translate Fig code to various Devices
 * Parts Copyright (c) 2015-2017 by Thomas Loimer
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies
 * of the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 */

/*
 * gentikz.h: convert fig to tikz header file
 * Copyright (c) 2015-2017 by Thomas Loimer
 *
 */
/*
 * Quick commands were tested and work as the normal commands under scaling and
 * rotation, i.e., replacing \pgfusepath{stroke} by \pgfusepathqstroke and
 * \pgfpathmoveto{\pgfqpoint{x}{y}} as well as \pgfpathlineto by
 * \pgfpathqmoveto{x}{y} and \pgfpathqlineto{x}{y}. Strangely, except of pgfqpoint
 * quick commands are not used in the definitions of patterns in
 * pgflibrarypatterns.code.tex. Here, they are not used, except for the first
 * pattern, lines 30 degree left.
 */

/* probably, use \pgfqpointxy */

#define	PATTERNS	\
"% lines 30 degree left\n\
\\pgfdeclarepatternformonly{xfigp0}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{5bp}}{\\pgfqpoint{8bp}{4bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{4.5bp}\\pgfpathqlineto{9bp}{-0.5bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% lines 30 degree right\n\
\\pgfdeclarepatternformonly{xfigp1}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{5bp}}{\\pgfqpoint{8bp}{4bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{-0.5bp}\\pgfpathqlineto{9bp}{4.5bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% crosshatch 30 degree\n\
\\pgfdeclarepatternformonly{xfigp2}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{5bp}}{\\pgfqpoint{8bp}{4bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{-0.5bp}\\pgfpathqlineto{9bp}{4.5bp}\n\
\t\\pgfpathqmoveto{-1bp}{4.5bp}\\pgfpathqlineto{9bp}{-0.5bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% lines 45 degree left\n\
\\pgfdeclarepatternformonly{xfigp3}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{9bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{9bp}\\pgfpathqlineto{9bp}{-1bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% lines 45 degree right\n\
\\pgfdeclarepatternformonly{xfigp4}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{9bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{-1bp}\\pgfpathqlineto{9bp}{9bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% crosshatch 45 degree\n\
\\pgfdeclarepatternformonly{xfigp5}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{9bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{-1bp}\\pgfpathqlineto{9bp}{9bp}\n\
\t\\pgfpathqmoveto{-1bp}{9bp}\\pgfpathqlineto{9bp}{-1bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% horizontal bricks\n\
\\pgfdeclarepatternformonly{xfigp6}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{17bp}{17bp}}{\\pgfqpoint{16bp}{16bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{4bp}\\pgfpathqlineto{17bp}{4bp}\n\
\t\\pgfpathqmoveto{-1bp}{12bp}\\pgfpathqlineto{17bp}{12bp}\n\
\t\\pgfpathqmoveto{4bp}{-1bp}\\pgfpathqlineto{4bp}{4bp}\n\
\t\\pgfpathqmoveto{4bp}{12bp}\\pgfpathqlineto{4bp}{17bp}\n\
\t\\pgfpathqmoveto{12bp}{4bp}\\pgfpathqlineto{12bp}{12bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% vertical bricks\n\
\\pgfdeclarepatternformonly{xfigp7}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{17bp}{17bp}}{\\pgfqpoint{16bp}{16bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{4bp}{-1bp}\\pgfpathqlineto{4bp}{17bp}\n\
\t\\pgfpathqmoveto{12bp}{-1bp}\\pgfpathqlineto{12bp}{17bp}\n\
\t\\pgfpathqmoveto{-1bp}{4bp}\\pgfpathqlineto{4bp}{4bp}\n\
\t\\pgfpathqmoveto{12bp}{4bp}\\pgfpathqlineto{17bp}{4bp}\n\
\t\\pgfpathqmoveto{4bp}{12bp}\\pgfpathqlineto{12bp}{12bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% horizontal lines\n\
\\pgfdeclarepatternformonly{xfigp8}\n\
{\\pgfpointorigin}{\\pgfqpoint{101bp}{1bp}}{\\pgfqpoint{100bp}{4bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{0bp}{0.5bp}\\pgfpathqlineto{101bp}{0.5bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% vertical lines\n\
\\pgfdeclarepatternformonly{xfigp9}\n\
{\\pgfpointorigin}{\\pgfqpoint{1bp}{101bp}}{\\pgfqpoint{4bp}{100bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{0.5bp}{0bp}\\pgfpathqlineto{0.5bp}{101bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% crosshatch\n\
\\pgfdeclarepatternformonly{xfigp10}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{5bp}{5bp}}{\\pgfqpoint{4bp}{4bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{2bp}\\pgfpathqlineto{5bp}{2bp}\n\
\t\\pgfpathqmoveto{2bp}{-1bp}\\pgfpathqlineto{2bp}{5bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% left shingles\n\
\\pgfdeclarepatternformonly{xfigp11}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{25bp}{25bp}}{\\pgfqpoint{24bp}{24bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{0bp}\\pgfpathqlineto{25bp}{0bp}\n\
\t\\pgfpathqmoveto{-1bp}{8bp}\\pgfpathqlineto{25bp}{8bp}\n\
\t\\pgfpathqmoveto{-1bp}{16bp}\\pgfpathqlineto{25bp}{16bp}\n\
\t\\pgfpathqmoveto{10bp}{0bp}\\pgfpathqlineto{14bp}{8bp}\n\
\t\\pgfpathqmoveto{2bp}{8bp}\\pgfpathqlineto{6bp}{16bp}\n\
\t\\pgfpathqmoveto{18bp}{16bp}\\pgfpathqlineto{22bp}{24bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% right shingles\n\
\\pgfdeclarepatternformonly{xfigp12}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{25bp}{25bp}}{\\pgfqpoint{24bp}{24bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-1bp}{0bp}\\pgfpathqlineto{25bp}{0bp}\n\
\t\\pgfpathqmoveto{-1bp}{8bp}\\pgfpathqlineto{25bp}{8bp}\n\
\t\\pgfpathqmoveto{-1bp}{16bp}\\pgfpathqlineto{25bp}{16bp}\n\
\t\\pgfpathqmoveto{14bp}{0bp}\\pgfpathqlineto{10bp}{8bp}\n\
\t\\pgfpathqmoveto{22bp}{8bp}\\pgfpathqlineto{18bp}{16bp}\n\
\t\\pgfpathqmoveto{6bp}{16bp}\\pgfpathqlineto{2bp}{24bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% vertical left shingles\n\
\\pgfdeclarepatternformonly{xfigp13}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{25bp}{25bp}}{\\pgfqpoint{24bp}{24bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{0bp}{-1bp}\\pgfpathqlineto{0bp}{25bp}\n\
\t\\pgfpathqmoveto{8bp}{-1bp}\\pgfpathqlineto{8bp}{25bp}\n\
\t\\pgfpathqmoveto{16bp}{-1bp}\\pgfpathqlineto{16bp}{25bp}\n\
\t\\pgfpathqmoveto{0bp}{14bp}\\pgfpathqlineto{8bp}{10bp}\n\
\t\\pgfpathqmoveto{8bp}{22bp}\\pgfpathqlineto{16bp}{18bp}\n\
\t\\pgfpathqmoveto{16bp}{6bp}\\pgfpathqlineto{24bp}{2bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% vertical right shingles\n\
\\pgfdeclarepatternformonly{xfigp14}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{25bp}{25bp}}{\\pgfqpoint{24bp}{24bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{0bp}{-1bp}\\pgfpathqlineto{0bp}{25bp}\n\
\t\\pgfpathqmoveto{8bp}{-1bp}\\pgfpathqlineto{8bp}{25bp}\n\
\t\\pgfpathqmoveto{16bp}{-1bp}\\pgfpathqlineto{16bp}{25bp}\n\
\t\\pgfpathqmoveto{0bp}{10bp}\\pgfpathqlineto{8bp}{14bp}\n\
\t\\pgfpathqmoveto{8bp}{2bp}\\pgfpathqlineto{16bp}{6bp}\n\
\t\\pgfpathqmoveto{16bp}{18bp}\\pgfpathqlineto{24bp}{22bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% fishscales\n\
\\pgfdeclarepatternformonly{xfigp15}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{17bp}{9bp}}{\\pgfqpoint{16bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\draw(8bp,0bp) arc [radius=10bp,start angle=270,end angle=216.87]\n\
\t\t(8bp,0bp) arc [radius=10bp,start angle=270,end angle=323.13]\n\
\t\t(0bp,4bp) arc [radius=10bp,start angle=270,end angle=323.13]\n\
\t\t(16bp,4bp) arc [radius=10bp,start angle=270,end angle=216.87];\n}\n",\
"% small fishscales\n\
\\pgfdeclarepatternformonly{xfigp16}\n\
{\\pgfqpoint{-1bp}{-1bp}}{\\pgfqpoint{9bp}{9bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetlinewidth{0.45bp}\n\
\t\\draw(0bp,4bp) arc [radius=4bp,start angle=180,end angle=360]\n\
\t\t(4bp,8bp) arc [radius=4bp,start angle=360,end angle=270]\n\
\t\t(4bp,8bp) arc [radius=4bp,start angle=180,end angle=270];\n}\n",\
"% circles\n\
\\pgfdeclarepatternformonly{xfigp17}\n\
{\\pgfqpoint{-9bp}{-9bp}}{\\pgfqpoint{8bp}{8bp}}{\\pgfqpoint{16bp}{16bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqcircle{8bp}\\pgfusepathqstroke\n}\n",\
"% hexagons\n\
\\pgfdeclarepatternformonly{xfigp18}\n\
{\\pgfqpoint{-5bp}{-1bp}}{\\pgfqpoint{23bp}{16bp}}{\\pgfqpoint{27bp}{15.6bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetmiterjoin\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathmoveto{0bp}{15.6bp}\\pgfpathqlineto{-4.5bp}{7.8bp}\n\
\t\\pgfpathqlineto{0bp}{0bp}\\pgfpathqlineto{9bp}{0bp}\n\
\t\\pgfpathqlineto{13.5bp}{7.8bp}\\pgfpathqlineto{9bp}{15.6bp}\n\
\t\\pgfpathqmoveto{13.5bp}{7.8bp}\\pgfpathqlineto{22.5bp}{7.8bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% octagons\n\
\\pgfdeclarepatternformonly{xfigp19}\n\
{\\pgfqpoint{-8bp}{-8bp}}{\\pgfqpoint{8bp}{8bp}}{\\pgfqpoint{15.84bp}{15.84bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetbuttcap\\pgfsetmiterjoin\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{-8bp}{0bp}\\pgfpathqlineto{-4.64bp}{0bp}\n\
\t\\pgfpathqlineto{0bp}{-4.64bp}\\pgfpathqlineto{4.64bp}{0bp}\n\
\t\\pgfpathqlineto{0bp}{4.64bp}\\pgfpathqlineto{-4.64bp}{0bp}\n\
\t\\pgfpathqmoveto{0bp}{-8bp}\\pgfpathqlineto{0bp}{-4.64bp}\n\
\t\\pgfpathqmoveto{0bp}{8bp}\\pgfpathqlineto{0bp}{4.64bp}\n\
\t\\pgfpathqmoveto{8bp}{0bp}\\pgfpathqlineto{4.64bp}{0bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% horizontal sawtooth lines / tire threads\n\
\\pgfdeclarepatternformonly{xfigp20}\n\
{\\pgfpointorigin}{\\pgfqpoint{9bp}{6bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetmiterjoin\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{0bp}{3bp}\\pgfpathqlineto{2bp}{5bp}\n\
\t\\pgfpathqlineto{6bp}{1bp}\\pgfpathqlineto{9bp}{4bp}\n\
\t\\pgfusepathqstroke\n}\n",\
"% vertical sawtooth lines / tire threads\n\
\\pgfdeclarepatternformonly{xfigp21}\n\
{\\pgfpointorigin}{\\pgfqpoint{6bp}{9bp}}{\\pgfqpoint{8bp}{8bp}}\n\
{\t\\pgfsetdash{}{0pt}\\pgfsetmiterjoin\\pgfsetlinewidth{0.45bp}\n\
\t\\pgfpathqmoveto{3bp}{0bp}\\pgfpathqlineto{5bp}{2bp}\n\
\t\\pgfpathqlineto{1bp}{6bp}\\pgfpathqlineto{4bp}{9bp}\n\
\t\\pgfusepathqstroke\n}\n"
