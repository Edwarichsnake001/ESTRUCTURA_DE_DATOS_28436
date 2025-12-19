#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iomanip>

using namespace std;

typedef unsigned int Reproduccion;
typedef std::string Nombre;
typedef std::string Genero;

struct Cancion{
    Nombre nombreCancion;
    Genero generoCancion;
    Reproduccion numReproduccion;
    
    Cancion() : nombreCancion(""), generoCancion(""), numReproduccion(0) {}
    Cancion(const Nombre& n, const Genero& g, Reproduccion r) 
        : nombreCancion(n), generoCancion(g), numReproduccion(r) {}
};

string convertirMinusculas(const string& str){
    string resultado = str;
    transform(resultado.begin(), resultado.end(), resultado.begin(), 
                [](unsigned char c){ return tolower(c); });
    return resultado;
}

// Nodo del Árbol B
class NodoB {
public:
    vector<Cancion> canciones;      // Canciones en el nodo
    vector<NodoB*> hijos;           // Punteros a hijos
    bool esHoja;                    // ¿Es hoja?
    int t;                          // Grado mínimo
    
    NodoB(int grado, bool hoja);
    
    void insertarNoLleno(const Cancion& cancion);
    void dividirHijo(int i, NodoB* hijo);
    NodoB* buscar(const string& nombre);
    void recorrerInorden(vector<Cancion>& lista);
    void buscarCoincidencias(const string& busqueda, vector<Cancion>& resultados);
    void buscarPorGenero(const string& genero, vector<Cancion>& resultados);
    void obtenerGeneros(vector<string>& generos);
    
    friend class ArbolB;
};

NodoB::NodoB(int grado, bool hoja) {
    t = grado;
    esHoja = hoja;
}

// Clase Árbol B
class ArbolB {
private:
    NodoB* raiz;
    int t;  // Grado mínimo
    
public:
    ArbolB(int grado) {
        raiz = nullptr;
        t = grado;
    }
    
    ~ArbolB() {
        destruirArbol(raiz);
    }
    
    void destruirArbol(NodoB* nodo) {
        if (nodo != nullptr) {
            if (!nodo->esHoja) {
                for (size_t i = 0; i < nodo->hijos.size(); i++) {
                    destruirArbol(nodo->hijos[i]);
                }
            }
            delete nodo;
        }
    }
    
    NodoB* buscar(const string& nombre) {
        return (raiz == nullptr) ? nullptr : raiz->buscar(nombre);
    }
    
    void insertar(const Cancion& cancion);
    void recorrerInorden(vector<Cancion>& lista);
    void buscarCoincidencias(const string& busqueda, vector<Cancion>& resultados);
    void buscarPorGenero(const string& genero, vector<Cancion>& resultados);
    void obtenerGeneros(vector<string>& generos);
    bool estaVacio() { return raiz == nullptr; }
    
    Cancion* buscarCancion(const string& nombre);
};

