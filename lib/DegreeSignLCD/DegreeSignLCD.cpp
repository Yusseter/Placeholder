#include "DegreeSignLCD.h"

void loadDegreeSign(LiquidCrystal_I2C &lcd) {
	byte degree_sign[] = {
		B01100,
		B10010,
		B10010,
		B01100,
		B00000,
		B00000,
		B00000,
		B00000
	};

	lcd.createChar(DEGREE, degree_sign); // Derece işareti (°)
}
