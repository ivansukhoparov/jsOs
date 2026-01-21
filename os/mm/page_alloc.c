#include "mm.h"

#define PAGE_SIZE 4096

typedef uintptr_t phys_addr_t;

static uint8_t* page_bitmap;     // bitmap в памяти
static size_t total_pages;       // всего страниц
static phys_addr_t memory_base;  // физический адрес страницы 0

static inline void bitmap_set(size_t bit) {
    page_bitmap[bit / 8] |= (1 << (bit % 8));
}

static inline void bitmap_clear(size_t bit) {
    page_bitmap[bit / 8] &= ~(1 << (bit % 8));
}

static inline int bitmap_test(size_t bit) {
    return page_bitmap[bit / 8] & (1 << (bit % 8));
}

extern char kernel_end[];

void init_page_allocator(phys_addr_t mem_start, phys_addr_t mem_end) {
    memory_base = ALIGN_UP((phys_addr_t)kernel_end, PAGE_SIZE);
    total_pages = (mem_end - memory_base) / PAGE_SIZE;

    size_t bitmap_size = (total_pages + 7) / 8;
    page_bitmap = (uint8_t*)memory_base;

    // bitmap занимает первые N байт
    memset(page_bitmap, 0xFF, bitmap_size); // всё занято

    // страницы после bitmap
    phys_addr_t first_free =
        ALIGN_UP(memory_base + bitmap_size, PAGE_SIZE);

    size_t first_free_page =
        (first_free - memory_base) / PAGE_SIZE;

    /* bitmap-страницы — заняты */
    for (size_t i = 0; i < first_free_page; i++)
        bitmap_set(i);

    /* остальные — свободны */
    for (size_t i = first_free_page; i < total_pages; i++)
        bitmap_clear(i);
}

void* alloc_page(void) {
    for (size_t i = 0; i < total_pages; i++) {
        if (!bitmap_test(i)) {
            bitmap_set(i);
            return (void*)(memory_base + i * PAGE_SIZE);
        }
    }
    return NULL; // OOM
}

void free_page(void* addr) {
    phys_addr_t p = (phys_addr_t)addr;

    if (p < memory_base)
        panic("free_page: addr < memory_base");

    if ((p - memory_base) % PAGE_SIZE != 0)
        panic("free_page: unaligned addr");

    size_t index = (p - memory_base) / PAGE_SIZE;

    if (index >= total_pages)
        panic("free_page: index out of range");

    if (!bitmap_test(index))
        panic("double free");

    bitmap_clear(index);
}