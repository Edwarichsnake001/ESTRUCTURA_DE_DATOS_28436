#pragma once

#include <iostream>
#include <string>
#include <iomanip>

// Estructura que representa un libro
struct Libro {
    std::string titulo;
    std::string autor; // Criterio 1: Orden alfabético
    int anio;          // Criterio 2: Ascendente
    std::string ISBN;

    // Función para imprimir el registro de manera clara
    void print() const {
        std::cout << "[Autor: " << std::setw(15) << std::left << autor 
                  << "| Año: " << std::setw(4) << anio 
                  << "| Título: " << std::setw(25) << std::left << titulo << "]";
    }
};

// =========================================================================
// NODO DOBLEMENTE ENLAZADO
// =========================================================================
struct Nodo {
    Libro data;
    Nodo* prev; // Puntero al nodo anterior
    Nodo* next; // Puntero al nodo siguiente
    
    // Constructor
    Nodo(const Libro& l) : data(l), prev(nullptr), next(nullptr) {}
};

// Globales para el análisis
int totalComparaciones = 0;
int totalMovimientosPunteros = 0;
int totalNodosIntercambiados = 0;

// =========================================================================
// FUNCIÓN DE COMPARACIÓN COMPUESTA (Prioridad: Autor -> Año)
// =========================================================================
// Retorna true si libro1 es "menor" (o tiene mayor prioridad) que libro2
bool esMenor(const Libro& l1, const Libro& l2) {
    totalComparaciones++; // Sumar la comparación base

    // 1. Autor (orden alfabético)
    if (l1.autor != l2.autor) {
        return l1.autor < l2.autor;
    }

    // 2. Año (ascendente)
    return l1.anio < l2.anio;
}

// =========================================================================
// CLASE LISTA DOBLEMENTE ENLAZADA
// =========================================================================
class ListaDoble {
private:
    Nodo* head;
    Nodo* tail;

    // Funcion auxiliar para intercambiar dos nodos (punteros) en la lista
    void swapNodes(Nodo* n1, Nodo* n2) {
        if (n1 == n2) return;

        // Necesitamos 8 re-conexiones por cada intercambio de nodos
        totalMovimientosPunteros += 8; 
        totalNodosIntercambiados++;

        // Manipular los vecinos de n1
        Nodo* n1_prev = n1->prev;
        Nodo* n1_next = n1->next;
        
        // Manipular los vecinos de n2
        Nodo* n2_prev = n2->prev;
        Nodo* n2_next = n2->next;

        // CASO 1: Nodos son adyacentes (n1 -> n2)
        if (n1_next == n2) {
            // A. n1_prev -> n2
            if (n1_prev) n1_prev->next = n2; else head = n2;
            n2->prev = n1_prev;

            // B. n2 -> n1
            n2->next = n1;
            n1->prev = n2;

            // C. n1 -> n2_next
            n1->next = n2_next;
            if (n2_next) n2_next->prev = n1; else tail = n1;
        } 
        // CASO 2: Nodos NO son adyacentes
        else {
            // A. Vecinos de n1 apuntan a n2
            if (n1_prev) n1_prev->next = n2; else head = n2;
            if (n1_next) n1_next->prev = n2;

            // B. Vecinos de n2 apuntan a n1
            if (n2_prev) n2_prev->next = n1; else head = n1;
            if (n2_next) n2_next->prev = n1;

            // C. Intercambiar los punteros internos de n1 y n2
            n1->next = n2_next;
            n1->prev = n2_prev;
            n2->next = n1_next;
            n2->prev = n1_prev;
        }

        // Asegurar que head y tail sean correctos
        if (!head) head = n1; // Si la lista estaba vacía, el primer nodo es la cabeza
        while (tail && tail->next) tail = tail->next; // Ajustar la cola si es necesario

        std::cout << "     \n";
    }

public:
    ListaDoble() : head(nullptr), tail(nullptr) {}
    ~ListaDoble() { /* Liberación de memoria */ }

