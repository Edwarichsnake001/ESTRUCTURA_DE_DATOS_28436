#pragma once

#include <iostream>
#include <string>



struct Estudiante
{
    std::string id;
    std::string nombre;
    int notaFinal;

    bool operator<(const Estudiante& otro)const
    {
        return notaFinal < otro.notaFinal;
    }

    bool operator>(const Estudiante& otro)const
    {
        return notaFinal > otro.notaFinal;
    }

    void imprimir()
    {
        std::cout << "[ID " << id <<", Nombre: "<<nombre<<", Nota: "<< notaFinal << "]\n";
    }

};
