## Estruturas de Dados: Lista Encadeada (LinkedList)

### Exercício 1.

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

### // Demonstração de uso:

const list = new List();

list.append(1);

list.append(2);

list.append(3);

console.log("Valores iniciais:", list.
values()); // [1, 2, 3]

list.delete(1); // Remove o '2'

list.append(4);

console.log("Após deletar pos(1) e 
adicionar 4:", list.values()); // [1, 3, 4]

console.log("Valor na posição 2:", list.get(2)); // 4

export default List;



## Estruturas de Dados: Lista Encadeada (LinkedList)

Este guia detalha a implementação de uma lista encadeada simples em JavaScript, explicando a lógica por 
trás de cada componente e método.

### 1. A Estrutura do Nó (class Node)

O Nó é a unidade básica da lista. Imagine-o como um elo de uma corrente.

 - value: Armazena o dado (pode ser um número, string, objeto, etc).

 - next: É o "ponteiro" ou referência. Ele começa como null porque, no momento da criação, o nó ainda não 
 está conectado a outro.

## 2. A Classe Principal (class List)

 - constructor(): Inicializa a lista como vazia, definindo this.head = null.

 - head (Cabeça): É o único ponto de entrada da lista. Se você perder a referência da cabeça, perderá o acesso a todos os outros nós (eles serão removidos da memória pelo Garbage Collector).

## 3. Método append(value) — Adicionar ao Final

 - 3.1. Este método percorre a lista até encontrar o último elemento para pendurar o novo nó.

 - 3.2 Cria uma nova instância de Node.

   - Caso A (Lista Vazia): Se head for null, o novo nó torna-se a head.

   - Caso B (Lista com itens):

   - Criamos uma variável auxiliar current que começa no head.

   - Usamos um laço while para "caminhar" pelos nós: while (current.next !== null).

   - Ao chegar no nó cujo next é null, conectamos o novo nó: current.next = newNode.

## 4. Método get(position) — Buscar por Índice

Como listas encadeadas não possuem índices físicos como os Arrays, precisamos contar manualmente:

 - 4.1. Começamos pela head com um contador i = 0.

 - 4.2. O while percorre os nós enquanto a lista não terminar E i for menor que a posição desejada.

 - 4.3. A cada passo, avançamos: current = current.next e i++.

 - 4.4. Retorno: Se o nó existir, retornamos seu value; caso contrário, undefined.

## 5. Método delete(position) — Remover um Item

Este é o método mais complexo, pois exige a técnica de "re-encadeamento" para não quebrar a corrente.

 - Remover a Cabeça (position === 0): A nova cabeça passa a ser o segundo item: this.head = this.head.next.

 - Remover no Meio ou Fim:

   - Utilizamos duas variáveis: current (o que será apagado) e previous (o que vem antes dele).

   - Caminhamos até a posição desejada.

   - A Manobra: O nó anterior (previous) passa a apontar para o próximo do atual (current.next), 
   "pulando" o nó que queremos excluir.

   - O nó excluído fica isolado e é removido automaticamente da memória.

## 6. Método values() — Visualizar a Lista

 - 6.1 Facilita a depuração transformando a estrutura de nós em um formato legível:

 - 6.2 Cria um array vazio chamado values.

 - 6.3 Percorre a lista do início ao fim.

 - 6.4 Adiciona o value de cada nó ao array via .push().

 - 6.5 Retorna o array (ex: [1, 2, 3]).

## 7. Fluxo de Execução Exemplo

 - 7.1 Considere as operações abaixo:

 - 7.2 append(1), append(2), append(3): Resulta em 1 -> 2 -> 3 -> null.

 - 7.3 delete(1): Localiza o valor 2. O nó 1 passa a apontar diretamente para o 3. Lista: 1 -> 3 -> null.

 - 7.4 append(4): Caminha até o 3 e adiciona o 4. Lista: 1 -> 3 -> 4 -> null.

 - 7.5 get(2): Pula o índice 0 (1), pula o 1 (3) e alcança o 2, retornando o valor 4

## 1. Representação de um Nó (Node)

Cada objeto Node que você criou tem esta estrutura interna:

┌───────────────┐
│     NODE      │
├───────────────┤
│ value: (dado) │
│ next:  (ref)  │──▶   Próximo Nó ou NULL
└───────────────┘


## 2. A Lista na Memória (Após append(1), append(2), append(3))

O this.head é o seu ponto de partida. Ele aponta para o primeiro nó.

 this.head
     │
     ▼         Node 0                 Node 1                 Node 2
  ┌──────────────┐       ┌──────────────┐       ┌──────────────┐
  │  value: 1    │       │  value: 2    │       │  value: 3    │
  │  next: ──────┼──────▶│  next: ──────┼──────▶│  next: NULL  │
  └──────────────┘       └──────────────┘       └──────────────┘


## 3. Operação delete(1) (Removendo a posição 1)

Esta é a parte mais importante. Para deletar o valor 2, nós não o "apagamos" fisicamente, 
nós mudamos a direção da seta do nó anterior.

## Passo 1: Identificar o anterior e o atual

 - previous = Node 0 (valor 1)
 - current = Node 1 (valor 2)

## Passo 2: O "Pulo do Gato" (previous.next = current.next)

Fazemos o Node 0 apontar para onde o Node 1 estava apontando.

   this.head
       │
       ▼         Node 0                                      Node 2
    ┌──────────────┐       ┌──────────────┐       ┌──────────────┐
    │  value: 1    │       │  value: 2    │       │  value: 3    │
    │  next: ──────┼──┐    │  next: ──────┼─────▶ │  next: NULL  │
    └──────────────┘  │    └──────────────┘       └──────────────┘
                      │           ▲
                      └───────────┘
                 (Seta redirecionada)

|peração | O que acontece no diagrama | Performance (Big O)
| --- | --- | --- |
| append | Percorre todas as setas até chegar no NULL e coloca um novo nó. | O(n) |
| get | Segue as setas uma por uma até contar o número desejado. | O(n) |
| delete | Ajusta o "ponteiro" do nó anterior para o próximo do atual. | O(n) |


## EXERCÍCIO 2

**Esta versão inclui a lógica de percorrer a lista até uma posição específica, utilizando os métodos:**

**indexOf, isEmpty,size, toString e  getHead.**

Implementação: LinkedList.js

class Node {
    
    constructor(element) {
        this.element = element;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.count = 0;
        this.head = null;
    }

    // Insere em uma posição específica (usando laço for)
    
    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = new Node(element);
            if (index === 0) { // Início da lista
                node.next = this.head;
                this.head = node;
            } else {
                let previous = this.head;
                
                // Laço for para atingir a posição desejada
                for (let i = 0; i < index - 1; i++) {
                    previous = previous.next;
                }
                
                node.next = previous.next;
                previous.next = node;
            }
            this.count++;
            return true;
        }
        return false;
    }

    // Remove de uma posição específica
    removeAt(index) {
        if (index >= 0 && index < this.count) {
            let current = this.head;
            if (index === 0) {
                this.head = current.next;
            } else {
                let previous = this.head;
                for (let i = 0; i < index - 1; i++) {
                    previous = previous.next;
                }
                current = previous.next;
                previous.next = current.next;
            }
            this.count--;
            return current.element;
        }
        return undefined;
    }

    // Retorna o índice de um elemento
    indexOf(element) {
        let current = this.head;
        for (let i = 0; i < this.count && current != null; i++) {
            if (element === current.element) {
                return i;
            }
            current = current.next;
        }
        return -1;
    }

    size() {
        return this.count;
    }

    isEmpty() {
        return this.size() === 0;
    }

    getHead() {
        return this.head;
    }

    toString() {
        if (this.head == null) return '';
        let objString = `${this.head.element}`;
        let current = this.head.next;
        for (let i = 1; i < this.size() && current != null; i++) {
            objString = `${objString}, ${current.element}`;
            current = current.next;
        }
        return objString;
    }
}

