#include <iostream>
#include <locale.h>
#include "Proceso.h" 

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    ListaDobleCircular procesos;

    cout << "--- Construcción de la Lista Doblemente Enlazada Circular ---\n";
    procesos.add({101, 50, 4}); 
    procesos.add({204, 10, 2}); 
    procesos.add({310, 80, 5}); 
    procesos.add({402, 25, 3}); 
    procesos.add({507, 45, 1}); 

    cout << "Lista Original (Desordenada):\n";
    procesos.print(); 

    procesos.sort();

    cout << "\n--- Lista Final (Ordenada por Prioridad - Simulación) ---\n";
    procesos.print(); 

    // Presentar el análisis
    procesos.showAnalysis();

    return 0;
}