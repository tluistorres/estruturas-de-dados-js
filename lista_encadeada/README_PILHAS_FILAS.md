# 🥞 Pilhas e Filas (Stacks & Queues)

Este diretório contém a implementação de estruturas de dados lineares com restrições de acesso, fundamentais para o controlo de fluxo e gestão de recursos.

---

## 1. Pilha (Stack) - LIFO
**LIFO** significa *Last In, First Out* (O último a entrar é o primeiro a sair).

### 📋 Analogia e Aplicação
- **Analogia:** Uma pilha de pratos. Só podes tirar o que está no topo.
- **Uso Real:** Função "Desfazer" (Undo) de editores, navegação de páginas (botão voltar) e chamadas de funções na memória (Stack Frame).

### 🖼️ Operações Básicas
- **Push:** Insere um elemento no topo.
- **Pop:** Remove o elemento do topo.

```text
Entrada: [A] -> [B] -> [C]
Pilha: 
| [C] | <-- Topo
| [B] |
| [A] |

2. Fila (Queue) - FIFO
FIFO significa First In, First Out (O primeiro a entrar é o primeiro a sair).

📋 Analogia e Aplicação
Analogia: Fila de um banco ou supermercado. Quem chega primeiro é atendido primeiro.

Uso Real: Escalonamento de processos no SO, filas de impressão e buffers de pacotes de rede.

🖼️ Operações Básicas
Enqueue (Inserir): Adiciona ao final da fila.

Dequeue (Remover): Remove do início da fila.

Entrada: [A] -> [B] -> [C]
Fila: [A] (Saída) <- [B] <- [C] (Entrada)

💻 Resumo de Implementação (pilha.c / fila.c)
A principal diferença entre elas e uma lista comum é onde a inserção e a remoção acontecem:

Estrutura   Inserção                  Remoção

Pilha       Sempre no Início (Topo)   Sempre no Início (Topo)
Fila        Sempre no Fim (Tail)      Sempre no Início (Head)

🛠️ Como Compilar e Testar
Atualize o seu Makefile para incluir os novos alvos e execute:

make pilha
make fila
./pilha
./fila

🛡️ Checklist de Segurança
Underflow: Verificar sempre se a pilha/fila está vazia antes de tentar um pop ou dequeue.

Ponteiros Duplos: Usar No** nas funções de modificação para garantir que o ponteiro da main seja atualizado corretamente.


