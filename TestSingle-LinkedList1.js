// --- CLASSE NODE (O VAGÃO) ---
class Node {
    constructor(data, next = null) {
        this.data = data; // Informação guardada
        this.next = next; // Endereço do próximo nó
    }
}

// --- CLASSE LINKEDLIST (O TREM) ---
class LinkedList {
    constructor() {
        this.head = null; // Início da lista
        this.tail = null; // Fim da lista
        this.size = 0;    // Contador interno para o tamanho
    }

    // Inicializa a lista manualmente (A -> B -> C -> D)
    init() {
        this.add(new Node("A"));
        this.add(new Node("B"));
        this.add(new Node("C"));
        this.add(new Node("D"));
    }

    // Adiciona ao final: O(1) de performance graças ao tail
    add(newNode) {
        if (!this.head) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            this.tail.next = newNode; // O antigo último aponta para o novo
            this.tail = newNode;      // O novo vira o novo último
        }
        this.size++; // Aumenta o contador
    }

    // Busca um valor: O(n) pois percorre a lista
    search(value) {
        let current = this.head;
        while (current !== null) {
            if (current.data === value) return current;
            current = current.next;
        }
        return null;
    }

    // Remove um nó: O(n) pois precisa encontrar o anterior
    remove(value) {
        if (!this.head) return;

        // Caso seja o primeiro nó
        if (this.head.data === value) {
            this.head = this.head.next;
            if (this.head === null) this.tail = null;
            this.size--; // Diminui o contador
            return;
        }

        let current = this.head;
        while (current.next !== null) {
            if (current.next.data === value) {
                // Se for remover o último, atualiza o tail
                if (current.next === this.tail) {
                    this.tail = current;
                }
                current.next = current.next.next; // "Pula" o nó removido
                this.size--; // Diminui o contador
                return;
            }
            current = current.next;
        }
    }

    // Retorna o tamanho atual sem precisar contar tudo de novo
    getSize() {
        return this.size;
    }
}

// --- FUNÇÃO DE IMPRESSÃO ---
function printList(list) {
    let p = list.head;
    let output = "";
    while (p != null) {
        output += p.data + " -> ";
        p = p.next;
    }
    console.log(output + "null");
}

// --- TESTE PRÁTICO ---
const lista = new LinkedList();
lista.init();             // A -> B -> C -> D (Size: 4)
lista.add(new Node("E")); // A -> B -> C -> D -> E (Size: 5)

console.log("Lista Atual:");
printList(lista);
console.log("Tamanho da lista:", lista.getSize()); // Saída: 5

console.log("\n--- Removendo 'B' ---");
lista.remove("B");
printList(lista);
console.log("Novo tamanho:", lista.getSize()); // Saída: 4