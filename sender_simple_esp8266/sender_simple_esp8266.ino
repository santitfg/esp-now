
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


//#include <SerialUntrefEsp.h>
//SerialUntrefEsp sUntref;

#define CHANNEL 0
#define ID 0


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
//48: 3F: DA: 0E: 4B: 8B

uint8_t broadcastAddress0[] = {0x48, 0x3F, 0xDA, 0x0E, 0x4B, 0x8B};

void OnDataSent(uint8_t *mac_addr, uint8_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: ");
  Serial.println(macStr);
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == 0 ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);


  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress0, ESP_NOW_ROLE_SLAVE, CHANNEL, NULL, 0);


  envio.id = ID;
}

void loop() {
  envio.valorFlow = rand();
  envio.filtro = rand();
  envio.rB = rand();
  envio.gB = rand();
  envio.bB = rand();
  envio.rD = rand();
  envio.gD = rand();
  envio.bD = rand();

  esp_now_send(  broadcastAddress0, (uint8_t *) &envio, sizeof(datos_envio));
  delay(1000);

}
