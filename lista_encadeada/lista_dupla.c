#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura com dois ponteiros
typedef struct No {
    int valor;           // Armazena o dado
    struct No* proximo;  // Aponta para o sucessor
    struct No* anterior; // Aponta para o antecessor (a novidade!)
} No;

// Função para inserir no início da lista
void inserir_inicio(No** cabeca, int valor) {
    // Aloca memória para o novo nó na Heap
    No* novo = (No*)malloc(sizeof(No));
    // Atribui o valor ao novo nó
    novo->valor = valor;
    // O próximo do novo nó será a antiga cabeça
    novo->proximo = *cabeca;
    // Como ele está entrando no início, o anterior é sempre NULL
    novo->anterior = NULL;

    // Se a lista não estiver vazia, precisamos atualizar o anterior da antiga cabeça
    if (*cabeca != NULL) {
        (*cabeca)->anterior = novo;
    }
    
    // O ponteiro da cabeça agora aponta oficialmente para o novo nó
    *cabeca = novo;
}

// Função para imprimir do início ao fim
void imprimir_direto(No* no) {
    printf("Caminho Direto: ");
    while (no != NULL) {
        printf("%d -> ", no->valor);
        no = no->proximo; // Vai para frente
    }
    printf("NULL\n");
}

// Função para imprimir do fim ao início
void imprimir_reverso(No* no) {
    // 1. Primeiro, precisamos chegar ao último nó
    if (no == NULL) return; // Se a lista estiver vazia, sai da função

    No* ultimo = no;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo; // Caminha até o fim da lista
    }

    // 2. Agora que estamos no último, usamos o 'anterior' para voltar
    printf("Caminho Reverso: ");
    while (ultimo != NULL) {
        printf("%d -> ", ultimo->valor);
        ultimo = ultimo->anterior; // Vai para trás!
    }
    printf("NULL\n");
}

// Liberação de memória (importante para o Valgrind!)
void liberar_lista(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp); // Libera o nó atual
    }
}

int main() {
    No* minha_lista = NULL; // Inicializa lista vazia

    inserir_inicio(&minha_lista, 10); // Lista: 10
    inserir_inicio(&minha_lista, 20); // Lista: 20 <-> 10
    inserir_inicio(&minha_lista, 30); // Lista: 30 <-> 20 <-> 10

    imprimir_direto(minha_lista);
    imprimir_reverso(minha_lista);

    liberar_lista(minha_lista); // Limpa a memória
    return 0;
}

// lista_encadeada/"lista_dupla"

// Caminho Direto: 30 -> 20 -> 10 -> NULL
// Caminho Reverso: 10 -> 20 -> 30 -> NULL

// Diagrama Estrutural: Lista Duplamente Encadeada

//       PONTEIRO          NÓ [0]                NÓ [1]                NÓ [2]
//        CABEÇA          (Head)                (Meio)                (Tail)
//       +-------+     +----------+          +----------+          +----------+
//       |       |     | ant: NULL| <------+ | ant: [0] | <------+ | ant: [1] |
//       | [0] ------> | val: 30  |          | val: 20  |          | val: 10  |
//       |       |     | prox: [1] ------>   | prox: [2] ------>   | prox:NULL|
//       +-------+     +----------+          +----------+          +----------+

// Detalhamento dos Elos (Passo a Passo)

// 1. A Cabeça (Head):

// É um ponteiro externo que apenas guarda onde a lista começa. No nosso caso, ela aponta para o endereço do Nó [0].

// 2. O Primeiro Nó (Valor 30):

//  - anterior: Aponta para NULL (não existe nada antes do primeiro).

//  - proximo: Guarda o endereço de memória do Nó [1].

// 3. O Nó do Meio (Valor 20):

//  - anterior: Aponta de volta para o Nó [0].

//  - proximo: Aponta para frente, para o Nó [2].

//  - Note que ele é o único que "segura as mãos" de dois vizinhos ao mesmo tempo.

// 4. O Último Nó (Valor 10):

//  - anterior: Aponta de volta para o Nó [1].

//  - proximo: Aponta para NULL, indicando que a lista terminou.

// Por que os NULL são vitais?

//  - O NULL no proximo: Diz ao seu laço while (na função de imprimir ou buscar) que é hora de parar de avançar.

//  - O NULL no anterior: Diz à sua função de imprimir_reverso ou de remoção que você chegou ao início da lista e 
// não há mais para onde voltar.

