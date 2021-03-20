#include <stdio.h>
extern int suma_parametros( int a0, int a1, int a2, int a3, int a4, int a5 ,int a6, int a7 );
int main(){
    int res = suma_parametros(1, 2, 3, 4, 5, 6, 7, 8);
    printf("el resultado es: %i", res);
    return 0;
}