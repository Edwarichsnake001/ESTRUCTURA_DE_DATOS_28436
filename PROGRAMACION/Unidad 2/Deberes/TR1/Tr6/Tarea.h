#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Tarea
{
    int prioridad;
    std::string descripcion;

    // Constructor simple para la lectura de la proridad y descripcopn / si hay tiempo evitamos usarlo
    Tarea(int p, const std::string &d) : prioridad(p), descripcion(d) {}

    void print() const
    {
        std::cout << "[P" << prioridad << " - " << descripcion << "]";
    }
};

struct NodoTarea
{
    Tarea data;

    NodoTarea(int p, const std::string &d) : data(p, d) {}
};

// Función template para mostrar el estado del vector de punteros
template <typename T>
void printVector(const std::vector<T *> &arr)
{
    std::cout << "Índice (Vector): |";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << std::setw(9) << std::right << i << " |";
    }
    std::cout << "\n------------------";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << "---------------";
    }
    std::cout << "\nValor Apuntado:    |";
    for (const auto &ptr : arr)
    {
        // Acceder a los datos a través del puntero
        std::cout << std::setw(8) << std::right << "P" << ptr->data.prioridad << " |";
    }
    std::cout << "\n";
}

template <typename T>
void bubbleSortPunteros(std::vector<T *> &ptr_arr)
{
    int n = ptr_arr.size();
    bool intercambiado;
    int totalComparaciones = 0;
    int totalIntercambios = 0;

    std::cout << "\n===================================================================\n";
    std::cout << "  INICIO DE ORDENAMIENTO (BUBBLE SORT INTERCAMBIO DE PUNTEROS)       \n";
    std::cout << "===================================================================\n";

    for (int i = 0; i < n - 1; ++i)
    {
        intercambiado = false;
        int compPasada = 0;
        int intercPasada = 0;

        std::cout << "\n--- Pasada " << (i + 1) << " ---\n";

        for (int j = 0; j < n - 1 - i; ++j)
        {

            if (ptr_arr[j]->data.prioridad > ptr_arr[j + 1]->data.prioridad)
            {

                std::swap(ptr_arr[j], ptr_arr[j + 1]);

                intercambiado = true;
                totalIntercambios++;
                intercPasada++;
            }
            totalComparaciones++;
            compPasada++;
        }

        std::cout << "  -> Comparaciones en esta pasada: " << compPasada << "\n";
        std::cout << "  -> Intercambios en esta pasada: " << intercPasada << "\n";

        std::cout << "\nEstado del Vector de Punteros tras la Pasada " << (i + 1) << ":\n";
        printVector(ptr_arr);

        if (!intercambiado)
        {
            std::cout << "  -> **OPTIMIZACIÓN:** Arreglo ordenado. Deteniendo.\n";
            break;
        }
    }

    std::cout << "\n===================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "===================================================================\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios de Punteros: " << totalIntercambios << "\n";
}
