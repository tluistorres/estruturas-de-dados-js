#include <stdio.h>

int main () {
    char name[] = "coding";

printf("%c", name[3]);
return 0;
};

// - %c é usado para imprimir um caractere (char).
// - name[3] é o caractere 'i'.
// - Saída: i

// Dedução:- %d imprime o valor numérico 

// - %d é usado para imprimir um número inteiro (int).
// - name[3] é o caractere 'i' (índice 3 da string "coding").
// - O caractere 'i' é convertido para o valor ASCII correspondente (105).
// - Saída: 105