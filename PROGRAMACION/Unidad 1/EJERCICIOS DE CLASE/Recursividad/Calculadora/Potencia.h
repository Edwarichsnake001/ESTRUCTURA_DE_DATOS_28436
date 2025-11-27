#pragma once

template<typename T>
class Potencia{
    protected:
        T base;
        T exponente;
    public:
        Potencia(T b, T e): base(b), exponente(e) {}
     T calculoPotencia();
   
};

#include "Potencia.tpp"