#pragma once
#include "Cancion.h"
#include <iostream>
#include <string>

using namespace std;

class Nodo {
private:
    Cancion dato;
    Nodo* siguiente;
    Nodo* anterior;
public:
    Nodo(Cancion c);
   
	Cancion getDato();
	void setSiguiente(Nodo*);
	Nodo* getSiguiente();
	void setAnterior(Nodo*);
	Nodo* getAnterior();

    ~Nodo() {}
};
