/*UNIDAD DE LAS FUERZAS ARMADAS
GRUPO N�4
    CHICAIZA MICHAEL
    FUENTES JORGE
    JACOME MICAELA
    ROGERON MATEO
PROBLEMA 10 - TDA + PLANTILLAS
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Coleccion
{
private:
    T elementos[10];
    int cantidad;

public:
    Coleccion() : cantidad(0) {}

    void insertar(const T &obj)
    {
        if (cantidad < 10)
        {
            elementos[cantidad++] = obj;
            cout << "Elemento agregado correctamente.\n";
        }
        else
        {
            cout << "Error: colecci�n llena.\n";
        }
    }

    // Lista todos los elementos
    void listar() const
    {
        if (cantidad == 0)
        {
            cout << "No hay elementos registrados.\n";
            return;
        }
        for (int i = 0; i < cantidad; ++i)
        {
            cout << elementos[i] << endl;
        }
    }

    // Elimina un elemento
    void eliminar(const T &obj)
    {
        for (int i = 0; i < cantidad; ++i)
        {
            if (elementos[i] == obj)
            {
                for (int j = i; j < cantidad - 1; ++j)
                {
                    elementos[j] = elementos[j + 1];
                }
                cantidad--;
                cout << "Elemento eliminado.\n";
                return;
            }
        }
        cout << "Elemento no encontrado.\n";
    }

    // Actualiza un elemento
    void actualizar(const T &viejo, const T &nuevo)
    {
        for (int i = 0; i < cantidad; ++i)
        {
            if (elementos[i] == viejo)
            {
                elementos[i] = nuevo;
                cout << "Elemento actualizado.\n";
                return;
            }
        }
        cout << "No se encontr� el elemento a actualizar.\n";
    }
};

class Alumno
{
private:
    string nombre;
    int id;
    float promedio;

public:
    Alumno(string n = "", int i = 0, float p = 0.0f)
        : nombre(n), id(i), promedio(p) {}

    void crear(string n, int i, float p)
    {
        nombre = n;
        id = i;
        promedio = p;
    }

    void mostrar() const
    {
        cout << "Alumno: " << nombre << " | ID: " << id << " | Promedio: " << promedio << endl;
    }

    void actualizar(float nuevoPromedio)
    {
        promedio = nuevoPromedio;
    }

    bool operator==(const Alumno &otro) const
    {
        return id == otro.id;
    }

    friend ostream &operator<<(ostream &os, const Alumno &a)
    {
        os << "Alumno: " << a.nombre << " | ID: " << a.id << " | Promedio: " << a.promedio;
        return os;
    }
};

class Profesor
{
private:
    string nombre;
    string materia;

public:
    Profesor(string n = "", string m = "") : nombre(n), materia(m) {}

    void crear(string n, string m)
    {
        nombre = n;
        materia = m;
    }

    void mostrar() const
    {
        cout << "Profesor: " << nombre << " | Materia: " << materia << endl;
    }

    void actualizar(string nuevaMateria)
    {
        materia = nuevaMateria;
    }

    bool operator==(const Profesor &otro) const
    {
        return nombre == otro.nombre && materia == otro.materia;
    }

    friend ostream &operator<<(ostream &os, const Profesor &p)
    {
        os << "Profesor: " << p.nombre << " | Materia: " << p.materia;
        return os;
    }
};

class Curso
{
private:
    string nombre;
    int codigo;

public:
    Curso(string n = "", int c = 0) : nombre(n), codigo(c) {}

    void crear(string n, int c)
    {
        nombre = n;
        codigo = c;
    }

    void mostrar() const
    {
        cout << "Curso: " << nombre << " | C�digo: " << codigo << endl;
    }

    void actualizar(string nuevoNombre)
    {
        nombre = nuevoNombre;
    }

    bool operator==(const Curso &otro) const
    {
        return codigo == otro.codigo;
    }

    friend ostream &operator<<(ostream &os, const Curso &c)
    {
        os << "Curso: " << c.nombre << " | C�digo: " << c.codigo;
        return os;
    }
};

int main()
{
    Coleccion<Alumno> alumnos;
    Coleccion<Profesor> profesores;
    Coleccion<Curso> cursos;
    int opcion;

    do
    {
        cout << "\n----SISTEMA ACADEMICO----\n";
        cout << "1. Registrar Alumno\n";
        cout << "2. Registrar Profesor\n";
        cout << "3. Registrar Curso\n";
        cout << "4. Listar Registros\n";
        cout << "5. Eliminar Elemento\n";
        cout << "6. Actualizar Elemento\n";
        cout << "0. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string nombre;
            int id;
            float prom;
            cout << "Nombre del alumno: ";
            cin >> nombre;
            cout << "ID: ";
            cin >> id;
            cout << "Promedio: ";
            cin >> prom;
            alumnos.insertar(Alumno(nombre, id, prom));
            break;
        }
        case 2:
        {
            string nombre, materia;
            cout << "Nombre del profesor: ";
            cin >> nombre;
            cout << "Materia: ";
            cin >> materia;
            profesores.insertar(Profesor(nombre, materia));
            break;
        }
        case 3:
        {
            string nombre;
            int codigo;
            cout << "Nombre del curso: ";
            cin >> nombre;
            cout << "C�digo: ";
            cin >> codigo;
            cursos.insertar(Curso(nombre, codigo));
            break;
        }
        case 4:
        {
            int sub;
            cout << "\nListar (1=Alumnos, 2=Profesores, 3=Cursos): ";
            cin >> sub;

            switch (sub)
            {
            case 1:
                alumnos.listar();
                break;
            case 2:
                profesores.listar();
                break;
            case 3:
                cursos.listar();
                break;
            default:
                cout << "Opci�n inv�lida.\n";
                break;
            }
            break;
        }
        case 5:
        {
            int sub;
            cout << "\nEliminar de (1=Alumnos, 2=Profesores, 3=Cursos): ";
            cin >> sub;

            switch (sub)
            {
            case 1:
            {
                int id;
                cout << "Ingrese ID: ";
                cin >> id;
                alumnos.eliminar(Alumno("", id, 0));
                break;
            }
            case 2:
            {
                string nombre, materia;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Materia: ";
                cin >> materia;
                profesores.eliminar(Profesor(nombre, materia));
                break;
            }
            case 3:
            {
                int codigo;
                cout << "C�digo: ";
                cin >> codigo;
                cursos.eliminar(Curso("", codigo));
                break;
            }
            default:
                cout << "Opci�n inv�lida.\n";
                break;
            }
            break;
        }
        case 6:
        {
            int sub;
            cout << "\nActualizar (1=Alumno, 2=Profesor, 3=Curso): ";
            cin >> sub;

            switch (sub)
            {
            case 1:
            {
                int id;
                float nuevoProm;
                cout << "Ingrese ID del alumno: ";
                cin >> id;
                cout << "Nuevo promedio: ";
                cin >> nuevoProm;
                alumnos.actualizar(Alumno("", id, 0), Alumno("", id, nuevoProm));
                break;
            }
            case 2:
            {
                string nombre, nuevaMateria;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Nueva materia: ";
                cin >> nuevaMateria;
                profesores.actualizar(Profesor(nombre, ""), Profesor(nombre, nuevaMateria));
                break;
            }
            case 3:
            {
                int codigo;
                string nuevoNombre;
                cout << "C�digo del curso: ";
                cin >> codigo;
                cout << "Nuevo nombre: ";
                cin >> nuevoNombre;
                cursos.actualizar(Curso("", codigo), Curso(nuevoNombre, codigo));
                break;
            }
            default:
                cout << "Opci�n inv�lida.\n";
                break;
            }
            break;
        }
        case 0:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opci�n inv�lida.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
