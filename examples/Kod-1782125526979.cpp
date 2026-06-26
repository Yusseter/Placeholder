#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD ayarlari
#define SDA_PIN D14
#define SCL_PIN D15
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// DHT11 ayarlari
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ gaz sensoru dijital cikis
#define MQ_DOUT_PIN D0

void setup() {
  Serial.begin(9600);
  delay(1000);

  // LCD baslat
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Sensorleri baslat
  dht.begin();
  pinMode(MQ_DOUT_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Sistem Basliyor");
  lcd.setCursor(0, 1);
  lcd.print("DHT + MQ + LCD");
  delay(2000);
  lcd.clear();
}

void loop() {
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  int gazDurumu = digitalRead(MQ_DOUT_PIN);

  Serial.print("Sicaklik: ");
  Serial.print(sicaklik);
  Serial.print(" C | Nem: ");
  Serial.print(nem);
  Serial.print(" % | MQ D0: ");
  Serial.println(gazDurumu);

  lcd.clear();

  // 1. satir: sicaklik ve nem
  lcd.setCursor(0, 0);

  if (isnan(nem) || isnan(sicaklik)) {
    lcd.print("DHT Hatasi");
  } else {
    lcd.print("T:");
    lcd.print(sicaklik, 1);
    lcd.print("C ");

    lcd.print("N:");
    lcd.print(nem, 0);
    lcd.print("%");
  }

  // 2. satir: gaz durumu
  lcd.setCursor(0, 1);

  // Sende daha once MQ D0 normalde 1 veriyordu.
  // Bu yuzden 1 = normal, 0 = gaz algilandi kabul ediyoruz.
  if (gazDurumu == 1) {
    lcd.print("Gaz: NORMAL");
  } else {
    lcd.print("Gaz: ALGILANDI");
  }

  delay(2000);
}