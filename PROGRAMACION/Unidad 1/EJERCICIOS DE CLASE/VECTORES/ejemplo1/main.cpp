#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

int main(){
    vector<int> numeros = {5, 10, 15, 20};

    try
    {
        cout << "Elemento en posicion 2: "<< numeros.at(2) << endl;
        cout << "Elemento en posicion 10: "<< numeros.at(10) << endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << endl;
    }
    

    /*Ingresar datos de nombre cedula y edad, funcion recurdica que realice la operacion con las edades, calucular la suma total de las edades o determinar la edad máxima
    Uso del metodo .at() para acceder */
}