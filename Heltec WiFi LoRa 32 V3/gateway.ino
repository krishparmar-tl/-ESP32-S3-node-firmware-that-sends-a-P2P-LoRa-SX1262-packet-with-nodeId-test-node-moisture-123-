#include <SPI.h>
#include <RadioLib.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// ----------------------------------------------------
// Wi-Fi Credentials
// ----------------------------------------------------
const char* ssid     = "Krish";
const char* password = "        ";

// ----------------------------------------------------
// SX1262 Pin Mapping (Heltec WiFi LoRa 32 V3)
// ----------------------------------------------------
#define LORA_SCK   9
#define LORA_MISO  11
#define LORA_MOSI  10
#define LORA_CS    8
#define LORA_RST   12
#define LORA_BUSY  13
#define LORA_DIO1  14

// SX1262 radio instance
SX1262 lora = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Heltec V3 LoRa HTTPS Gateway");

  // SPI init
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  // LoRa init
  int state = lora.begin(
    433.0,
    125.0,
    7,
    5,
    0xA5,
    17,
    8
  );

  if (state != RADIOLIB_ERR_NONE) {
    Serial.println("LoRa init failed");
    while (true);
  }

  Serial.println("LoRa ready");

  // Wi-Fi init
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {
  String payload;

  int state = lora.receive(payload);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.print("Received: ");
    Serial.println(payload);

    // HTTPS POST
    WiFiClientSecure client;
    client.setInsecure();  // OK for testing (httpbin/webhook)

    HTTPClient https;
    https.begin(client, "https://httpbin.org/post");
    https.addHeader("Content-Type", "application/json");

    int httpCode = https.POST(payload);
    Serial.print("HTTP Code: ");
    Serial.println(httpCode);

    if (httpCode > 0) {
      Serial.println("Response:");
      Serial.println(https.getString());
    }

    https.end();
  }
}
