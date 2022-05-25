#include "common.h"

typedef struct estudiante{
    char nombre[MAX+1];
    int sandwich;
}Estudiante;

typedef struct cola{
    Estudiante datos[MAX + 1];
    int inicio;
    int fin;
}Cola;

void inicializaCola(Cola *c){
    c->inicio = 0;
    c->fin = 0;
}
int estaVacia(Cola cola){
    if(cola.inicio == cola.fin){
        return 1;
    }
    return 0;
}
int estaLlena(Cola cola){
    if(cola.fin == cola.inicio - 1 || (cola.inicio == 0 && cola.fin == MAX)){
        return 1;
    }

    return 0;
}
int inserta(Cola *c, Estudiante valor){
    if(estaLlena(*c) == 0){
        c->datos[c->fin] = valor;
        c->fin++;
        if(c->fin == MAX+1){
            c->fin=0;
        }
        //c->fin = (c->fin + 1) % (MAX + 1);
        return 1;
    }

    return 0;
}
int elimina(Cola *c, Estudiante *v){
    if(!estaVacia(*c)){
        *v = c->datos[c->inicio];
        c->inicio = (c->inicio + 1) % (MAX + 1);
        return 1;
    }
    return 0;
}