#!/bin/bash

# Configurações
ALVO="192.168.0.153"  # Ajuste para o IP que você digitou no Sentinel
CONEXOES=20           # O Sentinel bloqueia com > 15

echo "🚀 Iniciando simulação de Port Scan em $ALVO..."

for ((i=1; i<=CONEXOES; i++))
do
    echo -n "Tentativa $i: Porta $i... "
    # O nc (netcat) tenta conectar. O timeout evita que o script trave.
    timeout 0.2 nc -zv $ALVO $i 2>&1 | grep -q "succeeded" && echo "ABERTA" || echo "FECHADA"
    
    # Pequena pausa para você conseguir ver o log subindo no Sentinel
    sleep 0.1
done

echo "------------------------------------------------"
echo "✅ Ataque finalizado. Verifique se o Sentinel baniu seu IP."
echo "Dica: Use 'sudo iptables -L -n' para ver o bloqueio."
