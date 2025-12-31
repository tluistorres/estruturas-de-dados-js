/**
 * Representa um nó individual na lista
 */
class Node {
  constructor(element) {
    this.element = element; // Armazena o valor (conteúdo) do nó
    this.next = undefined;  // Referência (ponteiro) para o próximo nó da lista
  }
}

/**
 * Função auxiliar para comparar se dois elementos são iguais
 */
function defaultEquals(a, b) {
  return a === b; // Retorna true se forem idênticos
}

/**
 * Classe principal da Lista Encadeada
 */
export default class LinkedList {
  constructor(equalsFn = defaultEquals) {
    this.count = 0;           // Mantém o rastro do número de elementos na lista
    this.head = undefined;    // O primeiro nó da lista (o ponto de entrada)
    this.equalsFn = equalsFn; // Permite passar funções de comparação personalizadas
  }

  // Adiciona um elemento ao FINAL da lista
  push(element) {
    const node = new Node(element); // Cria um novo nó com o valor fornecido
    if (!this.head) {               // Se a lista estiver vazia (sem cabeça)...
      this.head = node;             // ...o novo nó torna-se a cabeça
    } else {
      let current = this.head;      // Começa a busca a partir do primeiro nó
      while (current.next) {        // Enquanto existir um "próximo" nó...
        current = current.next;     // ...pula para o próximo nó
      }
      current.next = node;          // Encontrou o último? Faz o "next" dele apontar para o novo nó
    }
    this.count++;                   // Incrementa o tamanho total da lista
  }

  // Busca um NÓ em um índice específico
  getElementAt(index) {
    if (index >= 0 && index < this.count) { // Verifica se o índice está dentro dos limites
      let node = this.head;                 // Começa pelo primeiro nó
      for (let i = 0; i < index && node != null; i++) { // Percorre até chegar no índice
        node = node.next;                   // Move para o próximo nó
      }
      return node;                          // Retorna o nó encontrado
    }
    return undefined;                       // Índice inválido ou não encontrado
  }

  // Insere um elemento em QUALQUER posição
  insert(element, index) {
    if (index >= 0 && index <= this.count) { // Valida se o índice de inserção é possível
      const node = new Node(element);        // Cria o novo nó
      if (index === 0) {                     // Se for para inserir no início...
        node.next = this.head;               // O novo nó aponta para a antiga cabeça
        this.head = node;                    // A cabeça da lista passa a ser o novo nó
      } else {
        const previous = this.getElementAt(index - 1); // Localiza o nó anterior à posição
        node.next = previous.next;           // O novo nó aponta para onde o anterior apontava
        previous.next = node;                // O anterior agora aponta para o novo nó
      }
      this.count++;                          // Aumenta o contador
      return true;                           // Sucesso na operação
    }
    return false;                            // Falha (índice fora de alcance)
  }

  // Remove um elemento por ÍNDICE
  removeAt(index) {
    if (index >= 0 && index < this.count) {  // Valida o índice
      let current = this.head;               // Referência para o nó atual
      if (index === 0) {                     // Caso especial: remover o primeiro
        this.head = current.next;            // A cabeça passa a ser o segundo nó
      } else {
        const previous = this.getElementAt(index - 1); // Busca o nó anterior
        current = previous.next;             // O nó a ser removido é o próximo do anterior
        previous.next = current.next;        // O anterior "pula" o atual e aponta para o próximo
      }
      this.count--;                          // Diminui o contador
      return current.element;                // Retorna o valor do nó deletado
    }
    return undefined;                        // Índice inválido
  }

  // Encontra a POSIÇÃO de um valor na lista
  indexOf(element) {
    let current = this.head;                 // Começa pelo início
    for (let i = 0; i < this.count && current != null; i++) { // Loop por toda a lista
      if (this.equalsFn(element, current.element)) { // Se o valor for o que buscamos...
        return i;                            // Retorna o índice atual
      }
      current = current.next;                // Senão, vai para o próximo
    }
    return -1;                               // Se percorreu tudo e não achou, retorna -1
  }

  // Remove um elemento pelo VALOR
  remove(element) {
    const index = this.indexOf(element);     // Primeiro descobre onde ele está
    return this.removeAt(index);             // Depois usa o método de remover por índice
  }

  size() { return this.count; }              // Retorna o total de itens
  isEmpty() { return this.size() === 0; }    // Retorna true se estiver vazia
  getHead() { return this.head; }            // Retorna o nó inicial (head)

  // Converte a lista para uma string legível
  toString() {
    if (!this.head) { return '[ ]'; }        // Se vazia, retorna representação vazia
    let objString = `[ ${this.head.element}`; // Inicia com o primeiro elemento
    let current = this.head.next;            // Pega o segundo elemento para o loop
    while (current != null) {                // Enquanto houver nós...
      objString = `${objString}, ${current.element}`; // Concatena o valor na string
      current = current.next;                // Avança na lista
    }
    return `${objString} ]`;                 // Fecha o colchete e retorna
 
  }
}


const list = new LinkedList();
list.push("Café");
list.push("Açúcar");
list.push("Leite");

console.log(list.toString()); // [ Café, Açúcar, Leite ]

list.remove("Açúcar"); // O usuário não precisa saber que o açúcar está no índice 1

console.log(list.toString()); // [ Café, Leite ]