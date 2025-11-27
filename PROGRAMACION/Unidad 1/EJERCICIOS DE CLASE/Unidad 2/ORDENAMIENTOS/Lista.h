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

    void ordenPorIntercambio()
    {
        NodoLista<T> *actual = cabeza;

        if (cabeza == nullptr)
        {
            cout << "No hay puntuación disponible. Hecha una partida para ser el mejor";
            return;
        }

        // Bucle Exterior: Itera a través de cada elemento base (A, B, C...)
        while (actual != nullptr)
        {
            cout << "\n--- Iniciando Ordenamiento por Intercambio PURE (Visual) ---\n";

            /* Este puntero debe empezar en el siguiente de 'actual' en cada iteración exterior */
            NodoLista<T> *comparador = actual->getSiguiente();

            /* El cuerpo de ordenamiento Exchanged Sort: aquí se realiza una
            comparación a cada uno de los datos subsecuentes del primero.
            Esto es independiente de si esta ya está ordenada, por lo que
            igual realizará la comparación */

            // Bucle Interior: Compara 'actual' con todos los elementos restantes (B, C, D...)
            while (comparador != nullptr)
            {

                  cout << "Comparando: " << actual->getDato() << " con " << comparador->getDato() << endl;

                // Si el dato actual es menor que el dato del comparador (orden incorrecto)
                if (actual->getDato() < comparador->getDato())
                {
                     cout << "  -> ¡INTERCAMBIO! " << actual->getDato() << " pasa a ser " << comparador->getDato() << endl;

                    // Intercambiamos los datos dentro de los nodos
                    T temp = actual->getDato();
                    actual->setDato(comparador->getDato());
                    comparador->setDato(temp);
                }

                 cout << "--- Elemento base '" << actual->getDato() << "' ha completado su ronda de comparacion ---\n";

                // AVANCE CRUCIAL DEL COMPARADOR INTERNO
                comparador = comparador->getSiguiente();
            }

            // AVANCE CRUCIAL DEL PUNTERO BASE EXTERNO
            actual = actual->getSiguiente();
        }
         cout << "--- Ordenamiento Finalizado ---\n";
    }
};