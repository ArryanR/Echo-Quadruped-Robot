#include <Servo.h>
#include <math.h>

// NAME SERVOS
Servo FRHip, FRKnee;
Servo FLHip, FLKnee;
Servo BRHip, BRKnee;
Servo BLHip, BLKnee;

// The center position for servos ( usually 90 degrees)
const int HipCenter = 90;
const int KneeCenter = 80;

// Geometry setup
const float L1 = 40; // Upper leg length (this is really rounded)
const float L2 = 86; // Lower leg length

// Gait parameters
const unsigned long CycleTime = 2000; // Time for one full step cycle in ms
const float StepLength = 60.0;        // Horizontal travel
const float StepLift = 40.0;          // Vertical lift height
const float StandHeight = 80.0;     // Total neutral height (must be less than than L1+L2)

void legIK(float x, float z, float &hipDeg, float &kneeDeg) {
  // Distance from hip to foot
  float r = sqrt(x * x + z * z);

  // Law of Cosines for Knee Angle
  float cosKnee = (r * r - L1 * L1 - L2 * L2) / (2.0 * L1 * L2);

  // Constrained to avoid math errors
  cosKnee = constrain(cosKnee, -1.0, 1.0);

  float kneeRad = acos(cosKnee);

  // Angle of the vector (x, z)
  float alpha = atan2(z, x);
  
  // Interior angle between L1 and r
  float beta = atan2(L2 * sin(kneeRad), L1 + L2 * cos(kneeRad));

  float hipRad = alpha + beta; 

  hipDeg = hipRad * 180.0 / PI;
  kneeDeg = -kneeRad * 180.0 / PI;
  
  // the minus tells the computer that it is inverse legs as 2 legs are coded together
}

// Calculates leg position based on gait phase (0.0 to 1.0)
void moveLeg(Servo &hip, Servo &knee, float phase, bool invertX = false) {
  float xHip, zHip;
  float xKnee, zKnee;

  // Hip position
  if (phase < 0.5) {
    float p = phase / 0.5;
    xHip = StepLength * (0.5 - p);
    zHip = StandHeight;
  } else {
    float s = (phase - 0.5) / 0.5;
    xHip = StepLength * (s - 0.5);
    zHip = StandHeight + StepLift * sin(PI * s);
  }

  // Knee Position
  // 20ms / 2000ms = 0.01 phase shift
  float kneePhase = phase - 0.01; 
  if (kneePhase < 0) kneePhase += 1.0;

  if (kneePhase < 0.5) {
    float p = kneePhase / 0.5;
    xKnee = StepLength * (0.5 - p);
    zKnee = StandHeight;
  } else {
    float s = (kneePhase - 0.5) / 0.5;
    xKnee = StepLength * (s - 0.5);
    zKnee = StandHeight + StepLift * sin(PI * s);
  }

  if (invertX) {
    xHip = -xHip;
    xKnee = -xKnee;
  }

  float hipAngle, kneeAngle_trash; // trash angles are temporary but necessary but if I wanted to make this better then I'd definitely initialise functions better
  float hipAngle_trash, kneeAngle;

  // Calculate separate targets
  legIK(xHip, zHip, hipAngle, kneeAngle_trash);
  legIK(xKnee, zKnee, hipAngle_trash, kneeAngle);

  // Update servos
  hip.write(constrain(HipCenter + (int)hipAngle, 0, 180));
  knee.write(constrain(KneeCenter + (int)kneeAngle, 0, 180));
}

void setup() {
  Serial.begin(115200); // initialise communication

  // Calculate neutral position
  float startHipAngle, startKneeAngle;
  legIK(0, StandHeight, startHipAngle, startKneeAngle);
  
  int initHipPos = constrain(HipCenter + (int)startHipAngle, 0, 180);
  int initKneePos = constrain(KneeCenter + (int)startKneeAngle, 0, 180);

  // Write positions before attaching so they don't snap or jitter
  FRHip.write(initHipPos);
  FLHip.write(initHipPos);
  BRHip.write(initHipPos);
  BLHip.write(initHipPos);

  FRKnee.write(initKneePos);
  FLKnee.write(initKneePos);
  BRKnee.write(initKneePos);
  BLKnee.write(initKneePos);

  // Attach Hips first
  FRHip.attach(2);
  FLHip.attach(4);
  BRHip.attach(6);
  BLHip.attach(8);

  delay(500); // Wait for hips to initialize

  // Then Knees
  FRKnee.attach(3);
  FLKnee.attach(5);
  BRKnee.attach(7);
  BLKnee.attach(9);
}

void loop() {
  // Get global cycle time (0.0 to 1.0) note that this is coded in phases
  unsigned long currentTime = millis();
  float t = (float)(currentTime % CycleTime) / (float)CycleTime;

  // Diagonal pairs for a Trot Gait
  float phaseFR = t;
  float phaseBL = t;
  
  float phaseFL = t + 0.5;
  if (phaseFL >= 1.0) phaseFL -= 1.0;

  float phaseBR = t + 0.5;
  if (phaseBR >= 1.0) phaseBR -= 1.0;

  // Execute movements for all 4 legs
  moveLeg(FRHip, FRKnee, phaseFR);
  moveLeg(BLHip, BLKnee, phaseBL);
  moveLeg(FLHip, FLKnee, phaseFL);
  moveLeg(BRHip, BRKnee, phaseBR);

  // delay and repeat!!
  delay(10);
}
