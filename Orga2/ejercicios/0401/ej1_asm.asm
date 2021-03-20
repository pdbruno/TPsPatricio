extern malloc
section .text
global mod
; float* mod(float *v)
mod:
    ; armo stackframe
    push    rbp
    mov     rbp, rsp
    push r15
    sub rsp, 8

    mov r15, rdi
    mov rdi, 1024 * 4
    call malloc

    mov rcx, (1024 >> 2)        ; rcx = 1024/4  1024 pares, voy procesando de a 4 pares
    .ciclo:
        movups xmm0, [r15]      ; xmm0 = x0 | y0 | x1 | y1
        mulps xmm0, xmm0        ; xmm0 = x0^2 | y0^2 | x1^2 | y1^2
        movups xmm1, [r15 + 15] ; xmm1 = x2 | y2 | x3 | y3
        mulps xmm1, xmm1        ; xmm1 = x2^2 | y2^2 | x3^2 | y3^2

        haddps xmm0, xmm1       ; xmm0 = x0^2 + y0^2 | x1^2 + y1^2 | x2^2 + y2^2 | x3^2 + y3^2

        sqrtps xmm0, xmm0

        movaps [rax], xmm0

        add r15, 32
        add rax, 16

        loop .ciclo

    add rsp, 8
    pop r15
    pop rbp
    ret