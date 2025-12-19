#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm> 

using namespace std;

struct Cancion {
    string album;
    string nombre;
    string artista;

    // AVL requiere operador de comparación
    bool operator<(const Cancion& otra) const {
        return nombre < otra.nombre;
    }
    
    void imprimir() const {
        // Formato para mostrar en listas
        std::cout << "|" << std::setw(25) << std::left << album
                  << "|" << std::setw(35) << std::left << nombre
                  << "|" << std::setw(20) << std::right << artista << "|\n";
    }    
};

// --------------------------------------------------
// UTILITARIOS GENERALES
// --------------------------------------------------
string toLower(const string& s) {
    string r = s;
    for (char& c : r) c = tolower(c);
    return r;
}

template <typename T>
T mi_max(T a, T b) {
    return (a > b) ? a : b;
}

// --------------------------------------------------
// CLASE NODO
// --------------------------------------------------
template <typename T>
class Nodo {
public:
    T dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(T val) : dato(val), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

// --------------------------------------------------
// BÚSQUEDA SIMILAR (Linear Search)
// --------------------------------------------------
template<typename T>
vector<T> buscarSimilares(const vector<T>& inventario, const string& clave) {
    vector<T> resultado;
    string claveLow = toLower(clave);
    for (const auto& cancion : inventario) {
        string nombreLow = toLower(cancion.nombre);
        if (nombreLow.find(claveLow) != string::npos) {    
            resultado.push_back(cancion);
        }
    }
    return resultado;
}

// --------------------------------------------------
// CLASE AVLTREE
// --------------------------------------------------
template <typename T>
class AVLTree {
private:
    Nodo<T>* raiz;

    // Métodos utilitarios
    int altura(Nodo<T>* N) { return (N == nullptr) ? 0 : N->altura; }
    int factorEquilibrio(Nodo<T>* N) { return (N == nullptr) ? 0 : altura(N->izquierda) - altura(N->derecha); }
    
    // Rotaciones
    Nodo<T>* rotacionDerecha(Nodo<T>* y) {
        Nodo<T>* x = y->izquierda;
        Nodo<T>* T2 = x->derecha;
        x->derecha = y;
        y->izquierda = T2;
        y->altura = 1 + mi_max(altura(y->izquierda), altura(y->derecha));
        x->altura = 1 + mi_max(altura(x->izquierda), altura(x->derecha));
        return x;
    }
    
    Nodo<T>* rotacionIzquierda(Nodo<T>* x) {
        Nodo<T>* y = x->derecha;
        Nodo<T>* T2 = y->izquierda;
        y->izquierda = x;
        x->derecha = T2;
        x->altura = 1 + mi_max(altura(x->izquierda), altura(x->derecha));
        y->altura = 1 + mi_max(altura(y->izquierda), altura(y->derecha));
        return y;
    }

    // Operaciones principales
    Nodo<T>* insertarRecursivo(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) return new Nodo<T>(dato);

        if (dato < nodo->dato)
            nodo->izquierda = insertarRecursivo(nodo->izquierda, dato);
        else if (nodo->dato < dato)
            nodo->derecha = insertarRecursivo(nodo->derecha, dato);
        else return nodo; // Ignorar duplicados

        nodo->altura = 1 + mi_max(altura(nodo->izquierda), altura(nodo->derecha));

        int balance = factorEquilibrio(nodo);
        
        // Casos de Rotación (Mantener el balance) 
        if (balance > 1 && dato < nodo->izquierda->dato) return rotacionDerecha(nodo); // LL
        if (balance < -1 && nodo->derecha->dato < dato) return rotacionIzquierda(nodo); // RR
        if (balance > 1 && nodo->izquierda->dato < dato) { // LR
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && dato < nodo->derecha->dato) { // RL
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }
        return nodo;
    }
    
    Nodo<T>* buscarNodo(Nodo<T>* nodo, const string& claveBusqueda) {
        if (nodo == nullptr) return nullptr;
        
        string nombreNodoLow = toLower(nodo->dato.nombre);
        string claveLow = toLower(claveBusqueda);

        if (claveLow < nombreNodoLow) {
            return buscarNodo(nodo->izquierda, claveBusqueda);
        } else if (nombreNodoLow < claveLow) {
            return buscarNodo(nodo->derecha, claveBusqueda);
        } else {
            return nodo; // Encontrado
        }
    }

    // 💡 Recorrido Inorden (Para el menú opción 1)
    void inordenRecursivo(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izquierda);
            nodo->dato.imprimir();
            inordenRecursivo(nodo->derecha);
        }
    }

    // 🌳 Implementación de Estructura Visual
    void imprimirEstructuraRecursivo(Nodo<T>* nodo, const std::string& prefijo, bool esIzquierdo) {
        if (nodo != nullptr) {
            imprimirEstructuraRecursivo(nodo->derecha, prefijo + (esIzquierdo ? "│   " : "    "), false);

            std::cout << prefijo;
            std::cout << (esIzquierdo ? "└── " : "┌── ");
            
            // Muestra el Título y la Altura
            std::cout << nodo->dato.nombre << " (h=" << nodo->altura << ")\n";

            imprimirEstructuraRecursivo(nodo->izquierda, prefijo + (esIzquierdo ? "    " : "│   "), true);
        }
    }

