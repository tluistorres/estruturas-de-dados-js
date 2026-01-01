**Tabela Hash** (ou Hash Table) é como uma biblioteca perfeitamente organizada onde você não precisa procurar corredor por corredor: você pergunta pelo título e o bibliotecário te diz instantaneamente em qual estante e prateleira o livro está.

No JavaScript, os objetos {} e os Map são implementações de **tabelas hash.**

## O conceito fundamental

Uma Tabela Hash armazena pares de **chave** e **valor**. O segredo está na **Função Hash.**

 - Você dá uma **chave** (ex: "username").

 - A **Função Hash** transforma essa palavra em um **número** (índice).

 - O **valor** é guardado exatamente nesse índice de um array.

Por que ela é tão rápida?

### Por que ela é tão rápida?

Diferente da sua LinkedList, onde para achar o último elemento você precisava percorrer os outros (mesmo com o tail, para achar um elemento no meio você teria que caminhar), na Tabela Hash você **calcula** a posição. O acesso é $O(1)$ — tempo constante.

### O Problema: Colisões

Às vezes, a função hash pode gerar o mesmo índice para duas chaves diferentes (ex: "Ana" e "Bia" podem resultar no índice 5). Isso se chama **Colisão**. Existem duas formas principais de resolver isso:

 - **Encadeamento Separado:** Cada posição do array guarda uma... **Lista Encadeada.**

 - **Endereçamento Aberto:** Procura-se a próxima vaga livre no array.

## Vamos começar a implementação?

Para o seu novo projeto (podemos chamar de **HashVault**), crie um arquivo chamado hash-table.js. Primeiro, vamos criar uma função hash simples (chamada "lose-lose", pois é fácil de entender, embora gere colisões).

JavaScript

/ hash-table.js

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

  hashCode(key) {
    return this.loseloseHashCode(key);
  }

  // Insere ou atualiza
  put(key, value) {
    if (key != null && value != null) {
      const position = this.hashCode(key);
      this.table[position] = { key, value };
      return true;
    }
    return false;
  }

  get(key) {
    const position = this.hashCode(key);
    return this.table[position] == null ? undefined : this.table[position].value;
  }

  remove(key) {
    const position = this.hashCode(key);
    if (this.table[position] != null) {
      delete this.table[position];
      return true;
    }
    return false;
  }
}


**O que você acha de testarmos essa versão básica?**

Tente criar um arquivo de teste e inserir nomes como "John", "Tyrion" e "Aaron". Você verá que é extremamente rápido recuperar os valores.

Dica de desafio: Tente descobrir o que acontece se você inserir "Sue" e "Aet" na mesma tabela usando essa função hash simplificada. (Spoiler: elas vão colidir!).

Vamos criar um arquivo de teste para observar o fenômeno da Colisão que mencionei.

## 1. Criando o teste de colisão

Crie um arquivo chamado test-hash.js (ou adicione ao final do seu arquivo atual) com o seguinte conteúdo:

JavaScript
import HashTable from './hash-table.js';

const hash = new HashTable();

// Inserindo dados normais
hash.put("John", "john@email.com");   // Hash: 29
hash.put("Tyrion", "tyrion@email.com"); // Hash: 16

// Agora, o teste de colisão:
// "Sue" e "Aet" costumam gerar o mesmo hash na função lose-lose
hash.put("Sue", "sue@email.com");
hash.put("Aet", "aet@email.com");

console.log(`Hash Sue: ${hash.hashCode("Sue")}`);
console.log(`Hash Aet: ${hash.hashCode("Aet")}`);

console.log(`Get Sue: ${hash.get("Sue")}`);
console.log(`Get Aet: ${hash.get("Aet")}`);


2. O que vai acontecer? (O Problema)

Se você rodar esse código, verá que ao buscar por "Sue", o resultado será "aet@email.com".

Por que? Como ambas as chaves geram o mesmo índice (colisão), e a sua implementação atual apenas sobrescreve o valor naquela posição (this.table[position] = ...), o último a chegar ganha. No mundo real, isso seria um desastre: você tentaria acessar seus e-mails e veria os de outra pessoa!

3. A Solução: Encadeamento Separado (Separate Chaining)

Lembra que eu disse que a sua LinkedList seria útil aqui? Para resolver a colisão, em vez de guardar o par {key, value} direto no array, guardamos uma Lista Encadeada em cada posição.

Como ficaria a lógica:
O Hash aponta para o índice 5.

No índice 5, existe uma LinkedList.

Você adiciona "Sue" na lista.

Quando "Aet" chegar no índice 5, ele entra como o segundo nó da mesma lista.

Quer tentar evoluir sua HashTable?
Para isso, precisaríamos importar sua LinkedList original para dentro da HashTable. Você gostaria que eu mostrasse como modificar o método put e get para usar a lista e nunca mais perder dados por colisão?