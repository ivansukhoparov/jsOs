#include "../include/kernel/kprint.h"
#include "../_test/atrps.h"

void kmain(void)
{

    kprint("[Kernel] Boot OK\n");

    kprint("\n[Kernel] Before breakpoint\n");
    // breakpoint();
    kprint("\n[Kernel] After breakpoint\n");

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