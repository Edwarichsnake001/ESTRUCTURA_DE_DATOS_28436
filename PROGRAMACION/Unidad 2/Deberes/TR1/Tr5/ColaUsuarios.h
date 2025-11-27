#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath> 

// =========================================================================
// ESTRUCTURA INTERNA: USUARIO
// =========================================================================
struct Usuario {
    std::string id_usuario; // id_usuario [cite: 90]
    int tiempo_espera;      // tiempo_espera (en minutos) [cite: 91]
};

// =========================================================================
// NODO DE LA COLA DINÁMICA
// =========================================================================
struct NodoCola {
    Usuario user;
    NodoCola* next;
    NodoCola(const Usuario& u) : user(u), next(nullptr) {}
};

// =========================================================================
// ESTRUCTURA EXTERNA: COLA DE USUARIOS
// =========================================================================
class ColaUsuarios {
private:
    NodoCola* frente;
    NodoCola* final;
    int numUsuarios; // Contador de elementos para el promedio

public:
    ColaUsuarios() : frente(nullptr), final(nullptr), numUsuarios(0) {}

    int getNumUsuarios() const {
        return numUsuarios;
    }

    // Implementación del Encolar
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

    // Función que calcula el promedio de tiempo de espera 
    double calcularPromedio() const {
        if (numUsuarios == 0) return 0.0;

        double sumaTiempos = 0.0;
        NodoCola* actual = frente;
        while (actual) {
            sumaTiempos += actual->user.tiempo_espera;
            actual = actual->next;
        }
        // Usamos round para una mejor visualización de los promedios
        return std::round((sumaTiempos / numUsuarios) * 100.0) / 100.0; 
    }

    // Función de impresión para el trazado
    void print() const {
        std::cout << "[Promedio: " << std::fixed << std::setprecision(2) << calcularPromedio() << " min, Usuarios: " << numUsuarios << "]";
    }
};

// Función template para mostrar el estado del arreglo de colas
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

// =========================================================================
// ALGORITMO BUBBLE SORT OPTIMIZADO
// =========================================================================
template <typename T>
void bubbleSortOptimizado(std::vector<T>& arr) {
    int n = arr.size();
    bool intercambiado;
    int totalComparaciones = 0;
    int totalIntercambios = 0;
    std::vector<double> historialPromedios;

    std::cout << "\n=================================================================\n";
    std::cout << "      INICIO DE ORDENAMIENTO (BUBBLE SORT OPTIMIZADO)\n";
    std::cout << "=================================================================\n";

    // Bucle externo: recorre todas las pasadas (hasta n-1 o hasta que esté ordenado)
    for (int i = 0; i < n - 1; ++i) {
        intercambiado = false;
        int compPasada = 0;
        int intercPasada = 0;

        std::cout << "\n--- Pasada " << (i + 1) << " ---\n";

        // Bucle interno: realiza las comparaciones e intercambios en la pasada actual
        for (int j = 0; j < n - 1 - i; ++j) {
            // Comparar colas basándose en su promedio 
            if (arr[j].calcularPromedio() > arr[j + 1].calcularPromedio()) {
                std::swap(arr[j], arr[j + 1]); // Intercambio de estructuras (colas) completas
                intercambiado = true;
                totalIntercambios++;
                intercPasada++;
            }
            totalComparaciones++;
            compPasada++;
        }
        
        // Registrar la evolución de los promedios
        std::cout << "  -> Comparaciones realizadas: " << compPasada << " [cite: 100]\n";
        std::cout << "  -> Intercambios efectuados: " << intercPasada << " [cite: 101]\n";
        
        // Guardar el estado actual de los promedios para el gráfico final [cite: 103]
        std::cout << "  -> Promedios después de la pasada: ";
        for(const auto& cola : arr) {
            double prom = cola.calcularPromedio();
            historialPromedios.push_back(prom);
            std::cout << prom << " | ";
        }
        std::cout << "\n";

        // Optimización: Detectar si hubo una pasada sin cambios
        if (!intercambiado) {
            std::cout << "  -> **OPTIMIZACIÓN DETECTADA:** Pasada " << (i + 1) << " finalizada sin cambios. El arreglo está ordenado. Se detiene el algoritmo. [cite: 102]\n";
            break; 
        }
    }

    // Análisis Final
    std::cout << "\n=================================================================\n";
    std::cout << "                          ANÁLISIS FINAL\n";
    std::cout << "=================================================================\n";
    std::cout << "Total de Comparaciones: " << totalComparaciones << "\n";
    std::cout << "Total de Intercambios: " << totalIntercambios << "\n";
    
    std::cout << "\nIneficiencia de Bubble Sort con Comparaciones Costosas:\n";
    std::cout << "Bubble Sort se vuelve ineficiente porque en cada comparación (`arr[j].calcularPromedio() > arr[j+1].calcularPromedio()`), debe llamar a una función que requiere **recorrer y sumar** todos los elementos internos de la cola. Si cada cola tiene $K$ elementos, la comparación es $athcal{O}(K)$.\n";
    std::cout << "Como Bubble Sort tiene una complejidad $athcal{O}(N^2)$ en el peor caso, la complejidad total se convierte en $athcal{O}(N^2 dot K)$, donde:\n";
    std::cout << "* $N$: Número de colas en el arreglo.\n";
    std::cout << "* $K$: Número promedio de usuarios en cada cola.\n";
    std::cout << "Si $K$ es grande, el factor $mathcal{O}(N^2)$ se amplifica enormemente, haciendo el algoritmo muy lento.\n";
}
