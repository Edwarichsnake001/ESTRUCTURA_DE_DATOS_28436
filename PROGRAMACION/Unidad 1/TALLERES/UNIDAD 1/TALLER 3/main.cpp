#include "ListaCircular.h"
#include "Cancion.h"
#include <iostream>
#include <string>
#include <locale.h>
#include <limits>

using namespace std;

typedef int Numeros;

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    ListaCircularDoble lista;
    Numeros opcion;
    string titulo, artista;

    do
    {
        cout << "=========MENÚ DEL REPRODUCTOR=========\n";
        cout << "1. Agregar canción\n";
        cout << "2. Eliminar canción\n";
        cout << "3. Mostrar lista de canciones\n";
        cout << "4. Reproducir actual\n";
        cout << "5. Siguiente canción\n";
        cout << "6. Canción anterior\n";
        cout << "7. Buscar canción\n"; //solo por cumplimiento de busqueda
        cout << "0. Salir\n";
        cout << "Opción: ";

        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Título: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, titulo);
                cout << "Artista: ";
                getline(cin, artista);
                lista.insertar(Cancion(titulo, artista));
                break;

            case 2:
                cout << "Título de la canción a eliminar: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, titulo);
                cout << "Artista: ";
                getline(cin, artista);
                lista.eliminar(Cancion(titulo, artista));
                break;

            case 3:
                lista.mostrar();
                break;

            case 4:
                lista.reproducirCancionActual();
                break;

            case 5:
                lista.siguienteCancion();
                break;

            case 6:
                lista.anteriorCancion();
                break;

            case 7:
                cout << "Título: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, titulo);
                cout << "Artista: ";
                getline(cin, artista);
                if (lista.buscar(Cancion(titulo, artista)))
                    cout << "Canción encontrada en la lista." << endl;
                else
                    cout << "Canción no encontrada." << endl;
                break;

            case 0:
                cout << "Saliendo del reproductor..." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }



    } while (opcion !=0);






    return 0;
}
