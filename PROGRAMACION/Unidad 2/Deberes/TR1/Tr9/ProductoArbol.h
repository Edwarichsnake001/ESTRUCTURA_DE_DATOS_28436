#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <cstdlib>  
#include <ctime>    

struct Producto
{
    std::string codigo;
    std::string nombre;
    double precio;
    std::string categoria;

    void print() const
    {
        std::cout << "|" << std::setw(8) << std::left << codigo
                  << "|" << std::setw(15) << std::left << nombre
                  << "|" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << precio
                  << "|" << std::setw(12) << std::left << categoria << "|";
    }
};

template <typename T>
void printSubArray(const std::vector<T> &arr, int low, int high)
{
    std::cout << "[";
    for (int i = low; i <= high; ++i)
    {
        std::cout << arr[i].nombre;
        if (i < high)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

std::vector<std::string> recursionTree;

template <typename T>
int partition(std::vector<T> &arr, int low, int high, int &movimientos)
{

    std::srand(std::time(0)); 
    int random_idx = low + (std::rand() % (high - low + 1));
    std::swap(arr[random_idx], arr[high]);

    T pivot = arr[high]; 
    int i = low - 1; 
    int movPasada = 0;

    std::cout << "  -> Pivote seleccionado (Aleatorio) en índice " << high << ": " << pivot.nombre << " (Precio: " << pivot.precio << ")\n";
    std::cout << "  -> Índices usados (low=" << low << ", high=" << high << ")\n";

  
    for (int j = low; j < high; ++j)
    {
        if (arr[j].precio <= pivot.precio)
        {
            i++;
            std::swap(arr[i], arr[j]);
            movimientos++;
            movPasada++;
        }
    }

    std::swap(arr[i + 1], arr[high]);
    movimientos++;
    movPasada++;

    std::cout << "  -> Movimientos de elementos realizados en la partición: " << movPasada << "\n";

    return i + 1; 
}

template <typename T>
void quickSort(std::vector<T> &arr, int low, int high, int &movimientos, int level = 0)
{
    if (low < high)
    {

        std::string trace = "| Nivel " + std::to_string(level) + " | Subarreglo: ";
        trace += "[" + std::to_string(low) + "-" + std::to_string(high) + "] ";

        int pi = partition(arr, low, high, movimientos);

        trace += "-> Pivote final: " + arr[pi].nombre;
        trace += " -> Subarreglos: Izq [" + std::to_string(low) + "-" + std::to_string(pi - 1) + "]";
        trace += ", Der [" + std::to_string(pi + 1) + "-" + std::to_string(high) + "]";
        recursionTree.push_back(trace);

        quickSort(arr, low, pi - 1, movimientos, level + 1);
        quickSort(arr, pi + 1, high, movimientos, level + 1); 
    }
}

template <typename T>
void sortArray(std::vector<T> &arr)
{
    int movimientos = 0;
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "\n========================================================\n";
    std::cout << "       INICIO DE ORDENAMIENTO (QUICKSORT ALEATORIO)\n";
    std::cout << "========================================================\n";

    quickSort(arr, 0, arr.size() - 1, movimientos);

    std::cout << "\n========================================================\n";
    std::cout << "             ANÁLISIS FINAL DE QUICKSORT\n";
    std::cout << "========================================================\n";
    std::cout << "Total de Movimientos de Elementos (Swaps en Partición): " << movimientos << "\n";

    std::cout << "\nÁrbol de Recursión Generado:\n";
    for (const auto &line : recursionTree)
    {
        std::cout << line << "\n";
    }
}
