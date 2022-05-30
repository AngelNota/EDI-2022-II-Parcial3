//
// Created by Angel on 26/05/2022.
//
#include <stdio.h>
#include <math.h>
#define MAX 15

typedef struct amigoss{
    int amigos[MAX + 1];
    int inicio;
    int fin;
}Cola;
void inicializaCola( Cola *c);
int estaLlena(Cola cola);
int estaVacia(Cola cola);
int inserta(Cola *c, int valor);
int find(Cola set, int value);
int elimina(Cola *c, int v);
int juego(Cola *cola,int k,int amicos);

int main(){
    int amicos, k;
    Cola amigoss;
    inicializaCola( &amigoss);

    printf("Cuantos amigos van a jugar?");
    scanf("%d",&amicos);
    int a=0;
    for (int i = 0; i < amicos; ++i) {
        a=a+1;
        inserta(&amigoss, a);
    }
    printf("En que turnos parara?");
    scanf("%d",&k);

    juego(&amigoss, k, amicos);
    return 0;
}
int juego(Cola *cola,int k,int amicos){
    int inicio = k, fin,aux ;
    fin =  cola->fin;
    while (fin>1){

        if(inicio>fin){
            aux = inicio - amicos;
            inicio = fabs(aux);
            elimina(cola, inicio);
        }else {
            elimina(cola, inicio);
        }
        printf("El jugador eliminado es el de la posicion: %d\n", inicio);
        inicio = inicio + k;
        --fin;
    }
    printf("El ganador es el jugador: %d",cola->amigos[0]);
}
void inicializaCola(Cola *c){
    c->inicio = 0;
    c->fin = 0;
}
int estaLlena(Cola cola){
    if(cola.fin == cola.inicio - 1 || (cola.inicio == 0 && cola.fin == MAX)){
        return 1;
    }

    return 0;
}
int estaVacia(Cola cola){
    if(cola.inicio == cola.fin){
        return 1;
    }
    return 0;
}
int inserta(Cola *c, int valor){
    if(estaLlena(*c) == 0){
        c->amigos[c->fin] = valor;
        c->fin++;
        if(c->fin == MAX+1){
            c->fin=0;
        }
        //c->fin = (c->fin + 1) % (MAX + 1);
        return 1;
    }

    return 0;
}
int elimina(Cola *c, int v){
    int i = find(*c, v);
    if(i != -1){
        c->fin;
        for (; i <= c->fin -1 ; ++i) {
            c->amigos[i] = c->amigos[i+1];
        }
    }
}
int find(Cola set, int value){
    int inicio = 0, fin= set.fin -1;
    int mitad, encontrar = 0;

    while (inicio<=fin && encontrar == 0){
        mitad = inicio + (fin - inicio) / 2;

        if(set.amigos[mitad] == value){
            encontrar= 1;
        } else if(set.amigos[mitad] > value)
        {
            fin = mitad -1;
        } else{
            inicio = mitad + 1;
        }
    }
    if(encontrar == 1)
        return mitad;
    else
        return -1;
}