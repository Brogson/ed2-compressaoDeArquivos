#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"


/* Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html */
void *mallocSafe(size_t nbytes) {
    void *ptr = malloc(nbytes);
    if (ptr == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    return ptr;
}

void troca(void **x, void **y) {
    void* temp = *x;
    *x = *y;
    *y = temp;
}

void criaHeap(Heap* h, int capacidade) {
    h->tamanho = 0;
    h->capacidade = capacidade + 1; //Heap inicia da posição 1
    h->dados = (void**) mallocSafe(h->capacidade * sizeof(void*));
}

void heapifyUp(Heap* h, int i, bool (*ehMenor)(void*, void*)) {
    int pai = i / 2;
    if (i > 1 && ehMenor(h->dados[i], h->dados[pai])) {
        troca(&h->dados[i], &h->dados[pai]);
        heapifyUp(h, pai, ehMenor);
    }
}

void heapifyDown(Heap* h, int i, bool (*ehMenor)(void*, void*)) {
    int esq = 2 * i;
    int dir = 2 * i + 1;
    int menor = i;
    
    if (esq <= h->tamanho && ehMenor(h->dados[esq], h->dados[menor]))
        menor = esq;
    
    if (dir <= h->tamanho && ehMenor(h->dados[dir], h->dados[menor]))
        menor = dir;

    if (menor != i) {
        troca(&h->dados[menor], &h->dados[i]);
        heapifyDown(h, menor, ehMenor);
    }
}

void insereHeap(Heap* h, void* dado, bool (*ehMenor)(void*, void*)) {
    if (h == NULL || dado == NULL) {
        printf("Erro! Heap ou dado não existente...\n");
        return;
    }
    
    if (h->tamanho == h->capacidade) {
        printf("Heap cheio!\n");
        return;
    }

    h->dados[h->tamanho + 1] = dado;
    h->tamanho++;
    
    if (h->tamanho > 1)
        heapifyUp(h, h->tamanho, ehMenor);
}

void* extraiMin(Heap* h, bool (*ehMenor)(void*, void*)) {
    if (h != NULL && h->tamanho > 0) {
        void* raiz = h->dados[1];
        h->dados[1] = h->dados[h->tamanho];
        h->tamanho--;
        heapifyDown(h, 1, ehMenor);
        return raiz;
    }
    return NULL;
}

void liberaHeap(Heap* h) {
    if (h->dados != NULL) free(h->dados);
    free(h);
}
    