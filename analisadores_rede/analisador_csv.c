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

// Nova função para salvar a lista em um arquivo CSV
void salvar_csv(Hop *topo) {
    FILE *f = fopen("rota_japao.csv", "w");
    if (f == NULL) return;

    // Cabeçalho do CSV
    fprintf(f, "Salto,Nome do Host,IP\n");

    Hop *atual = topo;
    while (atual != NULL) {
        fprintf(f, "%d,%s,%s\n", atual->num, atual->nome, atual->ip);
        atual = atual->proximo;
    }

    fclose(f);
    printf("\n[SISTEMA] Dados exportados para 'rota_japao.csv' com sucesso!\n");
}

int main() {
    FILE *fp;
    char linha[512];
    Hop *lista_rota = NULL;

    printf("Iniciando varredura e exportação...\n");

    fp = popen("traceroute -m 20 yahoo.co.jp", "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); 

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        if (sscanf(linha, "%d %s (%[^)])", &n, host, ip) >= 2) {
            if (host[0] != '*') {
                inserir(&lista_rota, n, host, ip);
                printf("Capturado: %s\n", host);
            }
        }
    }
    pclose(fp);

    salvar_csv(lista_rota);
    return 0;
}
