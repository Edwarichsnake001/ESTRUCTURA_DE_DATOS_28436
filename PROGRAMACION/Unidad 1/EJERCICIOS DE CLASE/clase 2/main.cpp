#include <iostream>
#include <string>

using namespace std;

typedef unsigned int CodigoProducto;
typedef float Precio;
typedef string NombreProducto;
typedef unsigned int Cantidad;
typedef string Categoria;

struct Producto
{
    CodigoProducto codigo;
    NombreProducto nombre;
    Precio precio;
    Cantidad stock;
    Categoria categoria;
};

void mostrarProducto(const Producto &p)
{
    cout << "C�digo: " << p.codigo << endl;
    cout << "Nombre: " << p.nombre << endl;
    cout << "Precio: $" << p.precio << endl;
    cout << "Stock: " << p.stock << endl;
    cout << "Categor�a: " << p.categoria << endl;
}

int main()
{
    Producto producto1 = {1001, "Laptop", 1500.00, 10, "Electr��nica"};

    cout << "Detalles del Producto 1:" << endl;
    mostrarProducto(producto1);
    cout << endl;

    return 0;
}
