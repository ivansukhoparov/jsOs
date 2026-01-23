#include "../../../sched/scheduler.h"
#include "../trap.h"

void timer_handler(TrapFrame *tf);
void timer_ack(void) ;

void timer_handler(TrapFrame *tf);