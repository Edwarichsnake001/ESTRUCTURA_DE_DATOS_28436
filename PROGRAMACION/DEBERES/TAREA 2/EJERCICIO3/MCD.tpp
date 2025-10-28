#include "MCD.h"
#include <iostream>
#include <locale.h>
#include <stdexcept>

template <typename T>
T MCD<T>::calculoMCD(const T &num1, const T &num2)
{
    if (num1 < 0 || num2 < 0)
    {
        throw std::invalid_argument("Los números no pueden ser negativos.");
    }
    cout << "MCD(" << num1 << ", " << num2 << ")" << endl;
    if (num2 == 0)
    {
        return num1;
    }
    return calculoMCD(num2, num1 % num2);
}