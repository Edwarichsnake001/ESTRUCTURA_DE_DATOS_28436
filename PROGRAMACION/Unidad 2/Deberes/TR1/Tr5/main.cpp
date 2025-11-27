// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "ColaUsuarios.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    // Crear el arreglo donde cada elemento es una cola dinámica de usuarios [cite: 88]
    std::vector<ColaUsuarios> arregloColas;

    // Cola 1: Promedio alto (ej. 13.33 min)
    ColaUsuarios c1;
    c1.enqueue({"U001", 10});
    c1.enqueue({"U002", 15});
    c1.enqueue({"U003", 15});
    arregloColas.push_back(c1);

    // Cola 2: Promedio bajo (ej. 5.00 min)
    ColaUsuarios c2;
    c2.enqueue({"U010", 5});
    c2.enqueue({"U011", 5});
    arregloColas.push_back(c2);

    // Cola 3: Promedio medio (ej. 10.00 min)
    ColaUsuarios c3;
    c3.enqueue({"U020", 8});
    c3.enqueue({"U021", 12});
    c3.enqueue({"U022", 10});
    arregloColas.push_back(c3);

    // Cola 4: Promedio medio-alto (ej. 11.00 min)
    ColaUsuarios c4;
    c4.enqueue({"U030", 11});
    arregloColas.push_back(c4);
    
    cout << "--- Estado Inicial del Arreglo de Colas ---\n";
    printArray(arregloColas);

    // Aplicar Bubble Sort Optimizado
    bubbleSortOptimizado(arregloColas);

    cout << "\n--- Estado Final del Arreglo (Ordenado por Promedio) ---\n";
    printArray(arregloColas);

    return 0;
}