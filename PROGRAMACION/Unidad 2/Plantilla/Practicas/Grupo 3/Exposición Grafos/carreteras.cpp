#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

class RedCiudades {
private:
    map<string, vector<string>> conexiones;
    
public:
    // Agregar una carretera entre dos ciudades
    void agregarCarretera(string ciudad1, string ciudad2) {
        conexiones[ciudad1].push_back(ciudad2);
        conexiones[ciudad2].push_back(ciudad1);
    }
    
    // Mostrar todas las conexiones
    void mostrarRed() {
        cout << "\n||====================================||" << endl;
        cout << "||     RED DE CIUDADES CONECTADAS     ||" << endl;
        cout << "||====================================||\n" << endl;
        
        for (auto& par : conexiones) {
            cout << "ciudad " << par.first << " conecta con: ";
            for (size_t i = 0; i < par.second.size(); i++) {
                cout << par.second[i];
                if (i < par.second.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    
    // Graficar el grafo en ASCII
    void graficarRed() {
        cout << "\n┌─────────────────────────────────────┐" << endl;
        cout << "│       REPRESENTACIÓN GRÁFICA        │" << endl;
        cout << "│           DEL GRAFO DE              │" << endl;
        cout << "│             CIUDADES                │" << endl;
        cout << "└─────────────────────────────────────┘\n" << endl;
        
        // Definir posiciones aproximadas de las ciudades
        map<string, pair<int, int>> posiciones;
        
        // Asignar coordenadas para un layout más ordenado
        posiciones["Quito"] = {4, 0};
        posiciones["Guayaquil"] = {0, 4};
        posiciones["Cuenca"] = {4, 4};
        posiciones["Ambato"] = {8, 0};
        posiciones["Machala"] = {0, 8};
        posiciones["Loja"] = {8, 8};
        posiciones["Riobamba"] = {8, 4};
        posiciones["Esmeraldas"] = {0, 0};
        posiciones["Manta"] = {0, 2};
        
        // Crear una matriz para dibujar
        const int FILAS = 10;
        const int COLUMNAS = 12;
        char matriz[FILAS][COLUMNAS];
        
        // Inicializar matriz con espacios
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                matriz[i][j] = ' ';
            }
        }
        
        // Dibujar conexiones primero (para que las ciudades queden encima)
        for (auto& ciudad : conexiones) {
            string nombreCiudad = ciudad.first;
            if (posiciones.find(nombreCiudad) != posiciones.end()) {
                int x1 = posiciones[nombreCiudad].first;
                int y1 = posiciones[nombreCiudad].second;
                
                for (string vecino : ciudad.second) {
                    if (posiciones.find(vecino) != posiciones.end()) {
                        int x2 = posiciones[vecino].first;
                        int y2 = posiciones[vecino].second;
                        
                        // Dibujar línea entre las ciudades
                        int dx = x2 - x1;
                        int dy = y2 - y1;
                        int steps = max(abs(dx), abs(dy));
                        
                        for (int i = 0; i <= steps; i++) {
                            float t = (steps == 0) ? 0 : (float)i / steps;
                            int x = x1 + (int)(dx * t);
                            int y = y1 + (int)(dy * t);
                            
                            // Verificar límites de la matriz
                            if (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS) {
                                if (matriz[x][y] == ' ') {
                                    matriz[x][y] = '.';
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Dibujar ciudades (nodos)
        for (auto& pos : posiciones) {
            int x = pos.second.first;
            int y = pos.second.second;
            
            if (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS) {
                matriz[x][y] = '●';
                
                // Escribir nombre cerca del nodo
                string nombre = pos.first;
                
                // Posicionar el nombre según la ciudad
                if (nombre == "Quito") {
                    cout << "            ● Quito" << endl;
                } else if (nombre == "Guayaquil") {
                    cout << "        ● Guayaquil" << endl;
                } else if (nombre == "Cuenca") {
                    cout << "              ● Cuenca" << endl;
                } else if (nombre == "Ambato") {
                    cout << "                  ● Ambato" << endl;
                } else if (nombre == "Machala") {
                    cout << "        ● Machala" << endl;
                } else if (nombre == "Loja") {
                    cout << "                  ● Loja" << endl;
                } else if (nombre == "Riobamba") {
                    cout << "                  ● Riobamba" << endl;
                } else if (nombre == "Esmeraldas") {
                    cout << "    ● Esmeraldas" << endl;
                } else if (nombre == "Manta") {
                    cout << "    ● Manta" << endl;
                }
            }
        }
        
        // Imprimir matriz con las conexiones
        cout << "\n              GRAFO DE CONEXIONES\n";
        cout << "              ─────────────────\n";
        
        for (int i = 0; i < FILAS; i++) {
            cout << "              ";
            for (int j = 0; j < COLUMNAS; j++) {
                if (matriz[i][j] == '●') {
                    cout << "● ";
                } else if (matriz[i][j] == '.') {
                    cout << "· ";
                } else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        
        // Mostrar leyenda de conexiones
        cout << "\n┌─────────────────────────────────────────┐" << endl;
        cout << "│           LEYENDA DE CONEXIONES         │" << endl;
        cout << "├─────────────────────────────────────────┤" << endl;
        
        for (auto& ciudad : conexiones) {
            if (!ciudad.second.empty()) {
                cout << "│ " << ciudad.first;
                // Añadir espacios para alinear
                int espacios = 15 - ciudad.first.length();
                for (int i = 0; i < espacios; i++) cout << " ";
                cout << "→ ";
                
                for (size_t i = 0; i < ciudad.second.size(); i++) {
                    cout << ciudad.second[i];
                    if (i < ciudad.second.size() - 1) cout << ", ";
                }
                
                // Añadir espacios al final
                int totalLength = 15 + 2 + ciudad.first.length();
                for (size_t i = 0; i < ciudad.second.size(); i++) {
                    totalLength += ciudad.second[i].length();
                    if (i < ciudad.second.size() - 1) totalLength += 2;
                }
                
                espacios = 40 - totalLength;
                for (int i = 0; i < espacios; i++) cout << " ";
                cout << "│" << endl;
            }
        }
        cout << "└─────────────────────────────────────────┘" << endl;
    }
    
    // Buscar ruta más corta entre dos ciudades
    void buscarRuta(string origen, string destino) {
        cout << "\n Buscando ruta de " << origen << " a " << destino << "...\n" << endl;
        
        if (conexiones.find(origen) == conexiones.end()) {
            cout << " Error: La ciudad " << origen << " no existe en la red" << endl;
            return;
        }
        if (conexiones.find(destino) == conexiones.end()) {
            cout << " Error: La ciudad " << destino << " no existe en la red" << endl;
            return;
        }
        
        map<string, bool> visitado;
        map<string, string> padre;
        map<string, int> distancia;
        queue<string> cola;
        
        // Inicializar
        visitado[origen] = true;
        distancia[origen] = 0;
        padre[origen] = "";
        cola.push(origen);
        
        cout << " Explorando ciudades: ";
        
        // BFS
        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();
            cout << actual << " ";
            
            if (actual == destino) break;
            
            for (string vecino : conexiones[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    distancia[vecino] = distancia[actual] + 1;
                    padre[vecino] = actual;
                    cola.push(vecino);
                }
            }
        }
        
        cout << "\n" << endl;
        
        // Verificar si se encontró ruta
        if (!visitado[destino]) {
            cout << " No hay ruta entre " << origen << " y " << destino << endl;
            return;
        }
        
        // Reconstruir camino
        vector<string> ruta;
        string ciudad = destino;
        while (ciudad != "") {
            ruta.push_back(ciudad);
            ciudad = padre[ciudad];
        }
        
        // Mostrar resultado
        cout << " ¡Ruta encontrada!" << endl;
        cout << " Distancia: " << distancia[destino] << " conexiones" << endl;
        cout << "  Ruta: ";
        
        for (int i = ruta.size() - 1; i >= 0; i--) {
            cout << ruta[i];
            if (i > 0) cout << " → ";
        }
        cout << endl;
    }
};

int main() {
    RedCiudades red;
    
    cout << "\n||====================================||" << endl;
    cout << "||  SISTEMA DE RUTAS ENTRE CIUDADES   ||" << endl;
    cout << "||====================================||" << endl;
    
    // Crear la red de ciudades (grafo)
    cout << "\n Creando red de ciudades..." << endl;
    
    red.agregarCarretera("Quito", "Guayaquil");
    red.agregarCarretera("Quito", "Cuenca");
    red.agregarCarretera("Quito", "Ambato");
    red.agregarCarretera("Guayaquil", "Cuenca");
    red.agregarCarretera("Guayaquil", "Machala");
    red.agregarCarretera("Cuenca", "Loja");
    red.agregarCarretera("Ambato", "Riobamba");
    red.agregarCarretera("Riobamba", "Cuenca");
    red.agregarCarretera("Loja", "Machala");
    
    // Mostrar la red
    red.mostrarRed();
    
    // Graficar el grafo
    red.graficarRed();
    
    // Buscar diferentes rutas
    red.buscarRuta("Quito", "Loja");
    red.buscarRuta("Ambato", "Machala");
    red.buscarRuta("Guayaquil", "Riobamba");
    
    // Agregar ciudades desconectadas y graficar nuevamente
    cout << "\n" << endl;
    red.agregarCarretera("Esmeraldas", "Manta");
    
    cout << "\n||====================================||" << endl;
    cout << "||  GRAFO CON NUEVAS CONEXIONES       ||" << endl;
    cout << "||====================================||" << endl;
    red.graficarRed();
    
    // Intentar una ruta imposible
    red.buscarRuta("Quito", "Esmeraldas");
    
    cout << "\n||====================================||" << endl;
    cout << "||      PROGRAMA FINALIZADO           ||" << endl;
    cout << "||====================================||\n" << endl;
    
    return 0;
}