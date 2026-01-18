#include "../../kprint.h"
#include "../../panic.h"


void trap_handler(uint64_t mepc,
                  uint64_t mcause,
                  uint64_t mtval)
{
    kprint("TRAP ENTERED\n");

    kprint("mcause=");
    kprint_hex(mcause);
    kprint("\n");

    kprint("mepc=");
    kprint_hex(mepc);
    kprint("\n");

    for (;;)
        asm volatile("wfi");
}