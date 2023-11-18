#include "header.h"
struct s {
int a;
char b;
};
int main()
{
	struct s s;
	s.a = 2;s.b=3;
	fun((void*)&s, 0);
	return 0;
}


