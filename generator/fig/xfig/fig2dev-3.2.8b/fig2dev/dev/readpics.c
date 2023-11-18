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

/*
 * readpics.c: read image files
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "readpics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "messages.h"
#include "xtmpfile.h"


void
init_stream(struct xfig_stream *restrict xf_stream)
{
	xf_stream->fp = NULL;
	xf_stream->name = xf_stream->name_buf;
	xf_stream->name_on_disk = xf_stream->name_on_disk_buf;
	xf_stream->uncompress = NULL;
	xf_stream->content = xf_stream->content_buf;
	*xf_stream->content = '\0';
}

void
free_stream(struct xfig_stream *restrict xf_stream)
{
	if (xf_stream->content != xf_stream->name_on_disk) {
		if (*xf_stream->content && unlink(xf_stream->content)) {
			err_msg("Cannot remove temporary file %s",
					xf_stream->content);
		}
		if (xf_stream->content != xf_stream->content_buf) {
			free(xf_stream->content);
			xf_stream->content = xf_stream->content_buf;
		}
	}
	if (xf_stream->name != xf_stream->name_buf) {
		free(xf_stream->name);
		xf_stream->name = xf_stream->name_buf;
	}
	if (xf_stream->name_on_disk != xf_stream->name_on_disk_buf) {
		free(xf_stream->name_on_disk);
		xf_stream->name_on_disk = xf_stream->name_on_disk_buf;
	}
}

/*
 * Given name, search and return the name of the corresponding file on disk in
 * found. This may be "name", or "name" with a compression suffix appended,
 * e.g., "name.gz". If the file must be uncompressed, return the compression
 * command in a static string pointed to by "uncompress", otherwise let
 * "uncompress" point to the empty string. If the size of the character buffer
 * provided in found is too small to accomodate the string, return a pointer to
 * a malloc()'ed string.
 * Return 0 on success, -1 on failure.
 * Usage:
 *	char	found_buf[len];
 *	char	*found = found_buf;
 *	file_on_disk(name, &found, sizeof found_buf, &uncompress);
 *	...
 *	if (found != found_buf)
 *		free(found);
 */
static int
file_on_disk(char *restrict name, char *restrict *found, size_t len,
		const char *restrict *uncompress)
{
	int		i;
	size_t		name_len;
	char		*suffix;
	struct stat	status;
	static const char	empty[] = "";
	static char *const	filetypes[][2] = {
		/* sorted by popularity? */
#define FILEONDISK_ADD	5	/* must be max(strlen(filetypes[0][])) + 1 */
		{ ".gz",	"gunzip -c" },
		{ ".Z",		"gunzip -c" },
		{ ".z",		"gunzip -c" },
		{ ".zip",	"unzip -p"  },
		{ ".bz2",	"bunzip2 -c" },
		{ ".bz",	"bunzip2 -c" },
		{ ".xz",	"unxz -c" }
	};
	const int	filetypes_len =
				(int)(sizeof filetypes / sizeof(filetypes[1]));

	name_len = strlen(name);
	if (name_len >= len &&
			(*found = malloc(name_len + FILEONDISK_ADD)) == NULL) {
		put_msg(Err_mem);
		return -1;
	}

	strcpy(*found, name);

	/*
	 * Possibilities, e.g.,
	 *	name		name on disk		uncompress
	 *	img.ppm		img.ppm			""
	 *	img.ppm		img.ppm.gz		gunzip -c
	 *	img.ppm.gz	img.ppm.gz		gunzip -c
	 *	img.ppm.gz	img.ppm			""
	 */
	if (stat(name, &status)) {
		/* File not found. Now try, whether a file with one of
		   the known suffices appended exists. */
		if (len > name_len && len < name_len + FILEONDISK_ADD &&
				(*found = malloc(name_len + FILEONDISK_ADD))
				== NULL) {
			put_msg(Err_mem);
			return -1;
		}
		suffix = *found + name_len;
		for (i = 0; i < filetypes_len; ++i) {
			strcpy(suffix, filetypes[i][0]);
			if (!stat(*found, &status)) {
				*uncompress = filetypes[i][1];
				break;
			}
		}

		/* Not found. Check, whether the file has one of the known
		   compression suffices, but the uncompressed file
		   exists on disk. */
		*suffix = '\0';
		if (i == filetypes_len && (suffix = strrchr(name, '.'))) {
			for (i = 0; i < filetypes_len; ++i) {
				if (!strcmp(suffix, filetypes[i][0])) {
					*(*found + (suffix - name)) = '\0';
					if (!stat(*found, &status)) {
						*uncompress = empty;
						break;
					} else {
						*found[0] = '\0';
						i = filetypes_len;
					}
				}
			}
		}

		if (i == filetypes_len) {
			/* not found */
			*found[0] = '\0';
			return -1;
		}
	} else {
		/* File exists. Check, whether the name has one of the known
		   compression suffices. */
		if ((suffix = strrchr(name, '.'))) {
			for (i = 0; i < filetypes_len; ++i) {
				if (!strcmp(suffix, filetypes[i][0])) {
					*uncompress = filetypes[i][1];
					break;
				}
			}
		} else {
			i = filetypes_len;
		}

		if (i == filetypes_len)
			*uncompress = empty;
	}

	return 0;
}

