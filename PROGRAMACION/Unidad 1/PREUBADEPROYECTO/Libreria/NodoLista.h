#pragma once

template <typename T>
class NodoLista
{
private:
    T dato;
    NodoLista<T> *siguiente;

public:
    NodoLista(T valor) : dato(valor), siguiente(nullptr) {} //constructor

    T getDato() const { return dato; }
    NodoLista<T> *getSiguiente() const { return siguiente; }

    void setDato(T valor) { dato = valor; }
    void setSiguiente(NodoLista<T> *nodo) { siguiente = nodo; }
};
