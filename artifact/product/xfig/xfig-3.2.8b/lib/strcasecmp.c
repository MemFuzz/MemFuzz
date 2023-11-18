/* strcasecmp by Fred Appelman (Fred.Appelman@cv.ruu.nl) */

#include <ctype.h>

int strcasecmp(const char* s1, const char* s2)
{
	char c1,c2;

	while (*s1 && *s2)
	{
		c1=toupper(*s1++);
		c2=toupper(*s2++);
		if (c1<c2) return -1; /* s1 is "smaller" */
		if (c1>c2) return +1; /* s2 is "smaller" */
	}
	/* Check for end of string, if not both the strings ended they are
	 * not the same.
	 */
	if (*s1=='\0' && *s2!='\0') return -1; /* s1 ended premature */
	if (*s1!='\0' && *s2=='\0') return +1; /* s2 ended premature */
	return 0;
}
