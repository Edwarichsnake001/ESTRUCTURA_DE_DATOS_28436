#include "PalabraReversa.h"
#include <iostream>
#include <string>
#include <locale.h>

using namespace std;

int main(){
    string entrada;
    cout<<"Ingrese una palabra o frase corta: ";
    getline(cin,entrada);

    CadenaOps palabra;

    cout<< "Texto invertido: ";

    palabra.imprimirInverso(entrada);

}