#include "Estudiantes.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

typedef Estudiantes<string> EstudianteStr;
typedef Lista<EstudianteStr> ListaEstudianteStr;
typedef int opciones;

int main()
{
    EstudianteStr estudiante;
    ListaEstudianteStr lista;
    opciones opcion;

    EstudianteStr ana("E001", "Ana");
    EstudianteStr luis("E002", "Luis");
    EstudianteStr mateo("","");

    lista.agregarElemento(ana);
    lista.agregarElemento(luis);
    lista.agregarElemento(mateo);

    lista.mostrarElementos();

    bool comparacion = (ana == luis);

    if (ana.validar())
    {
        cout << "Objeto 'Ana' validado" << endl;
    }

    if (luis.validar())
    {
        cout << "Objeto 'Luis' validado" << endl;
    }

    if (mateo.validar())
    {
        cout << "Objeto 'Mateo' validado." << endl;
    }

    lista.eliminarElemento(mateo);

    lista.mostrarElementos();

    cout << "Resultado de la comparación entre Ana y Luis: " << boolalpha << comparacion << endl;

    if (!comparacion)
    {
        cout << "VERIFICACIÓN: El resultado de la comparación es FALSO. (Requisito Cumplido)" << endl;
    }
    else
    {
        cout << "El resultado de la comparación es VERDADERO. ERROR" << endl;
    }

    return 0;
}