typedef struct NoHuffman {
    char chave;
    int frequencia;
} NoHuffman;

void contaFrequencia(FILE* arquivo);

NoHuffman* criaNoHuffman(int posicao, int frequencia);