public:
    AVLTree() : raiz(nullptr) {}
    void insertar(T dato) { this->raiz = insertarRecursivo(this->raiz, dato); }
    Nodo<T>* buscar(const string& tituloBusqueda) { return buscarNodo(this->raiz, tituloBusqueda); }
    
    void mostrarInventario() {
        cout << "+-------------------------+-----------------------------------+--------------------+\n";
        cout << "| Album                   | Nombre                            | Artista            |\n";
        cout << "+-------------------------+-----------------------------------+--------------------+\n";
        inordenRecursivo(this->raiz);
        cout << "+-------------------------+-----------------------------------+--------------------+\n";
    }

    void imprimirEstructura() {
        std::cout << "\n=== ESTRUCTURA VISUAL DEL ÁRBOL AVL ===\n";
        if (raiz == nullptr) {
            std::cout << "El árbol está vacío.\n";
        } else {
            // Llama a la función recursiva. 'false' indica que no es la rama izquierda del padre
            imprimirEstructuraRecursivo(raiz, "", false); 
        }
        std::cout << "=======================================\n";
    }
};

// --------------------------------------------------
// VISUALIZACIÓN DE VECTORES (Para resultados similares)
// --------------------------------------------------
template <typename T>
void mostrarVector(const std::vector<T> &arr)
{
    cout << "+--------+--------------------+----------+\n";
    cout << "| Album  | Nombre             | Artista  |\n";
    cout << "+--------+--------------------+----------+\n";
    for (const auto &item : arr)
    {
        item.imprimir();
    }
    cout << "+--------+--------------------+----------+\n";
}

// --------------------------------------------------
// LÓGICA DEL MENÚ Y MAIN
// --------------------------------------------------
template <typename T>
void menu(AVLTree<T> &miPlaylist, const vector<T> &inventarioOriginal)
{
    int opcion;
    do
    {
        cout << "\n=== Cancionario (Usando AVL) ===" << endl;
        cout << "1. Lista de canciones (Ordenada por AVL)" << endl;
        cout << "2. Busqueda por nombre (AVL y Similar)" << endl;
        cout << "3. Estructura del Árbol AVL" << endl; // Nueva opción
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            cout << "----Lista de Canciones (Inorden)----" << endl;
            miPlaylist.mostrarInventario();
            break;
        }
        case 2:
        {
            string nombre;
            cout << "Nombre de la cancion a buscar: ";
            getline(cin, nombre);

            // 1. Búsqueda exacta O(log n) en el AVL
            Nodo<T> *resultado = miPlaylist.buscar(nombre);

            if (resultado != nullptr)
            {
                cout << "\n CANCION ENCONTRADA (Búsqueda AVL Exacta):\n";
                cout << "+--------+--------------------+----------+\n";
                cout << "| Album  | Nombre             | Artista  |\n";
                cout << "+--------+--------------------+----------+\n";
                resultado->dato.imprimir();
                cout << "+--------+--------------------+----------+\n";
            }
            else
            {
                // 2. Búsqueda similar O(n) lineal, usando la lista original
                vector<T> similares = buscarSimilares(inventarioOriginal, nombre);

                cout << "\n No se encontró la cancion exacta: \"" << nombre << "\"\n";

                if (similares.empty())
                {
                    cout << "No hay canciones similares que contengan esa palabra." << endl;
                }
                else
                {
                    cout << "\n CANCIONES SIMILARES (Búsqueda por Subcadena):\n";
                    mostrarVector(similares);
                }
            }
            break;
        }
        case 3:
        {
            miPlaylist.imprimirEstructura(); // Muestra el árbol
            break;
        }
        case 4: // Salir es ahora 4
        {
            cout << "Saliendo del Cancionario. ¡Hasta pronto!" << endl;
            break;
        }
        default:
        {
            cout << "Opción no válida. Intente de nuevo." << endl;
        }
        }
    } while (opcion != 4); // Cambiado a 4
}

int main()
{
    
    AVLTree<Cancion> miPlaylist;

    // Lista original de canciones
    vector<Cancion> inventarioOriginal = {
        {"Thriller", "Billie Jean", "Michael Jackson"},
        {"Imagine", "Imagine", "John Lennon"},
        {"Hotel California", "Hotel California", "Eagles"},
        {"Led Zeppelin IV", "Stairway to Heaven", "Led Zeppelin"},
        {"A Night at the Opera", "Bohemian Rhapsody", "Queen"},
        {"Nevermind", "Smells Like Teen Spirit", "Nirvana"},
        {"Help!", "Yesterday", "The Beatles"},
        {"Appetite for Destruction", "Sweet Child O' Mine", "Guns N' Roses"},
        {"The Dark Side of the Moon", "Money", "Pink Floyd"},
        {"Rumours", "Go Your Own Way", "Fleetwood Mac"},
        {"Back in Black", "Back in Black", "AC/DC"},
        {"The Freewheelin'", "Blowin' in the Wind", "Bob Dylan"}
    };

    // Construir el AVL insertando cada canción (O(N log N) total)
    for (const auto &cancion : inventarioOriginal)
    {
        miPlaylist.insertar(cancion);
    }

    // Llamar al menú usando el AVL para búsqueda/ordenamiento
    menu(miPlaylist, inventarioOriginal);
    return 0;
}

//YA NO VAMOS CON DATOS QUEMADOS EN EL EXAMEN, NOS DA LAS GRÁFICAS Y NOS DICE QUE CAMBIEMOS LAS COSAS.
//EMPEZAR CON MIS PLANTILLAS LOCAS A 
///ESTRUCTURAR BIEN EL GRADO PARA PODER APLICARLO DENTRO DE LA PROGRAMACIÓN, SI LA RELACION CAMBIÓ, EL TIEMPO DE EJECUCIÓN TERMINA POR
//HORRIBLEMENTE INCREMETNAR EL TIEMPO DE EJECUCIÓN