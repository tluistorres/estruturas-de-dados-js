#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h" // Inclui a definição de MonitorRede

// Removida a definição local para não conflitar com estruturas.h
MonitorRede rede = {0, 0, 0, 0.0};

void atualizar_estatisticas(char *linha) {
    int mudou = 0;

    if (strstr(linha, "ICMP echo request")) {
        rede.enviados++;
        mudou = 1;
    } 
    else if (strstr(linha, "ICMP echo reply")) {
        rede.recebidos++;
        mudou = 1;
    }

    if (mudou) {
        rede.perdidos = rede.enviados - rede.recebidos;
        if (rede.enviados > 0) {
            rede.taxa_perda = ((float)rede.perdidos / rede.enviados) * 100;
        }

        // \r faz o cursor voltar ao início da linha para o efeito de "loading"
        printf("\r[STATUS] Enviados: %d | Recebidos: %d | Perdidos: %d | Perda: %.2f%%", 
               rede.enviados, rede.recebidos, rede.perdidos, rede.taxa_perda);
        fflush(stdout);
    }
}

void analisar_com_perda(char *alvo) {
    char comando[512];
    char linha[1024];

    // O filtro exclui porta 53 (DNS) e foca no alvo escolhido
    snprintf(comando, sizeof(comando), 
             "sudo stdbuf -oL tcpdump -ln -i any host %s and icmp 2>/dev/null", alvo);

    printf("\n=====================================================");
    printf("\n📡 ANALISADOR HÍBRIDO v4.0: %s", alvo);
    printf("\n[INFO] Calculando Taxa de Perda em tempo real...");
    printf("\n=====================================================\n\n");

    FILE *pipe = popen(comando, "r");
    if (!pipe) {
        perror("Erro ao abrir pipe do tcpdump");
        return;
    }

    while (fgets(linha, sizeof(linha), pipe)) {
        atualizar_estatisticas(linha);
    }

    pclose(pipe);
}

int main() {
    char alvo[256];
    
    system("clear");
    printf("Digite o IP/Domínio para teste de perda: ");
    if (scanf("%255s", alvo) != 1) return 1;

    analisar_com_perda(alvo);

    return 0;
}
