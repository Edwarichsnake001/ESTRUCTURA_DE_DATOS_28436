#include "Libros.h"
#include <iostream>
#include <string>

using namespace std;

string Libros::getTitulo() const
{
    return titulo;
}

string Libros::getAutor() const
{
    return autor;
}

string Libros::getCodigo() const
{
    return codigo;
}

int Libros::getCantidad() const
{
    return cantidad;
}

bool Libros::operator==(const Libros &otro) const
{
   return codigo == otro.codigo;
}

void Libros::setDisponible(bool estado)
{
    disponible = estado;
}

bool Libros::disponibilidad() const
{
    return disponible;
}

bool Libros::coincideTitulo(const std::string &t) const
{
    return titulo == t;
}

bool Libros::coincideAutor(const std::string &a) const
{
    return autor == a;
}

/*Todavía no sé donde puedo implementar estos operadores ni como debería
usarlo dentro del programa como una funcionalidad necesaria
por lo que ahora solo están de """Adorno"""""*/
bool Libros::operator<(const Libros &otro) const
{
    return cantidad < otro.cantidad;
}

bool Libros::operator>(const Libros &otro) const
{
    return cantidad > otro.cantidad;
}

//Este no, este esta bien xd
std::ostream &operator<<(std::ostream &os, const Libros &libro)
{
    os << "Título: " << libro.titulo << endl
       << "Autor: " << libro.autor << endl
       << "Código: " << libro.codigo << endl
       << "Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl
       << "Cantidad: " << libro.cantidad << endl;
    return os;
}
