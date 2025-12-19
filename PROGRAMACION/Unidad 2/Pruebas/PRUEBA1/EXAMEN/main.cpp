#include <iostream>
#include <locale.h>
#include "ListaSimple.h"

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    ListaSimple estudiante;

    cout << "--- Construcción de la Lista (Ingreso de Estudiantes) ---\n";

    estudiante.insertar("E001","Mateo",17);
    estudiante.insertar("E002","Lionel",20);
    estudiante.insertar("E003","Rodrygo",18);
    estudiante.insertar("E004","Alexander",12);
    estudiante.insertar("E005","Natalia",14);
    estudiante.insertar("E006","Luis",10);

    cout << "Lista original (Desorden de notas)\n";
    estudiante.mostrar();
    cout << "------------------------------------------------------\n";

    estudiante.insertionSort();

    cout <<"====LISTA ORDENADA POR NOTA (MENOR A MAYOR)====\n";
    estudiante.mostrar();



    return 0;
}
