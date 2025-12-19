#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

struct Cancion{
    string album;
    string nombre;
    string artista;

    void imprimir() const {
        std::cout << "|" << std::setw(8) << std::left << album
                  << "|" << std::setw(20) << std::left << nombre
                  << "|" << std::setw(10) << std::right << std::fixed << std::setprecision(2) << artista << "|\n";
    } 
    
};

string toLower(const string& s) {
    string r = s;
    for (char& c : r) c = tolower(c);
    return r;
}

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

template <typename T>
int particion(vector<T> &arr, int low, int high){
    T pivote = arr[high];
    int i= low - 1;

    for(int j= low; j < high; j++){
        if(arr[j].nombre < pivote.nombre){
            i++;
            
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j]=temp;
        }
    }

    T temp2 = arr[i+1];
    arr[i+1]=arr[high];
    arr[high] = temp2;

    return i+1;
}

template <typename T>
void quickSort(vector<T> &arr, int low, int high){
    if( low < high){
        int ind = particion(arr, low, high);

        quickSort(arr, low, ind-1);
        quickSort(arr, ind +1 , high);
    }

}

template <typename T>
void mostrarVector(const std::vector<T>& arr) {
    cout << "+--------+--------------------+----------+\n";
    cout << "| Album | Nombre             | artista   |\n";
    cout << "+--------+--------------------+----------+\n";
    for (const auto& item : arr) {
        item.imprimir();
    }
    cout << "+--------+--------------------+----------+\n";
}

template<typename T, typename B>
int binario(const vector<T>& inventario, const B& valorbuscar){
    int inf = 0;
    int sup = inventario.size() - 1;
    while(inf <= sup){
        int med = inf + (sup - inf)/2;

        if(inventario[med].nombre==valorbuscar){
            return med;
        }

        if(inventario[med].nombre< valorbuscar){
            inf=med+1;

        }else{
            sup=med-1;
        }
    }
    return -1;
}

template<typename T>
void menu(vector<T> inventario){
    int opcion;
    cout<<"=== Cancionario ==="<<endl;
    cout<<"1. Lista de canciones"<<endl;
    cout<<"2. Busqueda por nombre"<<endl;
    cout<<"3. Salir"<<endl;
    cin>>opcion;
    cin.ignore();


    switch(opcion){
        case 1:{
            cout<<"----Lista de Canciones----"<<endl;
            mostrarVector(inventario);
            break;
        }
        case 2:{
              int num = inventario.size();
                string nombre;
                vector<T> inventarioOrdenado = inventario;
                
                quickSort(inventarioOrdenado, 0, num-1);
                
                cout << "Nombre de la cancion a buscar: ";
                getline(cin, nombre);
                
                int posicion = binario(inventarioOrdenado, nombre);
                if(posicion != -1) {
                    cout << "\n CANCION ENCONTRADA:\n";
                    cout << "+--------+-------------------------+---------------+\n";
                    cout << "| Album  | Nombre de la Canción    | Artista       |\n";
                    cout << "+--------+-------------------------+---------------+\n";
                    inventarioOrdenado[posicion].imprimir();
                    cout << "+--------+-------------------------+---------------+\n";
                    
                } else {
                    vector<T> similares = buscarSimilares(inventarioOrdenado, nombre);
                    if(similares.empty()){
                        cout<<"No hay canciones similares"<<endl;

                    }else{
                        cout << "\n No se encontro la cancion: \"" << nombre << "\"\n";
                    cout << "\n CANCIONES SIMILARES:\n";
                    mostrarVector(similares);
                    }
                    
                }
                break;
            }
        case 3:{
            break;

        }
    }


}


int main(){
    vector<Cancion> inventario = {
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
    menu(inventario);
    return 0;
}