#include "DegreeSignLCD.h"

void loadDegreeSign(LiquidCrystal_I2C &lcd) {
	byte degree_sign[] = {
		B00110,
		B01001,
		B01001,
		B00110,
		B00000,
		B00000,
		B00000,
		B00000
	};

	lcd.createChar(DEGREE, degree_sign); // Derece işareti (°)
}
