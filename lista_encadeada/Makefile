# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -g

# Lista de Binários
BINS = lista_simples lista_dupla arvore sistema_processos lista_remocao pilha fila navegador

all: $(BINS)

# --- Regras de Compilação ---
# Nota: Cada linha abaixo do nome do alvo DEVE começar com um TAB

lista_simples: lista_simples.c
	$(CC) $(CFLAGS) -o $@ $^

lista_dupla: lista_dupla.c
	$(CC) $(CFLAGS) -o $@ $^

arvore: ex-arvore-binaria.c
	$(CC) $(CFLAGS) -o $@ $^

sistema_processos: sistema_processos.c
	$(CC) $(CFLAGS) -o $@ $^

lista_remocao: lista_remocao.c
	$(CC) $(CFLAGS) -o $@ $^

pilha: pilha.c
	$(CC) $(CFLAGS) -o $@ $^

fila: fila.c
	$(CC) $(CFLAGS) -o $@ $^

navegador: navegador.c
	$(CC) $(CFLAGS) -o $@ $^

# --- Utilitários ---

clean:
	rm -f $(BINS)

backup:
	@echo "🚀 A subir para a raiz e a disparar backup_projeto.sh..."
	cd .. && ./backup_projeto.sh

test_all: all
	@echo "--- Testando Memória de Tudo ---"
	valgrind --leak-check=full ./lista_simples
	valgrind --leak-check=full ./lista_dupla
	valgrind --leak-check=full ./arvore
	valgrind --leak-check=full ./pilha
	valgrind --leak-check=full ./fila
	valgrind --leak-check=full ./navegador
