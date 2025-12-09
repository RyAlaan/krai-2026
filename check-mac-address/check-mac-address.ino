#include <ESP32_NOW.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
}

void loop() { 
  Serial.print("mac addresnya: ");
  Serial.println(WiFi.macAddress());

  delay(100);
}
