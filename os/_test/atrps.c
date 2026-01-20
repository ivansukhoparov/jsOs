#include "atrps.h"

void trigger_illegal(void) { asm volatile(".word 0x00000000"); }

void trigger_page_fault(void)
{
    volatile uint64_t *p = (uint64_t *)0xFFFFFFFFFFFFF000ULL;
    uint64_t x = *p; // LOAD PAGE FAULT
    (void)x;
}

void breakpoint(void) { asm volatile("ebreak"); }

void trigger_instruction_access_fault(void)
{
    typedef void (*fn_t)(void);
    ((fn_t)0x0)();
}

void trigger_load_access_fault(void)
{
    volatile uint64_t x = *(uint64_t *)0xFFFFFFFF;
}

void trigger_store_access_fault(void) { *(volatile uint64_t *)0x0 = 42; }