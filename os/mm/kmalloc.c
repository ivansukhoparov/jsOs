#include "mm.h"

void* kmalloc(size_t size) {
    if (size > PAGE_SIZE)
        return NULL;
    return alloc_page();
}

void kfree(void* ptr) {
    free_page(ptr);
}