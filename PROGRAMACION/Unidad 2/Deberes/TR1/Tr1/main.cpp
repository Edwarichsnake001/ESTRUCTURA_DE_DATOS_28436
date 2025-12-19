#include <iostream>
#include <locale.h>
#include "ListaSimple.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    ListaSimple cursos;

    cout << "--- Construcción de la Lista (Ingreso de Cursos) ---\n";

    cursos.add(402, "Física 2");
    cursos.add(203, "EDO");
    cursos.add(501, "Metodología Investigativa");
    cursos.add(101, "Matemática");
    cursos.add(315, "Cultura Ambiental");
    
    cout << "Lista Original (Desordenada):\n";
    cursos.print();
    cout << "------------------------------------------------------\n";

    cursos.insertionSort();

    cout << "\nLista Final Ordenada por ID:\n";
    cursos.print();

    // 3. Presentar el análisis final
    cursos.showFinalAnalysis();

    return 0;
}

 /*Razones por las que Insertion Sort es adecuado para Listas Enlazadas:
    Bajo Costo de Desplazamiento: Insertion Sort solo requiere cambiar punteros, lo que es una operación O(1)[cite: 3, 11].
    No se necesita mover la estructura de datos completa (como ocurre en arreglos, donde un desplazamiento es O(N)).\n";

    No requiere acceso aleatorio (índice):** Los algoritmos que dependen de índices (como Quicksort o Heapsort en arreglos) 
    son lentos en listas enlazadas, ya que acceder a un índice 'i' requiere recorrer la lista O(i). Insertion Sort opera 
    secuencialmente, lo cual es natural para esta estructura.\n";
    
    Eficiente para listas casi ordenadas: Si la lista ya está casi ordenada, Insertion Sort realiza pocos desplazamientos 
    y comparaciones, lo que lo hace muy rápido en el mejor caso (O(N));*/