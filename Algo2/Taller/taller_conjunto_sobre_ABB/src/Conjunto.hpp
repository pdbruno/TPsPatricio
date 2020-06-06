
/*Buenas, algunos comentarios:
 * 1- no es el código más lindo que escribí en mi vida
 * 2- la razón por la cual usé recurisón en insertar y en remover fue para poder precalcular la propiedad 'cant' de cada nodo en O(1)
 * sin tener que usar un stack (se podría decir que al fin y al cabo estoy usando el call stack para volver sobre mis pasos y poder modificar 'cant' de los padres de ser necesario)
 * 3- es verdad que en ningún lado estoy aprovechando el hecho de que cada nodo guarda su propio 'cant', pero podría ser útil si llego a necesitar reflejar el inOrder
 * en un vector (como enseñaron en al clase de ABB) o si quisiera generar otro árbol usando como raíz un nodo existente
 * */

template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr) {}

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
    Nodo* padre = nullptr;
    Nodo* ultimoGiroALaIzq = nullptr;
    Nodo* current = _raiz;
    while (current->valor != clave){
        padre = current;
        if(clave > current->valor){
            current = current->der;
        } else if(clave < current->valor){
            ultimoGiroALaIzq = current;
            current = current->izq;
        }
    }
    if(current->der == nullptr){
        if(padre->izq == current){
            return padre->valor;
        }else{
            return ultimoGiroALaIzq->valor;
        }
    } else {
        current = current->der;
        while (current->izq != nullptr){
            current = current->izq;
        }
        return current->valor;
    }
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
void Conjunto<T>::mostrar(std::ostream& o) const {
    mostrarInOrder(o, _raiz);
}
template <class T>
void Conjunto<T>::mostrarInOrder(std::ostream& o, const Nodo* n) const {
    if(n->izq != nullptr ){
        mostrarInOrder(o, n->izq);
    }
    o << n->valor << ' ';

    if(n->der != nullptr) {
        mostrarInOrder(o, n->der);
    }

}

