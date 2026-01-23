#include "../include/kernel/kprint.h"
#include "../_test/atrps.h"
#include "../include/kernel/kpanic.h"
#include "../_test/mm.h"
int test_global;


void task_a(void) {
    while (1) {
        kprint("A\n");
    }
}

void task_b(void) {
    while (1) {
        kprint("B\n");
    }
}

void kmain(phys_addr_t mem_start, phys_addr_t mem_end)
{
    init_page_allocator(mem_start, mem_end);

    if (test_global != 0) {
        panic("BSS not cleared");
    }

    init_page_allocator(mem_start, mem_end);

    /* 2. Планировщик */
    scheduler_init();

    scheduler_add(task_create(task_a));
    scheduler_add(task_create(task_b));

    /* 3. Таймер (включает прерывания) */
    timer_init();

    kprint("[Kernel] Boot OK\n");

    kprint("\n[Kernel] Before breakpoint\n");
  breakpoint();
    kprint("\n[Kernel] After breakpoint\n");
    memory_test();
    // kprint("\n[Kernel] Before PANIC\n");// должен PANIC
    // trigger_illegal();
    // trigger_page_fault() ;
    // breakpoint() ;
    // trigger_instruction_access_fault();
    // trigger_load_access_fault() ;
    // trigger_store_access_fault()  ;
    // kprint("\n[Kernel] After illegal\n");

    while (1) {
    }
}