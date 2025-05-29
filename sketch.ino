#include "ponabri_config.h" // Inclui definições globais PRIMEIRO

// =================================================================
// --- CHAVE MESTRA: MODO DE OPERAÇÃO ---
#define MODO_DE_OPERACAO 0
// =================================================================

// --- INCLUSÃO CONDICIONAL DOS ARQUIVOS DE LÓGICA ---
// Para executar o MODO_DE_OPERACAO == 0, deve incluir "PubSubClient" no libraries.txt

#if MODO_DE_OPERACAO == 0
  #include "modo_rede.h"
#elif MODO_DE_OPERACAO == 1
  #include "teste_local.h"
#elif MODO_DE_OPERACAO == 2
  #include "outros_testes.h"
#endif

void setup() {
  Serial.begin(115200);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  #if MODO_DE_OPERACAO == 0
    setupNetworkMode();
  #elif MODO_DE_OPERACAO == 1
    setupLocalTest();
  #elif MODO_DE_OPERACAO == 2
    setupOtherTests();
  #endif
}

void loop() {
  #if MODO_DE_OPERACAO == 0
    loopNetworkMode();
  #elif MODO_DE_OPERACAO == 1
    loopLocalTest();
  #elif MODO_DE_OPERACAO == 2
    loopOtherTests();
  #endif
}

void piscarLed(int pino, String resultado) {
  Serial.printf("RESULTADO: %s\n\n", resultado.c_str());
  digitalWrite(pino, HIGH);
  delay(10000);
  digitalWrite(pino, LOW);
  Serial.println("Aguardando próximo comando...");
}