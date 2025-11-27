#pragma once

#include <iostream>
#include <string>
#include <iomanip> // Para formato de tabla

// Estructura que representa una transacción bancaria
struct Transaccion {
    std::string id_transaccion; // id_transaccion [cite: 29]
    double monto;               // monto 
    std::string tipo;           // tipo [cite: 31]
    std::string fecha;          // fecha [cite: 32]

    // Campo de identificación para verificar la estabilidad (orden original)
    int order; 

    // Función para imprimir el registro de manera clara
    void print() const {
        std::cout << "|" << std::setw(5) << std::left << order
                  << "|" << std::setw(15) << std::left << id_transaccion
                  << "|" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << monto
                  << "|" << std::setw(10) << std::left << tipo
                  << "|" << std::setw(10) << std::left << fecha << "|";
    }
};

// Función template para mostrar el estado del arreglo
template <typename T>
void printArray(T arr[], int n) {
    std::cout << "+-----+---------------+--------+----------+----------+\n";
    std::cout << "|Ord. | ID Transacción| Monto  | Tipo     | Fecha    |\n";
    std::cout << "+-----+---------------+--------+----------+----------+\n";
    for (int i = 0; i < n; ++i) {
        arr[i].print();
        std::cout << "\n";
    }
    std::cout << "+-----+---------------+--------+----------+----------+\n";
}

// =========================================================================
// ALGORITMO INSERTION SORT (Implementación Principal)
// =========================================================================

// La función debe desplazar registros completos usando operaciones de movimiento 
template <typename T>
void insertionSort(T arr[], int n) {
    int totalComparaciones = 0;
    int totalDesplazamientos = 0;

    std::cout << "\n=================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO POR MONTO (INSERTION SORT ESTABLE)    \n";
    std::cout << "=================================================================\n";
    
    // Iteración externa: Recorrer el arreglo, i es el índice del primer elemento desordenado
    for (int i = 1; i < n; ++i) {
        T key = arr[i]; // Clave utilizada  (se desplaza el registro completo )
        int j = i - 1;
        int compCount = 0;
        int dispCount = 0;

        std::cout << "\n--- Iteración " << i << " (Clave: ";
        key.print();
        std::cout << ") ---\n";

        // Iteración interna: Mover elementos de la sublista ordenada que son mayores que la clave
        // Criterio de estabilidad: Usar '>':
        //   arr[j].monto > key.monto : Mueve si el elemento a la izquierda es estrictamente mayor.
        //   Esto asegura que elementos con monto IGUAL (arr[j].monto == key.monto) NO se muevan,
        //   preservando su orden original (estabilidad). 
        while (j >= 0 && arr[j].monto > key.monto) {
            arr[j + 1] = arr[j]; // Desplazamiento de registro completo 
            j = j - 1;
            compCount++;
            dispCount++;
        }
        totalComparaciones += compCount;
        totalDesplazamientos += dispCount;

        // Insertar la clave en su posición final
        if (j + 1 != i) {
            arr[j + 1] = key;
        }

        // --- Trazado de Análisis de la Iteración ---
        std::cout << "  -> Comparaciones efectuadas: " << compCount << "\n"; // 
        std::cout << "  -> Desplazamientos realizados: " << dispCount << "\n"; // 
        std::cout << "  -> Estado del arreglo tras esta iteración: \n"; // 
        printArray(arr, n);
    }

    // Análisis Final
    std::cout << "\n=================================================================\n";
    std::cout << "               ANÁLISIS FINAL Y ESTABILIDAD\n";
    std::cout << "=================================================================\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Desplazamientos (movimiento de registros): " << totalDesplazamientos << "\n";
    
    std::cout << "\nPreservación de la Estabilidad (monto igual):\n"; // [cite: 44]
    std::cout << "El algoritmo Insertion Sort es **naturalmente estable** [cite: 45] porque:\n";
    std::cout << "1. La condición de comparación es estricta: `arr[j].monto > key.monto`.\n";
    std::cout << "2. Si dos elementos tienen el mismo monto (`arr[j].monto == key.monto`), la condición es falsa, y la clave (`key`) se inserta **después** del elemento igual (`arr[j]`).\n";
    std::cout << "3. Esto garantiza que si el elemento A estaba antes que el elemento B en el arreglo original y `monto(A) == monto(B)`, A seguirá estando antes que B en el arreglo ordenado, cumpliendo con la definición de estabilidad.\n";

    std::cout << "\nImplicaciones en aplicaciones reales[cite: 46]:\n";
    std::cout << "* **Clasificación Secundaria:** Si ordenas por 'monto' y luego por 'fecha' (en el orden original), un algoritmo estable asegura que las transacciones con el mismo monto mantengan el orden de 'fecha' que tenían antes.\n";
    std::cout << "* **Auditoría:** Permite al sistema mantener el orden cronológico o de ingreso (nuestro campo `order`) dentro de grupos de datos idénticos.\n";
}
