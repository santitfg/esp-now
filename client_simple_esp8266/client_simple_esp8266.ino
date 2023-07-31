
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
  int id;
  float valorFlow;
  float filtro;
  float rB;
  float gB;
  float bB;
  float rD;
  float gD;
  float bD;
};


datos_envio envio;

//void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len) {
void OnDataRecv( uint8_t *mac_addr,  uint8_t *incomingData, uint8_t data_len) {

  memcpy(&envio, incomingData, sizeof(envio));

  Serial.print(". Dato id: "); Serial.print(envio.id);
  Serial.print(". Dato valorFlow: "); Serial.println(envio.valorFlow);
  Serial.println();
  Serial.print("envio.rB : ");
  Serial.println(envio.rB);
  Serial.print("envio.gB: ");
  Serial.println(envio.gB);
  Serial.print("envio.bB: ");
  Serial.println(envio.bB);
  Serial.print("envio.rD : ");
  Serial.println(envio.rD);
  Serial.print("envio.gD: ");
  Serial.println(envio.gD);
  Serial.print("envio.bD: ");
  Serial.println(envio.bD);
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
