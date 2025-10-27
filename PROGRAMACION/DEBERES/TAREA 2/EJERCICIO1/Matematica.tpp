#include "Matematica.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
int Matematica<T>::calculoFactorial(long numero, int nivel)
{
    if (numero < 0) {
        throw invalid_argument("El número no puede ser negativo.");
    }
    cout << string(nivel * 2, ' ') << "Nivel " << nivel << ": factorial de " << numero << endl;
    if (numero == 0 || numero == 1) {
        return 1;
    } else {
        return numero * calculoFactorial(numero - 1, nivel + 1);
    }
}