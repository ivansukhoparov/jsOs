#pragma once
#include "task.h"
#include "../arch/riscv/context/context.h"

void scheduler_init(void);
void scheduler_add(struct task *t);
void scheduler_tick(TrapFrame *tf);
