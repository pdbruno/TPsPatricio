#include "SistemaDeMensajes.h"
#include "ConexionJugador.h"
#if EJ >= 6
#include "Proxy2.h"
#else
#include "Proxy.h"
#endif

SistemaDeMensajes::SistemaDeMensajes(): _conns(), _proxies() {}

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
#if EJ < 4
Proxy::Proxy(ConexionJugador* conn) : _conn(conn) {}
#endif
Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    if(_proxies[id] == nullptr){
        _proxies[id] = new Proxy(&_conns[id]);
    }
        return _proxies[id];
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