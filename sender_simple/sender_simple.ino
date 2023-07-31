#include <WiFi.h>
#include <esp_now.h>
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

uint8_t broadcastAddress0[] = {0x30, 0xC6, 0xF7, 0x2A, 0x0C, 0x04};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: ");
  Serial.println(macStr);
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  ///****************
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddress0, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  
  envio.id = ID;
}

void loop() {
  envio.valorFlow=rand();
  envio.filtro=rand();
  envio.rB=rand();
  envio.gB=rand();
  envio.bB=rand();
  envio.rD=rand();
  envio.gD=rand();
  envio.bD=rand();
  
    esp_now_send(  broadcastAddress0, (uint8_t *) &envio, sizeof(datos_envio));
    delay(1000);

}
