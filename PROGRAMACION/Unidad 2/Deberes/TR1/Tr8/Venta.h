#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Venta {
    std::string id_venta;
    std::string fecha;
    double valor; 
    
    int order; 

    void print() const {
        std::cout << "|" << std::setw(3) << order 
                  << "|" << std::setw(10) << std::left << id_venta
                  << "|" << std::setw(10) << std::left << fecha
                  << "|" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << valor << "|";
    }
};

template <typename T>
void printArray(const std::vector<T>& arr) {
    std::cout << "+---+----------+----------+--------+\n";
    std::cout << "|Ord| ID Venta | Fecha    | Valor  |\n";
    std::cout << "+---+----------+----------+--------+\n";
    for (const auto& item : arr) {
        item.print();
        std::cout << "\n";
    }
    std::cout << "+---+----------+----------+--------+\n";
}

int totalComparaciones = 0;
int totalIntercambios = 0;

template <typename T>
void exchangeSort(std::vector<T>& arr) {
    int n = arr.size();
    
    std::cout << "\n========================================================\n";
    std::cout << "        INICIO DE ORDENAMIENTO (EXCHANGE SORT)\n";
    std::cout << "========================================================\n";

    for (int i = 0; i < n - 1; ++i) {
        std::cout << "\n--- Pasada Externa i = " << i << " ---\n";

        for (int j = i + 1; j < n; ++j) {

            totalComparaciones++;
            std::cout << "  -> Comparando Valor[" << i << "] (" << arr[i].valor << ") vs Valor[" << j << "] (" << arr[j].valor << ").\n";

            if (arr[j].valor < arr[i].valor) { 

                std::cout << "  -> INTERCAMBIO: Los elementos están fuera de orden. Swapping Venta(Ord " << arr[i].order << ") con Venta(Ord " << arr[j].order << ").\n";
                
                std::swap(arr[i], arr[j]); 
                totalIntercambios++;
            }
        }

        std::cout << "\nEstado del Arreglo después de la Pasada " << (i + 1) << ":\n";
        printArray(arr);
    }
}

template <typename T>
void analizarEstabilidad(const std::vector<T>& arr) {
    std::cout << "\n========================================================\n";
    std::cout << "           ANÁLISIS FORMAL DE ESTABILIDAD\n";
    std::cout << "========================================================\n";

    int index2 = -1; 
    int index3 = -1;

    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i].order == 2) index2 = i;
        if (arr[i].order == 3) index3 = i;
    }
    
    std::cout << "Elementos de prueba (Valor = $200.00):\n";
    std::cout << "  - V102 (Orden Original 2) está en la posición final: " << index2 << "\n";
    std::cout << "  - V103 (Orden Original 3) está en la posición final: " << index3 << "\n";
    
    std::cout << "\nComparación de Índices:\n";
    if (index2 < index3) {
        std::cout << "V102 (Ord 2) < V103 (Ord 3): El orden original se ha preservado.\n";
    } else {
        std::cout << "V102 (Ord 2) > V103 (Ord 3): El orden original NO se ha preservado.\n";
    }
    
    
    std::cout << "\n--- Resumen de Costos ---\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios: " << totalIntercambios << "\n";
}

