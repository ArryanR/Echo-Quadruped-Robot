#include <Servo.h>
#include <math.h>

// Declaring servos
Servo FrontRightOut;
Servo FrontLeftOut;
Servo BackRightOut;
Servo BackLeftOut;
Servo FrontRightHip;
Servo FrontLeftHip;
Servo BackRightHip;
Servo BackLeftHip;
Servo FrontRightKnee;
Servo FrontLeftKnee;
Servo BackRightKnee;
Servo BackLeftKnee;

int HipCenter = 90;

float CycleTime = 2000.0;     // ms
float StepHeight = 20.0;      // degrees
float HipAmplitude = 15.0;    // degrees

// Function prototype
void moveLeg(Servo &hip, Servo &knee, float phase);

void setup() { // attach servos to pins and make them go to Hip Center
  FrontRightOut.attach(1); // basically just a setup for the code to come (read the above comment)
  FrontLeftOut.attach(2);
  BackRightOut.attach(3);
  BackLeftOut.attach(4);

  FrontRightHip.attach(5);
  FrontLeftHip.attach(6);
  BackRightHip.attach(7);
  BackLeftHip.attach(8);

  FrontRightKnee.attach(9);
  FrontLeftKnee.attach(10);
  BackRightKnee.attach(11);
  BackLeftKnee.attach(12);

  FrontRightOut.write(HipCenter);
  FrontLeftOut.write(HipCenter);
  BackRightOut.write(HipCenter);
  BackLeftOut.write(HipCenter);

  FrontRightHip.write(HipCenter);
  FrontLeftHip.write(HipCenter);
  BackRightHip.write(HipCenter);
  BackLeftHip.write(HipCenter);

  FrontRightKnee.write(HipCenter);
  FrontLeftKnee.write(HipCenter);
  BackRightKnee.write(HipCenter);
  BackLeftKnee.write(HipCenter);
}

void loop() {
  unsigned long currentTime = millis(); // millis() now instead of delay()

  float t = fmod(currentTime, CycleTime) / CycleTime; // variable t makes it repeat

  float phaseFR = t;
  float phaseBL = t;
  float phaseFL = fmod(t + 0.5, 1.0);
  float phaseBR = fmod(t + 0.5, 1.0);

  moveLeg(FrontRightHip, FrontRightKnee, phaseFR);
  moveLeg(BackLeftHip, BackLeftKnee, phaseBL);
  moveLeg(FrontLeftHip, FrontLeftKnee, phaseFL);
  moveLeg(BackRightHip, BackRightKnee, phaseBR);
}

void moveLeg(Servo &hip, Servo &knee, float phase) {
  float hipPos;
  float kneePos;

  if (phase < 0.5) { // phases of walking
    hipPos = HipCenter - HipAmplitude * (phase / 0.5);
    kneePos = HipCenter;
  } else {
    float swingPhase = (phase - 0.5) / 0.5;
    hipPos = HipCenter + HipAmplitude * swingPhase;
    kneePos = HipCenter - StepHeight * sin(PI * swingPhase); // sin makes it run smoothly
  }

  hip.write(hipPos);
  knee.write(kneePos);
  /* finished with 90 lines of code!! 
  Who knew this could be made in such a short amount of time!!
  */
}
