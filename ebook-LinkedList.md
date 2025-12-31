## Listas Encadeadas é o Gerenciador de Histórico de Navegação (Botões Voltar e Avançar) ou um Reprodutor de Músicas (Playlist).

Vamos focar no Playlist de Músicas, pois ele utiliza perfeitamente a Lista Duplamente Encadeada, permitindo ir para a Próxima música ou voltar para a Anterior com eficiência máxima.

## Projeto Prático: Player de Música (Playlist)

Neste sistema, cada música é um Nó. Como a lista é dupla, cada música sabe quem vem antes e quem vem depois.

Arquivo: MusicPlayer.js

import DoublyLinkedList from './DoublyLinkedList.js'; // Importa sua classe de Lista Dupla

 // Simulador de Player de Música
 
class MusicPlayer {
  
  constructor() {
    
    this.playlist = new DoublyLinkedList();
    this.currentTrack = null; // Ponteiro para a música que está tocando agora
  }

  // Adiciona música à playlist
  
  addMusic(title, artist) {
  
    const musicInfo = `${title} - ${artist}`;
    this.playlist.insert(musicInfo, this.playlist.size());
  
    console.log(`Adicionada: ${musicInfo}`);
    
    // Se for a primeira música, define como a atual
  
    if (!this.currentTrack) {
      this.currentTrack = this.playlist.getHead();
    }
  }

  // Tocar próxima música
  
  next() {
  
    if (this.currentTrack && this.currentTrack.next) {
      this.currentTrack = this.currentTrack.next;
      this.play();
    } else {
      console.log("Fim da playlist.");
    }
  }

  // Tocar música anterior
  
  previous() {
  
    if (this.currentTrack && this.currentTrack.prev) {
      this.currentTrack = this.
      currentTrack.prev;
      this.play();
    } else {
      console.log("Início da playlist reached.");
    }
  }

  play() {
    
    if (this.currentTrack) {
      console.log(`▶️ Tocando agora: ${this.currentTrack.element}`);
    } else {
      console.log("Playlist vazia.");
    }
  }

  showPlaylist() {
    
    console.log(`🎵 Playlist: [ ${this.playlist.toString()} ]`);
  }
}

## // --- TESTANDO O PLAYER ---

const meuPlayer = new MusicPlayer();

meuPlayer.addMusic("Bohemian Rhapsody", "Queen");

meuPlayer.addMusic("Imagine", "John Lennon");

meuPlayer.addMusic("Starman", "David Bowie");

meuPlayer.showPlaylist();

meuPlayer.play();     // Tocando: Queen

meuPlayer.next();     // Tocando: John Lennon

meuPlayer.next();     // Tocando: David Bowie

meuPlayer.previous(); // Voltando para: John Lennon

**Por que este exemplo é ideal para o seu Ebook?**

 - Uso dos Dois Ponteiros: Demonstra a necessidade real do ponteiro prev (anterior). Em uma lista simples, o botão "Voltar" do player seria impossível sem percorrer toda a lista novamente.

 - Referência ao "Atual": O this.currentTrack é um ponteiro ativo. Ele não guarda apenas o nome da música, ele guarda o Nó inteiro. Isso significa que mudar de música é apenas mudar uma referência de memória, algo instantâneo (O(1)).

### Abstração: O usuário do MusicPlayer não precisa saber como os nós se conectam; ele apenas clica em "Próximo" ou "Anterior"

## Diagrama da Playlist (Memória em 2025)

       Musica 1             Musica 2             Musica 3
    ┌──────────┐         ┌──────────┐         ┌──────────┐
    │ prev:null│         │ prev:M1  │         │ prev:M2  │
    │ val:Queen│ ◀─────▶ │ val:John │ ◀─────▶ │ val:Bowie│
    │ next:M2  │         │ next:M3  │         │ next:null│
    └──────────┘         └──────────┘         └──────────┘
                              ▲
                              │
                        currentTrack ──▶ (Ponteiro aponta para o nó atual)

Como rodar no terminal:

Certifique-se de que o arquivo DoublyLinkedList.js está na mesma pasta e rode:

bash

node MusicPlayer.js

 - Esse conceito de "Nó Atual" é a base para o desenvolvimento de sistemas de paginação em sites modernos, onde o usuário navega entre "Página Anterior" e "Próxima Página" de forma fluida. Você pode ler mais sobre navegação encadeada no GeeksforGeeks - Doubly Linked List Applications.


### Análise do Resultado dos Testes


Análise dos Resultados dos Testes (DoublyLinkedList)

Teste | Saída Obtida | Diagnóstico de Lógica
|--- | --- | --- |
| Lista (toString) | Elemento A, Elemento B, Elemento C | Sucesso: Confirma que o encadeamento next e a ordem de inserção estão corretos. |
| Tamanho (size) | 3 | Sucesso: O controle do contador interno this.count está sincronizado com as operações. |
| Cabeça (head) | Elemento A | Sucesso: O ponteiro inicial está fixado corretamente no primeiro elemento inserido. |
| Cauda (tail) | Elemento C | Sucesso: A referência de fim de lista foi atualizada corretamente na última inserção. |
| Índice do 'B' | 1 | Sucesso: O método de busca por valor (indexOf) percorreu a lista e retornou a posição correta. |
| Removido | Elemento B | Sucesso: O método removeAt isolou o nó correto e retornou seu valor para o sistema. |
| Lista após remoção | Elemento A, Elemento C | Sucesso: A "ponte" entre o anterior e o próximo foi refeita, removendo o elo central. |
| Nova Cauda | Elemento C | Sucesso: A integridade do ponteiro tail foi mantida após a alteração no meio da lista. |
| Está vazia? | false | Sucesso: A validação de estado isEmpty() respondeu corretamente à presença de dados. |




