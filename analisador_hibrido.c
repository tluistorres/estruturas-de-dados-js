#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int enviados;
    int recebidos;
    int perdidos;
    float taxa_perda;
} Monitor Rede;

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

        // Limpa a linha atual e imprime o status atualizado
        printf("\r[STATUS] Enviados: %d | Recebidos: %d | Perdidos: %d | Perda: %.2f%%", 
               rede.enviados, rede.recebidos, rede.perdidos, rede.taxa_perda);
        fflush(stdout);
    }
}

void analisar_com_perda(char *alvo) {
    char comando[512];
    char linha[1024];

    // O filtro exclui tráfego DNS (porta 53) como fizeste no teu comando manual
    snprintf(comando, sizeof(comando), 
             "sudo stdbuf -oL tcpdump -ln -i any host %s and icmp and port ! 53 2>/dev/null", alvo);

    printf("\n=====================================================");
    printf("\n📡 ANALISADOR DE CONECTIVIDADE: %s", alvo);
    printf("\n[INFO] Calculando Taxa de Perda em tempo real...");
    printf("\n=====================================================\n\n");

    FILE *pipe = popen(comando, "r");
    if (!pipe) return;

    while (fgets(linha, sizeof(linha), pipe)) {
        atualizar_estatisticas(linha);
    }

    pclose(pipe);
}

int main() {
    char alvo[256];
    printf("Digite o IP/Domínio para teste de perda: ");
    scanf("%s", alvo);

    analisar_com_perda(alvo);

    return 0;
}
