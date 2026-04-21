class Stack {
  constructor() {
    this.count = 0;
    this.items = {};
  }

  // Adiciona uma nova ação ao topo da pilha
  push(element) {
    this.items[this.count] = element;
    this.count++;
  }

  // Remove e retorna a última ação (a que será desfeita)
  pop() {
    if (this.isEmpty()) return undefined;
    this.count--;
    const result = this.items[this.count];
    delete this.items[this.count];
    return result;
  }

  isEmpty() {
    return this.count === 0;
  }

  toString() {
    if (this.isEmpty()) return 'Vazio';
    let values = [];
    for (let i = 0; i < this.count; i++) {
      values.push(`"${this.items[i]}"`);
    }
    return values.join(" -> ");
  }
}

// --- LOGICA DO EDITOR DE TEXTO ---

const historicoAcoes = new Stack(); // Nossa pilha de "Undo"
let textoAtual = ""; // Representa o texto que o usuário vê

function digitar(novoTexto) {
    console.log(`\nDigitando: "${novoTexto}"`);
    historicoAcoes.push(textoAtual); // Salva o estado ANTERIOR na pilha
    textoAtual += novoTexto;         // Atualiza o texto com a nova digitação
    console.log("Texto na tela:", textoAtual);
}

function desfazer() {
    if (historicoAcoes.isEmpty()) {
        console.log("\nNada para desfazer!");
        return;
    }
    console.log("\n[Botão Desfazer Clicado]");
    textoAtual = historicoAcoes.pop(); // Recupera o último estado salvo
    console.log("Texto na tela após desfazer:", textoAtual);
}

// --- TESTANDO O FLUXO ---

digitar("Olá ");
digitar("Mundo");
digitar(" em 2025!");

console.log("\nHistórico de estados salvos:", historicoAcoes.toString());

desfazer(); // Remove " em 2025!"
desfazer(); // Remove "Mundo"

console.log("\nTexto Final:", textoAtual); // Deve sobrar apenas "Olá "
