#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Cancion {
    string album;
    string nombre;
    string artista;

    void imprimir() const {
        cout << "|" << setw(8) << left << album
             << "|" << setw(20) << left << nombre
             << "|" << setw(10) << right << artista
             << "|\n";
    }
};

struct NodoAVL {
    Cancion cancion;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
};

int altura(NodoAVL* n) {
    return n ? n->altura : 0;
}

int balance(NodoAVL* n) {
    return n ? altura(n->izq) - altura(n->der) : 0;
}

NodoAVL* rotDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = 1 + max(altura(y->izq), altura(y->der));
    x->altura = 1 + max(altura(x->izq), altura(x->der));

    return x;
}

NodoAVL* rotIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = 1 + max(altura(x->izq), altura(x->der));
    y->altura = 1 + max(altura(y->izq), altura(y->der));

    return y;
}

NodoAVL* insertarAVL(NodoAVL* nodo, Cancion c) {
    if (!nodo)
        return new NodoAVL{c, nullptr, nullptr, 1};

    if (c.nombre < nodo->cancion.nombre)
        nodo->izq = insertarAVL(nodo->izq, c);
    else if (c.nombre > nodo->cancion.nombre)
        nodo->der = insertarAVL(nodo->der, c);
    else
        return nodo;

    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
    int bal = balance(nodo);

    if (bal > 1 && c.nombre < nodo->izq->cancion.nombre)
        return rotDerecha(nodo);
    if (bal < -1 && c.nombre > nodo->der->cancion.nombre)
        return rotIzquierda(nodo);
    if (bal > 1 && c.nombre > nodo->izq->cancion.nombre) {
        nodo->izq = rotIzquierda(nodo->izq);
        return rotDerecha(nodo);
    }
    if (bal < -1 && c.nombre < nodo->der->cancion.nombre) {
        nodo->der = rotDerecha(nodo->der);
        return rotIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* buscarExacto(NodoAVL* nodo, const string& nombre) {
    if (!nodo) return nullptr;

    if (nombre == nodo->cancion.nombre)
        return nodo;

    if (nombre < nodo->cancion.nombre)
        return buscarExacto(nodo->izq, nombre);
    else
        return buscarExacto(nodo->der, nombre);
}

string toLower(const string& s) {
    string r = s;
    transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

void buscarSimilaresAVL(NodoAVL* nodo, const string& clave, vector<Cancion>& res) {
    if (!nodo) return;

    buscarSimilaresAVL(nodo->izq, clave, res);

    string low1 = toLower(nodo->cancion.nombre);
    string low2 = toLower(clave);
    if (low1.find(low2) != string::npos)
        res.push_back(nodo->cancion);

    buscarSimilaresAVL(nodo->der, clave, res);
}

void mostrarAVL(NodoAVL* nodo) {
    if (!nodo) return;
    mostrarAVL(nodo->izq);
    nodo->cancion.imprimir();
    mostrarAVL(nodo->der);
}

void menu(NodoAVL* raiz) {
    int opcion;
    cout<<"===== CANCIONERO (AVL) ====="<<endl;
    cout<<"1. Lista de canciones"<<endl;
    cout<<"2. Buscar por nombre"<<endl;
    cout<<"3. Salir"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    cin.ignore();

    if (opcion == 1) {
        cout << "+--------+--------------------+----------+\n";
        cout << "| Album  | Nombre             | Artista  |\n";
        cout << "+--------+--------------------+----------+\n";
        mostrarAVL(raiz);
        cout << "+--------+--------------------+----------+\n";
        menu(raiz);
    }
    else if (opcion == 2) {
        string nombre;
        cout << "Nombre de la cancion a buscar: ";
        getline(cin, nombre);

        NodoAVL* encontrado = buscarExacto(raiz, nombre);

        if (encontrado) {
            cout << "\nCANCION ENCONTRADA:\n";
            cout << "+--------+--------------------+----------+\n";
            encontrado->cancion.imprimir();
            cout << "+--------+--------------------+----------+\n";
        } else {
            cout << "\nNo se encontro. Buscando similares...\n";
            vector<Cancion> similares;
            buscarSimilaresAVL(raiz, nombre, similares);

            if (similares.empty()) {
                cout << "No hay canciones similares.\n";
            } else {
                cout << "+--------+--------------------+----------+\n";
                for (auto& c : similares) c.imprimir();
                cout << "+--------+--------------------+----------+\n";
            }
        }

        menu(raiz);
    }
}

int main() {
    vector<Cancion> inventario = {
        {"Thriller", "Billie Jean", "Michael Jackson"},
        {"Imagine", "Imagine", "John Lennon"},
        {"Hotel California", "Hotel California", "Eagles"},
        {"Zep", "Stairway to Heaven", "Led Zeppelin"},
        {"Opera", "Bohemian Rhapsody", "Queen"},
        {"Nevermind", "Smells Like Teen Spirit", "Nirvana"},
        {"Help!", "Yesterday", "Beatles"},
        {"GNR", "Sweet Child O' Mine", "Guns N' Roses"},
        {"DarkSide", "Money", "Pink Floyd"},
        {"Rumours", "Go Your Own Way", "Fleetwood Mac"}
    };

    NodoAVL* raiz = nullptr;

    for (auto& c : inventario)
        raiz = insertarAVL(raiz, c);

    menu(raiz);
    return 0;
}
