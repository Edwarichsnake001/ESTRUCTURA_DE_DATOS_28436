#include <iostream>
#include <string>
#include <locale.h>
#include <limits>

using namespace std;

struct NodoSimple
{
    int dato;
    NodoSimple *siguiente;
};

struct NodoDoble
{
    int dato;
    NodoDoble *anterior;
    NodoDoble *siguiente;
};

struct NodoCircular
{
    int dato;
    NodoCircular *siguiente;
};

struct NodoCircularDoble
{
    int dato;
    NodoCircularDoble *siguiente;
    NodoCircularDoble *anterior;
};

// Funciones lista simplemente enlazada

void insertarListaSimple(NodoSimple *&cabeza, int valor)
{
    NodoSimple *nuevo = new NodoSimple();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void mostrarListaSimple(NodoSimple *cabeza)
{
    cout << "\n LISTA SIMPLE - ENLAZADA: ";
    NodoSimple *actual = cabeza;
    while (actual != NULL)
    {
        cout << actual->dato << " —> " << flush;
        actual = actual->siguiente;
    };

    cout << "NULL\n";
}

// Funcion lista doblemente enlazada

void insertarDoble(NodoDoble *&cabeza, int valor)
{
    NodoDoble *nuevo = new NodoDoble();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    nuevo->anterior = NULL;

    if (cabeza != NULL)
    {
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

void mostrarDoble(NodoDoble *cabeza)
{
    cout << "\n LISTA DOBLE - ENLAZADA HACIA ADELANTE:";
    NodoDoble *actual = cabeza;
    NodoDoble *ultimo = NULL;
    while (actual != NULL)
    {
        cout << actual->dato << " <—> ";
        actual = actual->siguiente;
    }
    cout << "NULL\n";
    cout << "Lista doblemente enlazada hacia atras: ";
    while (ultimo != NULL)
    {
        cout << ultimo->dato << " <—> ";
        ultimo = ultimo->anterior;
    }
    cout << "NULL\n";
}

void insertarCircular(NodoCircular *&cabeza, int valor)
{
    NodoCircular *nuevo = new NodoCircular();
    nuevo->dato = valor;
    if (cabeza == NULL)
    {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
    }
    else
    {
        NodoCircular *actual = cabeza;
        while (actual->siguiente != cabeza)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->siguiente = cabeza;
    }
}

void mostrarCircular(NodoCircular *cabeza)
{
    if (cabeza == NULL)
    {
        cout << "\n LISTA CIRCULAR SIMPLE - ENLAZADA: VACÍO";
        return;
    }

    cout << "\n LISTA CIRCULAR SIMPLE: ";
    NodoCircular *actual = cabeza;
    do
    {
        cout << actual->dato << " —> " << flush;
        actual = actual->siguiente;
    } while (actual != cabeza);

    cout << "Vueleve al inicio \n";
}

void insertarCircularDoble(NodoCircularDoble *&cabeza, int valor)
{
    NodoCircularDoble *nuevo = new NodoCircularDoble();
    nuevo->dato = valor;
    if (cabeza == NULL)
    {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cabeza;
    }
    else
    {
        NodoCircularDoble *ultimo = cabeza->anterior;
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }
}

void mostrarCircularDoble(NodoCircularDoble *cabeza)
{
    if (cabeza == NULL)
    {
        cout << "\n VACÍO";
        return;
    }

    cout << "LISTA CIRCULAR DOBLE - ENLAZADA HACIA ADELANTE: ";
    NodoCircularDoble *actual = cabeza;
    do
    {
        cout << actual->dato << " —> " << flush;
        actual = actual->siguiente;
    } while (actual != cabeza);
    cout << "Retorna al inicio \n";

    cout << "\n LISTA CIRCULAR DOBLE ENLAZADA HACIA ATRÁS: ";
    NodoCircularDoble *ultimo = cabeza->anterior;
    actual = ultimo;

    do
    {
        cout << actual->dato << "<—>" << flush;
        actual = actual->anterior;

    } while (actual != cabeza->anterior);
    cout << "Retorna al final \n";
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    NodoSimple *listaSimple = NULL;
    NodoDoble *listaDoble = NULL;
    NodoCircular *listaCircular = NULL;
    NodoCircularDoble *listaCircularDoble = NULL;
    typedef int Numero;
    Numero opcionesM, opcionesL, num;

    do
    {
        cout << "====MENU LISTA===\n";
        cout << "1. Lista Simple\n";
        cout << "2. Lista Doble\n";
        cout << "3. Lista Circular\n";
        cout << "4. Lista Circular Doble\n";
        cout << "0. Salir...\n";

        cout << "Ingrese la opción: ";
        cin >> opcionesM;

        switch (opcionesM)
        {
        case 1:
            cout << "====MENU===\n";
            cout << "1. Insertar\n";
            cout << "2. Mostrar\n";
            cout << "0. Salir...\n";

            cin >> opcionesL;

            switch (opcionesL)
            {
            case 1:
                cout << "Ingresa un número: ";
                cin >> num;
                insertarListaSimple(listaSimple, num);

                break;
            case 2:
                mostrarListaSimple(listaSimple);
                break;

            case 0:
            default:
                cout << "Opcion no válida. Intente de nuevo \n";
                break;
            }
            break;
        case 2:
            cout << "====MENU===\n";
            cout << "1. Insertar\n";
            cout << "2. Mostrar\n";
            cout << "0. Salir...\n";

            cin >> opcionesL;

            switch (opcionesL)
            {
            case 1:
                cout << "Ingresa un número: ";
                cin >> num;
                insertarDoble(listaDoble, num);
                break;
            case 2:
                mostrarDoble(listaDoble);
                break;
            case 0:
                break;
            default:
                cout << "Opcion no válida. Intente de nuevo \n";
                break;
            }
            break;
        case 3:
            cout << "====MENU===\n";
            cout << "1. Insertar\n";
            cout << "2. Mostrar\n";
            cout << "0. Salir...\n";

            cin >> opcionesL;

            switch (opcionesL)
            {
            case 1:
                cout << "Ingresa un número: ";
                cin >> num;
                insertarCircular(listaCircular, num);
                break;
            case 2:
                mostrarCircular(listaCircular);
                break;
            case 0:
                break;
            default:
                cout << "Opcion no válida. Intente de nuevo \n";
                break;
            }
            break;
        case 4:
            cout << "====MENU===\n";
            cout << "1. Insertar\n";
            cout << "2. Mostrar\n";
            cout << "0. Salir...\n";

            cin >> opcionesL;

            switch (opcionesL)
            {
            case 1:
                cout << "Ingresa un número: ";
                cin >> num;
                insertarCircularDoble(listaCircularDoble, num);
                break;
            case 2:
                mostrarCircularDoble(listaCircularDoble);
                break;
            case 0:
                break;
            default:
                cout << "Opcion no válida. Intente de nuevo \n";
                break;
            }

            break;

        default:
            cout << "Opcion no válida. Intente de nuevo \n";
            break;
        }

    } while (opcionesM != 0);
}

// si yo tengo claro los conceptos de lista simple y doble enlazada estamos bien;