/**
 * @file mem.h
 * 
 * Memory functions, used as wrappers for malloc and free
*/

#include <stdint.h>


//Malloc and free syscall setup
uint32_t malloc_sys(size_t size);
uint32_t free_sys(uint32_t ptr);


/** @brief wrapper for malloc syscall, acts exactly like malloc
 * 
 * @param size the number of bytes to allocate
 * 
 * @return a pointer to the allocated memory
*/
void * mem_alloc(size_t size) {
    return (void*) malloc_sys(size);
}

/** @brief wrapper for free syscall, acts exactly like free
 * 
 * @param ptr the pointer to the memory to free
 * 
 * @return None
*/
void mem_free(void* ptr) {
    free_sys((uint32_t) ptr);
}