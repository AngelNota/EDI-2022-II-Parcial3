#include "stdio.h"
#include "string.h"
#include "cola.h"
#include "stack.h"
#include "common.h"
#include <stdlib.h>
#include "lista.h"
#define GRAPH_CAPACITY 32

typedef struct grafo{
    int edges[GRAPH_CAPACITY][GRAPH_CAPACITY];
    char vertices[GRAPH_CAPACITY][20];
    int size;
}Grafo;

Nodo* CrearNodo(Libro* libro){
    Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));
    strncpy(nodo->libro.titulo, libro->titulo, 50);
    strncpy(nodo->libro.autor, libro->autor, 50);
    strncpy(nodo->libro.isbn, libro->isbn, 50);

    nodo->siguiente = NULL;
    return nodo;
}

void DestruirNodo(Nodo* nodo){
    free(nodo);
}
void Insertar(Lista* lista, Libro* libro){
    Nodo* nodo = CrearNodo(libro);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    ++lista->longitud;
}

void InsertarFinal(Lista* lista, Libro* libro){
    Nodo* nodo = CrearNodo(libro);
    Nodo* puntero = lista->cabeza;
    if (lista->cabeza == NULL){
        lista->cabeza = nodo;
    }
    else {
        Nodo *puntero = lista->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    ++lista->longitud;
}
void InsertarDespues(int n, Lista* lista, Libro* libro){
    Nodo* nodo = CrearNodo(libro);
    if (lista->cabeza == NULL){
        lista->cabeza = nodo;
    } else{
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion<n && puntero->siguiente){
            puntero = puntero->siguiente;
            posicion++;
        }
        nodo->siguiente = puntero->siguiente;
        puntero->siguiente = nodo;
    }
    ++lista->longitud;
}
Libro * Obtener(int n, Lista* lista){
    if(lista->cabeza == NULL){
        return NULL;
    } else{
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion<n && puntero->siguiente){
            puntero = puntero->siguiente;
            posicion++;
        }
        if (posicion != n){
            return NULL;
        } else
        return &puntero->libro;
    }
}
int Contar(Lista* lista){
    return lista->longitud;
}
int EstaVacia(Lista* lista){
    return lista->cabeza == NULL;
}
void EliminarPrin(Lista* lista){
    if (lista->cabeza) {
        Nodo *eliminado = lista->cabeza;
        lista->cabeza = lista->cabeza->siguiente;
        DestruirNodo(eliminado);
        lista->longitud++;
    }
}
void EliminarFin(Lista* lista){
    if (lista->cabeza){
        if (lista->cabeza->siguiente) {
            Nodo *puntero = lista->cabeza;
            while (puntero->siguiente->siguiente) {
                puntero = puntero->siguiente;
            }
            Nodo* eliminado = puntero->siguiente;
            puntero->siguiente = NULL;
            DestruirNodo(eliminado);
            lista->longitud--;
        } else{
            Nodo* eliminado = lista->cabeza;
            lista->cabeza = NULL;
            DestruirNodo(eliminado);
            lista->longitud--;
        }
    }
}
void eliminarElementoN(int n, Lista* lista){
    if (lista->cabeza){
        if(n == 0){
            Nodo* eliminado = lista->cabeza;
            lista->cabeza = lista->cabeza->siguiente;
            DestruirNodo(eliminado);
            lista->longitud--;
        }
        else if (n < lista->longitud){
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion < (n-1)){
            puntero = puntero->siguiente;
            posicion++;
        }
        Nodo* eliminado = puntero->siguiente;
        puntero->siguiente = eliminado->siguiente;
        DestruirNodo(eliminado);
        lista->longitud--;
        }
    }
}
int addVertices(Grafo *g, char vertice[20]);
void initGrafo(Grafo *g);
int findVertice(Grafo grafo, char vertice[20]);
int addEdge(Grafo *g, char verticeSource[20], char verticeDestinity[20]);
void printGrafo(Grafo grafo);
int deleteVertices(Grafo *g,char verticeDestiny[20]);
int deleteEdge(Grafo *g, char verticeSource[20], char verticeDestiny[20]);
void recorridoProfundidad(Grafo *g, char verticeOrigen[20]);
void recorridoAmplitud(Grafo *g, char verticeOrigen[20]);
int main(){
    Grafo grafo;
    int relacion;

    initGrafo(&grafo);

    addVertices(&grafo, "A");
    addVertices(&grafo, "B");
    addVertices(&grafo, "C");
    addVertices(&grafo, "D");

    for (int i = 0; i < grafo.size; ++i){
        for (int j = 0; j < grafo.size; ++j) {
            printf("%s tiene relacion con %s", grafo.vertices[i], grafo.vertices[j]);
            scanf("%d", &relacion);
            if(relacion == 1)
            addEdge(&grafo, grafo.vertices[i], grafo.vertices[j]);
        }
    }

    printGrafo(grafo);
    deleteEdge(&grafo, "A","D");
    deleteVertices(&grafo, "B");
    printGrafo(grafo);
    recorridoAmplitud(&grafo, 'A');
    recorridoProfundidad(&grafo, 'A');
    return 0;
}
void initGrafo(Grafo *g){
    g->size = 0;
}
int addVertices(Grafo *g, char vertice[20]){
    if(g->size < GRAPH_CAPACITY){
        strcpy(g->vertices[g->size], vertice);
        for (int i = 0; i < GRAPH_CAPACITY; ++i) {
            g->edges[i][g->size] = 0;
        }
        for (int i = 0; i < GRAPH_CAPACITY; ++i) {
            g->edges[g->size][i] = 0;
        }
        g->size++;
    }
}
int findVertice(Grafo grafo, char vertice[20]){
    int i;
    int result = -1;

    for ( i = 0; i < grafo.size && result == -1; ++i) {
        if(strcmp(grafo.vertices[i], vertice) == 0){
            result = i;
        }
    }

    return result;
}
int addEdge(Grafo *g, char verticeSource[20], char verticeDestinity[20]){
    int posSource = findVertice(*g, verticeSource);
    int posDestiny = findVertice(*g, verticeDestinity);

    if(posSource != -1 && posDestiny != -1){
        g->edges[posSource][posDestiny] = 1;
        g->edges[posDestiny][posSource] = 1;
        return 1;
    }
    return 0;
}
void printGrafo(Grafo grafo){
    printf("\t");
    for (int i = 0; i < grafo.size; ++i) {
        printf("%s\t", grafo.vertices[i]);
    }
    printf("\n");
    for (int i = 0; i < grafo.size; ++i) {
        printf("%s\t", grafo.vertices[i]);
        for (int j = 0; j < grafo.size; ++j) {
            printf("%d\t", grafo.edges[i][j]);
        }
        printf("\n");
    }
}
int deleteVertices(Grafo *g,char verticeDestiny[20]){
    int posDestiny = findVertice(*g, verticeDestiny);
    if(posDestiny != -1) {
        --g->size;
        for (int i = posDestiny; i < g->size; ++i){
            strcpy(g->vertices[i], g->vertices[i + 1]);
        }
        for (int i = 0; i <= g->size;i++){
            if(posDestiny <= i){
                for (int j = 0; j <= g->size; ++j) {
                    g->edges[i][j] = g->edges[i+1][j];
                }
            }
        }
        for (int i = 0; i <= g->size; ++i) {
            for (int j = 0; j <= g->size; ++j) {
                if(j>=posDestiny){
                    g->edges[i][j] = g->edges[i][j+1];
                }
            }
        }
        return 1;
    }
    return 0;
}
int deleteEdge(Grafo *g, char verticeSource[20], char verticeDestiny[20]){
    int posSource = findVertice(*g, verticeSource);
    int posDestiny = findVertice(*g, verticeDestiny);

    if(posSource != -1 && posDestiny != -1){
        g->edges[posSource][posDestiny] = 0;
        g->edges[posDestiny][posSource] = 0;
        return 1;
    }
}
void recorridoAmplitud(Grafo *g, char verticeOrigen[20]){



}
void recorridoProfundidad(Grafo *g, char verticeOrigen[20]){
    int vOrigen = findVertice(*g,verticeOrigen);
    Cola cola;
    if(vOrigen != -1){
        inicializaCola(&cola);
        while (!estaVacia(cola)){
            char vActual = inserta(&cola, vActual);
            elimina(&cola, vActual);

        }
    }
    else{
        printf("El vertice no existe");
    }
}