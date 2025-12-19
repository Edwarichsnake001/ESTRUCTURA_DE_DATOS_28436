#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Grafo {
private:
    int n; // número de nodos
    vector<vector<pair<int,int>>> adj; // lista de adyacencia

public:
    // Constructor: inicializa el grafo con n nodos
    Grafo(int nodos) {
        n = nodos;
        adj.resize(n);
    }

    // Método para agregar arista (u -> v con peso w)
    void agregarArista(int u, int v, int peso) {
        // Insertamos el vecino y el peso en la lista del nodo u
        adj[u].push_back({v, peso});
    }

    /*
        Método Dijkstra:
        ----------------
        Calcula la distancia mínima desde un nodo origen
        a todos los demás utilizando una cola de prioridad.
    */
    vector<int> dijkstra(int origen) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[origen] = 0;

        // Cola de prioridad min-heap (guarda (distancia, nodo))
        priority_queue<pair<int,int>, 
                       vector<pair<int,int>>, 
                       greater<pair<int,int>>> pq;

        pq.push({0, origen});

        while (!pq.empty()) {
            int dActual = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // Si ya existe una distancia mejor, ignoramos esta
            if (dActual > dist[u]) continue;

            // Recorremos los vecinos del nodo u
            for (auto &par : adj[u]) {
                int v = par.first;
                int peso = par.second;

                // Relajación (actualizar distancia si encontramos algo mejor)
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    /*
        Creamos un grafo de 5 nodos y simulamos algo parecido
        a un mapa sencillo donde cada peso representa la distancia
        entre lugares.
    */

    Grafo mapa(5);

    // Agregamos conexiones entre lugares
    mapa.agregarArista(0, 1, 4);
    mapa.agregarArista(0, 2, 2);
    mapa.agregarArista(2, 1, 1);
    mapa.agregarArista(1, 3, 3);
    mapa.agregarArista(2, 3, 6);
    mapa.agregarArista(3, 4, 2);

    // Calculamos rutas desde el punto 0
    vector<int> distancias = mapa.dijkstra(0);

    cout << "Distancias minimas desde el nodo 0:\n";
    for (int i = 0; i < distancias.size(); i++) {
        cout << "0 -> " << i << " = " << distancias[i] << endl;
    }

    return 0;
}

