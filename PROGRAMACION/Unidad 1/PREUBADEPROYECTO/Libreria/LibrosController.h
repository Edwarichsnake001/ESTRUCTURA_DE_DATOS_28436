    #ifndef LIBROS_H
    #define LIBROS_H

    #include "Lista.h"
    #include "Libros.h"

    #include <string>

// Declaraciones de funciones
void insertarLibro(Lista<Libros>& lista, const Libros& libro);
bool eliminarLibro(Lista<Libros>& lista, const std::string& codigo);
void mostrarPorAutor(const Lista<Libros>& lista, const std::string& autor);
void mostrarPorCantidad(const Lista<Libros>& lista);
void mostrarLibros(const Lista<Libros> &lista);
void mostrarLibrosDisponibles(const Lista<Libros> &lista);
bool buscarPorTitulo(const Lista<Libros> &lista, const std::string &titulo);
int contarPrestados(const Lista<Libros> &lista);

#endif // LIBROS_H
