#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdlib.h>
#include <string.h>

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

static struct list *list_new() {
    return (struct list *)calloc(1, sizeof(struct list));
}

static void listnode_add(struct list *l, void *val) {
    struct listnode *n = (struct listnode *)malloc(sizeof(struct listnode));
    n->data = val;
    n->next = NULL;
    n->prev = l->tail;
    if (l->head == NULL) l->head = n;
    else l->tail->next = n;
    l->tail = n;
    l->count++;
}
#endif
