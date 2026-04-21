#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

// Cores ANSI
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"
#include <time.h>


// Estrutura de Dados
struct listnode {
    struct listnode *next;
    void *data; 
};

struct list {
    struct listnode *head;
    unsigned int count;
};

struct list *historico;
int total_capturado = 0;
time_t inicio_tempo;

// Função para encerrar com relatório (ED em ação)
void tratar_sigint(int sig) {
    time_t fim_tempo = time(NULL);
    double duracao = difftime(fim_tempo, inicio_tempo);
    
    printf("\n\n%s========================================================%s", RED, RESET);
    printf("\n%s                RELATÓRIO DE AUDITORIA FINAL            %s", RED, RESET);
    printf("\n%s========================================================%s", RED, RESET);
    printf("\n- Total de Pacotes OSPF: %d", total_capturado);
    printf("\n- Duração da Sessão: %.1f segundos", duracao);
    if (duracao > 0) printf("\n- Taxa de Tráfego: %.2f pps (pacotes/seg)", total_capturado/duracao);
    
    printf("\n\n%s[INTEGRIDADE]%s Verificando alertas do iWatch no syslog...", YEL, RESET);
    printf("\n%s--------------------------------------------------------%s\n", YEL, RESET);
    // Busca alertas do iwatch no log do sistema
    printf("\n[INTEGRIDADE] Verificando alertas do iWatch (Últimos 2 min)...\n");
    printf("--------------------------------------------------------\n");
    // Usamos journalctl para acessar os logs reais do serviço iwatch
    system("sudo journalctl -u iwatch --since '5 minutes ago' --no-pager | grep -iE 'IN_CREATE|IN_MODIFY|success' | tail -n 10");
    printf("--------------------------------------------------------\n");

    
    printf("\n%sSessão encerrada com segurança.%s\n", GRN, RESET);
    exit(0);
    
    // Dentro da função de relatório:
    time_t agora = time(NULL);
    printf("Data/Hora do Incidente: %s", ctime(&agora));

}

// ... (Mantenha as funções list_new e listnode_add que já usamos) ...
struct list *list_new() { return (struct list *)calloc(1, sizeof(struct list)); }
void listnode_add(struct list *l, void *val) {
    struct listnode *n = (struct listnode *)malloc(sizeof(struct listnode));
    n->data = val; n->next = l->head; l->head = n; l->count++;
}

void monitorar(char *ip, char *porta) {
    char comando[1024];
    char linha[2048];
    FILE *pipe_tcpdump;
    inicio_tempo = time(NULL);
    historico = list_new();

    signal(SIGINT, tratar_sigint); // Captura o Ctrl+C

    snprintf(comando, sizeof(comando), "sudo tcpdump -l -n -i any 'proto 89' 2>/dev/null");
    pipe_tcpdump = popen(comando, "r");

    while (fgets(linha, sizeof(linha), pipe_tcpdump) != NULL) {
        total_capturado++;
        listnode_add(historico, strdup(linha));
        
        // Limita a ED para não estourar RAM
        if (historico->count > 5) {
            struct listnode *temp = historico->head;
            while(temp->next && temp->next->next) temp = temp->next;
            free(temp->next->data); free(temp->next);
            temp->next = NULL; historico->count--;
        }
        printf("%s[RAM:%u]%s >> %s", YEL, historico->count, RESET, linha);
    }
}

int main() {
    monitorar("0", "89");
    return 0;
}
