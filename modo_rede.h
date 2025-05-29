#include "ponabri_config.h" // Inclui as definições de Pinos e Funções

// Bibliotecas e funções para o modo de rede
#include <WiFi.h>
#include <PubSubClient.h>

// --- Configurações de Rede e MQTT ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";
const char* topic_request = "ponabri/checkin/request";
const char* topic_response = "ponabri/checkin/response";

// --- Objetos de Rede ---
WiFiClient espClient;
PubSubClient client(espClient);

// --- Declaração antecipada de funções ---
void receiveMqttMessage(char* topic, byte* payload, unsigned int length);
void reconnectToMqtt();
void connectToWifi();

// --- Função de Setup para o Modo de Rede ---
void setupNetworkMode() {
  Serial.println("--- MODO DE REDE ATIVADO ---");
  connectToWifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(receiveMqttMessage);
}

// --- Função de Loop para o Modo de Rede ---
void loopNetworkMode() {
  if (!client.connected()) {
    reconnectToMqtt();
  }
  client.loop(); 

  if (Serial.available() > 0) {
    String codigoReserva = Serial.readStringUntil('\n');
    codigoReserva.trim();
    Serial.printf("Enviando código '%s' para validação...\n", codigoReserva.c_str());
    client.publish(topic_request, codigoReserva.c_str());
  }
}

// --- Funções Auxiliares de Rede ---
void receiveMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) { message += (char)payload[i]; }
  Serial.printf("Resposta recebida do gateway: %s\n", message.c_str());
  if (message == "valido") {
    piscarLed(LED_VERDE, "Reserva VÁLIDA");
  } else {
    piscarLed(LED_VERMELHO, "Reserva INVÁLIDA");
  }
}

void reconnectToMqtt() {
  while (!client.connected()) {
    Serial.print("Reconectando ao MQTT...");
    if (client.connect("ESP32_Ponabri_Client_FIAP")) { 
      Serial.println("Conectado!");
      client.subscribe(topic_response);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void connectToWifi() {
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
}