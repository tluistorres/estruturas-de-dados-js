Tabela: Camadas e Protocolos

 Camada       | Protocolos/Serviços              | Datagramas/Sessões            |
|--------------|----------------------------------|-------------------------------|
| Aplicação    | HTTP, FTP, SMTP, DNS, SMB, SSH   | Serviços (Web, email, etc)   |
| Apresentação | SSL/TLS, MIME, ASCII             | Codificação, compressão       |
| Sessão       | NetBIOS, RPC, SMB (sobre NetBIOS)| Gerenciamento de sessões       |
| Transporte   | TCP, UDP, SCTP                  | Conexões TCP, fluxos UDP      |
| Rede         | IP (IPv4, IPv6), ICMP, IGMP     | Pacotes IP                    |
| Enlace       | Ethernet (MAC), PPP, HDLC, ARP   | Frames                        |
| Física       | Ethernet, Wi-Fi (802.11)         | Bits                          |


Diagrama:

 OSI Layers
 ┌───────────┐
 │ Aplicação  │  (HTTP, FTP, SMB, DNS)
 ├───────────┤
 │Apresentação│  (SSL, MIME)
 ├───────────┤
 │  Sessão   │  (NetBIOS, RPC)
 ├───────────┤
 │Transporte  │  (TCP, UDP)
 ├───────────┤
 │    Rede    │  (IP, ICMP)
 ├───────────┤
 │   Enlace   │  (Ethernet, MAC)
 ├───────────┤
 │   Física   │  (Cabos, Wi-Fi)
 └───────────┘

 Porta | Descrição (protocolo) |
| --- | --- |
| 20/21 | FTP (File Transfer Protocol) |
| 22 | SSH (Secure Shell) |
| 23 | Telnet |
| 25/587 | SMTP (Simple Mail Transfer Protocol) |
| 53 | DNS (Domain Name System) |
| 67 | DHCP (Dynamic Host Configuration Protocol) |
| 69 | TFTP (Trivial File Transfer Protocol) |
| 79 | Finger |
| 80 | HTTP (Hypertext Transfer Protocol) |
| 110 | POP3 (Post Office Protocol) |
| 123 | NTP (Network Time Protocol) |
| 143 | IMAP (Internet Message Access Protocol) |
| 161/162 | SNMP (Simple Network Management Protocol) |
| 443 | HTTPS (HTTP Secure) |