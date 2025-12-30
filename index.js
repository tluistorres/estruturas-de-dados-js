import DoublyLinkedList from './DoublyLinkedList.js';

const list = new DoublyLinkedList();

console.log("=== TESTES MANUAIS: LISTA DUPLAMENTE ENCADEADA ===\n");

// 1. Testando isEmpty e size inicial
console.log("1. A lista está vazia?", list.isEmpty()); // true
console.log("2. Tamanho inicial:", list.size());       // 0

// 2. Testando inserção em diversas posições (Método insert com laço for)
console.log("\n--- Inserindo elementos ---");
list.insert("Elemento B", 0); // [B]
list.insert("Elemento A", 0); // [A, B] (Inserção no início)
list.insert("Elemento D", 2); // [A, B, D] (Inserção no fim/tail)
list.insert("Elemento C", 2); // [A, B, C, D] (Inserção no meio usando for)

console.log("3. Lista após inserções (toString):", list.toString()); 
// Saída esperada: "Elemento A, Elemento B, Elemento C, Elemento D"

// 3. Testando referências Head e Tail
console.log("\n--- Verificando Referências ---");
console.log("4. Cabeça (getHead):", list.getHead().element); // Elemento A
console.log("5. Cauda (getTail):", list.getTail().element);   // Elemento D

// 4. Provando a Conexão Dupla (Ponteiro Prev)
console.log("\n--- Provando a Conexão Dupla (Retrocesso) ---");
const ultimo = list.getTail();
console.log("6. Último elemento:", ultimo.element);
console.log("7. Anterior do último (prev):", ultimo.prev.element); // Elemento C

// 5. Testando indexOf
console.log("\n--- Testando Índices ---");
console.log("8. Índice do 'Elemento C':", list.indexOf("Elemento C")); // 2
console.log("9. Índice de inexistente:", list.indexOf("Elemento Z"));    // -1

// 6. Testando remoção (Método removeAt com laço for)
console.log("\n--- Testando Remoção ---");
const removidoMeio = list.removeAt(1); // Remove "Elemento B"
console.log("10. Elemento removido da pos 1:", removidoMeio);
console.log("11. Lista após remover pos 1:", list.toString()); 
// Saída esperada: "Elemento A, Elemento C, Elemento D"

// 7. Testando remoção do início e do fim
list.removeAt(0); // Remove Elemento A
console.log("12. Após remover o primeiro (head):", list.toString()); // "Elemento C, Elemento D"
console.log("13. Novo Head:", list.getHead().element); // Elemento C

// 8. Estado final
console.log("\n--- Estado Final ---");
console.log("14. Tamanho final:", list.size());    // 2
console.log("15. Está vazia?", list.isEmpty());   // false
