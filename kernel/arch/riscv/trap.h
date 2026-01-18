#pragma once
#include <stdint.h>

void trap_handler(uint64_t mepc,
                  uint64_t mcause,
                  uint64_t mtval);