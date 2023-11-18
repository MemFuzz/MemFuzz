#include <stdio.h>
#include <stdlib.h>

// Function pointer types
typedef void* (*MallocFunc)(size_t size);
typedef void* (*ReallocFunc)(void* ptr, size_t size);
typedef void* (*CallocFunc)(size_t nmemb, size_t size);
typedef void (*FreeFunc)(void* ptr);

// Pointers to the original functions
MallocFunc original_malloc = malloc;
ReallocFunc original_realloc = realloc;
CallocFunc original_calloc = calloc;
FreeFunc original_free = free;

// Custom memory management functions
void* custom_malloc(size_t size) {
    void* ptr = original_malloc(size);
    // Record the allocation
    printf("Allocated %zu bytes at address %p\n", size, ptr);
    return ptr;
}

void* custom_realloc(void* ptr, size_t size) {
    void* new_ptr = original_realloc(ptr, size);
    // Record the reallocation
    printf("Reallocated %zu bytes at address %p\n", size, new_ptr);
    return new_ptr;
}

void* custom_calloc(size_t nmemb, size_t size) {
    void* ptr = original_calloc(nmemb, size);
    // Record the allocation
    printf("Allocated %zu bytes at address %p\n", nmemb * size, ptr);
    return ptr;
}

void custom_free(void* ptr) {
    // Record the deallocation
    printf("Freed memory at address %p\n", ptr);
    original_free(ptr);
}

int main() {
    // Replace the original functions with custom ones
    original_malloc = custom_malloc;
    original_realloc = custom_realloc;
    original_calloc = custom_calloc;
    original_free = custom_free;

    // Your program logic here

    // Don't forget to free allocated memory
    void* mem = malloc(10);
    free(mem);

    return 0;
}

