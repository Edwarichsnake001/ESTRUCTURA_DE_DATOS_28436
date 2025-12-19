#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> 

using namespace std;

struct Proceso {
    int pid;
    int tiempo_cpu;
    int prioridad;
    
    void print() const {
        std::cout << "[PID: " << pid << ", Prio: " << prioridad << ", CPU: " << tiempo_cpu << "ms]";
    }
};

struct Nodo {
    Proceso data;
    Nodo* prev;
    Nodo* next;
    
    Nodo(const Proceso& p) : data(p), prev(nullptr), next(nullptr) {}
};

class ListaDobleCircular {
private:
    Nodo* head;
    
    void printRecursive(Nodo* start) const {
        if (!start) {
             std::cout << "Lista vacía.\n";
             return;
        }
        Nodo* current = start;
        do {
            current->data.print();
            if (current->next != start) {
                std::cout << " <=> \n";
            }
            current = current->next;
        } while (current != start);
        std::cout << " <=> (HEAD)\n";
    }

    Nodo* partition(Nodo* low, Nodo* high) {
        if (!low || !high || low == high || low->prev == high) return low; 
        
        int pivot_prioridad = high->data.prioridad;
        
        Nodo* i_before_low = low->prev; 
        Nodo* i = i_before_low;
        Nodo* j = low;
        
        std::cout << "\n  -> Pivote: "; high->data.print(); 
        std::cout << "\n  -> Rango: ["; low->data.print(); std::cout << " ... "; high->data.print(); std::cout << "]\n";
        
        while (j != high) {
            if (j->data.prioridad <= pivot_prioridad) {
                i = (i == i_before_low) ? low : i->next; 
                
                if (i != j) {
                    std::swap(i->data, j->data); 
                    std::cout << "    * Swap de datos: i (P" << i->data.prioridad << ") <-> j (P" << j->data.prioridad << ")\n";
                }
            }
            j = j->next; 
        }
        
        i = (i == i_before_low) ? low : i->next; 
        
        std::swap(i->data, high->data); 
        std::cout << "  -> Pivote final colocado en: "; i->data.print(); std::cout << "\n";
        
        return i;
    }
    
    void quickSortRecursive(Nodo* low, Nodo* high, int level) {
        if (!low || !high || low == high) return;
        if (low->next == high && low->data.prioridad <= high->data.prioridad) return;

        std::cout << "\n--- Llamada Recursiva (Nivel " << level << ") ---\n";
        
        Nodo* pivot = partition(low, high);
        
        if (pivot != low && pivot->prev != low) { 
             quickSortRecursive(low, pivot->prev, level + 1);
        }
        
        if (pivot != high && pivot->next != high) {
            quickSortRecursive(pivot->next, high, level + 1);
        }
        
        std::cout << "\n[Lista tras Nivel " << level << "]: ";
        printRecursive(head);
    }
    
public:
    ListaDobleCircular() : head(nullptr) {}

    void add(const Proceso& p) {
        Nodo* nuevo = new Nodo(p);
        if (!head) {
            head = nuevo;
            head->next = head;
            head->prev = head;
        } else {
            Nodo* last = head->prev;
            nuevo->next = head;
            nuevo->prev = last;
            head->prev = nuevo;
            last->next = nuevo;
        }
    }
    
    void print() const {
        printRecursive(head);
    }

    void sort() {
        if (!head || head->next == head) return;
        
        Nodo* tail = head->prev;
        
        quickSortRecursive(head, tail, 0);
    }
    
    void showAnalysis() const {
        std::cout << "\n========================================================\n";
        std::cout << "             ANÁLISIS DE QUICKSORT EN D-L-C\n";
        std::cout << "========================================================\n";
        
        std::cout << "\nDesafíos de aplicar Quicksort a Estructuras Enlazadas:\n";
        std::cout << "1. Sin Acceso Aleatorio O(N): Quicksort se basa en el acceso por índice O(1) para las particiones. En listas enlazadas, el acceso a un nodo k requiere O(k) pasos (recorrido secuencial).\n";
        std::cout << "2. Complejidad de la Partición: La partición requiere que los elementos menores que el pivote se muevan a la izquierda y los mayores a la derecha. Mover nodos completos en una lista doblemente enlazada circular requiere manipular 4 punteros (`prev` y `next` de los nodos vecinos) por cada nodo movido, haciendo que la partición sea costosa y propensa a errores.\n";
        std::cout << "3. Fusión de Sublistas: Una vez que la recursión devuelve las sublistas ordenadas, es necesario re-conectar (`low->prev` y `high->next`) los límites de las sublistas y ajustar la circularidad, lo cual añade otra capa de dificultad.\n";
        
        std::cout << "\nComparación de Eficiencia con la Versión para Arreglos:\n";
        std::cout << "La eficiencia teórica de Quicksort en listas enlazadas es mucho menor.\n";
        std::cout << "Arreglos: O(N log N) en tiempo promedio (por comparaciones) + costo constante de swaps.\n";
        std::cout << "Listas Enlazadas: La fase de partición (mover elementos menores/mayores) es ineficiente. El costo de recorrer para encontrar límites o elementos es alto. En la práctica, Quicksort en listas doblemente enlazadas suele ser más lento que algoritmos simples como Merge Sort (que es ideal para listas, ya que las divisiones son O(1) o Insertion Sort (para listas pequeñas/casi ordenadas).\n";
    }
};