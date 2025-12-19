#include <iostream>
#include <string>

using namespace std;

// Nodo con factor de altura para balanceo
struct Nodo {
    int dato;
    Nodo *izq, *der;
    int altura;
    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr), altura(1) {}
};

// Funciones para calcular niveles y balance
int obtenerAltura(Nodo* n) { return n ? n->altura : 0; }
int obtenerBalance(Nodo* n) { return n ? obtenerAltura(n->izq) - obtenerAltura(n->der) : 0; }
int maximo(int a, int b) { return (a > b) ? a : b; }

// Rotaciones 
Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;
    x->der = y;
    y->izq = T2;
    y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    return y;
}

// Insercion con balanceo  
Nodo* insertar(Nodo* nodo, int dato) {
    if (!nodo) return new Nodo(dato);

    if (dato < nodo->dato)
        nodo->izq = insertar(nodo->izq, dato);
    else if (dato > nodo->dato)
        nodo->der = insertar(nodo->der, dato);
    else return nodo;

    nodo->altura = 1 + maximo(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
    int balance = obtenerBalance(nodo);

    // Si se desbalancea rotamos
    if (balance > 1 && dato < nodo->izq->dato) return rotarDerecha(nodo);
    if (balance < -1 && dato > nodo->der->dato) return rotarIzquierda(nodo);
    if (balance > 1 && dato > nodo->izq->dato) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && dato < nodo->der->dato) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

// Imprimir por niveles para verificar el orden
void niveles(Nodo* raiz) {
    if (!raiz) return;
    Nodo* cola[10];
    int nivel[10];
    int ini = 0, fin = 0;
    cola[fin] = raiz; nivel[fin++] = 0;

    int nivAct = 0;
    cout << "Nivel 0: ";
    while(ini < fin){
        Nodo* act = cola[ini];
        int n = nivel[ini++];
        if(n != nivAct) { nivAct = n; cout << "\nNivel " << n << ": "; }
        cout << act->dato << " ";
        if(act->izq) { cola[fin] = act->izq; nivel[fin++] = n+1; }
        if(act->der) { cola[fin] = act->der; nivel[fin++] = n+1; }
    }
}

int main() {
    Nodo* raiz = nullptr;
    // Datos de tu imagen insertados uno a uno
    int datos[] = {9, 5, 10, 1, 7, 6, 8};

    for(int x : datos) raiz = insertar(raiz, x);

    cout << "--- Arbol Balanceado  ---" << endl;
    niveles(raiz);
    cout << endl;

    return 0;
}
