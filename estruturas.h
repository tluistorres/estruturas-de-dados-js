#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdlib.h>
#include <string.h>

// --- Estruturas para o Analisador de Rede (v4.0) ---
typedef struct {
    int enviados;
    int recebidos;
    int perdidos;
    float taxa_perda;
} MonitorRede;

// Alias para facilitar o uso nos arquivos .c
typedef struct listnode Node; 

// --- Estrutura Original de Lista Genérica ---
struct listnode {
    struct listnode *next;
    struct listnode *prev;
    void *data; 
};

struct list {
    struct listnode *head;
    struct listnode *tail;
    unsigned int count;
};

// --- Funções Auxiliares (Static) ---
static struct list *list_new() {
    return (struct list *)calloc(1, sizeof(struct list));
}

static void listnode_add(struct list *l, void *val) {
    struct listnode *n = (struct listnode *)malloc(sizeof(struct listnode));
    if (!n) return;
    n->data = val;
    n->next = NULL;
    n->prev = l->tail;
    if (l->head == NULL) l->head = n;
    else l->tail->next = n;
    l->tail = n;
    l->count++;
}

#endif
