#include <stdio.h>
#include "cola.h"
#include "common.h"
#include "stack.h"
#include "string.h"

#define CIRCLE_SANDWICH 0
#define SQUARE_SANDWICH 1

void sell_sandwich(Cola *c, Stack *s);
int main() {
    Stack stack;
    Cola cola;
    Estudiante estudiante;
    int sandwich;
    char alumno[20];
    inicializaCola(&cola);
    setup(&stack);

    printf("Como estan ordenados los sandwich?\n");
    for (int i = 0; i < MAX; ++i) {
        printf("sandwich %d: ", i+1);
        scanf("%d",&sandwich);
        push(&stack, sandwich);
    }

    for (int i = 0; i < MAX; ++i) {
        printf("Dame el nombre del alumno %d: ",i+1);
        scanf("%s",&alumno);
        printf("Que tipo de sandwich quiere %s? ",alumno);
        scanf("%d",&sandwich);
        strcpy(estudiante.nombre, alumno);
        estudiante.sandwich = sandwich;
        inserta(&cola,estudiante);
    }

    sell_sandwich(&cola, &stack);
    return 0;
}

void sell_sandwich(Cola *c, Stack *s){
    Estudiante estudianteActual;
    int sandwichActual;

    while(estaVacia(*c) == 0){
        elimina(c, &estudianteActual);
        pop(s, &sandwichActual);

        printf("\n\tEl estudiante %s quiere un sandwich: %d  en la pila hay %d",estudianteActual.nombre, estudianteActual.sandwich, sandwichActual);
        if (estudianteActual.sandwich != sandwichActual){
            printf("\n\t No se pudo entregar, regresando el estudiante a la cola y el sandwich a la pila");
            inserta(c, estudianteActual);
            push(s, sandwichActual);
        } else{
            printf("\n\tEl sandwich se entrego ;)");
        }
    }
}
