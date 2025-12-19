#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <limits>
#include <algorithm>
#include <string>
#include <iomanip> 

using namespace std;

// Definición de una arista: (Origen, Destino, Recompensa/Costo)
typedef tuple<string, string, double> MisionRelacion; 

// Función auxiliar para imprimir el estado actual de las recompensas (sin cambios)
void imprimir_recompensas(int iteracion, const map<string, double>& recompensas, const vector<string>& nodos) {
    cout << "\n========================================================================================================\n";
    if (iteracion == 0) {
        cout << "ESTADO INICIAL (Iteracion 0)";
    } else {
        cout << "ESTADO DESPUÉS DE ITERACIÓN " << iteracion;
    }
    cout << "\n========================================================================================================\n";
    
    // Encabezados de la tabla
    cout << "| " << setw(20) << left << "MISIÓN (NODO)" << " | " << setw(18) << right << "RECOMPENSA ACUMULADA" << " |" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Cuerpo de la tabla
    for (const string& nodo : nodos) {
        double recompensa = recompensas.at(nodo);
        cout << "| " << setw(20) << left << nodo << " | ";
        
        if (recompensa == -numeric_limits<double>::infinity()) {
            cout << setw(18) << right << "INF NEGATIVO";
        } else {
            cout << setw(18) << right << fixed << setprecision(1) << recompensa;
        }
        cout << " |" << endl;
    }
    cout << "========================================================================================================\n";
}

// Implementación del Algoritmo de Bellman-Ford (adaptado para Máxima Recompensa)
pair<map<string, double>, bool> bellman_ford_recompensa(
    const vector<string>& todos_los_nodos, 
    const vector<MisionRelacion>& relaciones, 
    const string& inicio
) {
    // ... [Inicialización de estructuras] ...
    map<string, double> recompensas; 
    map<string, string> predecesores;
    
    for (const string& nodo : todos_los_nodos) {
        recompensas[nodo] = -numeric_limits<double>::infinity();
        predecesores[nodo] = "-1"; 
    }
    recompensas[inicio] = 0.0;
    
    int V = todos_los_nodos.size();

    imprimir_recompensas(0, recompensas, todos_los_nodos);

    // 2. Relajación de Relaciones (V - 1) veces
    for (int i = 0; i < V - 1; ++i) {
        bool cambiado = false;
        
        cout << "\n--- RELAJACIÓN DE ARISTAS EN ITERACIÓN " << i + 1 << " ---" << endl;
        bool hubo_mejora_en_iteracion = false; // Flag para saber si imprimir "NO HUBO MEJORAS"

        // Usamos un vector temporal para almacenar los detalles de los cambios
        vector<string> cambios_detalle_vertical;

        for (const auto& relacion : relaciones) {
            string u, v; 
            double recompensa;
            tie(u, v, recompensa) = relacion;

            if (recompensas[u] != -numeric_limits<double>::infinity() && recompensas[u] + recompensa > recompensas[v]) {
                
                // Formato de salida vertical
                string detalle = "  -> RELAX: " + u + " -> " + v + " | Gana: " + to_string((int)recompensa) + 
                                 " | Antiguo: " + to_string((int)recompensas[v]) + 
                                 " | Nuevo Total: " + to_string((int)(recompensas[u] + recompensa));
                cambios_detalle_vertical.push_back(detalle);
                
                recompensas[v] = recompensas[u] + recompensa;
                predecesores[v] = u;
                cambiado = true;
                hubo_mejora_en_iteracion = true;
            }
        }
        
        if (hubo_mejora_en_iteracion) {
            cout << "CAMBIOS REALIZADOS EN ESTA PASADA:\n";
            for (const string& detalle : cambios_detalle_vertical) {
                cout << detalle << endl;
            }
        } else {
            cout << "NO HUBO MEJORAS EN ESTA ITERACIÓN." << endl;
        }
        
        imprimir_recompensas(i + 1, recompensas, todos_los_nodos);

        if (!cambiado) {
            cout << "\n[FIN TEMPRANO]: El grafo ha convergido después de la Iteración " << i << ".\n" << endl;
            break;
        }
    }

    // 3. Chequeo de Ciclos de Recompensa Positiva (V-ésima Iteración)
    cout << "\n--- PRUEBA DE CICLO DE GRINDEO POSITIVO (Iteracion V = " << V << ") ---" << endl;
    bool ciclo_infinito = false;
    
    for (const auto& relacion : relaciones) {
        string u, v;
        double recompensa;
        tie(u, v, recompensa) = relacion;

        if (recompensas[u] != -numeric_limits<double>::infinity() && recompensas[u] + recompensa > recompensas[v]) {
            // Identificar la arista específica que permite el ciclo!
            cout << "  ¡CICLO DETECTADO! La arista " << u << "->" << v 
                 << " permite otra mejora (" << recompensas[u] + recompensa << " > " << recompensas[v] << ").\n";
            ciclo_infinito = true;
            break; 
        }
    }

    return {recompensas, ciclo_infinito};
}

// Función principal de ejemplo (Main)
int main() {
    // --- Modelado de Misiones (Nodos) ---
    vector<string> misiones_nodos = {
        "Inicio", "MS_1: Tutorial", "MS_2: Recoleccion", 
        "MP_1: Explorar", "MP_2: Asalto", "Jefe", "Cofre_Secreto"
    };

    // --- Definición de las Relaciones (Aristas y Pesos) ---
    vector<MisionRelacion> relaciones_misiones = {
        {"Inicio", "MS_1: Tutorial", 100.0},
        {"Inicio", "MP_1: Explorar", 50.0},
        {"MS_1: Tutorial", "MS_2: Recoleccion", 200.0},
        
        // Bucle de grindeo (recompensa neta positiva: 500 + 10 = 510)
        {"MS_2: Recoleccion", "MP_2: Asalto", 500.0}, 
        {"MP_2: Asalto", "MS_2: Recoleccion", 10.0}, 

        {"MP_1: Explorar", "MS_2: Recoleccion", 150.0},
        {"MP_2: Asalto", "Jefe", 800.0},
        {"Jefe", "Cofre_Secreto", 1000.0}
    };

    string nodo_inicial = "Inicio";
    string nodo_destino = "Cofre_Secreto";
    
    // Ejecutar el algoritmo
    auto resultado = bellman_ford_recompensa(misiones_nodos, relaciones_misiones, nodo_inicial);
    map<string, double> recompensas = resultado.first;
    bool ciclo_infinito = resultado.second;

    // Imprimir los resultados
    cout << "\n================================================================\n";
    cout << "--- ANALISIS FINAL: RUTA DE MAXIMA RECOMPENSA ---\n";
    cout << "Objetivo: " << nodo_destino << endl;
    
    if (ciclo_infinito) {
        cout << "\n****************************************************************\n";
        cout << "ADVERTENCIA: Se detecto un BUCLE DE GRINDEO POSITIVO (Recompensa Infinita).\n";
        cout << "El camino de maxima recompensa es teoricamente infinito.\n";
        cout << "****************************************************************\n";
    } 

    cout << "\nRecompensa maxima alcanzada en el destino: ";
    if (recompensas.count(nodo_destino) && recompensas.at(nodo_destino) == -numeric_limits<double>::infinity()) {
        cout << "No alcanzable." << endl;
    } else {
        // Mostrar la recompensa máxima
        cout << recompensas.at(nodo_destino) << " XP/Oro" << (ciclo_infinito ? " (El valor puede ser arbitrariamente alto)" : "") << endl;
    }

    return 0;
}