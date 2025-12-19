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
};

template <typename T>
struct Nodo {
    T dato;
    Nodo* sig;
};

class Lista {
private:
    Nodo<Cancion>* inicio = NULL;

    string convertirMinusculas(const string& str){
        string resultado = str;
        transform(resultado.begin(), resultado.end(), resultado.begin(), 
                  [](unsigned char c){ return tolower(c); });
        return resultado;
    }

    bool cancionExiste(const string& nombre){
        Nodo<Cancion>* aux = inicio;
        string nombreBuscar = convertirMinusculas(nombre);
        while(aux != nullptr){
            if(convertirMinusculas(aux->dato.nombreCancion) == nombreBuscar){
                return true;
            }
            aux = aux->sig;
        }
        return false;
    }

    vector<Cancion> buscarCoincidencias(const string& busqueda){
        vector<Cancion> coincidencias;
        Nodo<Cancion>* aux = inicio;
        string busquedaMin = convertirMinusculas(busqueda);
        
        while(aux != nullptr){
            string nombreMin = convertirMinusculas(aux->dato.nombreCancion);
            if(nombreMin.find(busquedaMin) != string::npos){
                coincidencias.push_back(aux->dato);
            }
            aux = aux->sig;
        }
        
        return coincidencias;
    }

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

public:
    ~Lista(){
        while(inicio != nullptr){
            Nodo<Cancion>* temp = inicio;
            inicio = inicio->sig;
            delete temp;
        }
        cout << "\nMemoria liberada correctamente." << endl;
    }

    void agregarLista(){ 
        Nodo<Cancion>* nuevo = new(nothrow) Nodo<Cancion>();
        if(nuevo == nullptr){
            cout << "Error: No hay memoria disponible." << endl;
            return;
        }

        cout << "Ingrese el nombre de la cancion: ";
        getline(cin, nuevo->dato.nombreCancion);
        
        while(nuevo->dato.nombreCancion.empty() || 
            nuevo->dato.nombreCancion.find_first_not_of(' ') == string::npos){
            cout << "El nombre no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, nuevo->dato.nombreCancion);
        }
        
        if(cancionExiste(nuevo->dato.nombreCancion)){
            cout << "Error: Esta cancion ya existe en la playlist." << endl;
            delete nuevo;
            return;
        }

        cout << "Ingrese el genero de la cancion: ";
        getline(cin, nuevo->dato.generoCancion);
        
        while(nuevo->dato.generoCancion.empty() || 
            nuevo->dato.generoCancion.find_first_not_of(' ') == string::npos){
            cout << "El genero no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, nuevo->dato.generoCancion);
        }
        
        cout << "Ingrese el numero de reproducciones: ";
        while(!(cin >> nuevo->dato.numReproduccion)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un numero valido (mayor o igual a 0): ";
        }
        cin.ignore();
        
        nuevo->sig = nullptr;

        if(inicio == nullptr){
            inicio = nuevo;
        } else{
            Nodo<Cancion>* aux = inicio;
            while(aux->sig != nullptr){
                aux = aux->sig;
            }
            aux->sig = nuevo;
        }
        
        cout << "Cancion agregada exitosamente!" << endl;
    }

    void mostrarDatos(){
        if(inicio == nullptr){
            cout << "\nLa lista esta vacia. No hay canciones para mostrar." << endl;
            return;
        }

        Nodo<Cancion>* aux = inicio;
        int contador = 1;
        
        cout << "\n========== LISTA DE CANCIONES ==========\n" << endl;
        imprimirEncabezadoTabla();
        
        while(aux != nullptr){
            imprimirFilaTabla(contador, aux->dato);
            aux = aux->sig;
            contador++;
        }
        
        imprimirLineaTabla(80);
        cout << "Total de canciones: " << (contador - 1) << endl;
    }

