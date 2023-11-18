#include <stdio.h>
#include <vector>
using namespace std;
typedef  int i32;
class A{
public:
i32* a;
void gee()
{
	int a = 1 + 1;
printf("FUCK");
}
int foo()
{
	gee();
	return 2;
}
};
int main()
{
	class A a;
	a.foo();
	a.gee();
	vector<int> v;
	v.push_back(123);
	FILE *fp = fopen("t", "r");
	char buf[16];
	fread(buf, 1, 10, fp);
	fclose(fp);
	return 0;
}
