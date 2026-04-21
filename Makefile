# --- Configurações de Compilador ---
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpcap # Necessário para seus analisadores de rede

# --- Diretórios ---
SRC_DIR = analisadores_rede
BIN_DIR = binarios_c
PROJ_DIR = projetos

# --- Alvos ---
# Busca todos os .c em analisadores_rede
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Gera nomes de executáveis para a pasta binarios_c
BINS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(BINS)

# Cria a pasta de binários se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra de compilação: transforma analisadores_rede/arquivo.c em binarios_c/arquivo
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@echo "🛠️ Compilando: $<"
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	@echo "✅ Gerado: $@"

pilha: pilha.c $(CC) $(CFLAGS) -o $@ $^

# Limpeza
clean:
	rm -rf $(BIN_DIR)/*
	@echo "🧹 Pasta de binários limpa."

# Atalho para backup
backup:
	@echo "Fazendo backup de toda a pasta estruturas_de_dados..."
	cd .. && ./backup_projeto.sh
