#define BLYNK_TEMPLATE_ID "TMPL205_eDRI4"
#define BLYNK_TEMPLATE_NAME "ESP8266"

#define BLYNK_FIRMWARE_VERSION        "1.3.2"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

BlynkTimer timer; // Instância do timer

const int pinSensor = A0; // Pino utilizado pelo sensor

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(1000L, myTimerEvent); // Intervalo em milisegundos
}

void loop() {
  BlynkEdgent.run(); // Executa o Blynk
  timer.run(); // Executa o timer
}

void myTimerEvent()
{
  int umidade = analogRead(pinSensor); // Variável que armazena leitura de umidade do solo
  String texto = analisaUmidade(umidade); // Analisa o valor lido pelo sensor

  // Enviando valores para o Blynk.
  Blynk.virtualWrite(V4, umidade);
  Blynk.virtualWrite(V5, texto);
}

String analisaUmidade(int valorSensor) {

  // Status: Solo úmido
  if (valorSensor >= 0 && valorSensor <= 600)
  {
    return "Úmido";
  }

  // Status: Umidade moderada
  if (valorSensor > 600 && valorSensor <= 800)
  {
    return "Média";
  }

  // Status: Solo seco
  if (valorSensor > 800 && valorSensor <= 1024)
  {
    return "Seco";
  }
  return "Erro";
}
