// --- CLASSE NODE (Agora com duas conexões) ---
class Node {
    constructor(data, next = null, prev = null) {
        this.data = data;
        this.next = next;
        this.prev = prev; // Nova conexão para o nó anterior
    }
}

// --- CLASSE DOUBLY LINKED LIST ---
class DoublyLinkedList {
    constructor() {
        this.head = null;
        this.tail = null;
        this.size = 0;
    }

    // Adiciona ao final
    add(newNode) {
        if (!this.head) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            newNode.prev = this.tail; // O novo nó aponta para o antigo último
            this.tail.next = newNode; // O antigo último aponta para o novo
            this.tail = newNode;      // A cauda agora é o novo nó
        }
        this.size++;
    }

    // A mágica da lista dupla: remover é mais simples se você já tem o nó
    remove(value) {
        let current = this.head;

        while (current !== null) {
            if (current.data === value) {
                // Se for a cabeça
                if (current === this.head) {
                    this.head = current.next;
                    if (this.head) this.head.prev = null;
                } 
                // Se for a cauda
                else if (current === this.tail) {
                    this.tail = current.prev;
                    this.tail.next = null;
                } 
                // Se estiver no meio
                else {
                    current.prev.next = current.next;
                    current.next.prev = current.prev;
                }

                this.size--;
                return true;
            }
            current = current.next;
        }
        return false;
    }

    getSize() {
        return this.size;
    }

    // Método para adicionar DEPOIS de um valor específico
insertAfter(targetValue, newData) {
    let current = this.search(targetValue); // Usa o método search que já criamos
    
    if (current === null) return false; // Não achou o alvo

    let newNode = new Node(newData);
    
    // 1. Configura as pontes do novo nó
    newNode.next = current.next;
    newNode.prev = current;

    // 2. Configura a ponte de quem vem depois do novo nó
    if (current.next !== null) {
        current.next.prev = newNode;
    } else {
        this.tail = newNode; // Se inseriu após o último, o novo é o tail
    }

    // 3. Configura a ponte do nó atual para o novo
    current.next = newNode;
    
    this.size++;
    return true;
}


}

// --- FUNÇÃO PARA IMPRIMIR NOS DOIS SENTIDOS ---
function printDoubleList(list) {
    // Normal
    let p = list.head;
    let forward = "Frente: ";
    while (p != null) {
        forward += p.data + (p.next ? " <-> " : " -> null");
        p = p.next;
    }
    console.log(forward);

    // Reverso (Só é possível eficientemente na lista dupla!)
    let b = list.tail;
    let backward = "Trás:   ";
    while (b != null) {
        backward += b.data + (b.prev ? " <-> " : " -> null");
        b = b.prev;
    }
    console.log(backward);
}

// --- TESTE ---
const listaDupla = new DoublyLinkedList();
listaDupla.add(new Node("A"));
listaDupla.add(new Node("B"));
listaDupla.add(new Node("C"));

printDoubleList(listaDupla);