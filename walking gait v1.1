#include <Servo.h>

// hip servos
Servo hipFL;
Servo hipFR;
Servo hipBL;
Servo hipBR;

// knee servos (two for leg because of design)
Servo kneeFL_A;
Servo kneeFL_B;

Servo kneeFR_A;
Servo kneeFR_B;

Servo kneeBL_A;
Servo kneeBL_B;

Servo kneeBR_A;
Servo kneeBR_B;

// tuning values
int hipCenter  = 40;
int hipForward = 70;
int hipBack    = 50;

int kneeUp   = 30;
int kneeDown = 0;

// knee direction multipliers
// change these if a knee bends the wrong way
int kneeFL_dir = 1;
int kneeFR_dir = 1;
int kneeBL_dir = 1;
int kneeBR_dir = 1;

int pos;

// what pins go with what motors?

void setup() {

  // hips
  hipFL.attach(2);
  hipFR.attach(3);
  hipBL.attach(4);
  hipBR.attach(5);

  // knees
  kneeFL_A.attach(6);
  kneeFL_B.attach(7);

  kneeFR_A.attach(8);
  kneeFR_B.attach(9);

  kneeBL_A.attach(10);
  kneeBL_B.attach(11);

  kneeBR_A.attach(12);
  kneeBR_B.attach(13);

  // neutral position
  
  hipFL.write(hipCenter);
  hipFR.write(hipCenter);
  hipBL.write(hipCenter);
  hipBR.write(hipCenter);

  // knees start down
  kneeFL_A.write(kneeDown);
  kneeFL_B.write(180 - kneeDown);

  kneeFR_A.write(kneeDown);
  kneeFR_B.write(180 - kneeDown);

  kneeBL_A.write(kneeDown);
  kneeBL_B.write(180 - kneeDown);

  kneeBR_A.write(kneeDown);
  kneeBR_B.write(180 - kneeDown);
}

void loop() {

  // fl + br (front left + back right)

  // smooth hip movement 
  for (int h = hipCenter; h <= hipForward; h++) {
    hipFL.write(h);
    hipBR.write(hipCenter - (h - hipCenter)); // mirrored
    delay(10);
  }

  // lift knees
  for (pos = kneeDown; pos <= kneeUp; pos++) {
    kneeFL_A.write(pos);
    kneeFL_B.write(180 - pos);
    kneeBR_A.write(pos);
    kneeBR_B.write(180 - pos);
    delay(15);
  }

  // lower knees
  for (pos = kneeUp; pos >= kneeDown; pos--) {
    kneeFL_A.write(pos);
    kneeFL_B.write(180 - pos);
    kneeBR_A.write(pos);
    kneeBR_B.write(180 - pos);
    delay(15);
  }

  // reset hips
  for (int h = hipForward; h >= hipCenter; h--) {
    hipFL.write(h);
    hipBR.write(hipCenter - (h - hipCenter));
    delay(10);
  }
  delay(120);
  
  // fr + bl (front right + back left)

  // smooth hip movement 
  for (int h = hipCenter; h <= hipForward; h++) {
    hipFR.write(h);
    hipBL.write(hipCenter - (h - hipCenter)); // mirrored
    delay(10);
  }

  // lift knees
  for (pos = kneeDown; pos <= kneeUp; pos++) {
    kneeFR_A.write(pos);
    kneeFR_B.write(180 - pos);
    kneeBL_A.write(pos);
    kneeBL_B.write(180 - pos);
    delay(15);
  }

  // lower knees
  for (pos = kneeUp; pos >= kneeDown; pos--) {
    kneeFR_A.write(pos);
    kneeFR_B.write(180 - pos);
    kneeBL_A.write(pos);
    kneeBL_B.write(180 - pos);
    delay(15);
  }

  // reset hips
  for (int h = hipForward; h >= hipCenter; h--) {
    hipFR.write(h);
    hipBL.write(hipCenter - (h - hipCenter));
    delay(10);
  }
  delay(120);

  // FINISHED!!

}




