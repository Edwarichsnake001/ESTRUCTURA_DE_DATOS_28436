#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Producto {
    int codigo;
    std::string descripcion;
    std::string categoria;
    double peso;
    double precio;

    void print() const {
        std::cout << "|" << std::setw(8) << std::left << codigo
                  << "|" << std::setw(15) << std::left << descripcion
                  << "|" << std::setw(12) << std::left << categoria
                  << "|" << std::setw(7) << std::right << std::fixed << std::setprecision(2) << peso
                  << "|" << std::setw(7) << std::right << std::fixed << std::setprecision(2) << precio << "|";
    }
};

template <typename T>
void printArray(const std::vector<T>& arr) {
    std::cout << "+--------+---------------+------------+-------+-------+\n";
    std::cout << "| Código | Descripción   | Categoría  | Peso  | Precio|\n";
    std::cout << "+--------+---------------+------------+-------+-------+\n";
    for (const auto& item : arr) {
        item.print();
        std::cout << "\n";
    }
    std::cout << "+--------+---------------+------------+-------+-------+\n";
}


int totalComparaciones = 0;

bool esMenor(const Producto& prod1, const Producto& prod2, int& compCount) {
    compCount++; 
    if (prod1.categoria != prod2.categoria) {
        return prod1.categoria < prod2.categoria;
    }

    compCount++;
    if (prod1.precio != prod2.precio) {
       
        return prod1.precio < prod2.precio;
    }

    compCount++; 
    return prod1.peso < prod2.peso;
}

template <typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    
    std::cout << "\n======================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO (SELECTION SORT CON CRITERIO COMPUESTO)    \n";
    std::cout << "======================================================================\n";

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        int compCount = 0;
        bool intercambioOcurrido = false;

        std::cout << "\n--- Pasada " << (i + 1) << " (Buscando el mínimo desde el índice " << i << ") ---\n";

        for (int j = i + 1; j < n; ++j) {
            // Implementar la comparación compuesta
            if (esMenor(arr[j], arr[min_idx], compCount)) {
                min_idx = j; // Nueva posición del mínimo
            }
        }
        totalComparaciones += compCount;

        std::cout << "  -> Búsqueda del Mínimo: " << compCount << " comparaciones necesarias.\n";
        std::cout << "  -> La posición del Mínimo encontrado es: " << min_idx << ".\n";
        
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]); 
            intercambioOcurrido = true;
        }

        std::cout << "  -> ¿Ocurrió un intercambio? " << (intercambioOcurrido ? "SÍ" : "NO") << ".\n";
        
        std::cout << "\nEstado del Vector tras la Pasada " << (i + 1) << ":\n";
        printArray(arr);
    }
    
    // Análisis final
    std::cout << "\n======================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "======================================================================\n";
    std::cout << "Total de Comparaciones (Contando los 3 niveles): " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios realizados: " << n - 1 << " (Siempre ocurre uno por pasada, a menos que el mínimo ya esté en su lugar, pero la lógica de Selection Sort es hacer a lo sumo N-1 intercambios).\n";

}
