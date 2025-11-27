#include <iostream>
#include <vector>
#include <algorithm>

#include "LibrosController.h"

using namespace std;

void insertarLibro(Lista<Libros> &lista, const Libros &libro)
{
    lista.insertar(libro);
}

bool eliminarLibro(Lista<Libros> &lista, const std::string &codigo)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().getCodigo() == codigo)
        {
            lista.eliminar(actual->getDato());
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

void mostrarPorAutor(const Lista<Libros> &lista, const std::string &autor)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().coincideAutor(autor))
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}

void mostrarPorCantidad(const Lista<Libros> &lista)
{
    vector<Libros> libros;
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        libros.push_back(actual->getDato());
        actual = actual->getSiguiente();
    }

    sort(libros.begin(), libros.end(), [](const Libros &a, const Libros &b)
         { return a.getCantidad() > b.getCantidad(); });

    for (const auto &libro : libros)
    {
        cout << libro << endl;
    }
}

void mostrarLibros(const Lista<Libros> &lista)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (!actual->getDato().disponibilidad())
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}

bool buscarPorTituloRecursivo(NodoLista<Libros> *nodo, const std::string &titulo)
{
    if (!nodo)
        return false;
    if (nodo->getDato().coincideTitulo(titulo))
        return true;
    return buscarPorTituloRecursivo(nodo->getSiguiente(), titulo);
}

bool buscarPorTitulo(const Lista<Libros> &lista, const std::string &titulo)
{
    return buscarPorTituloRecursivo(lista.getCabeza(), titulo);
}

int contarPrestadosRec(NodoLista<Libros> *nodo)
{
    if (!nodo)
        return 0;
    int suma = nodo->getDato().disponibilidad() ? 0 : 1;
    return suma + contarPrestadosRec(nodo->getSiguiente());
}

int contarPrestados(const Lista<Libros> &lista)
{
    return contarPrestadosRec(lista.getCabeza());
}

void mostrarLibrosDisponibles(const Lista<Libros> &lista)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().disponibilidad())
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}
