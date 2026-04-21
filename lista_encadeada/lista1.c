#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No* proximo;
};

void inserir_inicio(struct No** cabeca, int novo_valor) {
    struct No* novo_no = (struct No*)malloc(sizeof(struct No));
    novo_no->valor = novo_valor;
    novo_no->proximo = *cabeca;
    *cabeca = novo_no;
}

// NOVA FUNÇÃO: Inserir no Final
void inserir_final(struct No** cabeca, int novo_valor) {
    struct No* novo_no = (struct No*)malloc(sizeof(struct No));
    novo_no->valor = novo_valor;
    novo_no->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo_no;
        return;
    }

    struct No* atual = *cabeca;
    while (atual->proximo != NULL) { // Caminhando até o último nó
        atual = atual->proximo;
    }
    atual->proximo = novo_no; // O antigo último agora aponta para o novo
}

void imprimir_lista(struct No* no) {
    while (no != NULL) {
        printf("%d -> ", no->valor);
        no = no->proximo;
    }
    printf("NULL\n");
}

void liberar_lista(struct No* cabeca) {
    struct No* temporario;
    while (cabeca != NULL) {
        temporario = cabeca;
        cabeca = cabeca->proximo;
        printf("Liberando: %d\n", temporario->valor);
        free(temporario);
    }
}

int main() {
    struct No* minha_lista = NULL;

    // Testando a ordem das inserções
    inserir_final(&minha_lista, 10);  // Lista: 10
    inserir_final(&minha_lista, 20);  // Lista: 10 -> 20
    inserir_inicio(&minha_lista, 5);  // Lista: 5 -> 10 -> 20

    printf("Lista final (Mista):\n");
    imprimir_lista(minha_lista);

    liberar_lista(minha_lista);
    return 0;
}

