#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath> 
#include <algorithm> 

struct Usuario {
    std::string id_usuario;
    int tiempo_espera;      
};

struct NodoCola {
    Usuario user;
    NodoCola* next;
    NodoCola(const Usuario& u) : user(u), next(nullptr) {}
};

class ColaUsuarios {
private:
    NodoCola* frente;
    NodoCola* final;
    int numUsuarios; 

public:
    ColaUsuarios() : frente(nullptr), final(nullptr), numUsuarios(0) {}

    int getNumUsuarios() const {
        return numUsuarios;
    }

    void enqueue(const Usuario& u) {
        NodoCola* nuevo = new NodoCola(u);
        if (final) {
            final->next = nuevo;
        } else {
            frente = nuevo;
        }
        final = nuevo;
        numUsuarios++;
    }

    double calcularPromedio() const {
        if (numUsuarios == 0) return 0.0;

        double sumaTiempos = 0.0;
        NodoCola* actual = frente;
        while (actual) {
            sumaTiempos += actual->user.tiempo_espera;
            actual = actual->next;
        }
        return std::round((sumaTiempos / numUsuarios) * 100.0) / 100.0; 
    }

    void print() const {
        std::cout << "[Promedio: " << std::fixed << std::setprecision(2) << calcularPromedio() << " min, Usuarios: " << numUsuarios << "]";
    }
};

template <typename T>
void printArray(const std::vector<T>& arr) {
    std::cout << "+---------------------------------------------------+\n";
    std::cout << "| Posición | Contenido de la Cola                      |\n";
    std::cout << "+----------+-----------------------------------------+\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "| " << std::setw(8) << std::left << i << " | ";
        arr[i].print();
        std::cout << std::string(38 - 19 - std::to_string(arr[i].calcularPromedio()).length() - std::to_string(arr[i].getNumUsuarios()).length(), ' ') << "|\n";
    }
    std::cout << "+----------+-----------------------------------------+\n";
}

template <typename T>
void bubbleSortOptimizado(std::vector<T>& arr) {
    int n = arr.size();
    bool intercambiado;
    int totalComparaciones = 0;
    int totalIntercambios = 0;
    std::vector<double> historialPromedios;

    std::cout << "\n=================================================================\n";
    std::cout << "       INICIO DE ORDENAMIENTO (BUBBLE SORT OPTIMIZADO)\n";
    std::cout << "=================================================================\n";

    for (int i = 0; i < n - 1; ++i) {
        intercambiado = false;
        int compPasada = 0;
        int intercPasada = 0;

        std::cout << "\n--- Pasada " << (i + 1) << " ---\n";

        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j].calcularPromedio() > arr[j + 1].calcularPromedio()) {
                std::swap(arr[j], arr[j + 1]); 
                intercambiado = true;
                totalIntercambios++;
                intercPasada++;
            }
            totalComparaciones++;
            compPasada++;
        }
        
        std::cout << "  -> Comparaciones realizadas: " << compPasada << "\n";
        std::cout << "  -> Intercambios efectuados: " << intercPasada << "\n";
        
        std::cout << "  -> Promedios después de la pasada: ";
        for(const auto& cola : arr) {
            double prom = cola.calcularPromedio();
            historialPromedios.push_back(prom);
            std::cout << prom << " | ";
        }
        std::cout << "\n";

        if (!intercambiado) {
            std::cout << "  -> **OPTIMIZACIÓN DETECTADA:** Pasada " << (i + 1) << " finalizada sin cambios. El arreglo está ordenado. Se detiene el algoritmo.\n";
            break; 
        }
    }

    // Análisis Final
    std::cout << "\n=================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "=================================================================\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios: " << totalIntercambios << "\n";
}