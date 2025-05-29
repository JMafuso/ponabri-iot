# Sistema de Check-in e Validação de Reserva por QR Code - Ponabri IoT

## 1. Checklist de Requisitos Técnicos Mínimos da Disciplina de IoT

| Requisito Técnico                          | Atendido? | Justificativa / Evidência                                                                                   |
|-------------------------------------------|-----------|-------------------------------------------------------------------------------------------------------------|
| Sistema IoT com 3+ dispositivos            | Sim       | ESP32 (Wokwi), Node-RED (gateway), API .NET no Azure (serviço backend)                                      |
| Hardware ESP32/Wokwi                        | Sim       | Código-fonte para ESP32 com uso de LEDs e Wi-Fi no Wokwi                                                    |
| Dashboard                                  | Sim       | Node-RED com nós de debug e monitoramento via painel                                                        |
| Gateway Node-RED                           | Sim       | Fluxo Node-RED que atua como gateway MQTT e faz chamadas HTTP para API .NET                                 |
| Protocolos MQTT e HTTP JSON com tópicos únicos | Sim       | MQTT com tópicos `ponabri/checkin/request` e `ponabri/checkin/response`; HTTP GET para API .NET com JSON     |

---

## 2. Descrição Completa da Solução IoT

### Sistema de Check-in e Validação de Reserva por QR Code

O sistema Ponabri implementa um mecanismo de check-in e validação de reservas por QR Code, onde o ESP32 simula a leitura do código de reserva e envia essa informação para validação. O objetivo é garantir que apenas reservas válidas sejam aceitas, proporcionando segurança e controle no acesso.

Este sistema integra-se ao projeto Ponabri como uma solução IoT disruptiva, utilizando comunicação MQTT para troca de mensagens entre o dispositivo ESP32 e o gateway Node-RED, que por sua vez consulta uma API .NET hospedada no Azure para validar as reservas.

### Componentes de Hardware no Wokwi

- **ESP32:** Microcontrolador responsável por capturar o código de reserva via Serial (simulação) e comunicar-se via MQTT.
- **LEDs (Verde e Vermelho):** Indicadores visuais que sinalizam se a reserva é válida (LED verde) ou inválida (LED vermelho).

> **Sugestão de imagens:**  
> - Aqui, adicione um print do circuito no Wokwi mostrando o ESP32 e os LEDs conectados.  
> - Aqui, adicione um print do fluxo principal do Node-RED com os nós MQTT, Function e HTTP Request.

---

## 3. Instruções Didáticas para Configuração, Execução e Testes

### Configuração do Wokwi (ESP32)

- Crie ou copie os seguintes arquivos no ambiente Wokwi:
  - `ponabri_config.h`
  - `sketch.ino`
  - `modo_rede.h`
  - `teste_local.h`
  - `outros_testes.h`
  - `libraries.txt`

- Configure a chave mestra `MODO_DE_OPERACAO` no arquivo `sketch.ino` para o modo de rede (valor `0`):

```c
#define MODO_DE_OPERACAO 0
```

- O arquivo `libraries.txt` deve conter a biblioteca necessária para o modo de rede:

```
PubSubClient
```

### Configuração do Node-RED

- Importe o arquivo de fluxo `ponabri_nodered_flows.json` (ou `flows.json`) no Node-RED.
- Os principais nós do fluxo são:
  - **MQTT in:** conecta ao broker `test.mosquitto.org` e escuta o tópico `ponabri/checkin/request`.
  - **Function (Prepara Chamada API):** constrói a URL da API .NET no Azure para validação da reserva.
  - **HTTP Request:** realiza uma requisição GET para a API .NET.
  - **Function (Processa Resposta da API):** interpreta a resposta JSON da API e prepara a mensagem para o ESP32.
  - **MQTT out:** publica a resposta no tópico `ponabri/checkin/response` para o ESP32.
- Configure a URL base da API .NET no nó "Prepara Chamada API" conforme o deploy realizado pela pipeline DevOps no Azure, por exemplo:

