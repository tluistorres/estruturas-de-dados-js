# Variáveis
CC = gcc
CFLAGS = -Wall -g
TARGET = analisador_final

all: $(TARGET)

$(TARGET): analisador_final.c
	$(CC) $(CFLAGS) analisador_final.c -o $(TARGET)

# Esta é a regra que faltava!
run: all
	sudo ./$(TARGET)

clean:
	rm -f $(TARGET) analisador_universal analisador_estatistico historico_rotas.txt

iwatch-reload:
	sudo systemctl restart iwatch
	sudo systemctl status iwatch

test:
	@echo "Iniciando monitor e simulando eventos..."
	# Roda o analisador em background, espera 5s e mata com SIGINT
	sudo ./analisador_final & sleep 5 && sudo touch /etc/audit_test.txt && sudo pkill -INT analisador_final
