OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
  /* QEMU virt обычно грузит -kernel около 0x80200000 */
  . = 0x80000000;

  .text : {
    *(.text.entry)
    *(.text .text.*)
  }

  .rodata : { *(.rodata .rodata.*) }
  .data   : { *(.data .data.*) }
  .bss    : {
    *(.bss .bss.*)
    *(COMMON)
  }

  /* --- СТЕК --- */
  .stack (NOLOAD) : {
    . = ALIGN(16);
    _stack_bottom = .;
    . = . + 0x4000;   /* 16 KB */
    _stack_top = .;
  }
}
