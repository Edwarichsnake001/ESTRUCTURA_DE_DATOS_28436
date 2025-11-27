#include <iostream>
#include <locale>
#include <string>

using namespace std;

class Factorial{
    public: 
    int calculadorFactorial(int n, int resultado = 1){
        if( n == 0){
            return resultado;
        } else {
            return calculadorFactorial(n - 1, n * resultado);
        }
    }
};

int main(){
    int numero;
    Factorial factorial;

    cout << "Ingrese un número para calular el factorial: ";
    cin >> numero;

    if(numero < 0){
        cout << "Número inválido..." << endl;
    } else {
        cout << "El factorial de " << numero << " es: " << factorial.calculadorFactorial(numero) << endl;
    }

    return 0;
}