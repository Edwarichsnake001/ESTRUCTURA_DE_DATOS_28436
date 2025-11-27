#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Nodo {
    int val;
    int prioridad;
    Nodo *siguiente;
};

struct PQueue {
    Nodo *head;
};

void init(PQueue &q) {
    q.head = nullptr;
}

bool empty(const PQueue &q) {
    return q.head == nullptr;
}

void push(PQueue &q, int v, int p) {
    Nodo *n = new Nodo{v, p, nullptr};
    if (empty(q) || p > q.head->prioridad) {
        n->siguiente = q.head;
        q.head = n;
        return;
    }

    Nodo *cur = q.head;
    while (cur->siguiente && cur->siguiente->prioridad >= p) {
        cur = cur->siguiente;
    }

    n->siguiente = cur->siguiente;
    cur->siguiente = n;
}

bool pop(PQueue &q, int &outVal, int &outPri) {
    if (empty(q)) return false;

    Nodo *t = q.head;
    outVal = t->val;
    outPri = t->prioridad;
    q.head = t->siguiente;
    delete t;
    return true;
}

int main() {
    PQueue q;
    init(q);
    srand(time(nullptr));

    int cantidad;
    cout << "¿Cuántos elementos deseas insertar? ";
    cin >> cantidad;

    int prioridadAnterior = 0;

    for (int i = 0; i < cantidad; i++) {
        int valor;
        cout << "Ingrese el valor #" << i + 1 << ": ";
        cin >> valor;

        int prioridad;
        do {
            prioridad = rand() % 3 + 1;
        } while (prioridad == prioridadAnterior); // Evita repetir la última prioridad

        prioridadAnterior = prioridad;

        push(q, valor, prioridad);
        cout << "Insertado: " << valor << " con prioridad aleatoria " << prioridad << "\n";
    }

    int v, p;
    cout << "\nExtrayendo elementos en orden de prioridad:\n";
    while (pop(q, v, p)) {
        cout << "Elemento " << v << " con prioridad " << p << " eliminado\n";
    }

    return 0;
}
