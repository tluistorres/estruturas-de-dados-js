// Incluímos a biblioteca padrão de entrada/saída
#include <stdio.h>

// Função principal do programa
int main() {
    // Declaramos uma variável inteira 'n'
    int n;
    
    // Imprimimos uma mensagem pedindo um número
    printf("Enter the number :");
    
    // Lemos o valor de 'n' do usuário
    scanf("%d", &n);
    
    // Loop externo: executa 'n' vezes
    for(int i = 1; i <= n; i++) {
        // Loop interno: executa 2 vezes
        for(int j = 1; j <= 2; j++) {
            // Imprimimos a mensagem "happy chhath pu"
            printf("happy chhath pu");
        }
        // Imprimimos uma quebra de linha após cada iteração do loop externo
        printf("\n");
    }
    // Retornamos 0 para indicar sucesso
    return 0;
}