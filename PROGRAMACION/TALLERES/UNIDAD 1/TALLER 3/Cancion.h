#pragma once
#include <string>
#include <iostream>

class Cancion {
private:
    std::string titulo;
    std::string artista;

public:
    Cancion(); // constructor por defecto
    Cancion(std::string t, std::string a); // constructor con parámetros

    std::string getTitulo() const;
    std::string getArtista() const;
    void setTitulo(std::string t);
    void setArtista(std::string a);

    bool operator==(const Cancion& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Cancion& c);
};
