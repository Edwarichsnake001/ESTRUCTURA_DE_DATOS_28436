#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

// =========================================================
// 1. ENTIDAD DE DATOS (El "Qué" estamos guardando)
// =========================================================
struct Producto {
    int id;
    string nombre;
    int precioBase;
    int nodoGraf; // Enlace clave: ID que este producto tiene en el Grafo
};

// =========================================================
// 2. MÓDULO ÁRBOL AVL (Búsqueda Eficiente O(log n))
// =========================================================
/* EXPLICACIÓN: El AVL mantiene los productos ordenados por ID. 
   Se usa para que, al buscar un producto entre miles, el sistema 
   no tarde casi nada. Las rotaciones mantienen el árbol balanceado.
*/
struct NodoAVL {
    Producto dato;
    NodoAVL *izq, *der;
    int altura;
    NodoAVL(Producto p) : dato(p), izq(nullptr), der(nullptr), altura(1) {}
};

int altura(NodoAVL* n) { return n ? n->altura : 0; }
int getBalance(NodoAVL* n) { return n ? altura(n->izq) - altura(n->der) : 0; }

// ROTACIONES: Movimientos mecánicos para equilibrar el árbol si un lado pesa más
NodoAVL* rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;
    x->der = y; y->izq = T2;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    return x;
}

NodoAVL* rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;
    y->izq = x; x->der = T2;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    return y;
}

