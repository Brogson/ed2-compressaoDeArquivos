#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"
#include "heap.h"


int main (void) {
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
        getchar();

        switch (opcao) {

            case 1:
                char nomeArquivoEntrada[100];
                char nomeArquivoSaida[100];
                
                if (raiz != NULL) liberaArvore(raiz);

                printf("Digite o nome do arquivo de entrada (.txt): ");
                fgets(nomeArquivoEntrada, 100, stdin);
                printf("Digite o nome do arquivo de saida: ");
                fgets(nomeArquivoSaida, 100, stdin);

                //Inicia a compressao do arquivo
                raiz = comprimeArquivo(nomeArquivoEntrada, nomeArquivoSaida, vetorFrequencia);

                printf("\nCompressao concluida!\n");
                aux = 1;
                break;
            
            case 2:
                if (!aux) {
                    printf("Erro! Voce ainda nao compactou um arquivo\n");
                    break;
                }
                
                // Caso ja tenha passado pela opcao 1, imprime as frequencias de cada caracter na tela
                printf("\n =-= Imprimindo Frequencias =-= \n");
                imprimeFrequencia(vetorFrequencia);
                break;
            
            case 3:
                if (!aux) {
                    printf("\nErro! Voce ainda nao compactou um arquivo\n");
                    break;
                }
                printf("\n =-= Imprimindo Arvore de Huffman =-= \n");

                // Caso ja tenha passado pela opcao 1, imprime a arvore na tela
                imprimeArvore(raiz, 0);
                break;
                
            case 4:
                if (raiz != NULL) liberaArvore(raiz); 
                char nomeArquivoComprimido[100];
                char nomeArquivoDescompactado[100];
                
                printf("Digite o nome do arquivo de entrada (.jlv): ");
                fgets(nomeArquivoComprimido, 100, stdin);
                printf("Digite o nome do arquivo de saida (.txt): ");
                fgets(nomeArquivoDescompactado, 100, stdin);

                // Retira o \n dos 2 nomes e chama a descompressao
                formataNome(nomeArquivoComprimido);
                formataNome(nomeArquivoDescompactado);

                descomprimeArquivo(nomeArquivoComprimido, nomeArquivoDescompactado);
                printf("\nDescompressao concluida!\n");
                break;

            case 5:
                printf("\nEncerrando o programa!\n");
                liberaArvore(raiz);
                exit(0);
            
            default:
                printf("\nOpcao Invalida! Tente novamente\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}