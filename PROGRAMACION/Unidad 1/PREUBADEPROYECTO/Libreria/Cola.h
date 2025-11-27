#pragma once
#include "NodoCola.h"
#include <iostream>

using namespace std;

template <typename T>
class Cola
{
private:
    NodoCola<T> *rear;
    NodoCola<T> *front;

public:
    Cola() : front(nullptr), rear(nullptr) {}

    void encolar(const T &dato);
    T desencolar();
    bool estaVacia() const;
    void mostrar() const;
};

template <typename T>
inline bool Cola<T>::estaVacia() const
{
    return front == nullptr;
}

template <typename T>
void Cola<T>::mostrar() const
{
    NodoCola<T> *actual = front;
    while (actual != nullptr)
    {
        std::cout << actual->getDato() << std::endl;
        actual = actual->getSiguiente();
    }
}

template <typename T>
void Cola<T>::encolar(const T &dato)
{
    NodoCola<T> *nuevo = new NodoCola<T>(dato);
    if (estaVacia())
    {
        front = rear = nuevo;
    }
    else
    {
        rear->setSiguiente(nuevo);
        rear = nuevo;
    }
}

template <typename T>
T Cola<T>::desencolar()
{
    if (estaVacia())
    {
        cout << "La cola está vacía\n";
        return T();
    }

    NodoCola<T> *temp = front;
    T dato = temp->getDato();
    front = front->getSiguiente();

    if (front == NULL)
    {
        rear = NULL;
    }

    delete temp;
    return dato;
    return T();
}
