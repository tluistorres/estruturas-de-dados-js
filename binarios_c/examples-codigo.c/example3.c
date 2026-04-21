// #include <stdio.h>

// int main() {
//     int a = 5;
//     if (a++ == 5)
//         printf("Brasil");
//     else if (a++ == 7)
//         printf("Alagoas");
//     else
//         printf("Igaci");
//     return 0;    
// }

#include <stdio.h>
// Inicia a função principal do programa
int main() {
    // Declara uma variável 'a' e atribui o valor 5
    int a = 5;
    // Verifica se o valor atual de 'a' (5) é igual a 5
    // Depois, incrementa 'a' para 6 (pós-incremento)
    if (a++ == 5)
        // Se a condição for verdadeira, imprime "Brasil"
        printf("Brasil");
    // Se a primeira condição for falsa, verifica essa
    else if (a++ == 7)
        // 'a' agora vale 6 (do incremento anterior), então isso é falso
        // Depois, incrementa 'a' para 7
        printf("Alagoas");
    // Se nenhuma das anteriores for verdadeira, imprime "Igaci"
    else
        printf("Igaci");
    // Termina o programa com sucesso
    return 0;
}


// O que acontece:- a = 5
// - a++ == 5 é verdadeiro, então imprime "Brasil"
// - a vira 6
// - O resto é ignorado

// Saída:
// Brasil
