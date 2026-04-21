# 📚 Guia Definitivo: Listas Encadeadas em C

Este documento é um registro técnico detalhado sobre estruturas dinâmicas, focando na manipulação de ponteiros e gestão de memória na Heap.

---

## 1. Lista Encadeada Simples (Singly Linked List)

### 📋 Situação Prática: Escalonador de Tarefas
**Cenário:** Um sistema gerencia uma fila de processos. Novas tarefas entram no início (prioridade) ou fim. O sistema deve remover tarefas por ID quando finalizadas.

### 🖼️ Diagrama Estrutural (Simples)

```text
   PONTEIRO          NÓ [0]                NÓ [1]                NÓ [2]
    CABEÇA          (Head)                (Meio)                (Tail)
   +-------+     +----------+          +----------+          +----------+
   |       |     | val: 30  |          | val: 20  |          | val: 10  |
   | [0] ------> |          |          |          |          |          |
   |       |     | prox: [1] ------>   | prox: [2] ------>   | prox:NULL|
   +-------+     +----------+          +----------+          +----------+

   💻 Código Completo e Comentado

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int id;
    struct No* proximo;
} No;

// Inserção no início: O(1)
void inserir_inicio(No** cabeca, int id) {
    No* novo = (No*)malloc(sizeof(No)); // Aloca memória para o novo nó
    novo->id = id;                      // Define o valor
    novo->proximo = *cabeca;            // O novo aponta para onde a cabeça apontava
    *cabeca = novo;                     // A cabeça agora aponta para o novo nó
}

// Remoção por ID: O(n)
void remover(No** cabeca, int id) {
    No *atual = *cabeca, *anterior = NULL;
    while (atual != NULL && atual->id != id) { // Busca o ID
        anterior = atual;                      // Salva o nó anterior
        atual = atual->proximo;                // Avança
    }
    if (atual == NULL) return;                 // Valor não encontrado
    if (anterior == NULL) *cabeca = atual->proximo; // Remoção na cabeça
    else anterior->proximo = atual->proximo;        // Remendo (pula o nó)
    free(atual);                               // Libera memória
}

void imprimir(No* n) {
    while (n != NULL) {
        printf("[%d] -> ", n->id);
        n = n->proximo;
    }
    printf("NULL\n");
}

void limpar(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    No* lista = NULL; // Inicializa a lista vazia

    printf("--- TESTE LISTA SIMPLES (Escalonador) ---\n");

    // Inserindo processos
    inserir_inicio(&lista, 10); // Lista: 10
    inserir_inicio(&lista, 20); // Lista: 20 -> 10
    inserir_inicio(&lista, 30); // Lista: 30 -> 20 -> 10
    
    printf("1. Fila Inicial: ");
    imprimir(lista);

    // Teste 1: Remover do meio (ID 20)
    remover(&lista, 20);
    printf("2. Após remover ID 20 (meio): ");
    imprimir(lista);

    // Teste 2: Remover do início (ID 30 - a nova cabeça)
    remover(&lista, 30);
    printf("3. Após remover ID 30 (início): ");
    imprimir(lista);

    // Teste 3: Remover o que sobrou (ID 10)
    remover(&lista, 10);
    printf("4. Após remover ID 10 (último): ");
    imprimir(lista);

    // Limpeza final para o Valgrind
    limpar(lista);
    printf("--- Teste Finalizado com Sucesso ---\n\n");

    return 0;
}


2. Lista Duplamente Encadeada (Doubly Linked List)

📋 Situação Prática: Histórico de Navegação
Cenário: Simulação de botões "Voltar" e "Avançar" de um navegador. Cada nó precisa conhecer seu sucessor e seu antecessor.

🖼️ Diagrama Estrutural (Dupla)

PONTEIRO          NÓ [0]                NÓ [1]                NÓ [2]
    CABEÇA          (Head)                (Meio)                (Tail)
   +-------+     +----------+          +----------+          +----------+
   |       |     | ant: NULL| <------+ | ant: [0] | <------+ | ant: [1] |
   | [0] ------> | val: 30  |          | val: 20  |          | val: 10  |
   |       |     | prox: [1] ------>   | prox: [2] ------>   | prox:NULL|
   +-------+     +----------+          +----------+          +----------+

💻 Código Completo e Comentado

#include <stdio.h>
#include <stdlib.h>

typedef struct NoDuplo {
    int id;
    struct NoDuplo* proximo;
    struct NoDuplo* anterior;
} NoDuplo;

// Inserção no início: O(1)
void inserir_inicio_duplo(NoDuplo** cabeca, int id) {
    NoDuplo* novo = (NoDuplo*)malloc(sizeof(NoDuplo)); // Aloca memória
    novo->id = id;
    novo->proximo = *cabeca;      // Aponta para frente
    novo->anterior = NULL;        // Primeiro nó: anterior é NULL
    if (*cabeca != NULL) 
        (*cabeca)->anterior = novo; // Faz a antiga cabeça apontar de volta
    *cabeca = novo;               // Atualiza a entrada
}

// Remoção: O(1) para desconexão (após busca)
void remover_duplo(NoDuplo** cabeca, int id) {
    NoDuplo* atual = *cabeca;
    while (atual != NULL && atual->id != id) // Busca o alvo
        atual = atual->proximo;
    if (atual == NULL) return;

    if (atual == *cabeca) *cabeca = atual->proximo; // Caso seja o primeiro
    if (atual->proximo != NULL) 
        atual->proximo->anterior = atual->anterior; // Ajusta o sucessor
    if (atual->anterior != NULL) 
        atual->anterior->proximo = atual->proximo; // Ajusta o antecessor
    
    free(atual); // Libera o nó
}

void imprimir_dupla(NoDuplo* n) {
    while (n != NULL) {
        printf("[%d] <-> ", n->id);
        n = n->proximo;
    }
    printf("NULL\n");
}

void limpar_dupla(NoDuplo* cabeca) {
    NoDuplo* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    NoDuplo* lista = NULL; // Inicializa a lista vazia

    printf("--- TESTE LISTA DUPLA (Histórico Navegador) ---\n");

    // Simulando navegação: entrando em páginas
    inserir_inicio_duplo(&lista, 100); // Página 100
    inserir_inicio_duplo(&lista, 200); // Página 200 <-> 100
    inserir_inicio_duplo(&lista, 300); // Página 300 <-> 200 <-> 100
    
    printf("1. Histórico (Mais recente primeiro): ");
    imprimir_dupla(lista);

    // Teste 1: Remover página do meio
    remover_duplo(&lista, 200);
    printf("2. Após remover ID 200: ");
    imprimir_dupla(lista);

    // Teste de Verificação: Se a lista ainda está íntegra
    // Vamos percorrer até o fim e voltar para provar que os elos 'anterior' funcionam
    NoDuplo* temp = lista;
    if(temp != NULL) {
        while(temp->proximo != NULL) temp = temp->proximo; // Vai até o fim
        printf("3. Verificação Reversa (Fim para Início): ");
        while(temp != NULL) {
            printf("[%d] <-> ", temp->id);
            temp = temp->anterior; // VOLTANDO pelos ponteiros anteriores
        }
        printf("NULL\n");
    }

    // Limpeza final
    limpar_dupla(lista);
    printf("--- Teste Finalizado com Sucesso ---\n");

    return 0;
}

🚀 Como executar e validar (Checklist final)

Como você está no diretório estruturas_de_dados, use estes comandos para garantir que não há erros de memória:


1. Para a Lista Simples:

gcc lista_simples_completa.c -o simples
valgrind --leak-check=full ./simples

2. Para a Lista Dupla:

gcc lista_dupla_completa.c -o dupla
valgrind --leak-check=full ./dupla

Obs:. O que você deve buscar na saída do Valgrind? A frase: ERROR SUMMARY: 0 errors from 0 contexts. Se aparecer isso, você oficialmente domina a gerência de memória para essas estruturas!

⚖️ Tabela Comparativa

Tipo      Memória    Vantagem                   Desvantagem

Simples   Menor      implicidade e leveza       Navegação unidirecional
Dupla     Maior      Navegação bi-direcional    Complexidade de ponteiros

🛡️ Garantia de Qualidade (Valgrind)

Para todos os exercícios no diretório estruturas_de_dados, utilize: gcc arquivo.c -o programa && valgrind --leak-check=full ./programa

