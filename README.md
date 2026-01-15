## 🛡️ IDS Project - Torres Development

Status: v4.0 (Performance & Integrity)

Ambiente de Testes:

Hardware: Lenovo IdeaPad Gaming 3

OS: Ubuntu 24.04 (Dual Boot Kali Linux Ready)

Métricas Alcançadas:

Throughput: Suporte verificado de até 12.165 pps.

Segurança: Monitoramento de integridade em tempo real via iWatch.

### 🛰️ 1. Analisador de Rotas Geográficas

Focado em mapear a jornada física de pacotes e identificar pontos críticos de troca de tráfego (IXP).

Estrutura de Dados: Lista Encadeada Simples.

Diferencial: Identificação de infraestruturas brasileiras (IX.br) e CDNs (Cloudflare, Akamai).

Métricas: Latência salto a salto com exportação para CSV/Log.

### 🛡️ 2. OSPF Performance & Integrity Monitor

Analisador focado no protocolo OSPF (proto 89), com monitoramento ativo de integridade do sistema.

Estrutura de Dados: Buffer Circular em RAM (Lista Encadeada Dupla) inspirado no Quagga.

Segurança Ativa: Integração com iWatch (inotify) para detectar alterações em /etc ou /bin.

### 🛠️ Como Compilar e Executar

O projeto utiliza um sistema de build automatizado para garantir a integridade das dependências e cabeçalhos (estruturas.h).

Instalar Dependências:

Bash

sudo apt install tcpdump hping3 iwatch

Compilar todos os módulos:

Bash

chmod +x build.sh

./build.sh

Execução com Geração de Snapshot (Log Forense):

Bash

sudo ./analisador_final.out | tee snapshot_auditoria_$(date +%Y%m%d_%H%M).log

### 📸 Snapshot & Auditoria

O uso do comando tee com $(date) permite:

Histórico: Comparação de performance entre diferentes versões do código.

Evidência Forense: Logs datados que provam a detecção de ataques ou anomalias.

Validação: Prova técnica de suporte à carga de 12k pps.

### 📊 Tecnologias

Linguagem: C (GCC)

Segurança: iWatch (File Integrity Monitoring)

Protocolos: OSPF, ICMP

Automação: Shell Script (Build System)
