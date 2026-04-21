// Modelo de um simples interpretador que simula máquinas PDP-8, intel 8080 e o NEANDER

public class Interp {
    static int PC;
    static int AC;
    static int instr;
    static int instr_type;
    static int data_loc;
    static int data;
    static boolean run_bit = true;

    public static void interpret(int memory[], int starting_address) {

    PC = starting_address;
    while (run_bit) {
        instr = memory[PC];
        PC = PC + 1;
        instr_type = get_instr_type(instr);
        data_loc = find_data(instr, instr_type);
        if (data_loc >= 0)
            data = memory[data_loc];
        execute(instr_type, data);
        }
    }
    
    private static int get_instr_type(int addr) { ... }
    private static int find_data(int instr, int type) { ... }
    private static void execute(int type, int data) { ... }