    // Agregar un libro al final de la lista (para construirla)
    void add(const Libro& l) {
        Nodo* newNode = new Nodo(l);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print() const {
        Nodo* current = head;
        if (!current) {
            std::cout << "Lista vacía.\n";
            return;
        }
        while (current != nullptr) {
            current->data.print();
            if (current->next) {
                std::cout << " <=> \n";
            }
            current = current->next;
        }
        std::cout << " <=> NULL\n";
    }

    // =========================================================================
    // IMPLEMENTACIÓN SELECTION SORT
    // =========================================================================
    void selectionSort() {
        if (!head || !head->next) return;

        Nodo* i = head;
        int pass = 1;

        std::cout << "\n==========================================================\n";
        std::cout << "      INICIO DE ORDENAMIENTO (SELECTION SORT DOBLE)       \n";
        std::cout << "==========================================================\n";

        while (i->next != nullptr) {
            Nodo* minNode = i;
            Nodo* j = i->next;

            std::cout << "\n--- Pasada " << pass << " (Buscando el mínimo desde: ";
            i->data.print();
            std::cout << " ) ---\n";
            
            // 1. Recorrer la sublista restante [i->next ... tail] para localizar el nodo mínimo
            while (j != nullptr) {
                if (esMenor(j->data, minNode->data)) {
                    minNode = j; // Nuevo nodo mínimo encontrado
                }
                j = j->next;
            }

            // 2. Intercambiar si el nodo mínimo no es el nodo actual (i)
            if (minNode != i) {
                std::cout << "  -> Mínimo encontrado: ";
                minNode->data.print();
                std::cout << "\n";
                
                // Mover los nodos completos (manipular punteros prev y next)
                swapNodes(i, minNode);

                // Como hicimos un swap, el puntero 'i' ahora apunta al nodo que estaba en minNode,
                // y minNode apunta al nodo que estaba en 'i'. Para continuar el ciclo, 
                // debemos avanzar 'i' al siguiente nodo de la lista ordenada.
                i = minNode; 
            } else {
                std::cout << "  -> Mínimo es el nodo actual. No hay intercambio.\n";
            }

            // Avance del puntero de la sublista ordenada
            i = i->next; 
            pass++;
            
            std::cout << "----------------------------------------------------------\n";
        }
    }

    // Presentar el análisis final
    void showFinalAnalysis() const {
        std::cout << "\n==========================================================\n";
        std::cout << "                 ANÁLISIS FINAL DEL ALGORITMO             \n";
        std::cout << "==========================================================\n";
        
        std::cout << "Registro de Operaciones:\n";
        std::cout << std::setw(35) << std::left << "Total de Comparaciones realizadas:" << totalComparaciones << "\n";
        std::cout << std::setw(35) << std::left << "Total de Nodos Intercambiados:" << totalNodosIntercambiados << "\n";
        std::cout << std::setw(35) << std::left << "Total de Movimientos de Punteros:" << totalMovimientosPunteros << "\n";
        
        std::cout << "\nVentajas de la Lista Doblemente Enlazada para Selection Sort:\n";
        std::cout << "1. **Simplificación del Intercambio (Relativa):** Aunque la lógica de intercambio de nodos sigue siendo compleja, la presencia del puntero `prev` facilita re-enlazar los nodos vecinos. En una lista simple, re-enlazar el nodo anterior requeriría recorrer toda la lista desde el inicio para encontrarlo.\n";
        std::cout << "2. **Acceso Bidireccional (Potencial):** Permite recorrer la lista hacia adelante (`next`) para la búsqueda del mínimo y, si fuera necesario para una adaptación del algoritmo, retroceder (`prev`).\n";
        std::cout << "3. **Manipulación de Punteros Fija:** A pesar de la complejidad, el intercambio de dos nodos requiere un número fijo (constante, O(1)) de re-asignaciones de punteros (generalmente 6-8 punteros) independientemente del tamaño de la lista, lo cual es más eficiente que el desplazamiento de registros completos en un arreglo pesado.\n";
    }
    
    // Función para registrar la tabla final (simulación)
    void showResultsTable() const {
        std::cout << "\n--- Tabla de Resultados (Simulada) ---\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
        std::cout << "| Intercambio #         | Comparaciones (Total)| Movimientos Punteros |\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
        // Aquí se registrarían los datos por iteración si el ejercicio lo requiriera,
        // pero se muestra el total al final.
        std::cout << "| Total                 | " << std::setw(19) << totalComparaciones << " | " << std::setw(20) << totalMovimientosPunteros << " |\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
    }
};
