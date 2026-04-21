// 1. Criação e Métodos Básicos
let tarefas = ["Estudar Arrays", "Configurar Wi-Fi"];

// push: Adiciona ao final | unshift: Adiciona ao início
tarefas.push("Praticar Métodos"); 
tarefas.unshift("Acordar cedo");

// pop: Remove o último | shift: Remove o primeiro
let ultima = tarefas.pop(); 
let primeira = tarefas.shift();

// 2. Localização e Modificação
// splice(índice, quantosRemover, novosItens...)
tarefas.splice(1, 0, "Revisar Pilhas", "Revisar Filas"); 

// 3. Métodos de Alta Ordem (High-Order Functions)
const listaDeTarefas = [
    { id: 1, nome: "Estudar Arrays", status: "concluido", prioridade: 1 },
    { id: 2, nome: "Configurar Wi-Fi", status: "pendente", prioridade: 3 },
    { id: 3, nome: "Revisar Pilhas", status: "pendente", prioridade: 2 },
    { id: 4, nome: "Revisar Filas", status: "concluido", prioridade: 2 }
];

// map(): Cria um novo array transformado (ex: apenas nomes em maiúsculo)
const nomesMaiusculos = listaDeTarefas.map(t => t.nome.toUpperCase());

// filter(): Filtra elementos com base em uma condição
const pendentes = listaDeTarefas.filter(t => t.status === "pendente");

// find(): Retorna o primeiro elemento que satisfaz a condição
const tarefaUrgente = listaDeTarefas.find(t => t.prioridade === 1);

// reduce(): Reduz o array a um único valor (ex: somar prioridades)
const somaPrioridades = listaDeTarefas.reduce((total, t) => total + t.prioridade, 0);

// every() e some(): Checagem booleana
const todasConcluidas = listaDeTarefas.every(t => t.status === "concluido");
const existePendente = listaDeTarefas.some(t => t.status === "pendente");

// sort(): Ordenação (modifica o array original)
listaDeTarefas.sort((a, b) => a.prioridade - b.prioridade);

console.log("Pendentes:", pendentes);
console.log("Soma das Prioridades:", somaPrioridades);