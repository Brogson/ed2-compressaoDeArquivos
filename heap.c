#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "huffman.h"

/* Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html */
void *mallocSafe(size_t nbytes) {
    void *ptr = malloc(nbytes);
    if (ptr == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }
    return ptr;
}

void troca(void **x, void **y) {
    void *temp = *x;
    *x = *y;
    *y = temp;
}

bool ehMenorInt(int* a, int* b) {
    return *a < *b;
}

void criaHeap(Heap* h, int capacidade) {
    h->dados = (void**) mallocSafe(capacidade * sizeof(void*));
    h->tamanho = 0;
    h->capacidade = capacidade + 1;
}

void heapifyUp(Heap* h, int i) {
    int pai = i / 2;
    if (i > 1 && ehMenorInt(h->dados[i], h->dados[pai])) {
        troca(&h->dados[i], &h->dados[pai]);
        heapifyUp(h, pai);
    }
}

void heapifyDown(Heap* h, int i) {
    int esq = 2 * i;
    int dir = 2 * i + 1;
    int menor = i;
    
    if (esq <= h->tamanho && h->dados[esq] < h->dados[i]) {
        menor = esq;
    }
    
    else if (dir <= h->tamanho && h->dados[dir] < h->dados[i]) {
        menor = dir;
    }

    if (menor != i) {
        troca(h->dados[menor], h->dados[i]);
        heapifyDown(h, menor);
    }
}

void insereHeap(Heap* h, void* dado) {
    if (h == NULL || dado == NULL) {
        printf("Erro! Heap ou dado não existente...\n");
        return;
    }
    
    if (h->tamanho == h->capacidade) {
        printf("Heap cheio!\n");
        return;
    }

    h->dados[h->tamanho + 1] = dado;
    heapifyUp(h, h->tamanho);
    h->tamanho++;
}

void* extraiMin(Heap* h) {
    if (h != NULL && h->tamanho > 0) {
        void* raiz = h->dados[0];
        h->dados[1] = h->dados[h->tamanho];
        h->tamanho--;
        heapifyDown(h, 1);
        return raiz;
    }
    return NULL;
}

void liberaHeap(Heap* h) {
    if (h->dados != NULL) free(h->dados);
    free(h);
}