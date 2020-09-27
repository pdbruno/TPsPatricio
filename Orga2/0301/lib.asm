;----------------------------------------------------------
; Firma:
;   void agregarPrimero(lista* unaLista, int unInt);
;
; Retorno:
;     void    
;
; Argumentos:
;    lista* unaLista        RDI
;    int unInt              ESI
;----------------------------------------------------------

%define PUNTERO_LISTA (rbx)
%define DATO (r12d)
%define TAMANIO_NODO 16

extern free
extern malloc
section .text
global agregarPrimero
global agregarUltimo
global borrarUltimo
global borrarPrimero
agregarPrimero:
    ;armo stackframe
    push    rbp
    mov     rbp, rsp
    push rbx		 ; pila alineada 8
    push r12		 ; pila alineada 16
    
    mov PUNTERO_LISTA, rdi
    mov DATO, esi

    ;pido memoria para el nuevo nodo
    mov rdi, TAMANIO_NODO
    call malloc ;rax = puntero a nuevo nodo
    
    mov rdi, [PUNTERO_LISTA] ;rdi = puntero a primer nodo
    ;armo el nuevo nodo
    mov [rax], DATO
    mov [rax + 8], rdi
    mov [PUNTERO_LISTA], rax

    ;desarmo stackframe
    pop r12
	pop rbx
    pop rbp
    ret

agregarUltimo: ;se puede hacer usando un solo puntero en vez de dos
    ;armo stackframe
    push    rbp
    mov     rbp, rsp
    push rbx		 ; pila alineada 8
    push r12		 ; pila alineada 16
    
    mov PUNTERO_LISTA, rdi
    mov DATO, esi

    ;pido memoria para el nuevo nodo
    mov rdi, TAMANIO_NODO
    call malloc ;rax = puntero a nuevo nodo
    ;armo el nuevo nodo
    mov [rax], DATO
    mov QWORD [rax + 8], 0

    lea rdi, [PUNTERO_LISTA]      ; rdi = direccion puntero al primer nodo (el famoso doble puntero)
    mov rcx, [rdi]                ; rcx = puntero a nodo

    .loop:
        test rcx, rcx
        jz .inserto
        lea rdi, [rcx + 8]
        mov rcx, [rdi]
        jmp .loop
    .inserto:
        mov [rdi], rax

    ;desarmo stackframe
    pop r12
	pop rbx
    pop rbp
    ret

borrarUltimo:
    ;armo stackframe
    push    rbp
    mov     rbp, rsp
    push rbx		 ; pila alineada 8
    sub rsp, 8		 ; pila alineada 16
    
    cmp QWORD [rdi], 0
    jz .fin

    .loop:
        mov rbx, [rdi] 
        cmp QWORD [rbx + 8], 0
        jz .borro
        mov rdi, [rdi]
        add rdi, 8
        jmp .loop
    .borro:
        mov rbx, rdi
        mov rdi, [rdi]
        call free
        mov QWORD [rbx], 0

    .fin:
    ;desarmo stackframe
    add rsp, 8
	pop rbx
    pop rbp
    ret

borrarPrimero:
    ;armo stackframe
    push    rbp
    mov     rbp, rsp
    
    cmp QWORD [rdi], 0
    jz .fin
    mov rax, [rdi] 
    
    mov rdx, [rax + 8]
    mov [rdi], rdx

    mov rdi, rax
    call free

    .fin:
    ;desarmo stackframe
    pop rbp
    ret