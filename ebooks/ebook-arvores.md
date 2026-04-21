## **1. O Conceito de Árvore Binária de Busca**

Em uma BST, cada nó pode ter no máximo dois filhos (esquerdo e direito). A regra de ouro é:

- Valores menores que o pai ficam à esquerda.

 - Valores maiores que o pai ficam à direita.

Diagrama Estrutural:

          [ 50 ]              <-- Raiz (Root)
         /      \
      [ 30 ]    [ 70 ]        <-- Filhos
     /    \    /    \
  [ 20 ] [40][60]  [ 80 ]     <-- Folhas (Leafs)


## **2. Implementação em JavaScript: BinarySearchTree.js**

javascript

/**
 * Classe que representa o Nó da Árvore
 */
class Node {
  constructor(key) {
    this.key = key;      // Valor do nó
    this.left = null;    // Ponteiro para o filho da esquerda (menores)
    this.right = null;   // Ponteiro para o filho da direita (maiores)
  }
}

/**
 * Classe principal da Árvore Binária de Busca
 */
class BinarySearchTree {
  constructor() {
    this.root = null; // A árvore começa vazia (sem raiz)
  }

  // Método para inserir um novo valor
  insert(key) {
    if (this.root === null) {
      this.root = new Node(key); // Se não houver raiz, o valor vira a raiz
    } else {
      this.insertNode(this.root, key); // Caso contrário, procura o lugar correto
    }
  }

  // Função auxiliar recursiva para inserção
  insertNode(node, key) {
    if (key < node.key) { // Se for menor, vai para a esquerda
      if (node.left === null) {
        node.left = new Node(key);
      } else {
        this.insertNode(node.left, key); // Continua descendo à esquerda
      }
    } else { // Se for maior ou igual, vai para a direita
      if (node.right === null) {
        node.right = new Node(key);
      } else {
        this.insertNode(node.right, key); // Continua descendo à direita
      }
    }
  }

  // Busca por um valor específico (retorna true ou false)
  search(key) {
    return this.searchNode(this.root, key);
  }

  searchNode(node, key) {
    if (node === null) return false; // Não encontrou
    if (key < node.key) return this.searchNode(node.left, key);
    if (key > node.key) return this.searchNode(node.right, key);
    return true; // Encontrou!
  }

  // Percurso Em-Ordem (In-Order Traversal): Visita do menor para o maior
  inOrderTraverse(callback) {
    this.inOrderTraverseNode(this.root, callback);
  }

  inOrderTraverseNode(node, callback) {
    if (node !== null) {
      this.inOrderTraverseNode(node.left, callback);  // Esquerda
      callback(node.key);                             // Raiz
      this.inOrderTraverseNode(node.right, callback); // Direita
    }
  }
}

export default BinarySearchTree;

3. Teste Manual: testaArvore.js

javascript

import BinarySearchTree from './BinarySearchTree.js';

const tree = new BinarySearchTree();

// Inserindo valores de forma desordenada
tree.insert(50);
tree.insert(30);
tree.insert(70);
tree.insert(20);
tree.insert(40);
tree.insert(60);
tree.insert(80);

console.log("--- Teste de Busca ---");
console.log("Existe o 40?", tree.search(40)); // true
console.log("Existe o 99?", tree.search(99)); // false

console.log("\n--- Percurso Em-Ordem (Crescente) ---");
let valores = [];
tree.inOrderTraverse(val => valores.push(val));
console.log(`[ ${valores.join(" ")} ]`); 
// Saída esperada: [ 20 30 40 50 60 70 80 ]

## **4. Detalhamento da Lógica**

1. Recursividade: Árvores são estruturas naturalmente recursivas. Para inserir ou buscar, o código "pergunta" ao nó atual: "Sou menor ou maior que você?". Dependendo da resposta, ele desce um nível e repete a pergunta até encontrar null ou o valor.

2. Eficiência de Busca: Em uma árvore equilibrada, a busca tem complexidade O(log n). Isso significa que, em uma árvore com 1 milhão de itens, você encontraria o valor em cerca de apenas 20 passos.

3. Percursos:

 -  Em-Ordem: Útil para obter os dados classificados.

 -  Pré-Ordem: Útil para copiar a árvore.

 - Pós-Ordem: Útil para deletar nós ou calcular o tamanho de pastas.

### Resumo Big O (Árvore Equilibrada)

Inserção: O(log n)

 - Busca: O(log n)

 - Remoção: O(log n)

 - Para rodar no seu terminal do VS Code em 2025:

bash

  node testaArvore.js

Para aprofundar, recomendo o simulador Visualgo - Binary Search Tree, que permite desenhar a árvore e ver a recursividade acontecendo em tempo real. Documentação de árvores no MDN.
A IA pode cometer erros. Por isso, cheque as respostas


## 1. Criar o Repositório no GitHub

 - Acesse o GitHub e faça login.

 - Clique no botão "+" (canto superior direito) e escolha "New repository".

 - Nomeie como estruturas-de-dados-js.

 - Deixe como Public e NÃO marque as opções de "Add a README" ou ".gitignore" agora (pois você já tem os arquivos no computador).

 - Clique em "Create repository".

 - O GitHub mostrará uma tela com vários comandos. Mantenha essa aba aberta.

## 2. Configurar o Git no seu Terminal

No terminal do VS Code (certifique-se de estar na pasta ~/estruturas_de_dados), execute:

bash

### 1. Inicializa o Git na pasta

git init

### 2. Adiciona todos os arquivos para serem salvos
git add .

### 3. Cria a primeira versão (commit)

git commit -m "Primeiro envio: Listas, 
Pilhas, Filas e Árvores"

### 4. Define o nome da branch principal como main

git branch -M main

## 3. Conectar e Enviar (Push)

Agora, copie a URL do repositório que você criou (ex: github.com) e execute:

bash

## 5. Conecta sua pasta local ao servidor do GitHub
git remote add origin github.com

## 6. Envia os arquivos

git push -u origin main

## Dica: O que NÃO enviar (.gitignore)

Como você tem a pasta node_modules, você não deve enviá-la ao GitHub (ela é muito pesada e pode ser baixada com npm install).

### Crie um arquivo chamado .gitignore na raiz.

Escreva apenas isso dentro dele:

node_modules/
.env

## 4. Usando o VS Code (Forma Visual)

Se preferir não usar o terminal para os próximos envios:

Clique no ícone de "Source Control" (o terceiro na barra lateral esquerda, parece uma bifurcação).

Escreva uma mensagem na caixa de texto.

Clique em "Commit" e depois em "Sync Changes" ou no botão de nuvem.

## Recursos Úteis:

Para entender melhor o fluxo, consulte o Guia oficial do GitHub.

Se você ainda não tem o Git instalado, baixe-o em git-scm.com.



 
