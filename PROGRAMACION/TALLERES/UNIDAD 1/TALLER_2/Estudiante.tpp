#include <iostream>
#include "Estudiante.h"
#include <string>
using namespace std;

template <typename T>
inline void Estudiante<T>::agregarEstudiante(const T &nombre, const T &cedula, const int &edad)
{
    this->nombre = nombre;
    this->cedula = cedula;
    this->edad = edad;
}

