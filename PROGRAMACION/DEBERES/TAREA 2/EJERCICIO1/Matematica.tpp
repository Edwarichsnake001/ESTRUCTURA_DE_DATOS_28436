#include "Matematica.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
int Matematica<T>::calculoFactorial(long numero, int nivel)
{

    //El numero negativo no existe en factorial lo que ocasionaría errores
    if (numero < 0) {
        throw invalid_argument("El número no puede ser negativo.");
    }
    cout << string(nivel * 2, ' ') << "Nivel " << nivel << ": factorial de " << numero << endl;

    if (numero == 0 || numero == 1) { //Casos base: 0! = 1 y 1! = 1
        return 1;
    } else {
        return numero * calculoFactorial(numero - 1, nivel + 1); //Paso recuersivo
    }
}

/*CUANDO PUEDE SER INFINITA? 
Cuando el numero no se reduce en cada llamado o si el caso base sea numero < 0
¿Por qué es natural?
El factorial de un número se define como n! = n * (n-1)!. Aquí podemos observar
como el factorial necesita de un factorial para continuar, por lo que se puede
emplear una función recursiva*/

