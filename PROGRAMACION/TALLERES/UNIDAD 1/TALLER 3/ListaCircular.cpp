#include "ListaCircular.h"
#include <iostream>

using namespace std;

ListaCircularDoble::ListaCircularDoble()
{
    primero = nullptr;
    ultimo = nullptr;
    actual = nullptr;
}


void ListaCircularDoble::insertar(Cancion c)
{
    Nodo *nuevo = new Nodo(c);
    if (!primero)
    {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        actual = primero;
    }
    else
    {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(primero);
        primero->setAnterior(nuevo);
        ultimo = nuevo;
    }
}

void ListaCircularDoble::eliminar(Cancion c)
{
    if (!primero)
        return;

    Nodo *actual = primero;
    Nodo *anterior = ultimo;
    do
    {
        if (actual->getDato() == c)
        {
            if (actual == primero && actual == ultimo)
            {
                primero = nullptr;
                ultimo = nullptr;
                this->actual = nullptr;
            }
            else
            {
                anterior->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(anterior);
                if (actual == primero)
                {
                    primero = actual->getSiguiente();
                }
                if (actual == ultimo)
                {
                    ultimo = anterior;
                }
                if (this->actual == actual)
                {
                    this->actual = actual->getSiguiente();
                }
            }
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);
}

void ListaCircularDoble::mostrar()
{
    if (!primero)
    {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo *temp = primero;
    do
    {
        cout << temp->getDato() << " \n";
        temp = temp->getSiguiente();
    } while (temp != primero);
    cout << endl;
}

bool ListaCircularDoble::buscar(Cancion c)
{
    if (!primero)
        return false;

    Nodo *temp = primero;
    do
    {
        if (temp->getDato() == c)
        {
            return true;
        }
        temp = temp->getSiguiente();
    } while (temp != primero);
    return false;
}

void ListaCircularDoble::reproducirCancionActual() {
    if (actual)
        cout << "Reproduciendo: " << actual->getDato() << endl;
    else
        cout << "No hay canción en reproducción." << endl;
}

void ListaCircularDoble::siguienteCancion() {
    if (actual)
        actual = actual->getSiguiente();
    reproducirCancionActual();
}

void ListaCircularDoble::anteriorCancion() {
    if (actual)
        actual = actual->getAnterior();
    reproducirCancionActual();
}


