#include <SPI.h>
#include <RadioLib.h>

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

  Serial.println("Heltec V3 LoRa NODE");

  // SPI init
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  // LoRa init (P2P)
  int state = lora.begin(
    433.0,   // Frequency (MHz)
    125.0,   // Bandwidth (kHz)
    7,       // Spreading Factor
    5,       // Coding Rate (4/5)
    0xA5,    // Sync Word
    17,      // TX Power (dBm)
    8        // Preamble length
  );

  if (state != RADIOLIB_ERR_NONE) {
    Serial.println("LoRa init failed");
    while (true);
  }

  Serial.println("Node ready");
}

void loop() {
  String payload = "{\"nodeId\":\"test-node\",\"moisture\":123}";

  Serial.print("Sending: ");
  Serial.println(payload);

  int state = lora.transmit(payload);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("TX OK");
  } else {
    Serial.print("TX failed: ");
    Serial.println(state);
  }

  delay(5000);
}
