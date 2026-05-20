#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "huffman.h"


//Callback para o heap genérico
bool ehMenorNo(void* a, void* b) {
    NoHuffman* noA = (NoHuffman*)a;
    NoHuffman* noB = (NoHuffman*)b;
    return noA.frequencia < noB.frequencia;
}

void contaFrequencia(FILE* arquivoLeitura, int vetorFrequencia[256]) {
    int caractere;
    
    // Adiciona-se 1 à posição referente ao caractere no vetor de Frequências:
    while ((caractere = fgetc(arquivoLeitura)) != EOF) {
        vetorFrequencia[caractere]++;
    }
}

NoHuffman* criaNoHuffman(int chave, int frequencia) {
    NoHuffman* novoNo = mallocSafe(sizeof(NoHuffman));

    novoNo->chave = (unsigned char)chave;
    novoNo->frequencia = frequencia;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    
    return novoNo;
}

NoHuffman* constroiArvore(int vetorFrequencia[256]) {
    Heap h;
    criaHeap(&h, 256);

    for (int i = 0; i < 256; i++) {
        if (vetorFrequencia[i] > 0) {
            NoHuffman* novoNo = criaNoHuffman(i, vetorFrequencia[i]);
            insereHeap(&h, novoNo, ehMenorNo);
        }
    }

    while (h.tamanho > 1) {
        NoHuffman* menor1 = (NoHuffman*) extraiMin(&h, ehMenorNo);
        NoHuffman* menor2 = (NoHuffman*) extraiMin(&h, ehMenorNo);
        NoHuffman* novoNo = criaNoHuffman('\0', menor1->frequencia + menor2->frequencia);
        novoNo->esq = menor1;
        novoNo->dir = menor2;
        insereHeap(&h, novoNo, ehMenorNo);
    }
    return (NoHuffman*) h.dados[1];
}

void criaCodigo(NoHuffman* raiz, int profundidade, char* codigo, unsigned char tabela[256][256]){

    if (raiz == NULL) return;

    // Encontrou o nó folha
    if (raiz->dir == NULL && raiz->esq == NULL) {

        // Preenche todo o vetor correspondente à posição do caractere com seu devido código
        for (int i = 0; i <= profundidade; i++) {
            tabela[raiz->chave][i] = codigo[i];
        }
        tabela[raiz->chave][profundidade] = '\0';
    }

    if (raiz->esq != NULL) {
        codigo[profundidade] = '0';
        criaCodigo(raiz->esq, profundidade + 1, codigo, tabela);
    }
    if (raiz->dir!= NULL) {
        codigo[profundidade] = '1';
        criaCodigo(raiz->dir, profundidade + 1, codigo, tabela);
    }
}

void liberaArvore(NoHuffman* raiz) {
    if (raiz == NULL) return;
    
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);

    free(raiz);
}
