# Capítulo 1

## Introdução a algoritmos

* **Pesquisa binária**

Vamos supor que vocẽ esteja procurando o nome de uma pessoa em uma agenda telefônica. O nome começa com K. Você pode começar na primeira página da agenda e ir folheando até chegar aos KS. Ṕorém você provavelmente vai começar pela metade, pois sabe que os Ks estarão mais perto dali.

Ou suponha que esteja procurando uma palavra que começa com O em um dicionário. Novamente, começará a busca pelo meio.

Isto é um problema de busca. E todos estes casos usam um algoritmo para resolvê-lo: pesquisa binária.

A pesquisa binária é um algoritmo. Sua entrada é umalista ordenada de elementos. S e o elemento que estamos buscando está na lista, a pesquisa binária retorna a sua localização. Caso contrário, a pesquisa binária retorna None.

* **Pesquisa Simples**
A cada tentativa, estaremos eliminando apenas um número.

Seja uma lista = [ 1, 2, 3, ... , 100 ]

* **Pesquisa Binária**
Seja qual for o número que estivermos pensando, poderá adivinhar, em no máximo de sete tentativas - porque a pesquisa binária elimina muito possibilidades .

Seja uma lista = [ 1, 2, 3, ... , 100 ]

Seja num dicionário com 240.000 palávras - pesquisando ocorrerá 18 Etapas.

* Pesquisa binária precisa-se de log n na base 2 para retornar o valor correto.
* Pesquisa simples linear precisa de n etapas. Pesqusa binária só funciona quando a lista estiver ordenada.
* Podemos armazenar uma sequência de elementos em uma linha de buckets conseccutivos que se chama array. Os buckets são numerados a partir do 0: o primeiro bucket está na posição #0; o segundo em #1; o terceiro em #2, e assim por diante.
* A função pesquisa_binaria pega um array ordenado e um item. Se o item está no array, a função retorna a sua posição.

```python

baixo = 0
alto = len(lista) - 1

// A cada tentativa, testamos o elemento central

meio = (baixo + alto) // 2
chute lista[meio]

// meio será arredondadopara baixo automaicamente pelo Python se (baixo + alto) não for um número par.
// Se o chute for muito baixo, atualizaremos a variável baixo proporcionalmente.

if chute < item:
 baixo = meio + 1

minha_lista = [1, 3, 5, 7, 9]

print pesquisa_binaria(minha_lista, 3)
print pesquisa_binaria(minha_lista, -1)

```

// E se o chute for muito alto, você atualizará a variável alto.

## Código completo:

# Função de pesquisa binária

```python
    def pesquisa_binaria(lista, item):
     
        baixo = 0
        alto = len(lista) - 1

        while baixo <= alto:  # enquanto não reduziu a lista para um elemento
            meio = (baixo + alto) // 2  # índice do meio
            chute = lista[meio]

            if chute == item:  # achou!
                return meio
            if chute > item:  # chute foi alto demais
                alto = meio - 1
            else:  # chute foi baixo demais
                baixo = meio + 1

        return None  # item não existe na lista

    # Testes

    minha_lista = [1, 3, 5, 7, 9]
    print(pesquisa_binaria(minha_lista, 3))  # deve retornar 1
    print(pesquisa_binaria(minha_lista, -1))  # deve retornar None

```

* **Tempo de execução**
* Notação Big O é uma notação especial que diz o qão rápido é um algoritmo.
* Tempo de execução crescem com velocidades  diferentes.
* Se a lista tem 1 bilhão de itens, o tempo de execução é a aproximadamente 33 milhões de vezes mais rápido.
* A notação Big O informa o quão rápido é um algoritmo, permitindo que se compare o número de operações.
* Tempo de execução O(n) e tempo de execução O(log n).
* Para verificar uma pesquisa com 100 elementos: vamos presumir que leva-se 1 milissegundo para verificar um elemento. Com a pesquisa simples, a busca leva 100 ms para rodar. Em contrapartida, precisa-se verificar apenas  sete elementos na pesquisa binária, logo a pesquisa binária leva 7 ms para ser executada.
* A pesquisa binária com 1 bilhão de elementos leva 30 ms ( log 1.000.000.000, na base 2 é igual 30).

      +-------------------------+------------------+------------------+
      |                         | PESQUISA SIMPLES | PESQUISA BINÁRIA |
      +-------------------------+------------------+------------------+
      | 100 ELEMENTOS           | 100ms            | 7ms              |
      | 10.000 ELEMENTOS        | 10 Ssegunos      | 14 ms            |
      | 1.000.000.000 ELEMENTOS | 11 dias          | 32ms             |
      +-------------------------+------------------+------------------+

