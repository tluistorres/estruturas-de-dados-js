///Código de Hamming(21,16) comentado linha por linha:
public class Hamming {
    // Método para codificar dados de 16 bits com Hamming(21,16)
    public static int[] encode(int[] data) {
        // Array para armazenar o código de Hamming (21 bits)
        int[] hamming = new int[21];
        // Posições dos bits de dados na palavra de 21 bits
        int[] pos = {3,5,6,7,9,10,11,12,13,14,15,17,18,19,20,21};
        int j = 0;

        // Coloca os 16 bits de dados nas posições correspondentes
        for (int i : pos) {
            hamming[i-1] = data[j++]; // Ajusta índice (0-based)
        }

        // Calcula os 5 bits de paridade
        hamming[0]  = pBit(hamming, 1);  // P1
        hamming[1]  = pBit(hamming, 2);  // P2
        hamming[3]  = pBit(hamming, 4);  // P4
        hamming[7]  = pBit(hamming, 8);  // P8
        hamming[15] = pBit(hamming, 16); // P16

        return hamming; // Retorna palavra codificada
    }

    // Método auxiliar para calcular um bit de paridade
    private static int pBit(int[] h, int pos) {
        int count = 0; // Contador para XOR
        // Percorre os bits cobertos pela paridade 'pos'
        for (int i = pos-1; i < 21; i += (pos*2)) {
            // Faz XOR nos bits cobertos
            for (int j = i; j < i+pos && j < 21; j++) {
                count ^= h[j]; // XOR para paridade
            }
        }
        return count; // Retorna o bit de paridade
    }

    // Método principal para teste
    public static void main(String[] args) {
        // Exemplo de dados de 16 bits
      //int[] data = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
        int[] data = {1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,1}; // Novos dados

        // Codifica em Hamming
        int[] hamming = encode(data);
        System.out.println("Hamming: ");
        // Imprime o código gerado
        for (int b : hamming) System.out.print(b);
    }
}


// Código de Hamming para palavra de 16 bits (Hamming(21,16))Para uma palavra de 16 bits, usamos Hamming(21,16):

// - Dados: 16 bits
// - Paridade: 5 bits (posições 1, 2, 4, 8, 16)
// - Posições de dados: {3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21}
// - Total: 21 bits

// Passos:1. Posicione os bits de dados (D) e paridade (P):
//     - P1 P2 D1 P4 D2 D3 D4 P8 D5 D6 D7 D8 D9 D10 D11 P16 D12 D13 D14 D15 D16
//     - Posições: 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21

// 2. Calcule os bits de paridade:
//     - P1 cobre: 3, 5, 7, 9, 11, 13, 15, 17, 19, 21
//     - P2 cobre: 3, 6, 7, 10, 11, 14, 15, 18, 19
//     - P4 cobre: 5, 6, 7, 12, 13, 14, 15, 20, 21
//     - P8 cobre: 9, 10, 11, 12, 13, 14, 15
//     - P16 cobre: 17, 18, 19, 20, 21

