/**
 * Classe que representa a unidade básica da lista (o Nó).
 */
class Node {
  constructor(data, next = null) {
    this.data = data; // Armazena a informação (número, string, etc.)
    this.next = next; // Referência (ponteiro) para o próximo nó da corrente
  }
}

/**
 * Classe que gerencia a Lista Encadeada.
 */
class LinkedList {
  constructor() {
    this.head = null; // A lista começa vazia (sem primeiro elemento)
    this.size = 0;    // Contador total de elementos na lista
  }

  // Insere um elemento no início (Cabeça)
  insertFirst(data) {
    // Cria novo nó apontando para a head antiga e assume o lugar dela
    this.head = new Node(data, this.head); 
    this.size++; // Incrementa o tamanho total
  }

  // Insere um elemento no final da lista
  insertLast(data) {
    let node = new Node(data); // Novo nó (next será null)
    let current;               // Auxiliar para navegação

    if (!this.head) {          // Se a lista estiver vazia...
      this.head = node;        // ...o novo nó vira a cabeça
    } else {                   // Caso contrário...
      current = this.head;     // Começa a percorrer desde o início
      while (current.next) {   // Enquanto houver um próximo nó...
        current = current.next; // ...pula para o próximo
      }
      current.next = node;     // No último nó, conecta o novo
    }
    this.size++;               // Incrementa o tamanho total
  }

  // Insere em uma posição (índice) específica
  insertAt(data, index) {
    // Validação: Se o índice for impossível (menor que zero ou maior que a lista)
    if (index > 0 && index > this.size) return;

    // Se for posição 0, usa a lógica de inserir no início
    if (index === 0) {
      this.insertFirst(data);
      return;
    }

    const node = new Node(data); // Cria o novo nó
    let current, previous;       // Auxiliares para o nó atual e o anterior

    current = this.head;         // Inicia na cabeça
    let count = 0;               // Contador de posição

    while (count < index) {      // Caminha até atingir o índice desejado
      previous = current;        // O atual vira o anterior
      count++;                   // Sobe o contador
      current = current.next;    // O atual vira o próximo
    }

    node.next = current;         // Novo nó aponta para o ocupante atual da vaga
    previous.next = node;        // Nó anterior aponta agora para o novo nó
    this.size++;                 // Incrementa o tamanho total
  }

  // Busca um valor pelo índice
  getAt(index) {
    let current = this.head;     // Inicia na cabeça
    let count = 0;               // Contador
    while (current) {            // Enquanto houver nós...
      if (count == index) {      // Se achar a posição...
        console.log(current.data); // Imprime o valor encontrado
      }
      count++;                   // Sobe contador
      current = current.next;    // Vai para o próximo
    }
    return null;
  }

  // Remove um elemento de uma posição específica
  removeAt(index) {
    if (index > 0 && index > this.size) return; // Validação

    let current = this.head;     // Inicia na cabeça
    let previous;                // Auxiliar para o nó anterior
    let count = 0;               // Contador

    if (index === 0) {           // Se for remover a cabeça...
      this.head = current.next;  // A nova cabeça é o segundo nó
    } else {                     // Se for no meio ou fim...
      while (count < index) {    // Caminha até a posição
        count++;                 // Sobe contador
        previous = current;      // Guarda o anterior
        current = current.next;  // Pula para o próximo
      }
      // O anterior aponta agora para o próximo do atual (pulando o atual)
      previous.next = current.next; 
    }
    this.size--;                 // Decrementa o tamanho total
  }

  // Esvazia a lista e limpa a memória
  clearList() {
    this.head = null;            // Corta o acesso a todos os nós
    this.size = 0;               // Reseta o contador
  }

  /**
   * Imprime a lista no formato: [ valor valor valor ]
   */
  printListData() {
    let current = this.head;      // Começa pela cabeça
    let values = [];              // Array temporário para formatar a saída

    while (current) {             // Percorre toda a corrente
      values.push(current.data);  // Guarda o dado no array
      current = current.next;     // Move para o próximo elo
    }

    // Exibe o array formatado como string dentro de colchetes
    console.log(`[ ${values.join(" ")} ]`); 
  }
}

// --- TESTE DE EXECUÇÃO ---

const ll = new LinkedList();     // Cria a instância da lista

ll.insertFirst(100);             // [ 100 ]
ll.insertFirst(200);             // [ 200 100 ]
ll.insertFirst(300);             // [ 300 200 100 ]
ll.insertLast(400);              // [ 300 200 100 400 ]
ll.insertAt(500, 3);             // [ 300 200 100 500 400 ]

// Saída final: [ 300 200 100 500 400 ]
ll.printListData(); 
