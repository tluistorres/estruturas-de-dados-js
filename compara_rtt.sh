#!/bin/bash

# Solicita o alvo ao usuário
echo -n "Digite o domínio ou IP para análise: "
read ALVO

# Resolve o IP
IP_ALVO=$(host $ALVO | grep -m 1 "has address" | awk '{print $4}')
if [ -z "$IP_ALVO" ]; then
    IP_ALVO=$ALVO
fi

INTERFACE="wlp0s20f3"
ARQUIVO_PCAP="captura_temporaria.pcap"

echo "====================================================="
echo "📊 COMPARADOR DE RTT: PING vs TCPDUMP"
echo "Alvo: $ALVO ($IP_ALVO)"
echo "====================================================="

# 1. Inicia o tcpdump no background
# Usamos -U (packet-buffered) para garantir que os dados vão para o arquivo imediatamente
sudo tcpdump -i $INTERFACE -n host $IP_ALVO and icmp -c 10 -U -w $ARQUIVO_PCAP > /dev/null 2>&1 &
TCPDUMP_PID=$!

sleep 2 

echo "🚀 Disparando 5 Pings..."
SAIDA_PING=$(ping -c 5 $IP_ALVO)
echo "$SAIDA_PING" | grep "time="

# Extrai a média do RTT do comando Ping (usa vírgula ou ponto conforme o sistema)
RTT_PING_AVG=$(echo "$SAIDA_PING" | tail -1 | awk -F '/' '{print $5}' | tr ',' '.')

echo -e "\n🔍 Analisando precisão no nível do Kernel (TCPDUMP)..."

# 2. Processamento dos carimbos de tempo (Timestamps)
# Ajustamos o awk para ser mais flexível na captura do número de sequência
RTT_TCPDUMP_AVG=$(tcpdump -r $ARQUIVO_PCAP -n -tt 2>/dev/null | awk '
    /echo request/ {
        match($0, /seq [0-9]+/);
        s = substr($0, RSTART+4, RLENGTH-4);
        req_time[s] = $1;
    }
    /echo reply/ {
        match($0, /seq [0-9]+/);
        s = substr($0, RSTART+4, RLENGTH-4);
        if (req_time[s]) {
            diff = $1 - req_time[s];
            soma += diff;
            cont++;
        }
    }
    END { if (cont > 0) printf "%.3f", (soma/cont)*1000; else print "0.000" }
')

# Garante que RTT_TCPDUMP_AVG não seja vazio
if [ -z "$RTT_TCPDUMP_AVG" ]; then RTT_TCPDUMP_AVG="0.000"; fi

echo "-----------------------------------------------------"
echo "✅ RESULTADO FINAL (Média RTT):"
echo "-----------------------------------------------------"
echo "Média via PING:    $RTT_PING_AVG ms"
echo "Média via TCPDUMP: $RTT_TCPDUMP_AVG ms"

# 3. Cálculo de Overhead (Forçando localidade C para evitar erro de vírgula/ponto)
OVERHEAD=$(awk "BEGIN {print $RTT_PING_AVG - $RTT_TCPDUMP_AVG}")

echo "-----------------------------------------------------"
echo "✅ RESULTADO FINAL (Média RTT):"
echo "-----------------------------------------------------"
echo "Média via PING:    $RTT_PING_AVG ms"
echo "Média via TCPDUMP: $RTT_TCPDUMP_AVG ms"

# Usamos LC_NUMERIC=C para o printf aceitar o ponto decimal do awk
LC_NUMERIC=C printf "Overhead do SO:    %.3f ms\n" "$OVERHEAD"

# Limpeza
rm -f $ARQUIVO_PCAP
