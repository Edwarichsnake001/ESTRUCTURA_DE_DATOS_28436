#include "Nodo.H"
#include <iostream>

using namespace std;

Nodo::Nodo(Cancion c)
{
    dato = c;
    siguiente = nullptr;
    anterior = nullptr;
}

Cancion Nodo::getDato()
{
    return dato;
}

void Nodo::setSiguiente(Nodo* sig)
{
    siguiente = sig;
}

Nodo* Nodo::getSiguiente()
{
    return siguiente;
}

void Nodo::setAnterior(Nodo* ant)
{
    anterior = ant;
}

Nodo* Nodo::getAnterior()
{
    return anterior;
}

