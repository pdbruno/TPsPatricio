template <typename T>
string_map<T>::string_map(): _size(0), _raiz(nullptr){
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    _size = d._size;
    destruir(_raiz);
    if(d._raiz != nullptr){
        _raiz = new Nodo(d._raiz);
    }
}


template<typename T>
string_map<T>::Nodo::Nodo(const T* def): siguientes(256, nullptr), definicion(def), hijos(0) {};

template<typename T>
string_map<T>::Nodo::Nodo(): siguientes(256, nullptr), definicion(nullptr), hijos(0) {};

template<typename T>
string_map<T>::Nodo::Nodo(const Nodo* aCopiar) : siguientes(256, nullptr), definicion(nullptr), hijos(aCopiar->hijos) {
    if(aCopiar->definicion != nullptr){
        definicion = new T(*aCopiar->definicion);
    }
    for (int i = 0; i < aCopiar->siguientes.size(); ++i) {
        if(aCopiar->siguientes[i] != nullptr){
            siguientes[i] = new Nodo(aCopiar->siguientes[i]);
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    destruir(_raiz);
}

template<typename T>
void string_map<T>::destruir(Nodo* n){
    if(n != nullptr){
        for (int i = 0; i < n->siguientes.size(); ++i) {
            destruir(n->siguientes[i]);
        }
        if(n->definicion != nullptr){
            delete n->definicion;
        }
        delete n;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int res = 0;
    if(_raiz == nullptr){
        return res;
    }
    Nodo* current = _raiz;
    int i = 0;
    while (i < clave.size() && current->siguientes[clave[i]] != nullptr){
        current = current->siguientes[clave[i]];
        i++;
    }
    if(i == clave.size() && current->definicion != nullptr){
        res = 1;
    }
    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* current = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        current = current->siguientes[clave[i]];
    }
    return current->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* current = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        current = current->siguientes[clave[i]];
    }
    return *(current->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* current = _raiz;
    Nodo* lastWithDef = _raiz;
    int lastPos = 0;
    for (int i = 0; i < clave.size(); ++i) {
        if(current->definicion != nullptr || current->hijos != 1){
            lastWithDef = current;
            lastPos = i;
        }
        current = current->siguientes[clave[i]];
    }
    delete current->definicion;
    current->definicion = nullptr;
    _size--;
    if(current->hijos == 0){
        current = lastWithDef->siguientes[clave[lastPos]];
        lastWithDef->siguientes[clave[lastPos]] = nullptr;
        lastPos++;
        lastWithDef->hijos--;
        lastWithDef = current;
        while (lastPos < clave.size()) {
            current = lastWithDef->siguientes[clave[lastPos]];
            lastPos++;
            delete lastWithDef;
            lastWithDef = current;
        }
        delete lastWithDef;
    }
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& entrada) {
    const string& clave = entrada.first;
    if(_raiz == nullptr){
        _raiz = new Nodo();
    }
    Nodo* current = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        if(current->siguientes[clave[i]] == nullptr){
            current->siguientes[clave[i]] = new Nodo();
            current->hijos++;
        }
        current = current->siguientes[clave[i]];
    }
    if(current->definicion == nullptr){
        _size++;
    } else {
        delete current->definicion;
    }
    current->definicion = new T(entrada.second);
}


template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const {
    return _raiz == nullptr;
}