NodoAVL* insertarAVL(NodoAVL* nodo, Producto p) {
    if (!nodo) return new NodoAVL(p);
    if (p.id < nodo->dato.id) nodo->izq = insertarAVL(nodo->izq, p);
    else if (p.id > nodo->dato.id) nodo->der = insertarAVL(nodo->der, p);
    else return nodo;

    // Actualizar altura y verificar balanceo
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
    int bal = getBalance(nodo);

    // Casos de rotación (Simple y Doble)
    if (bal > 1 && p.id < nodo->izq->dato.id) return rotarDerecha(nodo);
    if (bal < -1 && p.id > nodo->der->dato.id) return rotarIzquierda(nodo);
    if (bal > 1 && p.id > nodo->izq->dato.id) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
    if (bal < -1 && p.id < nodo->der->dato.id) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

NodoAVL* buscarAVL(NodoAVL* raiz, int id) {

    if (!raiz || raiz->dato.id == id) return raiz;

    if (id < raiz->dato.id) return buscarAVL(raiz->izq, id);

    return buscarAVL(raiz->der, id);

}

// =========================================================
// 3. MÓDULO GRAFOS (Lógica de Descuentos con Bellman-Ford)
// =========================================================
struct Promo {
    int u, v, ahorro; // u: requisito, v: producto con descuento, ahorro: negativo
};

/*
   EXPLICACIÓN: Bellman-Ford es ideal aquí porque los descuentos 
   se representan como "pesos negativos". El algoritmo recorre todas 
   las promos (aristas) buscando reducir el costo total.
*/
void optimizarCombo(int inicio, int fin, int V, const vector<Promo>& promos, map<int, string>& idANombre) {
    // 1. Inicializar: costo infinito para todos, 0 para el punto de partida
    vector<int> balance(V, 1e9);
    vector<int> rastro(V, -1);
    balance[inicio] = 0;

    // 2. Relajación: Repetir V-1 veces (Máximo camino posible sin ciclos)
    for (int i = 1; i <= V - 1; i++) {
        for (auto& p : promos) {
            // Si puedo llegar a 'v' de forma más barata a través de 'u', actualizo
            if (balance[p.u] != 1e9 && balance[p.u] + p.ahorro < balance[p.v]) {
                balance[p.v] = balance[p.u] + p.ahorro;
                rastro[p.v] = p.u;
            }
        }
    }

    // 3. Verificación de Ciclo Negativo: Si después de V-1 veces aún baja el costo, 
    // hay un bucle infinito de descuento (ERROR DE LÓGICA COMERCIAL).
    for (auto& p : promos) {
        if (balance[p.u] != 1e9 && balance[p.u] + p.ahorro < balance[p.v]) {
            cout << "\n[!] ERROR: Bucle de descuento infinito detectado. No es físicamente posible.\n";
            return;
        }
    }

    // 4. Mostrar Resultados
    if (balance[fin] == 1e9) {
        cout << "\nNo existe una cadena de descuentos que conecte estos productos." << endl;
    } else {
        cout << "\n>>> ESTRATEGIA DE COMPRA ENCONTRADA <<<" << endl;
        cout << "Ahorro acumulado al comprar en este orden: $" << abs(balance[fin]) << " USD." << endl;
        
        // Reconstrucción del camino usando el rastro (padres)
        vector<int> path;
        for (int v = fin; v != -1; v = rastro[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        
        cout << "PASOS: ";
        for (int i = 0; i < path.size(); i++)
            cout << idANombre[path[i]] << (i == path.size() - 1 ? "" : " -> ");
        cout << endl;
    }
}

// =========================================================
// 5. MAIN (Controlador de la lógica)
// =========================================================
int main() {
    NodoAVL* inventario = nullptr;
    vector<Promo> promociones;
    map<string, int> nombreANodo;
    map<int, string> idANombre;
    int contadorNodos = 0, opcion;

    do {
        cout << "\n==============================================" << endl;
        cout << "   SISTEMA INTELIGENTE DE VENTAS Y COMBOS     " << endl;
        cout << "==============================================" << endl;
        cout << "1. CONFIGURAR REGLAS DE DESCUENTO (Combos)" << endl;
        cout << "2. CARGAR INVENTARIO DE PRODUCTOS (Bodega)" << endl;
        cout << "3. ASISTENTE DE COMPRA: MAXIMIZAR AHORRO" << endl;
        cout << "0. SALIR DEL SISTEMA" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Seleccione una accion: "; cin >> opcion;

        switch (opcion) {
            case 1: {
                cin.ignore();
                cout << "\n--- MODULO DE CONFIGURACION DE OFERTAS ---" << endl;
                cout << "Instruccion: Indique que producto activa el descuento para el siguiente." << endl;
                cout << "(Escriba 'listo' para finalizar el registro)" << endl;
                while (true) {
                    string pA, pB; int desc;
                    cout << "\nProducto Requisito: "; getline(cin, pA);
                    if (pA == "listo") break;
                    cout << "Producto con Beneficio: "; getline(cin, pB);
                    cout << "Descuento otorgado ($): "; cin >> desc;
                    cin.ignore();

                    // Mapeo amigable
                    if (!nombreANodo.count(pA)) { 
                        nombreANodo[pA] = contadorNodos; 
                        idANombre[contadorNodos++] = pA; 
                    }
                    if (!nombreANodo.count(pB)) { 
                        nombreANodo[pB] = contadorNodos; 
                        idANombre[contadorNodos++] = pB; 
                    }
                    // Guardar regla como arista negativa
                    promociones.push_back({nombreANodo[pA], nombreANodo[pB], -abs(desc)});
                }
                break;
            }
            case 2: {
                cout << "\n--- MODULO DE INGRESO A BODEGA (AVL) ---" << endl;
                cout << "(Ingrese ID -1 para volver al menu principal)" << endl;
                while (true) {
                    int id; cout << "\nCodigo de Barras (ID): "; cin >> id;
                    if (id == -1) break;
                    Producto p; p.id = id;
                    cin.ignore();
                    cout << "Nombre Comercial: "; getline(cin, p.nombre);
                    cout << "Precio de Etiqueta ($): "; cin >> p.precioBase;
                    cout << "Vincular con Oferta (Nombre del Combo): "; cin.ignore();
                    string ref; getline(cin, ref);
                    
                    if (nombreANodo.count(ref)) {
                        p.nodoGraf = nombreANodo[ref];
                        inventario = insertarAVL(inventario, p);
                        cout << ">> [EXITO] Producto '" << p.nombre << "' guardado y vinculado." << endl;
                    } else {
                        cout << ">> [ERROR] No existe una regla de descuento para '" << ref << "'." << endl;
                        cout << "   Primero configure la regla en la Opcion 1." << endl;
                    }
                }
                break;
            }
            case 3: {
                if (!inventario) {
                    cout << "\n[!] El inventario esta vacio. Cargue productos primero." << endl;
                    break;
                }
                int idDest; 
                cout << "\n--- ASISTENTE DE COMPRA PERSONALIZADO ---" << endl;
                cout << "Ingrese el codigo del producto que desea comprar: "; cin >> idDest;
                
                NodoAVL* res = buscarAVL(inventario, idDest);
                if (res) {
                    cin.ignore();
                    string origen; 
                    cout << "Usted ya tiene '" << res->dato.nombre << "' en su carrito." << endl;
                    cout << "¿Que otro producto compro previamente para activar descuentos?: "; 
                    getline(cin, origen);

                    if (nombreANodo.count(origen)) {
                        cout << "\nCalculando la mejor estrategia de ahorro..." << endl;
                        optimizarCombo(nombreANodo[origen], res->dato.nodoGraf, contadorNodos, promociones, idANombre);
                    } else {
                        cout << "[!] El producto '" << origen << "' no participa en ninguna promocion." << endl;
                    }
                } else cout << "[!] Codigo de producto no encontrado." << endl;
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}