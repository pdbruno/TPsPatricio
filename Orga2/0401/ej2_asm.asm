section .text
global dotProduct
; int32_t dotProduct(int16_t *a, int16_t *b)
dotProduct:                     ; rdi = puntero a a, rsi = puntero a b
                                ; armo stackframe
    push    rbp
    mov     rbp, rsp
    pxor xmm8, xmm8

    mov rcx, (64 >> 3)        ; rcx = 64/8 son 64 pares y voy acumulando de a 8 pares
    .ciclo:
        movdqu xmm0, [rdi]      ; xmm0 = | a7 | a6 | a5 | a4 | a3 | a2 | a1 | a0 |
        movdqu xmm1, [rsi]              ; xmm1 = | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
        movdqu xmm2, xmm0               ; xmm2 = | a7 | a6 | a5 | a4 | a3 | a2 | a1 | a0 |
        pmulhw xmm2, xmm1               ; xmm2 = | hi(a7*b7) ... hi(a0*b0) |
        pmullw xmm0, xmm1               ; xmm0 = | low(a7*b7) ... low(a0*b0) |
        movdqu xmm1, xmm0               ; xmm1 = | low(a7*b7) ... low(a0*b0) |
        punpcklwd xmm0, xmm2            ; xmm0 = | (a3*b3) ... (0a*b0) |
        punpckhwd xmm1, xmm2            ; xmm1 = | (a7*b7) ... (a4*b4) |

        paddd xmm8, xmm0
        paddd xmm8, xmm1
        add rdi, 16
        add rsi, 16

        loop .ciclo

    phadd xmm8, xmm8
    phadd xmm8, xmm8
    movd eax, xmm8

    pop rbp
    ret