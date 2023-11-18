/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2020 by Thomas Loimer
 *
 * Copyright (c) 1992 by Brian Boyter
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

/* GS bitmap generation added: 13 Nov 1992, by Michael C. Grant
*  (mcgrant@rascals.stanford.edu) adapted from Marc Goldburg's
*  (marcg@rascals.stanford.edu) original idea and code. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "f_picobj.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>		/* time_t */
#include <X11/Intrinsic.h>	/* includes X11/Xlib.h, which includes X11/X.h */

#include "resources.h"		/* TMPDIR */
#include "object.h"
#include "f_readpcx.h"		/* read_pcx() */
#include "f_util.h"		/* file_timestamp() */
#include "u_create.h"		/* create_picture_entry() */
#include "w_file.h"		/* check_cancel() */
#include "w_msgpanel.h"
#include "w_setup.h"		/* PIX_PER_INCH, PIX_PER_CM */
#include "w_util.h"		/* app_flush() */

extern	int	read_gif(F_pic *pic, struct xfig_stream *restrict pic_stream);
extern	int	read_eps(F_pic *pic, struct xfig_stream *restrict pic_stream);
extern	int	read_pdf(F_pic *pic, struct xfig_stream *restrict pic_stream);
extern	int	read_ppm(F_pic *pic, struct xfig_stream *restrict pic_stream);
#ifdef HAVE_TIFF
extern	int	read_tif(F_pic *pic, struct xfig_stream *restrict pic_stream);
#endif
extern	int	read_xbm(F_pic *pic, struct xfig_stream *restrict pic_stream);
#ifdef HAVE_JPEG
extern	int	read_jpg(F_pic *pic, struct xfig_stream *restrict pic_stream);
#endif
#ifdef HAVE_PNG
extern	int	read_png(F_pic *pic, struct xfig_stream *restrict pic_stream);
#endif
#ifdef USE_XPM
extern	int	read_xpm(F_pic *pic, struct xfig_stream *restrict pic_stream);
#endif


static struct _haeders {
	char	*type;
	char	*bytes;
	int	(*readfunc)();
} headers[] = {
	{"GIF",		"GIF",					read_gif},
	{"PCX",		"\012\005\001",				read_pcx},
	{"EPS",		"%!",					read_eps},
	{"PDF",		"%PDF",					read_pdf},
	{"PPM",		"P3",					read_ppm},
	{"PPM",		"P6",					read_ppm},
#ifdef HAVE_TIFF
	{"TIFF",	"II*\000",				read_tif},
	{"TIFF",	"MM\000*",				read_tif},
#endif
	{"XBM",		"#define",				read_xbm},
#ifdef HAVE_JPEG
	{"JPEG",	"\377\330\377\340",			read_jpg},
	{"JPEG",	"\377\330\377\341",			read_jpg},
#endif
#ifdef HAVE_PNG
	{"PNG",		"\211\120\116\107\015\012\032\012",	read_png},
#endif
#ifdef USE_XPM
	{"XPM",		"/* XPM */",				read_xpm},
#endif
};


static void
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
			int	err = errno;
			file_msg("Cannot remove temporary file %s\nError: %s",
					xf_stream->content, strerror(err));
		}
		if (xf_stream->content != xf_stream->content_buf)
			free(xf_stream->content);
	}
	if (xf_stream->name != xf_stream->name_buf)
		free(xf_stream->name);
	if (xf_stream->name_on_disk != xf_stream->name_on_disk_buf)
		free(xf_stream->name_on_disk);
}

/*
 * Given name, search and return the name of the corresponding file on disk in
 * found. This may be "name", or "name" with a compression suffix appended,
 * e.g., "name.gz". If the file must be uncompressed, return the compression
 * command in a static string pointed to by "uncompress", otherwise let
 * "uncompress" point to the empty string. If the size of the character buffer
 * provided in found is too small to accomodate the string, return a pointer to
 * a malloc()'ed string.
 * Return 0 on success, or FileInvalid if the file is not found.
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
	static const char empty[] = "";
	static const char *filetypes[][2] = {
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
		file_msg("Out of memory.");
		return FileInvalid;
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
		if (len < name_len + FILEONDISK_ADD && (*found =
				malloc(name_len + FILEONDISK_ADD)) == NULL) {
			file_msg("Out of memory.");
			return FileInvalid;
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
			return FileInvalid;
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
 * Compare the picture information in pic with "file". If the file on disk
 * is newer than the picture information, set "reread" to true.
 * If a cached picture bitmap already exists, set "existing" to true.
 * Return FileInvalid, if "file" is not found, otherwise return 0.
 */
