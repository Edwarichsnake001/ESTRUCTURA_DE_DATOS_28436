#include <iostream>
#include <string>
#include <cctype>   //toupper e isdigit
using namespace std;

// Clase Vehiculo con todos los atributos
class Vehiculo {
	private:
	    string placa;
	    string marca;
	    string dueno;
	    int anio;
	    
	public:
	
	    Vehiculo() : placa(""), marca(""), dueno(""), anio(0) {}
	    
	    Vehiculo(string p, string m, string d, int a) 
	        : placa(p), marca(m), dueno(d), anio(a) {}
	        
	    string getPlaca() const{
	    	return placa;
		}
	
	    void mostrar() const {
	        cout << "  Placa: " << placa << endl;
	        cout << "  Marca: " << marca << endl;
	        cout << "  Dueno: " << dueno << endl;
	        cout << "  Anio: " << anio << endl;
	    }
};

// Nodo para la lista enlazada simple
struct Nodo {
    Vehiculo vehiculo;
    Nodo* siguiente;
    	Nodo(Vehiculo v) : vehiculo(v), siguiente(nullptr) {}
};

// Funcion auxiliar para convertir texto a mayusculas
string aMayusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}

// Tabla Hash para gestionar vehiculos
class TablaHash {
	private:
	    Nodo** tabla; //grupo de cajitas
	    int tam;
	
	public:
	    TablaHash(int t) {
	        tam = t;
	        tabla = new Nodo*[tam];
	        for (int i = 0; i < tam; i++) {
	            tabla[i] = nullptr;
	        }
	    }
	
	    ~TablaHash() {
	        for (int i = 0; i < tam; i++) {
	            Nodo* actual = tabla[i];
	            while (actual != nullptr) {
	                Nodo* temp = actual;
	                actual = actual->siguiente;
	                delete temp;
	            }
	        }
	        delete[] tabla;
	    }
	   
	    // Funcion Hash por modulo (division)
	    int funcionHash(const string& placa) {
	        int numero = 0;
	        for (char c : placa) { //Separa solo los numeros
	            if (isdigit(c)) {               //48
	                numero = numero * 10 + (c - '0');
	            }
	        }
	        return numero % tam;
	    }
	
	    // Insertar vehiculo en la tabla hash
	    void insertar(const Vehiculo& vehiculo) {
	        int pos = funcionHash(vehiculo.getPlaca());
	        Nodo* nuevo = new Nodo(vehiculo);
	        nuevo->siguiente = tabla[pos];
	        tabla[pos] = nuevo;
	    }
	
	    // Buscar vehiculo por placa usando tabla hash
	    // Complejidad: O(1) en promedio, O(n) en el peor caso
	    Vehiculo* buscar(const string& placa) {
	        int pos = funcionHash(placa);
	        Nodo* actual = tabla[pos];
	
	        while (actual != nullptr) {
	            if (aMayusculas(actual->vehiculo.getPlaca()) == aMayusculas(placa)) {
	                return &(actual->vehiculo);
	            }
	            actual = actual->siguiente;
	        }
	        return nullptr;
	    }
	
	    void mostrarTodos() {
	        cout << "\n========================================" << endl;
	        cout << "  VEHICULOS EN EL DEPOSITO" << endl;
	        cout << "========================================" << endl;
	        
	        int contador = 0;
	        for (int i = 0; i < tam; i++) {
	            Nodo* actual = tabla[i];
	            while (actual != nullptr) {
	                contador++;
	                cout << "\nVehiculo #" << contador << ":" << endl;
	                actual->vehiculo.mostrar();
	                cout << "----------------------------------------" << endl;
	                actual = actual->siguiente;
	            }
	        }
	        
	        if (contador == 0) {
	            cout << "No hay vehiculos en el deposito." << endl;
	        } else {
	            cout << "\nTotal de vehiculos: " << contador << endl;
	        }
	    }
	
	    void mostrarEstructuraHash() {
	        cout << "\n========================================" << endl;
	        cout << "  ESTRUCTURA DE LA TABLA HASH" << endl;
	        cout << "========================================" << endl;
	        
	        for (int i = 0; i < tam; i++) {
	            cout << "Posicion " << i << ": ";
	            Nodo* actual = tabla[i];
	            if (actual == nullptr) {
	                cout << "[VACIA]";
	            } else {
	                while (actual != nullptr) {
	                    cout << actual->vehiculo.getPlaca() << " -> ";
	                    actual = actual->siguiente;
	                }
	                cout << "NULL";
	            }
	            cout << endl;
	        }
	    }
};

