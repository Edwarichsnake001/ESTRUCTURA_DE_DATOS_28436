#include <iostream>
#include <string>
#include <locale>
#include <chrono>

using namespace std;
using namespace std::chrono;


/*=====CALCULADORA */

int sumaNumerosNaturales(int n);

int potenciaNumero(int base, int expo);

int main(){

    int numero, base, exponente;

    cout << "Ingresa un número natural: ";
    cin >> numero;

    if(numero < 1){
        cout << "Numero no natural... Opción inválida."<<endl;
    } else if (numero == 0){
        cout << "La suma es cero..."<< endl;
    } else {
        cout << "primer numero " << numero << endl;
        auto inicio = high_resolution_clock::now();
        int resultado = sumaNumerosNaturales(numero);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<microseconds>(fin - inicio);

        cout << "La suma de los primeros " << numero << " números naturales es: " << resultado 
        << "Tiempo de ejecución: "<< duracion.count()<< endl;
    }

   /* if(exponente == 0){
        cout << "La potencia es 1..."<< endl;
    }else if (exponente < 0){
        cout << "Exponente inválido..."<< endl;
    } else {
        cout << "Ingresa la base: ";
        cin >> base;
        cout << "Ingresa el exponente: ";
        cin >> exponente;

        int resultadoPotencia = potenciaNumero(base, exponente);
        cout << base << " elevado a la potencia de " << exponente << " es: " << resultadoPotencia << endl;
    }*/

}

int sumaNumerosNaturales(int n){
    if(n == 1){
        return 1;
    } else {
        return n + sumaNumerosNaturales(n - 1);
    }
}

/*int potenciaNumero(int base, int expo){
    if(expo == 0){
        return 1;
    } else {
        return base * potenciaNumero(base, expo - 1);
    }
}*/

