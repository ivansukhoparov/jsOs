#include "task.h"


#define STACK_SIZE 4096
#define MSTATUS_MIE   (1UL << 3)
#define MSTATUS_MPIE  (1UL << 7)

#define INITIAL_MSTATUS (MSTATUS_MPIE)

void task_exit(void) {
    panic("task returned");
}

struct task *task_create(void (*entry)(void)) {
    struct task *t = kmalloc(sizeof(*t));
    uint8_t *stack = kmalloc(STACK_SIZE);

    uintptr_t top = (uintptr_t)stack + STACK_SIZE;
    top &= ~0xFULL;

    TrapFrame *tf = (TrapFrame *)(top - sizeof(TrapFrame));
    memset(tf, 0, sizeof(*tf));

    tf->mepc = (uint64_t)entry;
    tf->mstatus = INITIAL_MSTATUS;
    tf->sp = top;

    extern void task_exit(void);
    tf->ra = (uint64_t)task_exit;

    t->tf = tf;
    return t;
}