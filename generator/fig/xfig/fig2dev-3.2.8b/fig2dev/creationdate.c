/*
 * Fig2dev: Translate Fig code to various Devices
 * Parts Copyright (c) 2016, 2017 by Thomas Loimer
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
 * creationdate.c: provide the creation time and enable reproducibe builds
 * Author: Thomas Loimer, 2016-06-28
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_STRERROR
#include <errno.h>
#endif
#include <time.h>
#include <limits.h>
#include "bool.h"

#include "creationdate.h"


int
creation_date(char *buf)
{
    time_t now;

#ifdef	HAVE_STRERROR
    char *source_date_epoch;
    unsigned long long epoch;
    char *endptr;

    source_date_epoch = getenv("SOURCE_DATE_EPOCH");
    if (source_date_epoch) {
	errno = 0;
	epoch = strtoull(source_date_epoch, &endptr, 10);
	if ((errno == ERANGE && (epoch == ULLONG_MAX || epoch == 0))
		|| (errno != 0 && epoch == 0)) {
	    fprintf(stderr,
		"Environment variable $SOURCE_DATE_EPOCH: strtoull: %s\n",
		strerror(errno));
	} else if (endptr == source_date_epoch) {
	    fprintf(stderr,
		"Environment variable $SOURCE_DATE_EPOCH: No digits were found: %s\n",
		endptr);
	} else if (*endptr != '\0') {
	    fprintf(stderr,
		"Environment variable $SOURCE_DATE_EPOCH: Trailing garbage: %s\n",
		endptr);
	} else if (epoch > ULONG_MAX) {
	    fprintf(stderr,
		"Environment variable $SOURCE_DATE_EPOCH: value must be smaller than or equal to: %lu but was found to be: %llu \n",
		ULONG_MAX, epoch);
	} else {
	    /* no errors, epoch is valid */
	    now = epoch;
	    strftime(buf, CREATION_TIME_LEN, "%F %H:%M:%S", gmtime(&now));
	    return true;
	}
    }
#endif

    /* fall trough on errors or !source_date_epoch */
    time(&now);
    if (strftime(buf, CREATION_TIME_LEN, "%F %H:%M:%S", localtime(&now)))
	return true;
    else
	return false;
}
