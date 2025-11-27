#include "NodoPila.h"
#include <iostream>

template <typename T>
class Pila
{
private:
    NodoPila<T> *cima;

public:
    Pila() : cima(nullptr) {}

    void push(const T &dato)
    {
        NodoPila<T> *nuevo = new NodoPila<T>(dato);
        nuevo->getAnterior(cima);
        cima = nuevo;
    }

    void pop()
    {
        if (cima == nullptr)
        {
            std::cout << "La pila está vacía\n";
            return;
        }
        NodoPila<T> *temp = cima;
        cima = cima->getAnterior();
        delete temp;
    }

    T peek() const
    {
        if (cima == nullptr)
        {
            std::cout << "Pila vacía\n";
            return T();
        }
        return cima->getDato();
    }

    void mostrar() const
    {
        NodoPila<T> *actual = cima;
        while (cima != nullptr)
        {
            std::cout << actual->getDato() << std::endl;
            actual = actual->getAnterior();
        }
    }

    ~Pila()
    {
        while (!estaVacia())
        {
            pop();
        }
    }
};
