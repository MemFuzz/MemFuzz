#ifndef ALLOC_HOOK_H_
#define ALLOC_HOOK_H_ 
#include <malloc.h>
#include <stdlib.h>
#include <glib.h>

extern GHashTable *alloc_table;
extern int alloc_trace;
static void* my_malloc_hook (size_t, const void *);
static void my_free_hook (void*, const void *);
static void* my_realloc_hook(void *, size_t, const void *);

static void* (*old_malloc_hook) (size_t, const void *);
static void  (*old_free_hook) (void*, const void *);
static void* (*old_realloc_hook)(void *, size_t, const void *);
void print_alloc_info(void);
void alloc_init(void);
size_t alloc_find(void* ptr);
#endif
