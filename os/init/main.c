#include "../include/kernel/kprint.h"
#include "../_test/atrps.h"
#include "../include/kernel/kpanic.h"
#include "../_test/mm.h"
int test_global;

void kmain(phys_addr_t mem_start, phys_addr_t mem_end)
{
    init_page_allocator(mem_start, mem_end);

    if (test_global != 0) {
        panic("BSS not cleared");
    }

    kprint("[Kernel] Boot OK\n");

    kprint("\n[Kernel] Before breakpoint\n");
    // breakpoint();
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