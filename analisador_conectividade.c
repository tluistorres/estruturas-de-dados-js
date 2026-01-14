#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Estrutura para controle de fluxo e estatísticas
typedef struct {
    int req_enviados;
    int rep_recebidos;
    int pacotes_perdidos;
    float percentual_perda;
} MonitorRede;

// Inicializa o monitor global
MonitorRede monitor = {0, 0, 0, 0.0};

void processar_estatisticas(char *linha) {
    int atualizou = 0;

    // Detecta saída (Request)
    if (strstr(linha, "ICMP echo request")) {
        monitor.req_enviados++;
        atualizou = 1;
    } 
    // Detecta entrada (Reply)
    else if (strstr(linha, "ICMP echo reply")) {
        monitor.rep_recebidos++;
        atualizou = 1;
    }

    if (atualizou) {
        monitor.pacotes_perdidos = monitor.req_enviados - monitor.rep_recebidos;
        
        if (monitor.req_enviados > 0) {
            monitor.percentual_perda = ((float)monitor.pacotes_perdidos / monitor.req_enviados) * 100;
        }

        // Exibe o painel em tempo real na mesma linha (\r)
        printf("\r[MONITOR] Enviados: %d | Recebidos: %d | Perdidos: %d | Status: %.1f%% de Perda", 
               monitor.req_enviados, monitor.rep_recebidos, monitor.pacotes_perdidos, monitor.percentual_perda);
        fflush(stdout);
    }
}

void iniciar_monitoramento(char *alvo) {
    char comando[512];
    char linha[1024];

    // O filtro exclui porta 53 (DNS) e foca no alvo escolhido
    snprintf(comando, sizeof(comando), 
             "sudo stdbuf -oL tcpdump -ln -i any host %s and icmp and port ! 53 2>/dev/null", alvo);

    printf("\n=====================================================");
    printf("\n🔍 ANALISADOR DE PERDA DE DADOS: %s", alvo);
    printf("\n[DICA] Use CTRL+C para parar e ver o resumo final.");
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

int main() {
    char ip_alvo[256];
    
    system("clear");
    printf("Digite o IP ou Domínio para teste de estresse: ");
    if (scanf("%255s", ip_alvo) != 1) return 1;

    iniciar_monitoramento(ip_alvo);

    return 0;
}

void limpar_memoria_final(Node *head) {
    Node *atual = head;
    int removidos = 0;
    
    while (atual != NULL) {
        Node *proximo = atual->proximo;
        free(atual);
        atual = proximo;
        removidos++;
    }
    
    if (removidos > 0) {
        printf("\n[MEMÓRIA] %d pacotes pendentes foram liberados com sucesso.\n", removidos);
    } else {
        printf("\n[MEMÓRIA] Lista limpa. Nenhum vazamento detectado.\n");
    }
}
