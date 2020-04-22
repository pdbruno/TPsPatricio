#include <utility>

using namespace std;

// Ejercicio 15

// Juego

using Pos = pair<int, int>;

char ARRIBA = '^';
char ABAJO = 'v'; 
char DERECHA = '<';
char IZQUIERDA = '>';

class Juego {
    Juego(uint casilleros, Pos pos_inicial);
    Pos posicion_jugador();
    uint turno_actual();
    void mover_jugador(char dir);
    void ingerir_pocion(uint movimientos, uint turnos);
};

Juego::Juego(uint casilleros, Pos pos_inicial){

}
Pos Juego::posicion_jugador(){

}
uint Juego::turno_actual(){

}
void Juego::mover_jugador(char dir){

}
void Juego::ingerir_pocion(uint movimientos, uint turnos){

}