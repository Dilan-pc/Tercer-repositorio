// Árbol general con representación "primer hijo - siguiente hermano".
// Ejemplo: un pequeño sistema de carpetas y archivos.
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Nodo {
    string dato;
    Nodo* primerHijo;
    Nodo* siguienteHermano;
    Nodo(const string& valor)
        : dato(valor), primerHijo(nullptr), siguienteHermano(nullptr) {}
};

// Agrega un hijo al final de la cadena de hijos del padre.
Nodo* agregarHijo(Nodo* padre, const string& valor) {
    Nodo* nuevo = new Nodo(valor);
    if (padre->primerHijo == nullptr) {
        padre->primerHijo = nuevo;
    } else {
        Nodo* h = padre->primerHijo;
        while (h->siguienteHermano != nullptr) h = h->siguienteHermano;
        h->siguienteHermano = nuevo;
    }
    return nuevo;
}

// Preorden: visito el nodo y luego cada hijo (con sangría según profundidad).
void imprimir(Nodo* n, int profundidad = 0) {
    if (n == nullptr) return;
    cout << string(profundidad * 3, ' ') << "- " << n->dato << '\n';
    for (Nodo* h = n->primerHijo; h != nullptr; h = h->siguienteHermano)
        imprimir(h, profundidad + 1);
}

int contarNodos(Nodo* n) {
    if (n == nullptr) return 0;
    int total = 1;
    for (Nodo* h = n->primerHijo; h; h = h->siguienteHermano)
        total += contarNodos(h);
    return total;
}

int contarHojas(Nodo* n) {
    if (n == nullptr) return 0;
    if (n->primerHijo == nullptr) return 1;
    int total = 0;
    for (Nodo* h = n->primerHijo; h; h = h->siguienteHermano)
        total += contarHojas(h);
    return total;
}

// Altura en aristas: una hoja tiene altura 0.
int altura(Nodo* n) {
    if (n == nullptr) return -1;
    int maxAltura = -1;
    for (Nodo* h = n->primerHijo; h; h = h->siguienteHermano)
        maxAltura = max(maxAltura, altura(h));
    return maxAltura + 1;
}

// Devuelve el nodo con ese dato (o nullptr si no existe).
Nodo* buscar(Nodo* n, const string& valor) {
    if (n == nullptr) return nullptr;
    if (n->dato == valor) return n;
    for (Nodo* h = n->primerHijo; h; h = h->siguienteHermano) {
        Nodo* r = buscar(h, valor);
        if (r != nullptr) return r;
    }
    return nullptr;
}

// Postorden: libero primero los hijos y después el padre.
void liberar(Nodo* n) {
    if (n == nullptr) return;
    Nodo* h = n->primerHijo;
    while (h != nullptr) {
        Nodo* sig = h->siguienteHermano;  // guardo antes de borrar
        liberar(h);
        h = sig;
    }
    delete n;
}

int main() {
    Nodo* raiz = new Nodo("Documentos");
    Nodo* uni = agregarHijo(raiz, "Universidad");
    Nodo* fotos = agregarHijo(raiz, "Fotos");
    agregarHijo(raiz, "notas.txt");

    Nodo* ed = agregarHijo(uni, "EstructurasDeDatos");
    agregarHijo(uni, "Calculo");
    agregarHijo(ed, "arboles.pdf");
    agregarHijo(ed, "taller1.cpp");
    agregarHijo(fotos, "vacaciones.jpg");
    agregarHijo(fotos, "familia.jpg");

    cout << "Estructura del árbol:\n";
    imprimir(raiz);

    cout << "\nTotal de nodos: " << contarNodos(raiz)
         << "\nAristas (n - 1): " << contarNodos(raiz) - 1
         << "\nHojas: " << contarHojas(raiz)
         << "\nAltura del árbol: " << altura(raiz) << '\n';

    cout << "\nBuscar \"Calculo\": "
         << (buscar(raiz, "Calculo") ? "encontrado" : "no existe") << '\n';
    cout << "Buscar \"musica.mp3\": "
         << (buscar(raiz, "musica.mp3") ? "encontrado" : "no existe") << '\n';

    liberar(raiz);
    return 0;
}
