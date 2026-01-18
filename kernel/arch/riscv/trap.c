#include "../../kprint.h"
#include "../../panic.h"
#include "trap.h"
#define SCAUSE_INTERRUPT (1ULL << 63)
#define SCAUSE_CODE(x) ((x) & ~(1ULL << 63))

enum {
    TRAP_ILLEGAL_INSTRUCTION = 2,
    TRAP_BREAKPOINT          = 3,
    TRAP_LOAD_PAGE_FAULT     = 13,
    TRAP_STORE_PAGE_FAULT    = 15,
    TRAP_INST_PAGE_FAULT     = 12,
};




void trap_handler(uint64_t mepc,
                  uint64_t mcause,
                  uint64_t mtval){
   uint64_t cause = mcause;
    uint64_t code  = SCAUSE_CODE(cause);


        kprint("mepc "); kprint_hex(mepc); kprint("\n");
        kprint("mcause "); kprint_hex(mcause); kprint("\n");
        kprint("mtval "); kprint_hex(mtval); kprint("\n");

        kprint("cause "); kprint_hex(cause); kprint("\n");
        kprint("code "); kprint_hex(code); kprint("\n");

        if (cause & SCAUSE_INTERRUPT) {
        panic("unexpected interrupt");
    }

    

    switch (code) {

        case TRAP_BREAKPOINT:
            kprint("BREAKPOINT at pc=");
            kprint_hex(mepc);
            kprint("\n");

            // ebreak = 4 байта → пропускаем инструкцию
            mepc += 4;
            return;

        case TRAP_ILLEGAL_INSTRUCTION:
            panic_mtrap("illegal instruction", mepc, mcause, mtval);

        case TRAP_LOAD_PAGE_FAULT:
        case TRAP_STORE_PAGE_FAULT:
        case TRAP_INST_PAGE_FAULT:
            panic_mtrap("page fault", mepc, mcause, mtval);

        default:
            panic_mtrap("unknown trap",mepc, mcause, mtval);
    }

    // kprint("TRAP ENTERED\n");

    // kprint("mcause=");
    // kprint_hex(tf->mcause);
    // kprint("\n");

    // kprint("mepc=");
    // kprint_hex(tf->mepc);
    // kprint("\n");

    // for (;;)
    //     asm volatile("wfi");
}