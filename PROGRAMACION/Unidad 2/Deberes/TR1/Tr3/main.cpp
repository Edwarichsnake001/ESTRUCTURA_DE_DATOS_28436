// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "Producto.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");

    std::vector<Producto> productos = {
        {101, "Leche", "Lacteo", 1.05, 3.50}, 
        {204, "Jugo Naranja", "Bebida", 0.50, 2.00}, 
        {310, "Yogurt", "Lacteo", 0.30, 1.20}, 
        {402, "Queso", "Lacteo", 0.40, 1.20}, 
        {507, "Agua 1L", "Bebida", 1.10, 2.00}  
    };
    
    cout << "--- Estado Inicial del Vector de Productos ---\n";
    printArray(productos);

    selectionSort(productos);

    cout << "\n--- Estado Final del Vector (Ordenado: Categoría -> Precio -> Peso) ---\n";
    printArray(productos);

    return 0;
}

/*Selection Sort es ideal para registros 'pesados' (grandes estructuras) porque minimiza el costo de movimiento.

Mínimo Movimiento: Realiza exactamente $N-1$ intercambios (en el peor y mejor caso, donde $N$ es el tamaño del arreglo).
Costo de Movimiento: Aunque el intercambio es costoso porque mueve el registro completo, este costo solo se paga una vez 
por pasada.
Costo de Comparación: El costo de las comparaciones O(N^2)S sigue siendo alto, pero en escenarios donde 
el movimiento es mucho más costoso que la comparación, Selection Sort es la mejor opción cuadrática.*/