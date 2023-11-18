#include <stdlib.h>
#include "memfuzz.h"
int main()
{
  alloc_init();
  int *a = malloc(400);
  assign_int32_t_array_test(a, 0, 100);
  printf("%ld\n", alloc_find(a));
  free(a);
  return 0;
}
