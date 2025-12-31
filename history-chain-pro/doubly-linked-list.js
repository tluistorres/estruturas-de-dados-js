// doubly-linked-list.js

// 1. Defina o Nó Duplo (não precisa de export se for usado só aqui)
class DoublyNode {
  constructor(element) {
    this.element = element;
    this.next = undefined;
    this.prev = undefined; 
  }
}

// 2. ADICIONE O 'export default' ANTES DA CLASSE
export default class DoublyLinkedList {
  constructor() {
    this.count = 0;
    this.head = undefined;
    this.tail = undefined;
  }

  // Seus métodos aqui...
  push(element) {
    const node = new DoublyNode(element);
    if (!this.head) {
      this.head = node;
      this.tail = node;
    } else {
      this.tail.next = node;
      node.prev = this.tail;
      this.tail = node;
    }
    this.count++;
  }

  isEmpty() {
    return this.count === 0;
  }
  
  // Adicione um toString básico para teste
  toString() {
    if (!this.head) return '[ ]';
    let s = `[ ${this.head.element}`;
    let curr = this.head.next;
    while(curr) {
      s += `, ${curr.element}`;
      curr = curr.next;
    }
    return s + ' ]';
  }removeAt(index) {
  if (index >= 0 && index < this.count) {
    let current = this.head;

    // Caso 1: Remover o primeiro elemento
    if (index === 0) {
      this.head = current.next;
      // Se a lista tinha apenas um elemento, o tail também deve ser limpo
      if (this.count === 1) {
        this.tail = undefined;
      } else {
        this.head.prev = undefined; // O novo primeiro não tem anterior
      }
    } 
    // Caso 2: Remover o último elemento (MUITO MAIS RÁPIDO NA LISTA DUPLA)
    else if (index === this.count - 1) {
      current = this.tail;
      this.tail = current.prev;
      this.tail.next = undefined; // O novo último não tem próximo
    } 
    // Caso 3: Remover do meio
    else {
      const previous = this.getElementAt(index - 1);
      current = previous.next;
      const next = current.next;

      previous.next = next; // Liga o anterior ao próximo
      next.prev = previous; // Liga o próximo de volta ao anterior
    }

    this.count--;
    return current.element;
  }
  return undefined;
}

  removeAt(index) {
  if (index >= 0 && index < this.count) {
    let current = this.head;

    // Caso 1: Remover o primeiro elemento
    if (index === 0) {
      this.head = current.next;
      // Se a lista tinha apenas um elemento, o tail também deve ser limpo
      if (this.count === 1) {
        this.tail = undefined;
      } else {
        this.head.prev = undefined; // O novo primeiro não tem anterior
      }
    } 
    // Caso 2: Remover o último elemento (MUITO MAIS RÁPIDO NA LISTA DUPLA)
    else if (index === this.count - 1) {
      current = this.tail;
      this.tail = current.prev;
      this.tail.next = undefined; // O novo último não tem próximo
    } 
    // Caso 3: Remover do meio
    else {
      const previous = this.getElementAt(index - 1);
      current = previous.next;
      const next = current.next;

      previous.next = next; // Liga o anterior ao próximo
      next.prev = previous; // Liga o próximo de volta ao anterior
    }

    this.count--;
    return current.element;
  }
  return undefined;
}

  // Retorna o número de elementos na lista
  size() {
    return this.count;
  }

  // Retorna true se a lista estiver vazia
  isEmpty() {
    return this.count === 0;
  }

  
  clear() {
    this.head = undefined;
    this.tail = undefined;
    this.count = 0;
  }

}