static int
get_picture_status(F_pic *pic, struct _pics *pics, char *file, bool force,
		bool *reread, bool *existing)
{
	char		found_buf[256];
	char		*found = found_buf;
	const char	*uncompress;
	time_t		mtime;

	/* get the name of the file on disk */
	if (file_on_disk(pics->file, &found, sizeof found_buf, &uncompress)) {
		if (found != found_buf)
			free(found);
		return FileInvalid;
	}

	/* check the timestamp */
	mtime = file_timestamp(found);
	if (found != found_buf)
		free(found);
	if (mtime < 0) {
		/* oops, doesn't exist? */
		file_msg("Error %s on %s", strerror(errno), file);
		return FileInvalid;
	}
	if (force || mtime > pics->time_stamp) {
		if (appres.DEBUG && mtime > pics->time_stamp)
			fprintf(stderr, "Timestamp changed, reread file %s\n",
					file);
		*reread = true;
		return 0;
	}

	pic->pic_cache = pics;
	pics->refcount++;

	if (appres.DEBUG)
		fprintf(stderr, "Found stored picture %s, count=%d\n", file,
				pics->refcount);

	/* there is a cached bitmap */
	if (pics->bitmap != NULL) {
		*existing = true;
		*reread = false;
		put_msg("Reading Picture object file...found cached picture");
	} else {
		*existing = false;
		*reread = true;
		if (appres.DEBUG)
			fprintf(stderr, "Re-reading file %s\n", file);
	}
	return 0;
}

/*
 * Check through the pictures repository to see if "file" is already there.
 * If so, set the pic->pic_cache pointer to that repository entry and set
 * "existing" to True.
 * If not, read the file via the relevant reader and add to the repository
 * and set "existing" to False.
 * If "force" is true, read the file unconditionally.
 */
