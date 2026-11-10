// Árbol binario de búsqueda (ABB) con el árbol de los apuntes:
// inserciones 8, 3, 10, 1, 6, 14.
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
};

Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return new Nodo(valor);
    if (valor < raiz->dato) raiz->izq = insertar(raiz->izq, valor);
    else if (valor > raiz->dato) raiz->der = insertar(raiz->der, valor);
    // si es igual: no hago nada (regla: sin duplicados)
    return raiz;
}

bool buscar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return false;
    if (valor == raiz->dato) return true;
    return valor < raiz->dato ? buscar(raiz->izq, valor)
                              : buscar(raiz->der, valor);
}

Nodo* minimo(Nodo* n) {
    while (n->izq != nullptr) n = n->izq;
    return n;
}

// Eliminar: hoja, un hijo o dos hijos (sucesor inorden).
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return nullptr;
    if (valor < raiz->dato) {
        raiz->izq = eliminar(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = eliminar(raiz->der, valor);
    } else {
        if (raiz->izq == nullptr) {          // hoja o solo hijo derecho
            Nodo* hijo = raiz->der;
            delete raiz;
            return hijo;
        }
        if (raiz->der == nullptr) {          // solo hijo izquierdo
            Nodo* hijo = raiz->izq;
            delete raiz;
            return hijo;
        }
        Nodo* sucesor = minimo(raiz->der);   // dos hijos
        raiz->dato = sucesor->dato;
        raiz->der = eliminar(raiz->der, sucesor->dato);
    }
    return raiz;
}

void preorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    cout << raiz->dato << ' ';
    preorden(raiz->izq);
    preorden(raiz->der);
}

void inorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izq);
    cout << raiz->dato << ' ';
    inorden(raiz->der);
}

void postorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->dato << ' ';
}

void porNiveles(Nodo* raiz) {
    if (raiz == nullptr) return;
    queue<Nodo*> q;
    q.push(raiz);
    while (!q.empty()) {
        Nodo* n = q.front(); q.pop();
        cout << n->dato << ' ';
        if (n->izq) q.push(n->izq);
        if (n->der) q.push(n->der);
    }
}

int altura(Nodo* raiz) {   // en aristas; árbol vacío = -1
    if (raiz == nullptr) return -1;
    return 1 + max(altura(raiz->izq), altura(raiz->der));
}

int contarNodos(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

void liberar(Nodo* raiz) {   // postorden
    if (raiz == nullptr) return;
    liberar(raiz->izq);
    liberar(raiz->der);
    delete raiz;
}

void mostrarRecorridos(Nodo* raiz) {
    cout << "  Preorden:    "; preorden(raiz);   cout << '\n';
    cout << "  Inorden:     "; inorden(raiz);    cout << '\n';
    cout << "  Postorden:   "; postorden(raiz);  cout << '\n';
    cout << "  Por niveles: "; porNiveles(raiz); cout << '\n';
}

int main() {
    Nodo* raiz = nullptr;
    for (int v : {8, 3, 10, 1, 6, 14}) raiz = insertar(raiz, v);

    cout << "Recorridos del ABB:\n";
    mostrarRecorridos(raiz);
    cout << "\nNodos: " << contarNodos(raiz)
         << " | Altura: " << altura(raiz) << '\n';

    cout << "\nBuscar 6:  " << (buscar(raiz, 6)  ? "encontrado" : "no existe") << '\n';
    cout << "Buscar 7:  " << (buscar(raiz, 7)  ? "encontrado" : "no existe") << '\n';

    cout << "\nEliminar 1 (hoja):\n";
    raiz = eliminar(raiz, 1);
    cout << "  Inorden: "; inorden(raiz); cout << '\n';

    cout << "Eliminar 10 (un hijo, el 14 sube):\n";
    raiz = eliminar(raiz, 10);
    cout << "  Inorden: "; inorden(raiz); cout << '\n';

    cout << "Eliminar 3 (dos hijos, lo reemplaza su sucesor):\n";
    raiz = eliminar(raiz, 3);
    cout << "  Inorden:  "; inorden(raiz); cout << '\n';
    cout << "  Preorden: "; preorden(raiz); cout << '\n';

    liberar(raiz);
    return 0;
}
