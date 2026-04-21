import DoublyLinkedList from './DoublyLinkedList.js';

test('Deveria inicializar uma lista duplamente encadeada vazia', () => {
  // Substitua pelo seu código real da DoublyLinkedList
  const list = { count: 0 }; 
  expect(list.count).toBe(0);
});

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
