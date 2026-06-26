#include "TurkishLCD.h"

void loadTurkishChars(LiquidCrystal_I2C &lcd) {
	byte latin_small_letter_u_with_diaeresis[] = {
		B01010,
		B00000,
		B10001,
		B10001,
		B10001,
		B10011,
		B01101,
		B00000
	};

	byte latin_small_letter_c_with_cedilla[] = {
		B00000,
		B00000,
		B01110,
		B10000,
		B10000,
		B10001,
		B01110,
		B00100
	};

	byte latin_small_letter_g_with_breve[] = {
		B01110,
		B00000,
		B01111,
		B10001,
		B10001,
		B01111,
		B00001,
		B01110
	};

	byte latin_small_letter_dotless_i[] = {
		B00000,
		B00000,
		B01100,
		B00100,
		B00100,
		B00100,
		B01110,
		B00000
	};

	byte latin_small_letter_o_with_diaeresis[] = {
		B01010,
		B00000,
		B01110,
		B10001,
		B10001,
		B10001,
		B01110,
		B00000
	};

	byte latin_small_letter_s_with_cedilla[] = {
		B00000,
		B00000,
		B01110,
		B10000,
		B01110,
		B00001,
		B11110,
		B00100
	};

/*
	byte latin_capital_letter_c_with_cedilla[] = {
		B01110,
		B10001,
		B10000,
		B10000,
		B10000,
		B10001,
		B01110,
		B00100
	};

	byte latin_capital_letter_g_with_breve[] = {
		B01110,
		B00000,
		B01110,
		B10000,
		B10111,
		B10001,
		B01110,
		B00000
	};

	byte latin_capital_letter_i_with_dot_above[] = {
		B00100,
		B00000,
		B01110,
		B00100,
		B00100,
		B00100,
		B01110,
		B00000
	};

	byte latin_capital_letter_o_with_diaeresis[] = {
		B01010,
		B00000,
		B01110,
		B10001,
		B10001,
		B10001,
		B01110,
		B00000
	};

	byte latin_capital_letter_s_with_cedilla[] = {
		B01111,
		B10000,
		B10000,
		B01110,
		B00001,
		B00001,
		B11110,
		B00100
	};

	byte latin_capital_letter_u_with_diaeresis[] = {
		B01010,
		B00000,
		B10001,
		B10001,
		B10001,
		B10001,
		B01110,
		B00000
	};
*/

	lcd.createChar(TR_C, latin_small_letter_c_with_cedilla);	// ç
	lcd.createChar(TR_G, latin_small_letter_g_with_breve);		// ğ
	lcd.createChar(TR_I, latin_small_letter_dotless_i);			// ı
	lcd.createChar(TR_O, latin_small_letter_o_with_diaeresis);	// ö
	lcd.createChar(TR_S, latin_small_letter_s_with_cedilla);	// ş
	lcd.createChar(TR_U, latin_small_letter_u_with_diaeresis);	// ü
}
