#include "scheduler.h"


static struct task *current;

void scheduler_init(void) {
    current = 0;
}

void scheduler_add(struct task *t) {
    if (!current) {
        current = t;
        t->next = t;
    } else {
        t->next = current->next;
        current->next = t;
    }
}

void scheduler_tick(TrapFrame *tf) {
    if (!current)
        return;

    current->tf = tf;
    current = current->next;

    asm volatile ("mv sp, %0" :: "r"(current->tf) : "memory");
}
