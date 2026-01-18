.option nopic

/* ===================== */
/* Точка входа ядра     */
/* ===================== */

.section .text.entry
.globl _start
_start:
    /* 1. инициализируем стек */
    la sp, _stack_top

    /* 2. указываем trap-вектор */
    la t0, trap_entry
    csrw mtvec, t0

    /* 3. переходим в C-код */
    call kmain

1:
    j 1b


/* ===================== */
/* Trap entry            */
/* ===================== */


.section .text.trap
.align 2  
.globl trap_entry
trap_entry:
    /* минимальный trap entry для Дня 2 */
    li   t0, 0x10000000      # UART THR
    li   t1, 'T'
    sb   t1, 0(t0)           # вывести 'T' сразу
    csrr a0, mepc
    csrr a1, mcause
    csrr a2, mtval

   call trap_handler

1:  j 1b
