#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para a Pilha (Histórico) e Fila (Downloads)
typedef struct No {
    char url[100];
    struct No* proximo;
} No;

// --- LÓGICA DA PILHA (Histórico) ---
void push_historico(No** topo, char* site) {
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->url, site);
    novo->proximo = *topo;
    *topo = novo;
    printf("[Histórico] Visitou: %s\n", site);
}

void pop_historico(No** topo) {
    if (*topo == NULL) return;
    No* temp = *topo;
    printf("[Voltar] Saindo de: %s\n", temp->url);
    *topo = (*topo)->proximo;
    free(temp);
}

// --- LÓGICA DA FILA (Downloads) ---
typedef struct {
    No *inicio, *fim;
} Fila;

void enqueue_download(Fila* f, char* arquivo) {
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->url, arquivo);
    novo->proximo = NULL;
    if (f->fim == NULL) f->inicio = f->fim = novo;
    else { f->fim->proximo = novo; f->fim = novo; }
    printf("[Download] Adicionado à fila: %s\n", arquivo);
}

void dequeue_download(Fila* f) {
    if (f->inicio == NULL) return;
    No* temp = f->inicio;
    printf("[Sistema] Concluído download de: %s\n", temp->url);
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
}

int main() {
    No* historico = NULL;
    Fila downloads = {NULL, NULL};

    printf("--- Iniciando Sessão de Navegação ---\n");
    push_historico(&historico, "google.com");
    push_historico(&historico, "github.com/luis");
    
    enqueue_download(&downloads, "ubuntu_iso.zip");
    enqueue_download(&downloads, "driver_wifi.exe");

    printf("\n--- Usuário clicou em 'Voltar' ---\n");
    pop_historico(&historico);

    printf("\n--- Processando Downloads ---\n");
    dequeue_download(&downloads);

    // Limpeza
    while(historico) pop_historico(&historico);
    while(downloads.inicio) dequeue_download(&downloads);

    return 0;
}
