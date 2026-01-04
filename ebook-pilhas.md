📚 1. O Conceito de Pilha (LIFO)

Imagine uma pilha de pratos: você só consegue colocar um novo prato no topo e só consegue remover o prato que está no topo. Se quiser o prato do fundo, precisa remover todos os de cima primeiro.
Diagrama de Operações:
text
      ENTRADA (Push)          SAÍDA (Pop)
          │                       ▲
          ▼                       │
    ┌───────────┐           ┌───────────┐
    │  Item 3   │ ◄── Topo  │  Item 3   │ (Removido)
    ├───────────┤           ├───────────┤
    │  Item 2   │           │  Item 2   │ ◄── Novo Topo
    ├───────────┤           ├───────────┤
    │  Item 1   │           │  Item 1   │
    └───────────┘           └───────────┘

## 2. Implementação em JavaScript: Stack.js

Nesta implementação moderna, utilizaremos um objeto para armazenar os itens, o que garante 
performance de O(1) para todas as operações.

javascript


# Classe que representa uma Pilha (Stack)
 
class Stack {
  constructor() {
    this.count = 0;   // Rastreador do tamanho da pilha
    this.items = {};  // Armazenamento usando objeto para acesso rápido
  }

  // Adiciona um elemento no topo da pilha (Push)
  push(element) {
    this.items[this.count] = element; // Adiciona o elemento no índice atual
    this.count++; // Incrementa o contador para o próximo item
  }

  // Remove e retorna o elemento do topo da pilha (Pop)
  pop() {
    if (this.isEmpty()) return undefined; // Se estiver vazia, não há o que remover

    this.count--; // Decrementa o contador antes de acessar (pois o count aponta para a próxima vaga livre)
    const result = this.items[this.count]; // Guarda o item do topo
    delete this.items[this.count]; // Remove o item do objeto (limpeza de memória)
    return result; // Retorna o elemento removido
  }

  // Apenas visualiza o elemento no topo sem remover (Peek)
  peek() {
    if (this.isEmpty()) return undefined;
    return this.items[this.count - 1]; // Retorna o último item inserido
  }

  // Verifica se a pilha está vazia
  isEmpty() {
    return this.count === 0;
  }

  // Retorna o tamanho da pilha
  size() {
    return this.count;
  }

  // Esvazia a pilha
  clear() {
    this.items = {}; // Reseta o objeto de armazenamento
    this.count = 0;  // Reseta o contador
  }

  // Exibe a pilha em formato de string [ item1 item2 ]
  toString() {
    if (this.isEmpty()) return '[]';
    
    let values = [];
    for (let i = 0; i < this.count; i++) {
      values.push(this.items[i]);
    }
    return `[ ${values.join(" ")} ]`;
  }
}

export default Stack;

🚀 3. Teste Manual: indexStack.js

javascript

import Stack from './Stack.js';

const pilha = new Stack();

console.log("Pilha está vazia?", pilha.isEmpty()); // true

pilha.push(10); // [ 10 ]
pilha.push(20); // [ 10 20 ]
pilha.push(30); // [ 10 20 30 ]

console.log("Estado atual:", pilha.toString()); // [ 10 20 30 ]
console.log("Topo da pilha (Peek):", pilha.peek()); // 30

console.log("Removendo topo (Pop):", pilha.pop()); // 30
console.log("Novo estado:", pilha.toString()); // [ 10 20 ]
console.log("Tamanho final:", pilha.size()); // 2
Use o código com cuidado.

# 4. Detalhamento da Lógica

1. push(element): Em 2025, usar um objeto {} em vez de um Array [] é uma técnica avançada para 
garantir que a inserção seja sempre constante (O(1)), independente do tamanho da pilha.

2. pop(): É o método mais crítico. Ele deve decrementar o count primeiro, pois se você tem 3 itens 
(índices 0, 1, 2), o count estará em 3 (a próxima vaga). O item do topo está em count - 1.

3. peek(): Útil para algoritmos de decisão onde você precisa saber o que está no topo antes de agir
(ex: processamento de expressões matemáticas).

4. clear(): Assim como na lista ligada, ao resetar o objeto e o contador, o JavaScript limpa a memória 
de todos os itens antigos automaticamente.

Resumo Big O (Performance)

 - Inserção (Push): O(1)

 - Remoção (Pop): O(1)

 - Acesso ao Topo (Peek): O(1)

 - Busca por item: O(n) - Nota: Pilhas não são feitas para buscar itens no meio.

