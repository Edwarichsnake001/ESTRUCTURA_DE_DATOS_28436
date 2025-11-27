#include <iostream>

using namespace std;

struct Nodo
{
    int dato;
    Nodo *siguiente;
};

struct Cola
{
    Nodo *front;
    Nodo *rear;
};

void inicializar(Cola &c)
{
    c.front = c.rear = nullptr;
}

bool estaVacia(Cola c)
{
    return c.front == nullptr;
}

void encolar(Cola &c, int valor)
{
    Nodo *nuevo = new Nodo{valor, nullptr};
    if (estaVacia(c))
    {
        c.front = c.rear = nuevo;
    }
    else
    {
        c.rear->siguiente = nuevo;
        c.rear = nuevo;
    }
}

int desencolar(Cola &c)
{
    if (estaVacia(c))
    {
        cout << "Cola vacía: \n";
        return -1;
    }
    else
    {
        Nodo *temp = c.front;
        int valor = temp->dato;
        c.front = c.front->siguiente;
        delete temp;
        return valor;
    }
}

int main(){
    Cola c;
    inicializar(c);

    //PRUEBA
    encolar(c,10);
    encolar(c,20);
    encolar(c,30);

    cout << "Desencolocado: " << desencolar(c) << endl;
    cout << "Desencolocado: " << desencolar(c) << endl;

    encolar(c,40);
    encolar(c,50);

    cout << "Desencolocado: " << desencolar(c) << endl;

    
    cout << "Direccion de cola: "<< &c << endl;
    cout << "Direccion del arreglo de datos:: "<< &c.rear<< endl;
    cout << "Direccion del primer elemento: "<< &c.front<< endl;
    return 0;
}
