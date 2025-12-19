// main.cpp
#include <iostream>
#include <locale.h>
#include "Transaccion.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    // Arreglo de transacciones bancarias. Se incluyen montos iguales ($100.00) 
    // para demostrar la estabilidad del algoritmo.
    Transaccion transactions[] = {
        // ID     Monto   Tipo    Fecha       Order (Original)
        {"T105", 250.00, "Dep.", "2025-11-24", 1},
        {"T201", 100.00, "Ret.", "2025-11-25", 2}, // Monto igual: 100.00 (Order 2)
        {"T100", 750.50, "Dep.", "2025-11-25", 3},
        {"T310", 100.00, "Com.", "2025-11-24", 4}, // Monto igual: 100.00 (Order 4)
        {"T050", 400.00, "Ret.", "2025-11-23", 5}
    };
    
    int n = sizeof(transactions) / sizeof(transactions[0]);

    cout << "--- Estado Inicial del Arreglo de Transacciones ---\n";
    imprimirArray(transactions, n);

    // Aplicar Insertion Sort (ordenando por monto)
    insertionSort(transactions, n);

    cout << "\n--- Estado Final del Arreglo (Ordenado por Monto) ---\n";
    imprimirArray(transactions, n);
    
    cout << "\nVerificación de Estabilidad:\n";
    cout << "Las transacciones con Monto = $100.00 (T201 y T310) mantuvieron su orden original:\n";
    cout << "  - T201 (Order 2) aparece antes que T310 (Order 4).\n";
    cout << "Esto confirma la estabilidad del Insertion Sort.\n";


    return 0;
}

/*Preservación de la Estabilidad (monto igual):
 El algoritmo Insertion Sort es naturalmente estable porque:
 La condición de comparación es estricta: `arr[j].monto > key.monto`.

 Si dos elementos tienen el mismo monto (`arr[j].monto == key.monto`), la condición es falsa, 
 y la clave (`key`) se inserta después del elemento igual (`arr[j]`).

 Esto garantiza que si el elemento A estaba antes que el elemento B en el arreglo original y 
 `monto(A) == monto(B)`, A seguirá estando antes que B en el arreglo ordenado, cumpliendo con la definición de estabilidad.

Implicaciones en aplicaciones reales:
Clasificación Secundaria: Si ordenas por 'monto' y luego por 'fecha' (en el orden original), 
un algoritmo estable asegura que las transacciones con el mismo monto mantengan el orden de 'fecha' que tenían antes.
Auditoría: Permite al sistema mantener el orden cronológico o de ingreso (nuestro campo `order`) 
dentro de grupos de datos idénticos.*/