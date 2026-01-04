#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de Nó para a Lista Encadeada
typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    struct Hop *proximo;
} Hop;

// Inserção no Fim O(n) - Mantém a ordem real da rota
void inserir_no_fim(Hop **cabeca, int n, char *host, char *endereco) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    if (novo == NULL) return;
    
    novo->num = n;
    strncpy(novo->nome, host, 99);
    strncpy(novo->ip, endereco, 39);
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

// Analisador Inteligente de Infraestrutura
void detectar_infra(char *hostname) {
    if (strstr(hostname, "fortaleza") || strstr(hostname, "ce.ix.br")) {
        printf("  [DETECTOR] >>> IX.br Fortaleza (Ponto de Troca de Tráfego Local) <<<\n");
    } else if (strstr(hostname, "as13335") || strstr(hostname, "cloudflare")) {
        printf("  [DETECTOR] >>> Rede Cloudflare (Servidor de Borda Próximo) <<<\n");
    } else if (strstr(hostname, "Washington") || strstr(hostname, "lumen") || strstr(hostname, "lax")) {
        printf("  [DETECTOR] >>> Rota Internacional: Estados Unidos <<<\n");
    } else if (strstr(hostname, "IIJ.Net") || strstr(hostname, "jp") || strstr(hostname, "tokyo")) {
        printf("  [DETECTOR] >>> Rota Internacional: Japão <<<\n");
    }
}

// Persistência: Salva a estrutura de dados no disco
void salvar_em_log(char *destino, Hop *cabeca) {
    FILE *log = fopen("historico_rotas.txt", "a");
    if (log == NULL) return;

    time_t agora = time(NULL);
    fprintf(log, "\n--- TESTE EM: %s", ctime(&agora));
    fprintf(log, "Destino: %s\n", destino);

    Hop *atual = cabeca;
    while (atual != NULL) {
        fprintf(log, "  Salto %d: %s (%s)\n", atual->num, atual->nome, atual->ip);
        atual = atual->proximo;
    }
    fprintf(log, "------------------------------------------------\n");
    fclose(log);
    printf("\n[SISTEMA] Relatório anexado em 'historico_rotas.txt'.\n");
}

// Gestão de Memória: Evita Memory Leaks
void liberar_lista(Hop *cabeca) {
    Hop *temp;
    int count = 0;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
        count++;
    }
    printf("[MEMORIA] %d nós liberados com sucesso.\n", count);
}

int main() {
    FILE *fp;
    char linha[512], destino[100], comando[150];
    Hop *lista_rota = NULL;

    printf("================ ANALISADOR DE ROTAS PRO ================\n");
    printf("Digite o domínio ou IP: ");
    scanf("%99s", destino);

    sprintf(comando, "traceroute -m 30 %s", destino);
    printf("\nIniciando rastreamento... (aguarde)\n\n");

    fp = popen(comando, "r");
    if (fp == NULL) return 1;

    fgets(linha, sizeof(linha), fp); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        
        // sscanf tenta capturar o formato: salto nome (ip)
        if (sscanf(linha, "%d %s (%[^)])", &n, host, ip) >= 2) {
            if (host[0] != '*') {
                detectar_infra(host);
                inserir_no_fim(&lista_rota, n, host, ip);
                printf("Capturado Salto %d: %s\n", n, host);
            }
        }
    }
    pclose(fp);

    // Salva o histórico
    if (lista_rota != NULL) {
        salvar_em_log(destino, lista_rota);
    }

    printf("\n--- RESULTADO DA ESTRUTURA NA RAM ---\n");
    Hop *atual = lista_rota;
    while (atual) {
        printf("[%d] %s (%s)\n", atual->num, atual->nome, atual->ip);
        if (atual->proximo) printf("  v\n");
        atual = atual->proximo;
    }

    // Liberação final de recursos
    printf("\nFinalizando programa...\n");
    liberar_lista(lista_rota);

    return 0;
}
