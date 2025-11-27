#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

template <typename T>
class ArregloOps
{
private:
    T sumaRecursiva(const vector<T> &v, int n);

public:
    T suma(const vector<T> &v);
};

template <typename T>
T ArregloOps<T>::sumaRecursiva(const vector<T> &v, int n)
{
    if (n < 0) //CASO BASE
    {              
        return T(); // valor neutro (0 para numéricos)
    }
    else
    {
        return v[n] + sumaRecursiva(v, n - 1); //CASO RECURSIVO
    }
}

template <typename T>
T ArregloOps<T>::suma(const vector<T> &v)
{
    return sumaRecursiva(v, v.size() - 1);
}

/* ¿CUÁNDO ESTO SERÍA INFINITO?
       La recursión se volvería infinita si el índice 'n' no se reduce correctamente en cada llamada.
       Por ejemplo, si se usa 'n + 1' en lugar de 'n - 1', o si se omite el caso base (n < 0),
       el algoritmo entraría en un ciclo indefinido y provocaría un desbordamiento de pila.
    */

    /* ¿POR QUÉ ES UNA SOLUCIÓN NATURAL?
       La suma de los elementos de un vector puede verse como:
       suma(v) = v[n] + suma(v[0..n-1])
       Esta definición se adapta perfectamente a la recursión, ya que el problema se descompone
       en una versión más pequeña de sí mismo.
    */