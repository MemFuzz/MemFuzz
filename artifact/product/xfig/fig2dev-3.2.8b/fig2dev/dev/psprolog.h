/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
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
 *
 */

#define		BEGIN_PROLOG1	"\
/$F2psDict 200 dict def\n\
$F2psDict begin\n\
$F2psDict /mtrx matrix put\n\
/col-1 {0 setgray} bind def\n"

#define		BEGIN_PROLOG2	"\
/cp {closepath} bind def\n\
/ef {eofill} bind def\n\
/gr {grestore} bind def\n\
/gs {gsave} bind def\n\
/sa {save} bind def\n\
/rs {restore} bind def\n\
/l {lineto} bind def\n\
/rl {rlineto} bind def\n\
/m {moveto} bind def\n\
/rm {rmoveto} bind def\n\
/n {newpath} bind def\n\
/s {stroke} bind def\n\
/sh {show} bind def\n\
/slc {setlinecap} bind def\n\
/slj {setlinejoin} bind def\n\
/slw {setlinewidth} bind def\n\
/srgb {setrgbcolor} bind def\n\
/rot {rotate} bind def\n\
/sc {scale} bind def\n\
/sd {setdash} bind def\n\
/ff {findfont} bind def\n\
/sf {setfont} bind def\n\
/scf {scalefont} bind def\n\
/sw {stringwidth} bind def\n\
/tr {translate} bind def\n\
/tnt {dup dup currentrgbcolor\n\
  4 -2 roll dup 1 exch sub 3 -1 roll mul add\n\
  4 -2 roll dup 1 exch sub 3 -1 roll mul add\n\
  4 -2 roll dup 1 exch sub 3 -1 roll mul add srgb}\n\
  bind def\n\
/shd {dup dup currentrgbcolor 4 -2 roll mul 4 -2 roll mul\n\
  4 -2 roll mul srgb} bind def\n\
/xfig_image {image Data flushfile} def\n"

#define		FILL_PAT01	"\
% left30\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 48 24]\n\
 /XStep 48\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .7 slw n\n\
  3 4 24 {dup -2 exch m 2 mul -1 l} for\n\
  1 4 22 {dup 2 mul 25 m 50 exch l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P1 exch def\n"
/*
 * % the line above
 *    3 4 24 {dup -2 exch m 2 mul -1 l} for	% is equivalent to ...
 * %	-2  3 m   6 -1 l
 * %	-2  7 m  14 -1 l
 * %	-2 11 m  22 -1 l
 * %		.
 * %		.
 * %	-2 23 m  46 -1 l
 *
 *    1 4 22 {dup 2 mul 25 m 50 exch l} for	% equivalent to ...
 * %	 2 25 m  50  1 l
 * %	10 25 m  50  5 l
 * %	18 25 m  50  9 l
 * %		.
 * %		.
 * %	42 25 m  50 21 l
 */

#define		FILL_PAT02	"\
% right30\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 48 24]\n\
 /XStep 48\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .7 slw n\n\
  -3 -4 -24 {dup -2 exch 24 add m -2 mul 25 l} for\n\
  -1 -4 -22 {dup -2 mul -1 m 50 exch 24 add l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P2 exch def\n"
/*
 * % the line above
 *   -3 -4 -24 {dup -2 exch 24 add m -2 mul 25 l} for	% is equivalent to ...
 * %	-2 21 m   6 25 l
 * %	-2 17 m  14 25 l
 * %	-2 13 m  22 25 l
 * %		.
 * %		.
 * %	-2  1 m  46 25 l
 *
 *   -1 -4 -22 {dup -2 mul -1 m 50 exch 24 add l} for	% equivalent to ...
 * %	 2 -1 m  50 23 l
 * %	10 -1 m  50 19 l
 * %	18 -1 m  50 15 l
 * %		.
 * %		.
 * %	42 -1 m  50  3 l
 */

#define		FILL_PAT03	"\
% crosshatch30\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 48 24]\n\
 /XStep 48\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .7 slw n\n\
  3 4 24 {dup 2 copy -2 exch m 2 mul -1 l -2 exch -1 mul 24 add m 2 mul 25 l} for\n\
  1 4 22 {dup 2 copy 2 mul 25 m 50 exch l 2 mul -1 m 50 exch -1 mul 24 add l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P3 exch def\n"

#define		FILL_PAT04	"\
% left45\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw n\n\
  7 8 24 {dup dup -1 exch m -1 l -2 add dup 25 m 25 exch l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P4 exch def\n"
/*
 * the procedure above was
 *  7 8 24 {dup -1 exch m -1 l} for\n\
 *  5 8 22 {dup 25 m 25 exch l} for\n\
 * equivalent to
 *  -1 7 m 7 -1 l  -1 15 m 15 -1 l  -1 23 m 23 -1 l
 *   5 25 m 25 5 l  13 25 m 25 13 l  21 25 m 25 21 l
 */

#define		FILL_PAT05	"\
% right45\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw n\n\
  1 8 18 {dup dup -1 m 25 exch -1 mul 24 add l 4 add dup -1 exch m\
 -1 mul 24 add 25 l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P5 exch def\n"

#define		FILL_PAT06	"\
% crosshatch45\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24] \n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw n\n\
  1 8 18 {dup 2 copy -1 m 25 exch -1 mul 24 add l 4 add dup -1 exch m\
 -1 mul 24 add 25 l\n\
    dup 6 add dup -1 exch m -1 l 4 add dup 25 m 25 exch l} for\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P6 exch def\n"

#define		FILL_PAT07	"\
% bricks\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 32 32]\n\
 /XStep 32\n\
 /YStep 32\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 4 {dup -1 exch m 34 0 rl 8 add} repeat pop\n\
  2 2 {dup 2 m 0 8 rl 0 8 rm 0 8 rl 16 add} repeat pop\n\
  10 2 {dup -1 m 0 3 rl 0 8 rm 0 8 rl 0 8 rm 0 7 rl 16 add} repeat pop\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P7 exch def\n"

#define		FILL_PAT08	"\
% vertical bricks\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 32 32]\n\
 /XStep 32\n\
 /YStep 32\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 4 {dup -1 m 0 34 rl 8 add} repeat pop\n\
  2 2 {dup 2 exch m 8 0 rl 8 0 rm 8 0 rl 16 add} repeat pop\n\
  10 2 {dup -1 exch m 3 0 rl 8 0 rm 8 0 rl 8 0 rm 7 0 rl 16 add} repeat pop\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P8 exch def\n"

