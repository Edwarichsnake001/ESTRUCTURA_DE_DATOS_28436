#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

// Estructuras de datos (Medidor y NodoBPlus se mantienen igual)
struct Medidor {
    int id;
    string direccion;
    int posteConectado;
};

struct NodoBPlus {
    bool esHoja;
    vector<int> llaves;
    vector<Medidor> datos;
    vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;
    NodoBPlus(bool hoja) : esHoja(hoja), siguiente(nullptr) {}
};

// Clase ArbolBPlus (Las funciones internas se mantienen igual)
class ArbolBPlus {
    NodoBPlus* raiz;
    int orden;
public:
    ArbolBPlus(int m) : raiz(nullptr), orden(m) {}

    Medidor* buscar(int id) {
        if (!raiz) return nullptr;
        NodoBPlus* temp = raiz;
        while (!temp->esHoja) {
            int i = upper_bound(temp->llaves.begin(), temp->llaves.end(), id) - temp->llaves.begin();
            temp = temp->hijos[i];
        }
        for (auto& m : temp->datos) {
            if (m.id == id) return &m;
        }
        return nullptr;
    }

    void dividirHijo(NodoBPlus* padre, int i, NodoBPlus* lleno) {
        NodoBPlus* nuevo = new NodoBPlus(lleno->esHoja);
        int t = orden / 2;
        if (lleno->esHoja) {
            for (int j = t; j < lleno->llaves.size(); j++) {
                nuevo->llaves.push_back(lleno->llaves[j]);
                nuevo->datos.push_back(lleno->datos[j]);
            }
            lleno->llaves.erase(lleno->llaves.begin() + t, lleno->llaves.end());
            lleno->datos.erase(lleno->datos.begin() + t, lleno->datos.end());
            nuevo->siguiente = lleno->siguiente;
            lleno->siguiente = nuevo;
            padre->llaves.insert(padre->llaves.begin() + i, nuevo->llaves[0]);
        } else {
            int midKey = lleno->llaves[t];
            for (int j = t + 1; j < lleno->llaves.size(); j++) nuevo->llaves.push_back(lleno->llaves[j]);
            for (int j = t + 1; j < lleno->hijos.size(); j++) nuevo->hijos.push_back(lleno->hijos[j]);
            lleno->llaves.erase(lleno->llaves.begin() + t, lleno->llaves.end());
            lleno->hijos.erase(lleno->hijos.begin() + t + 1, lleno->hijos.end());
            padre->llaves.insert(padre->llaves.begin() + i, midKey);
        }
        padre->hijos.insert(padre->hijos.begin() + i + 1, nuevo);
    }

    void insertar(Medidor m) {
        if (!raiz) {
            raiz = new NodoBPlus(true);
            raiz->llaves.push_back(m.id);
            raiz->datos.push_back(m);
            return;
        }
        if (raiz->llaves.size() >= orden) {
            NodoBPlus* nuevaRaiz = new NodoBPlus(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirHijo(nuevaRaiz, 0, raiz);
            raiz = nuevaRaiz;
        }
        insertarNoLleno(raiz, m);
    }

    void insertarNoLleno(NodoBPlus* nodo, Medidor m) {
        int i = nodo->llaves.size() - 1;
        if (nodo->esHoja) {
            nodo->llaves.push_back(0);
            nodo->datos.push_back(m);
            while (i >= 0 && m.id < nodo->llaves[i]) {
                nodo->llaves[i+1] = nodo->llaves[i];
                nodo->datos[i+1] = nodo->datos[i];
                i--;
            }
            nodo->llaves[i+1] = m.id;
            nodo->datos[i+1] = m;
        } else {
            while (i >= 0 && m.id < nodo->llaves[i]) i--;
            i++;
            if (nodo->hijos[i]->llaves.size() >= orden) {
                dividirHijo(nodo, i, nodo->hijos[i]);
                if (m.id > nodo->llaves[i]) i++;
            }
            insertarNoLleno(nodo->hijos[i], m);
        }
    }

    void mostrarEstructura(NodoBPlus* nodo, int nivel) {
        if (nodo != nullptr) {
            cout << string(nivel * 8, ' ') << "|-- [ ";
            for (int k : nodo->llaves) cout << k << " ";
            cout << "]" << (nodo->esHoja ? " (Hoja)" : "") << endl;
            if (!nodo->esHoja) {
                for (auto hijo : nodo->hijos) {
                    mostrarEstructura(hijo, nivel + 1);
                }
            }
        }
    }

    NodoBPlus* getRaiz() { return raiz; }
};

struct Arista { int v, peso; };

// Dijkstra y Tablas se mantienen igual...
void rutaMantenimiento(int origen, int destino, int n, const vector<vector<Arista>>& adj, map<int, string>& idANombre) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, 1e9);
    vector<int> padre(n, -1);
    dist[origen] = 0;
    pq.push({0, origen});

    while(!pq.empty()){
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if(d > dist[u]) continue;
        for(auto& e : adj[u]){
            if(dist[u] + e.peso < dist[e.v]){
                dist[e.v] = dist[u] + e.peso;
                padre[e.v] = u;
                pq.push({dist[e.v], e.v});
            }
        }
    }

    if(dist[destino] == 1e9) cout << "\n[!] No hay conexion entre los puntos.\n";
    else {
        cout << "\n>>> RESULTADO DE LOGISTICA <<<" << endl;
        cout << "Tiempo total estimado: " << dist[destino] << " min." << endl;
        cout << "Ruta optimizada: ";
        vector<int> path;
        for(int v=destino; v!=-1; v=padre[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        for(int i=0; i<path.size(); i++) 
            cout << idANombre[path[i]] << (i==path.size()-1 ? "" : " -> ");
        cout << endl;
    }
}

void mostrarTablaCalles(map<int, string>& idANombre, const vector<vector<Arista>>& grafo) {
    cout << "\n========== TABLA DE CONEXIONES (CIUDAD) ==========" << endl;
    cout << left << setw(20) << "ORIGEN" << setw(20) << "DESTINO" << setw(10) << "TIEMPO" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int u = 0; u < grafo.size(); u++) {
        for (auto& e : grafo[u]) {
            if (u < e.v) cout << left << setw(20) << idANombre[u] << setw(20) << idANombre[e.v] << setw(10) << e.peso << endl;
        }
    }
}

