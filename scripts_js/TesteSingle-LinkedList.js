// Define a classe que representa cada elemento (nó) da lista
class Node {
    // O construtor é chamado ao criar um "new Node"
    constructor(data, next = null) {
        this.data = data; // Armazena o valor (ex: "A", "B", etc.)
        this.next = next; // Armazena a referência para o próximo objeto Node (ou null se for o último)
    }

    // Método simples para retornar o valor guardado no nó
    getData() {
        return this.data;
    }
}

class LinkedList {
    // Inicializa uma lista vazia
    constructor() {
        this.head = null; // O primeiro nó da lista (começa vazio)
        this.tail = null; // O último nó da lista (começa vazio)
    }

    // Método para popular a lista manualmente com alguns dados iniciais
    init() {
        this.head = new Node("A");      // Cria o primeiro nó "A" e define como head
        let nodeB = new Node("B");      // Cria o nó "B"
        this.head.next = nodeB;         // Faz o nó "A" apontar para o "B"
        
        let nodeC = new Node("C");      // Cria o nó "C"
        nodeB.next = nodeC;             // Faz o nó "B" apontar para o "C"

        this.tail = new Node("D");      // Cria o nó "D" e define como o tail (cauda)
        nodeC.next = this.tail;         // Faz o nó "C" apontar para o final "D"
    }
    
    // Método para adicionar um novo nó dinamicamente ao final da lista
    add(newNode) {
        // Verifica se a lista está totalmente vazia
        if (!this.head) {
            this.head = newNode;        // O novo nó vira o começo
            this.tail = newNode;        // E também o fim
            return;
        }
        // Se já houver itens:
        this.tail.next = newNode;       // O atual último nó aponta para o novo nó
        this.tail = newNode;            // O ponteiro de cauda agora passa a ser o novo nó
    }
}

// test

// Função externa que recebe o primeiro nó e percorre a lista
function printList(node) {
    let p = node;                       // "p" é o nosso ponteiro de navegação (começa no head)
    let output = "";                    // String para acumular o resultado visual
    
    // Enquanto o ponteiro não chegar em um valor nulo (fim da lista)
    while (p != null) {
        output += p.data + " -> ";      // Pega o dado do nó atual e adiciona à string
        p = p.next;                     // O "p" pula para o próximo nó da corrente
    }
    
    console.log(output + "null");       // Exibe o caminho completo no console
}

// --- Execução ---
const minhaLista = new LinkedList();    // Cria a instância da lista
minhaLista.init();                      // Monta a estrutura A -> B -> C -> D
minhaLista.add(new Node("E"));          // Insere "E" após o "D" usando a lógica do Tail

printList(minhaLista.head);             // Inicia a impressão a partir do primeiro nó (head)

