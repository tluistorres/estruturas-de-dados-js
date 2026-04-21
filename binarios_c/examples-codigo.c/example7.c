#include <stdio.h>
// Inicia a função principal do programa
int main() {
    // Declara variáveis 'a' e 'b' com valores iniciais
    int a = 0;
    int b = 5;
    // Operador && (E lógico) com pós-incremento
    // a++ == 0 → verdadeiro (a vira 1)
    // Como o primeiro é verdadeiro, avalia o segundo: b++ == 5 → verdadeiro (b vira 6)
    if (a++ == 0 && b++ == 5)
        // Como a condição é verdadeira, imprime os valores
        printf("a=%d b=%d", a, b);
    // Termina o programa com sucesso
    return 0;
}


// O que acontece:- a = 0, b = 5
// - a++ == 0 é verdadeiro (usa 0, depois a vira 1)
// - b++ == 5 é verdadeiro (usa 5, depois b vira 6)
// - a = 1, b = 6
// - Imprime a=1 b=6

// Se o primeiro fosse falso:- Ex: if (a++ == 1 && b++ == 5)
// - a++ == 1 é falso (usa 0, depois a vira 1)
// - Não avalia o b++ (curto-circuito do &&)
// - a = 1, b = 5 (inalterado)
