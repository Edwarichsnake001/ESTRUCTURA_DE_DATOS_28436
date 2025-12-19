#pragma once

#include <iostream>
#include <string>

struct Curso {
    int id;
    std::string nombre;

    bool operator<(const Curso& other) const {
        return id < other.id;
    }
    
    bool operator>(const Curso& other) const {
        return id > other.id;
    }

    void print() const {
        std::cout << "[ID: " << id << ", Nombre: " << nombre << "]";
    }
};
