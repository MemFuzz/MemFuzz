#include "alloc_hook.h"

GHashTable *alloc_table = NULL;
int alloc_trace = 0;

void alloc_init (void)
{
  alloc_trace = 1;
  alloc_table = g_hash_table_new(g_direct_hash, g_direct_equal);
  if(alloc_table == NULL)
  {
    fprintf(stderr, "Failed to init g_hash_table_new\n");
    exit(1);
  }
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  old_realloc_hook = __realloc_hook;
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  __realloc_hook = my_realloc_hook;
}

static void *
my_malloc_hook (size_t size, const void *caller)
{
  void *result;
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  __realloc_hook = old_realloc_hook;
  result = malloc (size);
  memset(result, 0, size); // give init value. It also hooks calloc
  if(alloc_trace)
  {
    g_hash_table_insert(alloc_table, result, GINT_TO_POINTER(size));
  }
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  old_realloc_hook = __realloc_hook;
//   printf ("malloc (%u) returns %p\n", (unsigned int) size, result);
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  __realloc_hook = my_realloc_hook;
  return result;
}

static void
my_free_hook (void *ptr, const void *caller)
{
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  __realloc_hook = old_realloc_hook;
  if(alloc_trace)
  {
      g_hash_table_remove(alloc_table, ptr);
  }
  free (ptr);
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  old_realloc_hook = __realloc_hook;
//   printf ("freed pointer %p\n", ptr);
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  __realloc_hook = my_realloc_hook;
}

static void* my_realloc_hook(void *ptr, size_t size, const void *caller)
{
  void *result;
  char* ptr1;
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  __realloc_hook = old_realloc_hook;
  guint64 *val = g_hash_table_lookup(alloc_table, ptr);
  ptr1 = result = realloc (ptr, size);
  if(val != NULL)
  {
    size_t size0 = GPOINTER_TO_UINT(val);
    if(size > size0)
    {
      memset(result + size0, 0, size - size0);
    }
  }
  else
  {
    printf ("Warning: trace realloc (%u) returns %p from unknown pointer %p\n", (unsigned int) size, result, ptr);
  }
  if(alloc_trace)
  {
    g_hash_table_remove(alloc_table, ptr);
    g_hash_table_insert(alloc_table, result, GINT_TO_POINTER(size));
  }
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  old_realloc_hook = __realloc_hook;
//   printf ("realloc (%u) returns %p from %p\n", (unsigned int) size, result, ptr);
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  __realloc_hook = my_realloc_hook;
  return result;
}

void print_key_value(gpointer key, gpointer value, gpointer user_data) {
    guint64 v = GPOINTER_TO_UINT(value);
    printf("Key: %p, Value: %lu\n", key, v);
}

void print_alloc_info()
{
    if(alloc_table == NULL)
        return ;
    alloc_trace = 0;
    g_hash_table_foreach(alloc_table, print_key_value, NULL);
    alloc_trace = 1;
}

size_t alloc_find(void* ptr)
{
    if(alloc_table == NULL)
        return 0;
    alloc_trace = 0;
    guint64 *val = g_hash_table_lookup(alloc_table, ptr);
    alloc_trace = 1;
    if(val == NULL)
        return 0;
    return GPOINTER_TO_UINT(val);
}