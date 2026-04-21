// Incluímos a biblioteca padrão de entrada/saída
#include <stdio.h>

// Função principal do programa
int main() {
    // Definimos o tamanho do array
    int n = 3;
    
    // Declaramos um array de inteiros com tamanho 'n'
    int arr[n];

    // Imprimimos uma mensagem pedindo os números
    printf("Digite %d números:\n", n);
    
    // Loop para ler 'n' números
    for(int i = 0; i < n; i++) {
        // Lemos um número e armazenamos no array (usando &arr[i] ou arr+i)
        scanf("%d", &arr[i]); // ou arr + i
    }

    // Imprimimos os valores lidos
    printf("Valores em arr:\n");
    for(int i = 0; i < n; i++) {
        // Imprimimos cada valor do array
        printf("%d ", arr[i]);
    }
    // Quebra de linha no final
    printf("\n");

    // Retornamos 0 para indicar sucesso
    return 0;
}


