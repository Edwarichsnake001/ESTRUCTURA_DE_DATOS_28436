#pragma once

#include <iostream>
#include <locale.h>

using namespace std;

template <typename T>
class MCD {
    private: 
        T num1;
        T num2;
    public:
        MCD(T n1, T n2): num1(n1), num2(n2) {}

        T calculoMCD(const T& num1,const T& num2);
};

#include "MCD.tpp"

