#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    struct Hop *proximo;
} Hop;

void inserir(Hop **topo, int n, char *host, char *endereco) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    novo->num = n;
    strncpy(novo->nome, host, 99);
    strncpy(novo->ip, endereco, 39);
    novo->proximo = *topo;
    *topo = novo;
}

int main() {
    FILE *fp;
    char linha[512];
    Hop *lista_rota = NULL;

    printf("Iniciando varredura com RESOLUÇÃO DE NOMES (pode demorar mais)...\n");

    // Removemos o -n para que o traceroute mostre os nomes dos hosts
    fp = popen("traceroute -m 20 yahoo.co.jp", "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        
        // O formato muda para: " 1  nome-do-router (192.168.0.1) ..."
        // Vamos tentar capturar o número, o nome e o IP entre parênteses
        if (sscanf(linha, "%d %s (%[^)])", &n, host, ip) >= 2) {
            if (host[0] != '*') {
                inserir(&lista_rota, n, host, ip);
                printf("Salto %d: %s [%s]\n", n, host, ip);
            }
        }
    }
    pclose(fp);

    printf("\n--- MAPA DE MEMÓRIA DA ROTA COM NOMES ---\n");
    Hop *atual = lista_rota;
    while (atual != NULL) {
        printf("[%s | %s] \n  | \n  v \n", atual->nome, atual->ip);
        atual = atual->proximo;
    }
    printf("ORIGEM\n");

    return 0;
}
