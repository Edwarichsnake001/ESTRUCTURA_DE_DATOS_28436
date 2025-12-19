#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

// 1. Arbol binario de decision  (Triage Médico)

struct NodoTriage {
    string pregunta;
    string resultado;
    NodoTriage* izq;
    NodoTriage* der;

    NodoTriage(string q = "", string r = "")
        : pregunta(q), resultado(r), izq(nullptr), der(nullptr) {}
};

void evaluar_triage(NodoTriage* nodo) {
    if (!nodo) return;

    if (nodo->resultado != "") {
        cout << "Diagnostico final: " << nodo->resultado << endl;
        return;
    }

    string resp;
    cout << nodo->pregunta << " (si/no): ";
    cin >> resp;

    if (resp == "si")
        evaluar_triage(nodo->izq);
    else
        evaluar_triage(nodo->der);
}

void ejecutar_triage() {
    NodoTriage* raiz = new NodoTriage("Tiene fiebre?");
    raiz->izq = new NodoTriage("Tiene dificultad para respirar?");
    raiz->der = new NodoTriage("Tiene dolor?");
    raiz->izq->izq = new NodoTriage("", "ATENCION DE URGENCIA");
    raiz->izq->der = new NodoTriage("Tiene presion arterial alta?");
    raiz->izq->der->izq = new NodoTriage("", "OBSERVACION INMEDIATA");
    raiz->izq->der->der = new NodoTriage("Tiene enfermedad cronica?");
    raiz->izq->der->der->izq = new NodoTriage("", "CONSULTA PRIORITARIA");
    raiz->izq->der->der->der = new NodoTriage("", "CONSULTA NORMAL");
    raiz->der->izq = new NodoTriage("Es un dolor fuerte?");
    raiz->der->der = new NodoTriage("Tiene nauseas o vomito?");
    raiz->der->izq->izq = new NodoTriage("", "DOLOR INTENSO: ATENCION URGENTE");
    raiz->der->izq->der = new NodoTriage("", "TRATAMIENTO DE MEDICACION");
    raiz->der->der->izq = new NodoTriage("", "MEDICACION Y OBSERVACION");
    raiz->der->der->der = new NodoTriage("", "ENVIAR A CASA");

    cout << "\n------------ Triage Medico (Arbol Binario de Decision) -----------------\n";
    evaluar_triage(raiz);
}

// 2. Arbol AVL 

// Estructura basica de un nodo AVL
struct Nodo {
    int dato;
    int altura;
    Nodo* izq;
    Nodo* der;

    // Constructor del nodo
    Nodo(int d) : dato(d), altura(1), izq(NULL), der(NULL) {}
};

// Funcion para obtener la altura de un nodo
int altura(Nodo* n) {
    return n ? n->altura : 0;
}

// Calcula el factor de equilibrio (altura izquierda - derecha)
int factorEquilibrio(Nodo* n) {
    return n ? altura(n->izq) - altura(n->der) : 0;
}

// Rotacion simple a la derecha (caso RR)
Nodo* rotacionDerecha(Nodo* y) {
    cout << "-> Rotacion Derecha (RR) sobre nodo: " << y->dato << endl;

    // x queda como nueva raiz del subarbol
    Nodo* x = y->izq;
    Nodo* T = x->der;

    // Se realiza el intercambio
    x->der = y;
    y->izq = T;

    // Se actualizan alturas
    y->altura = 1 + max(altura(y->izq), altura(y->der));
    x->altura = 1 + max(altura(x->izq), altura(x->der));

    return x;
}

// Rotacion simple a la izquierda (caso LL)
Nodo* rotacionIzquierda(Nodo* x) {
    cout << "-> Rotacion Izquierda (LL) sobre nodo: " << x->dato << endl;

    Nodo* y = x->der;
    Nodo* T = y->izq;

    y->izq = x;
    x->der = T;

    x->altura = 1 + max(altura(x->izq), altura(x->der));
    y->altura = 1 + max(altura(y->izq), altura(y->der));

    return y;
}

