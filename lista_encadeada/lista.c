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

int main()
{
    struct No *minha_lista = NULL;

    inserir_inicio(&minha_lista, 10);
    inserir_inicio(&minha_lista, 20);
    inserir_inicio(&minha_lista, 30);

    imprimir_lista(minha_lista);

    // O toque de mestre:
    liberar_lista(minha_lista);

    return 0;
}
