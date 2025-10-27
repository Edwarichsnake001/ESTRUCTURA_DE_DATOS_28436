#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Punto {
private:
    T x;
    T y;   
public:
    Punto(T x = 0, T y = 0) : x(x), y(y){}

    void fijarX(const Punto& otro);
    void fijarY(const Punto& otro);
    void mostrarX() const;
    void mostrarY() const;

};

#include "Punto.tpp"
