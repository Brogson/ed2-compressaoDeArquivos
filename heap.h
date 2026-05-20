typedef struct heap {
    void **dados; //Fila de prioridade
    int tamanho;
    int capacidade;
} Heap;

void criaHeap(Heap* h, int capacidade);

void heapifyUp(Heap* h, int i, bool (*ehMenor)(void*, void*));

void heapifyDown(Heap* h, int i, bool (*ehMenor)(void*, void*));

void insereHeap(Heap* h, void* dado, bool (*ehMenor)(void*, void*));

void* extraiMin(Heap* h, bool (*ehMenor)(void*, void*));

void troca(void **x, void **y);

void* mallocSafe(size_t nbytes);

    

