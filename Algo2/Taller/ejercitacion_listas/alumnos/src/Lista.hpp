#include "Lista.h"

Lista::Nodo::Nodo(const int &elem): data(elem), next(nullptr), prev(nullptr) {}

Lista::Lista(): head_(nullptr), tail_(nullptr), longitud_(0) {
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    this->limpiar_lista_();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    this->limpiar_lista_();
    this->longitud_ = 0;
    for (int i = 0; i < aCopiar.longitud(); ++i) {
        this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    if(this->head_ == nullptr){
        this->head_ = new Nodo(elem);
        this->tail_ = this->head_;
    } else {
        this->head_->prev = new Nodo(elem);
        this->head_->prev->next = this->head_;
        this->head_ = this->head_->prev;
    }
    this->longitud_++;
}

void Lista::agregarAtras(const int& elem) {
    if(this->head_ == nullptr){
        this->head_ = new Nodo(elem);
        this->tail_ = this->head_;
    } else {
        this->tail_->next = new Nodo(elem);
        this->tail_->next->prev = this->tail_;
        this->tail_ = this->tail_->next;
    }
    this->longitud_++;
}

void Lista::eliminar(Nat i) {
    if(i >=0  && i < this->longitud_){
        Nodo* temp;
        if(longitud_ == 1){
            temp = this->head_;
            this->head_ = nullptr;
            this->tail_ = nullptr;
        } else if(i==0){ //si quiero borrar el head
            temp = this->head_;
            this->head_ = temp->next;
            this->head_->prev = nullptr;
        }else if(i == this->longitud_ - 1){ //si quiero borrar el tail
            temp = this->tail_;
            this->tail_ = temp->prev;
            this->tail_->next = nullptr;
        } else if(i<this->longitud_/2){ //si lo que quiero borrar esta en la primera mitad empiezo desde el principio
                int j = 0;
                temp = this->head_;
                while(j!=i){
                    temp= temp->next;
                    j++;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
        } else { //si lo que quiero borrar esta en la segunda mitad empiezo desde el final
            int j = this->longitud_ - 1;
            temp = this->tail_;
            while(j!=i){
                temp= temp->prev;
                j--;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        this->longitud_--;
    }
}

int Lista::longitud() const {
    return this->longitud_;
}

const int& Lista::iesimo(Nat i) const {
    int j = 0;
    Nodo* temp = this->head_;
    while(temp != nullptr && j!=i){
        temp= temp->next;
        j++;
    }
    return temp->data;
}

int& Lista::iesimo(Nat i) {
    int j = 0;
    Nodo* temp = this->head_;
    while(temp != nullptr && j!=i){
        temp= temp->next;
        j++;
    }
    return temp->data;
}

void Lista::mostrar(ostream& o) {
    o << "{";
    for (int i = 0; i < this->longitud_-1; ++i) {
        o << this->iesimo(i) << ", ";
    }
    o << this->iesimo(this->longitud_-1) << "}";

}

void Lista::limpiar_lista_() {
    Nodo* temp = this->head_;
    while(temp != nullptr){
        temp= temp->next;
        delete(this->head_);
        this->head_ = temp;
    }
}

