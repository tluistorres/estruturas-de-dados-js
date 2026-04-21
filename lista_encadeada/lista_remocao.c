#include <stdio.h>
#include <stdlib.h>

// Definição do Nó
struct No
{
    int valor;
    struct No *proximo;
};

// Função para inserir no início (mais simples)
void inserir_inicio(struct No **cabeca, int novo_valor)
{
    // 1. Alocar memória para o novo nó
    struct No *novo_no = (struct No *)malloc(sizeof(struct No));

    // 2. Colocar o valor
    novo_no->valor = novo_valor;

    // 3. Fazer o novo nó apontar para onde a cabeça apontava
    novo_no->proximo = *cabeca;

    // 4. Mover a cabeça para apontar para o novo nó
    *cabeca = novo_no;
}

void imprimir_lista(struct No *no)
{
    while (no != NULL)
    {
        printf("%d -> ", no->valor);
        no = no->proximo;
    }
    printf("NULL\n");
}

void inserir_final(struct No **cabeca, int novo_valor)
{
    // 1. Alocar memória
    struct No *novo_no = (struct No *)malloc(sizeof(struct No));
    struct No *ultimo = *cabeca;

    novo_no->valor = novo_valor;
    novo_no->proximo = NULL;

    // 2. Se a lista estiver vazia, o novo nó é a cabeça
    if (*cabeca == NULL)
    {
        *cabeca = novo_no;
        return;
    }

    // 3. Caso contrário, percorra até o fim
    while (ultimo->proximo != NULL)
    {
        ultimo = ultimo->proximo;
    }

    // 4. Mude o próximo do último nó
    ultimo->proximo = novo_no;
}

void liberar_lista(struct No *cabeca)
{
    struct No *temporario;

    while (cabeca != NULL)
    {
        temporario = cabeca;      // Guarda o nó atual
        cabeca = cabeca->proximo; // Move a cabeça para o próximo ANTES de deletar
        printf("Liberando no com valor: %d\n", temporario->valor);
        free(temporario); // Agora sim, deleta o que guardamos
    }
}

void remover_valor(struct No** cabeca, int valor_alvo) {
    struct No* atual = *cabeca;
    struct No* anterior = NULL;

    // Caso 1: O valor está na cabeça (primeiro nó)
    if (atual != NULL && atual->valor == valor_alvo) {
        *cabeca = atual->proximo; // A cabeça passa a ser o próximo
        printf("Removendo da cabeça: %d\n", atual->valor);
        free(atual);
        return;
    }

    // Caso 2: Procurar o valor no restante da lista
    while (atual != NULL && atual->valor != valor_alvo) {
        anterior = atual;       // Guarda o nó anterior
        atual = atual->proximo; // Vai para o próximo
    }

    // Caso 3: Valor não encontrado
    if (atual == NULL) {
        printf("Valor %d nao encontrado na lista.\n", valor_alvo);
        return;
    }

    // Caso 4: Encontrou o valor no meio ou fim
    anterior->proximo = atual->proximo; // O anterior "pula" o atual
    printf("Removendo do meio/fim: %d\n", atual->valor);
    free(atual);
}

int main() {
    struct No* minha_lista = NULL;

    inserir_final(&minha_lista, 10);
    inserir_final(&minha_lista, 20); // Vamos remover este
    inserir_final(&minha_lista, 30);

    printf("Lista Original: ");
    imprimir_lista(minha_lista);

    remover_valor(&minha_lista, 20);

    printf("Lista Após Remoção: ");
    imprimir_lista(minha_lista);

    liberar_lista(minha_lista);
    return 0;
}

// [Running] cd "/home/luis/estruturas_de_dados/lista_encadeada/" && gcc lista_remocao.c -o lista_remocao && "/home/luis/estruturas_de_dados/lista_encadeada/"lista_remocao
// Lista Original: 10 -> 20 -> 30 -> NULL
// Removendo do meio/fim: 20
// Lista Após Remoção: 10 -> 30 -> NULL
// Liberando no com valor: 10
// Liberando no com valor: 30

// [Done] exited with code=0 in 0.079 seconds

