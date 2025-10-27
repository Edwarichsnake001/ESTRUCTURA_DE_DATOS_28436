/*UNIDAD DE LAS FUERZAS ARMADAS
GRUPO N�4
    CHICAIZA MICHAEL
    FUENTES JORGE
    JACOME MICAELA
    ROGERON MATEO
PROBLEMA 8

*/

#include <iostream>
#include <string>

using namespace std;

template <typename T>
void compMayor(const T &a, const T &b)
{
    if (a > b){
        cout << a << " es mayor que " << b << endl;
    }else if (a == b){
        cout << a << " es igual a: " << b << endl;
    }else{
        cout << b << " es mayor a: " << a << endl;
    }
}

// Deportista como clase gen�rica para el ejemplo
class Futbolista{
private:
    string nombre;
    int goles;

public:
    Futbolista(string n, int p) : nombre(n), goles(p) {}

    // sobrecargar el operador para indicar como operar >
    bool operator>(const Futbolista &otro) const
    {
        return this->goles > otro.goles;
    }

    // sobrecargar el operador para indicar como operar ==
    bool operator==(const Futbolista &otro) const
    {
        return this->goles == otro.goles;
    }

    friend ostream &operator<<(ostream &os, const Futbolista &f)
    {
        os << f.nombre << " (" << f.goles << ")";
        return os;
    }
};

int main()
{
    int numMenu;
    int num1, num2;
    float decimal1, decimal2;
    string palabra1, palabra2;

    do
    {
        cout << "----COMPARACI�N DE DATOS----" << endl;
        cout << "1. ENTEROS" << endl;
        cout << "2. DECIMALES" << endl;
        cout << "3. STRING" << endl;
        cout << "4. CLASE" << endl;
        cout << "0. SALIR" << endl;
        cout << "Selecciona una opci�n: ";
        cin >> numMenu;
        cout << endl;

        switch (numMenu)
        {
        case 1:
            cout << "Ingrese dos enteros: ";
            cin >> num1 >> num2;
            compMayor(num1, num2);
            break;
        case 2:
            cout << "Ingrese dos n�meros decimales: ";
            cin >> decimal1 >> decimal2;
            compMayor(decimal1, decimal2);
            break;
        case 3:
            cout << "Ingrese dos palabras: ";
            cin >> palabra1 >> palabra2;
            compMayor(palabra1, palabra2);
            break;
        case 4:
        {

            // definimos variables dentro de este case para la clase (eN CONTRA DEL CLEAN CODE PERO ES PARA EJEMPLO)
            string nom1, nom2;
            int gol1, gol2;

            cout << "Ingresa el nombre y goles de la temporada del futbolista 1: ";
            cin >> nom1 >> gol1;
            cout << "Ingresa el nombre y goles de la temporada del futbolista 2: ";
            cin >> nom2 >> gol2;

            Futbolista fut1(nom1, gol1), fut2(nom2, gol2);
            compMayor(fut1, fut2);

            break;
        }

        case 0:

            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opci�n inv�lida. Intente de nuevo..." << endl;
            break;
        }
    } while (numMenu != 0);

    return 0;
}
