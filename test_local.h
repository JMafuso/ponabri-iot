#include "ponabri_config.h" // Inclui as definições de Pinos e Funções

// Funções para o modo de teste local
void setupLocalTest() {
  Serial.println("--- MODO DE TESTE LOCAL ATIVADO ---");
  Serial.println("Digite '12345' para teste VÁLIDO.");
}

void loopLocalTest() {
  if (Serial.available() > 0) {
    String codigoReserva = Serial.readStringUntil('\n');
    codigoReserva.trim();
    Serial.printf("Código de teste recebido: %s\n", codigoReserva.c_str());

    if (codigoReserva == "12345") {
      piscarLed(LED_VERDE, "Reserva VÁLIDA (Teste Local)");
    } else {
      piscarLed(LED_VERMELHO, "Reserva INVÁLIDA (Teste Local)");
    }
  }
}