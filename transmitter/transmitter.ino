#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMac[] = {0x68, 0x25, 0xDD, 0x49, 0x16, 0x94};

typedef struct struct_message {
  int id;
  float value;
} struct_message;

struct_message myPacket;

void setup () {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin();

  // initialize esp_now
  if (esp_now_init() != ESP_OK) {
    Serial.println("unable to initialize ESP_NOW");
    return;
  }

  // add peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // add peer result
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Unable to add peer");
    return;
  }
}

void loop() {
  // set data
  myPacket.id  = 1;
  myPacket.value = random(0, 100);

  // send data
  esp_err_t result = esp_now_send(receiverMac, (uint8_t *) &myPacket, sizeof(myPacket));

  if (result == ESP_OK) {
    Serial.println("Status: data sended successfully");
  } else {
    Serial.print("Status: ");
    Serial.println(result);
  }

  // loop every
  delay(5000);
}








