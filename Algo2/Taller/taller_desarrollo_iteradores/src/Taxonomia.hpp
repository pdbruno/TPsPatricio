#include <sstream>
#include <stack>
#include <vector>
#include "Taxonomia.h"


// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream& is) const {
    int c = is.peek();
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        is.get();
        c = is.peek();
    }
    return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::_leerDe(istream& is) {
    Taxonomia<T>::Nodo* nodo = new Taxonomia<T>::Nodo();
    is >> nodo->valor;
    if (_espiarProximoCaracter(is) == '{') {
        is.get();
        while (_espiarProximoCaracter(is) != '}') {
            nodo->hijos.push_back(_leerDe(is));
        }
        is.get();
    }
    return nodo;
}

template<class T>
Taxonomia<T>::Taxonomia(const string& input) {
    istringstream is(input);
    _raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo* nodo) {
    for (int i = 0; i < nodo->hijos.size(); i++) {
        _borrar(nodo->hijos[i]);
    }
    delete nodo;
}

template<class T>
Taxonomia<T>::~Taxonomia() {
    _borrar(_raiz);
}

template<class T>
void Taxonomia<T>::_identar(ostream& os, int tab) const {
    for (int i = 0; i < tab; i++) {
        os << "  ";
    }
}

template<class T>
void Taxonomia<T>::_mostrarEn(
        ostream& os, Taxonomia<T>::Nodo* nodo, int tab) const {
    _identar(os, tab);
    os << nodo->valor;
    if (nodo->hijos.size() == 0) {
        os << "\n";
    } else {
        os << " {\n";
        for (int i = 0; i < nodo->hijos.size(); i++) {
            _mostrarEn(os, nodo->hijos[i], tab + 1);
        }
        _identar(os, tab);
        os << "}\n";
    }
}

template<class T>
void Taxonomia<T>::mostrar(ostream& os) const {
    _mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
    return Taxonomia<T>::iterator(_raiz, stack<pair<Nodo*, int>>());
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
    return Taxonomia<T>::iterator(nullptr, stack<pair<Nodo*, int>>());
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator(Nodo* actual, stack<pair<Nodo*, int>> padres) {
    _actual = actual;
    _padres = padres;
}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T& Taxonomia<T>::iterator::operator*() const {
    return _actual->valor;
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
    return _actual->hijos.size();
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
    _padres.push(make_pair(_actual, _pos));
    _actual = _actual->hijos[i];
    _pos = i;
}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
    return _padres.empty();
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
    _actual = _padres.top().first;
    _pos = _padres.top().second;
    _padres.pop();
}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(
        const Taxonomia<T>::iterator& otro) const {
    return _actual == otro._actual;
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
    if(_actual->hijos.size() != 0){
        _padres.push(make_pair(_actual, _pos));
        _actual = _actual->hijos[0];
        _pos = 0;
    } else {
        while (!esRaiz() && _pos + 1 == _padres.top().first->hijos.size()){
            supercategoria();
        }
        if(esRaiz()){
            _actual = nullptr;
        } else {
            _actual = _padres.top().first->hijos[++_pos];
        }

    }
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
    if(esRaiz()){
        _actual = nullptr;
    } else {
        if(_pos == 0){
            supercategoria();
        } else {
            _actual = _padres.top().first->hijos[--_pos];
            while(_actual->hijos.size() != 0){
                _padres.push(make_pair(_actual, _pos));
                _pos = _actual->hijos.size() - 1;
                _actual = _actual->hijos[_pos];
            }
        }
    }
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T& nombre) {
    Nodo* nodo = new Taxonomia<T>::Nodo();
    nodo->valor = nombre;
    _actual->hijos.insert(_actual->hijos.begin() + i, nodo);
}

// Elimina la categoría actual de la taxonomía
// (y todas sus subcategorías).
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores. Debe encargarse de
// liberar la memoria.
// Pre: el iterador está posicionado sobre una categoría,
// y además !esRaiz().
template<class T>
void Taxonomia<T>::iterator::eliminarCategoria() {
    _padres.top().first->hijos.erase(_padres.top().first->hijos.begin() + _pos);
    _borrar(_actual);
    _actual = _padres.top().first;
    _pos = _padres.top().second;
}

template<class T>
void Taxonomia<T>::iterator::_borrar(Nodo* nodo) {
    for (int i = 0; i < nodo->hijos.size(); i++) {
        _borrar(nodo->hijos[i]);
    }
    delete nodo;
}