export default LinkedList;


const lista = new LinkedList();

console.log("Está vazia?", lista.isEmpty()); // true

lista.insert("A", 0); // [A]

lista.insert("C", 1); // [A, C]

lista.insert("B", 1); // [A, B, C] - 

Inseriu na posição 1 usando o laço for

console.log("Lista atual:", lista.toString()); // "A, B, C"

console.log("Tamanho:", lista.size());         // 3

console.log("Posição do elemento 'B':", lista.indexOf("B")); // 1

lista.removeAt(2); // Remove o "C"
console.log("Após remover posição 2:", lista.toString()); // "A, B"


## Explicação dos Pontos Chave:

 1. O Laço for: Diferente do método append que apenas busca o final, aqui o for para 
exatamente no nó anterior à posição onde você deseja inserir ou remover. 

Isso permite "desconectar" e "reconectar" as setas (next) para incluir o novo elemento.

2. indexOf: Percorre a lista comparando cada elemento até encontrar o valor igual ao buscado, 
retornando o contador i.

3. getHead: Essencial para casos onde outras funções precisam começar a ler a lista do 
zero manualmente.

4.  toString: Converte a estrutura de nós encadeados em uma string separada por vírgulas, facilitando 
a visualização no console.

## 1. Inserção em Posição Específica: insert(element, 

