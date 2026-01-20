#include "kpanic.h"
#include "kprint.h"
#include "../../arch/riscv/trap.h"

__attribute__((noreturn)) 
void panic(const char *msg) {
    kprint("\n=== KERNEL PANIC ===\n");
    kprint(msg);
    kprint("\n");
    for (;;)
        asm volatile("wfi");
}

__attribute__((noreturn)) 
void panic_mtrap(const char *msg, uint64_t mepc, uint64_t mcause, uint64_t mtval) {
    kprint("\n=== KERNEL PANIC ===\n");
    kprint(msg);
    kprint("\n\n");

    kprint("pc:     ");
    kprint_hex(mepc);
    kprint("\n");
    kprint("mcause: ");
    kprint_hex(mcause);
    kprint("\n");
    kprint("mtval:  ");
    kprint_hex(mtval);
    kprint("\n");

    for (;;)
        asm volatile("wfi");
}