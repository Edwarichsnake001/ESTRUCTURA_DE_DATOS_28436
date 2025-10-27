#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Estudiantes
{
private:
    T id;
    T nombre;

public:

    void ingresarDatos();
    void mostrarDatos() const;
    bool validar();

    bool operator==(const Estudiantes& otro) const {
        return id == otro.id;
    }

    friend ostream& operator<<(ostream& os, const Estudiantes& estudiante) {
        os << "ID: " << estudiante.id << ", Nombre: " << estudiante.nombre;
        return os;

    }  
};


template <typename T>
class Lista {
private:
    T cantidad[10];
    int tamano;

public:
   Lista() : tamano(0) {}

    void agregarElemento(const T& elemento);
    void mostrarElementos() const;
    void eliminarElemento(const T& elemento);
};

#include "Estudiantes.tpp"