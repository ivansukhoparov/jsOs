#include "timer.h"


#define CLINT_MTIME       0x0200BFF8UL
#define CLINT_MTIMECMP    0x02004000UL

#define TIMER_INTERVAL    1000000UL   // подбери под частоту

static volatile uint64_t *mtime    = (uint64_t *)CLINT_MTIME;
static volatile uint64_t *mtimecmp = (uint64_t *)CLINT_MTIMECMP;

void timer_init(void) {
    *mtimecmp = *mtime + TIMER_INTERVAL;

    /* включить machine timer interrupt */
    asm volatile (
        "csrs mie, %0\n"     // MTIE
        "csrs mstatus, %1\n" // MIE
        :
        : "r"(1 << 7),       // MTIE
          "r"(1 << 3)        // MIE
    );
}

void timer_ack(void) {
    *mtimecmp = *mtime + TIMER_INTERVAL;
}

void timer_handler(TrapFrame *tf) {
    timer_ack();          // ОБЯЗАТЕЛЬНО
    scheduler_tick(tf);
}
