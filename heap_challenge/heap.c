#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MinHeap *h, int val) {
    if (h->size >= MAX_SIZE) return;
    
    h->data[h->size] = val;
    int i = h->size;
    h->size++;

    // Sift-Up: Sobe o elemento se ele for menor que o pai
    while (i != 0 && h->data[i] < h->data[(i - 1) / 2]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void printHeap(MinHeap *h) {
    printf("Heap: ");
    for (int i = 0; i < h->size; i++) printf("%d ", h->data[i]);
    printf("\n");
}

int main() {
    MinHeap h = {.size = 0};
    
    insert(&h, 30);
    insert(&h, 10);
    insert(&h, 20);
    insert(&h, 5);
    
    printf("Desafio Heap - Inserindo 30, 10, 20, 5\n");
    printHeap(&h); // O 5 deve estar no topo (índice 0)
    
    return 0;
}
