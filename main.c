#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"
#include <heap.h>

int main () {
    int vetorFrequencia[256] = {0};
    int opcao, aux = 0;
    NoHuffman* raiz = NULL;

    do {
        printf("\n =-=-= Menu de opcoes =-=-= \n");
        printf("1 - Comprimir um arquivo\n");
        printf("2 - Contagem de ocorrencias\n");
        printf("3 - Imprimir o Codigo de Huffman\n");
        printf("4 - Descomprimir um arquivo\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                char* nomeArquivoEntrada;
                char* nomeArquivoSaida;
                
                printf("Digite o nome do arquivo de entrada: ");
                fgets(nomeArquivoEntrada, 100, stdin);
                printf("Digite o nome do arquivo de saida: ");
                fgets(nomeArquivoSaida, 100, stdin);

                // Cria arquivo saida formatado
                criaArquivoSaida(nomeArquivoSaida);

                //Inicia a compressao do arquivo
                comprimeArquivo(nomeArquivoEntrada, nomeArquivoSaida, &vetorFrequencia, raiz);

                printf("Compressao concluida!\n");
                aux = 1;
                break;

            case 2:
                if (!aux) {
                    printf("Erro! Voce ainda nao compactou um arquivo\n");
                    break;
                }
                
                // Caso ja tenha passado pela opcao 1, imprime as frequencias de cada caracter na tela
                printf(" =-= Imprimindo Frequencias =-= \n");
                imprimeFrequencia(&vetorFrequencia);
                break;
            
            case 3:
                if (!aux) {
                    printf("Erro! Voce ainda nao compactou um arquivo\n");
                    break;
                }
                printf(" =-= Imprimindo Arvore de Huffman =-= \n");

                // Caso ja tenha passado pela opcao 1, imprime a arvore na tela
                imprimeArvore(raiz, 0);
                break;
            case 4:
                // Falta implementar

            case 5:
                printf("Encerrando o programa!\n");
                exit(0);
            
            default:
                printf("Opcao Invalida! Tente novamente\n");
                break;
        }
    } while (opcao != 5);
}