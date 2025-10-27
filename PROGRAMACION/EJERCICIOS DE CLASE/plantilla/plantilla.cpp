#include <iostream>

using namespace std;

template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;
}

int main (){
    float precio1 = 15.75;
    float precio2 = 20.50;
    unsigned int stock1 = 30;
    unsigned int stock2 = 45;

    cout << "Precio mayor: $" << mayor(precio1, precio2) << endl;
    cout << "Stock mayor: $" << mayor(stock1, stock2) << endl;
}