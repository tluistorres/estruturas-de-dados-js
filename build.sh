#!/bin/bash

# Cores para o terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sem cor

echo -e "${GREEN}🔨 Iniciando Compilação do Projeto IDS v4.0...${NC}"

# Remove binários antigos para garantir uma build limpa
rm -f *.out

# Lista de arquivos para compilar
arquivos=(
    "analisador_conectividade.c"
    "analisador_hibrido.c"
    "analisador_final.c"
    "analisador_rotas.c"
)

# Loop de compilação
for arquivo in "${arquivos[@]}"; do
    if [ -f "$arquivo" ]; then
        gcc "$arquivo" -o "${arquivo%.c}.out" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo -e "[ ✅ ] $arquivo -> ${arquivo%.c}.out"
        else
            echo -e "[ ❌ ] Erro ao compilar $arquivo (Verifique dependências)"
        fi
    fi
done

echo -e "${GREEN}✨ Processo concluído!${NC}"
