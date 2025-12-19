#include <iostream>
#include <locale.h>
#include <vector>
#include <string>
#include <iomanip>
#include "Cancion.h" 

using namespace std;

auto ordenarPorTitulo = [](const Cancion& a, const Cancion& b) {
    return a.titulo < b.titulo; 
};

int main() {
    setlocale(LC_CTYPE, "Spanish");

    std::vector<Cancion> playlist = {
        {"Queen", "Bohemian Rhapsody", 354.00},
        {"The Beatles", "Octopus' Garden", 482.00},
        {"Kendrick Lamar", "Not Like us", 187.00},
        {"Kenshi Yonezu", "Iris Out", 390.00},
        {"N.W.A", "F@*k tha police", 125.00},
        {"AC/DC", "TNT", 292.00},
        {"Gorillaz", "Silent Running", 267.00},
        {"Queen", "Somebady To Love", 187.00},
        {"The Beatles", "Yesterday", 125.00},
        {"YUZU", "Hyori ittai", 292.00},
        {"Lacco Tower", "Usubeni", 267.00},
        {"UGS", "Sugar Song To bitter Step", 187.00},
        {"Queen", "Killer Quuen", 187.00},
        {"The Beatles", "Here Comes The Sun", 125.00},
        {"GARDENIUS", "HUNTING FOR YOUR DREAM", 292.00},
        {"Gorillaz", "19-2000 (Souldchild Remix)", 267.00},
        {"Gorillaz", "Crashing Down", 187.00}
    };

    int n = playlist.size();
    
    quickSort(playlist, 0, n - 1, ordenarPorTitulo); 

    cout << "\n--- PLAYLIST ORDENADA---\n";
    imprimirVector(playlist);

    string titulo_buscado = "Silent Running";

    int indice = busquedaBinariaPorTitulo(playlist, titulo_buscado);

    cout << "\n--- RESULTADO DE BÚSQUEDA BINARIA ---\n";
    cout << "Buscando canción con Título: " << titulo_buscado << endl;
    
    if (indice != -1) {
        cout << "¡Canción encontrada en el índice" << indice << endl;
        playlist[indice].imprimir();
    } else {
        cout << "Canción no encontrada.\n";
    }

    string titulo_buscado2 = "F@*k tha police";

    int indice2 = busquedaBinariaPorTitulo(playlist, titulo_buscado);
    cout << "Buscando canción con Título: " << titulo_buscado2 << endl;

        if (indice2 != -1) {
        cout << "¡Canción encontrada en el índice" << indice2 << endl;
        playlist[indice2].imprimir();
    } else {
        cout << "Canción no encontrada.\n";
    }

    string titulo_no_encontrado = "No Vaseline";
    indice = busquedaBinariaPorTitulo(playlist, titulo_no_encontrado);

    cout << "\nBuscando Título: " << titulo_no_encontrado << "\n";
    if (indice == -1) {
        cout << "Canción no encontrada.\n";
    }

    return 0;
}