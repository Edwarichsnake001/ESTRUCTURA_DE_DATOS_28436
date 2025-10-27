#include <iostream>

using namespace std;

template <typename T>
void Punto<T>::fijarX(const Punto<T>& otro) {
    x = otro.x;
}

template <typename T>
void Punto<T>::fijarY(const Punto<T>& otro) {
    y = otro.y;
}

template <typename T>
void Punto<T>::mostrarX() const {
    cout << "X: " << x << endl;
}

template <typename T>
void Punto<T>::mostrarY() const {
    cout << "Y: " << y << endl;
}
