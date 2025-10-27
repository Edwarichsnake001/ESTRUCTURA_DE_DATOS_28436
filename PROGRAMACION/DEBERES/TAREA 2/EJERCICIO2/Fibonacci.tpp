#include <iostream>
#include "Fibonacci.h"
#include <stdexcept>

template <typename T>
int Fibonacci<T>::sucesionFibonacci(int n)
{
    if (n < 0) {
        throw invalid_argument("El numero debe ser no negativo.");
    }
    if(n == 0) {
        return 0;
    }else if(n == 1) {
        return 1;
    }else {
        return sucesionFibonacci(n - 1) + sucesionFibonacci(n - 2);
    }
}