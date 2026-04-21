#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Acao {
    char comando[50];
    struct Acao* abaixo; // Ponteiro para o elemento anterior na pilha
} Acao;

// Operação PUSH: Adicionar no topo
void push(Acao** topo, char* texto) {
    Acao* nova = (Acao*)malloc(sizeof(Acao));
    strcpy(nova->comando, texto);
    nova->abaixo = *topo; // A nova ação aponta para a antiga
    *topo = nova;         // O topo agora é a nova ação
    printf("Acao registrada: %s\n", texto);
}

// Operação POP: Remover do topo (Desfazer)
void pop(Acao** topo) {
    if (*topo == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }
    Acao* temp = *topo;
    printf("Desfazendo: %s\n", temp->comando);
    *topo = (*topo)->abaixo; // O topo passa a ser o elemento de baixo
    free(temp);
}

void imprimir_pilha(Acao* topo) {
    printf("\n--- Pilha de Operacoes ---\n");
    while (topo != NULL) {
        printf("| %-15s |\n", topo->comando);
        topo = topo->abaixo;
    }
    printf("--------------------------\n");
}

int main() {
    Acao* historico = NULL;

    push(&historico, "Digitar 'Ola'");
    push(&historico, "Negritar texto");
    push(&historico, "Mudar cor: azul");

    imprimir_pilha(historico);

    pop(&historico); // Remove 'Mudar cor'
    imprimir_pilha(historico);

    // Limpar o que restou
    while(historico) pop(&historico);

    return 0;
}
