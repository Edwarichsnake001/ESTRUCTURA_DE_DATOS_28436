#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

   
    int max_val = arr[0];
    int min_val = arr[0];

    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    int range = max_val - min_val + 1;
    
    // --- 2. Crear y llenar el array de conteo (La 'distribución' clave) ---
    // Este array almacena cuántas veces aparece cada número
    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - min_val]++;
    }

    // --- 3. Modificar el conteo para tener posiciones acumuladas (sin ordenamiento secundario) ---
    // Esto es lo que evita el sort secundario. Convierte las frecuencias en índices finales.
    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // --- 4. Reconstruir el array de salida ---
    // Iteramos al revés para asegurar estabilidad (importante si hubiera datos asociados)
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }

    // --- 5. Copiar los elementos ordenados al array original ---
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

int main() {
    std::vector<int> data = {4, 2, 2, 8, 3, 3, 1, 9, 5};

    std::cout << "Array original: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    countingSort(data);

    std::cout << "Array ordenado con Counting Sort: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