* Sendo assim, conforme o número de itens cresce, a pesquisa binária aumenta só um pouco o seu tenpo de execução. Já a pesquisa simples leva muito tempo a mais. Logo conforme a lista de números cresce, a pesquisa binária se torna muito mais rápida do que a pesquisa simples.

* Por isso, não basta saber quanto tempo um algoritmo leva para ser executado - precisamos saber se o tempo de execução aumenta conforme a lista aumenta. É aí que a a notação Big O atua.

* A notação Big O estabelece o tempo de execução para a pior hipótese.

## Alguns exemplos comuns de tempo de execuçãonBig O
Aqui temos cinco tempos de execução Big O uue encontraremos bastante, ordenados do mais rápido para o mais lento.

 * O(log n), também conhecido como tempo logarítmico. Exemplo: pesquisa binária.

 * O(n), conhecido como tempo linear. Exemplo: pesquisa simples.

 * O(n * log n). Exemplo: um algoritmo rápido de ordenação, como o quicksort.

 * O(n^2). Exemplo: um algoritmo lento de ordenação, como a ordenação por seleção.

 * O(n!). Exemplo: um algoritmo bastante lento, como o do caixeiro viajante.

# Exemplo Clássico de O(n!): Caixeiro Viajante (TSP)

## Problema
Dado um conjunto de cidades e as distâncias entre elas, achar o caminho mais curto que visita cada cidade uma vez e volta ao início.

## Algoritmo Força Bruta (Permutação)

1. Gera todas as permutações possíveis das cidades
2. Para cada permutação, calcula a distância total
3. Retorna a permutação com menor distância

## Por que O(n!)?
* Para `n` cidades, tem `n!` permutações possíveis
* Para cada permutação, calcula a distância (`O(n)`)
* Total: `O(n! × n)` → simplifica para `O(n!)` porque `n!` domina

## Exemplo em Python

```python

import itertools

def distancia(cidades, rota):
    total = 0
    for i in range(len(rota)-1):
        total += cidades[rota[i]][rota[i+1]]
    total += cidades[rota[-1]][rota[0]]  # volta pro início
    return total

def caixeiro_viajante(cidades):
    melhor_rota = None
    menor_dist = float('inf')

    for rota in itertools.permutations(range(len(cidades))):
        dist = distancia(cidades, rota)
        if dist < menor_dist:
            menor_dist = dist
            melhor_rota = rota

    return melhor_rota, menor_dist


# Exemplo com 3 cidades
cidades = [
    [0, 10, 15],
    [10, 0, 20],
    [15, 20, 0]
]
rota, dist = caixeiro_viajante(cidades)
print(f"Melhor rota: {rota}, Distância: {dist}")

```

# Capítulo 2

## Ordenação por seleção

* **Como fucinoa a memóra**
O computador se parece com um grande conjuntos de gavetas, e cada gaveta tem seu endereço. Cada vez que quer armazenar um item na memória, você pede ao computador um pouco de espaço e ele dá um endereço no qual se pode armazernar o item. Existem duas maneira para se fazer isso: arrays e listas encadeadas.

* **Arrays** 
Usar uma array significa que todas as tarefas estão armazenadas contiguamente (uma ao ladoda outra) na memória.

Os Websites que apresentam listas "top 10" usam uma tática trapaceira para conseguir mais visualizações. Em vez de mostrarem a lista em um a única página, eles colocam um item em cada página e fazem a pessoa clicar em "próximo"  para ler o item seguinte. Por exemplo " Os 10 melhores vilões da TV". Seria muito melhor se a lista estivesse em uma única página e você pudesse clicar no nome de cada vilão para saber mais.

Listas encadeadas tem um problema, os elementos não estão próximos uns dos outros, então não podemos calcular instantaneamente a posição de um elemento na memória - precisa ir ao primeiro elemento para encontrar o endereçp  do segundo elemento, então ir ao segundo elemento para encontrar o endereço do terceiro elemento, até chegar ao elemento que deseje.

               ARRAY DE CINCO ELEMENTOS

               |    |    |    |    |    | ---> 04 é o quinto elemento
                 00   01   02   03   04

