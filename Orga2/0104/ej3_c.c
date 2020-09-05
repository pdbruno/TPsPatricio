#include <stdio.h>
extern void imprime_parametros(int a, double f, char* s);
int main(){
    imprime_parametros(5, 3.14, "holiss");
    return 0;
}