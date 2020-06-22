template <typename T>
string_map<T>::string_map(): _size(0), _raiz(nullptr){
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
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
    while (i < clave.size() && current->siguientes[int(clave[i])] != nullptr){
        current = current->siguientes[int(clave[i])];
        i++;
    }
    if(i == clave.size()){
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
    return current->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
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
        }
        current = current->siguientes[clave[i]];
    }
    if(current->definicion == nullptr){
        _size++;
    }
    current->definicion = &(entrada.second);
}

template <typename T>
void string_map<T>::insert(pair<string, T>& entrada) {
    const string& clave = entrada.first;
    if(_raiz == nullptr){
        _raiz = new Nodo();
    }
    Nodo* current = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        if(current->siguientes[clave[i]] == nullptr){
            current->siguientes[clave[i]] = new Nodo();
        }
        current = current->siguientes[clave[i]];
    }
    if(current->definicion == nullptr){
        _size++;
    }
    current->definicion = &(entrada.second);
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const {
    return _raiz == nullptr;
}