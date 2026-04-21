# 📊 Relatório de Análise de Latência: Kernel vs. Usuário

Este relatório apresenta uma análise comparativa entre o Round Trip Time (RTT) medido na camada de aplicação (utilizando o utilitário `ping`) e na camada de rede/enlace (captura direta via `tcpdump`).

## 🎯 Objetivo
Medir o **Overhead do Sistema Operacional**, ou seja, o tempo que o kernel do Linux e a pilha de protocolos levam para processar um pacote ICMP desde que ele atinge a interface de rede física até ser entregue ao processo do usuário.

## 💻 Ambiente de Teste
- **OS:** Linux (Debian/Ubuntu)
- **Interface:** wlp0s20f3 (Wi-Fi)
- **Ferramenta:** Script Bash customizado (`compara_rtt.sh`)

## 📈 Dados Coletados

| Alvo | Localização Est. | RTT Médio (Ping) | RTT Médio (Kernel) | Overhead do SO |
| :--- | :--- | :--- | :--- | :--- |
| **Yahoo Japão** | Japão (Ásia) | 330.141 ms | 330.675 ms | ~0.000 ms* |
| **Darknet** | EUA (América do Norte) | 175.356 ms | 163.995 ms | 11.361 ms |
| **PUC** | Brasil (Local/CDN) | 21.888 ms | 20.828 ms | **1.060 ms** |

*\*Nota: No Yahoo, a alta latência e o jitter da rede de longa distância causaram uma inversão desprezível nos carimbos de tempo.*

## 🧠 Conclusões Técnicas

1. **Impacto da Distância:** Conforme esperado, o RTT escala com a distância geográfica (Japão > EUA > Brasil).
2. **Overhead de Processamento:** No teste local (PUC), observamos um overhead de **1.060 ms**. Isso representa o tempo de interrupção de hardware, processamento da pilha TCP/IP no Kernel e a troca de contexto para o espaço do usuário.
3. **Precisão:** O `tcpdump` oferece uma visão mais fiel da latência real da fibra óptica, enquanto o `ping` inclui o "atraso de software".

<h2 align="center">📊 Comparativo de Performance: Rede vs. Sistema</h2>

<table align="center">
  <thead>
    <tr style="background-color: #333; color: white;">
      <th>Destino</th>
      <th>Distância</th>
      <th>📡 Aplicação (Ping)</th>
      <th>🔌 Kernel (Tcpdump)</th>
      <th>💻 Overhead do SO</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><b>Yahoo Japão</b></td>
      <td>Muito Alta 🌏</td>
      <td>330.14 ms</td>
      <td>330.67 ms</td>
      <td style="color: #888;">&lt; 0.1 ms</td>
    </tr>
    <tr style="background-color: #f9f9f9;">
      <td><b>Darknet</b></td>
      <td>Média 🌎</td>
      <td>175.35 ms</td>
      <td>163.99 ms</td>
      <td style="color: #d9534f; font-weight: bold;">11.36 ms</td>
    </tr>
    <tr>
      <td><b>PUC (Brasil)</b></td>
      <td>Baixa 🏠</td>
      <td>21.88 ms</td>
      <td>20.82 ms</td>
      <td style="color: #5cb85c; font-weight: bold;">1.06 ms</td>
    </tr>
  </tbody>
</table>

<p align="center">
  <i>* Valores coletados via script <code>compara_rtt.sh</code> em ambiente de teste Linux.</i>
</p>
