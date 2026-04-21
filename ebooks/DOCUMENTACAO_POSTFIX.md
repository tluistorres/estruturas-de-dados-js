# Documentação de Configuração: Postfix + Gmail Relay
**Data:** 20 de Janeiro de 2026
**Autor:** Luis Torres
**Projeto:** Projeto Coração (Estruturas de Dados)

## 1. Objetivo
Configurar o servidor de e-mail local (Postfix) para realizar o envio de notificações e arquivos para e-mails externos (Gmail) utilizando um túnel autenticado (Relay).

## 2. Pré-requisitos no Google
* Autenticação de dois fatores ativa.
* **Senha de App:** Gerada no painel de segurança do Google (16 dígitos).

## 3. Configuração do Postfix (`/etc/postfix/main.cf`)
As configurações principais para o funcionamento correto foram:

* **Protocolo:** Forçado para `ipv4` para evitar erros de rede inacessível.
* **Relay Host:** `[smtp.gmail.com]:587`
* **Segurança TLS:** Ativada como `encrypt`.

```text
inet_protocols = ipv4
relayhost = [smtp.gmail.com]:587
smtp_sasl_auth_enable = yes
smtp_sasl_password_maps = hash:/etc/postfix/sasl_passwd
smtp_sasl_security_options = noanonymous
smtp_tls_security_level = encrypt

## 4. Gerenciamento de Credenciais

As credenciais foram armazenadas em /etc/postfix/sasl_passwd no formato: [smtp.gmail.com]:587 seu-email@gmail.com:sua-senha-de-app

Comandos de manutenção:

sudo postmap /etc/postfix/sasl_passwd (Para atualizar a base de dados de senhas)

sudo systemctl restart postfix (Para aplicar mudanças)

## 5. Comandos Úteis de Terminal

Verificar a fila de e-mails:

mailq

Limpar toda a fila (Delete ALL):

sudo postsuper -d ALL

Monitorar logs em tempo real:

sudo tail -f /var/log/mail.log

Enviar e-mail com anexo:

echo "Corpo do e-mail" | mutt -s "Assunto" -a arquivo.ext -- destinatario@gmail.com

## 6. Resolução de Erros Comuns

SASL Authentication Failed: Senha de app incorreta ou ausente.

Network is unreachable: Tentativa de uso de IPv6 em rede não compatível (resolvido mudando para inet_protocols = ipv4).

User lookup error (iwatch): Típico de logs gerados por serviços automáticos enviando para usuários inexistentes.

---

### Passo 3: Salvar e Testar

1. No nano, aperte `Ctrl + O` e `Enter` para salvar.
2. Aperte `Ctrl + X` para sair.
3. **Que tal fechar com chave de ouro enviando a sua própria documentação para o seu e-mail?**

```bash
echo "Documentação técnica gerada hoje." | mutt -s "Doc: Configuração Postfix" -a DOCUMENTACAO_POSTFIX.md -- luistorres090165@gmail.com
