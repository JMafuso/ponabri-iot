// =======================================================
// ARQUIVO DE CONFIGURAÇÃO CENTRAL - ponabri_config.h
// Todas as definições e declarações globais ficam aqui.
// =======================================================

// Evita que o arquivo seja incluído múltiplas vezes
#ifndef PONABRI_CONFIG_H
#define PONABRI_CONFIG_H

// --- Definições dos Pinos ---
#define LED_VERDE 13
#define LED_VERMELHO 2

// --- Declaração de Funções Globais ---
// Informa a todos os arquivos que a função 'piscarLed' existe.
// A definição completa dela continua no sketch.ino principal.
void piscarLed(int pino, String resultado);

#endif