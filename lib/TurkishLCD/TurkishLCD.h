#ifndef TURKISH_LCD_H
#define TURKISH_LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define TR_C 1 // ç
#define TR_G 2 // ğ
#define TR_I 3 // ı
#define TR_O 4 // ö
#define TR_S 5 // ş
#define TR_U 6 // ü
/*
#define TR_C 7 // Ç
#define TR_G 8 // Ğ
#define TR_I 9 // İ
#define TR_O 10 // Ö
#define TR_S 11 // Ş
#define TR_U 12 // Ü
*/

void loadTurkishChars(LiquidCrystal_I2C &lcd);

#endif
