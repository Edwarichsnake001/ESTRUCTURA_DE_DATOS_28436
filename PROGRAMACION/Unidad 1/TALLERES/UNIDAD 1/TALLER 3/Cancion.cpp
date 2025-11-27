#include "Cancion.h"

Cancion::Cancion() : titulo(""), artista("") {} // Constructor por defecto

Cancion::Cancion(std::string t, std::string a) : titulo(t), artista(a) {}

std::string Cancion::getTitulo() const {
    return titulo;
}

bool Cancion::operator==(const Cancion &other) const
{
    return titulo == other.titulo && artista == other.artista;
}

std::ostream& operator<<(std::ostream& os, const Cancion& c) {
    os << c.titulo << " - " << c.artista;
    return os;
}

std::string Cancion::getArtista() const {
    return artista;
}

void Cancion::setTitulo(std::string t) {
    titulo = t;
}

void Cancion::setArtista(std::string a) {
    artista = a;
}