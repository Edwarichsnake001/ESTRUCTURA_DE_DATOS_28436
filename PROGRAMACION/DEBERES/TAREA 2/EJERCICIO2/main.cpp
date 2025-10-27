#include "Fibonacci.h"
#include <iostream>
#include <stdexcept>
#include <locale>

using namespace std;

int main(){

    Fibonacci<int> fib;
    typedef int Numero;

    Numero n, opciones;

    cout << "Ingrese un numero para calcular su Fibonacci: ";
    cin >> n;
    try {
        Numero resultado = fib.sucesionFibonacci(n);
        cout << "El Fibonacci de " << n << " es: " << resultado << endl;
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
}