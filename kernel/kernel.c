#include "kprint.h"


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
 
  kprint("SP test\n");
kprint_hex((uint64_t)__builtin_frame_address(0));
kprint("\n");
kprint("Hello kernel\n");
kprint("pc=");
kprint_hex(0x1234);
kprint("\n");
 kprint("[Kernel] Boot OK\n");

breakpoint();        // должен ВЕРНУТЬСЯ
trigger_illegal();   // должен PANIC
    trigger_page_fault();// до него уже не дойдёт
  while (1) { }
}