Para visualizar a pilha de chamadas (Call Stack) do próprio JavaScript enquanto estuda, use as 
Ferramentas de Desenvolvedor do Chrome (Painel Sources), que mostra exatamente essa estrutura 
em tempo real.

# Criar o arquivo de execução

Crie um arquivo chamado testaPilha.js e cole o código de teste:


import Stack from './Stack.js';

const pilha = new Stack();
pilha.push(10);
pilha.push(20);
pilha.push(30);

console.log("Pilha completa:", pilha.toString());
console.log("Elemento removido:", pilha.pop());
console.log("Pilha após pop:", pilha.toString());


 - node testaPilha.js

📌 Projeto Prático: Simulador de Histórico de Editor de Texto

Neste exemplo, cada vez que o usuário digita algo, "empilhamos" a ação. Quando ele aperta "Desfazer",
"desempilhamos" a última alteração.

Arquivo: EditorTexto.js

javascript
/**
 * Classe Pilha (Stack) - A base do nosso mecanismo de Undo
 */

class Stack {
  constructor() {
    this.count = 0;
    this.items = {};
  }

  // Adiciona uma nova ação ao topo da pilha
  push(element) {
    this.items[this.count] = element;
    this.count++;
  }

  // Remove e retorna a última ação (a que será desfeita)
  pop() {
    if (this.isEmpty()) return undefined;
    this.count--;
    const result = this.items[this.count];
    delete this.items[this.count];
    return result;
  }

  isEmpty() {
    return this.count === 0;
  }

  toString() {
    if (this.isEmpty()) return 'Vazio';
    let values = [];
    for (let i = 0; i < this.count; i++) {
      values.push(`"${this.items[i]}"`);
    }
    return values.join(" -> ");
  }
}

// --- LOGICA DO EDITOR DE TEXTO ---

const historicoAcoes = new Stack(); // Nossa pilha de "Undo"
let textoAtual = ""; // Representa o texto que o usuário vê

function digitar(novoTexto) {
    console.log(`\nDigitando: "${novoTexto}"`);
    historicoAcoes.push(textoAtual); // Salva o estado ANTERIOR na pilha
    textoAtual += novoTexto;         // Atualiza o texto com a nova digitação
    console.log("Texto na tela:", textoAtual);
}

function desfazer() {
    if (historicoAcoes.isEmpty()) {
        console.log("\nNada para desfazer!");
        return;
    }
    console.log("\n[Botão Desfazer Clicado]");
    textoAtual = historicoAcoes.pop(); // Recupera o último estado salvo
    console.log("Texto na tela após desfazer:", textoAtual);
}

// --- TESTANDO O FLUXO ---

digitar("Olá ");
digitar("Mundo");
digitar(" em 2025!");

console.log("\nHistórico de estados salvos:", historicoAcoes.toString());

desfazer(); // Remove " em 2025!"
desfazer(); // Remove "Mundo"

console.log("\nTexto Final:", textoAtual); // Deve sobrar apenas "Olá "


📚 Por que este projeto é importante para o seu Ebook?

 - Contextualização: O leitor entende que a Pilha não é apenas um conceito abstrato, mas a 
 ferramenta que salva o trabalho dele todos os dias no VS Code.

 - Estado do Objeto: Demonstra como capturar o estado de uma variável (textoAtual) e guardá-lo 
 com segurança.

 - Performance O(1): O "Desfazer" é instantâneo, não importa se você digitou 10 ou 10.000 vezes, 
 pois acessar o topo de um objeto via índice numérico é a operação mais rápida do JavaScript.

Diagrama deste Fluxo (Undo Stack)

AÇÃO 1: "Olá "         AÇÃO 2: "Mundo"       DESFAZER (POP)
┌───────────┐          ┌───────────┐          ┌───────────┐
│           │          │  "Olá "   │          │           │
├───────────┤          ├───────────┤          ├───────────┤
│ (Vazio)   │ ──▶      │ (Vazio)   │ ──▶      │ (Vazio)   │
└───────────┘          └───────────┘          └───────────┘
Pilha guarda o         Pilha guarda o         O topo ("Olá ") 
estado anterior.       estado anterior.       volta a ser o 
                                              texto atual.

Como rodar no terminal:

bash

node EditorTexto.js
