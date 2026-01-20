OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
  /* QEMU virt обычно грузит -kernel около 0x80200000 */
  . = 0x80000000;

  .text : ALIGN(4K) {
    *(.text.entry)
    *(.text .text.*)
  }

  .rodata : ALIGN(4K) { *(.rodata .rodata.*) }
  .data   : ALIGN(4K) { *(.data .data.*) }
  .bss (NOLOAD) : ALIGN(4K) {
    __bss_start = .;
    *(.bss .bss.*)
    *(COMMON)
    __bss_end = .;
  }
  /* --- СТЕК --- */
  .stack (NOLOAD) : {
    . = ALIGN(16);
    _stack_bottom = .;
    . = . + 0x4000;   /* 16 KB */
    _stack_top = .;
  }
    /* конец ядра */
  _end = .;
  PROVIDE(kernel_end = .);

  /DISCARD/ : {
    *(.eh_frame*)
    *(.comment)
  }
}
