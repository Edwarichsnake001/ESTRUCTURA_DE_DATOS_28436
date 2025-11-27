#pragma once

template <typename T>
class NodoCola
{
private:
    T dato;
    NodoCola<T> *siguiente;

public:
    NodoCola(T valor) : dato(valor), siguiente(nullptr) {}

    T getDato() const { return dato; }
    NodoCola<T> *getSiguiente() const { return siguiente; }

    void setDato(T valor) { dato = valor; }
    void setSiguiente(NodoCola<T> *nodo) { siguiente = nodo; }
};
