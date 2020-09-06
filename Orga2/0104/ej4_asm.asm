global suma_parametros
section .text
;a0 -> edi
;a1 -> esi
;a2 -> edx
;a3 -> ecx
;a4 -> r8d
;a5 -> r9d
;a6 -> pilarda ([rsp+16])
;a7 -> pilarda ([rsp+24])
suma_parametros:
    push rbp
    mov rbp, rsp
    mov eax, edi
    sub eax, esi
    add eax, edx
    sub eax, ecx
    add eax, r8d
    sub eax, r9d
    add eax, [rbp + 16]
    sub eax, [rbp + 24]
    pop rbp
    ret