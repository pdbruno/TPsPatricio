
#include "ColaPrior.h"
template<class T>
ColaPrior<T>::ColaPrior(): arr(new vector<T>()) {
	// COMPLETAR
}

template<class T>
ColaPrior<T>::~ColaPrior(){
    delete arr;
}
template<class T>
int ColaPrior<T>::tam() const {
	return arr->size();
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	arr->push_back(elem);
	int curr = arr->size() -1;
	int parent = padre(curr);
	while(arr->operator[](parent)< arr->operator[](curr)){
	    T aux = arr->at(parent);
        arr->at(parent) = arr->at(curr);
        arr->at(curr) = aux;
        curr = parent;
        parent = padre(curr);
	}
}

template<class T>
const T& ColaPrior<T>::proximo() const {
    return arr->operator[](0);
}

template<class T>
void ColaPrior<T>::desencolar() {
	arr->operator[](0) = arr->operator[](arr->size() -1);
	arr->pop_back();
	int size = arr->size();
    int curr = 0;
    int izq = hijoIzq(curr);
    int der = hijoDer(curr);
    while((izq < size && arr->operator[](curr) < arr->operator[](izq)) || (der < size && arr->operator[](curr) < arr->operator[](der))){
        int next = (der >= size || arr->operator[](der) < arr->operator[](izq)) ? next = izq : next = der;
        T aux = arr->operator[](next);
        arr->operator[](next) = arr->operator[](curr);
        arr->operator[](curr) = aux;
        curr = next;
        izq = hijoIzq(curr);
        der = hijoDer(curr);
    }

}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems): arr(new vector<T>(elems)) {
	int size = elems.size();
    for (int i = size/2; i >= 0 ; --i) {
        int curr = i;
        int izq = hijoIzq(curr);
        int der = hijoDer(curr);
        while((izq < size && arr->operator[](curr) < arr->operator[](izq)) || (der < size && arr->operator[](curr) < arr->operator[](der))){
            int next = (der >= size || arr->operator[](der) < arr->operator[](izq)) ? next = izq : next = der;
            T aux = arr->operator[](next);
            arr->operator[](next) = arr->operator[](curr);
            arr->operator[](curr) = aux;
            curr = next;
            izq = hijoIzq(curr);
            der = hijoDer(curr);
        }
    }
}

template<class T>
int ColaPrior<T>::hijoIzq(int i) {
    return 2*i + 1;
}

template<class T>
int ColaPrior<T>::hijoDer(int i) {
    return 2*i + 2;
}

template<class T>
int ColaPrior<T>::padre(int i) {
    return (i-1)/2;
}

