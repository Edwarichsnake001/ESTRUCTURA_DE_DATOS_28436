#include <iostream>

using namespace std;

#define MAX 5

//define la estrictira u define la cola estática
struct Cola
{
    int datos[MAX];
    int front;
    int rear;

};

void inicializar(Cola &c){
    c.front = 0;
    c.rear = -1;
}

bool estaVacio(Cola c){
    return c.front > c.rear;
}


bool estaLlena(Cola c){
    return c.rear == MAX;
}

void encolar(Cola &c, int valor){
    if(!estaLlena(c)){
        c.datos[++c.rear] = valor;
        cout << "Elemento " << valor << " encolado\n";
    }else{
        cout << "Cola llena\n";
    }
}

//Eliminar el elemento del frente
int desencolar(Cola &c){
    if(!estaVacio(c)){
        return c.datos[c.front++];
    }else{
        cout << "La cola está vacía\n";
        return -1;
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
    encolar(c,60);

    cout << "Desencolocado: " << desencolar(c) << endl;

    
    cout << "Direccion de cola: "<< &c << endl;
    cout << "Direccion del arreglo de datos:: "<< &c. datos << endl;
    cout << "Direccion del primer elemento: "<< &c.datos[0] << endl;
    return 0;
}


