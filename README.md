# Compactador de Arquivos com Algoritmo de Huffman

> Trabalho 1 — Estrutura de Dados II  
> Curso de Ciência da Computação

---

# Grupo

| Jonathan Alves Bispo da Paz |
| Leandro Brognoli Grazziotin |
| Victor da Rocha Toniato |

---

# Descrição

Implementação de um compactador e descompactador de arquivos de texto utilizando o **algoritmo de Huffman**, desenvolvido em linguagem C. O projeto inclui uma fila de prioridades genérica baseada em heap binário, utilizada como estrutura auxiliar na construção da árvore de Huffman.

---

# Compilação e Execução

# Pré-requisitos

- Sistema operacional **Linux**
- Compilador **GCC** instalado
- Utilitário **make**

# Comandos

```bash
# Compilar o projeto
make

# Compilar e executar
make run

# Remover arquivos objeto e executável
make clean
```

---

# Menu do Programa

Ao executar, o programa exibe o seguinte menu:

```
=-=-= Menu de Opcoes =-=-=
1. Comprimir arquivo
2. Exibir contagem de caracteres
3. Imprimir árvore de Huffman
4. Descomprimir arquivo
5. Sair
Escolha uma opcao:
```

# Opções

| Opção | Descrição |
|-------|-----------|
| **1** | Informa o arquivo `.txt` de entrada e o nome do arquivo comprimido de saída |
| **2** | Exibe tabela com a frequência de cada caractere do arquivo informado na opção 1 |
| **3** | Imprime a estrutura da árvore de Huffman gerada |
| **4** | Informa o arquivo comprimido e o nome do arquivo de saída descomprimido |
| **5** | Encerra o programa |

Vale ressaltar que as opções 2 e 3 só funcionam após a execução da opção 1.

---

# Módulos Implementados

# `heap.h` / `heap.c` — Fila de Prioridades Genérica

Implementação de um **heap binário mínimo** para tipos genéricos de dados utilizando `void*`. Principais funções:

- `criaHeap` — inicializa a estrutura
- `insereHeap` — insere um elemento e restaura a propriedade do heap
- `extraiMin` — remove e retorna o elemento de menor prioridade
- `destroiHeap` — libera a memória alocada

### `huffman.h` / `huffman.c` — Algoritmo de Huffman

Implementação completa do algoritmo. Principais funções:

- `contaFrequencias` — lê o arquivo e conta a ocorrência de cada caractere
- `constroiArvore` — usa a fila de prioridades para montar a árvore de Huffman
- `geraCodigosHuffman` — percorre a árvore e gera os códigos binários
- `compactaArquivo` — substitui os caracteres pelos códigos e grava o arquivo comprimido
- `descompactaArquivo` — lê o arquivo comprimido e reconstrói o texto original
- `imprimeArvore` — exibe a estrutura da árvore no terminal

---

# Exemplo de Saída

# Tabela de Frequências

```
Caractere | Frequência
----------+-----------
'a'       |     15
'b'       |      7
'e'       |     20
' '       |     12
```

# Árvore de Huffman

```
        [54]
       /    \
    [23]    [31]
    /  \    /  \
  a:15 b:8 e:20 ' ':11
```

# Códigos Gerados

```
'e' -> 10
'a' -> 00
' ' -> 11
'b' -> 01
```

---

# Observações

- O arquivo comprimido armazena a tabela de frequências no cabeçalho, permitindo a descompactação sem arquivos auxiliares.
- A implementação trata todos os caracteres ASCII, incluindo acentuação, espaços, tabulações e quebras de linha.
- Em caso de empate de frequência entre dois caracteres, a ordem de inserção é mantida.
