#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, double> Arista;
typedef pair<double, int> ParDistancia;

map<int, double> dijkstra(const map<int, vector<Arista>>& grafo, int inicio) {
    map<int, double> distancias;
    for (auto const& [nodo, _] : grafo) {
        distancias[nodo] = numeric_limits<double>::infinity();
    }
    distancias[inicio] = 0.0;

    priority_queue<ParDistancia, vector<ParDistancia>, greater<ParDistancia>> pq;
    pq.push({0.0, inicio});

    while (!pq.empty()) {
        double dist_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (dist_actual > distancias[nodo_actual]) {
            continue;
        }

        for (const auto& arista : grafo.at(nodo_actual)) {
            int vecino = arista.first;
            double peso = arista.second;
            
            double nueva_distancia = dist_actual + peso;
            
            if (nueva_distancia < distancias[vecino]) {
                distancias[vecino] = nueva_distancia;
                pq.push({nueva_distancia, vecino});
            }
        }
    }

    return distancias;
}

int main() {
    map<int, vector<Arista>> grafo_ejemplo = {
        {1, {{2, 1.0}, {3, 4.0}}},
        {2, {{3, 2.0}, {4, 5.0}, {5, 10.0}}},
        {3, {{4, 2.0}}},
        {4, {{5, 3.0}}},
        {5, {}}
    };

    int nodo_inicial = 1;
    
    map<int, double> resultados = dijkstra(grafo_ejemplo, nodo_inicial);

    cout << "Distancias mas cortas desde el nodo " << nodo_inicial << ":\n";
    for (const auto& par : resultados) {
        cout << "Nodo " << par.first << ": " << par.second << endl;
    }

    return 0;
}