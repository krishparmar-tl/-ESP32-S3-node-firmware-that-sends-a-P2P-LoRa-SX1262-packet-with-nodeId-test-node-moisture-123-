#include <SPI.h>
#include <LoRa.h>

#define SS   5
#define RST  14
#define DIO0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa NODE");

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }

  LoRa.setSyncWord(0xA5);
  LoRa.setTxPower(17);

  Serial.println("Node ready");
}

void loop() {
  String payload = "{\"nodeId\":\"test-node\",\"moisture\":123}";

  Serial.print("Sending: ");
  Serial.println(payload);

  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();

  delay(5000);
}
