// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "Producto.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    // Crear un vector de productos. Los datos están diseñados para probar la comparación compuesta:
    // P1 y P5 tienen la misma categoría (Bebida), forzando la comparación por Precio.
    // P5 y P3 tienen diferente categoría.
    // P3 y P2 tienen la misma categoría y el mismo precio, forzando la comparación por Peso.
    std::vector<Producto> productos = {
        // Código | Descripción | Categoría | Peso | Precio
        {101, "Leche", "Lacteo", 1.05, 3.50}, // P0 (Mínimo final)
        {204, "Jugo Naranja", "Bebida", 0.50, 2.00}, // P1
        {310, "Yogurt", "Lacteo", 0.30, 1.20}, // P2
        {402, "Queso", "Lacteo", 0.40, 1.20}, // P3 (Igual Precio que P2, mayor Peso)
        {507, "Agua 1L", "Bebida", 1.10, 2.00}  // P4 (Igual Precio que P1, mayor Peso)
    };
    
    cout << "--- Estado Inicial del Vector de Productos ---\n";
    printArray(productos);

    // Aplicar Selection Sort
    selectionSort(productos);

    cout << "\n--- Estado Final del Vector (Ordenado: Categoría -> Precio -> Peso) ---\n";
    printArray(productos);

    return 0;
}