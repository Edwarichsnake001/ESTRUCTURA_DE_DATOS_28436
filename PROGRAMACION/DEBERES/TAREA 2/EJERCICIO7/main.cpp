#include "Arreglo.h"
#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "spanish");
    typedef int Numeros;

    ArregloOps<int> arregloInt;
    Numeros cantidad;

    cout << "¿Cuántos números enteros desea ingresar? ";
    cin >> cantidad;

    if(cantidad <= 0){
        cout << "La cantidad debe ser un número positivo mayor que cero." << endl;
        return 1;
    }

    vector<Numeros> numeros(cantidad);
    
    cout << "Ingrese " << cantidad << " números enteros:" << endl;
    for(int i = 0; i < cantidad; i++){
        cin >> numeros[i];
    }

    Numeros sumaTotal = arregloInt.suma(numeros);
    cout << "La suma de los números ingresados es: " << sumaTotal << endl;
    
    return 0;
}