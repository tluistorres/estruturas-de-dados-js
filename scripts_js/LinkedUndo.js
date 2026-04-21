import LinkedList from './linked-list.js';
// O erro acontece se você esquecer o ".js" no final

class UndoManager {
  constructor() {
    this.history = new LinkedList(); // Armazena o histórico principal
    this.redoStack = new LinkedList(); // Armazena o que foi desfeito
  }

  // Registra uma nova ação
  addAction(action) {
    this.history.push(action);
    // Sempre que uma ação nova ocorre, o futuro (redo) é descartado
    this.redoStack.clear(); 
    console.log(`Ação: "${action}"`);
  }

  // Desfaz: tira do History e move para o Redo
  undo() {
    if (this.history.isEmpty()) return;

    const action = this.history.removeAt(this.history.size() - 1);
    this.redoStack.push(action); // Guarda para o caso de querer refazer
    console.log(`Desfeito: "${action}"`);
  }

  // Refaz: tira do Redo e volta para o History
  redo() {
    if (this.redoStack.isEmpty()) {
      console.log("Nada para refazer.");
      return;
    }

    const action = this.redoStack.removeAt(this.redoStack.size() - 1);
    this.history.push(action); // Devolve para o histórico principal
    console.log(`Refeito: "${action}"`);
  }

  showStatus() {
    console.log("--- Estado do HistoryChain ---");
    console.log("Histórico:", this.history.toString());
    console.log("Pode Refazer:", this.redoStack.toString());
    console.log("------------------------------");
  }
}

const myEditor = new UndoManager();

myEditor.addAction("Escreveu 'A'");
myEditor.addAction("Escreveu 'B'");
myEditor.undo();         // Remove 'B' e manda para o Redo
myEditor.showStatus();   // History: [ A ], Redo: [ B ]

myEditor.redo();         // Tira 'B' do Redo e volta para o History
myEditor.showStatus();   // History: [ A, B ], Redo: [ ]