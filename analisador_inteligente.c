#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    struct Hop *proximo;
} Hop;

// Inserção no Fim para manter a ordem cronológica O(n)
void inserir_no_fim(Hop **cabeca, int n, char *host, char *endereco) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    novo->num = n;
    strncpy(novo->nome, host, 99);
    strncpy(novo->ip, endereco, 39);
    novo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Hop *atual = *cabeca;
        while (atual->proximo != NULL) atual = atual->proximo;
        atual->proximo = novo;
    }
}

// A nossa "Inteligência" de Análise de Dados
void detectar_pais(char *hostname) {
    if (strstr(hostname, "Washington") || strstr(hostname, "lumen") || strstr(hostname, "lax")) {
        printf("  [DETECTOR] >>> Fronteira Detectada: Entrando nos EUA (Hub Internacional) <<<\n");
    } else if (strstr(hostname, "IIJ.Net") || strstr(hostname, "osk") || strstr(hostname, "jp")) {
        printf("  [DETECTOR] >>> Fronteira Detectada: Chegada ao JAPÃO (Tokyo/Osaka) <<<\n");
    } else if (strstr(hostname, "commcorp") || strstr(hostname, "embratel") || strstr(hostname, "claro")) {
        printf("  [DETECTOR] Infraestrutura Nacional (Brasil) detectada.\n");
    }
}

int main() {
    FILE *fp;
    char linha[512];
    Hop *lista_rota = NULL;

    printf("Iniciando varredura inteligente (Traceroute + Análise Geográfica)...\n");

    fp = popen("traceroute -m 25 yahoo.co.jp", "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); 

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        if (sscanf(linha, "%d %s (%[^)])", &n, host, ip) >= 2) {
            if (host[0] != '*') {
                detectar_pais(host); // Analisa o nome antes de inserir
                inserir_no_fim(&lista_rota, n, host, ip);
                printf("Salto %d: %s\n", n, host);
            }
        }
    }
    pclose(fp);

    printf("\n--- RELATÓRIO FINAL DE ROTA ---\n");
    Hop *atual = lista_rota;
    while (atual != NULL) {
        printf("Passo %d: %s [%s]\n", atual->num, atual->nome, atual->ip);
        atual = atual->proximo;
    }

    return 0;
}
