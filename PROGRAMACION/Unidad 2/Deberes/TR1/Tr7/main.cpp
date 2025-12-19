// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "Persona.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    std::vector<Persona> personas = {

        {101, "Carlos", 35, {"Principal", 101, "Quito"}}, 
        {204, "Ana",    28, {"Calle A", 50,  "Guayaquil"}}, 
        {310, "Elena",  35, {"Central", 200, "Quito"}}, 
        {402, "Bruno",  40, {"Av. Sur", 15,  "Guayaquil"}},
        {507, "Daniel", 28, {"2da Av.", 70,  "Guayaquil"}}  
    };
    
    cout << "--- Estado Inicial del Arreglo de Personas ---\n";
    cout << "+---+---------------+-----+---------------+---------------+\n";
    cout << "| ID| Nombre        | Edad| Ciudad        | Calle         |\n";
    cout << "+---+---------------+-----+---------------+---------------+\n";
    for (const auto& p : personas) {
        p.print();
        cout << "\n";
    }
    cout << "+---+---------------+-----+---------------+---------------+\n";

    exchangeSort(personas);

    cout << "\n--- Estado Final del Arreglo (Ordenado: Ciudad -> Edad -> Nombre) ---\n";
    cout << "+---+---------------+-----+---------------+---------------+\n";
    cout << "| ID| Nombre        | Edad| Ciudad        | Calle         |\n";
    cout << "+---+---------------+-----+---------------+---------------+\n";
    for (const auto& p : personas) {
        p.print();
        cout << "\n";
    }
    cout << "+---+---------------+-----+---------------+---------------+\n";

    return 0;
}

/*Impacto de Exchange Sort con Registros Complejos y Pesados:
1.Costo de Comparación (Costo Fijo Alto):Cada comparación requiere evaluar tres niveles(`ciudad`, `edad`, `nombre`).
Esto hace que el costo constante de la operación O(1) sea alto. Dado que el algoritmo es O(n^2) en comparaciones, 
este alto costo se multiplica por N^2.

2.Costo de Movimiento (Costo Variable Alto):Cada intercambio (`std::swap`) implica copiar la estructura completa, 
incluyendo la sub-estructura `Direccion`. Si la estructura `Persona` es 'pesada', el costo de mover estos datos 
es alto y se ejecuta tantas veces como sea necesario (puede ser hasta $athcal{O}(N^2)$ intercambios).

3.Costo en Memoria por Mover Registros Grandes:El costo en memoria (tiempo/latencia) de mover registros grandes 
es significativo. En Exchange Sort, el número de intercambios no es fijo como en Selection Sort, lo que significa 
que en el peor caso, Exchange Sort es menos eficiente para estructuras pesadas que Selection Sort, 
debido al potencial de muchos más intercambios.\n";*/