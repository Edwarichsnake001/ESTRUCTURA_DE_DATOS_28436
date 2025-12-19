#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class GrafoBipartido {
private:
    int procesos;
    int recursos;

    vector<vector<int>> grafo;        // Procesos -> Recursos
    vector<int> asignacionRecurso;     // Recurso -> Proceso
    vector<bool> visitado;

public:
    // Constructor
    GrafoBipartido(int p, int r) {
        procesos = p;
        recursos = r;
        grafo.resize(procesos);
        asignacionRecurso.assign(recursos, -1);
        visitado.resize(procesos);
    }

    // Agregar arista Proceso -> Recurso
    void agregarArista(int proceso, int recurso) {
        grafo[proceso].push_back(recurso);
    }

    // BFS para asignar un recurso a un proceso
    bool bfs(int procesoInicial) {
        queue<int> q;
        q.push(procesoInicial);
        fill(visitado.begin(), visitado.end(), false);

        while (!q.empty()) {
            int p = q.front();
            q.pop();

            for (int r : grafo[p]) {
                int procesoAsignado = asignacionRecurso[r];

                // Recurso libre
                if (procesoAsignado == -1) {
                    asignacionRecurso[r] = p;
                    return true;
                }
                // Intentar reasignar
                else if (!visitado[procesoAsignado]) {
                    visitado[procesoAsignado] = true;
                    q.push(procesoAsignado);
                }
            }
        }
        return false;
    }

    // Ejecutar la asignación de recursos
    void asignarRecursos() {
        int asignaciones = 0;

        for (int p = 0; p < procesos; p++) {
            if (bfs(p)) {
                asignaciones++;
            }
        }

        cout << "Asignaciones finales:\n";
        for (int r = 0; r < recursos; r++) {
            if (asignacionRecurso[r] != -1) {
                cout << "Recurso R" << r
                     << " asignado al Proceso P"
                     << asignacionRecurso[r] << endl;
            }
        }

        cout << "Total de asignaciones: " << asignaciones << endl;
    }
};

int main() {
    GrafoBipartido g(3, 3);

    // Conexiones Proceso -> Recursos
    g.agregarArista(0, 0);
    g.agregarArista(0, 1);
    g.agregarArista(1, 1);
    g.agregarArista(2, 0);
    g.agregarArista(2, 2);

    g.asignarRecursos();

    return 0;
}