**1) DIAGRAMAS**

Imagine que temos a lista [A, C] e queremos inserir "B" na posição 1.

Estado Inicial:

      pos: 0                pos: 1
    ┌──────────┐          ┌──────────┐
    │  Elem: A │          │  Elem: C │
    │  next: ──┼─────────▶│  next:null│
    └──────────┘          └──────────┘


O Laço for encontra o previous (índice 0):

## 1. Criamos o newNode (B).

## 2. Fazemos newNode.next = previous.next (B agora aponta para C).

## 3.Fazemos previous.next = newNode (A agora aponta para B).

Estado Final:

      pos: 0                pos: 1                pos: 2
    ┌──────────┐          ┌──────────┐          ┌──────────┐
    │  Elem: A │          │  Elem: B │          │  Elem: C │
    │  next: ──┼──┐       │  next: ──┼──▶       │  next:null│
    └──────────┘  │       └──────────┘          └──────────┘
                  │             ▲
                  └─────────────┘

## 2. Remoção em Posição Específica: removeAt(1)

Vamos remover o elemento "B" da posição 1.

**A Manobra do Laço:**

O laço for caminha até o nó anterior à remoção (nó A).

## 2.1 Identificamos o alvo: current = previous.next (B).

## 2. O Pulo: previous.next = current.next (A passa a apontar direto para C).

      pos: 0              (DELETADO)              pos: 1
    ┌──────────┐          ┌──────────┐          ┌──────────┐
    │  Elem: A │          │  Elem: B │          │  Elem: C │
    │  next: ──┼──┐       │  next: ──┼──▶       │  next:null│
    └──────────┘  │       └──────────┘          └──────────┘
                  │                                   ▲
                  └───────────────────────────────────┘
                         (A ponte pula o B)

**Mapa Mental dos Métodos Utilitários**

| Método | Representação Visual | Lógica Interna |
| --- | --- | --- |

| indexOf | A -> B -> C | Compara B == alvo? Não. Pula. C == alvo? Sim! Retorna o contador. |

| isEmpty | - | Verifica se o contador de tamanho está zerado. |
| getHead | - | Apenas entrega a "chave da casa" (o primeiro nó). |
| toString | A + ", " + B | Percorre a lista acumulando os textos em uma única variável de texto. |

## EXEMPLO 3

class DoublyNode {
    constructor(element) {
        this.element = element;
        this.next = null;
        this.prev = null; // A nova conexão para o nó anterior
    }
}

class DoublyLinkedList {
    constructor() {
        this.count = 0;
        this.head = null;
        this.tail = null; // Referência ao último elemento
    }

    // Inserção em qualquer posição com laço for
    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = new DoublyNode(element);
            let current = this.head;

