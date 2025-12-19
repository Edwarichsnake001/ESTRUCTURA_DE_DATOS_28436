#pragma once

#include "Curso.h"
#include <iomanip> // Para formato de tabla

// Definición del nodo de la lista
struct Nodo
{
    Curso data;
    Nodo *next;

    // Constructor
    Nodo(const Curso &c) : data(c), next(nullptr) {}
};

class ListaSimple
{
private:
    Nodo *head;

    // Variables de análisis
    int totalComparaciones = 0;
    int totalPunterosModificados = 0;

    bool insertarOrdenado(Nodo *&sortedHead, Nodo *key)
    {
        if (!sortedHead || key->data < sortedHead->data)
        {
            key->next = sortedHead;
            sortedHead = key;
            totalPunterosModificados += 2;
            return true;
        }

        Nodo *current = sortedHead;
        Nodo *prev = nullptr;
        int compCount = 0;
        int dispCount = 0;

        while (current != nullptr && current->data < key->data)
        {
            prev = current;
            current = current->next;
            compCount++;
        }
        totalComparaciones += compCount;

        if (prev == nullptr)
        {
            return false;
        }

        key->next = current;
        prev->next = key;
        totalPunterosModificados += 2;

        std::cout << "  -> Inserción en posición: ";
        if (current)
            current->data.print();
        else
            std::cout << "FINAL";
        std::cout << "\n";

        return true;
    }

public:
    ListaSimple() : head(nullptr) {}
    ~ListaSimple()
    {
        // Liberación de memoria (Destructor)
        Nodo *current = head;
        while (current != nullptr)
        {
            Nodo *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void add(int id, const std::string &nombre)
    {
        Curso c = {id, nombre};
        Nodo *newNode = new Nodo(c);
        newNode->next = head;
        head = newNode;
    }

    void print() const
    {
        Nodo *current = head;
        if (!current)
        {
            std::cout << "Lista vacía.\n";
            return;
        }
        while (current != nullptr)
        {
            current->data.print();
            if (current->next)
            {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << " -> NULL\n";
    }

    void insertionSort()
    {
        if (!head || !head->next)
        {
            return;
        }

        Nodo *sorted = nullptr;
        Nodo *current = head;

        std::cout << "\n======================================================\n";
        std::cout << "       INICIO DE ORDENAMIENTO (INSERTION SORT)       \n";
        std::cout << "======================================================\n";

        while (current != nullptr)
        {
            Nodo *key = current;
            current = current->next;
            key->next = nullptr;

            std::cout << "\n--- CLAVE: ";
            key->data.print();
            std::cout << " ---\n";

            int initialPointers = totalPunterosModificados;

            if (insertarOrdenado(sorted, key))
            {
                std::cout << "  -> Nodos desplazados: 1 (el nodo clave)\n";
            }
            else
            {
                std::cout << "  -> Nodos desplazados: 0 (el nodo clave ya estaba en orden)\n";
            }

            head = sorted;

            std::cout << "  -> Comparaciones realizadas en esta pasada: " << (totalComparaciones - initialPointers / 2) << "\n";
            std::cout << "  -> Punteros modificados en esta pasada: " << (totalPunterosModificados - initialPointers) << "\n";

            std::cout << "\nEstado de la Lista: \n";
            print();
            std::cout << "------------------------------------------------------\n";
        }
    }

    void showFinalAnalysis() const
    {
        std::cout << "\n======================================================\n";
        std::cout << "             ANÁLISIS FINAL DEL ALGORITMO             \n";
        std::cout << "======================================================\n";

        std::cout << std::setw(30) << std::left << "Total de Comparaciones:" << totalComparaciones << "\n";
        std::cout << std::setw(30) << std::left << "Total de Punteros Modificados:" << totalPunterosModificados << "\n";
    }
};
