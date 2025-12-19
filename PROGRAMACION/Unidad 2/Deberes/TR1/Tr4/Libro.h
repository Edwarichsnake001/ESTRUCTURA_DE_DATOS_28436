#pragma once

#include <iostream>
#include <string>
#include <iomanip>

struct Libro {
    std::string titulo;
    std::string autor;
    int anio;
    std::string ISBN;

    void print() const {
        std::cout << "[Autor: " << std::setw(15) << std::left << autor 
                  << "| Año: " << std::setw(4) << anio 
                  << "| Título: " << std::setw(25) << std::left << titulo << "]";
    }
};

struct Nodo {
    Libro data;
    Nodo* prev;
    Nodo* next;
    
    Nodo(const Libro& l) : data(l), prev(nullptr), next(nullptr) {}
};

int totalComparaciones = 0;
int totalMovimientosPunteros = 0;
int totalNodosIntercambiados = 0;

bool esMenor(const Libro& l1, const Libro& l2) {
    totalComparaciones++;

    if (l1.autor != l2.autor) {
        return l1.autor < l2.autor;
    }

    return l1.anio < l2.anio;
}

class ListaDoble {
private:
    Nodo* head;
    Nodo* tail;

    void swapNodes(Nodo* n1, Nodo* n2) {
        if (n1 == n2) return;

        totalMovimientosPunteros += 8; 
        totalNodosIntercambiados++;

        Nodo* n1_prev = n1->prev;
        Nodo* n1_next = n1->next;
        
        Nodo* n2_prev = n2->prev;
        Nodo* n2_next = n2->next;

        if (n1_next == n2) {
            if (n1_prev) n1_prev->next = n2; else head = n2;
            n2->prev = n1_prev;

            n2->next = n1;
            n1->prev = n2;

            n1->next = n2_next;
            if (n2_next) n2_next->prev = n1; else tail = n1;
        } 
        else {
            if (n1_prev) n1_prev->next = n2; else head = n2;
            if (n1_next) n1_next->prev = n2;

            if (n2_prev) n2_prev->next = n1; else head = n1;
            if (n2_next) n2_next->prev = n1;

            n1->next = n2_next;
            n1->prev = n2_prev;
            n2->next = n1_next;
            n2->prev = n1_prev;
        }

        if (!head) head = n1;
        while (tail && tail->next) tail = tail->next;
        
        std::cout << " \n";
    }

public:
    ListaDoble() : head(nullptr), tail(nullptr) {}
    ~ListaDoble() { }

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

    void selectionSort() {
        if (!head || !head->next) return;

        Nodo* i = head;
        int pass = 1;

        std::cout << "\n==========================================================\n";
        std::cout << "       INICIO DE ORDENAMIENTO (SELECTION SORT DOBLE)       \n";
        std::cout << "==========================================================\n";

        while (i->next != nullptr) {
            Nodo* minNode = i;
            Nodo* j = i->next;

            std::cout << "\n--- Pasada " << pass << " (Buscando el mínimo desde: ";
            i->data.print();
            std::cout << " ) ---\n";
            
            while (j != nullptr) {
                if (esMenor(j->data, minNode->data)) {
                    minNode = j;
                }
                j = j->next;
            }

            if (minNode != i) {
                std::cout << "  -> Mínimo encontrado: ";
                minNode->data.print();
                std::cout << "\n";
                
                swapNodes(i, minNode);

                i = minNode; 
            } else {
                std::cout << "  -> Mínimo es el nodo actual. No hay intercambio.\n";
            }

            i = i->next; 
            pass++;
            
            std::cout << "----------------------------------------------------------\n";
        }
    }

    void showFinalAnalysis() const {
        std::cout << "\n==========================================================\n";
        std::cout << "             ANÁLISIS FINAL DEL ALGORITMO             \n";
        std::cout << "==========================================================\n";
        
        std::cout << "Registro de Operaciones:\n";
        std::cout << std::setw(35) << std::left << "Total de Comparaciones realizadas:" << totalComparaciones << "\n";
        std::cout << std::setw(35) << std::left << "Total de Nodos Intercambiados:" << totalNodosIntercambiados << "\n";
        std::cout << std::setw(35) << std::left << "Total de Movimientos de Punteros:" << totalMovimientosPunteros << "\n";
        
    }
    
    void showResultsTable() const {
        std::cout << "\n--- Tabla de Resultados (Simulada) ---\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
        std::cout << "| Intercambio #         | Comparaciones (Total)| Movimientos Punteros |\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
        std::cout << "| Total                 | " << std::setw(19) << totalComparaciones << " | " << std::setw(20) << totalMovimientosPunteros << " |\n";
        std::cout << "+-----------------------+---------------------+----------------------+\n";
    }
};