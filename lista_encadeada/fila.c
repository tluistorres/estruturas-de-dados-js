#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char pedido[50];
    struct No* proximo;
} No;

typedef struct Fila {
    No* inicio;
    No* fim;
} Fila;

// Inicializa a fila
Fila* criar_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

// Enqueue: Adiciona ao fim
void enfileirar(Fila* f, char* item) {
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->pedido, item);
    novo->proximo = NULL;

    if (f->fim == NULL) { // Fila vazia
        f->inicio = f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    printf("Entrou na fila: %s\n", item);
}

// Dequeue: Remove do início
void desenfileirar(Fila* f) {
    if (f->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    No* temp = f->inicio;
    printf("Atendendo pedido: %s\n", temp->pedido);
    
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL; // Fila ficou vazia

    free(temp);
}

int main() {
    Fila* lanchonete = criar_fila();

    enfileirar(lanchonete, "Pedido 01: Hamburguer");
    enfileirar(lanchonete, "Pedido 02: Pizza");
    enfileirar(lanchonete, "Pedido 03: Batata Frita");

    printf("\n--- Processando Pedidos ---\n");
    desenfileirar(lanchonete);
    desenfileirar(lanchonete);

    printf("\nNovo pedido chegando...\n");
    enfileirar(lanchonete, "Pedido 04: Suco");

    while(lanchonete->inicio) desenfileirar(lanchonete);
    
    free(lanchonete);
    return 0;
}