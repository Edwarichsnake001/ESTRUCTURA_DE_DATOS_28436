// main.cpp
#include <iostream>
#include <locale.h>
#include <vector>
#include "Tarea.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    // 1. Crear los nodos dinámicos (registros pesados)
    // Se crean y permanecen en memoria, solo movemos las referencias.
    NodoTarea* n1 = new NodoTarea(5, "Revisar Documentos"); // Menor prioridad (debe ir al final)
    NodoTarea* n2 = new NodoTarea(2, "Merge Request Urgente"); // Mayor prioridad (debe ir al inicio)
    NodoTarea* n3 = new NodoTarea(4, "Reunión Equipo");
    NodoTarea* n4 = new NodoTarea(1, "Fix de Producción"); // Máxima prioridad
    
    // 2. Un vector contiene punteros a nodos que representan tareas.
    std::vector<NodoTarea*> vectorPunteros = {n1, n2, n3, n4};
    
    cout << "--- Estado Inicial del Vector de Punteros (Orden por Prioridad) ---\n";
    printVector(vectorPunteros);

    // Aplicar Bubble Sort Intercambiando Punteros
    bubbleSortPunteros(vectorPunteros);

    cout << "\n--- Estado Final del Vector (Ordenado por Prioridad) ---\n";
    printVector(vectorPunteros);

    // IMPORTANTE: Liberación de memoria dinámica
    for (NodoTarea* ptr : vectorPunteros) {
        delete ptr;
    }

    return 0;
}

/*Beneficio de Mover Punteros en Lugar de Registros Completos:
1.Costo de Movimiento:Mover un registro grande es costoso (implica muchas copias de memoria). 
Mover un puntero es extremadamente rápido O(1)
2.Eficiencia del Intercambio:Al usar `std::swap(puntero1, puntero2)`, solo se intercambian 
las direcciones en el vector, mientras que la estructura de datos `Tarea` permanece estática 
en la memoria. 
El costo de Bubble Sort sigue siendo O(N^2) en comparaciones, pero el costo constante por cada intercambio es mínimo.
3.Aplicación:Esta técnica es esencial cuando se ordenan estructuras grandes en memoria o cuando se requiere que los 
datos originales no se muevan de su ubicación física .*/