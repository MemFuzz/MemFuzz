#ifndef _MEMFUZZ_POOL_
#define _MEMFUZZ_POOL_
#include <glib.h>
#include <stdio.h>

int pool_init();
int pool_init_with_names(char** names, int len);
void pool_insert(char *name, void* val);
void pool_print_info();
int pool_get_size(char* name);
void** pool_get_values(char* name, int *len); // The caller takes the ownership of the return value
void pool_destroy();

int dup_is_in(void* addr);
void dup_insert(void* addr);
int dup_init();
void dup_destroy();
#endif