/*
 * Return a file stream, either to a pipe or to a regular file.
 * If xf_stream->uncompress[0] == '\0', it is a regular file, otherwise a pipe.
 */
FILE *
open_stream(char *restrict name, struct xfig_stream *restrict xf_stream)
{
	size_t	len;

	if (xf_stream->name != name) {
		/* strcpy (xf_stream->name, name) */
		len = strlen(name);
		if (len >= sizeof xf_stream->name_buf) {
			if ((xf_stream->name = malloc(len + 1)) == NULL) {
				put_msg(Err_mem);
				return NULL;
			}
		}
		memcpy(xf_stream->name, name, len + 1);
	}

	if (file_on_disk(name, &xf_stream->name_on_disk,
				sizeof xf_stream->name_on_disk_buf,
				&xf_stream->uncompress)) {

		free_stream(xf_stream);
		return NULL;
	}

	if (xf_stream->uncompress && *xf_stream->uncompress) {
		/* a compressed file */
		char	command_buf[256];
		char	*command = command_buf;

		len = strlen(xf_stream->name_on_disk) +
					strlen(xf_stream->uncompress) + 2;
		if (len > sizeof command_buf) {
			if ((command = malloc(len)) == NULL) {
				put_msg(Err_mem);
				return NULL;
			}
		}
		sprintf(command, "%s %s",
				xf_stream->uncompress, xf_stream->name_on_disk);
		xf_stream->fp = popen(command, "r");
		if (command != command_buf)
			free(command);
	} else {
		/* uncompressed file */
		xf_stream->fp = fopen(xf_stream->name_on_disk, "rb");
	}

	return xf_stream->fp;
}

/*
 * Close a file stream opened by open_file(). Do not free xf_stream.
 */
int
close_stream(struct xfig_stream *restrict xf_stream)
{
	if (xf_stream->fp == NULL)
		return -1;

	if (xf_stream->uncompress[0] == '\0') {
		/* a regular file */
		return fclose(xf_stream->fp);
	} else {
		/* a pipe */
		char	trash[BUFSIZ];
		int	status;
		/* for a pipe, must read everything or
		   we'll get a broken pipe message */
		while (fread(trash, (size_t)1, (size_t)BUFSIZ, xf_stream->fp) ==
				(size_t)BUFSIZ)
			;
		status = pclose(xf_stream->fp);
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
		else
			return -1;
	}
}

FILE *
rewind_stream(struct xfig_stream *restrict xf_stream)
{
	if (xf_stream->fp == NULL)
		return NULL;

	if (xf_stream->uncompress[0] == '\0') {
		/* a regular file */
		rewind(xf_stream->fp);
		return xf_stream->fp;
	} else  {
		/* a pipe */
		(void)close_stream(xf_stream);
		/* if, in the meantime, e.g., the file on disk
		   was uncompressed, change the filetype. */
		return open_stream(xf_stream->name, xf_stream);
	}
}

/*
 * Have xf_stream->content either point to a regular file containing the
 * uncompressed content of xf_stream->name, or to xf_stream->name_on_disk, if
 * name_on_disk is not compressed.
 * Return 0 on succes, -1 on failure.
 * Use after a call to open_stream():
 *	struct xfig_stream	xf_stream;
 *	open_stream(name, &xf_stream);
 *	close_stream(&xf_stream);
 *	uncompressed_content(&xf_stream)
 *	do_something(xf_stream->content);
 *	free_stream(&xf_stream);
 */
int
uncompressed_content(struct xfig_stream *restrict xf_stream)
{
	int		ret = -1;
	int		len;
	char		command_buf[256];
	char		*command = command_buf;
	char *const	uncompress_fmt = "%s '%s' >%s";
	FILE		*f;

	if (*xf_stream->uncompress == '\0') {
		xf_stream->content = xf_stream->name_on_disk;
		return 0;
	}

	/* return early, if uncompressed_content was already called */
	if (*xf_stream->uncompress)
		return 0;

	/* create a temporary file */
	strcpy(xf_stream->content, "f2dXXXXXX");
	f = xtmpfile(&xf_stream->content, sizeof xf_stream->content_buf);
	if (f)
		fclose(f);
	else
		return ret;

	/* uncompress to a temporary file */
	len = snprintf(command, sizeof command_buf, uncompress_fmt,
			xf_stream->uncompress, xf_stream->name_on_disk,
			xf_stream->content);
	if (len >= (int)(sizeof command_buf)) {
		if ((command = malloc(len + 1)) == NULL) {
			put_msg(Err_mem);
			return ret;
		}
		len = sprintf(command, uncompress_fmt, xf_stream->uncompress,
				xf_stream->name_on_disk, xf_stream->uncompress);
	}
	if (len < 0) {
		err_msg("Unable to write command to uncompress file");
		return ret;
	}

	if (system(command) == 0)
		ret = 0;
	else
		err_msg("Could not uncompress %s, command, %s",
				xf_stream->name_on_disk, command);

	if (command != command_buf)
		free(command);
	return ret;
}