#define		FILL_PAT09	"\
% horizontal lines\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 36 24]\n\
 /XStep 36\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  -2 6 {4 add dup -1 exch m 38 0 rl} repeat pop s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P9 exch def"

#define		FILL_PAT10	"\
% vertical lines\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 36]\n\
 /XStep 24\n\
 /YStep 36\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  -2 6 {4 add dup -1 m 0 38 rl} repeat pop s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P10 exch def\n"

#define		FILL_PAT11	"\
% crosshatch lines\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 36 36]\n\
 /XStep 36\n\
 /YStep 36\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  -2 9 {4 add dup dup -1 exch m 38 0 rl -1 m 0 38 rl} repeat pop s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P11 exch def\n"

#define		FILL_PAT12	"\
% left-shingles\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 3 {dup -1 exch m 26 0 rl 8 add} repeat pop\n\
  2 10 m 6 18 l 10 2 m 14 10 l 18 18 m 22 26 l 20 -2 m 22 2 l\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P12 exch def\n"

#define		FILL_PAT13	"\
% right-shingles\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 3 {dup -1 exch m 26 0 rl 8 add} repeat pop\n\
  2 26 m 6 18 l 14 2 m 10 10 l 18 18 m 22 10 l 2 2 m 4 -2 l\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P13 exch def\n"

#define		FILL_PAT14	"\
% vertical left-shingles\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 3 {dup -1 m 0 26 rl 8 add} repeat pop\n\
  26 2 m 18 6 l 2 14 m 10 10 l 18 18 m 10 22 l 2 2 m -2 4 l\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P14 exch def\n"

#define		FILL_PAT15	"\
% vertical right-shingles\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  1 slw 0 slc n\n\
  2 3 {dup -1 m 0 26 rl 8 add} repeat pop\n\
  10 2 m 18 6 l 2 10 m 10 14 l 18 18 m 26 22 l -2 20 m 2 22 l\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P15 exch def\n"

