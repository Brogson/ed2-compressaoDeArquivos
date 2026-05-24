typedef struct no {
    unsigned char chave;
    int frequencia;
    struct no* esq;
    struct no* dir;
} NoHuffman;

bool ehMenorNo(void* a, void*b);

void verificaArquivo(FILE* arquivo);

void contaFrequencia(FILE** arquivo, int** vetorFrequencia);

void imprimeFrequencia(int vetorFrequencia[256]);

void criaTabelaCodigos(NoHuffman* raiz, int profundidade, char* codigo, unsigned char* tabela[256][256]);

void imprimeArvore(NoHuffman* raiz, int profundidade);

void formataNome(char* nomeArquivo);

void comprimeArquivo(char* nomeArquivoLeitura, char* nomeArquivoSaida, int vetorFrequencia[256]);

void descomprimeArquivo(char* arquivoLeitura, char* arquivoSaida);

void liberaArvore(NoHuffman* raiz);

FILE* criaArquivoSaida(char* nomeArquivoSaida);

NoHuffman* criaNoHuffman(int posicao, int frequencia);

NoHuffman* constroiArvore(int vetorFrequencia[256]);