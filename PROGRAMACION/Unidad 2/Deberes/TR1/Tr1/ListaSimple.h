#pragma once

#include "Curso.h"
#include <iomanip> // Para formato de tabla

// Definición del nodo de la lista
struct Nodo {
    Curso data;
    Nodo* next;
    
    // Constructor
    Nodo(const Curso& c) : data(c), next(nullptr) {}
};

class ListaSimple {
private:
    Nodo* head;

    // Variables de análisis
    int totalComparaciones = 0;
    int totalPunterosModificados = 0;

    // Funcion auxiliar para insertar el nodo 'key' en la sublista ordenada
    // Retorna true si se insertó, false si no hubo movimiento.
    bool insertarOrdenado(Nodo*& sortedHead, Nodo* key) {
        if (!sortedHead || key->data < sortedHead->data) {
            // Caso 1: Insertar al inicio de la sublista ordenada
            key->next = sortedHead;
            sortedHead = key;
            totalPunterosModificados += 2; // key->next y sortedHead
            return true;
        }

        Nodo* current = sortedHead;
        Nodo* prev = nullptr;
        int compCount = 0;
        int dispCount = 0;
        
        // Buscar la posición correcta. Se usa <= para asegurar la estabilidad,
        // aunque Insertion Sort con punteros en una lista es inherentemente estable
        // si se inserta después de elementos iguales. Aquí usamos < o > para el ordenamiento.
        while (current != nullptr && current->data < key->data) {
            prev = current;
            current = current->next;
            compCount++;
        }
        totalComparaciones += compCount;

        if (prev == nullptr) {
            // El elemento ya es el menor de la sublista (no debería llegar aquí por el check inicial)
            return false;
        }

        // Insertar el nodo 'key' entre 'prev' y 'current'
        key->next = current;
        prev->next = key;
        totalPunterosModificados += 2; // key->next y prev->next
        
        std::cout << "  -> Inserción en posición: ";
        if (current) current->data.print();
        else std::cout << "FINAL";
        std::cout << "\n";
        
        return true;
    }

public:
    ListaSimple() : head(nullptr) {}
    ~ListaSimple() {
        // Liberación de memoria (Destructor)
        Nodo* current = head;
        while (current != nullptr) {
            Nodo* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // Agregar un curso al inicio de la lista (para construirla)
    void add(int id, const std::string& nombre) {
        Curso c = {id, nombre};
        Nodo* newNode = new Nodo(c);
        newNode->next = head;
        head = newNode;
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
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << " -> NULL\n";
    }

    // Implementación del Insertion Sort que mueve nodos completos
    void insertionSort() {
        if (!head || !head->next) {
            return; // 0 o 1 nodo, ya está ordenada
        }

        Nodo* sorted = nullptr; // La cabeza de la sublista ordenada
        Nodo* current = head;   // Recorre la lista original

        std::cout << "\n======================================================\n";
        std::cout << "       INICIO DE ORDENAMIENTO (INSERTION SORT)       \n";
        std::cout << "======================================================\n";

        // Iterar sobre cada nodo de la lista original
        while (current != nullptr) {
            Nodo* key = current;
            current = current->next; // Mover el puntero de la lista original antes de romper el enlace
            key->next = nullptr;     // Desconectar el nodo 'clave'

            // --- Trazado de Análisis de la Iteración ---
            std::cout << "\n--- CLAVE: ";
            key->data.print();
            std::cout << " ---\n";
            
            int initialPointers = totalPunterosModificados;

            // Insertar la 'clave' en la sublista ordenada
            if (insertarOrdenado(sorted, key)) {
                std::cout << "  -> Nodos desplazados: 1 (el nodo clave)\n";
            } else {
                 std::cout << "  -> Nodos desplazados: 0 (el nodo clave ya estaba en orden)\n";
            }
            
            // Reconstruir la lista original (head = sorted) para la visualización
            head = sorted; 

            // --- Registro de la Iteración ---
            std::cout << "  -> Comparaciones realizadas en esta pasada: " << (totalComparaciones - initialPointers / 2) << "\n";
            std::cout << "  -> Punteros modificados en esta pasada: " << (totalPunterosModificados - initialPointers) << "\n";
            
            std::cout << "\nEstado de la Lista: \n";
            print();
            std::cout << "------------------------------------------------------\n";
        }
    }

    // Presentar el análisis final
    void showFinalAnalysis() const {
        std::cout << "\n======================================================\n";
        std::cout << "             ANÁLISIS FINAL DEL ALGORITMO             \n";
        std::cout << "======================================================\n";
        
        std::cout << std::setw(30) << std::left << "Total de Comparaciones:" << totalComparaciones << "\n";
        std::cout << std::setw(30) << std::left << "Total de Punteros Modificados:" << totalPunterosModificados << "\n";
        
        std::cout << "\nRazones por las que Insertion Sort es adecuado para Listas Enlazadas:\n";
        std::cout << "* **Bajo Costo de Desplazamiento:** Insertion Sort solo requiere cambiar punteros, lo que es una operación O(1)[cite: 3, 11]. No se necesita mover la estructura de datos completa (como ocurre en arreglos, donde un desplazamiento es O(N)).\n";
        std::cout << "* **No requiere acceso aleatorio (índice):** Los algoritmos que dependen de índices (como Quicksort o Heapsort en arreglos) son lentos en listas enlazadas, ya que acceder a un índice 'i' requiere recorrer la lista O(i). Insertion Sort opera secuencialmente, lo cual es natural para esta estructura.\n";
        std::cout << "* **Eficiente para listas casi ordenadas:** Si la lista ya está casi ordenada, Insertion Sort realiza pocos desplazamientos y comparaciones, lo que lo hace muy rápido en el mejor caso (O(N)).\n";
    }
};