Então arrays são ótimos quando você deseja ler elememtos aleatórios, pois pode encontrar qualquer elemento instantaneamente em um array.

* **Temo de execução para operaçãocomuns de arrays e listas.**

                | Arrays | Listas
      Leitura   | O(1)   | O(n)
      Inserção  | O(n)   | O(1)
      Eliminação| O(n)   | O(Q)

## Inserido algo no meio da lista
Imagine que você queira que sua lista de tarefas se pareça mais com um calendário. Antes você adicionava os itens ao final da  lista. Agora , quer adiconar suas starefas  na ordem em que elas devam se realizar. O que seria melhor para inserir elementos no meio de uma lista: array ou lista encadeadas? Usando listas encadeadas , basta mudar o endereço para o qual o elemento antes está apontando.

Já para arrays, você deve mover todos os itens que estão abaixo do endereço de inserção. Se não houver espaço, pode ser necessário mover tudo, para um novo local! Por isso, listas encadeadas são melhores caso queira inserir um elemento no meio de uma lista.

* **Listas Encadeadas**
Com listas encadeadas, seus itens podem estar em qualquer lugar da memória. Cada item armazena o endereço do próximomitem da lista. Um monte de endereços aleatórios da memória estão ligados.

Com as listas encadeadas nunca precisa-se mover os itens como no array: coloca-se o item em qualquer lugar da memória e armazena o endereço do item anterior.

Ex.: Imagine que está tentando encontrar 10.000 slots para um array. A memória tem 10.000 slots, mas eles não estão juntos. Vocẽ não consegue arrumar um lugar para o seu array! Usar listas encadeadas seria possível se existir espaço na memória, você terá espaço para a sua lista encadeada.

## Deleções
E se quiser deletar um elemento? Novamente, é mais fácil fazer isso usando listas encadeadas, pois é necessaŕio mudar apenas o endereço para o qual o elemento anterior está apontando. Com aarays, tudo precisa ser movido quando um elemento é eliminado.

Ao contrário do que ocorre com as inserções, a eliminação de elementos sempre funcionará. A inserção poderá falhar quando não houver espaço suficiente na memória.

*É uma prática comum acompanhar o primeiro e o último item de uma lista encadeada para que o tempo de execução para deletá-lo seja  O(1).*

O que é mais usado arrays ou listas? Depende do caso em que se aplica. Entretanto os arrays são mais comuns porque permitem acesso aleatório. Existem dois tipos de acessos: o aleatório e o sequencial.  O sequencial significa ler os elementos, um por um, começando pelo primeiro. Listas encadeadas só podem lidar com acesso sequencial. Se você quiser ler o décimo elemento de uma lista encadeada, primeiro precisará ler os nove  elementos anteriores para chegar ao endereço do décimo elemento. O aleatório permite que você pule direto para o décimo elemento. Muitos casos requerem o acesso aleatório, o que faz os arrays serem mais utilizados. Os arrays e listas são usados para implementar outras estruturas de dados.

## Ordenação por seleção

Ordenação por Seleção (Selection Sort)

## Problema
Tenho uma lista de artistas e o número de plays de cada um. Quero ordenar do mais tocado pro menos tocado.

## Como funciona o Selection Sort
1. Acha o artista mais tocado → coloca no início
2. Acha o próximo mais tocado → coloca na segunda posição
3. Repete até terminar a lista

## Exemplo com artistas
Lista original:

    Artista    Plays
   
      A          120
      B          450
      C          210
      D          80

## Passos:
1. Acha o maior → B (450) → troca com A

B(450) A(120) C(210) D(80)

2. Acha o maior (restante) → C (210) → troca com A

B(450) C(210) A(120) D(80)

3. Acha o maior (restante) → A (120) → troca com D

B(450) C(210) A(120) D(80)

4. Pronto! Lista ordenada:

B(450) C(210) A(120) D(80)


## Código em Python

```python

def selection_sort(arr):
    for i in range(len(arr)):
        # acha o índice do máximo (restante)
        max_idx = i
        for j in range(i+1, len(arr)):
            if arr[j][1] > arr[max_idx][1]:
                max_idx = j
        # troca
        arr[i], arr[max_idx] = arr[max_idx], arr[i]
    return arr

# Exemplo
artistas = [
    ('A', 120),
    ('B', 450),
    ('C', 210),
    ('D', 80)
]

ordenados = selection_sort(artistas)
print(ordenados)
# Saída: [('B', 450), ('C', 210), ('A', 120), ('D', 80)]

```
## Complexidade
- Tempo: O(n^2)
- Espaço: O(1) (in-place)

