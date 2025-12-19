#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Producto {
    int id;
    string nombre;
    int cantidad;
    float precio;
    string categoria;
    string estado;
};

template <typename T, typename F>
int buscar(const T arr[], int n, F criterio) {
    for (int i = 0; i < n; i++) {
        if (criterio(arr[i])) return i;
    }
    return -1;
}

// ============================
// MOSTRAR INVENTARIO COMPLETO
// ============================
void mostrarInventario(const Producto inventario[], int n) {
    cout << "\n===== LISTA DE PRODUCTOS (ID Y NOMBRE) =====\n";
    cout << "+------+-----------------------------+\n";
    cout << "|  ID  |           Nombre           |\n";
    cout << "+------+-----------------------------+\n";

    for (int i = 0; i < n; i++) {
        cout << "| "
             << setw(4) << inventario[i].id << " | "
             << setw(27) << left << inventario[i].nombre.substr(0,27) << "|\n";
    }

    cout << "+------+-----------------------------+\n\n";
}

// ============================
// IMPRIMIR UN PRODUCTO
// ============================
void imprimirProducto(const Producto& p) {
    cout << "\n+------+----------------------+----------+---------+-----------------+--------------+\n";
    cout << "|  ID  |       Nombre        | Cantidad | Precio  |    Categoria    |    Estado    |\n";
    cout << "+------+----------------------+----------+---------+-----------------+--------------+\n";

    cout << "| "
         << setw(4) << p.id << " | "
         << setw(20) << left << p.nombre.substr(0,20) << right << " | "
         << setw(8) << p.cantidad << " | "
         << setw(7) << fixed << setprecision(2) << p.precio << " | "
         << setw(15) << left << p.categoria.substr(0,15) << right << " | "
         << setw(12) << left << p.estado.substr(0,12) << right << " |\n";

    cout << "+------+----------------------+----------+---------+-----------------+--------------+\n";
}

int main() {
    const int N = 25;

    Producto inventario[N] = {
        {1,  "Tornillo M6",         150, 0.15,  "Ferreteria", "Disponible"},
        {2,  "Tuerca M8",           90,  0.20,  "Ferreteria", "Disponible"},
        {3,  "Aceite Industrial",   25,  18.50, "Lubricantes","Disponible"},
        {4,  "Motor 1HP",           4,   120.0, "Motores",    "Bajo stock"},
        {5,  "Sensor Proximidad",   12,  32.0,  "Electronica","Disponible"},
        {6,  "Cable 10mm",          40,  2.80,  "Electrico",  "Disponible"},
        {7,  "Guantes Nitrilo",     0,   3.50,  "Seguridad",   "Agotado"},
        {8,  "Mascarilla N95",      100, 1.20,  "Seguridad",   "Disponible"},
        {9,  "Alcohol Industrial",  60,  4.10,  "Quimicos",    "Disponible"},
        {10, "PCB 2 capas",         20,  12.0,  "Electronica", "Disponible"},
        {11, "Cable UTP Cat6",      35,  0.90,  "Redes",       "Disponible"},
        {12, "Switch 8P",           10,  22.0,  "Redes",       "Disponible"},
        {13, "Router WiFi",         6,   35.0,  "Redes",       "Bajo stock"},
        {14, "Lima Metal",          18,  2.60,  "Ferreteria",  "Disponible"},
        {15, "Destornillador",      50,  1.80,  "Ferreteria",  "Disponible"},
        {16, "Bomba Agua 1/2HP",    3,   95.0,  "Motores",     "Bajo stock"},
        {17, "Soldadura Estaño",    45,  4.75,  "Electronica", "Disponible"},
        {18, "Lámpara LED 12W",     70,  1.50,  "Electrico",   "Disponible"},
        {19, "Cinta Aislante",      80,  0.60,  "Electrico",   "Disponible"},
        {20, "Pintura Acrílica",    25,  6.90,  "Pinturas",    "Disponible"},
        {21, "Brocha 2 pulgadas",   19,  1.30,  "Pinturas",    "Disponible"},
        {22, "Casco Seguridad",     15,  8.40,  "Seguridad",   "Disponible"},
        {23, "Botas Industriales",  10,  23.0,  "Seguridad",   "Bajo stock"},
        {24, "Multímetro Digital",  7,   14.0,  "Electronica", "Disponible"},
        {25, "Relay 12V",           55,  1.10,  "Electronica", "Disponible"}
    };

    int opcion;

    do {
        mostrarInventario(inventario, N);

        cout << "=== BUSQUEDA DE PRODUCTOS ===\n";
        cout << "1. Buscar por ID\n";
        cout << "2. Buscar por nombre\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int idBuscado;
            cout << "Ingrese ID: ";
            cin >> idBuscado;

            int pos = buscar(inventario, N, [idBuscado](const Producto& p) {
                return p.id == idBuscado;
            });

            if (pos != -1)
                imprimirProducto(inventario[pos]);
            else
                cout << "\nProducto no encontrado.\n";

        } else if (opcion == 2) {
            cin.ignore();
            string nombreBuscado;
            cout << "Ingrese nombre: ";
            getline(cin, nombreBuscado);

            int pos = buscar(inventario, N, [nombreBuscado](const Producto& p) {
                return p.nombre == nombreBuscado;
            });

            if (pos != -1)
                imprimirProducto(inventario[pos]);
            else
                cout << "\nProducto no encontrado.\n";

        } else if (opcion != 3) {
            cout << "\nOpción inválida.\n";
        }

    } while (opcion != 3);

    cout << "\nSaliendo del programa...\n";
    return 0;
}


