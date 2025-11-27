#include "UsuarioController.h"

UsuariosControlador::UsuariosControlador()
{
    usuarios.push_back(Usuario("Mat", "0102030405", "admin01", "clave123", Rol::Admin));
    usuarios.push_back(Usuario("Ana", "1122334455", "user01", "libros456", Rol::Usuario));
}

Usuario *UsuariosControlador::login(const string id, const string &contrasena)
{
    for (auto &usuario : usuarios)
    {
        if (usuario.getId() == id && usuario.getContrasena() == contrasena)
        {
            return &usuario;
        }
    }
    return nullptr;
}

void UsuariosControlador::agregarUsuario(const Usuario &nuevoUser)
{
    usuarios.push_back(nuevoUser);
}

Usuario *UsuariosControlador::busquedaID(const string &id)
{
    for (auto &usuario : usuarios)
    {
        if (usuario.getId() == id)
        {
            return &usuario;
        }
    }
    return nullptr;
}
