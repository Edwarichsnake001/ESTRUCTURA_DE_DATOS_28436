#include <iostream>

using namespace std;

const int MAXQ = 5;

struct ColaCircular
{
    int data[MAXQ];
    int front;
    int rear;
    int contador;
};

void inicializar(ColaCircular &c)
{
    c.front = 0;
    c.rear = -1;
    c.contador = 0;
}

bool vacio(const ColaCircular &c)
{
    return c.contador == 0;
}

bool llena(const ColaCircular &c)
{
    return c.contador == MAXQ;
}

bool encolar(ColaCircular &c, int valor)
{
    if (llena(c))
    {
        return false;
    }
    c.rear = (c.rear + 1) % MAXQ; // Avanza el índice de forma circular
    c.data[c.rear] = valor;
    c.contador++;
    return true;
}

bool desencolar(ColaCircular &c, int &out)
{
    if (vacio(c))
    {
        return false;
    }
    out = c.data[c.front];
    c.front = (c.front + 1) % MAXQ;
    c.contador--;
    return true;
}

int main()
{
    ColaCircular c;
    inicializar(c);

    for (int i = 1; i <= 5; i++)
    {
        cout << (encolar(c, i * 10) ? "Encolado.\n " : "Cola llena.\n");
    }

    int x;
    desencolar(c, x);
    cout << "Desencolado: " << x << endl;

    encolar(c, 60);

    while (desencolar(c, x))
    {
        cout << "Desencolado: " << x << "\n";
    }
}