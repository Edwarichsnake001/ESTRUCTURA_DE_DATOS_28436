#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

template <typename T>
class Estudiante {
private:
    T nombre;
    T cedula;
    int edad;
public:
    Estudiante(T nombre, T cedula, int edad) : nombre(nombre), cedula(cedula), edad(edad) {}

    void agregarEstudiante(const T& nombre,const T& cedula,const int& edad);
    


};

#include "Estudiante.tpp"


