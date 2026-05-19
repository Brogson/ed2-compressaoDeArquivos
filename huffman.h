typedef struct NoHuffman {
    unsigned char chave;
    int frequencia;
    
    NoHuffman* esq;
    NoHuffman* dir;
} NoHuffman;

void contaFrequencia(FILE* arquivo);

NoHuffman* criaNoHuffman(int posicao, int frequencia);