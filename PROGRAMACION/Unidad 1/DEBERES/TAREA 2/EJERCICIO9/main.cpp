#include "Cadena.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

int main(){
    CadenaOps cadenaOps;
    string texto;
    cout << "Ingrese una cadena de texto: ";
    getline(cin, texto);

    try {
        if(cadenaOps.palindromo(texto, 0, texto.length() - 1)) {
            cout << "La cadena es un palíndromo." << endl;
        } else {
            cout << "La cadena no es un palíndromo." << endl;
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}