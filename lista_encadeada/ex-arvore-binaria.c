#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó: 2 "filhos" em vez de anterior/próximo
typedef struct No {
    int valor;
    struct No* esquerda;  // Ponteiro para valores menores
    struct No* direita;   // Ponteiro para valores maiores
} No;

// Função Auxiliar: Cria um novo nó na Heap
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Inserção Recursiva: Organiza a árvore automaticamente
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor); // Lugar encontrado!

    if (valor < raiz->valor) 
        raiz->esquerda = inserir(raiz->esquerda, valor); // Vai para esquerda
    else if (valor > raiz->valor) 
        raiz->direita = inserir(raiz->direita, valor);   // Vai para direita

    return raiz;
}

// Busca O(log n): A grande vantagem da árvore
No* buscar(No* raiz, int alvo) {
    if (raiz == NULL || raiz->valor == alvo) return raiz;
    
    if (alvo > raiz->valor) 
        return buscar(raiz->direita, alvo); // Descarta a esquerda
    
    return buscar(raiz->esquerda, alvo);    // Descarta a direita
}

// Percurso Em-Ordem: Imprime os dados ordenados
void imprimir_em_ordem(No* raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimir_em_ordem(raiz->direita);
    }
}

// Liberação de Memória: Recursiva (Post-Order)
void liberar_arvore(No* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for(int i=0; i<7; i++) raiz = inserir(raiz, valores[i]);

    printf("Elementos Ordenados: ");
    imprimir_em_ordem(raiz);
    
    int alvo = 60;
    if (buscar(raiz, alvo)) printf("\nID %d encontrado!", alvo);
    else printf("\nID %d nao existe.", alvo);

    liberar_arvore(raiz);
    return 0;
}