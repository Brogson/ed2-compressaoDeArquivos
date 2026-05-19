#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

// Vetor para registro das frequencias de cada caractere em relacao à tabela ASCII estendida
int vetorFrequencia[256] = {0};

void contaFrequencia(FILE* arquivo) {
    int caractere;
    
    // Adiciona-se 1 à posição referente ao caractere no vetor de Frequências:
    while ((caractere = fgetc(arquivo)) != EOF) {
        vetorFrequencia[caractere]++;
    }
}

NoHuffman* criaNoHuffman(int posicao, int frequencia) {
    NoHuffman *novoNo = mallocSafe(sizeof(NoHuffman));

    if (novoNo == NULL) return NULL;
    
    novoNo->chave = (char) posicao;
    novoNo->frequencia = frequencia;

    return novoNo;
}