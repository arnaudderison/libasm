section .text
global ft_strcmp

ft_strcmp:
    xor rcx, rcx

.loop:
    movzx eax, byte [rdi + rcx]
    movzx edx, byte [rsi + rcx]

    cmp al, dl
    jne .diff

    cmp al, 0
    je .equal

    inc rcx
    jmp .loop

.diff:
    sub eax, edx
    ret

.equal:
    xor eax, eax
    ret