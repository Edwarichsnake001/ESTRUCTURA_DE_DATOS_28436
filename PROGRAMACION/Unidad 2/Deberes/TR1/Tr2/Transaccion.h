#pragma once

#include <iostream>
#include <string>
#include <iomanip>

struct Transaccion {
    std::string id_transaccion;
    double monto;              
    std::string tipo;          
    std::string fecha;          

    int order; 

    void imprimir() const {
        std::cout << "|" << std::setw(5) << std::left << order
                  << "|" << std::setw(15) << std::left << id_transaccion
                  << "|" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << monto
                  << "|" << std::setw(10) << std::left << tipo
                  << "|" << std::setw(10) << std::left << fecha << "|";
    }
};

template <typename T>
void imprimirArray(T arr[], int n) {
    std::cout << "+-----+---------------+--------+----------+----------+\n";
    std::cout << "|Ord. | ID Transacción| Monto  | Tipo     | Fecha    |\n";
    std::cout << "+-----+---------------+--------+----------+----------+\n";
    for (int i = 0; i < n; ++i) {
        arr[i].imprimir();
        std::cout << "\n";
    }
    std::cout << "+-----+---------------+--------+----------+----------+\n";
}

template <typename T>
void insertionSort(T arr[], int n) {
    int totalComparaciones = 0;
    int totalDesplazamientos = 0;

    std::cout << "\n=================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO POR MONTO (INSERTION SORT ESTABLE)    \n";
    std::cout << "=================================================================\n";

    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        int compCount = 0;
        int dispCount = 0;

        std::cout << "\n--- Iteración " << i << " (Clave: ";
        key.imprimir();
        std::cout << ") ---\n";

        while (j >= 0 && arr[j].monto > key.monto) {
            arr[j + 1] = arr[j]; 
            j = j - 1;
            compCount++;
            dispCount++;
        }
        totalComparaciones += compCount;
        totalDesplazamientos += dispCount;

        if (j + 1 != i) {
            arr[j + 1] = key;
        }

        std::cout << "  -> Comparaciones efectuadas: " << compCount << "\n"; // 
        std::cout << "  -> Desplazamientos realizados: " << dispCount << "\n"; // 
        std::cout << "  -> Estado del arreglo tras esta iteración: \n"; // 
        imprimirArray(arr, n);
    }

    std::cout << "\n=================================================================\n";
    std::cout << "               ANÁLISIS FINAL Y ESTABILIDAD\n";
    std::cout << "=================================================================\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Desplazamientos (movimiento de registros): " << totalDesplazamientos << "\n";
    
   
}
