//
// Created by Angel on 26/05/2022.
//

#include <stdio.h>
#define SET_CAPACITY 10

typedef struct
{
    int data[SET_CAPACITY];
    int size;
}Set;

void init_set(Set *s);
int add(Set *s, int value);
int find(Set set, int value);
int remov(Set *s, int value);
int exist(Set set, int value);
void intersect(Set setA,Set setB, Set *sC);
void printSet(Set set);
void unioon(Set setA,Set setB, Set *sC);
void complemento(Set setA,Set setB, Set *sC);
void diferencia(Set setB,Set setA, Set *sC);
int main()
{
    Set setA, setB, setC;

    init_set(&setA);
    add(&setA, 23);
    add(&setA,11);
    add(&setA, 16);
    add(&setA,5);
    add(&setA,7);

    init_set(&setB);
    add(&setB, 10);
    add(&setB,11);
    add(&setB, 21);
    add(&setB,5);

    init_set(&setC);

    printSet(setA);
    printSet(setB);
    printSet(setC);
    printf("~Interseccion~\n");
    intersect(setA, setB, &setC);
    printSet(setC);
    printf("~union~\n");
    unioon(setA, setB, &setC);
    printSet(setC);
    printf("~complemento~\n");
    complemento(setA, setB, &setC);
    printSet(setC);
    printf("~diferencia~\n");
    diferencia(setB,setA, &setC);
    printSet(setC);
    //remov(&setA, 1);

    //exist(setA, 1);
    //exist(setA, 14);
    return 0;
}
void unioon(Set setA,Set setB, Set *sC){
    for (int i = sC->size; i > 0 ; --i) {
        remov(sC, sC->data[i]);
    }
    init_set(sC);
    int e;
    for (int i = 0; i < setA.size; ++i) {
        add(sC, setA.data[i]);
    }

    for (int i = 0; i < setB.size; ++i) {
        e = exist(setA, setB.data[i]);
        if(e==0){
            add(sC, setB.data[i]);
        }
    }

}
void complemento(Set setA,Set setB, Set *sC)
{
    for (int i = sC->size; i > 0 ; --i) {
        remov(sC, sC->data[i]);
    }
    init_set(sC);
    int e;
    for (int i = 0; i < setB.size; ++i) {
        e = exist(setB, setA.data[i]);
        if(e==0){
            add(sC, setB.data[i]);
        }
    }
}
void diferencia(Set setB,Set setA, Set *sC){
    for (int i = sC->size; i == 0 ; --i) {
        remov(sC, sC->data[i]);
    }
    init_set(sC);
    int e;
    for (int i = 0; i < setA.size; ++i) {
        e = exist(setA, setB.data[i]);
        if(e==0){
            add(sC, setA.data[i]);
        }
    }
}
void printSet(Set set){
    printf("[");
    for (int i = 0; i < set.size; ++i) {
        printf("%d ",set.data[i]);
    }
    printf("]\n");
}
void intersect(Set setA,Set setB, Set *sC){
    int e;
    for (int index = 0; index < setA.size; ++index) {
        printf("set.data[%d] = %d\n", index, setA.data[index]);
        e = exist(setB, setA.data[index]);
        if(e==1){
            printf("%d existe en B\n", setA.data[index]);
            add(sC, setA.data[index]);
        }
    }
}
int exist(Set set, int value){
    int index = find(set, value);

    if(index == -1){
        return 0;
    }
    return 1;
}
int remov(Set *s, int value){
    int index = find(*s, value);

    if(index != -1){
        s->size;
        for ( ; index <= s->size -1 ; ++index) {
            s->data[index] = s->data[index+1];
        }
    }
}
void init_set(Set *s)
{
    s->size = 0;
}

int add(Set *s, int value)
{
    int exists = 0;
    int result = 0;
    if(s->size < SET_CAPACITY)
    {
        exists = find(*s, value);
        if(exists == -1){
            int i;
            for (i = s->size-1; i >= 0 && s->data[i] > value ; --i) {
                s->data[i + 1] = s->data[i];
            }

            s->data[i+1] = value;
            s->size++;
            result = 1;
        }
    }

    return result;
}

int find(Set set, int value){
    int inicio = 0, fin= set.size -1;
    int mitad, encontrar = 0;

    while (inicio<=fin && encontrar == 0){
        mitad = inicio + (fin - inicio) / 2;

        if(set.data[mitad] == value){
            encontrar= 1;
        } else if(set.data[mitad] > value)
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
