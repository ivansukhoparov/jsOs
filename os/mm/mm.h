#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../lib/string.h"
#include "../include/kernel/kpanic.h"

#define ALIGN_UP(x, a)   (((x) + ((a) - 1)) & ~((a) - 1))
#define PAGE_SIZE 4096

typedef uintptr_t phys_addr_t;

void init_page_allocator(phys_addr_t mem_start,
                          phys_addr_t mem_end);

void* alloc_page(void);
void  free_page(void* page);

void* kmalloc(size_t size);
void  kfree(void* ptr); 