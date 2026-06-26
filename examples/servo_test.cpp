#include <Deneyap_Servo.h>

Servo servo360;

#define SERVO_PIN D8

void setup() {
  servo360.attach(SERVO_PIN);

  // Başlangıçta dur
  servo360.write(90);
  delay(2000);
}

void loop() {
  // Bir yöne dön
  servo360.write(180);
  delay(3000);

  // Dur
  servo360.write(90);
  delay(2000);

  // Diğer yöne dön
  servo360.write(0);
  delay(3000);

  // Dur
  servo360.write(90);
  delay(2000);
}
