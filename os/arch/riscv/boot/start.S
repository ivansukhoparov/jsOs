.option nopic

.extern __bss_start
.extern __bss_end

/* ===================== */
/* Точка входа ядра     */
/* ===================== */

.section .text.entry
.globl _start
_start:
    /* 1. инициализируем стек */
    la sp, _stack_top

    /* 2. очистка .bss */
    la t0, __bss_start     /* t0 = current */
    la t1, __bss_end       /* t1 = end */

1:
    bgeu t0, t1, 2f        /* if current >= end → done */
    sd zero, 0(t0)         /* store 0 */
    addi t0, t0, 8         /* RV64: 8 bytes */
    j 1b

2:
    /* 3. указываем trap-вектор */
    la t0, trap_entry
    csrw mtvec, t0

    /* 4. переходим в C-код */
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
    addi sp, sp, -(31*8 + 4*8)   # 32 рега + 4 CSR = 36*8 = 288 байт

    # --- save GPRs (x1..x31) ---
    sd ra,   0*8(sp)
    sd sp,   1*8(sp)   # сохраняем значение sp ПОСЛЕ аллокации (так удобнее)
    sd gp,   2*8(sp)
    sd tp,   3*8(sp)
    sd t0,   4*8(sp)
    sd t1,   5*8(sp)
    sd t2,   6*8(sp)
    sd s0,   7*8(sp)
    sd s1,   8*8(sp)
    sd a0,   9*8(sp)
    sd a1,  10*8(sp)
    sd a2,  11*8(sp)
    sd a3,  12*8(sp)
    sd a4,  13*8(sp)
    sd a5,  14*8(sp)
    sd a6,  15*8(sp)
    sd a7,  16*8(sp)
    sd s2,  17*8(sp)
    sd s3,  18*8(sp)
    sd s4,  19*8(sp)
    sd s5,  20*8(sp)
    sd s6,  21*8(sp)
    sd s7,  22*8(sp)
    sd s8,  23*8(sp)
    sd s9,  24*8(sp)
    sd s10, 25*8(sp)
    sd s11, 26*8(sp)
    sd t3,  27*8(sp)
    sd t4,  28*8(sp)
    sd t5,  29*8(sp)
    sd t6,  30*8(sp)

    # --- save CSRs ---
    csrr t0, mepc
    csrr t1, mstatus
    csrr t2, mcause
    csrr t3, mtval

    sd t0,  31*8(sp)   # mepc
    sd t1,  32*8(sp)   # mstatus
    sd t2,  33*8(sp)   # mcause
    sd t3,  34*8(sp)   # mtval

    # call C handler(tf)
    mv a0, sp
    call trap_handler

    # handler мог изменить mepc (например breakpoint)
    ld t0, 31*8(sp)
    csrw mepc, t0

    # --- restore GPRs ---
    ld ra,   0*8(sp)
    # sp восстанавливаем в самом конце
    ld gp,   2*8(sp)
    ld tp,   3*8(sp)
    ld t0,   4*8(sp)
    ld t1,   5*8(sp)
    ld t2,   6*8(sp)
    ld s0,   7*8(sp)
    ld s1,   8*8(sp)
    ld a0,   9*8(sp)
    ld a1,  10*8(sp)
    ld a2,  11*8(sp)
    ld a3,  12*8(sp)
    ld a4,  13*8(sp)
    ld a5,  14*8(sp)
    ld a6,  15*8(sp)
    ld a7,  16*8(sp)
    ld s2,  17*8(sp)
    ld s3,  18*8(sp)
    ld s4,  19*8(sp)
    ld s5,  20*8(sp)
    ld s6,  21*8(sp)
    ld s7,  22*8(sp)
    ld s8,  23*8(sp)
    ld s9,  24*8(sp)
    ld s10, 25*8(sp)
    ld s11, 26*8(sp)
    ld t3,  27*8(sp)
    ld t4,  28*8(sp)
    ld t5,  29*8(sp)
    ld t6,  30*8(sp)

    addi sp, sp, (31*8 + 4*8)
    mret
