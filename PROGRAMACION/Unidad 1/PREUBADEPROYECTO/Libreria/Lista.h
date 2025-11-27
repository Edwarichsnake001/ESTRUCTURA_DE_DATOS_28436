#pragma once
#include "NodoLista.h"
#include <iostream>

using namespace std;

template <typename T>
class Lista
{
private:
    NodoLista<T> *cabeza;

public:
    Lista() : cabeza(nullptr) {}

    NodoLista<T> *getCabeza() const
    {
        return cabeza;
    }

    void insertar(const T &dato)
    {
        NodoLista<T> *nuevo = new NodoLista<T>(dato);
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
    }

    void mostrar() const
    {
        NodoLista<T> *actual = cabeza;
        while (actual != nullptr)
        {
            cout << actual->getDato() << endl;
            actual = actual->getSiguiente();
        }
    }

    bool estaVacia() const
    {
        return cabeza == nullptr;
    }

    void eliminar(const T &dato)
    {
        NodoLista<T> *actual = cabeza;
        NodoLista<T> *anterior = nullptr;

        while (actual)
        {
            if (actual->getDato() == dato)
            {
                if (anterior)
                {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                else
                {
                    cabeza = actual->getSiguiente();
                }
                delete actual;
                return;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
    }

    ~Lista()
    {
        NodoLista<T> *actual = cabeza;
        while (actual != nullptr)
        {
            NodoLista<T> *temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        }
    }
};