// Insercion en un arbol AVL
// Aqui se observa como se insertan los datos y se detectan los desbalances
Nodo* insertar(Nodo* nodo, int dato) {
    // Caso base: el nodo esta vacio
    if (!nodo) {
        cout << "Insertando: " << dato << endl;
        return new Nodo(dato);
    }

    // Insercion normal como en ABB
    if (dato < nodo->dato)
        nodo->izq = insertar(nodo->izq, dato);
    else if (dato > nodo->dato)
        nodo->der = insertar(nodo->der, dato);
    else
        return nodo; // No se permiten duplicados

    // Actualizamos altura del nodo padre
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    // Obtenemos el factor de equilibrio
    int fe = factorEquilibrio(nodo);

    cout << "\nNodo " << nodo->dato << " FE=" << fe << endl;

    // Caso RR -> rotacion derecha
    if (fe > 1 && dato < nodo->izq->dato) {
        cout << "-> Desbalance Detectado (RR)" << endl;
        return rotacionDerecha(nodo);
    }

    // Caso LL -> rotacion izquierda
    if (fe < -1 && dato > nodo->der->dato) {
        cout << "-> Desbalance Detectado (LL)" << endl;
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// Recorrido InOrden (para mostrar los datos ordenados)
void inOrden(Nodo* nodo) {
    if (!nodo) return;
    inOrden(nodo->izq);
    cout << nodo->dato << " ";
    inOrden(nodo->der);
}

void ejecutar_avl() {

    Nodo* raiz = NULL;

    cout << "\n------------ Arbol AVL (Balanceo Automatico) -----------------\n";
    cout << " Demostracion de Insercion y Rotacion (30, 20, 10)\n";

    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 10);  // Aqui ocurre la rotacion RR

    cout << "\nArbol final en InOrden: ";
    inOrden(raiz);

    cout << "\n\nArbol AVL balanceado correctamente." << endl;
}

// 3. Arbol B (Gestion tienda)

struct Producto {
    int id;
    string nombre;
    // Constructor por defecto
    Producto() : id(0), nombre("") {}
    // Constructor con parametros
    Producto(int unId, const string& unNombre) : id(unId), nombre(unNombre) {}
};

class NodoB {
public:
    bool esHoja;
    vector<Producto> claves;
    vector<NodoB*> hijos;
    int t; // Grado mínimo (t)

    // Constructor
    NodoB(int elGradoMinimo, bool esHojaNodo){
        t = elGradoMinimo;
        esHoja = esHojaNodo;
    }

    // Funcion para recorrer (mostrar) el arbol
    void recorrer(){
        for(size_t i = 0; i < claves.size(); i++){
            if(!esHoja && i < hijos.size() && hijos[i] != nullptr)
                hijos[i]->recorrer();

            cout << "[" << claves[i].id << " - " << claves[i].nombre << "] ";
        }

        if(!esHoja && claves.size() < hijos.size() && hijos[claves.size()] != nullptr)
            hijos[claves.size()]->recorrer();
    }

    // Funcion para buscar un producto por su id (clave)
    NodoB* buscarNodo(int claveBuscada){
        size_t i = 0;
        while(i < claves.size() && claveBuscada > claves[i].id) i++;

        if(i < claves.size() && claves[i].id == claveBuscada)
            return this;

        if(esHoja) return nullptr;

        if(i < hijos.size() && hijos[i] != nullptr)
            return hijos[i]->buscarNodo(claveBuscada);
        else
            return nullptr;
    }

    // Funcion para insertar una clave cuando el nodo no esta lleno
    void insertarNoLleno(const Producto& prod){
        int i = (int)claves.size() - 1;

        if(esHoja){
            // Inserta manteniendo el orden por id
            claves.insert(upper_bound(claves.begin(), claves.end(), prod,
                [](const Producto& a, const Producto& b){ return a.id < b.id; }) , prod);
        }
        else{
            while(i >= 0 && claves[i].id > prod.id) i--;

            int idx = i + 1;
            // Si el hijo donde se debe insertar esta lleno
            if(idx < (int)hijos.size() && hijos[idx]->claves.size() == 2*t - 1){
                dividirHijo(idx, hijos[idx]);
                // Despues de la division, la clave podria ir en el nuevo hijo
                if(claves[idx].id < prod.id) idx++;
            }
            if(idx < (int)hijos.size())
                hijos[idx]->insertarNoLleno(prod);
        }
    }

    // Funcion para dividir el hijo y en el indice i
    void dividirHijo(int i, NodoB *hijoLleno){
        NodoB* nuevoNodo = new NodoB(hijoLleno->t, hijoLleno->esHoja);

        // Copia las claves de la mitad superior
        for(int j = 0; j < t - 1; j++){
            nuevoNodo->claves.push_back(hijoLleno->claves[j + t]);
        }

        // Copia los hijos si no es hoja
        if(!hijoLleno->esHoja){
            for(int j = 0; j < t; j++){
                nuevoNodo->hijos.push_back(hijoLleno->hijos[j + t]);
            }
        }

        // Reduce el tamaño del hijo lleno
        hijoLleno->claves.resize(t - 1);
        if(!hijoLleno->esHoja) hijoLleno->hijos.resize(t);

        // Inserta el nuevoNodo como hijo
        hijos.insert(hijos.begin() + i + 1, nuevoNodo);

        // Sube la clave central al padre (este nodo)
        claves.insert(claves.begin() + i, hijoLleno->claves[t - 1]);
    }
};

class ArbolB {
public:
    NodoB *raiz;
    int t; // Grado mínimo (t)

    // Constructor
    ArbolB(int elGradoMinimo){
        raiz = nullptr;
        t = elGradoMinimo;
    }

    // Funcion principal para insertar un producto
    void insertar(const Producto& prod){
        if(raiz == nullptr){
            raiz = new NodoB(t, true);
            raiz->claves.push_back(prod);
        }
        else{
            // Si la raiz esta llena
            if(raiz->claves.size() == 2*t - 1){
                NodoB* nuevaRaiz = new NodoB(t, false);
                nuevaRaiz->hijos.push_back(raiz);
                nuevaRaiz->dividirHijo(0, raiz);

                int i = 0;
                // Determina en cual de los dos nuevos hijos insertar
                if(nuevaRaiz->claves.size() > 0 && nuevaRaiz->claves[0].id < prod.id)
                    i++;

                nuevaRaiz->hijos[i]->insertarNoLleno(prod);
                raiz = nuevaRaiz;
            }
            else{
                raiz->insertarNoLleno(prod);
            }
        }
    }

    // Muestra todo el arbol
    void mostrar(){
        if(raiz != nullptr)
            raiz->recorrer();
        cout << "\n";
    }

    // Busca un producto e imprime un mensaje
    void buscarProducto(int id){
        NodoB* resultado = (raiz == nullptr) ? nullptr : raiz->buscarNodo(id);

        if(resultado == nullptr)
            cout << " Producto NO encontrado.\n";
        else
            cout << " Producto encontrado en un nodo del arbol.\n";
    }
};

void ejecutarArbolB() {
    cout << "\n------------ Arbol B (Gestion de Inventario - Tienda) -----------------\n";
    cout << "Ingrese el grado minimo t (2 - 3): ";
    int grado;
    cin >> grado;
    if (grado < 2) grado = 2; // Asegura que t >= 2

    ArbolB arbolInventario(grado);

    int opcion;
    do {
        cout << "\n--- MENU ARBOL B (Inventario) ---\n";
        cout << "1. Insertar producto\n";
        cout << "2. Buscar producto por ID\n";
        cout << "3. Mostrar inventario (recorrido)\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione: ";
        cin >> opcion;

        if(opcion == 1){
            int id;
            string nombre;
            cout << "ID del producto: ";
            cin >> id;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Nombre del producto: ";
            getline(cin, nombre);
            arbolInventario.insertar(Producto(id, nombre));
            cout << "Producto insertado.\n";
            
        }
        else if(opcion == 2){
            int id;
            cout << "ID a buscar: ";
            cin >> id;
            arbolInventario.buscarProducto(id);
        }
        else if(opcion == 3){
            cout << "Inventario (clave - nombre):\n";
            arbolInventario.mostrar();
        }
        else if(opcion == 4){
            cout << "Regresando al menu principal...\n";
        }
        else {
            cout << "Opcion invalida.\n";
        }

    } while(opcion != 4);
}

// 4. Arbol B+ 

class NodoBPlus {
public:
    bool hoja;
    vector<int> claves;
    vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;

    NodoBPlus(bool esHoja) {
        hoja = esHoja;
        siguiente = nullptr;
    }
};

class ArbolBPlus {
private:
    int orden;
    NodoBPlus* raiz;

public:
    ArbolBPlus(int _orden) {
        orden = _orden;
        raiz = new NodoBPlus(true);
    }

    void insertar(int clave) {
        cout << "Insertando " << clave << endl;
        if (raiz->claves.size() == orden) {
            NodoBPlus* nuevaRaiz = new NodoBPlus(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirNodo(nuevaRaiz, 0);
            raiz = nuevaRaiz;
        }
        insertarInterno(raiz, clave);
    }

    void insertarInterno(NodoBPlus* nodo, int clave) {
        if (nodo->hoja) {
            nodo->claves.push_back(clave);
            sort(nodo->claves.begin(), nodo->claves.end());
        } else {
            int i = upper_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();
            if (nodo->hijos[i]->claves.size() == orden) {
                dividirNodo(nodo, i);
                if (clave > nodo->claves[i]) i++;
            }
            insertarInterno(nodo->hijos[i], clave);
        }
    }

    void dividirNodo(NodoBPlus* padre, int indice) {
        NodoBPlus* nodo = padre->hijos[indice];
        NodoBPlus* nuevo = new NodoBPlus(nodo->hoja);

        int mitad = orden / 2;

        nuevo->claves.assign(nodo->claves.begin() + mitad, nodo->claves.end());
        nodo->claves.resize(mitad);

        if (!nodo->hoja) {
            nuevo->hijos.assign(nodo->hijos.begin() + mitad + 1, nodo->hijos.end());
            nodo->hijos.resize(mitad + 1);
        } else {
            nuevo->siguiente = nodo->siguiente;
            nodo->siguiente = nuevo;
        }

        padre->claves.insert(padre->claves.begin() + indice, nuevo->claves[0]);
        padre->hijos.insert(padre->hijos.begin() + indice + 1, nuevo);
    }

    bool buscar(int clave) {
        NodoBPlus* nodo = raiz;
        cout << "Buscando " << clave << endl;

        while (!nodo->hoja) {
            cout << "Nodo interno: ";
            for (int c : nodo->claves) cout << c << " ";
            cout << endl;

            int i = upper_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();
            cout << "Bajando al hijo " << i << endl;
            nodo = nodo->hijos[i];
        }

        cout << "Llegando a hoja: ";
        for (int c : nodo->claves) cout << c << " ";
        cout << endl;

        bool encontrado = binary_search(nodo->claves.begin(), nodo->claves.end(), clave);
        return encontrado;
    }

    void imprimirHojas() {
        NodoBPlus* nodo = raiz;
        while (!nodo->hoja) nodo = nodo->hijos[0];

        cout << "Hojas del arbol (enlazadas):" << endl;
        while (nodo) {
            for (int c : nodo->claves) cout << c << " ";
            cout << " | ";
            nodo = nodo->siguiente;
        }
        cout << endl;
    }
};

void ejecutar_arbol_bplus() {
    cout << "\n------------ Arbol B+ (Indexacion en Bases de Datos) -----------------\n";
    cout << " Demostracion de Insercion y Busqueda (Orden M=4)\n";
    
    ArbolBPlus arbol(4);

    int datos[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(datos)/sizeof(datos[0]);

    for (int i = 0; i < n; i++) {
        arbol.insertar(datos[i]);
    }

    cout << "\n--- Resultado de la Busqueda ---\n";
    int claveBuscar = 12;
    if (arbol.buscar(claveBuscar))
        cout << "Clave encontrada" << endl;
    else
        cout << "Clave no encontrada" << endl;

    cout << "\n--- Recorrido Secuencial ---\n";
    arbol.imprimirHojas();
}


int main() {
    int opcion;

    do {
        cout << "\n\n******************************************************\n";
        cout << "*               MENU  ARBOLES       *\n";
        cout << "******************************************************\n";
        cout << " 1. Arbol Binario de Decision - Triage Medico\n";
        cout << " 2. Arbol AVL - Insercion y Balanceo\n";
        cout << " 3. Arbol B - Gestion de Inventario (Tienda)\n";
        cout << " 4. Arbol B+ - Indexacion en Bases de Datos\n";
        cout << " 5. Salir\n";
        cout << "------------------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutar_triage();
                break;

            case 2:
                ejecutar_avl();
                break;

            case 3:
                ejecutarArbolB();
                break;

            case 4:
                ejecutar_arbol_bplus();
                break;

            case 5:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << " Opcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 5);

    return 0;
}

