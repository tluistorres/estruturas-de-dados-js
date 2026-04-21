#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó da Árvore
typedef struct No {
    int valor;
    struct No* esquerda;  // Valores menores
    struct No* direita;   // Valores maiores
} No;

// Função para criar um novo nó (auxiliar)
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No)); // Aloca memória
    novo->valor = valor;                // Define o valor
    novo->esquerda = NULL;              // Inicializa filhos como NULL
    novo->direita = NULL;
    return novo;                        // Retorna o endereço do novo nó
}

// Inserção Recursiva (A forma mais elegante em Árvores)
No* inserir(No* raiz, int valor) {
    // 1. Se a posição estiver vazia, encontramos o lugar do novo nó
    if (raiz == NULL) {
        return criar_no(valor);
    }

    // 2. Se o valor for menor, "tenta" inserir na esquerda
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } 
    // 3. Se o valor for maior, "tenta" inserir na direita
    else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }

    // Retorna o ponteiro do nó (inalterado)
    return raiz;
}

// Função para buscar um valor na árvore
// Retorna o ponteiro do nó se encontrar, ou NULL se não existir
No* buscar(No* raiz, int alvo) {
    // 1. Caso Base: Raiz nula (não achou) ou Valor encontrado
    if (raiz == NULL || raiz->valor == alvo) {
        return raiz;
    }

    // 2. Se o alvo for maior que a raiz, busca na direita
    if (alvo > raiz->valor) {
        return buscar(raiz->direita, alvo);
    }

    // 3. Se o alvo for menor, busca na esquerda
    return buscar(raiz->esquerda, alvo);
}

// Função Auxiliar: Encontra o nó com o menor valor (mais à esquerda)
// Usada no Caso 3 da remoção
No* encontrar_minimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função de Remoção Recursiva
No* remover_no(No* raiz, int valor) {
    // 1. Caso Base: Árvore vazia
    if (raiz == NULL) return raiz;

    // 2. Navegação até encontrar o nó
    if (valor < raiz->valor)
        raiz->esquerda = remover_no(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover_no(raiz->direita, valor);
    
    // 3. Nó encontrado! Iniciando a lógica de remoção
    else {
        // CASO 1 e 2: Zero ou apenas um filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp; // O filho da direita assume o lugar
        } 
        else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp; // O filho da esquerda assume o lugar
        }

        // CASO 3: Nó com dois filhos
        // Busca o Sucessor (menor valor da subárvore direita)
        No* temp = encontrar_minimo(raiz->direita);

        // Copia o valor do sucessor para o nó atual
        raiz->valor = temp->valor;

        // Deleta o sucessor na subárvore direita
        raiz->direita = remover_no(raiz->direita, temp->valor);
    }
    return raiz;
}

// Percurso Em-Ordem (Imprime a árvore em ordem crescente!)
void imprimir_em_ordem(No* raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esquerda); // Visita a subárvore esquerda
        printf("%d ", raiz->valor);        // Imprime o valor do nó
        imprimir_em_ordem(raiz->direita);  // Visita a subárvore direita
    }
}

// Liberação de memória (Recursiva)
void liberar_arvore(No* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda); // Vai até o fim na esquerda
        liberar_arvore(raiz->direita);  // Vai até o fim na direita
        free(raiz);                     // Libera o nó atual
    }
}

int main() {
    No* raiz = NULL;

    // Criando a árvore do diagrama acima
    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 70);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 60);
    inserir(raiz, 80);

    printf("Árvore em ordem crescente: ");
    imprimir_em_ordem(raiz);
    printf("\n");

printf("\nRemovendo o no 50 (Raiz)...\n");
raiz = remover_no(raiz, 50);

printf("Arvore apos remocao: ");
imprimir_em_ordem(raiz);
printf("\n");


int num = 60;
if (buscar(raiz, num) != NULL) {
    printf("\nO elemento %d foi encontrado na arvore!\n", num);
} else {
    printf("\nO elemento %d NAO existe na arvore.\n", num);
}

    liberar_arvore(raiz);
    return 0;
}

