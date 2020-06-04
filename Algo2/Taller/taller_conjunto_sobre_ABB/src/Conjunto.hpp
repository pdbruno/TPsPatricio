
template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr) {
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruir(_raiz);
    _raiz = nullptr;
}
template<class T>
void Conjunto<T>::destruir(Nodo* n){
    if(n != nullptr){
        destruir(n->der);
        destruir(n->izq);
        delete n;
    }
}
template<class T>
Conjunto<T>::Nodo::Nodo(const T &v): valor(v), izq(nullptr), der(nullptr), cant(0) {};
template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* current = _raiz;
    bool existe = false;
    while (current != nullptr && !existe){
        existe = clave == current->valor;
        if(clave < current->valor){
            current = current->izq;
        } else {
            current = current->der;
        }

    }
    return existe;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(_raiz == nullptr){
        _raiz = new Nodo(clave);
    } else {
        recursiveInsertar(clave, &_raiz);
    }
}
template <class T>
bool Conjunto<T>::recursiveInsertar(const T &clave, Nodo** current) {//true significa no existe el nodo (efectivamente inserte algo)

    if(*current == nullptr){
        *current = new Nodo(clave);
        return true;
    } else {

        if(clave == (*current)->valor){
            return false;
        } else {
            bool claveNoExiste;
            if(clave < (*current)->valor) {
                claveNoExiste = recursiveInsertar(clave, &((*current)->izq));
            } else{
                claveNoExiste = recursiveInsertar(clave, &((*current)->der));
            }
            if(claveNoExiste){
                (*current)->cant++;
            }
            return claveNoExiste;

        }


    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(_raiz != nullptr){
        recursiveRemover(clave, &_raiz);
    }
}
template <class T>
bool Conjunto<T>::recursiveRemover(const T &clave, Nodo** current) { //true significa no existe el nodo (no borre nada)

    if(*current == nullptr){
        return true;
    } else {

        if(clave == (*current)->valor){
            if((*current)->der == nullptr && (*current)->izq == nullptr){ //el nodo a borrar es un hoja
                delete (*current);
                (*current) = nullptr;
            } else if ((*current)->der == nullptr && (*current)->izq != nullptr){ //tiene hijo izquierdo
                Nodo* temp = (*current);
                (*current) = (*current)->izq;
                delete temp;
            } else if((*current)->der != nullptr && (*current)->izq == nullptr){//tiene hijo derecho
                Nodo* temp = (*current);
                (*current) = (*current)->der;
                delete temp;
            } else { //tiene ambos hijos

                Nodo* parent = *current;
                Nodo* sig = parent->der;//este es el reemplazo
                while (sig->izq != nullptr){
                    parent->cant--;
                    parent = sig;
                    sig = sig->izq;
                }
                // parent es el padre del reemplazo
                if(parent != *current){
                    if(sig->der != nullptr){
                        parent->izq = sig->der;
                    } else {
                        parent->izq = nullptr;
                    }
                    sig->der = (*current)->der;
                    sig->cant = (*current)->cant;
                } else {
                    sig->cant = (*current)->cant - 1;
                }
                sig->izq = (*current)->izq;
                delete (*current);
                *current = sig;
            }
            return false;

        } else {
            bool claveNoExiste;
            if(clave < (*current)->valor) {
                claveNoExiste = recursiveRemover(clave, &((*current)->izq));
            } else{
                claveNoExiste = recursiveRemover(clave, &((*current)->der));
            }
            if(!claveNoExiste){
                (*current)->cant--;
            }
            return claveNoExiste;
        }

    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* prev = nullptr;
    Nodo* current = _raiz;
    while (current->valor != clave){
        prev = current;
        if(clave > current->valor){
            current = current->der;
        } else if(clave < current->valor){
            current = current->izq;
        }
    }
    if(current->der == nullptr){
        return prev->valor;
    } else {
        return inmediatoSuc(current)->valor;
    }
}
template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::inmediatoSuc(const Nodo* n) {
    Nodo* current = n->der;
    while (current->izq != nullptr){
        current = current->izq;
    }
    return current;
}


template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* current = _raiz;
    while (current->izq != nullptr){
        current = current->izq;
    }
    return current->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* current = _raiz;
    while (current->der != nullptr){
        current = current->der;
    }
    return current->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    if(_raiz == nullptr){
        return 0;
    } else {
        return 1 + _raiz->cant;
    }
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

