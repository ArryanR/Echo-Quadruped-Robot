
#include <Servo.h>

Servo kneeFL;
Servo kneeFR;
Servo kneeBL;
Servo kneeBR;

int pos = 0;

void setup() {
  kneeFL.attach(9);
  kneeFR.attach(10);
  kneeBL.attach(11);
  kneeBR.attach(12);
}

void loop() {

  for (pos = 0; pos <= 30; pos++) {
    kneeFL.write(pos);
    kneeBR.write(pos);
    delay(15);
  }

  for (pos 30; pos >= 0; pos--) {
    kneeFL.write(pos);
    kneeBR.write(pos);
    delay(15);
  }

  delay(300);

  for (pos = 0; pos <= 30; pos++) {
    kneeFR.write(pos);
    kneeBL.write(pos);
    delay(15);
  }

  for (pos = 30; pos >= 0; pos--) {
    kneeFR.write(pos);
    kneeBL.write(pos);
    delay(15);
  }

  delay(300);
}
