// Incluímos bibliotecas necessárias
#include <stdio.h>
#include <string.h>

// Função para calcular um bit de paridade em uma posição específica
int pBit(int h[21], int pos) {
    // Inicializa o contador para cálculo de paridade (XOR)
    int count = 0;
    // Percorre os bits cobertos pela paridade 'pos'
    for (int i = pos-1; i < 21; i += (pos*2)) {
        // Faz XOR nos bits correspondentes
        for (int j = i; j < i+pos && j < 21; j++) {
            count ^= h[j]; // XOR para calcular paridade
        }
    }
    // Retorna o bit de paridade calculado
    return count;
}

// Função para codificar dados de 16 bits com Hamming(21,16)
void encode(int data[16], int hamming[21]) {
    // Posições dos bits de dados na palavra de 21 bits
    int pos[16] = {3,5,6,7,9,10,11,12,13,14,15,17,18,19,20,21};
    int j = 0;

    // Zera o array hamming antes de usar
    memset(hamming, 0, 21 * sizeof(int));

    // Coloca os 16 bits de dados nas posições correspondentes
    for (int i = 0; i < 16; i++) {
        hamming[pos[i]-1] = data[i]; // Ajusta para índice 0-based
    }

    // Calcula os 5 bits de paridade
    hamming[0]  = pBit(hamming, 1);  // P1
    hamming[1]  = pBit(hamming, 2);  // P2
    hamming[3]  = pBit(hamming, 4);  // P4
    hamming[7]  = pBit(hamming, 8);  // P8
    hamming[15] = pBit(hamming, 16); // P16
}

// Função principal
int main() {
    // Dados de exemplo (16 bits)
    int data[16] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
    // Array para armazenar o código de Hamming (21 bits)
    int hamming[21];

    // Codifica os dados com Hamming
    encode(data, hamming);

    // Imprime o código de Hamming gerado
    printf("Hamming: ");
    for (int i = 0; i < 21; i++) {
        printf("%d", hamming[i]);
    }
    printf("\n");

    // Retorna 0 para indicar execução bem-sucedida
    return 0;
}

