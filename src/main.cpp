#include <string>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Deneyap_Servo.h>
#include <TurkishLCD.h> // Türkçe karakter desteği için oluşturduğumuz kütüphane.
#include <DegreeSignLCD.h> // Derece işareti desteği için oluşturduğumuz kütüphane.
/*
Bu kütüphaneler ile kullandığımız yeni karakterler aşağıdaki karşılıkları ile kullanılır.
ç için \1,
ğ için \2,
ı için \3,
ö için \4,
ş için \5,
ü için \6,
° için \7
*/

// LCD tanımlamaları
#define SDA_PIN D14
#define SCL_PIN D15

LiquidCrystal_I2C lcd(0x27, 20, 4);

// DHT sensör tanımlamaları
#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// MQ sensör tanımlamaları
#define MQ_DOUT_PIN D0
#define MQ_AOUT_PIN A0

const int GAS_RAW_MIN = 0;
const int GAS_RAW_MAX = 4095;
const int GAS_PERCENT_MIN = 0;
const int GAS_PERCENT_MAX = 100;

// Buzzer tanımlamaları
#define BUZZER_PIN D12

// Servo tanımlamaları
#define SERVO_PIN D8

Servo servo;

void clearLcdLine(int line) {
	lcd.setCursor(0, line);

	for (int i = 0; i < 20; i++) {
		lcd.print(" ");
	}

	lcd.setCursor(0, line);
}

void showStartupAnimation() {
	for (int repeat = 0; repeat < 2; repeat++) {
		for (int dotCount = 0; dotCount <= 3; dotCount++) {
			clearLcdLine(0);

			lcd.print("Sistem Ba\5l\3yor");

			for (int i = 0; i < dotCount; i++) {
				lcd.print(".");
			}

			delay(500);
		}
	}

	lcd.clear();
}

void setup() {
	Serial.begin(115200);
	delay(1000);

	Wire.begin(SDA_PIN, SCL_PIN);
	lcd.init();
	lcd.backlight();
	lcd.clear();

	loadTurkishChars(lcd);
	loadDegreeSign(lcd);

	dht.begin();
	pinMode(MQ_DOUT_PIN, INPUT);
	
	pinMode(BUZZER_PIN, OUTPUT);
	digitalWrite(BUZZER_PIN, LOW);

	servo.attach(SERVO_PIN);
	servo.write(0);

	showStartupAnimation();
}

void loop() {
	float humidity = dht.readHumidity();
	float temperature = dht.readTemperature();
	int gasStatus = digitalRead(MQ_DOUT_PIN);
	int gasRaw = analogRead(MQ_AOUT_PIN);
	int gasPercent = map(gasRaw, GAS_RAW_MIN, GAS_RAW_MAX, GAS_PERCENT_MIN, GAS_PERCENT_MAX);

	if (isnan(temperature)) Serial.println("Sıcaklık değeri geçersiz!");
	else Serial.print("Sıcaklık: "); Serial.print(temperature); Serial.println("°C");

	if (isnan(humidity)) Serial.println("Nem değeri geçersiz!");
	else Serial.print("Nem: "); Serial.println(humidity);

	if (isnan(gasStatus)) Serial.println("MQ değeri geçersiz!");
	else Serial.print("MQ değeri: "); Serial.println(gasStatus);

	if (isnan(gasRaw)) Serial.println("MQ ham değeri geçersiz!");
	else Serial.print("MQ Ham: "); Serial.println(gasRaw);

	if (isnan(gasPercent)) Serial.println("MQ yüzde değeri geçersiz!");
	else Serial.print("MQ Yüzde: %"); Serial.println(gasPercent);

	lcd.clear();
	lcd.setCursor(0, 0);

	if (isnan(humidity) || isnan(temperature)) lcd.print("DHT Hatas\3!");
	else {
		lcd.print("S\3cakl\3k: "); lcd.print(temperature, 1); lcd.print("\7C");
		lcd.setCursor(0, 1);
		lcd.print("Nem: %"); lcd.print(humidity, 0);
	}

	lcd.setCursor(0, 2);

	if (gasStatus == 0) {
		lcd.print("Gaz Seviyesi: %"); lcd.print(gasPercent);
		lcd.setCursor(0, 3);
		lcd.print("ALARM!");
		servo.write(180);

		digitalWrite(BUZZER_PIN, HIGH);
	}
	else {
		lcd.print("Gaz Seviyesi: %"); lcd.print(gasPercent);
		lcd.setCursor(0, 3);
		lcd.print("Normal");
		servo.write(0);

		digitalWrite(BUZZER_PIN, LOW);
	}

	delay(2000);
}
