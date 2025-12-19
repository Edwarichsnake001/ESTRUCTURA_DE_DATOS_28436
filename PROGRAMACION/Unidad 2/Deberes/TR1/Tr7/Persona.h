#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Direccion {
    std::string calle;
    int numero;
    std::string ciudad; 
};

struct Persona {
    int id;
    std::string nombre;
    int edad; 
    Direccion direccion; 
    
    void print() const {
        std::cout << "|" << std::setw(3) << id
                  << "|" << std::setw(15) << std::left << nombre
                  << "|" << std::setw(5) << edad
                  << "|" << std::setw(15) << std::left << direccion.ciudad
                  << "|" << std::setw(15) << std::left << direccion.calle << "|";
    }
};

int totalComparaciones = 0;
int totalIntercambios = 0;

bool esMenor(const Persona& p1, const Persona& p2) {
    totalComparaciones++; 
    
    if (p1.direccion.ciudad != p2.direccion.ciudad) {
        return p1.direccion.ciudad < p2.direccion.ciudad;
    }
    
    totalComparaciones++;
    // 2. Criterio: Edad (Ascendente)
    if (p1.edad != p2.edad) {
        return p1.edad < p2.edad;
    }
    
    totalComparaciones++;
    return p1.nombre < p2.nombre;
}

template <typename T>
void exchangeSort(std::vector<T>& arr) {
    int n = arr.size();
    
    std::cout << "\n======================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO (EXCHANGE SORT CON CRITERIO COMPLEJO)    \n";
    std::cout << "======================================================================\n";

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {

            if (esMenor(arr[j], arr[i])) { 

                std::cout << "\n  -> Intercambio forzado:\n";
                std::cout << "     - Elemento i: "; arr[i].print(); std::cout << "\n";
                std::cout << "     - Elemento j: "; arr[j].print(); std::cout << "\n";
                
                std::swap(arr[i], arr[j]); 
                totalIntercambios++;
            }
        }
        
        std::cout << "\nEstado del Arreglo tras la Pasada Externa " << (i + 1) << ":\n";
        std::cout << "+---+---------------+-----+---------------+---------------+\n";
        std::cout << "| ID| Nombre        | Edad| Ciudad        | Calle         |\n";
        std::cout << "+---+---------------+-----+---------------+---------------+\n";
        for (const auto& p : arr) {
            p.print();
            std::cout << "\n";
        }
        std::cout << "+---+---------------+-----+---------------+---------------+\n";
    }

    std::cout << "\n======================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "======================================================================\n";
    std::cout << "Total de Comparaciones (Aprox. N^2 * 3 niveles): " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios realizados: " << totalIntercambios << "\n";
    
   
}
