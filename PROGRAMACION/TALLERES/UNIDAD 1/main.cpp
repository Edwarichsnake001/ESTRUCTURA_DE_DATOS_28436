#include "Punto.h"
#include <iostream>

using namespace std;

int main() {
    Punto<int> p1(3, 4);
    Punto<double> p2(5.5, 6.6);

    cout << "Punto p1:" << endl;
    p1.mostrarX();
    p1.mostrarY();

    cout << "Punto p2:" << endl;
    p2.mostrarX();
    p2.mostrarY();

    Punto<int> p3;
    p3.fijarX(p1);
    p3.fijarY(p1);

    cout << "Punto p3 (despues de fijar desde p1):" << endl;
    p3.mostrarX();
    p3.mostrarY();

    return 0;
}

