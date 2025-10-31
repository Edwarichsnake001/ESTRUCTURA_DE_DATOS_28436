#include "Factorial.h"
#include <iostream>
#include <locale.h>
#include <stdexcept>

using namespace std;

int main(){
    setlocale(LC_ALL, "es_ES.UTF-8");

    Factorial factorial;
    long numero;

    cout << "Ingrese un número para calcular su factorial: ";
    cin >> numero;

    try{
       long resultado = factorial.factorial(numero);
        cout << "El factorial de " << numero << " es: " << resultado << endl;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}