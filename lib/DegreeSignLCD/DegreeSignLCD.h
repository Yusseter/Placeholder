#ifndef DEGREESIGH_LCD_LCD_H
#define DEGREESIGH_LCD_LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define DEGREE 7 // Derece işareti (°)

void loadDegreeSign(LiquidCrystal_I2C &lcd);

#endif
