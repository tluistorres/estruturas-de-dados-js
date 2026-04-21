#!/bin/bash

EMAIL="luistorres090165@gmail.com"
DATA=$(date +%d-%m-%Y_%Hh%M)
# Se estiver na raiz de estruturas_de_dados, faz backup de tudo. 
# Se estiver em uma pasta (ex: projeto_coracao), faz só dela.
NOME_ALVO=$(basename "$PWD")
ARQUIVO_BACKUP="/tmp/backup_${NOME_ALVO}_${DATA}.tar.gz"

echo "📦 Gerando backup de: $NOME_ALVO"

# Criar o tar.gz excluindo pastas pesadas e binários de C (.out e sem extensão)
# Isso mantém o anexo leve para o Gmail
tar -czf "$ARQUIVO_BACKUP" \
    --exclude='node_modules' \
    --exclude='*.pcap' \
    --exclude='*.out' \
    --exclude='*.bin' \
    --exclude='analisador_*' \
    .

# Enviar via Mutt
echo "Relatório de Backup:
Projeto: $NOME_ALVO
Data: $(date)
Arquivos incluídos: Scripts JS, Fontes C, Markdown e Logs." | \
mutt -s "🚀 Backup Estruturas: $NOME_ALVO" -a "$ARQUIVO_BACKUP" -- "$EMAIL"

rm "$ARQUIVO_BACKUP"
echo "✅ Enviado com sucesso para $EMAIL"
