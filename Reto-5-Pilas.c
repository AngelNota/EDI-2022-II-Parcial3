#include "stack.h"
#include <stdio.h>
#include "common.h"
#include <string.h>

int comparar(Cadena *s, Cadena *T);
int main(){
    Stack stackS, stackT;
    Cadena s, T;
    char cadena[MAX];
    setup(&stackS);
    setup(&stackT);

    printf("Escribe una cadena con backspace: ");
    scanf("%s", cadena);
    strcpy(s.palabra, cadena);
    push(&stackS, s);

    printf("Escribe otra cadena con backspace: ");
    scanf("%s", cadena);
    strcpy(T.palabra, cadena);
    push(&stackT, T);


    if (comparar(&s, &T)){
        printf("1\n %s | %s",s,T);
    } else
        printf("0\n %s | %s",s,T);
    return 0;
}
int comparar(Cadena *s, Cadena *T){
    int ps = -1, pt = -1;
    for (int i = 0; i < strlen(s->palabra) ; ++i) {
        if (s->palabra[i] == '#' && ps != -1){
            ps -= 1;
        } else if (s->palabra[i] != '#'){
            s->palabra[i] = s->palabra[i];
            ps += 1;
        }
    }
    for (int i = 0; i < strlen(T->palabra); ++i) {
        if (T->palabra[i] == '#' && pt != -1){
            pt -= 1;
        } else if (T->palabra[i] != '#'){
            T->palabra[i] = T->palabra[i];
            pt += 1;
        }
    }

    if (pt != ps) {
        return 0;
    }
    else if (ps == -1 && pt == -1) {
        return 1;
    }
    else {
        for (int i = 0; i <= pt; i++) {
            if (s->palabra[i] != T->palabra[i]){
                return 0;
            }
        }
        return 1;
    }
}