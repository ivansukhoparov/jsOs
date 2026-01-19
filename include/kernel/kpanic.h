#pragma once
#include <stdint.h>


__attribute__((noreturn))
void panic(const char* msg);

__attribute__((noreturn))
void panic_mtrap(const char* msg, uint64_t mepc, uint64_t mcause, uint64_t mtval);