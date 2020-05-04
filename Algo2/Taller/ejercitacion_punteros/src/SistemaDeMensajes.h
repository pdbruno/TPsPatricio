#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "ConexionJugador.h"
#include <string>


#if EJ >= 6
#include "Proxy2.h"
#else
#include "Proxy.h"
#endif

using namespace std;

class SistemaDeMensajes {
  public:
    SistemaDeMensajes();
    // Pre: 0 <= id < 4
    void registrarJugador(int id, string ip);
    // Pre: 0 <= id < 4
    bool registrado(int id) const;

    // Pre: registrado(id)
    void enviarMensaje(int id, string mensaje);

    // Pre: registrado(id)
    string ipJugador(int id) const;

    void desregistrarJugador(int id);

    Proxy* obtenerProxy(int id);

    ~SistemaDeMensajes();

  private:
    ConexionJugador* _conns[4];
    Proxy* _proxies[4];
};

#endif
