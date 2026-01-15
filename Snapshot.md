## 📸 Guia de Geração: Snapshot v4.0

Para garantir a integridade dos testes e manter um histórico preciso da performance do seu IDS, siga as instruções abaixo para gerar o Snapshot v4.0.

## 🚀 Comando de Execução

Utilize o comando abaixo para rodar o analisador e salvar a saída simultaneamente em um arquivo de log datado:

Bash

sudo ./analisador_final | tee snapshot_auditoria_$(date +%Y%m%d_%H%M).log

## 🛠️ Por que usar o tee?

Histórico: O comando $(date +%Y%m%d_%H%M) cria um arquivo com nome único (ex: snapshot_auditoria_20260115_1445.log). Isso permite comparar o desempenho de forma granular entre diferentes versões.

Evidência: Caso o iWatch detecte um ataque real ou uma anomalia de rede (como a inundação OSPF detectada hoje), você terá um log datado para análise forense detalhada.

GitHub: Recomendamos subir esses arquivos .log para uma pasta /logs no seu repositório. Isso serve como prova técnica de que seu código suporta a carga de 12k pps (pacotes por segundo) observada nos testes.

## 📝 Sugestão para o seu README.md

Adicione o bloco abaixo no topo do seu arquivo README.md para destacar o status profissional do projeto:

Markdown

# 🛡️ IDS Project - Torres Development

> **Status:** v4.0 (Performance & Integrity)
> 
> **Ambiente de Testes:**
> - **Hardware:** Lenovo IdeaPad Gaming 3
> - **OS:** Ubuntu 24.04 (Dual Boot Kali Linux Ready)
> 
> **Métricas Alcançadas:**
> - **Throughput:** Suporte verificado de até **12.165 pps**.
> - **Segurança:** Monitoramento de integridade de arquivos em tempo real via integração **iWatch**.
