/*UNIDAD DE LAS FUERZAS ARMADAS
GRUPO N°4
    CHICAIZA MICHAEL
    FUENTES JORGE
    JACOME MICAELA
    ROGERON MATEO
PROBLEMA 9
*/

#include <iostream>
#include <string>

using namespace std;

//clase plantilla de Nombre Registro
template <typename T>
class Registro {
private:
    //USO DE ARRAY PARA CONTROLAR LOS ELEMENTOS INGRESADOS... SIN DINAMISMO
    T espacios[15];
    int contador;

public:
    Registro() : contador(0) {}

    //INSERCIÓN DE ELEMENTOS
    void insertar(const T& nuevo) {
        if (contador < 15) {
            espacios[contador++] = nuevo;
            cout << "Elemento correctamente agregado" << endl;
        } else {
            cout << "Lo sentimos. El registro se encuentra lleno" << endl;
        }
    }

    void mostrarTodos() const {
        //mensaje por si el array está vacío
        if (contador == 0) {
            cout << "Sin elementos que mostrar" << endl;
        } else {
            cout << "Elementos registrados:\n";
            for (int i = 0; i < contador; i++) {
                cout << "- " << espacios[i] << endl;
            }
        }
    }

    bool buscar(const T& valor) const {
        for (int i = 0; i < contador; i++) {
            if (espacios[i] == valor) {
                cout << "Elemento encontrado: " << espacios[i] << endl;
                return true;
            }
        }
        cout << "Elemento no encontrado o no listado" << endl;
        return false;
    }
};

//Clase Alumnos
class Alumnos {
private:
    string nombre;
    int edad;

public:
    Alumnos(string n = "", int p = 0) : nombre(n), edad(p) {}

    bool operator==(const Alumnos& otro) const {
        return nombre == otro.nombre && edad == otro.edad;
    }

    friend ostream& operator<<(ostream& os, const Alumnos& a) {
        os << "Alumno: " << a.nombre << " | Edad: " << a.edad;
        return os;
    }
};

//Clase Libro
class Libro {
private:
    string nombreLibro;
    string autor;
    int numeroSerie;

public:
    Libro(string t = "", string a = "", int d = 0)
        : nombreLibro(t), autor(a), numeroSerie(d) {}

    bool operator==(const Libro& otro) const {
        return nombreLibro == otro.nombreLibro &&
               autor == otro.autor &&
               numeroSerie == otro.numeroSerie;
    }

    friend ostream& operator<<(ostream& os, const Libro& l) {
        os << "Libro: " << l.nombreLibro
           << " | Autor: " << l.autor
           << " | Serie: " << l.numeroSerie;
        return os;
    }
};

int main() {
    int opciones, opcion1;

    Registro<int> registrarEnteros;
    Registro<Alumnos> registroAlumnos;
    Registro<Libro> registroLibros;

    do {
        cout << "\n---- MENÚ REGISTRO GENÉRICO ----\n";
        cout << "1. Registrar elemento\n";
        cout << "2. Mostrar todos\n";
        cout << "3. Buscar elemento\n";
        cout << "0. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> opciones;
        cout << endl;

        switch (opciones) {
        case 1:
            cout << "¿Qué tipo deseas registrar?\n";
            cout << "1. Entero\n2. Alumno\n3. Libro\n";
            cin >> opcion1;

            switch (opcion1) {
            case 1: {
                int valor;
                cout << "Ingrese el número: ";
                cin >> valor;
                registrarEnteros.insertar(valor);
                break;
            }
            case 2: {
                string nombre;
                int edad;
                cout << "Nombre del alumno: ";
                cin >> nombre;
                cout << "Edad: ";
                cin >> edad;
                registroAlumnos.insertar(Alumnos(nombre, edad));
                break;
            }
            case 3: {
                string titulo, autor;
                int serie;
                cout << "Título del libro: ";
                cin >> titulo;
                cout << "Autor: ";
                cin >> autor;
                cout << "Número de serie: ";
                cin >> serie;
                registroLibros.insertar(Libro(titulo, autor, serie));
                break;
            }
            default:
                cout << "Opción inválida..." << endl;
            }
            break;

        case 2:
            cout << "¿Qué tipo deseas mostrar?\n";
            cout << "1. Enteros\n2. Alumnos\n3. Libros\n";
            cin >> opcion1;

            switch (opcion1) {
            case 1:
                registrarEnteros.mostrarTodos();
                break;
            case 2:
                registroAlumnos.mostrarTodos();
                break;
            case 3:
                registroLibros.mostrarTodos();
                break;
            default:
                cout << "Opción inválida..." << endl;
            }
            break;

        case 3:
            cout << "¿Qué tipo deseas buscar?\n";
            cout << "1. Entero\n2. Alumno\n3. Libro\n";
            cin >> opcion1;

            switch (opcion1) {
            case 1: {
                int valor;
                cout << "Ingrese el número a buscar: ";
                cin >> valor;
                registrarEnteros.buscar(valor);
                break;
            }
            case 2: {
                string nombre;
                int edad;
                cout << "Nombre del alumno: ";
                cin >> nombre;
                cout << "Edad: ";
                cin >> edad;
                registroAlumnos.buscar(Alumnos(nombre, edad));
                break;
            }
            case 3: {
                string titulo, autor;
                int serie;
                cout << "Título del libro: ";
                cin >> titulo;
                cout << "Autor: ";
                cin >> autor;
                cout << "Número de serie: ";
                cin >> serie;
                registroLibros.buscar(Libro(titulo, autor, serie));
                break;
            }
            default:
                cout << "Opción inválida..." << endl;
            }
            break;

        case 0:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida..." << endl;
        }

    } while (opciones != 0);

    return 0;
}
