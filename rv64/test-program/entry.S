    .section .text
    .globl _start
    .align 2
_start:
    la      sp, _stack_end
    andi    sp, sp, -16

    call    main

    wfi
    ebreak

1:  wfi
    j   1b

    .section .bss
    .align 12
    .global _stack
_stack:
    .space 16384
_stack_end:
