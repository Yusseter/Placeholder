#include <string>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Deneyap_Servo.h>
#include <TurkishLCD.h> // Türkçe karakter desteği için oluşturduğumuz kütüphane
#include <DegreeSignLCD.h> // Derece işareti desteği için oluşturduğumuz kütüphane
/*
Bu kütüphaneler de kullandığımız harfler aşağıdaki karşılıkları ile kullanılır.
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

LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT sensör tanımlamaları
#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// MQ sensör tanımlamaları
#define MQ_DOUT_PIN D0
#define MQ_AOUT_PIN A0

const int GAS_RAW_MIN		= 0;
const int GAS_RAW_MAX		= 4095;
const int GAS_PERCENT_MIN	= 0;
const int GAS_PERCENT_MAX	= 100;

// Buzzer tanımlamaları
#define BUZZER_PIN D12

// Servo tanımlamaları
#define SERVO_PIN D8
Servo servo;

// Yerleştirmeler
String startupMessage = "Sistem Ba\5l\3yor";

void setup() {
	Serial.begin(9600);
	delay(1000);

	Wire.begin(SDA_PIN, SCL_PIN);
	lcd.init();
	lcd.backlight();
	lcd.clear();

	loadTurkishChars(lcd);

	dht.begin();
	pinMode(MQ_DOUT_PIN, INPUT);
	
	pinMode(BUZZER_PIN, OUTPUT);
	digitalWrite(BUZZER_PIN, LOW);

	servo.attach(SERVO_PIN);
	servo.write(0);

	lcd.setCursor(0, 0);
	lcd.print(startupMessage);
	delay(2000);
	lcd.clear();
}

void loop() {
	float humidity		= dht.readHumidity();
	float temperature	= dht.readTemperature();
	int gasStatus		= digitalRead(MQ_DOUT_PIN);
	int gasRaw			= analogRead(MQ_AOUT_PIN);
	int gasLevelPercent	= map(gasRaw, GAS_RAW_MIN, GAS_RAW_MAX, GAS_PERCENT_MIN, GAS_PERCENT_MAX);

	Serial.print("S\3cakl\3k: ");	Serial.print(temperature);	Serial.print("\7C");
	Serial.print(" | Nem: ");		Serial.print(humidity);
	Serial.print(" % | MQ D0: ");	Serial.print(gasStatus);
	Serial.print(" | MQ Ham: ");	Serial.print(gasRaw);
	Serial.print(" | MQ Y\6zde: ");	Serial.print(gasLevelPercent);	Serial.println(" %");

	lcd.clear();
	lcd.setCursor(0, 0);

	if (isnan(humidity) || isnan(temperature)) lcd.print("DHT Hatas\3");
	else {
		lcd.print("S\3cakl\3k: ");	lcd.print(temperature, 1);	lcd.print("\7C ");
		lcd.print("Nem: ");			lcd.print(humidity, 0);		lcd.print("%");
	}

	lcd.setCursor(0, 1);

	if (gasStatus == 0) {
		lcd.print("Gaz Seviyesi: "); lcd.print(gasLevelPercent);
		lcd.print(" ALARM!  ");
		servo.write(180);

		digitalWrite(BUZZER_PIN, HIGH);
	}
	else {
		lcd.print("Gaz:Normal %"); lcd.print(gasLevelPercent);

		digitalWrite(BUZZER_PIN, LOW);
	}

	delay(2000);
}
