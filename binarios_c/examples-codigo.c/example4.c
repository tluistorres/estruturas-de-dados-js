#include <stdio.h>

int main() {
    int a = 4, b = 2, result;

    // A expressão abaixo envolve operadores de pré e pós-incremento
    result = a++ * --b + b++;

    // Imprime os valores finais de a, b e result
    printf("%d %d %d", a, b, result);

    return 0;
}     

// Explicação detalhada1. Início:
//     - a = 4
//     - b = 2

// 2. Avaliação da expressão:
//     - --b: b vira 1 e retorna 1.
//     - a++: usa a (4) e incrementa a para 5.
//     - b++: usa b (1) e incrementa b para 2.
//     - A expressão fica: 4 * 1 + 1 = 5.
//     - result = 5.

// 3. Valores finais:
//     - a = 5 (pós-incremento)
//     - b = 2 (pós-incremento)
//     - result = 5
