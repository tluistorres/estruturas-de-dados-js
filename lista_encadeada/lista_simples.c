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

