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
c