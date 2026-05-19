#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void **dados; //Fila de prioridade
    int tamanho;
    int capacidade;
} Heap;

void troca(void **x, void **y);

bool ehMenorInt(int* a, int* b);

void heapifyUp(Heap* h, int i);

void heapifyDown(Heap* h, int i);

void insereHeap(Heap* h, void* dado);

void* extraiMin(Heap* h);

void *mallocSafe(size_t nbytes);

    