            if (index === 0) { // Inserir no início
                if (this.head == null) {
                    this.head = node;
                    this.tail = node;
                } else {
                    node.next = this.head;
                    this.head.prev = node;
                    this.head = node;
                }
            } else if (index === this.count) { // Inserir no final (tail)
                current = this.tail;
                current.next = node;
                node.prev = current;
                this.tail = node;
            } else { // Inserir no meio usando laço for
                let previous;
                for (let i = 0; i < index; i++) {
                    previous = current;
                    current = current.next;
                }
                node.next = current;
                node.prev = previous;
                previous.next = node;
                current.prev = node;
            }
            this.count++;
            return true;
        }
        return false;
    }

    // Remoção de posição específica
    removeAt(index) {
        if (index >= 0 && index < this.count) {
            let current = this.head;

            if (index === 0) { // Remover o primeiro
                this.head = current.next;
                if (this.count === 1) {
                    this.tail = null;
                } else {
                    this.head.prev = null;
                }
            } else if (index === this.count - 1) { // Remover o último
                current = this.tail;
                this.tail = current.prev;
                this.tail.next = null;
            } else { // Remover do meio com laço for
                for (let i = 0; i < index; i++) {
                    current = current.next;
                }
                const previous = current.prev;
                previous.next = current.next;
                current.next.prev = previous;
            }
            this.count--;
            return current.element;
        }
        return undefined;
    }

    indexOf(element) {
        let current = this.head;
        for (let i = 0; i < this.count && current != null; i++) {
            if (element === current.element) return i;
            current = current.next;
        }
        return -1;
    }

    size() { return this.count; }
    isEmpty() { return this.size() === 0; }
    getHead() { return this.head; }
    getTail() { return this.tail; }

    toString() {
        if (this.head == null) return '';
        let objString = `${this.head.element}`;
        let current = this.head.next;
        while (current != null) {
            objString = `${objString}, ${current.element}`;
            current = current.next;
        }
        return objString;
    }
}

export default DoublyLinkedList;


## 2. Diagrama Visual: A Conexão Dupla - Exemplo 3


Diferente da lista simples, aqui as "setas" vão e voltam.

Representação de um Nó:

      ┌──────────────┐
◀─────┤ prev | val | next ├─────▶
      └──────────────┘

Inserção no Meio (Ex: entre A e C):
Para inserir B, quatro ponteiros devem ser atualizados:

1. B.next = C
2. B.prev = A
3. A.next = B
4. C.prev = B

      HEAD                                           TAIL
       │                                              │
       ▼       Node A           Node B          Node C ▼
    ┌──────┐        ┌──────┐        ┌──────┐
    │ prev:null     │ prev:A │        │ prev:B │
    │ val: A ◀─────▶│ val: B ◀─────▶│ val: C │
    │ next:B │      │ next:C │        │ next:null
    └──────┘        └──────┘        └──────┘


## 3. Diferenciais para o seu Ebook

Ao documentar este código no seu projeto, destaque estes pontos:

1. Vantagem: Você pode percorrer a lista do fim para o começo (tail para head) de forma muito eficiente.

2. Custo: Cada nó ocupa um pouco mais de memória (espaço extra para o ponteiro prev).

3. Complexidade de Código: O método insert e removeAt exige mais cuidado, pois se você esquecer de atualizar 
um dos quatro ponteiros, a lista "quebra".

## 1.Arquivo de Teste Manual: index.js

import DoublyLinkedList from './DoublyLinkedList.js';

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
const removido = list.removeAt(1); // 
Remove "B"

console.log("Removido:", removido);

console.log("Lista após remoção:", list.toString());

console.log("Nova Cauda:", list.getTail().element);

console.log("\n--- Verificando se está vazia ---");

console.log("Está vazia?", list.isEmpty());


## 2. Como rodar no terminal do VS Code

