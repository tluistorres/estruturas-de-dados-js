// O Array de Objetos (representando produtos)
const carrinho = [
    { nome: "Mouse Gamer", preco: 150, qtd: 1 },
    { nome: "Teclado Mecânico", preco: 300, qtd: 1 },
    { nome: "Monitor 144hz", preco: 1200, qtd: 2 }
];

// 1. MAP: Criar uma lista apenas com os nomes dos produtos
const nomesProdutos = carrinho.map(item => item.nome);
console.log("Itens no carrinho:", nomesProdutos);

// 2. FILTER: Filtrar apenas produtos que custam mais de 200 reais
const produtosCaros = carrinho.filter(item => item.preco > 200);

// 3. REDUCE: Calcular o valor TOTAL do carrinho
// (acumulador, item) => lógica, valor inicial
const totalGeral = carrinho.reduce((total, item) => {
    return total + (item.preco * item.qtd);
}, 0);

console.log(`Total a pagar: R$ ${totalGeral}`);

// 4. FIND: Localizar um produto específico para dar um detalhe
const teclado = carrinho.find(item => item.nome === "Teclado Mecânico");
console.log("Detalhes do teclado:", teclado);