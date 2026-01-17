#include "kprint.c"
#include "panic.c"

void trigger_illegal(void) {
    asm volatile (".word 0x00000000");
}

void trigger_page_fault(void) {
    volatile uint64_t* p = (uint64_t*)0x0;
    *p = 1;
}

void breakpoint(void) {
    asm volatile ("ebreak");
}

void kmain(void) {
    kprint("Kernel start\n");

    breakpoint();        // должен ВЕРНУТЬСЯ
    trigger_illegal();   // должен PANIC
    trigger_page_fault();// до него уже не дойдёт
}

