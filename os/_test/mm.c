#include "mm.h"

void memory_test()
{
    const int number = 1024;
    const int rounds = 40; // 512*20 = 10240
    void *pages[number];

    for (int r = 0; r < rounds; r++) {
        for (int i = 0; i < number; i++) {
            pages[i] = kmalloc(128);
            if (!pages[i])
                panic("OOM");
        }
        kprint("kmalloc-");
        kprint_dec(rounds);
        kprint(" OK\n");
        for (int i = 0; i < number; i++) {
            kfree(pages[i]);
        }
        kprint("kfree-");
        kprint_dec(rounds);
        kprint(" OK\n");
    }
    kprint("alloc/free batched OK\n");
}