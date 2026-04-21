// Incluímos a biblioteca padrão de entrada/saída
#include <stdio.h>

// Função que imprime o tamanho do "array" (na verdade, um ponteiro)
void func(int arr[]) {
    // sizeof(arr) aqui retorna o tamanho do ponteiro (8 bytes em 64 bits)
    printf("%ld ", sizeof(arr));
}

// Função principal do programa
int main() {
    // Declaramos um array de 10 inteiros
    int arr[10];
    
    // sizeof(arr) aqui retorna o tamanho total do array (10 * 4 = 40 bytes)
    printf("%ld ", sizeof(arr));
    
    // Chamamos a função passando o array (que decai para ponteiro)
    func(arr);
    
    // Retornamos 0 para indicar sucesso
    return 0;
}