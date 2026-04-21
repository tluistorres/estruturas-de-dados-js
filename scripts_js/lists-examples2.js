class Node {
    constructor(value) {
        this.value = value;
        this.next = null; 
    }
}

class List {
    constructor() {
        this.head = null; 
    }

    // O método deve estar DENTRO da classe e sem o ";" após o nome
    append(value) {
        const newNode = new Node(value);
        if (this.head === null) {
            this.head = newNode;
        } else {
            let current = this.head;
            while (current.next !== null) { 
                current = current.next;
            }
            current.next = newNode; // Faltava conectar o novo nó ao final
        }
    }

    get(position) {
        if (position > -1) {
            let current = this.head;
            let i = 0;
            while (current !== null && i < position) {
                current = current.next;
                i++;
            }
            return current !== null ? current.value : undefined;
        } else {
            return undefined;
        }
    }

    delete(position) { // Corrigido: delet -> delete
        if (this.head === null || position < 0) {
            throw new RangeError(`Sem item na posição ${position}`);
        }

        if (position === 0) {
            this.head = this.head.next;
            return true;
        }

        let current = this.head;
        let previous = null;
        let i = 0;

        while (current !== null && i < position) {
            previous = current; // Salva o anterior para "pular" o atual depois
            current = current.next;
            i++;
        }

        if (current !== null) {
            previous.next = current.next; // Remove o nó atual da corrente
            return true;
        }
        
        throw new RangeError(`Sem item na posição ${position}`);
    }

    values() {
        let current = this.head;
        let values = [];
        while (current !== null) {
            values.push(current.value); // Corrigido: era createSecureContext
            current = current.next;
        }
        return values;
    }
}

// Demonstração de uso:
const list = new List();
list.append(1);
list.append(2);
list.append(3);

console.log("Valores iniciais:", list.values()); // [1, 2, 3]
list.delete(1); // Remove o '2'
list.append(4);

console.log("Após deletar pos(1) e adicionar 4:", list.values()); // [1, 3, 4]
console.log("Valor na posição 2:", list.get(2)); // 4

export default List;

