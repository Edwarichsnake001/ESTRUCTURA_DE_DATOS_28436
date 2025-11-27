#pragma once

#include "Lista.h"
#include <iostream>
#include <ostream>
#include <string>


using namespace std;

class Libros
{
private:
    string titulo;
    string autor;
    string codigo;
    bool disponible;
    int cantidad;

public:
    Libros(string tit, string aut, string cod, bool disp, int cant)
        : titulo(tit), autor(aut), codigo(cod), disponible(disp), cantidad(cant) {}

    string getTitulo() const;

    string getAutor() const;

    string getCodigo() const;

    int getCantidad() const;

    bool operator==(const Libros &otro) const;

    void setDisponible(bool estado);

    bool disponibilidad() const;

    bool coincideTitulo(const std::string &t) const;
    bool coincideAutor(const std::string &a) const;

    friend std::ostream &operator<<(std::ostream &os, const Libros &libro);

    bool operator<(const Libros &otro) const;
    bool operator>(const Libros &otro) const;
};
