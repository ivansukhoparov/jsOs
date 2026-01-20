#include "trap.h"
#include "../../include/kernel/kprint.h"
#include "../../include/kernel/kpanic.h"

#define MCAUSE_INTERRUPT (1ULL << 63)
#define MCAUSE_CODE(x) ((x) & ~(1ULL << 63))

enum {
    TRAP_INSTRUCTION_ACCESS_FAULT = 1,
    TRAP_ILLEGAL_INSTRUCTION = 2,
    TRAP_BREAKPOINT = 3,
    TRAP_LOAD_ACCESS_FAULT = 5,
    TRAP_STORE_ACCESS_FAULT = 7,
    TRAP_LOAD_PAGE_FAULT = 13,
    TRAP_STORE_PAGE_FAULT = 15,
    TRAP_INST_PAGE_FAULT = 12,
};

static inline uint64_t insn_len(uint64_t pc)
{
    uint16_t i16 = *(uint16_t *)pc;
    return ((i16 & 0x3) == 0x3) ? 4 : 2; // 11b => 32-bit, иначе 16-bit
}

void trap_handler(TrapFrame *tf)
{
    uint64_t cause = tf->mcause;
    uint64_t code = MCAUSE_CODE(cause);

    if (cause & MCAUSE_INTERRUPT) {
        panic_mtrap("unexpected interrupt", tf->mepc, tf->mcause, tf->mtval);
    }

    switch (code) {
        case TRAP_BREAKPOINT:
            kprint("BREAKPOINT at pc=");
            kprint_hex(tf->mepc);
            kprint("\n");

            tf->mepc += insn_len(tf->mepc); // пропускаем ebreak (4 байта)
            return;                         // вернёмся в asm → mret

        case TRAP_ILLEGAL_INSTRUCTION:
            panic_mtrap("illegal instruction", tf->mepc, tf->mcause, tf->mtval);

        case TRAP_LOAD_PAGE_FAULT:
        case TRAP_STORE_PAGE_FAULT:
        case TRAP_INST_PAGE_FAULT:
            panic_mtrap("page fault", tf->mepc, tf->mcause, tf->mtval);

        case TRAP_INSTRUCTION_ACCESS_FAULT:
            panic_mtrap("inctuction access fault", tf->mepc, tf->mcause,
                        tf->mtval);

        case TRAP_LOAD_ACCESS_FAULT:
            panic_mtrap("load access fault", tf->mepc, tf->mcause, tf->mtval);

        case TRAP_STORE_ACCESS_FAULT:
            panic_mtrap("store access fault", tf->mepc, tf->mcause, tf->mtval);

        default:
            panic_mtrap("unknown trap", tf->mepc, tf->mcause, tf->mtval);
    }
}
