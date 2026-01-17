    .section .text.entry
    .globl _start
_start:
    /* выставляем стек */
    la sp, _stack_top

    /* вызываем C-код */
    call kmain

1:  /* если kmain вернулся — зависаем */
    j 1b