#define		FILL_PAT16	"\
% fishscales\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 16 8]\n\
 /XStep 16\n\
 /YStep 8\n\
 /PaintProc\n\
 {\n\
  pop\n\
  0.7 slw 0 slc\n\
  8 9 8 17 8 25 0 13 16 13 0 21 16 21 7 {n 11 223 317 arc s} repeat\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P16 exch def\n"

#define		FILL_PAT17	"\
% small fishscales\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 16]\n\
 /XStep 24\n\
 /YStep 16\n\
 /PaintProc\n\
 {\n\
  pop\n\
  0.7 slw 0 slc 2 slj\n\
  n -6 8 27 {2 4 180 360 arc} for s\n\
  n -2 8 23 {6 4 180 360 arc} for s\n\
  n -6 8 27 {10 4 180 360 arc} for s\n\
  n -2 8 23 {14 4 180 360 arc} for s\n\
  n -6 8 27 {18 4 180 360 arc} for s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P17 exch def\n"

#define		FILL_PAT18	"\
% circles\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 16 16]\n\
 /XStep 16\n\
 /YStep 16\n\
 /PaintProc\n\
 {\n\
  pop\n\
  0.7 slw\n\
  n 8 8 8 0 360 arc s\n\
 } bind\n\
>>\n\
\n\
matrix\n\
makepattern\n\
/P18 exch def\n"

#define		FILL_PAT19	"\
% hexagons\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 26 16]\n\
 /XStep 26\n\
 /YStep 16\n\
 /PaintProc\n\
 {\n\
  pop\n\
  0.7 slw 0 slj n\n\
  -1 8 m 2 8 l 6 0 l 15 0 l 19 8 l 15 16 l 6 16 l 2 8 l\n\
  19 8 m 27 8 l s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P19 exch def\n"

#define		FILL_PAT20	"\
% octagons\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 16 16]\n\
 /XStep 16\n\
 /YStep 16\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .8 slw 0 slj n\n\
  5 0 m 11 0 l 16 5 l 16 11 l 11 16 l 5 16 l 0 11 l 0 5 l cp s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P20 exch def\n"

#define		FILL_PAT21	"\
% horizontal sawtooth lines\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .8 slw 0 slj n\n\
  -1 5 m 2 2 l 3 {4 4 rl 4 -4 rl} repeat\n\
  -1 13 m 2 10 l 3 {4 4 rl 4 -4 rl} repeat\n\
  -1 21 m 2 18 l 3 {4 4 rl 4 -4 rl} repeat\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P21 exch def\n"

#define		FILL_PAT22	"\
% vertical sawtooth lines\n\
<<\n\
 /PatternType 1\n\
 /PaintType 2\n\
 /TilingType 1\n\
 /BBox [0 0 24 24]\n\
 /XStep 24\n\
 /YStep 24\n\
 /PaintProc\n\
 {\n\
  pop\n\
  .8 slw 0 slj n\n\
  5 -1 m 2 2 l 3 {4 4 rl -4 4 rl} repeat\n\
  13 -1 m 10 2 l 3 {4 4 rl -4 4 rl} repeat\n\
  21 -1 m 18 2 l 3 {4 4 rl -4 4 rl} repeat\n\
  s\n\
 } bind\n\
>>\n\
matrix\n\
makepattern\n\
/P22 exch def\n"


