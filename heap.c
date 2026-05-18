#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "huffman.h"

void criaHeap(Heap* h, int capacidade){
    h->dados = (void**) malloc(capacidade * sizeof(void*));
    h->tamanho = 0;
    h->capacidade = capacidade;
}

void heapifyUp(Heap* h, int i) {
    int pai = (i - 1) / 2;
    if (i > 1 && h->ehMenor(h->dados[i], h->dados[pai])) {
        troca(&h->dados[i], &h->dados[pai]);
        heapifyUp(h, pai);
    }
}

void insereHeap(Heap* h, void* dado){
    if (h == NULL || dado == NULL) {
        printf("Erro! Heap ou dado não existente...\n");
        return;
    }
    
    if (h->tamanho == h->capacidade) {
        printf("Heap cheio!\n");
        return;
    }

    h->dados[h->tamanho] = dado;
    heapifyUp(h, h->tamanho);
    h->tamanho++;
}

void* extraiMin(Heap* h) {
    if (h != NULL && h->tamanho > 0) {
        void* raiz = h->dados[0];
        return raiz;
    }
}