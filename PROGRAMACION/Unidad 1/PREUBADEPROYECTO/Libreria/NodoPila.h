#pragma once

template <typename T>
class NodoPila {
private:
    T dato;
    NodoPila<T>* anterior;

public:
    NodoPila(T valor) : dato(valor), anterior(nullptr) {}

    T getDato() const { return dato; }
    NodoPila<T>* getAnterior() const { return anterior; }

    void setDato(T valor) { dato = valor; }
    void setAnterior(NodoPila<T>* nodo) { anterior = nodo; }
};
