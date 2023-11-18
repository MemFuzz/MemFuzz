/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2021 by Thomas Loimer
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

#ifndef DRIVERS_H
#define DRIVERS_H

/* When adding or removing drivers, be sure to update transfig/transfig.c too */

extern struct driver dev_box;
extern struct driver dev_cgm;
extern struct driver dev_epic;
extern struct driver dev_ibmgl;
extern struct driver dev_latex;
extern struct driver dev_tikz;
extern struct driver dev_pict2e;
extern struct driver dev_pic;
extern struct driver dev_pictex;
extern struct driver dev_ps;
extern struct driver dev_emf;
extern struct driver dev_eps;
extern struct driver dev_pdf;
extern struct driver dev_pdftex;
extern struct driver dev_pdftex_t;
extern struct driver dev_pstex;
extern struct driver dev_pstex_t;
extern struct driver dev_pstricks;
extern struct driver dev_textyl;
extern struct driver dev_tk;
extern struct driver dev_ptk;
extern struct driver dev_tpic;
extern struct driver dev_mf;
extern struct driver dev_mp;
extern struct driver dev_ge;
extern struct driver dev_bitmaps;
extern struct driver dev_map;
extern struct driver dev_svg;
extern struct driver dev_gbx;
extern struct driver dev_shape;

extern struct driver dev_dxf;

/* all the bitmap formats use the dev_bitmaps driver */

struct {
	char		*name;
	char		*alias;
	struct driver	*dev;
/* sizeof lang[] in fig2dev.c must be larger than the
   maximum string length of a driver name */
} drivers[] = {
	{"box",		NULL,	&dev_box},
	{"cgm",		NULL,	&dev_cgm},
	{"dxf",		NULL,	&dev_dxf},
	{"eepic",	NULL,	&dev_epic},
	{"eepicemu",	NULL,	&dev_epic},
	{"emf",		NULL,	&dev_emf},
	{"epic",	NULL,	&dev_epic},
	{"eps",		NULL,	&dev_eps},
	{"gbx",		NULL,	&dev_gbx},
	{"ge",		NULL,	&dev_ge},
	{"gif",		NULL,	&dev_bitmaps},
	{"ibmgl",	NULL,	&dev_ibmgl},
	{"jpeg",	"jpg",	&dev_bitmaps},
	{"latex",	NULL,	&dev_latex},
	{"map",		NULL,	&dev_map},
	{"mf",		NULL,	&dev_mf},
	{"mp",		NULL,	&dev_mp},
	{"pcx",		NULL,	&dev_bitmaps},
	{"pdf",		NULL,	&dev_pdf},
	{"pdftex",	NULL,	&dev_pdftex},
	{"pdftex_t",	NULL,	&dev_pdftex_t},
	{"pic",		NULL,	&dev_pic},
	{"pict2e",	NULL,	&dev_pict2e},
	{"pictex",	NULL,	&dev_pictex},
	{"png",		NULL,	&dev_bitmaps},
	{"ppm",		NULL,	&dev_bitmaps},
	{"ps",		NULL,	&dev_ps},
	{"pstex",	NULL,	&dev_pstex},
	{"pstex_t",	NULL,	&dev_pstex_t},
	{"pstricks",	NULL,	&dev_pstricks},
	{"ptk",		NULL,	&dev_ptk},
	{"shape",	NULL,	&dev_shape},
	{"sld",		NULL,	&dev_bitmaps},
	{"svg",		NULL,	&dev_svg},
	{"textyl",	NULL,	&dev_textyl},
	{"tiff",	"tif",	&dev_bitmaps},
	{"tikz",	NULL,	&dev_tikz},
	{"tk",		NULL,	&dev_tk},
	{"tpic",	NULL,	&dev_tpic},
	{"xbm",		NULL,	&dev_bitmaps},
	{"xpm",		NULL,	&dev_bitmaps},
	{"",		NULL,	NULL}
};

#endif /* DRIVERS_H */
