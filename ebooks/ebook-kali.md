| Comando | Função |
| --- | --- |
| `nmap <IP>` | Escaneia as 1000 portas mais comuns do host |
| `nmap -Pn <IP>` | Escaneia o host ignorando o ping (útil se o host bloqueia ping) |
| `nmap -p <portas> <IP>` | Escaneia portas específicas (ex: `-p 80,443`) |
| `nmap -sV <IP>` | Detecta serviços e versões nas portas abertas |
| `nmap -sT <IP>` | Faz um scan TCP connect (útil se não tem privilégios) |
| `nmap -O <IP>` | Tenta detectar o sistema operacional do host |
| `nmap -F <IP>` | Escaneia as 100 portas mais comuns |
| `nmap -p- <IP>` | Escaneia todas as portas (1-65535) |
