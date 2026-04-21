#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pacote {
    char destino[20];
    struct Pacote *proximo;
} Pacote;

typedef struct Fila {
    Pacote *frente;
    Pacote *tras;
} Fila;

void enfileirar(Fila *f, char *ip) {
    Pacote *novo = (Pacote*) malloc(sizeof(Pacote));
    strcpy(novo->destino, ip);
    novo->proximo = NULL;
    if (f->tras == NULL) {
        f->frente = f->tras = novo;
        return;
    }
    f->tras->proximo = novo;
    f->tras = novo;
    printf("Pacote para %s entrou na fila.\n", ip);
}

void desenfileirar(Fila *f) {
    if (f->frente == NULL) return;
    Pacote *temp = f->frente;
    printf("Roteador processando envio para: %s\n", temp->destino);
    f->frente = f->frente->proximo;
    if (f->frente == NULL) f->tras = NULL;
    free(temp);
}

int main() {
    Fila roteador = {NULL, NULL};

    enfileirar(&roteador, "192.168.0.1");
    enfileirar(&roteador, "106.187.12.13");
    
    printf("\n--- PROCESSANDO FILA ---\n");
    desenfileirar(&roteador);
    desenfileirar(&roteador);

    return 0;
}