void
read_picobj(F_pic *pic, char *file, int color, Boolean force, Boolean *existing)
{
	FILE		*fp;
	int		i;
	char		buf[16];
	bool		reread;
	struct _pics	*pics, *lastpic;
	struct xfig_stream	pic_stream;

	pic->color = color;
	/* don't touch the flipped flag - caller has already set it */
	pic->pixmap = (Pixmap)0;
	pic->hw_ratio = 0.0;
	pic->pix_rotation = 0;
	pic->pix_width = 0;
	pic->pix_height = 0;
	pic->pix_flipped = 0;

	/* check if user pressed cancel button */
	if (check_cancel())
		return;

	put_msg("Reading Picture object file...");
	app_flush();

	/* look in the repository for this filename */
	lastpic = pictures;
	for (pics = pictures; pics; pics = pics->next) {
		if (strcmp(pics->file, file) == 0) {
			/* check, whether picture exists, or must be re-read */
			if (get_picture_status(pic, pics, file, force, &reread,
						(bool *)existing) ==FileInvalid)
				return;
			if (!reread && *existing) {
				/* must set the h/w ratio here */
				pic->hw_ratio =(float)pic->pic_cache->bit_size.y
					/ pic->pic_cache->bit_size.x;
				return;
			}
			break;
		}
		/* keep pointer to last entry */
		lastpic = pics;
	}

	if (pics == NULL) {
		/* didn't find it in the repository, add it */
		pics = create_picture_entry();
		if (lastpic) {
			/* add to list */
			lastpic->next = pics;
			pics->prev = lastpic;
		} else {
			/* first one */
			pictures = pics;
		}
		pics->file = strdup(file);
		pics->refcount = 1;
		pics->bitmap = NULL;
		pics->subtype = T_PIC_NONE;
		pics->numcols = 0;
		pics->size_x = 0;
		pics->size_y = 0;
		pics->bit_size.x = 0;
		pics->bit_size.y = 0;
		if (appres.DEBUG)
			fprintf(stderr, "New picture %s\n", file);
	}
	/* put it in the pic */
	pic->pic_cache = pics;
	pic->pixmap = (Pixmap)0;

	if (appres.DEBUG)
		fprintf(stderr, "Reading file %s\n", file);

	init_stream(&pic_stream);

	/* open the file and read a few bytes of the header to see what it is */
	if ((fp = open_stream(file, &pic_stream)) == NULL) {
		file_msg("No such picture file: %s", file);
		free_stream(&pic_stream);
		return;
	}
	/* get the modified time and save it */
	pics->time_stamp = file_timestamp(pic_stream.name_on_disk);

	/* read some bytes from the file */
	for (i = 0; i < (int)sizeof buf; ++i) {
		int	c;
		if ((c = getc(fp)) == EOF)
			break;
		buf[i] = (char)c;
	}

	/* now find which header it is */
	for (i = 0; i < (int)(sizeof headers / sizeof(headers[0])); ++i)
		if (!memcmp(buf, headers[i].bytes, strlen(headers[i].bytes)))
			break;

	/* not found */
	if (i == (int)(sizeof headers / sizeof(headers[0]))) {
		file_msg("%s: Unknown image format", file);
		put_msg("Reading Picture object file...Failed");
		app_flush();
		close_stream(&pic_stream);
		free_stream(&pic_stream);
		return;
	}

	/* readfunc() expect an open file stream, positioned not at the
	   start of the stream. The stream remains open after returning. */
	if (headers[i].readfunc(pic, &pic_stream) != PicSuccess) {
		file_msg("%s: Bad %s format", file, headers[i].type);
	} else {
		put_msg("Reading Picture object file...Done");
	}

	close_stream(&pic_stream);
	free_stream(&pic_stream);
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
				file_msg("Out of memory.");
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

	if (*xf_stream->uncompress) {
		/* a compressed file */
		char	command_buf[256];
		char	*command = command_buf;

		len = strlen(xf_stream->name_on_disk) +
					strlen(xf_stream->uncompress) + 2;
		if (len > sizeof command_buf) {
			if ((command = malloc(len)) == NULL) {
				file_msg("Out of memory.");
				return NULL;
			}
		}
		sprintf(command, "%s '%s'",
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
		/* for a pipe, must read everything or
		   we'll get a broken pipe message */
		while (fread(trash, (size_t)1, (size_t)BUFSIZ, xf_stream->fp) ==
				(size_t)BUFSIZ)
			;
		return pclose(xf_stream->fp);
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
	int		fd;
	int		len;
	char		command_buf[256];
	char		*command = command_buf;
	char *const	command_fmt = "%s '%s' 1>&%d";
	char *const	content_fmt = "%s/xfigXXXXXX";

	if (*xf_stream->uncompress == '\0') {
		xf_stream->content = xf_stream->name_on_disk;
		return 0;
	}

	/* uncompress to a temporary file */

	len = snprintf(xf_stream->content, sizeof xf_stream->content_buf,
			content_fmt, TMPDIR);
	if (len >= (int)(sizeof xf_stream->content_buf)) {
		if ((xf_stream->content = malloc(len + 1)) == NULL) {
			file_msg("Out of memory.");
			return ret;
		}
		len = sprintf(xf_stream->content, content_fmt, TMPDIR);
	}
	if (len < 0) {
		len = errno;
		file_msg("Unable to write temporary file path to string.");
		file_msg("Error: %s", strerror(len));
		return ret;
	}

	if ((fd = mkstemp(xf_stream->content)) == -1) {
		fd = errno;
		file_msg("Could not open temporary file %s, error: %s",
				xf_stream->content, strerror(fd));
		return ret;
	}

	/*
	 * One could already here redirect stdout to the fd of our tmp
	 * file - but then, how to re-open stdout?
	 *   close(1);
	 *   dup(fd);	* takes the lowest integer found, now 1 *
	 *   close(fd);
	 */
	len = snprintf(command, sizeof command_buf, command_fmt,
			xf_stream->uncompress, xf_stream->name_on_disk, fd);
	if (len >= (int)(sizeof command_buf)) {
		if ((command = malloc(len + 1)) == NULL) {
			file_msg("Out of memory.");
			close(fd);
			return ret;
		}
		len = sprintf(command, command_fmt, xf_stream->uncompress,
						xf_stream->name_on_disk, fd);
	}
	if (len < 0) {
		len = errno;
		file_msg("Unable to write command string.");
		file_msg("Error: %s", strerror(len));
		return ret;
	}

	if (system(command) == 0)
		ret = 0;
	else
		file_msg("Could not uncompress %s, command: %s",
				xf_stream->name_on_disk, command);

	close(fd);
	if (command != command_buf)
		free(command);
	return ret;
}

/*
 * Compute the image dimension (size_x, size_y) in Fig-units from the number of
 * pixels and the resolution in x- and y-direction, pixels_x, pixels_y, and
 * res_x and res_y, respectively.
 * The resolution is given in pixels / cm or pixels / inch, depending on
 * whether 'c' or 'i' is passed to unit. For any other character passed to unit,
 * a resolution of 72 pixels per inch is assumed.
 */
void
image_size(int *size_x, int *size_y, int pixels_x, int pixels_y,
		char unit, float res_x, float res_y)
{
	/* exclude negative and absurdly small values */
	if (res_x < 1. || res_y < 1.) {
		res_x = 72.0f;
		res_y = 72.0f;
		unit = 'i';
	}

	if (unit == 'i') {		/* pixel / inch */
		if (appres.INCHES) {
			*size_x = pixels_x * PIX_PER_INCH / res_x + 0.5;
			*size_y = pixels_y * PIX_PER_INCH / res_y + 0.5;
		} else {
			*size_x = pixels_x * PIX_PER_CM * 2.54 / res_x + 0.5;
			*size_y = pixels_y * PIX_PER_CM * 2.54 / res_y + 0.5;
		}
	} else if (unit == 'c') {	/* pixel / cm */
		if (appres.INCHES) {
			*size_x = pixels_x * PIX_PER_INCH / (res_x * 2.54) +0.5;
			*size_y = pixels_y * PIX_PER_INCH / (res_y * 2.54) +0.5;
		} else {
			*size_x = pixels_x * PIX_PER_CM / res_x + 0.5;
			*size_y = pixels_y * PIX_PER_CM / res_y + 0.5;
		}
	} else {			/* unknown, default to 72 ppi */
		*size_x = pixels_x * PIC_FACTOR + 0.5;
		*size_y = pixels_y * PIC_FACTOR * res_x / res_y + 0.5;
	}
}
