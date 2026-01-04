#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    struct Hop *proximo;
} Hop;

// Inserção no Fim O(n) - Mantém a ordem da rota
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

// Analisador Geográfico Atualizado para sua região (Ceará/IX.br)
void detectar_infra(char *hostname) {
    if (strstr(hostname, "fortaleza") || strstr(hostname, "ce.ix.br")) {
        printf("  [DETECTOR] >>> Localizado: Ponto de Troca de Tráfego de Fortaleza (Ceará) <<<\n");
    } else if (strstr(hostname, "as13335") || strstr(hostname, "cloudflare")) {
        printf("  [DETECTOR] >>> Rede detectada: Cloudflare (Conteúdo entregue localmente) <<<\n");
    } else if (strstr(hostname, "Washington") || strstr(hostname, "lumen") || strstr(hostname, "lax")) {
        printf("  [DETECTOR] >>> Rota Internacional: EUA <<<\n");
    } else if (strstr(hostname, "IIJ.Net") || strstr(hostname, "jp") || strstr(hostname, "tokyo")) {
        printf("  [DETECTOR] >>> Rota Internacional: JAPÃO <<<\n");
    }
}

// Função de Análise da Estrutura de Dados
void gerar_sumario(Hop *cabeca) {
    int contagem = 0;
    int ultimo_salto = 0;
    Hop *atual = cabeca;

    while (atual != NULL) {
        contagem++;
        ultimo_salto = atual->num;
        atual = atual->proximo;
    }

    printf("\n================ SUMÁRIO DA ESTRUTURA ================\n");
    printf("Total de nós na Lista Encadeada: %d\n", contagem);
    printf("Distância total (Salto final): %d\n", ultimo_salto);
    printf("Saltos ocultos/firewall: %d\n", ultimo_salto - contagem);
    printf("Status da Rota: %s\n", (contagem > 0) ? "Sucesso" : "Falha");
    printf("======================================================\n");
}

int main() {
    FILE *fp;
    char linha[512];
    char destino[100];
    char comando[150];
    Hop *lista_rota = NULL;

    printf("Digite o domínio ou IP (ex: yahoo.co.jp): ");
    scanf("%99s", destino);

    sprintf(comando, "traceroute -m 30 %s", destino);
    
    printf("\nMonitorando rota para: %s...\n", destino);

    fp = popen(comando, "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); 

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        
        // Tenta capturar o formato padrão do traceroute
        if (sscanf(linha, "%d %s (%[^)])", &n, host, ip) >= 2) {
            if (host[0] != '*') {
                detectar_infra(host);
                inserir_no_fim(&lista_rota, n, host, ip);
                printf("Salto %d: %s [%s]\n", n, host, ip);
            }
        }
    }
    pclose(fp);

    printf("\n--- MAPA VISUAL DA LISTA ---\n");
    Hop *exibir = lista_rota;
    while (exibir != NULL) {
        printf("[%d] %s", exibir->num, exibir->nome);
        if (exibir->proximo) printf("\n  | \n  v \n");
        exibir = exibir->proximo;
    }
    printf("\n");

    gerar_sumario(lista_rota);

    return 0;
}
