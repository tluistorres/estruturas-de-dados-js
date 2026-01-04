#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Hop {
    int num;
    char nome[100];
    char ip[40];
    float latencia;
    struct Hop *proximo;
} Hop;

void inserir_no_fim(Hop **cabeca, int n, char *host, char *endereco, float ms) {
    Hop *novo = (Hop*) malloc(sizeof(Hop));
    if (!novo) return;
    novo->num = n;
    strncpy(novo->nome, host, 99);
    strncpy(novo->ip, endereco, 39);
    novo->latencia = ms;
    novo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Hop *atual = *cabeca;
        while (atual->proximo) atual = atual->proximo;
        atual->proximo = novo;
    }
}

// Função que percorre a lista para calcular estatísticas
void calcular_estatisticas(Hop *cabeca) {
    if (!cabeca) return;

    float soma = 0;
    int contador = 0;
    float max_lat = 0;
    Hop *atual = cabeca;

    while (atual) {
        soma += atual->latencia;
        if (atual->latencia > max_lat) max_lat = atual->latencia;
        contador++;
        atual = atual->proximo;
    }

    float media = soma / contador;

    printf("\n========= ESTATÍSTICAS DA ESTRUTURA =========\n");
    printf("Nós processados: %d\n", contador);
    printf("Latência Média:  %.2f ms\n", media);
    printf("Maior Latência:  %.2f ms\n", max_lat);
    printf("Qualidade:       %s\n", (media < 50) ? "EXCELENTE" : (media < 150) ? "BOA" : "CRÍTICA");
    printf("==============================================\n");
}

void liberar_lista(Hop *cabeca) {
    while (cabeca) {
        Hop *temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    FILE *fp;
    char linha[512], destino[100], comando[150];
    Hop *lista_rota = NULL;

    printf("Digite o alvo para relatório estatístico: ");
    scanf("%99s", destino);

    sprintf(comando, "traceroute -m 30 %s", destino);
    fp = popen(comando, "r");
    if (!fp) return 1;

    fgets(linha, sizeof(linha), fp); 

    while (fgets(linha, sizeof(linha), fp)) {
        int n;
        char host[100], ip[40];
        float ms;
        
        if (sscanf(linha, "%d %s (%[^)]) %f", &n, host, ip, &ms) >= 3) {
            if (host[0] != '*') {
                inserir_no_fim(&lista_rota, n, host, ip, ms);
                printf("Capturado: %s [%.2f ms]\n", host, ms);
            }
        }
    }
    pclose(fp);

    calcular_estatisticas(lista_rota);
    liberar_lista(lista_rota);

    return 0;
}
