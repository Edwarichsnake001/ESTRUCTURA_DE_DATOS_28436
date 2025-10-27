#include <iostream>
#include <string>
#include <locale>

using namespace std;

template<typename T>
class SecuanciasParImpar{
    public:
    void generarSecuencia(int n){
        if (n != 1){
            cout << n << " — ";  
            if (n % 2 == 0){
                generarSecuencia(n / 2); 
            } else {
                generarSecuencia(3 * n + 1); 
            }
        }
    }
};

int main(){
    int numero;
    SecuanciasParImpar<int> secuencia;

    cout << "Ingresa un número entero positivo: ";
    cin >> numero;

    if (numero <= 0){
        cout << "Número inválido. Por favor, ingresa un número entero positivo." << endl;
    } else {
        secuencia.generarSecuencia(numero);
        cout << endl;
    }

    return 0;
}