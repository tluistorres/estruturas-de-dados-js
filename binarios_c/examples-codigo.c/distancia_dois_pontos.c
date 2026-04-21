#include <stdio.h>
#include <stdlib.h>
#include <math.h> // <--- Adiciona isso

// Struct para representar um ponto 2D
typedef struct {
    int x;
    int y;
} Ponto;

// Função para criar um ponto
Ponto* criar_ponto(int x, int y) {
    // Aloca memória para o ponto
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    if (!p) return NULL; // Verifica se a alocação falhou
    p->x = x;
 cl   p->y = y;
    return p;
}

// Função para calcular a distância entre dois pontos
double distancia(Ponto* p1, Ponto* p2) {
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return sqrt(dx*dx + dy*dy);
}

int main() {
    // Cria dois pontos
    Ponto* p1 = criar_ponto(1, 2);
    Ponto* p2 = criar_ponto(4, 6);
    
    if (!p1 || !p2) {
        printf("Erro de alocação!\n");
        return 1;
    }
    
    // Calcula e imprime a distância
    double d = distancia(p1, p2);
    printf("Distância: %.2f\n", d);
    
    // Libera a memória
    free(p1);
    free(p2);
    
    return 0;
}

// O que acontece:- Cria uma struct Ponto com x e y
// - criar_ponto aloca memória e inicializa um ponto
// - distancia calcula a distância entre dois pontos usando Pitágoras
// - main cria pontos, calcula a distância e libera memória

// Detalhes:- Uso de ponteiros e malloc para alocação dinâmica
// - Funções para modularizar o código
// - Verificação de erro na alocação
// - Uso de -> para acessar membros de struct via ponteiro
// - Pra rodar este código: 
// bash gcc distancia_dois_pontos.c -o distancia_dois_pontos -lm 
// bash ./distancia_dois_pontos
