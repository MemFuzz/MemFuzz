/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2018 by Thomas Loimer
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

extern Boolean	print_all_layers;
extern Boolean	bound_active_layers;
extern Boolean	print_hpgl_pcl_switch;
extern Boolean	hpgl_specified_font;
extern Boolean	pdf_pagemode;
extern int	preview_type;
extern void	print_to_printer(char *printer, char *backgrnd, float mag,
			Boolean print_all_layers, Boolean bound_active_layers,
			char *grid, char *params);
extern int	print_to_file(char *file, int xoff, int yoff, char *backgrnd,
			char *transparent, Boolean use_transp_backg, int border,
			char *grid);
extern void	make_rgb_string (int color, char *rgb_string);
extern void	gen_print_cmd(char *cmd, char *file, char *printer,
				char *pr_params);
