#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// ===== Wi-Fi credentials =====
const char* ssid     = "Krish";
const char* password = "        ";

// ===== SX1278 pins (ESP32-S3) =====
#define SS    10
#define RST   9
#define DIO0  4

// SPI pins (ESP32-S3)
#define SCK   12
#define MISO  13
#define MOSI  11

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa + WiFi Gateway");

  // ---- SPI init (mandatory for ESP32-S3) ----
  SPI.begin(SCK, MISO, MOSI, SS);

  // ---- LoRa init ----
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }

  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa ready");

  // ---- Wi-Fi init ----
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {

    String payload = "";
    while (LoRa.available()) {
      payload += (char)LoRa.read();
    }

    Serial.print("Received: ");
    Serial.println(payload);

    // ---- HTTPS POST ----
    WiFiClientSecure client;
    client.setInsecure();   // OK for httpbin test

    HTTPClient https;
    https.begin(client, "https://httpbin.org/post");
    https.addHeader("Content-Type", "application/json");

    int httpCode = https.POST(payload);

    Serial.print("HTTP Code: ");
    Serial.println(httpCode);

    if (httpCode > 0) {
      String response = https.getString();
      Serial.println("Response:");
      Serial.println(response);
    }

    https.end();
  }
}