Não é o mais eficiente, mas é simples de entender 

# Resumo

## Guia de Algoritmos e Estruturas de Dados

## Capítulo 1: Introdução a Algoritmos

* **Pesquisa Binária**

A pesquisa binária é um algoritmo de busca eficiente. Sua entrada deve ser obrigatoriamente uma **lista ordenada.**

  * Sucesso: Retorna a posição (índice) do elemento.

  * Falha: Retorna None.

**Comparação de Performance**

Para uma lista de n elementos:

  * **Pesquisa Simples (Linear):** Testa um por um. No pior caso, leva n etapas.
  
  * **esquisa Binária:** Divide a lista ao meio a cada passo. No pior caso, leva log_2 n etapas.

        +-------------------------+------------------+------------------+
        | Elementos               | Pesquisa Simples | Pesquisa Binária |
        +-------------------------+------------------+------------------+
        | 100                     | 100 ms           | 7 ms             |
        | 10.000                  | 10 segundos      | 14 ms            |
        | 1.000.000.000           | 11 dias          | 30 ms            |
        +-------------------------+------------------+------------------+

## Notação Big O

A notação Big O não mede o tempo em segundos, mas o **crescimento do número de operações** conforme o tamanho da entrada (n) aumenta. Ela foca no **pior cenário.**

**Tempos de Execução Comuns (do mais rápido ao mais lento):**

   1. O(log n): Tempo logarítmico (ex: Pesquisa Binária).
 
   2. O(n): Tempo linear (ex: Pesquisa Simples).
   
   3. O(nlog n): Algoritmos rápidos de ordenação (ex: Quicksort).
   
   4. O(n^2): Algoritmos lentos de ordenação (ex: Ordenação por Seleção).
   
   5. O(n!): Tempo fatorial, extremamente lento (ex: Caixeiro Viajante).Exemplo de Código: Pesquisa Binária em Python

```python

def pesquisa_binaria(lista, item):
    baixo = 0
    alto = len(lista) - 1

    while baixo <= alto:
        meio = (baixo + alto) // 2 # Arredonda para baixo automaticamente
        chute = lista[meio]

        if chute == item:
            return meio
        if chute > item:
            alto = meio - 1
        else:
            baixo = meio + 1
    return None

minha_lista = [1, 3, 5, 7, 9]
print(pesquisa_binaria(minha_lista, 3))  # Saída: 1
print(pesquisa_binaria(minha_lista, -1)) # Saída: None

```

## Capítulo 2: Ordenação por Seleção

## Como funciona a memória
A memória do computador funciona como um conjunto de gavetas endereçadas. Para armazenar múltiplos itens, usamos principalmente duas estruturas: **Arrays e Listas Encadeadas.**

**Arrays vs. Listas Encadeadas**

  * **Arrays:** Todos os itens ficam grudados (contíguos). Permite o **Acesso Aleatório** (pular direto para qualquer índice).

  * **Listas Encadeadas:** Os itens ficam espalhados. Cada item guarda o endereço do próximo. Só permite **Acesso Sequencial** (ler um por um).

        +------------------------+------------------+------------------------+
        | Operação               | Arrays           | Listas Encadeadas      |
        +------------------------+------------------+------------------------+
        | Leitura                | O(1)             | O(n)                   |
        | Inserção               | O(n)             | O(1)                   |
        | Deleção                | O(n)             | O(1)                   |
        +------------------------+------------------+------------------------+

    **Nota:** Inserir ou deletar em Arrays é lento porque exige deslocar todos os elementos seguintes na memória. Já nas listas, basta alterar o "ponteiro" do endereço.

## Algoritmo: Ordenação por Seleção (Selection Sort)
Este algoritmo ordena uma lista buscando repetidamente o maior (ou menor) elemento e movendo-o para a posição correta.

**Exemplo Prático (Ranking de Artistas por Plays)**

 1. Percorra a lista e encontre o artista com mais plays.

 2. Mova-o para uma nova lista (ou para o início da atual).

 3. Repita o processo para os itens restantes até que a lista esteja vazia/ordenada.

