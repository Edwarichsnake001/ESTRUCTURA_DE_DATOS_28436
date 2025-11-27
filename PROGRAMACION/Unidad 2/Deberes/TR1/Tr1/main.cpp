#include <iostream>
#include <locale.h>
#include "ListaSimple.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    ListaSimple cursos;

    // Construir la lista enlazada dinámica (usaremos un orden inverso para demostrar el ordenamiento)
    cout << "--- Construcción de la Lista (Ingreso de Cursos) ---\n";
    
    // NOTA: Agregar al inicio (add) para simular una construcción rápida y desordenada
    cursos.add(402, "Física 2");
    cursos.add(203, "EDO");
    cursos.add(501, "Metodología Investigativa");
    cursos.add(101, "Matemática");
    cursos.add(315, "Cultura Ambiental");
    
    cout << "Lista Original (Desordenada):\n";
    cursos.print();
    cout << "------------------------------------------------------\n";

    // 1. Aplicar Insertion Sort (seleccionando nodo clave, buscando posición, desplazando, insertando)
    cursos.insertionSort();

    // 2. Mostrar la lista final ordenada
    cout << "\nLista Final Ordenada por ID:\n";
    cursos.print();

    // 3. Presentar el análisis final
    cursos.showFinalAnalysis();

    return 0;
}