ASM = $(wildcard *.asm)
ASM_O = $(ASM:.asm=.o)

main: ${ASM} *c
	make ${ASM_O}
	gcc -g -ggdb *.c *.o -o ejec -lm -no-pie

%.o: %.c
	gcc -g -ggdb -lm -no-pie -c -o $@ $<

%.o: %.asm
	nasm -f elf64 -F DWARF $< -g

clean:
	-rm -f *.o ejec

# CC=c99
# CFLAGS=-Wall -Wextra -pedantic -O0 -g -lm -Wno-unused-variable -Wno-unused-parameter -no-pie
# CFLAGS=-g -lm -no-pie
# NASM=nasm
# NASMFLAGS=-f elf64 -g -F DWARF 

# all: main lib.o

# main: main.c lib.o
# 	$(CC) $(CFLAGS) $^ -o $@


# lib.o: lib.asm
# 	$(NASM) $(NASMFLAGS) $< -o $@

# clean:
# 	rm -f *.o ejec
