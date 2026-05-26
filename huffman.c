#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include "huffman.h"


//Callback para o heap genérico
bool ehMenorNo(void* a, void* b) {
    NoHuffman* noA = (NoHuffman*)a;
    NoHuffman* noB = (NoHuffman*)b;
    return noA->frequencia < noB->frequencia;
}

void verificaArquivo(FILE* arquivoEntrada) {
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
}

void contaFrequencia(FILE* arquivoLeitura, int* vetorFrequencia) {
    int caractere;
    
    // Adiciona-se 1 à posição referente ao caractere no vetor de Frequências:
    while ((caractere = fgetc(arquivoLeitura)) != EOF) {
        vetorFrequencia[(unsigned char)caractere]++;
    }
}

void imprimeFrequencia(int vetorFrequencia[256]) {
    for (int i = 0; i < 256; i++) {
        if (vetorFrequencia[i] > 0) {
            if (i == '\n') {
                printf("\tASCII: %d, Caractere: \\n, Frequencia: %d\n", i, vetorFrequencia[i]);
            }
            else if (i == '\t') {
                printf("\tASCII: %d, Caractere: \\t, Frequencia: %d\n", i, vetorFrequencia[i]);
            }
            else if (i == '\r') {
                printf("\tASCII: %d, Caractere: \\r, Frequencia: %d\n", i, vetorFrequencia[i]);
            }
            else
                printf("\tASCII: %d, Caractere: %c, Frequencia: %d\n", i, i, vetorFrequencia[i]);
        }
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
    Heap* h = mallocSafe(sizeof(Heap));
    criaHeap(h, 256);

    for (int i = 0; i < 256; i++) {
        if (vetorFrequencia[i] > 0) {
            NoHuffman* novoNo = criaNoHuffman(i, vetorFrequencia[i]);
            insereHeap(h, novoNo, ehMenorNo);
        }
    }

    while (h->tamanho > 1) {
        NoHuffman* menor1 = (NoHuffman*) extraiMin(h, ehMenorNo);
        NoHuffman* menor2 = (NoHuffman*) extraiMin(h, ehMenorNo);
        NoHuffman* novoNo = criaNoHuffman('\0', menor1->frequencia + menor2->frequencia);
        novoNo->esq = menor1;
        novoNo->dir = menor2;
        insereHeap(h, novoNo, ehMenorNo);
    }

    NoHuffman* raiz = (NoHuffman*) extraiMin(h, ehMenorNo);
    liberaHeap(h);
    return raiz;
}

void criaTabelaCodigos(NoHuffman* raiz, int profundidade, char* codigo, unsigned char tabela[256][256]){
    
    if (raiz == NULL) return;

    // Encontrou o no folha
    if (raiz->dir == NULL && raiz->esq == NULL) {
        // Preenche todo o vetor correspondente a posicao do caractere com seu devido codigo
        for (int i = 0; i <= profundidade; i++) {
            tabela[raiz->chave][i] = codigo[i];
        }
        tabela[raiz->chave][profundidade] = '\0';
    }

    if (raiz->esq != NULL) {
        codigo[profundidade] = '0';
        criaTabelaCodigos(raiz->esq, profundidade + 1, codigo, tabela);
    }

    if (raiz->dir!= NULL) {
        codigo[profundidade] = '1';
        criaTabelaCodigos(raiz->dir, profundidade + 1, codigo, tabela);
    }
}

void imprimeArvore(NoHuffman* raiz, int profundidade) {
    if (raiz == NULL) return;

    imprimeArvore(raiz->dir, profundidade + 1);

    for (int i = 0; i < profundidade; i++) {
        printf("        ");
    }

    if (raiz->esq == NULL && raiz->dir == NULL) {
        if (raiz->chave == '\n') {
            printf("[\\n : %d]\n", raiz->frequencia);
        }
        else if (raiz->chave == '\t') {
            printf("[\\t : %d]\n", raiz->frequencia);
        }
        else if (raiz->chave == '\r') {
            printf("[\\r : %d]\n", raiz->frequencia);
        }
        else {
            printf("[%c : %d]\n", raiz->chave, raiz->frequencia);
        }
    }

    else {
        printf("[%d]\n", raiz->frequencia);
    }

    imprimeArvore(raiz->esq, profundidade + 1);
}

void formataNome(char* nomeArquivo) {
    int i = 0;
    while (nomeArquivo[i] != '\n') {
        i++;
    }
    nomeArquivo[i] = '\0';
}

FILE* criaArquivoSaida(char* nomeArquivoSaida) {
    nomeArquivoSaida = strcat(nomeArquivoSaida, ".jlv");

    // Cria o arquivo para escrita binaria e retorna aberto
    FILE* arquivoSaida = fopen(nomeArquivoSaida, "wb");
    verificaArquivo(arquivoSaida);
    return arquivoSaida;
}

NoHuffman* comprimeArquivo(char* nomeArquivoLeitura, char* nomeArquivoSaida, int vetorFrequencia[256]) {

    FILE* arquivoLeitura = fopen(nomeArquivoLeitura, "rb");
    verificaArquivo(arquivoLeitura);
    contaFrequencia(arquivoLeitura, vetorFrequencia);

    NoHuffman* raiz = constroiArvore(vetorFrequencia);
    unsigned char tabelaCodigos[256][256];
    char codigo[256];

    memset(tabelaCodigos, 0, sizeof(tabelaCodigos));

    criaTabelaCodigos(raiz, 0, codigo, tabelaCodigos);

    FILE* arquivoSaida = criaArquivoSaida(nomeArquivoSaida);

    // Escreve cabecalho no arquivo de saida
    fwrite(vetorFrequencia, sizeof(int), 256, arquivoSaida);

    // Retorna o ponteiro para o inicio do arquivo
    rewind(arquivoLeitura);

    int c, contadorBits = 0;
    unsigned char aux = 0;
    while ((c = fgetc(arquivoLeitura)) != EOF) {
        
        // Representacao do caractere em bits
        int tamanho = strlen((char*) tabelaCodigos[c]);
        for (int i = 0; i < tamanho; i++) {

            // Transforma o codigo do caractere em inteiro 0 e 1
            int bit = tabelaCodigos[c][i] - '0';
            
            // Move o auxiliar para esquerda e adiciona o bit referente ao codigo do caractere 
            aux = (aux << 1) | bit;
            contadorBits++;
            
            if (contadorBits == 8) {
                fputc(aux, arquivoSaida);
                aux = 0;
                contadorBits = 0;
            }
        }
    }

    // Caso tenha sobrado algum bit
    if (contadorBits > 0) {
        aux = aux << (8 - contadorBits);
        fputc(aux, arquivoSaida);
    }

    fclose(arquivoLeitura);
    fclose(arquivoSaida);
    return raiz;
}

NoHuffman* descomprimeArquivo(char* nomeArquivoLeitura, char* nomeArquivoSaida) {

    FILE* arquivoLeitura = fopen(nomeArquivoLeitura, "rb");
    verificaArquivo(arquivoLeitura);
    
    int vetorFrequencia[256];
    fread(vetorFrequencia, sizeof(int), 256, arquivoLeitura);

    NoHuffman* raiz = constroiArvore(vetorFrequencia);
    
    FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
    verificaArquivo(arquivoSaida);
    
    int c;
    NoHuffman* atual = raiz;

    unsigned char aux;
    int contadorBits;
    int caracteresEscritos = 0;

    while((c = fgetc(arquivoLeitura)) != EOF && caracteresEscritos < raiz->frequencia) {
        aux = 0;
        contadorBits = 0;

        while (contadorBits < 8 && caracteresEscritos < raiz->frequencia) {
            //Caso a raiz seja folha, ou seja, apenas um caractere no txt original:
            if (raiz->esq == NULL && raiz->dir == NULL) {
                fputc(atual->chave, arquivoSaida);
                caracteresEscritos++;
                contadorBits++;
            }

            else {
               aux = (c >> (7 - contadorBits)) & 1;
                contadorBits++;

                if (aux == 0) atual = atual->esq;
                else atual = atual->dir;
        
                if (atual->dir == NULL && atual->esq == NULL) {
                    fputc(atual->chave, arquivoSaida);
                    atual = raiz;
                    caracteresEscritos++;
                } 
            }
        }
    }

    fclose(arquivoLeitura);
    fclose(arquivoSaida);

    return raiz;
}

void liberaArvore(NoHuffman* raiz) {
    if (raiz == NULL) return;
    
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
}