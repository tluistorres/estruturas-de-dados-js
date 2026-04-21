public class Interp {
    static int PC;          // Program Counter (Ponteiro para a instrução atual)
    static int AC;          // Acumulador (Onde os cálculos acontecem)
    static int instr;       // Instrução completa
    static int instr_type;  // O código da operação (Opcode)
    static int data_loc;    // Endereço do dado
    static int data;        // Valor do dado
    static boolean run_bit = true;

    // Definição do nosso conjunto de instruções (Opcodes)
    private static final int STOP  = 0; // Para o programa
    private static final int LOAD  = 1; // Carrega da Memória para o AC
    private static final int ADD   = 2; // Soma Memória ao AC
    private static final int STORE = 3; // Salva o AC na Memória
    private static final int SUB   = 4; // Subtrai Memória do AC

    public static void interpret(int memory[], int starting_address) {
        PC = starting_address;
        run_bit = true;

        while (run_bit) {
            // 1. BUSCA (Fetch)
            instr = memory[PC];
            System.out.println("Executando PC " + PC + ": Instrução " + instr);
            PC = PC + 1;

            // 2. DECODIFICAÇÃO (Decode)
            instr_type = get_instr_type(instr);
            data_loc = find_data(instr, instr_type);

            // 3. BUSCA OPERANDO (Se a instrução precisar de dados da memória)
            // Instruções como STORE e STOP tratam o data_loc de forma diferente
            if (data_loc >= 0 && instr_type != STORE) {
                data = memory[data_loc];
            }

            // 4. EXECUÇÃO
            execute(instr_type, data_loc, memory);
            
            System.out.println("   -> AC atual: " + AC);
        }
        System.out.println("Programa finalizado.");
    }

    // Extrai o primeiro dígito (Ex: 1050 -> 1)
    private static int get_instr_type(int instr) {
        return instr / 1000; 
    }

    // Extrai os últimos 3 dígitos (Ex: 1050 -> 050)
    private static int find_data(int instr, int type) {
        return instr % 1000;
    }

    // A lógica real de cada comando
    private static void execute(int type, int loc, int memory[]) {
        switch (type) {
            case STOP:
                run_bit = false;
                break;
            case LOAD:
                AC = memory[loc];
                break;
            case ADD:
                AC = AC + memory[loc];
                break;
            case SUB:
                AC = AC - memory[loc];
                break;
            case STORE:
                memory[loc] = AC;
                System.out.println("   -> Salvou " + AC + " na posição " + loc);
                break;
            default:
                System.out.println("Instrução inválida!");
                run_bit = false;
                break;        }
    }

    // Testando o interpretador
    public static void main(String[] args) {
        // Criamos uma memória de 100 posições
        int[] memoria = new int[100];

        // Vamos fazer um programa que soma 15 + 25 e salva no endereço 50
        // Endereço 0: LOAD o valor que está no endereço 10 (15)
        // Endereço 1: ADD o valor que está no endereço 11 (25)
        // Endereço 2: STORE o resultado no endereço 50
        // Endereço 3: STOP
        memoria[0] = 1010; 
        memoria[1] = 2011; 
        memoria[2] = 3050; 
        memoria[3] = 0000; 

        // Dados para o programa usar
        memoria[10] = 15; // Nosso primeiro número
        memoria[11] = 25; // Nosso segundo número

        // Inicia o interpretador no endereço 0
        interpret(memoria, 0);

        // Verifica se o resultado está na memória 50
        System.out.println("Resultado final na memória[50]: " + memoria[50]);
    }
}

// Para tornar este código funcional, precisamos definir uma arquitetura de instruções (o que cada número significa) e implementar a lógica que falta nos métodos vazios.
// Vou criar uma implementação baseada em uma máquina decimal simples (estilo didática), onde a instrução funciona assim:
// Se a instrução é 1050, o "1" é o comando (ex: somar) e "050" é o endereço na memória.
// Aqui está o código completo e funcional:
// code
// Java
// O que foi alterado/adicionado:
// Lógica dos Opcodes: Defini que os comandos são 1 (Load), 2 (Add), 3 (Store), etc.
// Separação de Instrução e Endereço: Usei divisão por 1000 (/ 1000) para pegar o comando e resto (% 1000) para pegar o endereço. Isso é comum em arquiteturas antigas que usavam palavras decimais.
// Correção no execute:
// Mudei o parâmetro de true para type (como mencionado antes, true é proibido).
// Adicionei o array memory como parâmetro no execute, pois a instrução STORE precisa escrever na memória.
// Método main: Criei um exemplo real. Ele carrega o número 15, soma com 25, salva o resultado (40) em outro lugar e desliga.
// Como testar:
// Copie o código para um arquivo chamado Interp.java.
// Compile com javac Interp.java.
// Execute com java Interp.
// O console mostrará o passo a passo do processador "trabalhando".
