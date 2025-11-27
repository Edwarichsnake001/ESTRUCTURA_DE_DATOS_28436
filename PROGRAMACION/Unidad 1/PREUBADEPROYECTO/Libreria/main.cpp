#include "LibrosController.h"
#include "UsuarioController.h"
#include "Libros.h"
#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

void mostrarMenuAdmin() {
    cout << "\n===== MENÚ ADMINISTRADOR =====\n";
    cout << "1. Insertar libro\n";
    cout << "2. Eliminar libro\n";
    cout << "3. Mostrar todos los libros\n";
    cout << "4. Mostrar libros por cantidad\n";
    cout << "5. Mostrar libros por autor\n";
    cout << "6. Contar libros prestados\n";
    cout << "0. Salir\n";
    cout << "==============================\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuUsuario() {
    cout << "\n===== MENÚ USUARIO =====\n";
    cout << "1. Mostrar libros disponibles\n";
    cout << "2. Buscar libro por título\n";
    cout << "3. Mostrar libros por autor\n";
    cout << "4. Contar libros prestados\n";
    cout << "5. Mostrar todos los libros\n";
    cout << "0. Salir\n";
    cout << "=========================\n";
    cout << "Seleccione una opción: ";
}

void ejecutarMenuAdmin(Lista<Libros>& lista) {
    int opcion;
    do {
        mostrarMenuAdmin();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string titulo, autor, codigo;
                bool disponible;
                int cantidad;

                cout << "Título: ";
                getline(cin, titulo);
                cout << "Autor: ";
                getline(cin, autor);
                cout << "Código: ";
                getline(cin, codigo);
                cout << "¿Disponible? (1 = sí, 0 = no): ";
                cin >> disponible;
                cout << "Cantidad: ";
                cin >> cantidad;
                cin.ignore();

                insertarLibro(lista, Libros(titulo, autor, codigo, disponible, cantidad));
                break;
            }
            case 2: {
                string codigo;
                cout << "Código del libro a eliminar: ";
                getline(cin, codigo);
                eliminarLibro(lista, codigo);
                break;
            }
            case 3:
                mostrarLibros(lista);
                break;
            case 4:
                mostrarPorCantidad(lista);
                break;
            case 5: {
                string autor;
                cout << "Autor a mostrar: ";
                getline(cin, autor);
                mostrarPorAutor(lista, autor);
                break;
            }
            case 6:
                cout << "Cantidad de libros prestados: " << contarPrestados(lista) << "\n";
                break;
            case 0:
                cout << "Saliendo del menú administrador...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void ejecutarMenuUsuario(Lista<Libros>& lista) {
    int opcion;
    do {
        mostrarMenuUsuario();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                mostrarLibrosDisponibles(lista);
                break;
            case 2: {
                string titulo;
                cout << "Título a buscar: ";
                getline(cin, titulo);
                cout << (buscarPorTitulo(lista, titulo) ? "Encontrado\n" : "No encontrado\n");
                break;
            }
            case 3: {
                string autor;
                cout << "Autor a mostrar: ";
                getline(cin, autor);
                mostrarPorAutor(lista, autor);
                break;
            }
            case 4:
                cout << "Cantidad de libros prestados: " << contarPrestados(lista) << "\n";
                break;
            case 5:
                mostrarLibros(lista);
                break;
            case 0:
                cout << "Saliendo del menú usuario...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    Lista<Libros> lista;
    UsuariosControlador usuariosControlador;

    // Libros de prueba
    insertarLibro(lista, Libros("1984", "George Orwell", "L001", true, 5));
    insertarLibro(lista, Libros("Cien años de soledad", "Gabriel García Márquez", "L002", false, 3));
    insertarLibro(lista, Libros("El Principito", "Antoine de Saint-Exupéry", "L003", true, 7));
    insertarLibro(lista, Libros("Ficciones", "Jorge Luis Borges", "L004", false, 2));

    // Login
    string id, contrasena;
    cout << "=== LOGIN ===\n";
    cout << "ID: ";
    getline(cin, id);
    cout << "Contraseña: ";
    getline(cin, contrasena);

    Usuario* usuarioActual = usuariosControlador.login(id, contrasena);

    if (!usuarioActual) {
        cout << "Credenciales inválidas.\n";
        return 1;
    }

    cout << "Bienvenido, " << usuarioActual->getNombre() << "\n";

    if (usuarioActual->esAdministrador()) {
        ejecutarMenuAdmin(lista);
    } else {
        ejecutarMenuUsuario(lista);
    }

    return 0;
}