void mostrarTablaMedidores(NodoBPlus* raiz, map<int, string>& idANombre) {
    cout << "\n========== TABLA DE MEDIDORES REGISTRADOS ==========" << endl;
    cout << left << setw(10) << "ID" << setw(25) << "DIRECCION" << setw(20) << "CONEXION" << endl;
    cout << "----------------------------------------------------" << endl;
    NodoBPlus* temp = raiz;
    if (!temp) return;
    while (!temp->esHoja) temp = temp->hijos[0];
    while (temp) {
        for (auto& m : temp->datos) {
            cout << left << setw(10) << m.id << setw(25) << m.direccion << setw(20) << idANombre[m.posteConectado] << endl;
        }
        temp = temp->siguiente;
    }
}

// ==========================================
// MAIN MODIFICADO PARA SOPORTAR ESPACIOS
// ==========================================
int main() {
    int m;
    cout << "Configuracion Inicial - Orden Arbol B+: "; cin >> m;
    ArbolBPlus tree(m);
    
    map<string, int> nombreANodo;
    map<int, string> idANombre;
    int contadorNodos = 0;
    vector<vector<Arista>> grafo;

    int opcion;
    do {
        cout << "\n==========================================" << endl;
        cout << "    SISTEMA DE GESTION ELECTRICA (ED)     " << endl;
        cout << "==========================================" << endl;
        cout << "1. Registrar Calles/Conexiones" << endl;
        cout << "2. Registrar Medidores" << endl;
        cout << "3. Ver Tablas de Datos" << endl;
        cout << "4. Ver Estructura del Arbol B+" << endl;
        cout << "5. Calcular Ruta de Mantenimiento (Falla)" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: "; 
        if(!(cin >> opcion)) { // Limpiar si ingresan letras en el menú
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch(opcion) {
            case 1: {
                cin.ignore(); 
                cout << "\n--- REGISTRO DE CIUDAD (Escriba 'fin' para terminar) ---" << endl;
                while (true) {
                    string u_n, v_n, peso_str;
                    cout << "Punto A: "; getline(cin, u_n);
                    if (u_n == "fin") break;
                    cout << "Punto B: "; getline(cin, v_n);
                    cout << "Tiempo/Peso (minutos): "; getline(cin, peso_str);
                    int w = stoi(peso_str);

                    if (!nombreANodo.count(u_n)) {
                        nombreANodo[u_n] = contadorNodos;
                        idANombre[contadorNodos++] = u_n;
                        grafo.push_back({});
                    }
                    if (!nombreANodo.count(v_n)) {
                        nombreANodo[v_n] = contadorNodos;
                        idANombre[contadorNodos++] = v_n;
                        grafo.push_back({});
                    }
                    grafo[nombreANodo[u_n]].push_back({nombreANodo[v_n], w});
                    grafo[nombreANodo[v_n]].push_back({nombreANodo[u_n], w});
                }
                break;
            }
            case 2: {
                cout << "\n--- REGISTRO DE MEDIDORES (ID -1 para terminar) ---" << endl;
                while (true) {
                    string id_str;
                    cout << "ID Medidor: "; cin >> id_str;
                    int id = stoi(id_str);
                    if (id == -1) break;

                    cin.ignore();
                    Medidor med; med.id = id;
                    cout << "Direccion completa: "; getline(cin, med.direccion);
                    cout << "Conectado al lugar (Nombre exacto): "; string lug; getline(cin, lug);

                    if (nombreANodo.count(lug)) {
                        med.posteConectado = nombreANodo[lug];
                        tree.insertar(med);
                    } else cout << "[!] Error: El lugar '" << lug << "' no existe." << endl;
                }
                break;
            }
            case 3:
                mostrarTablaCalles(idANombre, grafo);
                mostrarTablaMedidores(tree.getRaiz(), idANombre);
                break;
            case 4:
                tree.mostrarEstructura(tree.getRaiz(), 0);
                break;
            case 5: {
                int idBusq; cout << "ID del medidor con falla: "; cin >> idBusq;
                Medidor* f = tree.buscar(idBusq);
                if (f) {
                    cin.ignore();
                    string loc; cout << "Ubicacion actual del camion: "; getline(cin, loc);
                    if (nombreANodo.count(loc)) {
                        rutaMantenimiento(nombreANodo[loc], f->posteConectado, contadorNodos, grafo, idANombre);
                    } else cout << "[!] El lugar no existe." << endl;
                } else cout << "[!] No encontrado." << endl;
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}