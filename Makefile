# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -g

# Alvos (executáveis)
all: analisador_universal analisador_estatistico

analisador_universal: analisador_universal.c
	$(CC) $(CFLAGS) analisador_universal.c -o analisador_universal

analisador_estatistico: analisador_estatistico.c
	$(CC) $(CFLAGS) analisador_estatistico.c -o analisador_estatistico

clean:
	rm -f analisador_universal analisador_estatistico