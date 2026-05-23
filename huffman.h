typedef struct no {
    unsigned char chave;
    int frequencia;
    
    struct no* esq;
    struct no* dir;
} NoHuffman;

bool ehMenorNo(void* a, void*b);

void contaFrequencia(FILE** arquivo, int vetorFrequencia[256]);

void imprimeFrequencia(int vetorFrequencia[256]);

NoHuffman* criaNoHuffman(int posicao, int frequencia);

NoHuffman* constroiArvore(int vetorFrequencia[256]);

void criaCodigoHuffman(NoHuffman* raiz, int profundidade, char* codigo, unsigned char* tabela[256][256]);

void imprimeArvore(NoHuffman* raiz, int profundidade);

void formataNome(char* nomeArquivo);

FILE* criaArquivoSaida(char* nomeArquivoSaida);

void comprimeArquivo(char* nomeArquivoLeitura, char* nomeArquivoSaida, int* vetorFrequencia[256], NoHuffman* raiz);

void liberaArvore(NoHuffman* raiz);