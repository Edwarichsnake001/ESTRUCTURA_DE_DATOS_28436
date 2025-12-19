#include <iostream>
#include <locale.h>
#include "Libro.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    ListaDoble libros;

    // Construir la lista con datos desordenados para probar la lógica de comparación y el swap
    cout << "--- Construcción de la Lista Doblemente Enlazada ---\n";
    libros.add({"El Quijote", "Cervantes, M.", 1605, "1234"}); // A
    libros.add({"Cien Años", "García Márquez, G.", 1967, "5678"}); // B (Mínimo por Autor)
    libros.add({"La Odisea", "Homero", -800, "9012"}); // C
    libros.add({"El Amor", "García Márquez, G.", 1985, "3456"}); // D (Mismo Autor que B, Mayor Año)
    libros.add({"Fundacion", "Asimov, I.", 1951, "7890"}); // E

    cout << "Lista Original (Desordenada):\n";
    libros.print();

    // Aplicar Selection Sort
    libros.selectionSort();

    cout << "\n--- Lista Final Ordenada (Autor -> Año) ---\n";
    libros.print();

    // Presentar el análisis final y la tabla de resultados
    libros.showResultsTable();
    libros.showFinalAnalysis();

    return 0;
}

/*Ventajas de la Lista Doblemente Enlazada para Selection Sort:
Simplificación del Intercambio (Relativa): Aunque la lógica de intercambio de nodos sigue siendo compleja, 
la presencia del puntero `prev` facilita re-enlazar los nodos vecinos. 
En una lista simple, re-enlazar el nodo anterior requeriría recorrer toda la lista desde el inicio para encontrarlo.

Acceso Bidireccional (Potencial): Permite recorrer la lista hacia adelante (`next`) para la búsqueda del mínimo y, 
si fuera necesario para una adaptación del algoritmo, retroceder (`prev`).
Manipulación de Punteros Fija: A pesar de la complejidad, el intercambio de dos nodos requiere un número fijo 
(constante, O(1)) de re-asignaciones de punteros (generalmente 6-8 punteros) independientemente del tamaño de la lista, 
lo cual es más eficiente que el desplazamiento de registros completos en un arreglo pesado.*/