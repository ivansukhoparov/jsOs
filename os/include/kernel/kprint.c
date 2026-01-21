#include <stdint.h>
#include "kprint.h"

#define UART_BASE 0x10000000UL
#define UART_THR 0x00 /* transmit holding register */
#define UART_LSR 0x05 /* line status register */
#define LSR_TX_IDLE 0x20
#define UART_LSR_EMPTY 0x40

static inline void mmio_write(uint64_t addr, uint8_t value)
{
    *(volatile uint8_t *)addr = value;
}

static inline uint8_t mmio_read(uint64_t addr)
{
    return *(volatile uint8_t *)addr;
}

static inline void uart_putc(char c)
{
    volatile uint8_t *uart = (uint8_t *)UART_BASE;

    // ждём, пока UART готов принять байт
    while ((uart[UART_LSR] & UART_LSR_EMPTY) == 0) {
    }

    uart[UART_THR] = c;
}

void kprint(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}

void kprint_hex(uint64_t v)
{
    const char *hex = "0123456789abcdef";

    kprint("0x");

    for (int i = 60; i >= 0; i -= 4) {
        uart_putc(hex[(v >> i) & 0xF]);
    }
}

void kprint_dec(long x) {
    char buf[32];
    int i = 0;

    if (x == 0) {
        kprint("0");
        return;
    }

    if (x < 0) {
        kprint("-");
        x = -x;
    }

    while (x > 0 && i < (int)sizeof(buf) - 1) {
        buf[i++] = '0' + (x % 10);
        x /= 10;
    }

    // reverse
    for (int j = i - 1; j >= 0; j--) {
        char s[2] = { buf[j], 0 };
        kprint(s);
    }
}