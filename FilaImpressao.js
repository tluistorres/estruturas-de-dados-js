/**
 * Classe que representa a estrutura de dados Fila
 */
class Queue {
  constructor() {
    this.count = 0;          // Monitora o final da fila (onde novos itens entram)
    this.lowestCount = 0;    // Monitora o início da fila (de onde itens saem)
    this.items = {};         // Objeto que armazena os elementos
  }

  // Adiciona um documento para o final da fila
  enqueue(element) {
    this.items[this.count] = element; // Adiciona o documento no índice atual do fim
    this.count++;                     // Prepara a próxima posição do fim
  }

  // Remove e retorna o documento do início (o que será impresso)
  dequeue() {
    if (this.isEmpty()) return undefined; // Se não houver documentos, retorna nada

    const result = this.items[this.lowestCount]; // Armazena o documento do início
    delete this.items[this.lowestCount];         // Remove o documento processado da memória
    this.lowestCount++;                          // Move o ponteiro do início para o próximo documento
    return result;                               // Retorna o documento que foi "impresso"
  }

  // Apenas espia qual é o próximo documento na vez
  peek() {
    if (this.isEmpty()) return undefined;
    return this.items[this.lowestCount];
  }

  // Verifica se ainda existem documentos na fila
  isEmpty() {
    return this.count - this.lowestCount === 0;
  }

  // Retorna a quantidade de documentos aguardando
  size() {
    return this.count - this.lowestCount;
  }

  // Formata a fila para exibição visual: [ doc1 doc2 ]
  toString() {
    if (this.isEmpty()) return '[]';
    let values = [];
    for (let i = this.lowestCount; i < this.count; i++) {
      values.push(this.items[i]);
    }
    return `[ ${values.join(" ")} ]`;
  }
}

// --- EXEMPLO PRÁTICO: SIMULADOR DE IMPRESSORA ---

const impressoraHP = new Queue(); // Instancia nossa fila de impressão

console.log("--- Enviando documentos para a impressora ---");
impressoraHP.enqueue("Relatorio_Financeiro.pdf");
impressoraHP.enqueue("Foto_Ferias.jpg");
impressoraHP.enqueue("Contrato_Aluguel.docx");

console.log("Documentos na fila:", impressoraHP.toString()); 
// Saída: [ Relatorio_Financeiro.pdf Foto_Ferias.jpg Contrato_Aluguel.docx ]

console.log("\nQual o próximo documento da vez?", impressoraHP.peek());
// Saída: Relatorio_Financeiro.pdf

console.log("\n--- Iniciando impressões ---");
console.log("Imprimindo agora:", impressoraHP.dequeue()); // Imprime o Financeiro
console.log("Imprimindo agora:", impressoraHP.dequeue()); // Imprime a Foto

console.log("\nQuantos documentos restam?", impressoraHP.size()); 
// Saída: 1

console.log("Fila atualizada:", impressoraHP.toString());
// Saída: [ Contrato_Aluguel.docx ]
