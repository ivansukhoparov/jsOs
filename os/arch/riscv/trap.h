#pragma once
#include <stdint.h>

#pragma once
#include "stdint.h"

typedef struct TrapFrame {
    uint64_t ra, sp, gp, tp;
    uint64_t t0, t1, t2;
    uint64_t s0, s1;
    uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint64_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    uint64_t t3, t4, t5, t6;

    uint64_t mepc, mstatus, mcause, mtval;
    uint64_t pad;
} TrapFrame;

void trap_handler(TrapFrame *tf);