// Funcion para cargar vehiculos predefinidos
void cargarVehiculosPredefinidos(TablaHash& tabla) {
    tabla.insertar(Vehiculo("PBA-123", "Toyota Corolla", "Juan Perez", 2020));
    tabla.insertar(Vehiculo("GSD-432", "Honda Civic", "Maria Garcia", 2019));
    tabla.insertar(Vehiculo("TAA-900", "Ford Focus", "Carlos Rodriguez", 2021));
    tabla.insertar(Vehiculo("ABC-100", "Chevrolet Spark", "Ana Martinez", 2018));
    tabla.insertar(Vehiculo("DEF-921", "Nissan Sentra", "Luis Hernandez", 2022));
    tabla.insertar(Vehiculo("KRL-334", "Mazda 3", "Sofia Lopez", 2020));
    tabla.insertar(Vehiculo("MJR-846", "Hyundai Elantra", "Pedro Gomez", 2019));
    tabla.insertar(Vehiculo("HMO-237", "Kia Rio", "Laura Fernandez", 2021));
    tabla.insertar(Vehiculo("JHS-448", "Volkswagen Jetta", "Diego Sanchez", 2020));
    tabla.insertar(Vehiculo("KRL-649", "Toyota Yaris", "Carmen Diaz", 2018));
    tabla.insertar(Vehiculo("FRT-105", "Honda Accord", "Roberto Torres", 2022));
    tabla.insertar(Vehiculo("SCH-342", "Ford Escape", "Patricia Ramirez", 2021));
    tabla.insertar(Vehiculo("IOP-675", "Chevrolet Cruze", "Miguel Flores", 2019));
    tabla.insertar(Vehiculo("QWE-800", "Nissan Versa", "Elena Castro", 2020));
    tabla.insertar(Vehiculo("RTY-374", "Mazda CX-5", "Fernando Ortiz", 2022));
    tabla.insertar(Vehiculo("YUI-987", "Hyundai Tucson", "Gabriela Ruiz", 2021));
    tabla.insertar(Vehiculo("OPA-091", "Kia Sportage", "Andres Morales", 2019));
    tabla.insertar(Vehiculo("SDF-103", "Volkswagen Tiguan", "Valeria Jimenez", 2020));
    tabla.insertar(Vehiculo("GHJ-234", "Toyota RAV4", "Javier Mendoza", 2022));
    tabla.insertar(Vehiculo("KLZ-986", "Honda CR-V", "Daniela Vargas", 2021));
}

void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "  DEPOSITO DE VEHICULOS - MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. Buscar vehiculo por placa" << endl;
    cout << "2. Mostrar todos los vehiculos" << endl;
    cout << "3. Mostrar estructura de tabla hash" << endl;
    cout << "4. Salir" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    TablaHash deposito(10);
    
    cout << "Cargando vehiculos en el deposito..." << endl;
    cargarVehiculosPredefinidos(deposito);

    
    int opcion;
    string placaBuscar;
    
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        switch(opcion) {
            case 1:
                cout << "\nIngrese la placa a buscar: ";
                getline(cin, placaBuscar);
                
                {
                    Vehiculo* encontrado = deposito.buscar(placaBuscar);
                    if (encontrado != nullptr) {
                        cout << "\n========================================" << endl;
                        cout << "  VEHICULO ENCONTRADO (Tabla Hash)" << endl;
                        cout << "========================================" << endl;
                        encontrado->mostrar();
                        cout << "========================================" << endl;
                    } else {
                        cout << "\nVehiculo con placa '" << placaBuscar << "' no encontrado en el deposito." << endl;
                    }
                }
                break;
                
            case 2:
                deposito.mostrarTodos();
                break;
                
            case 3:
                deposito.mostrarEstructuraHash();
                break;
                
            case 4:
                cout << "\nSaliendo del sistema..." << endl;
                break;
                
            default:
                cout << "\nOpcion invalida. Intente nuevamente..." << endl;
        }
        
        if (opcion != 4) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
        
    } while (opcion != 4);

    return 0;
}


