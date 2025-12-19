// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "ColaUsuarios.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    std::vector<ColaUsuarios> arregloColas;

    ColaUsuarios c1;
    c1.enqueue({"U001", 10});
    c1.enqueue({"U002", 15});
    c1.enqueue({"U003", 15});
    arregloColas.push_back(c1);

    ColaUsuarios c2;
    c2.enqueue({"U010", 5});
    c2.enqueue({"U011", 5});
    arregloColas.push_back(c2);

    ColaUsuarios c3;
    c3.enqueue({"U020", 8});
    c3.enqueue({"U021", 12});
    c3.enqueue({"U022", 10});
    arregloColas.push_back(c3);

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

/*Ineficiencia de Bubble Sort con Comparaciones Costosas:
Bubble Sort se vuelve ineficiente porque en cada comparación 
(`arr[j].calcularPromedio() > arr[j+1].calcularPromedio()`), debe llamar a una función 
que requiere **recorrer y sumar** todos los elementos internos de la cola. 

Si cada cola tiene K elementos, la comparación es O(K).
Como Bubble Sort tiene una complejidad O(N^2) en el peor caso, 
la complejidad total se convierte en O(N^2 * K), donde:
N: Número de colas en el arreglo.
K: Número promedio de usuarios en cada cola.
Si K es grande, el factor O(N^2) se amplifica enormemente, haciendo el algoritmo muy lento.*/