#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>


void printHexVal(uint16_t val) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//Raw Momory lo que muestra es el almacenamiento de los datos en bytes, vistos de forma hexadecimal.
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
    for (uint16_t l = 0; l < lines; ++l) {
        std::cout << reinterpret_cast<void*>(p) << " ";
        for (uint16_t u = 0; u < linebytes; ++u) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)p[u] << " ";
        }
        p += linebytes;
        std::cout << "\n";
    }
}

//====================================================================================
// Clase Productos con inspección de memoria
//====================================================================================
template <typename TNombre, typename TPrecio, typename TStock, typename TId>
class Productos {
private:
    TNombre* Nombre;
    TPrecio* Precio;
    TStock* Stock;
    TId* Id;

public:
    Productos(std::string nombre, float precio, int stock, int id) {
        Nombre = new std::string(nombre);
        Precio = new float(precio);
        Stock = new int(stock);
        Id = new int(id);
    }

    void mostrarInventario() {
        std::cout << "=======================================" << std::endl;
        std::cout << "Nombre: " << *Nombre << " Direccion: " << Nombre << std::endl;
        std::cout << "Precio: " << *Precio << " Direccion: " << Precio << std::endl;
        std::cout << "Stock: " << *Stock << " Direccion: " << Stock << std::endl;
        std::cout << "ID: " << *Id << " Direccion: " << Id << std::endl;
        std::cout << "=======================================" << std::endl;
    }

    void mostrarMemoriaCruda() {
        std::cout << "\n Memoria del objeto Productos:\n";
        printRawMem(reinterpret_cast<uint8_t*>(this), 16, 2);

        std::cout << "\n Memoria de Nombre:\n";
        printRawMem(reinterpret_cast<uint8_t*>(Nombre), 16, 2);

        std::cout << "\n Memoria de Precio:\n";
        printRawMem(reinterpret_cast<uint8_t*>(Precio), 16, 1);

        std::cout << "\n Memoria de Stock:\n";
        printRawMem(reinterpret_cast<uint8_t*>(Stock), 16, 1);

        std::cout << "\n Memoria de Id:\n";
        printRawMem(reinterpret_cast<uint8_t*>(Id), 16, 1);
    }

    void operator++(int) {
        int incremento = 10;
        *Stock += incremento;
        std::cout << "Stock aumentado en " << incremento << " unidades." << std::endl;
    }

    ~Productos() {
        std::cout << "Liberando memoria: " << *Nombre << std::endl;
        delete Nombre;
        delete Precio;
        delete Stock;
        delete Id;
    }
};

int main() {
    Productos<std::string, float, int, int>* producto1 = new Productos<std::string, float, int, int>("Cuaderno", 2.5, 100, 12);

    producto1->mostrarInventario();
    producto1->mostrarMemoriaCruda();

    (*producto1)++;
    producto1->mostrarInventario();
    producto1->mostrarMemoriaCruda();

    delete producto1;

    return 0;
}
