#include <stdio.h>
// Inicia a função principal do programa
int main() {
    // Declara uma variável 'a' e atribui o valor 5
    int a = 5;
    // Operador ternário: (condição) ? valor_se_verdadeiro : valor_se_falso
    // Se a == 5, msg recebe "Lisboa", senão recebe "Portugal"
    char *msg = (a == 5) ? "Lisboa" : "Portugal";
    // Imprime o valor de msg ("Lisboa")
    printf("%s", msg);
    // Termina o programa com sucesso
    return 0;
}


// O que acontece:- a == 5 é verdadeiro
// - msg recebe "Lisboa"
// - Imprime "Lisboa"

// Se `a` fosse diferente de 5:- Ex: int a = 10;
// - msg receberia "Portugal"
// - Imprime "Portugal"