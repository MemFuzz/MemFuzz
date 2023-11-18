#include <set>
struct s
{
  int a;
  char b;
};


static std::set<void*> dedup;

  static void cppfun(void *ptr,int level)
  {
    if(dedup.find(ptr) == dedup.end())
	    return ;
    struct s *ptr1 = (struct s*)ptr;
    ptr1->a = 1;
    ptr1->b = 2;
    return ;
  }

extern "C" void fun(void *ptr, int level);
void fun(void*ptr, int level)
{
  cppfun(ptr, level);
}




