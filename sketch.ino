#include "ponabri_config.h" // Inclui definições globais PRIMEIRO

// =================================================================
// --- CHAVE MESTRA: MODO DE OPERAÇÃO ---
// Define o modo de operação do sistema:
// 0 - Modo Rede (comunicação via MQTT e Node-RED)
// 1 - Modo Teste Local (validação local sem rede)
// 2 - Outros Testes (testes de hardware, LEDs, etc.)
#define MODO_DE_OPERACAO 0
// =================================================================

// --- INCLUSÃO CONDICIONAL DOS ARQUIVOS DE LÓGICA ---
// Inclui o arquivo correspondente ao modo de operação selecionado.
// Para o modo rede (0), é necessário incluir a biblioteca PubSubClient no libraries.txt.
#if MODO_DE_OPERACAO == 0
  #include "modo_rede.h"
#elif MODO_DE_OPERACAO == 1
  #include "teste_local.h"
#elif MODO_DE_OPERACAO == 2
  #include "outros_testes.h"
#endif

// Função de configuração inicial do ESP32
void setup() {
  Serial.begin(115200); // Inicializa comunicação serial para debug e entrada de dados
  pinMode(LED_VERDE, OUTPUT); // Configura pino do LED verde como saída
  pinMode(LED_VERMELHO, OUTPUT); // Configura pino do LED vermelho como saída

  // Chama a função de setup específica do modo de operação selecionado
  #if MODO_DE_OPERACAO == 0
    setupNetworkMode();
  #elif MODO_DE_OPERACAO == 1
    setupLocalTest();
  #elif MODO_DE_OPERACAO == 2
    setupOtherTests();
  #endif
}

// Função principal que roda continuamente no ESP32
void loop() {
  // Chama a função de loop específica do modo de operação selecionado
  #if MODO_DE_OPERACAO == 0
    loopNetworkMode();
  #elif MODO_DE_OPERACAO == 1
    loopLocalTest();
  #elif MODO_DE_OPERACAO == 2
    loopOtherTests();
  #endif
}

// Função para piscar o LED correspondente e imprimir resultado no Serial Monitor
// pino: pino do LED a ser acionado
// resultado: mensagem a ser exibida no Serial Monitor
void piscarLed(int pino, String resultado) {
  Serial.printf("RESULTADO: %s\n\n", resultado.c_str());
  digitalWrite(pino, HIGH); // Liga o LED
  delay(10000);             // Mantém o LED ligado por 10 segundos
  digitalWrite(pino, LOW);  // Desliga o LED
  Serial.println("Aguardando próximo comando...");
}
