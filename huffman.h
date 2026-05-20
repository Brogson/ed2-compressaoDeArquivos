typedef struct no {
    unsigned char chave;
    int frequencia;
    
    struct no* esq;
    struct no* dir;
} NoHuffman;

bool ehMenorNo(void* a, void*b);

void contaFrequencia(FILE* arquivo);

NoHuffman* criaNoHuffman(int posicao, int frequencia);

NoHuffman* constroiArvore(int vetorFrequencia[256]);

void criaCodigo(NoHuffman* raiz, int profundidade, char* codigo, unsigned char tabela[256][256]);

void liberaArvore(NoHuffman* raiz);