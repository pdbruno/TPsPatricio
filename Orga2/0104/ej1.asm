global fun
section .text
fun:
    push rbp
    mov rbp, rsp
    add edi, esi
    mov eax, esi
    pop rbp
    ret