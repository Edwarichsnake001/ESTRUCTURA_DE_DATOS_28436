#pragma once

#include "Estudiante.h"
#include <iomanip> // Para formato de tabla

using namespace std;

struct Nodo

{
    Estudiante dato;
    Nodo *siguiente;
    Nodo(const Estudiante &c) : dato(c), siguiente(nullptr) {}

};

class ListaSimple

{

private:
    Nodo *cabeza;
    bool insertarOrdenado(Nodo *& sortedHead, Nodo *llave)
    {
        if (!sortedHead || llave->dato < sortedHead->dato)
        {
            llave -> siguiente = sortedHead;
            sortedHead = llave;
            return true;
        }


        Nodo *current = sortedHead;
        Nodo *anterior = nullptr;

        while (current != nullptr && current->dato < llave->dato)
        {
            anterior = current;
            current = current->siguiente;
        }

        if(anterior == nullptr)
        {
            return false;
        }

        llave->siguiente = current;
        anterior->siguiente = llave;

        cout << " -> Inserción de la posición: ";
        if(current)
        {
            current->dato.imprimir();
        }
        else
        {
            cout<<" FINAL \n";
        }
        return true;
    }

public:

    ListaSimple() : cabeza(nullptr) {}
    ~ListaSimple()
    {
        // Liberación de memoria (Destructor)
        Nodo *current = cabeza;
        while (current != nullptr)
        {
            Nodo *siguiente = current->siguiente;
            delete current;
            current = siguiente;
        }
        cabeza = nullptr;
    }

    void insertar(string id, string nombre, int nota)
    {
        Estudiante c= {id,nombre,nota};
        Nodo *nuevoNodo = new Nodo(c);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }

    void mostrar() const
    {
        Nodo *current = cabeza;
        if (!current)
        {
            std::cout << "Lista vacía.\n";
            return;
        }
        while (current != nullptr)
        {
            current->dato.imprimir();
            if (current->siguiente)
            {
                std::cout << " -> ";
            }
            current = current->siguiente;
        }
        std::cout << " -> NULL\n";
    }

    void insertionSort()
    {

        if (!cabeza || !cabeza->siguiente)
        {
            return;
        }

        Nodo *sorted = nullptr;
        Nodo *current = cabeza;

        std::cout << "\n======================================================\n";
        std::cout << "       INICIO DE ORDENAMIENTO (INSERTION SORT)       \n";
        std::cout << "======================================================\n";

        while(current != nullptr)
        {
            Nodo *key = current;
            current = current->siguiente;
            key->siguiente = nullptr;

            std::cout << "\n--- CLAVE: ";
            key->dato.imprimir();
            std::cout << " ---\n";
            if (insertarOrdenado(sorted, key))
            {
                std::cout << "  -> Nodos desplazados: 1 (el nodo clave)\n";
            }
            else
            {
                std::cout << "  -> Nodos desplazados: 0 (el nodo clave ya estaba en orden)\n";
            }

            cabeza = sorted;

            std::cout << "\nEstado de la Lista: \n";
            mostrar();
            std::cout << "------------------------------------------------------\n";
        }


    }
};
