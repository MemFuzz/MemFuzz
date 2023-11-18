#ifndef _MEMFUZZ_HOOK_
#define _MEMFUZZ_HOOK_ 

#include <stdlib.h>

static void* my_malloc_hook (size_t, const void *);
static void  my_free_hook (void*, const void *);
static void* my_realloc_hook(void *, size_t, const void *);

void alloc_print_info(void);
void alloc_init(void);
size_t alloc_find(void* ptr);
void alloc_stop_trace();
void alloc_begin_trace();
#endif
