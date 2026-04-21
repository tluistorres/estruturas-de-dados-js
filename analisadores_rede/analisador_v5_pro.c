#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas.h"

struct banimento {
    char ip[64];
    long tempo_inicio;
};

void registrar_log(char *ip) {
    FILE *log = fopen("banimentos_log.txt", "a");
    if (log) {
        time_t agora = time(NULL);
        char *data = ctime(&agora);
        data[strlen(data) - 1] = '\0';
        fprintf(log, "[%s] BLOQUEIO: %s\n", data, ip);
        fclose(log);
    }
}

void bloquear_ip(char *ip) {
    char comando[256];
    // Inserindo na linha 1 para garantir precedência sobre o UFW
    snprintf(comando, sizeof(comando), "sudo iptables -I INPUT 1 -s %s -j DROP", ip);
    system(comando);
    printf("\n\e[1;31m[BLOQUEIO ATIVO]\e[0m IP %s banido!\n", ip);
    registrar_log(ip);
}

void desbloquear_ip(char *ip) {
    char comando[256];
    snprintf(comando, sizeof(comando), "sudo iptables -D INPUT -s %s -j DROP", ip);
    system(comando);
    printf("\e[1;32m[LIBERADO]\e[0m IP %s pode voltar a acessar.\n", ip);
}

void gerenciar_banidos(struct list *lista_banidos) {
    struct listnode *atual = lista_banidos->head;
    struct listnode *anterior = NULL;
    long agora = time(NULL);

    while (atual != NULL) {
        struct banimento *b = (struct banimento *)atual->data;
        if ((agora - b->tempo_inicio) >= 60) { 
            desbloquear_ip(b->ip);
            if (anterior == NULL) lista_banidos->head = atual->next;
            else anterior->next = atual->next;
            struct listnode *temp = atual;
            atual = atual->next;
            free(temp->data);
            free(temp);
            lista_banidos->count--;
            continue;
        }
        anterior = atual;
        atual = atual->next;
    }
}

void iniciar_ips() {
    char comando_tcpdump[1024];
    char linha[1024];
    struct list *historico_trafego = list_new(); 
    struct list *lista_banidos = list_new();

    // Captura TUDO na interface any. stdbuf garante que não haja atraso no buffer.
    snprintf(comando_tcpdump, sizeof(comando_tcpdump), 
             "sudo stdbuf -oL tcpdump -lnn -i any 'tcp or udp'");

    printf("\n=====================================================");
    printf("\n🛡️  SENTINEL IPS v5.5 | MODO DIAGNÓSTICO ATIVO");
    printf("\n=====================================================\n");

    FILE *pipe = popen(comando_tcpdump, "r");
    if (!pipe) return;

    while (fgets(linha, sizeof(linha), pipe)) {
        // LINHA DE DIAGNÓSTICO: Mostra o que o programa está lendo
        if (strstr(linha, "IP")) printf("Capturado: %s", linha);

        char ip_origem[64] = {0}, destino_str[128] = {0};
        int porta_dest = 0;

        gerenciar_banidos(lista_banidos);

        if (sscanf(linha, "%*s IP %63s > %127[^:]", ip_origem, destino_str) >= 2) {
            char *ponto_porta = strrchr(destino_str, '.');
            if (ponto_porta) porta_dest = atoi(ponto_porta + 1);

            char *ponto_ip = strrchr(ip_origem, '.');
            if (ponto_ip) *ponto_ip = '\0';

            if (porta_dest > 0) {
                int *p = malloc(sizeof(int));
                *p = porta_dest;
                listnode_add(historico_trafego, p);

                if (historico_trafego->count > 15) {
                    struct banimento *nb = malloc(sizeof(struct banimento));
                    strncpy(nb->ip, ip_origem, 64);
                    nb->tempo_inicio = time(NULL);
                    listnode_add(lista_banidos, nb);
                    bloquear_ip(nb->ip);
                    list_clear(historico_trafego);
                }
            }
        }
    }
    pclose(pipe);
}

int main() {
    iniciar_ips();
    return 0;
}