#include <iostream>
#include <string>
#include "Lista.h"

using namespace std;

struct Puntaje
{
    string inciales;
    int puntuacion;

    bool operator<(const Puntaje &valor) const
    {
        return puntuacion > valor.puntuacion;
    }
    friend std::ostream &operator<<(std::ostream &os, const Puntaje &se)
    {
        os << se.inciales << " : " << se.puntuacion;
        return os;
    }
};

int main()
{
    Lista<Puntaje> puntajes;
    puntajes.insertar({"MAT",18000});
    puntajes.insertar({"LIS",84450});
    puntajes.insertar({"MAT",65222});
    puntajes.insertar({"MAT",10000});

    cout<<"======PUNTAJES ANTES DE ORDENAR======\n";
    puntajes.mostrar();
    

    puntajes.ordenPorIntercambio();

    cout<<"======PUNTAJES TRAS ORDENAR======\n";
    puntajes.mostrar();

    return 0;
}