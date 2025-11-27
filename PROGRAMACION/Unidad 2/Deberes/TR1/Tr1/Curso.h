#pragma once

#include <iostream>
#include <string>

// Estructura que representa el dato a almacenar en el nodo
struct Curso {
    int id;
    std::string nombre;

    // Sobrecarga del operador < para que el Insertion Sort sepa cómo comparar
    // Ordenaremos por 'id' como criterio principal.
    bool operator<(const Curso& other) const {
        return id < other.id;
    }
    
    // Sobrecarga del operador > para comparación
    bool operator>(const Curso& other) const {
        return id > other.id;
    }
    
    // Función para imprimir el curso de manera clara
    void print() const {
        std::cout << "[ID: " << id << ", Nombre: " << nombre << "]";
    }
};
