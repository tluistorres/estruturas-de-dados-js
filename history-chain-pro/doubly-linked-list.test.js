// Nó específico para lista dupla
class DoublyNode {
  constructor(element) {
    this.element = element;
    this.next = undefined; // Ponteiro para o próximo
    this.prev = undefined; // Ponteiro para o anterior (A NOVIDADE!)
  }
}

export default class DoublyLinkedList {
  constructor() {
    this.count = 0;
    this.head = undefined;
    this.tail = undefined; // Referência para o ÚLTIMO nó
  }

  // Na lista dupla, inserir no final é instantâneo (O(1)) 
  // porque temos a referência "this.tail"
  push(element) {
    const node = new DoublyNode(element);
    if (!this.head) {
      this.head = node;
      this.tail = node;
    } else {
      node.prev = this.tail;
      this.tail.next = node;
      this.tail = node;
    }
    this.count++;
  }
}