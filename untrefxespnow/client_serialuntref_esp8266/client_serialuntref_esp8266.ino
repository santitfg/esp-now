#include <SerialUntrefEsp.h>
SerialUntrefEsp sUntref;


#if defined(ESP32)
#include "WiFi.h"
#include <esp_now.h>
#elif defined(ESP8266)
#include "ESP8266WiFi.h"
#include <espnow.h>

#else
// Non supported board
#error This board is not supported
#endif


#define CHANNEL 0

typedef struct datos_envio {
  float distancia;
};


datos_envio envio;

//void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len) {
void OnDataRecv( uint8_t *mac_addr,  uint8_t *incomingData, uint8_t data_len) {

  memcpy(&envio, incomingData, sizeof(envio));


  sUntref.newPackage();

  sUntref.addFloat(envio.distancia);

  sUntref.endPackage();
  for (int i = 0; i < sUntref.dataOutSize; i++) {
    Serial.write(sUntref.getDataOut(i));

  }
  Serial.print("distacia: ");
  Serial.println(envio.distancia);

}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //esp_now_register_send_cb
  //esp_now_register_recv_cb(OnDataRecv);
#if defined(ESP8266)
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
#else
  esp_now_register_recv_cb(OnDataRecv);

#endif



}

void loop() {

}
