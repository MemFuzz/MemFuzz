// #include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
// #include <string.h>
// #include <sys/shm.h>

static void __hook_init(void) __attribute__((constructor));
static void* (*real_malloc)( size_t size );
static void* (*real_calloc)( size_t num, size_t size );
static void* (*real_realloc)( void *ptr, size_t new_size );
static void (*real_free)( void *ptr );

// void* malloc(size_t size)
// {
//   // printf("malloc %lu\n", size);
//   // write(1, "123", 3);
//   return real_malloc(size);
// }

void* calloc(size_t num, size_t size)
{
  // printf("calloc %lu\n", num * size);
  return real_calloc(num, size);
}

void* realloc(void *ptr, size_t new_size )
{
  // printf("realloc %p %lu\n", ptr, new_size);
  return real_realloc(ptr, new_size);
}

// void free(void *ptr)
// {
//   // printf("free %p\n", ptr);
//   real_free(ptr);
// }

/*hook init*/
__attribute__((constructor)) static void __hook_init(void) 
{
  void *handle = dlopen("libc.so.6", RTLD_LAZY);
  if(handle == NULL)
    return;
  // void *handle = dlopen("libstdc++.so.6", RTLD_LAZY);
  real_calloc = dlsym(handle, "calloc");
  real_realloc = dlsym(handle, "realloc");
  real_free = dlsym(handle, "free");
  real_malloc = dlsym(handle, "malloc");
}

