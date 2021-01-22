       #ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
       #endif 

       #include <Arduino.h>
       #ifdef ESP8266 
       #include <ESP8266WiFi.h>
       #endif 
       #ifdef ESP32   
       #include <WiFi.h>
       #endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "brisa-1246194"  // Nome da rede wifi
#define WIFI_PASS         "lfpo3vpc" //Senha da rede wifi
#define APP_KEY           "9a3a96d0-1089-4511-93fb-7c052377b0c5"      // Tem que ser semelhante a "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "cb4eefae-b76c-4f38-9d48-7b3f477c6dfb-9fca72ab-1e03-4281-a2c0-63bb7b38b3fa"   // Deve ser parecido "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "6006bf28905d812f24105d16"    // Deve ser parecido "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         9600                // Altere a taxa de transmissao de acordo com a sua necessidade

#define RELAY_PIN          5                  // Pino aonde o rele é conectado (D1 = GPIO 05 on ESP8266)

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, state);             // Definir o estado do Pin
  return true;                                // Solicitação tratada adquadamente
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);                 // Definir pino de relé para modo de saída
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // Start wifi

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   // Criar um novo dispositivo de troca
  mySwitch.onPowerState(onPowerState);                // apply onPowerState callback
  SinricPro.begin(APP_KEY, APP_SECRET);               // start SinricPro
}

void loop() {
  SinricPro.handle();                         // handle SinricPro commands
}
