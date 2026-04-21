#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hop {
    int num;
    char ip[40];
    struct Hop *proximo;
} Hop;

// Função para inserir na lista
void inserir(Hop **topo, int n, char *endereco) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    novo->num = n;
    strncpy(novo->ip, endereco, 39);
    novo->proximo = *topo; // Inserindo no início para simplificar
    *topo = novo;
}

int main() {
    FILE *fp;
    char linha[256];
    Hop *lista_rota = NULL;

    printf("Iniciando varredura de rota (aguarde)...\n");

    // Executa o traceroute e abre a saída para leitura
    fp = popen("traceroute -n -m 20 yahoo.co.jp", "r");
    if (fp == NULL) {
        printf("Erro ao executar traceroute\n");
        return 1;
    }

    // Pula a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), fp);

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char ip_extraido[40];
        
        // sscanf tenta ler o número do salto e o IP da linha
        if (sscanf(linha, "%d %39s", &n, ip_extraido) == 2) {
            if (strcmp(ip_extraido, "*") != 0) { // Ignora saltos vazios
                inserir(&lista_rota, n, ip_extraido);
                printf("Salto %d capturado: %s\n", n, ip_extraido);
            }
        }
    }
    pclose(fp);

    printf("\n--- MAPA DE MEMÓRIA DA ROTA ---\n");
    Hop *atual = lista_rota;
    while (atual != NULL) {
        printf("[%s] -> ", atual->ip);
        atual = atual->proximo;
    }
    printf("ORIGEM\n");

    return 0;
}
