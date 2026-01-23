#pragma once
#include <stdint.h>
#include "../mm/mm.h"
#include "../arch/riscv/trap.h"
#include "../include/kernel/kpanic.h"

struct task {
    TrapFrame *tf;
    struct task *next;
};

void task_exit(void);

struct task *task_create(void (*entry)(void));