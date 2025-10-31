#include <iostream>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish");

    static int contador = 0;

    cout << "Llamada así mismo número: " << contador << endl;

    if (contador < 10) //Caso base
    {
        contador++;
        main(); //Caso recursivo
    }
}

/*¿CUÁNDO ESTO SERÍA INFINITO?
       Si no se incrementa 'contador' o se elimina la condición de parada (contador < 10),
       la función se llamaría a sí misma indefinidamente, provocando un desbordamiento de pila.
   ¿POR QUÉ ES UNA SOLUCIÓN NATURAL?{
       Aunque la recursión es funcional, esta no es una solución natural debido a que usar el main()
       es una práctica poco común con respecto a una resolución.
       De igual forma, usarla de esta forma puede generar confusión, dificultar la lectura del código 
       y provocar errores en entornos donde la recursión de 'main()' está restringida.  */