section .data
formato_printf:
    db '%d, %f, %s', 10, 0


global imprime_parametros
extern printf
section .text
;a->edi
;f->xmm0
;s->rsi
imprime_parametros:
    push rbp
    mov rbp, rsp
    ;formato -> rdi
    ;a -> esi
    ;f -> xmm0
    ;s -> rdx
    mov rdx, rsi
    mov esi, edi
    mov rdi, formato_printf
    mov rax, 1
    call printf
    pop rbp
    ret