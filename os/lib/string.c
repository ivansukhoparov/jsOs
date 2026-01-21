#include "string.h"

void *memset(void *dst, int c, size_t n)
{
    uint8_t *p = dst;
    while (n--)
        *p++ = (uint8_t)c;
    return dst;
}
