#include "lista.h"

extern void agregarPrimero(lista_t* unaLista, int unInt);
extern void agregarUltimo(lista_t* unaLista, int unInt);
extern void borrarUltimo(lista_t* unaLista);
extern void borrarPrimero(lista_t* unaLista);
int main(int argc, char* argv){
	
	lista_t lista;
	lista.primero = NULL;

	borrarPrimero(&lista);
	borrarUltimo(&lista);
	agregarUltimo(&lista, 4);
	agregarPrimero(&lista, 3);
	agregarPrimero(&lista, 2);
	agregarPrimero(&lista, 1);
	agregarUltimo(&lista, 5);
	borrarUltimo(&lista);
	borrarPrimero(&lista);

	printList(&lista);

	vaciarLista(&lista);
	return 0;

}