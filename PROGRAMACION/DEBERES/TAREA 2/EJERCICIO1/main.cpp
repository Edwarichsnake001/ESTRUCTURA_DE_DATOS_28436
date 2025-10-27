#include "Matematica.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <locale>

using namespace std;

int main(){
    Matematica<int> matematica;
    typedef long Numero;
    typedef int Enteros;
    Numero numero;

    cout << "Ingrese un número para calcular su factorial: ";
    cin >> numero;
    try {
        Enteros resultado = matematica.calculoFactorial(numero, 0);
        cout << "El factorial de " << numero << " es: " << resultado << endl;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;

}