class DoublyNode {
    constructor(element) {
        this.element = element;
        this.next = null;
        this.prev = null; // A nova conexão para o nó anterior
    }
}

class DoublyLinkedList {
    constructor() {
        this.count = 0;
        this.head = null;
        this.tail = null; // Referência ao último elemento
    }

    // Inserção em qualquer posição com laço for
    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = new DoublyNode(element);
            let current = this.head;

            if (index === 0) { // Inserir no início
                if (this.head == null) {
                    this.head = node;
                    this.tail = node;
                } else {
                    node.next = this.head;
                    this.head.prev = node;
                    this.head = node;
                }
            } else if (index === this.count) { // Inserir no final (tail)
                current = this.tail;
                current.next = node;
                node.prev = current;
                this.tail = node;
            } else { // Inserir no meio usando laço for
                let previous;
                for (let i = 0; i < index; i++) {
                    previous = current;
                    current = current.next;
                }
                node.next = current;
                node.prev = previous;
                previous.next = node;
                current.prev = node;
            }
            this.count++;
            return true;
        }
        return false;
    }

    // Remoção de posição específica
    removeAt(index) {
        if (index >= 0 && index < this.count) {
            let current = this.head;

            if (index === 0) { // Remover o primeiro
                this.head = current.next;
                if (this.count === 1) {
                    this.tail = null;
                } else {
                    this.head.prev = null;
                }
            } else if (index === this.count - 1) { // Remover o último
                current = this.tail;
                this.tail = current.prev;
                this.tail.next = null;
            } else { // Remover do meio com laço for
                for (let i = 0; i < index; i++) {
                    current = current.next;
                }
                const previous = current.prev;
                previous.next = current.next;
                current.next.prev = previous;
            }
            this.count--;
            return current.element;
        }
        return undefined;
    }

    indexOf(element) {
        let current = this.head;
        for (let i = 0; i < this.count && current != null; i++) {
            if (element === current.element) return i;
            current = current.next;
        }
        return -1;
    }

    size() { return this.count; }
    isEmpty() { return this.size() === 0; }
    getHead() { return this.head; }
    getTail() { return this.tail; }

    toString() {
        if (this.head == null) return '';
        let objString = `${this.head.element}`;
        let current = this.head.next;
        while (current != null) {
            objString = `${objString}, ${current.element}`;
            current = current.next;
        }
        return objString;
    }
}

export default DoublyLinkedList;

//////////////////////////////////////////////////////////////

// import DoublyLinkedList from './DoublyLinkedList.js';

const list = new DoublyLinkedList();

console.log("--- Testando Inserção ---");
list.insert("Elemento A", 0); // Início: [A]
list.insert("Elemento C", 1); // Fim: [A, C]
list.insert("Elemento B", 1); // Meio: [A, B, C]
console.log("Lista (toString):", list.toString()); 
console.log("Tamanho (size):", list.size());

console.log("\n--- Testando Posições e Referências ---");
console.log("Cabeça (head):", list.getHead().element);
console.log("Cauda (tail):", list.getTail().element);
console.log("Índice do 'B':", list.indexOf("Elemento B"));

console.log("\n--- Testando Remoção ---");
const removido = list.removeAt(1); // Remove "B"
console.log("Removido:", removido);
console.log("Lista após remoção:", list.toString());
console.log("Nova Cauda:", list.getTail().element);

console.log("\n--- Verificando se está vazia ---");
console.log("Está vazia?", list.isEmpty());