**No terminal (atalho Ctrl + '), execute:**

bash

 node index.js

O que observar no teste manual (Dicas de Estudo):

1. A Conexão Dupla: Como é uma lista duplamente ligada, experimente acessar o nó anterior manualmente para provar que a conexão existe. 

No seu index.js, adicione:

// Acessando o 'A' a partir do 'C' voltando pelo ponteiro 'prev'
console.log("Anterior do último:", list.
getTail().prev.element); 

2. Consistência da Cauda (tail): Sempre que você remover o último elemento (list.removeAt(list.size() - 1)), 
verifique se o getTail() foi atualizado para o elemento que agora ficou por último.

3. Lógica do for: Note que no método insert da lista dupla, o laço percorre os elementos para encontrar 
onde "abrir espaço" para as novas setas prev e next.

## 1. Lista Ligada Circular (CircularLinkedList.js)

Nesta lista, tail.next aponta para head. Isso permite percorrer a lista infinitamente em ciclos.

javascript

import LinkedList from './LinkedList.js'; 

// Reaproveita a lógica base

class CircularLinkedList extends 
LinkedList {

    insert(element, index) {
        if (index >= 0 && index <= this.count) {
            const node = { element, next: null };
            let current = this.head;
            if (index === 0) {
                if (this.head == null) {
                    this.head = node;
                    node.next = this.head; // Aponta para si mesmo
                } else {
                    node.next = current;
                    current = this.getElementAt(this.size() - 1); // Pega o último
                    this.head = node;
                    current.next = this.head; // Fecha o círculo
                }
            } else {
                const previous = this.getElementAt(index - 1);
                node.next = previous.next;
                previous.next = node;
            }
            this.count++;
            return true;
        }
        return false;
    }
}


## Diagrama Circular

      ┌─────────────────────────────────────────┐
      │                                         │ (Loop)
      ▼         Node 0           Node 1         │
   ┌──────┐       ┌──────┐       ┌──────┐       │
   │ val:A│       │ val:B│       │ val:C│       │
   │ next:┼──────▶│ next:┼──────▶│ next:┼───────┘
   └──────┘       └──────┘       └──────┘
     HEAD                          TAIL

## 2. Lista Ordenada (SortedLinkedList.js)

Diferente das outras, ela não aceita um índice na inserção. Ela compara o valor e insere na posição correta para manter a ordem.

javascript

import LinkedList from './LinkedList.js';

const Compare = { LESS_THAN: -1, BIGGER_THAN: 1 };

class SortedLinkedList extends LinkedList {
 
    constructor() {
        super();
    }

    // Método de comparação (pode ser customizado para objetos)
    compare(a, b) {
        if (a === b) return 0;
        return a < b ? Compare.LESS_THAN : Compare.BIGGER_THAN;
    }

    insert(element) {
        if (this.isEmpty()) {
            return super.insert(element, 0);
        }
        const pos = this.getIndexNextSortedElement(element);
        return super.insert(element, pos);
    }

    getIndexNextSortedElement(element) {
        let current = this.head;
        let i = 0;
        for (; i < this.size() && current; i++) {
            const comp = this.compare(element, current.element);
            if (comp === Compare.LESS_THAN) return i;
            current = current.next;
        }
        return i;
    }
}



## Diagrama Ordenado

Se inserirmos o número 15 na lista [10, 20]:

O código compara 15 < 10? (Não).

Compara 15 < 20? (Sim!).

Insere na posição 1.

    [ 10 ]  ────────▶  [ 15 ]  ────────▶  [ 20 ]
   (Pos 0)            (Novo Nó)          (Pos 2)


##**Resumo para seu Ebook**

| Tipo de Lista | Diferencial Principal | Melhor Uso em 2025 |
| --- | --- | --- |
| Circular | O último nó volta para o primeiro. | Sistemas de turnos (round-robin), playlists de música. |
| Ordenada | Mantém a ordem no momento da inserção. | Listas de recordes (high scores), agendas. |


## Exercício 4

## 1. Estrutura do Nó (class Node)

O nó armazena o dado (data) e a referência para o próximo elemento (next).

┌───────────────┐
│     NODE      │
├───────────────┤
│ data:  value  │
│ next:  ptr  ──┼──▶ Próximo ou null
└───────────────┘


## 2. Métodos de Inserção

insertFirst(data)

Insere o elemento no início. O novo nó aponta para onde a head apontava, e a head passa a ser o novo nó.

Diagrama:

Novo Nó [500] ──▶ Head Atual [100]
Head ──▶ [500]

insertLast(data)

Caminha até o fim da lista (while (current.next)) e pendura o novo nó no último next.

Diagrama:

[100] ──▶ [200] ──▶ [300] ──▶ null
                      │
               (Novo) [400] ──▶ null

insertAt(data, index)

Usa um contador para parar exatamente no índice desejado.

previous guarda o nó anterior ao índice.
current guarda o nó que estava naquela posição.

A manobra: previous.next = node e node.next = current.

**Diagrama (Inserindo 500 no índice 2):**

Índice:    0          1               2
Lista:   [A] ──▶ [B] (prev)      [C] (curr)
                  │               ▲
                  └──▶ [500] ─────┘

## 3. Métodos de Busca e Remoção

getAt(index)

Percorre a lista com um contador. Quando count == index, ele exibe o dado. Note que este método percorre a lista 
inteira mesmo após encontrar o item (pode ser otimizado com um return).

**removeAt(index)**

Para remover, o código "pula" o nó do índice escolhido.

 - Localiza o previous (nó anterior ao que será removido).

 - Localiza o current (nó a ser removido).

 - A manobra: previous.next = current.next.

**Diagrama:**

Antes:  [A] ──▶ [B] (remover) ──▶ [C]
Depois: [A] ────────────────────▶ [C]

clearList()

Zera a lista. Em JavaScript, basta apontar a head para null. Como não há mais referências para os nós, o sistema limpa 
a memória automaticamente.

## 4. Fluxo do Exemplo Fornecido

Executando os comandos do seu código:

insertFirst(100): [100]

insertFirst(200): [200, 100]

insertFirst(300): [300, 200, 100]

insertLast(400): [300, 200, 100, 400]

insertAt(500, 3): Insere no índice 3 (antes do 400).

Resultado final no console (printListData):

300
200
100
500
400

## Resumo para Documentação

Método | Complexidade (Big O) | Descrição
--- | --- | ---
insertFirst | O(1) | Mais rápido, pois não percorre a lista.
insertLast | O(n) | Precisa caminhar até o último nó.
insertAt | O(n) | Percorre até o índice específico.
removeAt | O(n) | Localiza e re-encadeia os ponteiros.

1. Execução Passo a Passo

ll.insertFirst(50): A lista deixa de ser nula e cria o primeiro nó.

Estado: [50] -> null

ll.insertFirst(75): O 75 entra no início e aponta para o 50.

Estado: [75] -> [50] -> null

ll.insertLast(100): O código percorre a lista, acha o 50 e pendura o 100 depois dele.

Estado: [75] -> [50] -> [100] -> null

ll.getAt(0): O método percorre a lista e, ao encontrar o índice 0, executa o console.

log(current.data).
Saída no Console: 75

ll.printListData(): Percorre e imprime todos.

## 2. Diagrama da Nova Lista

Após esses comandos, sua estrutura de dados em 2025 estará assim:

      HEAD
       │
       ▼           Índice 0          Índice 1          Índice 2
    ┌──────────┐      ┌──────────┐      ┌──────────┐
    │ data: 75 │      │ data: 50 │      │ data: 100│
    │ next: ───┼─────▶│ next: ───┼─────▶│ next:null│
    └──────────┘      └──────────┘      └──────────┘

## 3. Resultado Final no Console

Se você rodar exatamente essa sequência no seu VS Code agora, o terminal mostrará:

75    <-- (Resultado do getAt(0))

75    <-- (Início do printListData)

50

100

## Dicas Importantes:

Reuso de Memória: O JavaScript é muito eficiente nisso. Os nós antigos que foram limpos pelo 

clearList já foram marcados para exclusão, e esses novos ocupam espaços novos de memória de forma limpa.

Consistência do size: O seu método insertFirst e insertLast fazem this.size++, então o contador que estava 
em 0 (após o clear) terminará em 3.

Para conferir o estado completo do objeto no VS Code, você pode usar o comando console.dir(ll, { depth: null });
, que mostrará toda a árvore de nós expandida no terminal. Documentação do console.dir.




