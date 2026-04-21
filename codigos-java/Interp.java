// Declaração da classe Interp
public class Interp {

    // Método principal de interpretação do programa
    public static void interpret(int memory[], int starting_address) {
        int PC = starting_address; // Program Counter: endereço da próxima instrução
        boolean run_bit = true; // Flag para controlar o loop de execução

        // Loop principal de execução enquanto run_bit for true e PC válido
        while (run_bit && PC < memory.length) {
            int instr = memory[PC]; // Lê a instrução da memória
            PC = PC + 1; // Incrementa o PC
            int instr_type = get_instr_type(instr); // Identifica o tipo da instrução (0: soma, 1: subtração, 2: pare)
            int data_loc = find_data(instr, instr_type); // Encontra o local dos dados

            // Se o local dos dados for válido, lê o dado da memória
            if (data_loc >= 0 && data_loc < memory.length) {
                int data = memory[data_loc];
                run_bit = execute(instr_type, data); // Executa a instrução e atualiza run_bit
            }
        }
    }

    // Método para determinar o tipo da instrução
    private static int get_instr_type(int addr) {
        // Exemplo: 0 = soma, 1 = subtração, 2 = pare
        if (addr % 3 == 0) return 0; // Soma
        if (addr % 3 == 1) return 1; // Subtração
        return 2; // Pare
    }

    // Método para encontrar o local dos dados na memória
    private static int find_data(int instr, int type) {
        // Exemplo: busca dado no próximo endereço ou no final
        return (instr + type) % 5; // Retorna índice válido (0-4)
    }

    // Método para executar a instrução
    private static boolean execute(int instrType, int data) {
        if (instrType == 0) {
            System.out.println("Somando: " + data);
            return true;
        }
        if (instrType == 1) {
            System.out.println("Subtraindo: " + data);
            return true;
        }
        if (instrType == 2) {
            System.out.println("Parando execução.");
            return false; // Para o loop
        }
        return true;
    }

    // Método main para teste
    public static void main(String[] args) {
        int[] memory = {1, 2, 3, 4, 5};
        interpret(memory, 0);
    }
}
