#ifndef _MEMFUZZ_HOOK_
#define _MEMFUZZ_HOOK_ 

#include <stdlib.h>

void alloc_print_info(void);
void alloc_init(void);
size_t alloc_find(void* ptr);
void alloc_stop_trace();
void alloc_begin_trace();
#endif
