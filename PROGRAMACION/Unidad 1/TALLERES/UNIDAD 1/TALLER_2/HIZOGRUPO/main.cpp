#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Estudiante {
private:
    string Nombre;
    int Edad;
    int Cedula;

public:
    Estudiante(string nombre, int edad, int cedula) {
        Nombre = nombre;
        Edad = edad;
        Cedula = cedula;
    }

    Estudiante() {}

    void Insertar() {
        cin.ignore(); // limpia el buffer antes de getline
        cout << "Ingresar nombre: ";
        getline(cin, Nombre);
        cout << "Ingresar edad: ";
        cin >> Edad;
        cout << "Ingresar cedula: ";
        cin >> Cedula;
    }

    void mostrar() const {
        cout << "Nombre: " << Nombre << endl;
        cout << "Edad: " << Edad << endl;
        cout << "Cedula: " << Cedula << endl;
    }

    int getEdad() const {
        return Edad;
    }
};

// Función recursiva para sumar edades
int sumarEdades(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        return 0;
    } else {
        int ultimaEdad = estudiantes.back().getEdad();
        vector<Estudiante> subvector(estudiantes.begin(), estudiantes.end() - 1);
        return ultimaEdad + sumarEdades(subvector);
    }
}

int main() {
    vector<Estudiante> estudiante;
    Estudiante e1;

    for (int n = 0; n < 3; n++) {
        cout << "\nEstudiante " << n + 1 << ":" << endl;
        e1.Insertar();
        estudiante.push_back(e1);
    }

    cout << "\nEstudiantes registrados:\n";
    for (int n = 0; n < 3; n++) {
        estudiante.at(n).mostrar();
        cout << endl;
    }

    int suma = sumarEdades(estudiante);
    cout << "Suma de edades: " << suma << endl;

    return 0;
}