void NodoB::insertarNoLleno(const Cancion& cancion) {
    int i = canciones.size() - 1;
    
    if (esHoja) {
        canciones.push_back(Cancion());
        string nombreNuevo = convertirMinusculas(cancion.nombreCancion);
        
        while (i >= 0 && convertirMinusculas(canciones[i].nombreCancion) > nombreNuevo) {
            canciones[i + 1] = canciones[i];
            i--;
        }
        canciones[i + 1] = cancion;
    } else {
        string nombreNuevo = convertirMinusculas(cancion.nombreCancion);
        while (i >= 0 && convertirMinusculas(canciones[i].nombreCancion) > nombreNuevo) {
            i--;
        }
        i++;
        
        if (hijos[i]->canciones.size() == 2 * t - 1) {
            dividirHijo(i, hijos[i]);
            if (convertirMinusculas(canciones[i].nombreCancion) < nombreNuevo) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(cancion);
    }
}

void NodoB::dividirHijo(int i, NodoB* hijo) {
    NodoB* nuevoNodo = new NodoB(hijo->t, hijo->esHoja);
    
    for (int j = 0; j < t - 1; j++) {
        nuevoNodo->canciones.push_back(hijo->canciones[j + t]);
    }
    
    if (!hijo->esHoja) {
        for (int j = 0; j < t; j++) {
            nuevoNodo->hijos.push_back(hijo->hijos[j + t]);
        }
    }
    
    Cancion mediana = hijo->canciones[t - 1];
    
    hijo->canciones.resize(t - 1);
    if (!hijo->esHoja) {
        hijo->hijos.resize(t);
    }
    
    hijos.insert(hijos.begin() + i + 1, nuevoNodo);
    canciones.insert(canciones.begin() + i, mediana);
}

NodoB* NodoB::buscar(const string& nombre) {
    string nombreBuscar = convertirMinusculas(nombre);
    size_t i = 0;
    
    while (i < canciones.size() && nombreBuscar > convertirMinusculas(canciones[i].nombreCancion)) {
        i++;
    }
    
    if (i < canciones.size() && convertirMinusculas(canciones[i].nombreCancion) == nombreBuscar) {
        return this;
    }
    
    if (esHoja) {
        return nullptr;
    }
    
    return hijos[i]->buscar(nombre);
}

void NodoB::recorrerInorden(vector<Cancion>& lista) {
    size_t i;
    for (i = 0; i < canciones.size(); i++) {
        if (!esHoja) {
            hijos[i]->recorrerInorden(lista);
        }
        lista.push_back(canciones[i]);
    }
    
    if (!esHoja) {
        hijos[i]->recorrerInorden(lista);
    }
}

void NodoB::buscarCoincidencias(const string& busqueda, vector<Cancion>& resultados) {
    string busquedaMin = convertirMinusculas(busqueda);
    
    for (size_t i = 0; i < canciones.size(); i++) {
        if (!esHoja && i < hijos.size()) {
            hijos[i]->buscarCoincidencias(busqueda, resultados);
        }
        
        string nombreMin = convertirMinusculas(canciones[i].nombreCancion);
        if (nombreMin.find(busquedaMin) != string::npos) {
            resultados.push_back(canciones[i]);
        }
    }
    
    if (!esHoja && canciones.size() < hijos.size()) {
        hijos[canciones.size()]->buscarCoincidencias(busqueda, resultados);
    }
}

void NodoB::buscarPorGenero(const string& genero, vector<Cancion>& resultados) {
    string generoMin = convertirMinusculas(genero);
    
    for (size_t i = 0; i < canciones.size(); i++) {
        if (!esHoja && i < hijos.size()) {
            hijos[i]->buscarPorGenero(genero, resultados);
        }
        
        if (convertirMinusculas(canciones[i].generoCancion) == generoMin) {
            resultados.push_back(canciones[i]);
        }
    }
    
    if (!esHoja && canciones.size() < hijos.size()) {
        hijos[canciones.size()]->buscarPorGenero(genero, resultados);
    }
}

void NodoB::obtenerGeneros(vector<string>& generos) {
    for (size_t i = 0; i < canciones.size(); i++) {
        if (!esHoja && i < hijos.size()) {
            hijos[i]->obtenerGeneros(generos);
        }
        
        string generoMin = convertirMinusculas(canciones[i].generoCancion);
        bool existe = false;
        
        for (size_t j = 0; j < generos.size(); j++) {
            if (convertirMinusculas(generos[j]) == generoMin) {
                existe = true;
                break;
            }
        }
        
        if (!existe) {
            generos.push_back(canciones[i].generoCancion);
        }
    }
    
    if (!esHoja && canciones.size() < hijos.size()) {
        hijos[canciones.size()]->obtenerGeneros(generos);
    }
}

void ArbolB::insertar(const Cancion& cancion) {
    if (raiz == nullptr) {
        raiz = new NodoB(t, true);
        raiz->canciones.push_back(cancion);
    } else {
        if (raiz->canciones.size() == 2 * t - 1) {
            NodoB* nuevaRaiz = new NodoB(t, false);
            nuevaRaiz->hijos.push_back(raiz);
            nuevaRaiz->dividirHijo(0, raiz);
            
            int i = 0;
            if (convertirMinusculas(nuevaRaiz->canciones[0].nombreCancion) < 
                convertirMinusculas(cancion.nombreCancion)) {
                i++;
            }
            nuevaRaiz->hijos[i]->insertarNoLleno(cancion);
            
            raiz = nuevaRaiz;
        } else {
            raiz->insertarNoLleno(cancion);
        }
    }
}

void ArbolB::recorrerInorden(vector<Cancion>& lista) {
    if (raiz != nullptr) {
        raiz->recorrerInorden(lista);
    }
}

void ArbolB::buscarCoincidencias(const string& busqueda, vector<Cancion>& resultados) {
    if (raiz != nullptr) {
        raiz->buscarCoincidencias(busqueda, resultados);
    }
}

void ArbolB::buscarPorGenero(const string& genero, vector<Cancion>& resultados) {
    if (raiz != nullptr) {
        raiz->buscarPorGenero(genero, resultados);
    }
}

void ArbolB::obtenerGeneros(vector<string>& generos) {
    if (raiz != nullptr) {
        raiz->obtenerGeneros(generos);
    }
}

Cancion* ArbolB::buscarCancion(const string& nombre) {
    NodoB* nodo = buscar(nombre);
    if (nodo == nullptr) return nullptr;
    
    string nombreBuscar = convertirMinusculas(nombre);
    for (size_t i = 0; i < nodo->canciones.size(); i++) {
        if (convertirMinusculas(nodo->canciones[i].nombreCancion) == nombreBuscar) {
            return &(nodo->canciones[i]);
        }
    }
    return nullptr;
}

// Clase Lista para gestionar la playlist
class Lista {
private:
    ArbolB* arbol;
    
    void imprimirLineaTabla(int ancho){
        cout << "+";
        for(int i = 0; i < ancho; i++){
            cout << "-";
        }
        cout << "+" << endl;
    }

    void imprimirEncabezadoTabla(){
        int anchoTotal = 80;
        imprimirLineaTabla(anchoTotal);
        cout << "| " << left << setw(4) << "#" 
            << "| " << setw(30) << "NOMBRE" 
            << "| " << setw(20) << "GENERO" 
            << "| " << setw(17) << "REPRODUCCIONES" << "|" << endl;
        imprimirLineaTabla(anchoTotal);
    }

    void imprimirFilaTabla(int numero, const Cancion& cancion){
        cout << "| " << left << setw(4) << numero
            << "| " << setw(30) << (cancion.nombreCancion.length() > 30 ? 
                cancion.nombreCancion.substr(0, 27) + "..." : cancion.nombreCancion)
            << "| " << setw(20) << (cancion.generoCancion.length() > 20 ? 
                cancion.generoCancion.substr(0, 17) + "..." : cancion.generoCancion)
            << "| " << setw(17) << cancion.numReproduccion << "|" << endl;
    }

    bool cancionExiste(const string& nombre){
        return arbol->buscarCancion(nombre) != nullptr;
    }

public:
    Lista() {
        arbol = new ArbolB(3);  // Grado mínimo t=3
    }
    
    ~Lista(){
        delete arbol;
        cout << "\nMemoria liberada correctamente." << endl;
    }

    void agregarLista(){ 
        Cancion nueva;

        cout << "Ingrese el nombre de la cancion: ";
        getline(cin, nueva.nombreCancion);
        
        while(nueva.nombreCancion.empty() || 
            nueva.nombreCancion.find_first_not_of(' ') == string::npos){
            cout << "El nombre no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, nueva.nombreCancion);
        }
        
        if(cancionExiste(nueva.nombreCancion)){
            cout << "Error: Esta cancion ya existe en la playlist." << endl;
            return;
        }

        cout << "Ingrese el genero de la cancion: ";
        getline(cin, nueva.generoCancion);
        
        while(nueva.generoCancion.empty() || 
            nueva.generoCancion.find_first_not_of(' ') == string::npos){
            cout << "El genero no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, nueva.generoCancion);
        }
        
        cout << "Ingrese el numero de reproducciones: ";
        while(!(cin >> nueva.numReproduccion)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un numero valido (mayor o igual a 0): ";
        }
        cin.ignore();
        
        arbol->insertar(nueva);
        cout << "Cancion agregada exitosamente!" << endl;
    }

    void mostrarDatos(){
        if(arbol->estaVacio()){
            cout << "\nLa lista esta vacia. No hay canciones para mostrar." << endl;
            return;
        }

        vector<Cancion> lista;
        arbol->recorrerInorden(lista);
        
        cout << "\n========== LISTA DE CANCIONES (Ordenadas por Nombre) ==========\n" << endl;
        imprimirEncabezadoTabla();
        
        for(size_t i = 0; i < lista.size(); i++){
            imprimirFilaTabla(i + 1, lista[i]);
        }
        
        imprimirLineaTabla(80);
        cout << "Total de canciones: " << lista.size() << endl;
    }

    void buscarPorGenero(const string& genero){
        if(arbol->estaVacio()){
            cout << "\nLa lista esta vacia. No hay canciones para buscar." << endl;
            return;
        }

        vector<Cancion> cancionesEncontradas;
        arbol->buscarPorGenero(genero, cancionesEncontradas);

        if(cancionesEncontradas.empty()){
            cout << "\nNo se encontraron canciones del genero \"" << genero << "\"" << endl;
            return;
        }

        cout << "\n========== CANCIONES DEL GENERO: " << genero << " ==========\n" << endl;
        imprimirEncabezadoTabla();
        
        for(size_t i = 0; i < cancionesEncontradas.size(); i++){
            imprimirFilaTabla(i + 1, cancionesEncontradas[i]);
        }
        
        imprimirLineaTabla(80);
        cout << "Total de canciones encontradas: " << cancionesEncontradas.size() << endl;

        cout << "\n¿Desea reproducir alguna cancion? (s/n): ";
        char respuesta;
        cin >> respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(respuesta == 's' || respuesta == 'S'){
            cout << "Ingrese el numero de la cancion a reproducir (0 para cancelar): ";
            int seleccion;
            
            while(true){
                if(cin >> seleccion){
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if(seleccion == 0){
                        cout << "\nReproduccion cancelada." << endl;
                        return;
                    }
                    
                    if(seleccion > 0 && seleccion <= (int)cancionesEncontradas.size()){
                        reproducirCancion(cancionesEncontradas[seleccion - 1].nombreCancion);
                        return;
                    } else {
                        cout << "Opcion invalida. Ingrese un numero entre 0 y " 
                            << cancionesEncontradas.size() << ": ";
                    }
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Ingrese un numero valido: ";
                }
            }
        }
    }

    void mostrarGenerosDisponibles(){
        if(arbol->estaVacio()){
            cout << "\nLa lista esta vacia. No hay generos para mostrar." << endl;
            return;
        }

        vector<string> generos;
        arbol->obtenerGeneros(generos);

        cout << "\n========== GENEROS DISPONIBLES ==========\n" << endl;
        int anchoTabla = 40;
        cout << "+" << string(anchoTabla, '-') << "+" << endl;
        cout << "| " << left << setw(4) << "#" << "| " << setw(32) << "GENERO" << "|" << endl;
        cout << "+" << string(anchoTabla, '-') << "+" << endl;
        
        for(size_t i = 0; i < generos.size(); i++){
            cout << "| " << left << setw(4) << (i + 1) 
                << "| " << setw(32) << (generos[i].length() > 32 ? 
                    generos[i].substr(0, 29) + "..." : generos[i]) << "|" << endl;
        }
        
        cout << "+" << string(anchoTabla, '-') << "+" << endl;
        cout << "Total de generos: " << generos.size() << endl;
    }

    void reproducirCancion(const string& nombre){
        if(arbol->estaVacio()){
            cout << "\nLa lista esta vacia. No hay canciones para reproducir." << endl;
            return;
        }
        
        Cancion* cancion = arbol->buscarCancion(nombre);
        
        if(cancion != nullptr){
            cancion->numReproduccion++;
            cout << "\n Reproduciendo: " << cancion->nombreCancion << endl;
            cout << "  Genero: " << cancion->generoCancion << endl;
            cout << "  Reproducciones totales: " << cancion->numReproduccion << endl;
        } else {
            vector<Cancion> coincidencias;
            arbol->buscarCoincidencias(nombre, coincidencias);
            
            if(coincidencias.empty()){
                cout << "\nNo se encontraron canciones que coincidan con: \"" << nombre << "\"" << endl;
            } else {
                cout << "\nNo se encontro una coincidencia exacta." << endl;
                cout << "Se encontraron " << coincidencias.size() << " coincidencia(s) parcial(es):\n" << endl;
                
                imprimirEncabezadoTabla();
                for(size_t i = 0; i < coincidencias.size(); i++){
                    imprimirFilaTabla(i + 1, coincidencias[i]);
                }
                imprimirLineaTabla(80);
                
                cout << "\n0. Cancelar" << endl;
                cout << "\nSeleccione el numero de la cancion a reproducir: ";
                
                int seleccion;
                while(true){
                    if(cin >> seleccion){
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if(seleccion == 0){
                            cout << "\nReproduccion cancelada." << endl;
                            return;
                        }
                        
                        if(seleccion > 0 && seleccion <= (int)coincidencias.size()){
                            reproducirCancion(coincidencias[seleccion - 1].nombreCancion);
                            return;
                        } else {
                            cout << "Opcion invalida. Ingrese un numero entre 0 y " 
                                << coincidencias.size() << ": ";
                        }
                    } else {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Error: Ingrese un numero valido: ";
                    }
                }
            }
        }
    }

    void ordenarPorReproducciones(){
        if(arbol->estaVacio()){
            cout << "\nNo hay canciones para mostrar. La lista esta vacia." << endl;
            return;
        }
        
        vector<Cancion> lista;
        arbol->recorrerInorden(lista);
        
        // Ordenar por reproducciones (mayor a menor)
        for(size_t i = 0; i < lista.size() - 1; i++){
            for(size_t j = 0; j < lista.size() - i - 1; j++){
                if(lista[j].numReproduccion < lista[j + 1].numReproduccion){
                    Cancion temp = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = temp;
                }
            }
        }
        
        cout << "\n========== CANCIONES ORDENADAS POR REPRODUCCIONES ==========\n" << endl;
        imprimirEncabezadoTabla();
        
        for(size_t i = 0; i < lista.size(); i++){
            imprimirFilaTabla(i + 1, lista[i]);
        }
        
        imprimirLineaTabla(80);
        cout << "Total de canciones: " << lista.size() << endl;
    }

    void guardarEnArchivo(){
        if(arbol->estaVacio()){
            cout << "\nNo hay canciones para guardar. La lista esta vacia." << endl;
            return;
        }
        
        ofstream archivo("playlist.txt");
        
        if(!archivo.is_open()){
            cout << "\nError: No se pudo abrir el archivo para guardar." << endl;
            cout << "Verifique los permisos de escritura." << endl;
            return;
        }
        
        vector<Cancion> lista;
        arbol->recorrerInorden(lista);
        
        for(size_t i = 0; i < lista.size(); i++){
            archivo << lista[i].nombreCancion << endl;
            archivo << lista[i].generoCancion << endl;
            archivo << lista[i].numReproduccion << endl;
        }
        
        archivo.close();
        cout << "\nPlaylist guardada exitosamente (" << lista.size() << " canciones)." << endl;
    }

    void cargarDesdeArchivo(){
        ifstream archivo("playlist.txt");
        
        if(!archivo.is_open()){
            cout << "\nNo se encontro archivo previo. Iniciando con playlist vacia." << endl;
            return;
        }
        
        string nombre, genero;
        Reproduccion reproducciones;
        int contador = 0;
        
        while(getline(archivo, nombre)){
            if(getline(archivo, genero) && archivo >> reproducciones){
                archivo.ignore();
                
                if(!nombre.empty() && nombre.find_first_not_of(' ') != string::npos &&
                    !genero.empty() && genero.find_first_not_of(' ') != string::npos){
                    Cancion nueva(nombre, genero, reproducciones);
                    arbol->insertar(nueva);
                    contador++;
                }
            }
        }
        
        archivo.close();
        if(contador > 0){
            cout << "\nPlaylist cargada exitosamente (" << contador << " canciones)." << endl;
        }
    }

    bool estaVacia(){
        return arbol->estaVacio();
    }
};

int leerOpcion(){
    int opcion;
    while(true){
        if(cin >> opcion){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nError: Ingrese un numero valido: ";
        }
    }
}

string leerString(const string& mensaje){
    string texto;
    cout << mensaje;
    getline(cin, texto);
    
    while(texto.empty() || texto.find_first_not_of(' ') == string::npos){
        cout << "El texto no puede estar vacio. Intente nuevamente: ";
        getline(cin, texto);
    }
    
    return texto;
}

int main(){
    Lista playlist;
    
    cout << "========================================" << endl;
    cout << "   SISTEMA DE GESTION DE PLAYLIST" << endl;
    cout << "      (Implementado con Arbol B)" << endl;
    cout << "========================================" << endl;
    
    playlist.cargarDesdeArchivo();
    
    int opcion;
    string nombreCancion, genero;

    do{
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar todas las canciones\n";
        cout << "3. Reproducir cancion\n";
        cout << "4. Buscar canciones por genero\n";
        cout << "5. Mostrar generos disponibles\n";
        cout << "6. Ordenar por reproducciones\n";
        cout << "7. Guardar y salir\n";
        cout << "====================================\n";
        cout << "Seleccione una opcion: ";
        
        opcion = leerOpcion();
        
        switch(opcion){
            case 1:
                playlist.agregarLista();
                playlist.guardarEnArchivo();
                break;
                
            case 2:
                playlist.mostrarDatos();
                break;
                
            case 3:
                if(playlist.estaVacia()){
                    cout << "\nLa lista esta vacia. Agregue canciones primero." << endl;
                } else {
                    nombreCancion = leerString("Ingrese el nombre de la cancion a reproducir: ");
                    playlist.reproducirCancion(nombreCancion);
                    playlist.guardarEnArchivo();
                }
                break;
                
            case 4:
                if(playlist.estaVacia()){
                    cout << "\nLa lista esta vacia. Agregue canciones primero." << endl;
                } else {
                    genero = leerString("Ingrese el genero a buscar: ");
                    playlist.buscarPorGenero(genero);
                    playlist.guardarEnArchivo();
                }
                break;
                
            case 5:
                playlist.mostrarGenerosDisponibles();
                break;
                
            case 6:
                playlist.ordenarPorReproducciones();
                break;
                
            case 7:
                playlist.guardarEnArchivo();
                cout << "\nGracias por usar el sistema. Hasta pronto!" << endl;
                break;
                
            default:
                cout << "\nOpcion invalida." << endl;
        }
        
    } while(opcion != 7);
    
    return 0;
}