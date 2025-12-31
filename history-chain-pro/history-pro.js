import DoublyLinkedList from './doubly-linked-list.js';

class UndoManager {
  constructor() {
    this.history = new DoublyLinkedList();
    this.redoStack = new DoublyLinkedList();
  }

  addAction(action) {
    this.history.push(action);
    this.redoStack = new DoublyLinkedList(); // Limpa o redo ao fazer algo novo
    console.log(`+ Ação: ${action}`);
  }

  undo() {
    if (this.history.isEmpty()) return;
    // Remove do final (índice count - 1)
    const action = this.history.removeAt(this.history.size() - 1);
    this.redoStack.push(action);
    console.log(`- Desfazer: ${action}`);
  }

  redo() {
    if (this.redoStack.isEmpty()) return;
    const action = this.redoStack.removeAt(this.redoStack.size() - 1);
    this.history.push(action);
    console.log(`> Refazer: ${action}`);
  }

  print() {
    console.log(`\nEstado Atual: ${this.history.toString()}`);
    console.log(`Pode Refazer: ${this.redoStack.toString()}\n`);
  }

  undo() {
    if (this.history.isEmpty()) {
      console.log("! Nada para desfazer.");
      return;
    }
    const action = this.history.removeAt(this.history.size() - 1);
    this.redoStack.push(action);
    console.log(`- Desfazer: ${action}`);
  }

  redo() {
    if (this.redoStack.isEmpty()) {
      console.log("! Nada para refazer.");
      return;
    }
    const action = this.redoStack.removeAt(this.redoStack.size() - 1);
    this.history.push(action);
    console.log(`> Refazer: ${action}`);
  }

  clearHistory() {
  this.history.clear();
  this.redoStack.clear();
  console.log("!!! Histórico e Redo limpos com sucesso.");

  }

}


// --- EXECUÇÃO DO TESTE ---
const manager = new UndoManager();

manager.addAction("Escrever 'JavaScript'");
manager.addAction("Escrever 'é'");
manager.addAction("Escrever 'Incrível'");
manager.print();

manager.undo(); // Tira 'Incrível'
manager.undo(); // Tira 'é'
manager.print();

manager.redo(); // Devolve 'é'
manager.print();