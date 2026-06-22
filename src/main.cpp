#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN D14
#define SCL_PIN D15

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
    delay(500);

    Wire.begin(SDA_PIN, SCL_PIN);

    lcd.init();
    lcd.backlight();
    lcd.clear();

    delay(100);

    lcd.setCursor(0, 0);
    lcd.print("PlatformIO");

    lcd.setCursor(0, 1);
    lcd.print("LCD OK 3V3");
}

void loop() {
}
