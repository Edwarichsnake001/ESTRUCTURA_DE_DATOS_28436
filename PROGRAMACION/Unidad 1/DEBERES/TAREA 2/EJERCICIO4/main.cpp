#include <iostream>
#include "Torre.h"

using namespace std;

int main()
{
    Hanoi torre;
    int disco;

    do
    {
        cout << "Ingrese el número de discos: ";
        cin >> disco;

        if (disco > 10)
        {
            cout << "Número de discos demasiado grande, por favor ingrese un número menor o igual a 10." << endl;
        }
        else
        {
            try
            {
                torre.moverDiscos(disco, 'A', 'C', 'B');
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error a la hora de movimientos" << e.what() << '\n';
            }
        }
    } while (disco > 10);
}