#include <utility>

using namespace std;

// Ejercicio 15

// Juego

using Pos = pair<int, int>;

char ARRIBA = '^';
char ABAJO = 'v';
char IZQUIERDA = '<';
char DERECHA = '>';

class Juego {
public:
    Juego(uint casilleros, Pos pos_inicial);

    Pos posicion_jugador();

    uint turno_actual();

    void mover_jugador(char dir);

    void ingerir_pocion(uint movimientos, uint turnos);

private:
    vector<vector<uint>> tablero_;
    Pos posicion_jugador_;
    uint turno_actual_;
    uint casilleros_;
    uint turnos_pocion_;
    uint movimientos_pocion_;
};

Juego::Juego(uint casilleros, Pos pos_inicial) : turno_actual_(0), posicion_jugador_(pos_inicial), casilleros_(casilleros), turnos_pocion_(0), movimientos_pocion_(1) {

}

Pos Juego::posicion_jugador() {
    return this->posicion_jugador_;
}

uint Juego::turno_actual() {
    return this->turno_actual_;
}

void Juego::mover_jugador(char dir) {
    switch (dir) {
        case '^':
            if (this->posicion_jugador_.second !=  0){
                this->posicion_jugador_.first--;
            }
            break;
        case 'v':
            if (this->posicion_jugador_.second != casilleros_-1){
                this->posicion_jugador_.first++;
            }
            break;
        case '<':
            if (this->posicion_jugador_.first != 0){
                this->posicion_jugador_.second--;
            }
            break;
        case '>':
            if (this->posicion_jugador_.first != casilleros_-1){
                this->posicion_jugador_.second++;
            }

            break;
    }
    if(this->movimientos_pocion_ > 1){
        movimientos_pocion_--;
    } else if(this->movimientos_pocion_ == 1){

    }

    this->turno_actual_++;
}

void Juego::ingerir_pocion(uint movimientos, uint turnos) {
    //esta mal explicado y es una paja chau
}