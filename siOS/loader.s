global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

section .text
align 4
dd MAGIC_NUMBER
dd FLAGS
dd CHECKSUM

loader:
    mov edi, 0xB8000
    mov ecx, 80*25
    mov ax, 0x0720   ; 0x20 = ' ' (пробел), 0x07 = цвет
    rep stosw
    mov edi, 0xB8000
    mov ecx, 16
    mov esi, msg
    
.loop:
    lodsb
    mov [edi], al
    mov byte [edi+1], 0x0F
    add edi, 2
    loop .loop
    
hang:
    jmp hang


section .data
msg db "siOS version 0.1"

