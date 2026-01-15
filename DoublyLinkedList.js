/**
 * Classe que representa o Nó de uma Lista Dupla.
 * Contém o elemento, o ponteiro para o próximo e o ponteiro para o anterior.
 */
class DoublyNode {
    constructor(element) {
        this.element = element;
        this.next = null;
        this.prev = null; // Link para o nó anterior
    }
}

/**
 * Classe principal da Lista Duplamente Encadeada.
 */
class DoublyLinkedList {
    constructor() {
        this.count = 0;
        this.head = null;
        this.tail = null; // Referência direta ao último elemento
    }

    // Insere um elemento em qualquer posição
    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = new DoublyNode(element);
            let current = this.head;

            if (index === 0) { // Inserção no início
                if (this.head == null) {
                    this.head = node;
                    this.tail = node;
                } else {
                    node.next = this.head;
                    this.head.prev = node;
                    this.head = node;
                }
            } else if (index === this.count) { // Inserção no final
                current = this.tail;
                current.next = node;
                node.prev = current;
                this.tail = node;
            } else { // Inserção no meio usando laço for
                let previous;
                for (let i = 0; i < index; i++) {
                    previous = current;
                    current = current.next;
                }
                // Conectando o novo nó
                node.next = current;
                node.prev = previous;
                // Reencadeando os vizinhos
                previous.next = node;
                current.prev = node;
            }
            this.count++;
            return true;
        }
        return false;
    }

    // Remove um elemento de uma posição específica
    removeAt(index) {
        if (index >= 0 && index < this.count) {
            let current = this.head;

            if (index === 0) { // Remover do início
                this.head = current.next;
                if (this.count === 1) {
                    this.tail = null;
                } else {
                    this.head.prev = null;
                }
            } else if (index === this.count - 1) { // Remover do final
                current = this.tail;
                this.tail = current.prev;
                this.tail.next = null;
            } else { // Remover do meio com laço for
                for (let i = 0; i < index; i++) {
                    current = current.next;
                }
                const previous = current.prev;
                // Pula o 'current' fazendo a ponte direta
                previous.next = current.next;
                current.next.prev = previous;
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
            if (element === current.element) return i;
            current = current.next;
        }
        return -1;
    }

    isEmpty() {
        return this.count === 0;
    }

    size() {
        return this.count;
    }

    getHead() {
        return this.head;
    }

    getTail() {
        return this.tail;
    }

    // Converte a lista para string separada por vírgulas
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
    

    inverseToString() {
        if (this.tail == null) return '';
        let objString = `${this.tail.element}`;
        let previous = this.tail.prev;
        while (previous != null) {
        objString = `${objString}, ${previous.element}`;
        previous = previous.prev;
        
        }
        return objString;
    }
}

// ESSENCIAL: Exportação padrão para o ES Modules (index.js e Jest)
export default DoublyLinkedList;

