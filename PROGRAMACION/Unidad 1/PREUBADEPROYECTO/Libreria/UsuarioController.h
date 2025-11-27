#pragma once

#include "Usuario.h"
#include <vector>
#include <string>

using namespace std;

class UsuariosControlador
{
private:
    vector<Usuario> usuarios;

public:
    UsuariosControlador();
    Usuario *login(const string id, const string &contrasena);
    void agregarUsuario(const Usuario &nuevoUser);
    Usuario *busquedaID(const string &id);

};
