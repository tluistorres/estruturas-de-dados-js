// hash-table.js
import LinkedList from './LinkedList.js';

class ValuePair {
  constructor(key, value) {
    this.key = key;
    this.value = value;
  }
}

export default class HashTable {
  constructor() {
    this.table = {}; // Usaremos um objeto como repositório
  }

  // A função mágica: Transforma string em número
  loseloseHashCode(key) {
    if (typeof key === 'number') return key;
    
    let hash = 0;
    for (let i = 0; i < key.length; i++) {
      hash += key.charCodeAt(i); // Soma o valor ASCII de cada letra
    }
    return hash % 37; // Usamos o resto da divisão para limitar o tamanho
  }

  // A nova função robusta
djb2HashCode(key) {
  const tableKey = typeof key === 'symbol' ? key.toString() : key;
  let hash = 5381; 
  for (let i = 0; i < tableKey.length; i++) {
    hash = (hash * 33) + tableKey.charCodeAt(i);
  }
  return hash % 1013; 
}

// O "atalho" que o put, get e remove usam
hashCode(key) {
  return this.djb2HashCode(key); // Certifique-se que o nome aqui coincide!
}

  // Insere ou atualiza
  put(key, value) {
  if (key != null && value != null) {
    const position = this.hashCode(key);

    if (this.table[position] == null) {
      this.table[position] = new LinkedList();
    }

    // AJUSTE AQUI: Use o nome exato do método da sua LinkedList (ex: append)
    this.table[position].append(new ValuePair(key, value)); 
    return true;
  }
  return false;
}

  get(key) {
  const position = this.hashCode(key);
  const linkedList = this.table[position];

  if (linkedList != null && !linkedList.isEmpty()) {
    let current = linkedList.head; // Começamos no início da lista

    while (current != null) {
      if (current.element.key === key) {
        return current.element.value; // Encontrou!
      }
      current = current.next; // Próximo nó
    }
  }
  return undefined; // Não encontrou a chave na lista
}


  remove(key) {
  const position = this.hashCode(key);
  const linkedList = this.table[position];

  if (linkedList != null && !linkedList.isEmpty()) {
    let current = linkedList.head;
    let index = 0;

    while (current != null) {
      if (current.element.key === key) {
        linkedList.removeAt(index); // Remove especificamente esse nó da lista
        
        if (linkedList.isEmpty()) {
          delete this.table[position]; // Se a lista esvaziou, deleta o balde
        }
        return true;
      }
      current = current.next;
      index++;
    }
  }
  return false;
}

  toString() {
  if (Object.keys(this.table).length === 0) return '';
  
  let objString = '';
  for (const position in this.table) {
    const linkedList = this.table[position];
    objString += `{${position} => ${linkedList.toString()}}\n`;
  }
  return objString;
}
}





//const hash = new HashTable();

// // Inserindo dados normais
// hash.put("John", "john@email.com");   // Hash: 29
// hash.put("Tyrion", "tyrion@email.com"); // Hash: 16

// console.log(`Hash John: ${hash.hashCode("John")}`);
// console.log(`Hash Tyrion: ${hash.hashCode("Tyrion")}`);

// // Agora, o teste de colisão:
// // "Sue" e "Aet" costumam gerar o mesmo hash na função lose-lose
// hash.put("Sue", "sue@email.com");
// hash.put("Aet", "aet@email.com");

// console.log(`Hash Sue: ${hash.hashCode("Sue")}`);
// console.log(`Hash Aet: ${hash.hashCode("Aet")}`);

// console.log(`Get Sue: ${hash.get("Sue")}`);
// console.log(`Get Aet: ${hash.get("Aet")}`);


// hash.put("Jonathan", "jonathan@email.com");
// hash.put("Jamie", "jamie@email.com");

// console.log(`Hash Jonathan: ${hash.hashCode("Jonathan")}`);
// console.log(`Hash Jamie: ${hash.hashCode("Jamie")}`);

// console.log(`Get Jonathan: ${hash.get("Jonathan")}`); // Pode retornar Jamie!

// Adicione ao final do hash-table.js
 const hash = new HashTable();

hash.put("Jonathan", "jonathan@email.com"); // Vai para o índice 5
hash.put("Jamie", "jamie@email.com");       // TAMBÉM vai para o índice 5

console.log("=== TESTE DE COLISÃO (SEPARATE CHAINING) ===");
console.log(`E-mail do Jonathan: ${hash.get("Jonathan")}`);
console.log(`E-mail do Jamie: ${hash.get("Jamie")}`);

console.log("\nRemovendo Jonathan...");
hash.remove("Jonathan");

console.log(`Jonathan existe? ${hash.get("Jonathan")}`);
console.log(`Jamie ainda existe? ${hash.get("Jamie")}`);


