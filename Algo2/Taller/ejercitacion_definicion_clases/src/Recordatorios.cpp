#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
public:
    int mes();

    int dia();

    Fecha(int mes, int dia);
    // Completar declaraciones funciones
#if EJ >= 9 // Para ejercicio 9

    bool operator==(Fecha o);
    bool operator<(Fecha o);

#endif

    void incrementar_dia();

private:
    int dia_;
    int mes_;
};

Fecha::Fecha(int mes, int dia) : dia_(dia), mes_(mes) {}

int Fecha::mes() {
    return this->mes_;
}

int Fecha::dia() {
    return this->dia_;
}

ostream &operator<<(ostream &os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9

bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();

    return igual_dia and igual_mes;
}
bool Fecha::operator<(Fecha f) {
    if (this->mes() < f.mes()) {
        return false;
    }
    if (this->mes() == f.mes() && this->dia() <= f.dia()) {
        return false;
    }
    return true;
}

#endif

void Fecha::incrementar_dia() {
    if (this->dia_ == dias_en_mes(this->mes_)) {
        this->dia_ = 1;
        this->mes_++;
    } else {
        this->dia_++;
    }
}
// Ejercicio 11, 12

// Clase Horario
class Horario {
public:
    uint hora();

    uint min();

    Horario(uint hora, uint min);

    bool operator==(Horario o);

    bool operator<(Horario h);

private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min) : hora_(hora), min_(min) {}

uint Horario::hora() {
    return this->hora_;
}

uint Horario::min() {
    return this->min_;
}

bool Horario::operator==(Horario o) {
    bool igual_hora = this->hora() == o.hora();
    bool igual_min = this->min() == o.min();

    return igual_hora and igual_min;
}

ostream &operator<<(ostream &os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator<(Horario h) {
    if (this->hora() > h.hora()) {
        return false;
    }
    if (this->hora() == h.hora() && this->min() >= h.min()) {
        return false;
    }
    return true;
}

// Ejercicio 13

// Clase Recordatorio
class Recordatorio {
public:
    Recordatorio(Fecha f, Horario h, string msg);

    Fecha fecha();

    Horario horario();

    string mensaje();

    bool operator<(Recordatorio r);

private:
    Fecha fecha_;
    Horario horario_;
    string mensaje_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string msg) : fecha_(f), horario_(h), mensaje_(msg) {}

bool Recordatorio::operator<(Recordatorio r) {
    if (!(this->fecha() < r.fecha()) && !(this->fecha() == r.fecha())) {
        return false;
    }
    if (this->fecha() == r.fecha() && !(this->horario() < r.horario())) {
        return false;
    }
    return true;
}

Fecha Recordatorio::fecha() {
    return this->fecha_;
}

Horario Recordatorio::horario() {
    return this->horario_;
}

string Recordatorio::mensaje() {
    return this->mensaje_;
}
ostream &operator<<(ostream &os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}
// Ejercicio 14

// Clase Agenda
class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

private:
    Fecha hoy_;
    list<Recordatorio> recs_;
};

Agenda::Agenda(Fecha fecha_inicial): hoy_(fecha_inicial), recs_() {}

Fecha Agenda::hoy() {
    return  this->hoy_;
}
void Agenda::agregar_recordatorio(Recordatorio rec) {
    this->recs_.push_back(rec);
}
void Agenda::incrementar_dia() {
    this->hoy_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> res;
    for(Recordatorio r: this->recs_){
        if (r.fecha() == this->hoy_){
            res.push_back(r);
        }
    }
    return res;
}
ostream &operator<<(ostream &os, Agenda a) {
    os << a.hoy() << endl << "=====" << endl;
    list<Recordatorio> copy = a.recordatorios_de_hoy();
    copy.sort();
    for (Recordatorio rec : copy) {
        os << rec << endl;
    }
    return os;
}
