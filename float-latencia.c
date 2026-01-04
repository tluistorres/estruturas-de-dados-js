#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    float latencia; // <--- Novo campo
    struct Hop *proximo;
} Hop;

void inserir_no_fim(Hop **cabeca, int n, char *host, char *endereco, float ms) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    novo->num = n;
    strncpy(novo->nome, host, 99);
    strncpy(novo->ip, endereco, 39);
    novo->latencia = ms; // <--- Guarda a latência
    novo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Hop *atual = *cabeca;
        while (atual->proximo != NULL) atual = atual->proximo;
        atual->proximo = novo;
    }
}

int main() {
    FILE *fp;
    char linha[512], destino[100], comando[150];
    Hop *lista_rota = NULL;

    printf("Alvo para análise de latência: ");
    scanf("%99s", destino);

    sprintf(comando, "traceroute -m 30 %s", destino);
    fp = popen(comando, "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); 

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        float ms;
        
        // Ajustamos o sscanf para ler o número, o host, o ip e a PRIMEIRA latência
        if (sscanf(linha, "%d %s (%[^)]) %f", &n, host, ip, &ms) >= 3) {
            if (host[0] != '*') {
                inserir_no_fim(&lista_rota, n, host, ip, ms);
                printf("Salto %d: %s -> %.2f ms\n", n, host, ms);
            }
        }
    }
    pclose(fp);

    printf("\n--- ANÁLISE DE PERFORMANCE DA LISTA ---\n");
    Hop *atual = lista_rota;
    while (atual) {
        printf("[%d] %s (%.2f ms)\n", atual->num, atual->nome, atual->latencia);
        if (atual->latencia > 200.0) printf("  [!] Latência Alta detectada neste ponto!\n");
        atual = atual->proximo;
    }

    // (Lembre-se de liberar a memória e salvar no log como fizemos antes)
    return 0;
}
