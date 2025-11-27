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