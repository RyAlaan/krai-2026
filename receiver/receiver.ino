#include <esp_now.h>
#include <WiFi.h>

// Struktur data yang diterima (harus sama dengan sender)
typedef struct struct_message {
  int id;
  float value;
} struct_message;

struct_message incomingData;

// Callback saat data diterima
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  char macStr[18];
  snprintf(macStr, sizeof(macStr),
           "%02X:%02X:%02X:%02X:%02X:%02X",
           info->src_addr[0], info->src_addr[1], info->src_addr[2],
           info->src_addr[3], info->src_addr[4], info->src_addr[5]);

  Serial.print("Data dari: ");
  Serial.print(macStr);
  Serial.print(" | ID: ");
  Serial.print(incomingData.id);
  Serial.print(" | Value: ");
  Serial.println(incomingData.value);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Channel: ");
  Serial.println(WiFi.channel()); 
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal inisialisasi ESP-NOW");
    return;
  }

  // Daftarkan callback penerima
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}