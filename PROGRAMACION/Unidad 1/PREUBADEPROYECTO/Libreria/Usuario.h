#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class Rol
{
    Usuario,
    Admin
};

class Usuario
{
private:
    string nombre;
    string cedula;
    string id;
    string contrasena;
    Rol rol;

public:
    Usuario(string nom, string ced, string i, string cont, Rol r) : nombre(nom), cedula(ced), id(i), contrasena(cont), rol(r) {}

    Rol getRol() const
    {
        return rol;
    }

    string getNombre() const { return nombre; }
    string getCedula() const { return cedula; }
    string getId() const { return id; }
    string getContrasena() const { return contrasena; }

    bool esAdministrador() const
    {
        return rol == Rol::Admin;
    }
};
