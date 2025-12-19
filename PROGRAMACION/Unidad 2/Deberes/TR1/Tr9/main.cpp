#include <iostream>
#include <locale.h>
#include <vector>
#include "ProductoArbol.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");

    std::vector<Producto> productos = {

        {"D01", "Destornillador", 15.00, "Herramienta"}, 
        {"M05", "Martillo",       30.00, "Herramienta"}, 
        {"T03", "Tuerca M5",       1.50, "Fijacion"},   
        {"B02", "Broca 1/4",      12.00, "Herramienta"},
        {"C01", "Cinta Metrica",  20.00, "Medicion"}, 
        {"C02", "Clavos",          5.00, "Fijacion"}  
    };
    
    cout << "--- Estado Inicial del Vector de Productos ---\n";
    cout << "+--------+---------------+--------+------------+\n";
    cout << "| Código | Nombre        | Precio | Categoría  |\n";
    cout << "+--------+---------------+--------+------------+\n";
    for (const auto& p : productos) {
        p.print();
        cout << "\n";
    }
    cout << "+--------+---------------+--------+------------+\n";

    sortArray(productos);

    cout << "\n--- Estado Final del Vector (Ordenado por Precio) ---\n";
    cout << "+--------+---------------+--------+------------+\n";
    cout << "| Código | Nombre        | Precio | Categoría  |\n";
    cout << "+--------+---------------+--------+------------+\n";
    for (const auto& p : productos) {
        p.print();
        cout << "\n";
    }
    cout << "+--------+---------------+--------+------------+\n";

    return 0;
}

/*Análisis de Rendimiento y Aleatorización del Pivote:
1. Rendimiento Promedio: Quicksort tiene un rendimiento promedio excelente de 
O(N log N).

2. Impacto de la Aleatorización: La aleatorización del pivote es una estrategia 
para evitar el peor caso O(N^2), que ocurre cuando el pivote siempre resulta ser 
el elemento más pequeño o el más grande.

3. Garantía Probabilística: Al elegir un pivote aleatorio, se asegura que, 
en promedio, el arreglo se dividirá en dos subarreglos de tamaño similar, 
manteniendo la complejidad en O(N log N) con alta probabilidad, 
independientemente del orden inicial de los datos.*/