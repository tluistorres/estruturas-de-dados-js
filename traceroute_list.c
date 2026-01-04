#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura do Nó (o salto da rede)
typedef struct Hop {
    int id;
    char ip[20];
    float latencia;
    struct Hop *proximo; // Ponteiro para o próximo salto
} Hop;

// Função para adicionar um salto no final da lista
void adicionar_salto(Hop **cabeca, int id, char *ip, float latencia) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    novo->id = id;
    strcpy(novo->ip, ip);
    novo->latencia = latencia;
    novo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Hop *atual = *cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

// Função para percorrer a lista e exibir o caminho
void exibir_rota(Hop *cabeca) {
    printf("\n--- ESTRUTURA DA ROTA (LISTA ENCADEADA) ---\n");
    Hop *atual = cabeca;
    while (atual != NULL) {
        printf("[%d] IP: %s | Latencia: %.2f ms -> ", atual->id, atual->ip, atual->latencia);
        atual = atual->proximo;
    }
    printf("DESTINO\n");
}

int main() {
    Hop *minha_rota = NULL;

    // Simulando os dados que voce obteve no traceroute
    adicionar_salto(&minha_rota, 1, "192.168.0.1", 2.66);
    adicionar_salto(&minha_rota, 10, "5.178.43.230", 19.02);
    adicionar_salto(&minha_rota, 14, "106.187.12.13", 362.71);

    exibir_rota(minha_rota);

    return 0;
}
