// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "Venta.h"

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    std::vector<Venta> ventas = {
        {"V101", "2025-01-10", 350.00, 1},
        {"V102", "2025-01-11", 200.00, 2},
        {"V103", "2025-01-12", 200.00, 3},
        {"V104", "2025-01-09", 500.00, 4},
        {"V105", "2025-01-13", 150.00, 5}};

    cout << "--- Estado Inicial del Arreglo de Ventas ---\n";
    printArray(ventas);

    exchangeSort(ventas);

    cout << "\n--- Estado Final del Arreglo (Ordenado por Valor) ---\n";
    printArray(ventas);

    analizarEstabilidad(ventas);

    return 0;
}

/*
El algoritmo Exchange Sort (Simple) es INESTABLE.
Justificación:
La inestabilidad ocurre porque el algoritmo realiza intercambios basados 
en una condición estricta (`arr[j].valor < arr[i].valor`).

Si tuviéramos dos elementos A y B con el mismo valor (`valor(A) == valor(B)`) 
y A aparece antes que B en el arreglo original, el Exchange Sort puede intercambiarlos 
si un tercer elemento, C, es menor que A y B, pero se compara primero con B.

Más directamente, si `arr[j].valor < arr[i].valor` es la condición de swap, y tenemos 
A=5 en i y B=5 en j, un Exchange Sort estándar puede terminar invirtiendo su orden 
original cuando intenta colocar otro elemento C=4 en la posición de A.

El Exchange Sort simple realiza comparaciones entre elementos no adyacentes (`i` y `j`), 
permitiendo que el elemento con mayor índice (`j`) salte por delante del elemento 
con menor índice (`i`) incluso si sus valores son iguales, o si el elemento en `j`
 ayuda a colocar un elemento anterior.*/