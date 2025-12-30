/**
 * Classe que representa uma Pilha (Stack)
 */
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



//  Teste Manual: indexStack.js

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

export default Stack;