#include <iostream>
#include <queue>
using namespace std;

class ArbolBinario {
private:

    struct Nodo {
        int dato;
        Nodo* izq;
        Nodo* der;
        Nodo(int v) : dato(v), izq(nullptr), der(nullptr) {}
    };

    Nodo* raiz;

    // --------- Inserción recursiva ---------
    Nodo* insertarRec(Nodo* nodo, int valor) {
        if (!nodo) return new Nodo(valor);

        if (valor < nodo->dato) nodo->izq = insertarRec(nodo->izq, valor);
        else if (valor > nodo->dato) nodo->der = insertarRec(nodo->der, valor);

        return nodo;
    }

    // --------- Encontrar mínimo ---------
    Nodo* minimo(Nodo* nodo) {
        while (nodo && nodo->izq)
            nodo = nodo->izq;
        return nodo;
    }

    // --------- Eliminación recursiva ---------
    Nodo* eliminarRec(Nodo* nodo, int valor) {
        if (!nodo) return nullptr;

        if (valor < nodo->dato) nodo->izq = eliminarRec(nodo->izq, valor);
        else if (valor > nodo->dato) nodo->der = eliminarRec(nodo->der, valor);
        else {
            // Caso 1: sin hijos
            if (!nodo->izq && !nodo->der) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: un hijo
            if (!nodo->izq || !nodo->der) {
                Nodo* temp = nodo->izq ? nodo->izq : nodo->der;
                delete nodo;
                return temp;
            }
            // Caso 3: dos hijos
            Nodo* suc = minimo(nodo->der);
            nodo->dato = suc->dato;
            nodo->der = eliminarRec(nodo->der, suc->dato);
        }
        return nodo;
    }

    // Recorridos sistemáticos
    void inorden(Nodo* nodo) {
        if (!nodo) return;
        inorden(nodo->izq);
        cout << nodo->dato << " ";
        inorden(nodo->der);
    }

    void preorden(Nodo* nodo) {
        if (!nodo) return;
        cout << nodo->dato << " ";
        preorden(nodo->izq);
        preorden(nodo->der);
    }

    void postorden(Nodo* nodo) {
        if (!nodo) return;
        postorden(nodo->izq);
        postorden(nodo->der);
        cout << nodo->dato << " ";
    }

    // --------- Altura de un nodo ---------
    int altura(Nodo* nodo) {
        if (!nodo) return 0;
        int izq = altura(nodo->izq);
        int der = altura(nodo->der);
        return 1 + max(izq, der);
    }

public:

    ArbolBinario() : raiz(nullptr) {}

    void insertar(int valor) { raiz = insertarRec(raiz, valor); }

    void eliminar(int valor) { raiz = eliminarRec(raiz, valor); }

    // Recorridos
    void mostrarInorden() { 
        cout << "Inorden: "; 
        inorden(raiz); 
        cout << "\n"; 
    }

    void mostrarPreorden() { 
        cout << "Preorden: "; 
        preorden(raiz); 
        cout << "\n"; 
    }

    void mostrarPostorden() { 
        cout << "Postorden: "; 
        postorden(raiz); 
        cout << "\n"; 
    }

    void mostrarNiveles() {
        if (!raiz) return;
        queue<Nodo*> q;
        q.push(raiz);

        cout << "Por niveles: ";
        while (!q.empty()) {
            Nodo* n = q.front(); q.pop();
            cout << n->dato << " ";
            if (n->izq) q.push(n->izq);
            if (n->der) q.push(n->der);
        }
        cout << "\n";
    }

    void obtenerBalance() {
        if (!raiz) {
            cout << "Árbol vacío.\n";
            return;
        }
        int izq = altura(raiz->izq);
        int der = altura(raiz->der);
        cout << "Factor de balance (altura izq - altura der) = " 
             << izq - der << "\n";
    }
};

int main() {

    ArbolBinario arbol;

    // Creación + Inserción
    int datos[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : datos) arbol.insertar(v);

    // Recorridos
    arbol.mostrarInorden();
    arbol.mostrarPreorden();
    arbol.mostrarPostorden();
    arbol.mostrarNiveles();

    // Altura y balance
    arbol.obtenerBalance();

    // Eliminación
    cout << "\nEliminando 20, 30 y 50...\n";
    arbol.eliminar(20);
    arbol.eliminar(30);
    arbol.eliminar(50);

    // Recorridos después de eliminar
    arbol.mostrarInorden();
    arbol.obtenerBalance();

    return 0;
}

