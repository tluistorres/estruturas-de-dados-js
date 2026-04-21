🌳 README_ARVORES.md (Versão Final e Completa)

 - Este arquivo agora reflete todo o seu progresso no diretório estruturas_de_dados, incluindo a complexa lógica de remoção.

 - Este diretório documenta o estudo de árvores, uma estrutura onde a busca é otimizada através da organização lógica de "Menores à Esquerda" e "Maiores à Direita".

---

# 🌳 Estruturas Hierárquicas: Árvore Binária de Busca (BST)

Este diretório documenta o estudo de árvores binárias, focando em algoritmos recursivos de busca e reestruturação de nós.

---

## 1. O Conceito de BST (Binary Search Tree)

A BST é uma estrutura de dados não linear onde cada nó tem no máximo dois filhos. A regra fundamental é:

* **Subárvore Esquerda:** Somente valores menores que o nó pai.
* **Subárvore Direita:** Somente valores maiores que o nó pai.


# 🌳 Estruturas Hierárquicas: Árvore Binária de Busca (BST)

Este diretório documenta o estudo de árvores binárias, focando em algoritmos recursivos de busca e reestruturação de nós.

---

## 1. O Conceito de BST (Binary Search Tree)

A BST é uma estrutura de dados não linear onde cada nó tem no máximo dois filhos. A regra fundamental é:

* **Subárvore Esquerda:** Somente valores menores que o nó pai.
* **Subárvore Direita:** Somente valores maiores que o nó pai.

### 🖼️ Diagrama de Remoção (Caso 3: Dois Filhos)

Para remover um nó com dois filhos (ex: a Raiz 50), buscamos o **Sucessor em Ordem** (o menor valor da subárvore direita).

```text
       [50] Deletar             [60] Nova Raiz
      /    \                   /    \
   [30]    [70]      --->   [30]    [70]
          /    \                   /    \
       [60]    [80]              NULL   [80]

💻 Código de Referência (arvore_binaria.c)

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

Saída: Árvore em ordem crescente: 20 30 40 50 60 70 80 

Removendo o no 50 (Raiz)...

Arvore apos remocao: 20 30 40 60 70 80 

O elemento 60 foi encontrado na arvore!

⚖️ Tabela de Complexidade (Média)

Operação  Lista Encadeada   Árvore (BST)

Busca     O(n)              O(log n)
Inserção  O(1)              O(log n)
Remoção   O(n)              O(log n)

⚖️ Comparação: Lista vs. Árvore

Estrutura      Busca (Pior Caso)    Inserção      Organização

Lista Simples  O(n)(Lento)          O(1)(Início)  Desordenada
Árvore (BST)   O(log n)(Rápido)     O(log n)      Auto-ordenada


🛡️ Checklist de Sobrevivência

 - Ponteiros: Sempre atualize o ponteiro do nó pai ao remover um filho (raiz->esquerda = remover(...)).

 - Memória: Use o Valgrind para garantir que a liberação recursiva não deixou "folhas" órfãs na memória.

 - Recursão: O caso base if (raiz == NULL) é o que impede seu programa de travar (Segfault).