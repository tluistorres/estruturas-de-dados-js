#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "estruturas.h"

/* Nota: As definições de MonitorRede e Node agora devem estar 
   APENAS no arquivo estruturas.h para evitar erros de redefinição.
*/

// Inicializa o monitor global
MonitorRede monitor = {0, 0, 0, 0.0};

void processar_estatisticas(char *linha) {
    int atualizou = 0;

    if (strstr(linha, "ICMP echo request")) {
        monitor.enviados++; // Usando nomes de membros compatíveis com estruturas.h
        atualizou = 1;
    } 
    else if (strstr(linha, "ICMP echo reply")) {
        monitor.recebidos++;
        atualizou = 1;
    }

    if (atualizou) {
        monitor.perdidos = monitor.enviados - monitor.recebidos;
        
        if (monitor.enviados > 0) {
            monitor.taxa_perda = ((float)monitor.perdidos / monitor.enviados) * 100;
        }

        printf("\r[MONITOR] Enviados: %d | Recebidos: %d | Perdidos: %d | Status: %.1f%% de Perda", 
               monitor.enviados, monitor.recebidos, monitor.perdidos, monitor.taxa_perda);
        fflush(stdout);
    }
}

void iniciar_monitoramento(char *alvo) {
    char comando[512];
    char linha[1024];

    snprintf(comando, sizeof(comando), 
             "sudo stdbuf -oL tcpdump -ln -i any host %s and icmp 2>/dev/null", alvo);

    printf("\n=====================================================");
    printf("\n🔍 ANALISADOR DE CONECTIVIDADE v4.0: %s", alvo);
    printf("\n[DICA] Use CTRL+C para parar.");
    printf("\n=====================================================\n\n");

    FILE *pipe = popen(comando, "r");
    if (!pipe) {
        perror("Falha ao iniciar motor de captura");
        return;
    }

    while (fgets(linha, sizeof(linha), pipe)) {
        processar_estatisticas(linha);
    }

    pclose(pipe);
}

// Corrigido: usando 'next' conforme definido na struct Node
void limpar_memoria_final(Node *head) {
    Node *atual = head;
    int removidos = 0;
    
    while (atual != NULL) {
        Node *proximo = atual->next; // Corrigido de 'proximo' para 'next'
        free(atual);
        atual = proximo;
        removidos++;
    }
    
    if (removidos > 0) {
        printf("\n[MEMÓRIA] %d pacotes liberados.\n", removidos);
    }
}

int main() {
    char ip_alvo[256];
    
    system("clear");
    printf("Digite o IP ou Domínio para teste (ex: 8.8.8.8): ");
    if (scanf("%255s", ip_alvo) != 1) return 1;

    iniciar_monitoramento(ip_alvo);

    return 0;
}
