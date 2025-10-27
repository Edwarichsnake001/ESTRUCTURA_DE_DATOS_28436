#include "Estudiantes.h"
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <cstdint>

using namespace std;

typedef Estudiantes<string> EstudianteStr;
typedef Estudiantes<int> EstudianteInt;
typedef Lista<EstudianteStr> ListaEstudianteStr;
typedef int opciones;

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


int main(){
    EstudianteStr estudiante;
    ListaEstudianteStr lista;
    opciones opcion;

    do
    {
        cout << "\n————SRA ESPE————\n";
        cout << "1. Agregar Estudiante\n" 
             << "2. Mostrar Estudiante" << endl 
             << "3. Eliminar Estudiante" << endl
             << "0. SALIR"<<endl;
        
        cin >> opcion;

        switch (opcion)
        {
        case 1:
                estudiante.ingresarDatos();
                if (estudiante.validar())
                {
                    lista.agregarElemento(estudiante);
                }else{
                    cout << "Campos vacíos, no se registrará en el sistema...";
                }
                break;

        case 2:
                lista.mostrarElementos();
                printRawMem(reinterpret_cast<uint8_t*>(&estudiante), 16, 4);
                break;
        case 3:
                estudiante.ingresarDatos();
                lista.eliminarElemento(estudiante);
                printRawMem(reinterpret_cast<uint8_t*>(&lista), 16, 4);
                break;

        case 0:
            cout << "Saliendo del sistema...\n";
            break;
        
        default:
            cout << "Opción inválida... Intente otra vez"<<endl;
            break;
        }

    } while (opcion != 0);
    

}