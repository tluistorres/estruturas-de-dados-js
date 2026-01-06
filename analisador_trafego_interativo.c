#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/tcp.h>   // Estrutura do cabeçalho TCP
#include <netinet/ip.h>    // Estrutura do cabeçalho IP
#include <arpa/inet.h>     // Conversão de endereços IP


void analisar_trafego(char *alvo) {
    char comando[512];
    char linha[1024];
    FILE *pipe_tcpdump;

    // Comando configurado com as chaves solicitadas:
    // -l: Line buffered (saída imediata)
    // -n: Sem resolução DNS (mostra IP puro)
    // -q: Quiet (saída simplificada)
    snprintf(comando, sizeof(comando), "sudo tcpdump -l -n -q -i any host %s 2>/dev/null", alvo);

    printf("\n[MONITOR] Conectando ao motor tcpdump...\n");
    printf("[COMANDO] %s\n", comando);
    printf("[INFO] Pressione CTRL+C para encerrar.\n\n");

    pipe_tcpdump = popen(comando, "r");
    if (pipe_tcpdump == NULL) {
        perror("Erro ao abrir pipe do tcpdump");
        return;
    }

    // Lendo a saída do tcpdump linha por linha em tempo real
    while (fgets(linha, sizeof(linha), pipe_tcpdump) != NULL) {
        printf(">> %s", linha);
        
        // Dica: Aqui você pode usar strtok ou sscanf para extrair 
        // os IPs e alimentar suas estruturas de dados (Lista Encadeada).
    }

    pclose(pipe_tcpdump);
}

int main() {
    char alvo[256];
    char ping_cmd[256];

    printf("================ ANALISADOR DE TRÁFEGO INTERATIVO ================\n");
    printf("Digite o IP ou Domínio para monitorar: ");
    if (scanf("%255s", alvo) != 1) return 1;

    // Gera tráfego em background para garantir que o tcpdump tenha o que capturar
    // -c 5 (envia 5 pacotes)
    // Adicionamos -l para forçar a saída linha a linha e -i any para cobrir todas as placas
    snprintf(comando, sizeof(comando), "sudo tcpdump -l -n -i any host %s 2>/dev/null", alvo);
    printf("[SISTEMA] Gerando tráfego inicial para %s...\n", alvo);
    system(ping_cmd);

    // Inicia a função de análise
    analisar_trafego(alvo);

    return 0;
}
