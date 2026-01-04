## Entendendo o Fluxo de Memória

No JavaScript, os métodos de array se dividem em dois tipos principais que você precisa dominar para evitar bugs em estruturas_de_dados:

 - Mutáveis: Alteram o array original (ex: push, pop, splice, sort).

 - Imutáveis: Retornam um novo array, preservando o original (ex: map, filter, slice). Isso é a base do desenvolvimento moderno (React, por exemplo).

## Diagrama de Procedimento: Métodos de Iteração

Este diagrama detalha como o motor do JavaScript (V8) processa métodos como map e filter por debaixo dos panos:

Resumo do Procedimento

Entrada: Um array de elementos.

Callback: Uma função que você define para ser executada em cada item.

Execução: O JS percorre o array (index 0 até N).

Saída: Depende do método (Novo array para map, Booleano para some, Valor único para reduce).

## Exemplo Prático: Sistema de Carrinho

Neste código, vamos calcular o total, aplicar desconto e remover itens.

// O Array de Objetos (representando produtos)

const carrinho = [
    { nome: "Mouse Gamer", preco: 150, qtd: 1 },
    
    { nome: "Teclado Mecânico", preco: 300, qtd: 1 },
    
    { nome: "Monitor 144hz", preco: 1200, qtd: 2 }
];

// 1. MAP: Criar uma lista apenas com os nomes dos produtos

const nomesProdutos = carrinho.map(item => item.nome);

console.log("Itens no carrinho:", nomesProdutos);

// 2. FILTER: Filtrar apenas produtos que custam mais de 200 reais

const produtosCaros = carrinho.filter(item => item.preco > 200);

// 3. REDUCE: Calcular o valor TOTAL do carrinho

// (acumulador, item) => lógica, valor inicial

const totalGeral = carrinho.reduce((total, item) => {
    return total + (item.preco * item.qtd);
}, 0);

console.log(`Total a pagar: R$ ${totalGeral}`);

// 4. FIND: Localizar um produto específico para dar um detalhe

const teclado = carrinho.find(item => item.nome === "Teclado Mecânico");

console.log("Detalhes do teclado:", teclado);

Procedimento Detalhado (Como o Array é processado)

Para entender a lógica, imagine que o JavaScript faz uma varredura (loop) automática para você. 
No caso do reduce, o procedimento segue este fluxo:

 - Inicialização: O total começa em 0 (valor que definimos no final).
 
  - Passo 1: Pega o Mouse (150). Total agora é 150.
  
  - Passo 2: Pega o Teclado (300). Total agora é 450.
   
  - Passo 3: Pega o Monitor (1200 * 2 = 2400). Total final é 2850.
  
  ## Comparação de Procedimentos
  
  | Método | Entrada (Input) | Procedimento | Saída (Output) |
| --- | --- | --- | --- |
| Map | Array [A, B, C] | Transforma cada item | Novo Array [A', B', C'] |
| Filter | Array [A, B, C] | Testa uma condição | Novo Array [A, C] (só os que passaram) |
| Reduce | Array [A, B, C] | Acumula os valores | Um único valor (Número ou String) |