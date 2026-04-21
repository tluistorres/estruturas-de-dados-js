class Node {
    constructor(element) {
        this.element = element;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.count = 0;
        this.head = null;
    }

    // Insere em uma posição específica (usando laço for)
    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = new Node(element);
            if (index === 0) { // Início da lista
                node.next = this.head;
                this.head = node;
            } else {
                let previous = this.head;
                // Laço for para atingir a posição desejada
                for (let i = 0; i < index - 1; i++) {
                    previous = previous.next;
                }
                node.next = previous.next;
                previous.next = node;
            }
            this.count++;
            return true;
        }
        return false;
    }

    // Remove de uma posição específica
    removeAt(index) {
        if (index >= 0 && index < this.count) {
            let current = this.head;
            if (index === 0) {
                this.head = current.next;
            } else {
                let previous = this.head;
                for (let i = 0; i < index - 1; i++) {
                    previous = previous.next;
                }
                current = previous.next;
                previous.next = current.next;
            }
            this.count--;
            return current.element;
        }
        return undefined;
    }

    // Retorna o índice de um elemento
    indexOf(element) {
        let current = this.head;
        for (let i = 0; i < this.count && current != null; i++) {
            if (element === current.element) {
                return i;
            }
            current = current.next;
        }
        return -1;
    }

    size() {
        return this.count;
    }

    isEmpty() {
        return this.size() === 0;
    }

    getHead() {
        return this.head;
    }

    toString() {
        if (this.head == null) return '';
        let objString = `${this.head.element}`;
        let current = this.head.next;
        for (let i = 1; i < this.size() && current != null; i++) {
            objString = `${objString}, ${current.element}`;
            current = current.next;
        }
        return objString;
    }
}

export default LinkedList;


const lista = new LinkedList();

console.log("Está vazia?", lista.isEmpty()); // true

lista.insert("A", 0); // [A]
lista.insert("C", 1); // [A, C]
lista.insert("B", 1); // [A, B, C] - Inseriu na posição 1 usando o laço for

console.log("Lista atual:", lista.toString()); // "A, B, C"
console.log("Tamanho:", lista.size());         // 3
console.log("Posição do elemento 'B':", lista.indexOf("B")); // 1

lista.removeAt(2); // Remove o "C"
console.log("Após remover posição 2:", lista.toString()); // "A, B"