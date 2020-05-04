#include "Proxy2.h"

void Proxy::enviarMensaje(string msg) {
    (*_conn)->enviarMensaje(msg);
}
Proxy::Proxy(ConexionJugador** conn) : _conn(conn) {}