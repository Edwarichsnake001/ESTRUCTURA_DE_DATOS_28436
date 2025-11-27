#include "Matematica.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "es_ES.UTF-8"); //Para que lea caracteres latinos
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