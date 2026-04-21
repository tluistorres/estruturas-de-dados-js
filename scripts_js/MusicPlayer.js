import DoublyLinkedList from './DoublyLinkedList.js'; // Importa sua classe de Lista Dupla

/**
 * Simulador de Player de Música
 */
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
      this.currentTrack = this.currentTrack.prev;
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

// --- TESTANDO O PLAYER ---

const meuPlayer = new MusicPlayer();

meuPlayer.addMusic("Bohemian Rhapsody", "Queen");
meuPlayer.addMusic("Imagine", "John Lennon");
meuPlayer.addMusic("Starman", "David Bowie");

meuPlayer.showPlaylist();

meuPlayer.play();     // Tocando: Queen
meuPlayer.next();     // Tocando: John Lennon
meuPlayer.next();     // Tocando: David Bowie
meuPlayer.previous(); // Voltando para: John Lennon

