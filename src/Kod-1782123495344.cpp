#include <Arduino.h>
#include <Wire.h>

#define SDA_PIN D14
#define SCL_PIN D15

void scanI2C() {
  Serial.println("--------------------");
  Serial.println("I2C taraniyor...");

  byte count = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C cihaz bulundu: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      count++;
    }
  }

  if (count == 0) {
    Serial.println("I2C cihaz bulunamadi.");
  }

  Serial.println("Tarama bitti.");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Surekli I2C scanner basladi.");
}

void loop() {
  scanI2C();
  delay(2000);
}