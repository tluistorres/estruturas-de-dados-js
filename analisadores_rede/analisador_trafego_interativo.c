#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Estrutura para armazenar os dados extraídos de cada pacote
typedef struct {
    int hora, min, seg, micro;
    int seq;
    char tipo[10]; // "request" ou "reply"
} PacoteICMP;

// Função para processar a string bruta do tcpdump e extrair dados
void processar_linha(char *linha) {
    PacoteICMP p;
    
    // O tcpdump emite a linha com o timestamp no início: HH:MM:SS.ffffff
    // Usamos sscanf para capturar o tempo. 
    // O restante da linha buscamos com strstr para identificar o tipo e o seq.
    if (sscanf(linha, "%d:%d:%d.%d", &p.hora, &p.min, &p.seg, &p.micro) >= 4) {
        
        // Identifica se é Request ou Reply
        if (strstr(linha, "ICMP echo request")) {
            strcpy(p.tipo, "request");
        } else if (strstr(linha, "ICMP echo reply")) {
            strcpy(p.tipo, "reply");
        } else {
            return; // Ignora outros tipos de pacotes
        }

        // Extrai o número de sequência (seq X)
        char *seq_ptr = strstr(linha, "seq ");
        if (seq_ptr) {
            sscanf(seq_ptr, "seq %d", &p.seq);
        }

        // Exibe os dados prontos para serem inseridos em uma Estrutura de Dados
        printf("[DATA] Seq: %d | Tipo: %-7s | Tempo: %02d:%02d:%02d.%06d\n", 
                p.seq, p.tipo, p.hora, p.min, p.seg, p.micro);
        
        /* DICA DE ESTRUTURA DE DADOS:
           Aqui você chamaria sua função de lista:
           inserir_na_lista(p.seq, p.tipo, p.hora, p.min, p.seg, p.micro);
        */
    }
}

void analisar_trafego(char *alvo) {
    char comando[512];
    char linha[1024];
    FILE *pipe_tcpdump;

    // stdbuf -oL: força o buffer de linha para o C ler instantaneamente
    // host %s and icmp: filtra apenas o que nos interessa
    snprintf(comando, sizeof(comando), 
             "sudo stdbuf -oL tcpdump -l -n -i any host %s and icmp 2>/dev/null", alvo);

    printf("\n=====================================================");
    printf("\n🔍 MONITORANDO: %s", alvo);
    printf("\n[DICA] Em outro terminal, rode: ping -c 5 %s", alvo);
    printf("\n=====================================================\n\n");

    pipe_tcpdump = popen(comando, "r");
    if (pipe_tcpdump == NULL) {
        perror("Erro ao abrir pipe do tcpdump");
        return;
    }

    // Loop de leitura em tempo real
    while (fgets(linha, sizeof(linha), pipe_tcpdump) != NULL) {
        processar_linha(linha);
    }

    pclose(pipe_tcpdump);
}

int main() {
    char alvo[256];

    // Limpa a tela para uma melhor apresentação
    system("clear");

    printf("================ ANALISADOR DE TRÁFEGO INTERATIVO ================\n");
    printf("Digite o IP ou Domínio para monitorar: ");
    if (scanf("%255s", alvo) != 1) return 1;

    analisar_trafego(alvo);

    return 0;
}
