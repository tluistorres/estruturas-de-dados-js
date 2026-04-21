#include <stdio.h>

int main() {
    int a[7] = {1, 2, 3, 4, 5, 6, 7}; // Array de inteiros
    int sum = 0; // Variável para armazenar a soma
    int i; // Índice do loop

    // Loop para somar os elementos do array
    for (i = 0; i < 7; i++) {
        sum += a[i]; // Adiciona cada elemento ao sum
    }

    // Imprime o resultado
    printf("A soma dos elementos do array é: %d\n", sum);

    return 0; // Finaização do programa
}

// O i < 7 é a condição de parada do loop for.

// Explicação:
// - i é o índice que começa em 0.
// - O array a tem 7 elementos, com índices de 0 a 6.
// - i < 7 significa: "continue o loop enquanto i for menor que 7".
// - Quando i chega a 7, a condição é falsa e o loop para.

// Exemplo:
// - i = 0: a[0] → OK
// - i = 1: a[1] → OK
// - ...
// - i = 6: a[6] → OK
// - i = 7: Sai do loop (não acessa a[7], que não existe).

// Dica:
// - Usar i < sizeof(a) / sizeof(a[0]) é mais seguro, pois evita erros se o array mudar de tamanho.

// for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
//     sum += a[i];
// }