**Código em Python: Selection Sort**

```python

def busca_maior(arr):
    maior = arr[0][1]
    maior_indice = 0
    for i in range(1, len(arr)):
        if arr[i][1] > maior:
            maior = arr[i][1]
            maior_indice = i
    return maior_indice

def ordenacao_selecao(arr):
    novo_arr = []
    for i in range(len(arr)):
        # Busca o maior elemento restante
        maior = busca_maior(arr)
        # Remove da lista original e adiciona na nova
        novo_arr.append(arr.pop(maior))
    return novo_arr

artistas = [('A', 120), ('B', 450), ('C', 210), ('D', 80)]
print(ordenacao_selecao(artistas)) 
# Saída: [('B', 450), ('C', 210), ('A', 120), ('D', 80)]

```
**Complexidade:** O(n^2). Embora simples, torna-se muito lento para listas grandes se comparado ao Quicksort ou Merge Sort.

# Capítulo 3: Recursividade

A recursividade é uma técnica onde uma função chama a si mesma para resolver um problema. Ela é frequentemente usada para tornar o código mais limpo e elegante, especialmente em problemas que podem ser quebrados em partes idênticas e menores.

**As Duas Partes de uma Função Recursiva**

Para evitar que uma função rode para sempre (o que causa o erro de Stack Overflow), toda função recursiva precisa de duas partes:

  1. **Caso Base:** Quando a função para de chamar a si mesma. É a condição de saída.
  
  2. **Caso Recursivo:** Quando a função chama a si mesma para se aproximar do caso base.
  
  **Exemplo Clássico: Fatorial (n!)**
  
  O fatorial de 5 é 5 x 4 x 3 x 2 x 1. Em termos recursivos: 5 x fatorial(4).

```python

def fatorial(n):
    if n == 1:       # Caso Base
        return 1
    else:            # Caso Recursivo
        return n * fatorial(n - 1)

print(fatorial(5))  # 120

```

## A Pilha de Chamadas (Call Stack)

O computador usa uma estrutura de dados interna chamada Pilha para gerenciar as funções. Quando você chama uma função dentro de outra, a função atual fica "em espera" (pausada) no topo da pilha enquanto a nova função é executada.

**Funcionamento na Memória:**

 1. fatorial(3) é chamada. (Pilha: fatorial(3))
 
 2. fatorial(3) chama fatorial(2). (Pilha: fatorial(3) -> fatorial(2))
 
 3. fatorial(2) chama fatorial(1). (Pilha: fatorial(3) -> fatorial(2) -> fatorial(1))
 
 4. fatorial(1) atinge o **Caso Base** e retorna 1.
 
 5. A pilha começa a "desempilhar":
 
    * fatorial(2) recebe o 1 e retorna 2 x  1 = 2.
    
    * fatorial(3) recebe o 2 e retorna 3 x 2 = 6.

## Recursividade vs. Iteração (Loops)

Nem sempre a recursividade é a melhor escolha.

 * Recursividade: Mais elegante, facilita a leitura em estruturas como Árvores e Grafos. Porém, consome mais memória (cada chamada ocupa espaço na pilha).

 * Iteração (while/for): Geralmente mais eficiente em termos de memória, pois não cria novas camadas na pilha de chamadas.

* **Exemplo: Soma de Lista (Recursivo)**

```python

def soma_recursiva(lista):
    if not lista: # Caso Base: lista vazia
        return 0
    return lista[0] + soma_recursiva(lista[1:]) # Caso Recursivo

print(soma_recursiva([1, 2, 3, 4])) # Saída: 10

```

**Atenção:** Se você tiver uma recursão muito profunda (ex: chamar fatorial(10000)), o Python lançará um RecursionError. Isso ocorre porque a pilha de chamadas tem um limite físico de memória.

# Capítulo 4: Quicksort e a Estratégia Dividir para Conquistar

O Quicksort é um dos algoritmos de ordenação mais eficientes e elegantes da computação. Ele utiliza uma abordagem poderosa chamada **Dividir para Conquistar (D&C)** para transformar problemas complexos em subproblemas triviais.

## 1. A Estratégia Dividir para Conquistar (D&C)

A estratégia D&C não é apenas um algoritmo, mas uma técnica de resolução de problemas. Ela segue dois passos fundamentais:

