#pragma once
#include "Nodo.h"

class ListaCircularDoble
{
private:
	Nodo* primero;
	Nodo* ultimo;
    Nodo* actual;

public:
	ListaCircularDoble();
	
	void insertar(Cancion c);
	void eliminar(Cancion c);
	void mostrar();
	bool buscar(Cancion c);

    void reproducirCancionActual();
    void siguienteCancion();
    void anteriorCancion();
    ~ListaCircularDoble(){}
};