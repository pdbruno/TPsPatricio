SET R0, 0x0A
SET R1, 0x00 ;comienzo mi acumulador en 0
CMP R0, R1 ;seteo los flags acorde a si R0 es 0
ciclo:
JZ fin ; si el flag Z es 0 termino
ADD R1, R0 ;acumulo
DEC R0 ;resto 1 a R0 y actualizo el flag Z
JMP ciclo ;vuelvo arriba de todo
fin:
JMP fin

