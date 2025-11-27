#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

// Estructura que representa un producto
struct Producto {
    int codigo;
    std::string descripcion;
    std::string categoria;
    double peso;
    double precio;

    // Función para imprimir el registro de manera clara
    void print() const {
        std::cout << "|" << std::setw(8) << std::left << codigo
                  << "|" << std::setw(15) << std::left << descripcion
                  << "|" << std::setw(12) << std::left << categoria
                  << "|" << std::setw(7) << std::right << std::fixed << std::setprecision(2) << peso
                  << "|" << std::setw(7) << std::right << std::fixed << std::setprecision(2) << precio << "|";
    }
};

// Función template para mostrar el estado del arreglo
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

// Globales para el análisis
int totalComparaciones = 0;

// =========================================================================
// FUNCIÓN DE COMPARACIÓN COMPUESTA (Prioridad: Categoría -> Precio -> Peso)
// =========================================================================
// Retorna true si prod1 es "menor" o tiene mayor prioridad que prod2
bool esMenor(const Producto& prod1, const Producto& prod2, int& compCount) {
    compCount++; // Comparación 1: Categoría
    if (prod1.categoria != prod2.categoria) {
        // 1. Categoría (orden alfabético - el menor es el que va primero)
        return prod1.categoria < prod2.categoria;
    }

    compCount++; // Comparación 2: Precio
    if (prod1.precio != prod2.precio) {
        // 2. Precio (ascendente - el menor es el que va primero)
        return prod1.precio < prod2.precio;
    }

    compCount++; // Comparación 3: Peso
    // 3. Peso (ascendente - el menor es el que va primero)
    return prod1.peso < prod2.peso;
}

// =========================================================================
// ALGORITMO SELECTION SORT (Implementación Principal)
// =========================================================================
template <typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    
    std::cout << "\n======================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO (SELECTION SORT CON CRITERIO COMPUESTO)    \n";
    std::cout << "======================================================================\n";

    // Iteración externa: El límite de la sublista desordenada
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        int compCount = 0;
        bool intercambioOcurrido = false;

        std::cout << "\n--- Pasada " << (i + 1) << " (Buscando el mínimo desde el índice " << i << ") ---\n";

        // Iteración interna: Buscar el mínimo en la sublista restante [i...n-1]
        for (int j = i + 1; j < n; ++j) {
            // Implementar la comparación compuesta
            if (esMenor(arr[j], arr[min_idx], compCount)) {
                min_idx = j; // Nueva posición del mínimo
            }
        }
        totalComparaciones += compCount;

        // Mostrar el proceso de búsqueda y el mínimo
        std::cout << "  -> Búsqueda del Mínimo: " << compCount << " comparaciones necesarias.\n";
        std::cout << "  -> La posición del Mínimo encontrado es: " << min_idx << ".\n";
        
        // Intercambio: si el mínimo no está en la posición actual (i)
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]); // Intercambio de registros completos
            intercambioOcurrido = true;
        }

        // Indicar si ocurrió o no un intercambio
        std::cout << "  -> ¿Ocurrió un intercambio? " << (intercambioOcurrido ? "SÍ" : "NO") << ".\n";
        
        // Mostrar el vector completo luego de cada iteración externa
        std::cout << "\nEstado del Vector tras la Pasada " << (i + 1) << ":\n";
        printArray(arr);
    }
    
    // Análisis final
    std::cout << "\n======================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "======================================================================\n";
    std::cout << "Total de Comparaciones (Contando los 3 niveles): " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios realizados: " << n - 1 << " (Siempre ocurre uno por pasada, a menos que el mínimo ya esté en su lugar, pero la lógica de Selection Sort es hacer a lo sumo N-1 intercambios).\n";
    
    std::cout << "\nAnálisis: Selection Sort es eficiente cuando los registros son pesados:\n";
    std::cout << "Selection Sort es ideal para registros 'pesados' (grandes estructuras) porque minimiza el costo de **movimiento**.\n";
    std::cout << "1. **Mínimo Movimiento:** Realiza exactamente $N-1$ intercambios (en el peor y mejor caso, donde $N$ es el tamaño del arreglo).\n";
    std::cout << "2. **Costo de Movimiento:** Aunque el intercambio es costoso porque mueve el registro completo (ej. copiar 500 bytes de datos), este costo solo se paga una vez por pasada.\n";
    std::cout << "3. **Costo de Comparación:** El costo de las comparaciones ($mathcal{O}(N^2)$) sigue siendo alto, pero en escenarios donde el movimiento es mucho más costoso que la comparación (e.g., nuestra comparación tiene 3 niveles, pero el registro tiene 100 campos), Selection Sort es la mejor opción cuadrática.\n";
}
