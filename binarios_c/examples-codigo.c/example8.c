#include <stdio.h>
// Inicia a função principal do programa
int main() {
    // Declara uma variável 'c' do tipo char com valor 'a'
    char c = 'a';
    // switch: testa o valor de 'c'
    switch (c) {
        // Se c == 'a', executa esse caso
        case 'a':
            // Imprime "alpha"
            printf("alpha");
            // break: sai do switch
            break;
        // Se nenhum case for verdadeiro, executa default
        default:
            printf("outro");
    }
    // Termina o programa com sucesso
    return 0;
}


// O que acontece:- c = 'a'
// - switch (c) testa o valor de c
// - case 'a' é verdadeiro
// - Imprime "alpha"
// - break sai do switch
// - Não executa o default

// Se `c` fosse diferente:- Ex: char c = 'b';
// - case 'a' é falso
// - Vai para default
// - Imprime "outro"

// Se não tivesse `break`:
// switch (c) {
//     case 'a':
//         printf("alpha");
//     default:
//         printf("outro");
// }

// - c = 'a' → imprime "alphaoutro"
