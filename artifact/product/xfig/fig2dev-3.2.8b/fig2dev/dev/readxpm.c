/*
 * Fig2dev: Translate Fig code to various Devices
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2020 by Thomas Loimer
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

/*
 * readxpm.c: import xpm into PostScript
 *
 */

#include <stdio.h>
#include <stdlib.h>	/* size_t */
#include <string.h>
#include <unistd.h>

#include "fig2dev.h"
#include "object.h"
#include "messages.h"
#include "readpics.h"
#include "xtmpfile.h"

extern	int	 _read_pcx(FILE *pcxfile, F_pic *pic);		/* readpcx.c */


/* return codes:  1 : success
		  0 : invalid file
*/
int
read_xpm(F_pic *pic, struct xfig_stream *restrict pic_stream, int *llx,int *lly)
{
	int		stat;
	size_t		size;
	char		buf[BUFSIZ];
	char		pcxname_buf[128] = "f2dpcxXXXXXX";
	char		*pcxname = pcxname_buf;
	char		*cmd = buf;
	static char	*cmd_fmt = NULL;
	FILE		*pcx;
	FILE		*xpmtopcx;

	if (!rewind_stream(pic_stream))
		return 0;

	if (cmd_fmt == NULL) {
		if (!system("{ xpmtoppm -version && ppmtopcx -version; } "
								"2>/dev/null"))
			cmd_fmt = "xpmtoppm | ppmtopcx -quiet >'%s'";
		else if (!system("convert -version >/dev/null"))
			cmd_fmt = "convert - pcx:'%s'";
		else if (!system("gm convert -version >/dev/null"))
			cmd_fmt = "gm convert - pcx:'%s'";
		else {
			cmd_fmt = "";
			put_msg("Cannot read xpm files.\nTo read xpm image "
				"files, install either the netpbm, or the "
				"imagemagick,\nor the graphicsmagick package.");
			return 0;
		}
	}
	if (*cmd_fmt == '\0')
		return 0;

	*llx = *lly = 0;

	fprintf(tfp, "%% Originally from a XPM File: %s\n\n", pic->file);

	/* create a temporary file */
	if ((pcx = xtmpfile(&pcxname, sizeof pcxname_buf)) == NULL) {
		if (pcxname != pcxname_buf)
			free(pcxname);
		return 0;
	}
#define REMOVE_PCXFILE				\
	do {	fclose(pcx);	unlink(pcxname);\
		if (pcxname != pcxname_buf)	\
			free(pcxname);		\
	} while (0)

	/* construct a pipe to convert the xpm to a pcx in a temporary file */
	if ((size = strlen(cmd_fmt) + strlen(pcxname) > sizeof buf) &&
			(cmd = malloc(size - 1)) == NULL) {
		REMOVE_PCXFILE;
		return 0;
	}
	sprintf(cmd, cmd_fmt, pcxname);

	xpmtopcx = popen(cmd, "w");
	if (xpmtopcx == NULL) {
		err_msg("Cannot convert xpm to pcx, %s", cmd);
		REMOVE_PCXFILE;
		if (cmd != buf)
			free(cmd);
		return 0;
	}
	if (cmd != buf)
		free(cmd);

	if (!rewind_stream(pic_stream)) {
		REMOVE_PCXFILE;
		return 0;
	}
	/* write to the pipe */
	while ((size = fread(buf, 1, sizeof buf, pic_stream->fp)) != 0)
		fwrite(buf, size, 1, xpmtopcx);

	if (pclose(xpmtopcx)) {
		err_msg("Could not read xpm file '%s'", pic->file);
		REMOVE_PCXFILE;
		return 0;
	}

	/* read the pcx file that was generated above */
	rewind(pcx);
	stat = _read_pcx(pcx, pic);
	REMOVE_PCXFILE;

	return stat;
}