    void buscarPorGenero(const string& genero){
        if(inicio == nullptr){
            cout << "\nLa lista esta vacia. No hay canciones para buscar." << endl;
            return;
        }

        Nodo<Cancion>* aux = inicio;
        string generoBuscar = convertirMinusculas(genero);
        vector<Cancion> cancionesEncontradas;

        while(aux != nullptr){
            if(convertirMinusculas(aux->dato.generoCancion) == generoBuscar){
                cancionesEncontradas.push_back(aux->dato);
            }
            aux = aux->sig;
        }

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

        // Preguntar si desea reproducir alguna canción
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
        if(inicio == nullptr){
            cout << "\nLa lista esta vacia. No hay generos para mostrar." << endl;
            return;
        }

        vector<string> generos;
        Nodo<Cancion>* aux = inicio;

        while(aux != nullptr){
            string generoMin = convertirMinusculas(aux->dato.generoCancion);
            bool existe = false;
            
            for(size_t i = 0; i < generos.size(); i++){
                if(convertirMinusculas(generos[i]) == generoMin){
                    existe = true;
                    break;
                }
            }
            
            if(!existe){
                generos.push_back(aux->dato.generoCancion);
            }
            
            aux = aux->sig;
        }

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
        if(inicio == nullptr){
            cout << "\nLa lista esta vacia. No hay canciones para reproducir." << endl;
            return;
        }
        
        Nodo<Cancion>* aux = inicio;
        bool encontrado = false;
        string nombreBuscar = convertirMinusculas(nombre);
        
        while(aux != nullptr){
            if(convertirMinusculas(aux->dato.nombreCancion) == nombreBuscar){
                aux->dato.numReproduccion++;
                cout << "\nReproduciendo: " << aux->dato.nombreCancion << endl;
                cout << "  Genero: " << aux->dato.generoCancion << endl;
                cout << "  Reproducciones totales: " << aux->dato.numReproduccion << endl;
                encontrado = true;
                break;
            }
            aux = aux->sig;
        }
        
        if(!encontrado){
            vector<Cancion> coincidencias = buscarCoincidencias(nombre);
            
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

    void ordenarPoNombre(){
        if(inicio == nullptr){
            cout << "\nNo hay canciones para ordenar. La lista esta vacia." << endl;
            return;
        }
        
        if(inicio->sig == nullptr){
            cout << "\nSolo hay una cancion. No es necesario ordenar." << endl;
            return;
        }
        
        bool intercambio;
        do{
            intercambio = false;
            Nodo<Cancion>* actual = inicio;
            while(actual->sig != nullptr){
                if(convertirMinusculas(actual->dato.nombreCancion) > 
                   convertirMinusculas(actual->sig->dato.nombreCancion)){
                    Cancion temp = actual->dato;
                    actual->dato = actual->sig->dato;
                    actual->sig->dato = temp;
                    intercambio = true;
                }
                actual = actual->sig;
            }
        }while(intercambio);

        cout << "\nLista ordenada por nombre exitosamente." << endl;
    }

    void ordenarPorReproducciones(){
        if(inicio == nullptr){
            cout << "\nNo hay canciones para ordenar. La lista esta vacia." << endl;
            return;
        }
        
        if(inicio->sig == nullptr){
            cout << "\nSolo hay una cancion. No es necesario ordenar." << endl;
            return;
        }
        
        bool intercambio;
        do{
            intercambio = false;
            Nodo<Cancion>* actual = inicio;
            while(actual->sig != nullptr){
                if(actual->dato.numReproduccion < actual->sig->dato.numReproduccion){
                    Cancion temp = actual->dato;
                    actual->dato = actual->sig->dato;
                    actual->sig->dato = temp;
                    intercambio = true;
                }
                actual = actual->sig;
            }
        }while(intercambio);

        cout << "\nLista ordenada por reproducciones (Mayor a Menor) exitosamente." << endl;
    }

    void guardarEnArchivo(){
        if(inicio == nullptr){
            cout << "\nNo hay canciones para guardar. La lista esta vacia." << endl;
            return;
        }
        
        ofstream archivo("playlist.txt");
        
        if(!archivo.is_open()){
            cout << "\nError: No se pudo abrir el archivo para guardar." << endl;
            cout << "Verifique los permisos de escritura." << endl;
            return;
        }
        
        Nodo<Cancion>* aux = inicio;
        int contador = 0;
        while(aux != nullptr){
            archivo << aux->dato.nombreCancion << endl;
            archivo << aux->dato.generoCancion << endl;
            archivo << aux->dato.numReproduccion << endl;
            aux = aux->sig;
            contador++;
        }
        
        archivo.close();
        cout << "\nPlaylist guardada exitosamente (" << contador << " canciones)." << endl;
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
                    Nodo<Cancion>* nuevo = new(nothrow) Nodo<Cancion>();
                    if(nuevo == nullptr){
                        cout << "\nError: Memoria insuficiente al cargar canciones." << endl;
                        break;
                    }
                    
                    nuevo->dato.nombreCancion = nombre;
                    nuevo->dato.generoCancion = genero;
                    nuevo->dato.numReproduccion = reproducciones;
                    nuevo->sig = nullptr;
                    
                    if(inicio == nullptr){
                        inicio = nuevo;
                    } else{
                        Nodo<Cancion>* aux = inicio;
                        while(aux->sig != nullptr){
                            aux = aux->sig;
                        }
                        aux->sig = nuevo;
                    }
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
        return inicio == nullptr;
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
        cout << "6. Ordenar por nombre\n";
        cout << "7. Ordenar por reproducciones\n";
        cout << "8. Guardar y salir\n";
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
                playlist.ordenarPoNombre();
                if(!playlist.estaVacia()){
                    playlist.guardarEnArchivo();
                }
                break;
                
            case 7:
                playlist.ordenarPorReproducciones();
                if(!playlist.estaVacia()){
                    playlist.guardarEnArchivo();
                }
                break;
                
            case 8:
                playlist.guardarEnArchivo();
                cout << "\nGracias por usar el sistema. Hasta pronto!" << endl;
                break;
                
            default:
                cout << "\nOpcion invalida." << endl;
        }
        
    } while(opcion != 8);
    
    return 0;
}