#include <stdint.h>

void trigger_illegal(void);
void trigger_page_fault(void);
void breakpoint(void);
void trigger_instruction_access_fault(void);
void trigger_load_access_fault(void);
void trigger_store_access_fault(void);