1.  **Caso Base:** Identifique o cenário mais simples possível, onde a solução é imediata.
2.  **Caso Recursivo:** Divida ou diminua o problema até que ele se torne o caso base.

No contexto de ordenação, o **caso base** é uma lista vazia `[]` ou uma lista com apenas um elemento `[x]`, pois ambas já estão tecnicamente ordenadas.

---

## 2. Como o Quicksort Funciona

O Quicksort baseia-se no processo de **particionamento**. O algoritmo segue este fluxo:

1.  **Escolha do Pivô:** Selecione um elemento do array (pode ser o primeiro, o último ou o central).
2.  **Particionamento:** Reorganize o array para que:
    * Todos os elementos **menores** que o pivô fiquem à esquerda.
    * O **pivô** fique na sua posição final.
    * Todos os elementos **maiores** que o pivô fiquem à direita.
3.  **Recursão:** Aplique o Quicksort repetidamente nas sublistas de menores e maiores.


### Exemplo de Implementação em Python

```python
def quicksort(array):
    # Caso base: listas com 0 ou 1 elemento já estão ordenadas
    if len(array) < 2:
        return array
    else:
        # Caso recursivo
        pivo = array[0] 
        menores = [i for i in array[1:] if i <= pivo] 
        maiores = [i for i in array[1:] if i > pivo]
        
        return quicksort(menores) + [pivo] + quicksort(maiores)

# Teste
minha_lista = [10, 5, 2, 3]
print(quicksort(minha_lista)) # Saída: [2, 3, 5, 10]

```

**3. Análise de Performance: Caso Médio vs. Pior Caso**

A velocidade do Quicksort é influenciada diretamente pela altura da pilha de chamadas (call stack), que depende da escolha do pivô.

**O Pior Caso:** O(n^2) 

Ocorre quando o pivô é sempre o menor ou o maior elemento (comum em listas já ordenadas se o pivô for o primeiro item).

  * A lista não é dividida ao meio; apenas um elemento é removido por vez.
  
  * A pilha de chamadas tem altura $n$.
  
  * Total: n níveis x n elementos em cada nível = O(n^2).

**O Caso Médio:** O(log n)

Ocorre quando o pivô divide a lista aproximadamente ao meio.

  * A cada nível, o problema é reduzido pela metade.
  
  * A pilha de chamadas tem altura log n.
  
  * **Total:** log n níveis x n elementos em cada nível = O(nlog n).

## 4. Quicksort vs. Merge Sort

**O Merge Sort** também possui tempo médio e pior caso de O(nlog n). Então, por que o Quicksort é tão popular?

        +------------------------+------------------+------------------+
        | Característica         | Quicksort        | Merge Sort       |
        +------------------------+------------------+------------------+
        | Tempo Médio            | O(nlogn)         | O(nlogn)         |
        | Pior Caso              | O(n^2)           | O(nlogn)         |
        | Espaço Extra           | Baixo (In-place*)| Alto (O(n))      |
        | Vantagem Real          | Constante menor  | Estável e        |
        |                        | (mais rápido)    | garantido        |
        +------------------------+------------------+------------------+

### Por que o Quicksort costuma ganhar?

 1. **Constante Oculta:** O trabalho interno do Quicksort por comparação é mais simples.

 2. **Localidade de Referência:** Ele acessa endereços de memória próximos, aproveitando melhor o cache do processador.

 3. **In-place:** Diferente do Merge Sort, o Quicksort não precisa criar cópias inteiras da lista na memória.

## 5. Arquitetura e Execução de Hardware

        +----------------------------+-------------------------------+
        | Processamento              | Armazenamento                 |
        +----------------------------+-------------------------------+
        | ULA (Cálculos de           | Pilha de Chamadas (Stack)     |
        | Comparação)                |                               |
        |                            |                               |
        | BARRAMENTO INTERNO         |                               |
        |                            |                               |
        | UC (Controle do Fluxo      | RI (Instrução de Desvio/      |
        | Recursivo)                 | Salto)                        |
        |                            |                               |
        | REM (Endereços do Pivô)    | ---> [B. Endereços]           |
        |                            |                               |
        | Decodificador              | CI (Próxima Partição)         |
        |                            |                               |
        | RDM (Dados do Array)       | <-> [B. Dados]                |
        |                            |                               |
        | CLOCK (Sincronismo)        | MEMÓRIA PRINCIPAL (RAM)       |
        +----------------------------+-------------------------------+

