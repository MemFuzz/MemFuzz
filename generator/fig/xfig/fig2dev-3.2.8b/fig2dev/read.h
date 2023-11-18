/*
 * Parts Copyright (c) 2015-2017 by Thomas Loimer
 * Copyright (c) 1991 by Micah Beck
 * Parts Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 2015-2019 by Thomas Loimer
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

#ifndef READ_H
#define READ_H

extern int	read_fig(char *file_name, F_compound *obj);
extern int	readfp_fig(FILE *fp, F_compound *obj);
extern void	read_fail_message(char *file, int err);
extern int	read_1_3_objects(FILE *fp, F_compound *obj);

#endif /* READ_H */
