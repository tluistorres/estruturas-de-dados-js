#include <stdio.h>
#include <stdlib.h>

// Estrutura clássica da lista dupla
typedef struct No {
    int valor;
    struct No* proximo;
    struct No* anterior;
} No;

// Inserção no início para popularmos nossa lista
void inserir_inicio(No** cabeca, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = *cabeca;
    novo->anterior = NULL;
    if (*cabeca != NULL) (*cabeca)->anterior = novo;
    *cabeca = novo;
}

// FUNÇÃO DE REMOÇÃO COMENTADA PASSO A PASSO
void remover_no(No** cabeca, int valor_alvo) {
    // Começamos a busca a partir da cabeça
    No* atual = *cabeca;

    // Enquanto não chegarmos ao fim e não encontrarmos o valor
    while (atual != NULL && atual->valor != valor_alvo) {
        atual = atual->proximo; // Caminha para o próximo nó
    }

    // Se o 'atual' for NULL, percorremos tudo e não achamos o valor
    if (atual == NULL) {
        printf("Valor %d nao encontrado.\n", valor_alvo);
        return;
    }

    // --- AGORA A MÁGICA DA REMOÇÃO ---

    // 1. Se o nó a ser removido for a CABEÇA
    if (atual == *cabeca) {
        *cabeca = atual->proximo; // A cabeça agora aponta para o segundo nó
    }

    // 2. Se houver um nó DEPOIS do atual, atualizamos o 'anterior' dele
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    // 3. Se houver um nó ANTES do atual, atualizamos o 'proximo' dele
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    }

    // 4. Com o nó devidamente isolado, liberamos a memória
    printf("Removendo no com valor: %d\n", atual->valor);
    free(atual);
}

void imprimir_lista(No* no) {
    printf("Lista atual: ");
    while (no != NULL) {
        printf("%d <-> ", no->valor);
        no = no->proximo;
    }
    printf("NULL\n");
}

void liberar_total(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    No* minha_lista = NULL;

    // Criando: 30 <-> 20 <-> 10
    inserir_inicio(&minha_lista, 10);
    inserir_inicio(&minha_lista, 20);
    inserir_inicio(&minha_lista, 30);

    imprimir_lista(minha_lista);

    // Testando a remoção do meio (o valor 20)
    remover_no(&minha_lista, 20);
    imprimir_lista(minha_lista);

    // Testando a remoção do início (o valor 30)
    remover_no(&minha_lista, 30);
    imprimir_lista(minha_lista);

    liberar_total(minha_lista);
    return 0;
}