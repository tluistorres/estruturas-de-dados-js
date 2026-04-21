#include <stdio.h>
// Inicia a função principal do programa
int main() {
    // Declara uma variável 'a' e atribui o valor 5
    int a = 5;
    // Usa pré-incremento: incrementa 'a' para 6 E DEPOIS compara com 6
    if (++a == 6)
        // Como 6 == 6, a condição é verdadeira, imprime "Alemanha"
        printf("Alemanha");
    else
        // Não entra aqui
        printf("Berlim");
    // Termina o programa com sucesso
    return 0;
}


// O que acontece:- a = 5
// - ++a → a vira 6
// - 6 == 6 é verdadeiro
// - Imprime "Alemanha"
// - a termina valendo 6

// Se fosse `a++` (pós-incremento):- a++ == 5 seria verdadeiro (usa o valor 5, depois incrementa para 6)
