#include <stdint.h>

#define UART0_BASE 0x10000000UL
#define UART_THR   0x00 /* transmit holding register */
#define UART_LSR   0x05 /* line status register */
#define LSR_TX_IDLE 0x20

static inline void mmio_write(uint64_t addr, uint8_t value) {
  *(volatile uint8_t*)addr = value;
}

static inline uint8_t mmio_read(uint64_t addr) {
  return *(volatile uint8_t*)addr;
}

static void uart_putc(char c) {
  /* ждём, пока можно отправлять */
  while ((mmio_read(UART0_BASE + UART_LSR) & LSR_TX_IDLE) == 0) {}
  mmio_write(UART0_BASE + UART_THR, (uint8_t)c);
}

static void uart_puts(const char* s) {
  while (*s) {
    if (*s == '\n') uart_putc('\r');
    uart_putc(*s++);
  }
}

void kmain(void) {
  uart_puts("[Kernel] Boot OK\n");
  while (1) { }
}