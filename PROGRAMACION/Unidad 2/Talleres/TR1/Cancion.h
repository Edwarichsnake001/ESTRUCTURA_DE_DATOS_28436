#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Cancion
{
    string id;         
    string titulo;      
    double duracion;    

    void imprimir() const
    {
        cout << "|" << std::setw(15) << std::left << id
             << "|" << std::setw(30) << std::left << titulo
             << "|" << std::setw(10) << std::right << std::fixed << std::setprecision(2) << duracion << "s |\n";
    }
};

template <typename T, typename Comp>
int particion(vector<T> &arr, int low, int high, Comp comp)
{
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        // El criterio de ordenamiento es completamente definido por la lambda 'comp'.
        // Aquí usamos: arr[j] es 'menor o igual' que pivot.
        if (comp(arr[j], pivot) || (!comp(pivot, arr[j]) && !comp(arr[j], pivot))) 
        {
            i++;
            // Intercambio
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Colocar el pivote en su posición final
    T temp_pivot = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp_pivot;

    return i + 1;
}

template <typename T, typename Comp>
void quickSort(vector<T> &arr, int low, int high, Comp comp)
{
    if (low < high)
    {
        int ind = particion(arr, low, high, comp);
        quickSort(arr, low, ind - 1, comp);
        quickSort(arr, ind + 1, high, comp);
    }
}

template <typename T>
int busquedaBinariaPorTitulo(const std::vector<T> &arr, const std::string &tituloBuscado)
{
    int bajo = 0;
    int alto = arr.size() - 1;

    while (bajo <= alto)
    {
        int medio = bajo + (alto - bajo) / 2;
        
        if (arr[medio].titulo < tituloBuscado) 
        {
            // El título en medio es alfabéticamente menor, busca en la mitad superior.
            bajo = medio + 1;
        }
        else if (tituloBuscado < arr[medio].titulo) 
        {
            // El título buscado es alfabéticamente menor, busca en la mitad inferior.
            alto = medio - 1;
        }
        else
        {
            return medio;
        }
    }

    return -1; // No encontrado
}

template <typename T>
void imprimirVector(const vector<T> &arr)
{
    cout << "+---------------+------------------------------+-------------+\n";
    cout << "| ID            | Título                       |  Duración   |\n";
    cout << "+---------------+------------------------------+-------------+\n";
    for (const auto &item : arr)
    {
        item.imprimir();
    }
    cout << "+---------------+------------------------------+-------------+\n";
}