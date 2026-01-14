# Network Analysis & Performance Suite

Este repositório contém ferramentas em C desenvolvidas para análise de infraestrutura de rede e monitoramento de protocolos, unindo conceitos de **Estruturas de Dados** com administração de sistemas Linux.

---

## 🛰️ 1. Analisador de Rotas Geográficas
Focado em mapear a jornada física de pacotes e identificar pontos críticos de troca de tráfego (IXP).

- **Estrutura de Dados:** Lista Encadeada Simples.
- **Diferencial:** Identificação heurística de CDN (Cloudflare, Akamai) e infraestruturas brasileiras (IX.br).
- **Métricas:** Latência salto a salto e persistência em CSV/Log.

---

## 🛡️ 2. OSPF Performance & Integrity Monitor (v4.0)
Analisador de tráfego de nível industrial focado no protocolo **OSPF (proto 89)**, com monitoramento de integridade do sistema.

- **Estrutura de Dados:** Buffer Circular em RAM (Lista Encadeada Dupla) inspirado no **Quagga/OSPF-MDR**.
- **Segurança Ativa:** Integração com `iWatch` (inotify) para detectar alterações em `/etc` ou `/bin` durante a captura de rede.
- **Análise Forense:** Suporte a arquivos `.pcap` para inspeção de pacotes.

### 🚀 Como rodar
1. **Pré-requisitos:**
   ```bash
   sudo apt install tcpdump hping3 iwatch


### Compilação e Execução:

Bash

make
sudo make run

### 📊 Relatório Final

Ao encerrar com Ctrl+C, o sistema gera automaticamente:

Taxa de pacotes por segundo (PPS).

Log de eventos de integridade capturados pelo iWatch no syslog.

Dump das rotas processadas em RAM.

### 🛠️ Tecnologias

Linguagem: C (GCC)

Segurança: iWatch (File Integrity Monitoring)

Protocolos: OSPF, ICMP

Automação: Makefile
