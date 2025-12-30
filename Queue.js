/**
 * Classe que representa uma Fila (Queue)
 */
class Queue {
  constructor() {
    this.count = 0;          // Rastreador da posição do próximo item (Fim)
    this.lowestCount = 0;    // Rastreador do primeiro item (Início)
    this.items = {};         // Armazenamento
  }

  // Adiciona um elemento ao final da fila (Enqueue)
  enqueue(element) {
    this.items[this.count] = element; // Adiciona no final
    this.count++; // Move o ponteiro do fim para a próxima vaga
  }

  // Remove e retorna o primeiro elemento da fila (Dequeue)
  dequeue() {
    if (this.isEmpty()) return undefined;

    const result = this.items[this.lowestCount]; // Guarda o primeiro item
    delete this.items[this.lowestCount];         // Remove da memória
    this.lowestCount++;                          // Move o ponteiro do início para o próximo
    return result;
  }

  // Apenas visualiza o primeiro elemento (Peek)
  peek() {
    if (this.isEmpty()) return undefined;
    return this.items[this.lowestCount];
  }

  isEmpty() {
    // A fila está vazia se a diferença entre fim e início for zero
    return this.count - this.lowestCount === 0;
  }

  size() {
    return this.count - this.lowestCount;
  }

  clear() {
    this.items = {};
    this.count = 0;
    this.lowestCount = 0;
  }

  // Formata para [ item1 item2 ]
  toString() {
    if (this.isEmpty()) return '[]';
    
    let values = [];
    for (let i = this.lowestCount; i < this.count; i++) {
      values.push(this.items[i]);
    }
    return `[ ${values.join(" ")} ]`;
  }
}


// import Queue from './Queue.js';

const fila = new Queue();

console.log("Inserindo: A, B, C, D");
fila.enqueue("A");
fila.enqueue("B");
fila.enqueue("C");
fila.enqueue("D");

console.log("Fila atual:", fila.toString()); // [ A B C ]
console.log("Primeiro da fila (Peek):", fila.peek()); // A

console.log("Atendendo (Dequeue):", fila.dequeue()); // A
console.log("Fila após atendimento:", fila.toString()); // [ B C ]

console.log("Tamanho atual:", fila.size()); // 2


export default Queue;

