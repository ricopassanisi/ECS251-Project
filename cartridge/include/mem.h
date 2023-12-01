#include <stdint.h>



uint32_t malloc_sys(size_t size);

void * mem_alloc(size_t size) {
    return (void*) malloc_sys(size);
}