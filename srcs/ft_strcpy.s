section .text
global ft_strcpy

ft_strcpy:
    mov rax, rdi
    xor rcx, rcx

.loop:
   mov dl, [rsi + rcx]
   mov [rdi + rcx], dl

   cmp dl, 0
   je .done

   inc rcx
   jmp .loop

.done:
    ret 