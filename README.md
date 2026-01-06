# Analisador de Rotas Geográficas em C

Este projeto utiliza **Listas Encadeadas** para mapear a jornada de um pacote de rede. 

## 🚀 Funcionalidades
- Captura de dados em tempo real via `traceroute`.
- Armazenamento dinâmico em **Lista Encadeada**.
- Análise Heurística de infraestrutura (Detecta IX.br Fortaleza, Cloudflare, Akamai).
- Cálculo de latência média e estatísticas de performance.
- Persistência de dados em arquivo de log.

## ��️ Tecnologias
- Linguagem C
- Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- Ambiente: Linux (Debian/Ubuntu)

"O projeto inclui arquivos .pcap para análise forense de rede, permitindo verificar a latência de cada salto capturado diretamente na camada de enlace."