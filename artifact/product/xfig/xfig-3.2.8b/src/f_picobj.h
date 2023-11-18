/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2020 by Thomas Loimer
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

#ifndef F_PICOBJ_H
#define F_PICOBJ_H

#if defined HAVE_CONFIG_H && !defined VERSION
#include "config.h"		/* restrict */
#endif

#include <stdio.h>
#include <X11/Intrinsic.h>	/* Boolean */

#include "object.h"		/* F_pic */

/*
 * The xfig_stream struct either refers to a file, or to a pipe obtained by
 * uncompressing a compressed file. In addition, the uncompressed content
 * may be provided.
 */
struct xfig_stream {
	FILE	*fp;		/* NULL, if not open */
	char	*name;		/* e.g., image.ppm */
	char	*name_on_disk;	/* e.g., image.ppm.gz */
	char	*content;	/* points to a regular file containing the
				   uncompressed content of name */
	const char *uncompress;	/* e.g., "gunzip -c", "", or NULL
				   NULL if compression status is undecided */
	char	name_buf[128];
	char	name_on_disk_buf[128];
	char	content_buf[128];
	/* regular file, if *uncompress == '\0' */
};

extern void	read_picobj(F_pic *pic, char *file, int color, Boolean force,
				Boolean *existing);
extern void	image_size(int *size_x, int *size_y, int pixels_x, int pixels_y,
				char unit, float res_x, float res_y);

extern FILE	*open_stream(char *restrict name,
				struct xfig_stream *restrict xf_stream);
extern int	close_stream(struct xfig_stream *restrict xf_stream);
extern FILE	*rewind_stream(struct xfig_stream *restrict xf_stream);
extern int	uncompressed_content(struct xfig_stream *restrict xf_stream);
extern void	free_stream(struct xfig_stream *restrict xf_stream);

#endif
