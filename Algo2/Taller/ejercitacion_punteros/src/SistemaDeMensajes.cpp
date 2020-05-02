#include "SistemaDeMensajes.h"
#include "ConexionJugador.h"

SistemaDeMensajes::SistemaDeMensajes(): _conns() {}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    this->_conns[id] = new ConexionJugador(ip);
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    this->_conns[id]->enviarMensaje(mensaje);
}

bool  SistemaDeMensajes::registrado(int id) const {
    return this->_conns[id] != nullptr;
}

string SistemaDeMensajes::ipJugador(int id) const {
    return this->_conns[id]->ip();
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    this->_conns[id] = nullptr;
}

Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    if(this->_proxies[id] == nullptr){
            this->_proxies[id] = new Proxy(this->_conns[id]);

    }
        return this->_proxies[id];
}

SistemaDeMensajes::~SistemaDeMensajes(){
    for (int i = 0; i < 4; ++i) {
        if (this->_conns[i] != nullptr){
            delete this->_conns[i];
        }
        if (this->_proxies[i] != nullptr){
            delete this->_proxies[i];
        }
    }
}