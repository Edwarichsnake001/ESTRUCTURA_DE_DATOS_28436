#include <iostream>
#include "Estudiante.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <locale>
using namespace std;



int main(){
    vector<Estudiante<string>> estudiantes;
    typedef string Texto;
    typedef int Numero;
    Texto nombre;
    Texto cedula;
    Numero edad;
    Numero opcion;
    Estudiante<string> nuevoEstudiante(nombre, cedula, edad);


    do {
        cout << "=====Menu de opciones:=====\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese el nombre del estudiante: ";
            cin >> nombre;
            cout << "Ingrese la cedula del estudiante: ";
            cin >> cedula;
            cout << "Ingrese la edad del estudiante: ";
            cin >> edad;
            nuevoEstudiante.agregarEstudiante(nombre, cedula, edad);
            estudiantes.push_back(nuevoEstudiante);
        }

    } while (opcion != 2);




}