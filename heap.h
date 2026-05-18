#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados; //Fila de prioridade
    int tamanho;
    int capacidade;
    int (*ehMenor)(void*, void*);
} Heap;

void troca(void **x, void **y) {
    void *temp = *x;
    *x = *y;
    *y = temp;
}


    

