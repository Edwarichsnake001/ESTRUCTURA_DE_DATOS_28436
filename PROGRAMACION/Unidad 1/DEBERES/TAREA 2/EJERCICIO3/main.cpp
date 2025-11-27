#include "MCD.h"
#include <iostream>
#include <locale.h>
#include <stdexcept>

using namespace std;

int main(){
    typedef int numeros;
    setlocale(LC_ALL, "es_ES.UTF-8");

    numeros n1, n2;
    cout << "Ingrese el primer número: ";
    cin >> n1;
    cout << "Ingrese el segundo número: ";
    cin >> n2;
    MCD<numeros> mcd(n1, n2);

    try {
        numeros resultado = mcd.calculoMCD(n1, n2);
        cout << "El MCD de " << n1 << " y " << n2 << " es: " << resultado << endl;
    } catch (const invalid_argument &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}