#define		SPECIAL_CHAR_1	"\
/reencdict 12 dict def /ReEncode { reencdict begin\n\
/newcodesandnames exch def /newfontname exch def /basefontname exch def\n\
/basefontdict basefontname findfont def /newfont basefontdict maxlength dict def\n\
basefontdict { exch dup /FID ne { dup /Encoding eq\n\
{ exch dup length array copy newfont 3 1 roll put }\n\
{ exch newfont 3 1 roll put } ifelse } { pop pop } ifelse } forall\n\
newfont /FontName newfontname put newcodesandnames aload pop\n\
128 1 255 { newfont /Encoding get exch /.notdef put } for\n\
newcodesandnames length 2 idiv { newfont /Encoding get 3 1 roll put } repeat\n\
newfontname newfont definefont pop end } def\n\
/isovec [\n\
"
#define		SPECIAL_CHAR_2	"\
8#055 /minus 8#200 /grave 8#201 /acute 8#202 /circumflex 8#203 /tilde\n\
8#204 /macron 8#205 /breve 8#206 /dotaccent 8#207 /dieresis\n\
8#210 /ring 8#211 /cedilla 8#212 /hungarumlaut 8#213 /ogonek 8#214 /caron\n\
8#220 /dotlessi 8#230 /oe 8#231 /OE\n\
8#240 /space 8#241 /exclamdown 8#242 /cent 8#243 /sterling\n\
8#244 /currency 8#245 /yen 8#246 /brokenbar 8#247 /section 8#250 /dieresis\n\
8#251 /copyright 8#252 /ordfeminine 8#253 /guillemotleft 8#254 /logicalnot\n\
8#255 /hyphen 8#256 /registered 8#257 /macron 8#260 /degree 8#261 /plusminus\n\
8#262 /twosuperior 8#263 /threesuperior 8#264 /acute 8#265 /mu 8#266 /paragraph\n\
8#267 /periodcentered 8#270 /cedilla 8#271 /onesuperior 8#272 /ordmasculine\n\
8#273 /guillemotright 8#274 /onequarter 8#275 /onehalf\n\
8#276 /threequarters 8#277 /questiondown 8#300 /Agrave 8#301 /Aacute\n\
8#302 /Acircumflex 8#303 /Atilde 8#304 /Adieresis 8#305 /Aring\n\
"
#define		SPECIAL_CHAR_3	"\
8#306 /AE 8#307 /Ccedilla 8#310 /Egrave 8#311 /Eacute\n\
8#312 /Ecircumflex 8#313 /Edieresis 8#314 /Igrave 8#315 /Iacute\n\
8#316 /Icircumflex 8#317 /Idieresis 8#320 /Eth 8#321 /Ntilde 8#322 /Ograve\n\
8#323 /Oacute 8#324 /Ocircumflex 8#325 /Otilde 8#326 /Odieresis 8#327 /multiply\n\
8#330 /Oslash 8#331 /Ugrave 8#332 /Uacute 8#333 /Ucircumflex\n\
8#334 /Udieresis 8#335 /Yacute 8#336 /Thorn 8#337 /germandbls 8#340 /agrave\n\
8#341 /aacute 8#342 /acircumflex 8#343 /atilde 8#344 /adieresis 8#345 /aring\n\
8#346 /ae 8#347 /ccedilla 8#350 /egrave 8#351 /eacute\n\
8#352 /ecircumflex 8#353 /edieresis 8#354 /igrave 8#355 /iacute\n\
8#356 /icircumflex 8#357 /idieresis 8#360 /eth 8#361 /ntilde 8#362 /ograve\n\
8#363 /oacute 8#364 /ocircumflex 8#365 /otilde 8#366 /odieresis 8#367 /divide\n\
8#370 /oslash 8#371 /ugrave 8#372 /uacute 8#373 /ucircumflex\n\
8#374 /udieresis 8#375 /yacute 8#376 /thorn 8#377 /ydieresis\
] def\n\
"

#define		ELLIPSE_PS	" \
/DrawEllipse {\n\
	/endangle exch def\n\
	/startangle exch def\n\
	/yrad exch def\n\
	/xrad exch def\n\
	/y exch def\n\
	/x exch def\n\
	/savematrix mtrx currentmatrix def\n\
	x y tr xrad yrad sc 0 0 1 startangle endangle arc\n\
	closepath\n\
	savematrix setmatrix\n\
	} def\n\
"
/* The original PostScript definition for adding a spline section to the
 * current path uses recursive bisection.  The following definition using the
 * curveto operator is more efficient since it executes at compiled rather
 * than interpreted code speed.  The Bezier control points are 2/3 of the way
 * from z1 (and z3) to z2.
 *
 * ---Rene Llames, 21 July 1988.
 */
#define		SPLINE_PS	" \
/DrawSplineSection {\n\
	/y3 exch def\n\
	/x3 exch def\n\
	/y2 exch def\n\
	/x2 exch def\n\
	/y1 exch def\n\
	/x1 exch def\n\
	/xa x1 x2 x1 sub 0.666667 mul add def\n\
	/ya y1 y2 y1 sub 0.666667 mul add def\n\
	/xb x3 x2 x3 sub 0.666667 mul add def\n\
	/yb y3 y2 y3 sub 0.666667 mul add def\n\
	x1 y1 lineto\n\
	xa ya xb yb x3 y3 curveto\n\
	} def\n\
"
#define		END_PROLOG	"\
/$F2psBegin {$F2psDict begin /$F2psEnteredState save def} def\n\
/$F2psEnd {$F2psEnteredState restore end} def\n\
"
