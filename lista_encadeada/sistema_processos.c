#include <stdio.h>
#include <stdlib.h>

typedef struct Processo {
    int id;
    struct Processo* proximo;
} Processo;

// 1. ADICIONAR PRIORITÁRIO (Inserir no Início)
void adicionar_prioritario(Processo** cabeca, int id) {
    Processo* novo = (Processo*)malloc(sizeof(Processo));
    novo->id = id;
    novo->proximo = *cabeca;
    *cabeca = novo;
    printf(">> Processo Prioritário %d adicionado ao início.\n", id);
}

// 2. ADICIONAR COMUM (Inserir no Final)
void adicionar_comum(Processo** cabeca, int id) {
    Processo* novo = (Processo*)malloc(sizeof(Processo));
    novo->id = id;
    novo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    Processo* atual = *cabeca;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    printf(">> Processo Comum %d adicionado ao final.\n", id);
}

// 3. ENCERRAR PROCESSO (Remover por ID - Início, Meio ou Fim)
void encerrar_processo(Processo** cabeca, int id) {
    Processo *atual = *cabeca, *anterior = NULL;

    if (atual != NULL && atual->id == id) {
        *cabeca = atual->proximo;
        free(atual);
        printf(">> Processo %d encerrado (era o primeiro).\n", id);
        return;
    }

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf(">> Erro: Processo %d não encontrado.\n", id);
        return;
    }

    anterior->proximo = atual->proximo;
    free(atual);
    printf(">> Processo %d encerrado e removido da fila.\n", id);
}

// 4. LISTAR PROCESSOS
void listar_fila(Processo* cabeca) {
    printf("\nFILA DE PROCESSOS ATIVOS: ");
    if (cabeca == NULL) printf("Vazia.");
    while (cabeca != NULL) {
        printf("[%d] -> ", cabeca->id);
        cabeca = cabeca->proximo;
    }
    printf("NULL\n\n");
}

// LIMPEZA FINAL
void desligar_sistema(Processo* cabeca) {
    Processo* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    Processo* fila = NULL;

    // Simulando o uso do sistema
    adicionar_comum(&fila, 101);       // Fila: 101
    adicionar_comum(&fila, 102);       // Fila: 101 -> 102
    adicionar_prioritario(&fila, 999); // Fila: 999 -> 101 -> 102
    
    listar_fila(fila);

    encerrar_processo(&fila, 101);     // Remove do meio
    encerrar_processo(&fila, 999);     // Remove do início
    
    listar_fila(fila);

    desligar_sistema(fila);
    return 0;
}
