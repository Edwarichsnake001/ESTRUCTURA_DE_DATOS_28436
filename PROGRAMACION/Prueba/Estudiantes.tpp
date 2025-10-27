#include <iostream>
#include "Estudiantes.h"
using namespace std;

template <typename T>
void Estudiantes<T>::ingresarDatos()
{
    cout << "Ingrese ID: ";
    cin >> id;
    cout << "Ingrese Nombre: ";
    cin >> nombre;
}

template <typename T>
void Estudiantes<T>::mostrarDatos() const
{
    cout << "ID: " << id << ", Nombre: " << nombre << endl;
}

template <typename T>
bool Estudiantes<T>::validar()
{
    if (id.empty() || nombre.empty()) {
        cout << "Los datos están vacíos\n";
    }
    return true;
}

template <typename T>
void Lista<T>::agregarElemento(const T& elemento)
{
    if (tamano < 10)
    {
        cantidad[tamano++] = elemento;
    }
    else
    {
        cout << "Lista llena, no se puede agregar mas estudiantes." << endl;
    }
}

template <typename T>
void Lista<T>::mostrarElementos() const
{
    for (int i = 0; i < tamano; ++i)
    {
        cout << cantidad[i] << endl;
    }
}   

template <typename T>
void Lista<T>::eliminarElemento(const T& elemento)
{
    for (int i = 0; i < tamano; ++i)
    {
        if (cantidad[i] == elemento)
        {
            for (int j = i; j < tamano - 1; ++j)
            {
                cantidad[j] = cantidad[j + 1];
            }
            --tamano;
            cout << "Estudiante eliminado." << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}

