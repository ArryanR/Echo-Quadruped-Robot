#include <Servo.h>
#include <math.h>

// NAME SERVOS
Servo FRHip, FRKnee;
Servo FLHip, FLKnee;
Servo BRHip, BRKnee;
Servo BLHip, BLKnee;

// The center position for my servos ( 90 degrees)
const int HipCenter = 90;
const int KneeCenter = 90;

// leg height
const float L1 = 103.286; // Upper leg length
const float L2 = 125.789; // Lower leg length

// parameters
const unsigned long CycleTime = 2000; // Time for one full step cycle in ms
const float StepLength = 60.0;        // Horizontal travel
const float StepLift = 40.0;          // Vertical lift height
const float StandHeight = -160.0;     // Total neutral height (must be < L1+L2)


void legIK(float x, float z, float &hipDeg, float &kneeDeg) {
  // Distance from hip to foot
  float r = sqrt(x * x + z * z);

  // Law of Cosines for the Knee Angle
  float cosKnee = (r * r - L1 * L1 - L2 * L2) / (2.0 * L1 * L2);

  cosKnee = constrain(cosKnee, -1.0, 1.0);

  float kneeRad = acos(cosKnee);

  // Angle of the vector (x, z)
  float alpha = atan2(z, x);
  // Interior angle between L1 and r
  float beta = atan2(L2 * sin(kneeRad), L1 + L2 * cos(kneeRad));

  float hipRad = alpha + beta; 

  hipDeg = hipRad * 180.0 / PI;
  kneeDeg = kneeRad * 180.0 / PI;
}

/**
 * Calculates leg position based on gait phase (0.0 to 1.0)
 */
void moveLeg(Servo &hip, Servo &knee, float phase, bool invertX = false) {
  float x, z;

  // Trot Gait logic: 0.0-0.5 is Stance (ground), 0.5-1.0 is Swing (air)
  if (phase < 0.5) {
    // Stance phase: move backward linearly
    float p = phase / 0.5;
    x = StepLength * (0.5 - p);
    z = StandHeight;
  } else {
    // Swing phase: move forward in an arc
    float s = (phase - 0.5) / 0.5;
    x = StepLength * (s - 0.5);
    z = StandHeight + StepLift * sin(PI * s);
  }

  if (invertX) x = -x;

  float hipA, kneeA;
  legIK(x, z, hipA, kneeA);
  
  hip.write(constrain(HipCenter + (int)hipA, 0, 180));
  knee.write(constrain(KneeCenter + (int)kneeA, 0, 180));
}

void setup() {
  Serial.begin(115200);

  FRHip.attach(2);
  FRKnee.attach(3);
  FLHip.attach(4);
  FLKnee.attach(5);
  BRHip.attach(6);
  BRKnee.attach(7);
  BLHip.attach(8);
  BLKnee.attach(9);

}

void loop() {
  // Get global cycle time (0.0 to 1.0) (phases basically)
  // Using float division to ensure precision in the sim loop
  unsigned long currentTime = millis();
  float t = (float)(currentTime % CycleTime) / (float)CycleTime;

  // trot gait and phases
  float phaseFR = t;
  float phaseBL = t;

  float phaseFL = t + 0.5;
  if (phaseFL >= 1.0) phaseFL -= 1.0;

  float phaseBR = t + 0.5;
  if (phaseBR >= 1.0) phaseBR -= 1.0;

  // do movements for all 4 legs
  moveLeg(FRHip, FRKnee, phaseFR);
  moveLeg(BLHip, BLKnee, phaseBL);
  moveLeg(FLHip, FLKnee, phaseFL);
  moveLeg(BRHip, BRKnee, phaseBR);

  // delay step
  delay(20);
}

// lots of preparation for a small loop haha
// wires are kind of all over the place in my sim though