```
https://ponabriapiapp-ggdbf5fagphpfzc8.brazilsouth-01.azurewebsites.net
```

### Execução e Teste do Sistema Integrado

- Inicie a simulação no Wokwi com o modo de operação configurado para rede (`MODO_DE_OPERACAO = 0`).
- No Node-RED, certifique-se de que o fluxo está com o botão **Deploy** ativado.
- No Serial Monitor do Wokwi, digite um código de reserva para simular a entrada.
- Observe:
  - No Wokwi: os LEDs acendem verde para código válido e vermelho para código inválido; mensagens de status aparecem no Serial Monitor.
  - No Node-RED: o painel de debug exibe as mensagens MQTT recebidas, chamadas HTTP e respostas da API.

---

## 4. Detalhamento dos Fluxos Implementados no Node-RED

### Fluxo Principal de Validação da Reserva

- **Nó `MQTT in` ("Recebe de ESP32"):**  
  Escuta o tópico `ponabri/checkin/request` e recebe mensagens do ESP32 contendo o código da reserva.

- **Nó `Function` ("Prepara Chamada API"):**  
  Processa a mensagem recebida, extrai o código da reserva e constrói a URL para a API .NET no Azure, usando a base URL do deploy da pipeline DevOps.

- **Nó `HTTP Request` ("Chama API Ponabri no Azure"):**  
  Realiza uma requisição HTTP GET para a URL construída, esperando uma resposta JSON da API.

- **Nó `Function` ("Processa Resposta da API"):**  
  Interpreta o JSON retornado pela API, extrai o campo `status` (ex: "valido" ou "invalido") e prepara a mensagem para envio ao ESP32.

- **Nó `MQTT out` ("Envia para o ESP32"):**  
  Publica a resposta no tópico `ponabri/checkin/response`, que o ESP32 escuta para reagir.

- **Nós `debug`:**  
  Auxiliam no monitoramento do fluxo, exibindo mensagens MQTT, chamadas HTTP e respostas da API para facilitar o desenvolvimento e depuração.

---

## 5. Apresentação Clara do Código-Fonte

- **ponabri_config.h:**  
  Define os pinos dos LEDs e declara a função global `piscarLed`.

- **sketch.ino:**  
  Arquivo principal que inclui a "chave mestra" `MODO_DE_OPERACAO` para selecionar o modo de operação (rede, teste local, outros testes) e chama as funções de setup e loop correspondentes.

- **modo_rede.h:**  
  Implementa a lógica de conexão Wi-Fi, MQTT, envio e recebimento de mensagens, e controle dos LEDs conforme a validação da reserva.

- **teste_local.h:**  
  Modo de teste local que valida um código fixo ("12345") sem comunicação de rede.

- **outros_testes.h:**  
  Testa a sequência dos LEDs para verificar o hardware.

- **libraries.txt:**  
  Lista a biblioteca `PubSubClient` necessária para o modo de rede.

---

## 6. Explicação da Integração (Wokwi -> Node-RED -> API .NET via Pipeline DevOps)

O sistema IoT Ponabri integra os seguintes componentes:

1. **ESP32 (Wokwi):**  
   Envia o código da reserva via MQTT para o broker público `test.mosquitto.org`.

2. **Node-RED (Gateway):**  
   Inscreve-se no broker MQTT, recebe o código da reserva, e realiza uma chamada HTTP GET para a API .NET hospedada no Azure.

3. **API .NET no Azure:**  
   A URL da API (ex: `https://ponabriapiapp-....azurewebsites.net`) é resultado do processo de deploy automatizado pela pipeline DevOps no Azure. A API valida o código e retorna uma resposta JSON.

4. **Node-RED:**  
   Processa a resposta da API e publica uma mensagem MQTT de volta para o ESP32 indicando se a reserva é válida ou inválida.

5. **ESP32:**  
   Recebe a resposta MQTT e acende o LED verde ou vermelho conforme o resultado da validação.
