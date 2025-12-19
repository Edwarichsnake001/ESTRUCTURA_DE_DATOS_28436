#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

class Estudiante{
	private:
		int id;
		string nombre;
		string cedula;
	public:
		Estudiante(){
			id = 0;
			nombre = "";
			cedula = ""; 
		}
		
		Estudiante(int id_est, string nom, string ce){
			id = id_est;
			nombre = nom;
			cedula = ce; 
		}
		
		int getId() const{
			return id;
		}
		
		string getNombre() const{
			return nombre;
		}
		
		string getCedula() const{
			return cedula;
		}
		
		void mostrar(){
			cout << "==========================" << endl;
			cout << "Estudiante " << id << endl;
			cout << "Nombre: " << nombre << endl;
			cout << "Cedula: " << cedula << endl;
			cout << "==========================" << endl;
		}
		
};

struct Nodo {
    Estudiante dato;
    Nodo* izq;
    Nodo* der;

    Nodo(const Estudiante& x) : dato(x), izq(nullptr), der(nullptr) {}
};

// Insertar un estudiante en el árbol
Nodo* insertar(Nodo* raiz, const Estudiante& valor) {
    if (raiz == nullptr) {
        return new Nodo(valor);
    }
    if (valor.getId() < raiz->dato.getId())
        raiz->izq = insertar(raiz->izq, valor);
    else
        raiz->der = insertar(raiz->der, valor);

    return raiz;
}

// Recorrido Inorden (izq - raiz - der)
void inorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izq);
    cout << endl;
	raiz->dato.mostrar();
	cout << " ";
    inorden(raiz->der);
}

// Recorrido Preorden (raiz - izq - der)
void preorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    cout << endl;
	raiz->dato.mostrar();
	cout << " ";
    preorden(raiz->izq);
    preorden(raiz->der);
}

// Recorrido Postorden (izq - der - raiz)
void postorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << endl;
	raiz->dato.mostrar();
	cout << " ";
}

// Buscar
bool buscar(Nodo* raiz, const int id) {
    if (raiz == nullptr) return false;
    if (raiz->dato.getId() == id) {
    	cout << "==========================" << endl;
		cout << "Estudiante " << raiz->dato.getId() << endl;
		cout << "Nombre: " << raiz->dato.getNombre() << endl;
		cout << "Cedula: " << raiz->dato.getCedula() << endl;
		cout << "==========================" << endl; 
    	return true;
	}
    if (id < raiz->dato.getId())
        return buscar(raiz->izq, id);
    else
        return buscar(raiz->der, id);
    
}

void generarArchivo(const char* filename) {
    ofstream file(filename);

    file << "1 Marjorie 1752231207\n";
    file << "2 Gabriel 1758964825\n";
    file << "4 Sofia 1753341290\n";
    file << "7 Carlos 1759987123\n";
    file << "3 Valeria 1751123408\n";
    file << "12 Daniel 1756678902\n";
    file << "21 Lucia 1754527811\n";

    file.close();
}

bool cargarArchivo(const char* filename, Estudiante arr[], int &count, int maxSize) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    int id;
    string nombre, cedula;
    count = 0;

    while (file >> id >> nombre >> cedula && count < maxSize) {
        arr[count++] = Estudiante(id, nombre, cedula);
    }

    file.close();
    return count > 0;
}

int main() {
    const char* filename = "estudiantes.txt";
    const int MAX = 100;
    Estudiante lista[MAX];
    int count = 0;
    int opc, id;

    // Crear archivo
    ifstream test(filename);
    if (!test.is_open()) {
        cout << "Archivo no encontrado. Generando 'estudiantes.txt'..." << endl;
        generarArchivo(filename);
    }
    test.close();

    // Cargar
    if (!cargarArchivo(filename, lista, count, MAX)) {
        cout << "Error cargando estudiantes." << endl;
        return 1;
    }
    cout << "Se cargaron " << count << " estudiantes desde el archivo." << endl;
    
    // Insertar
    Nodo* raiz = nullptr;

    for (int i = 0; i < count; i++) {
        raiz = insertar(raiz, lista[i]);
    }
    
	do{
		
		cout << "MENU - ARBOL BINARIO" << endl;
		cout << "1. Mostrar In-Orden" << endl;
		cout << "2. Mostrar Pre-Orden" << endl;
		cout << "3. Mostrar Pos-Orden" << endl;
		cout << "4. Buscar Estudiante" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese la opcion que desee: ";
		cin >> opc;
		system("cls");
		switch(opc){
			case 1:{
			    cout << "\nInorden: ";
			    inorden(raiz);
			    system("pause");
			    system("cls");
				break;
			}
			case 2:{
				cout << "\n\nPreorden: ";
    			preorden(raiz);
    			system("pause");
			    system("cls");
				break;
			}
			case 3:{
				cout << "\n\nPostorden: ";
    			postorden(raiz);
    			system("pause");
			    system("cls");
				break;
			}
			case 4:{
				cout << "\nIngrese el Id del estudiante que desee buscar: ";
				cin >> id;
    			cout << (buscar(raiz, id) ? "Encontrado" : "No encontrado") << endl;
    			system("pause");
			    system("cls");
				break;
			}
			case 5:{
				cout << "Saliendo del sistema..." << endl;
				return 0;
				break;
			}
			default:{
				cout << "Opcion ingresada invalida!!! Intente nuevamente..." << endl;
				system("pause");
			    system("cls");
				break;
			}
				
		}
	}while(opc != 5);

    
}

