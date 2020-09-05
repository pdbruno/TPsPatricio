global fun
section .text
fun:
    push rbp
    mov rbp, rsp
    addpd xmm0, xmm1
    pop rbp
    ret