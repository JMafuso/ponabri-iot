#include "ponabri_config.h" // Inclui as definições de Pinos e Funções

// Funções para outros tipos de testes

void setupOtherTests() {
  Serial.println("--- MODO 'OUTROS TESTES' ATIVADO ---");
  Serial.println("Iniciando teste de sequência de LEDs...");
}

void loopOtherTests() {
  // Testa o LED Verde
  Serial.println("Testando LED Verde...");
  digitalWrite(LED_VERDE, HIGH);
  delay(1000);
  digitalWrite(LED_VERDE, LOW);
  delay(500);

  // Testa o LED Vermelho
  Serial.println("Testando LED Vermelho...");
  digitalWrite(LED_VERMELHO, HIGH);
  delay(1000);
  digitalWrite(LED_VERMELHO, LOW);
  delay(2000); // Espera 2 segundos antes de repetir
}