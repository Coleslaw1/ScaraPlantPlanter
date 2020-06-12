
/*
  AccelStepper library: http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a73bdecf1273d98d8c5fbcb764cabeea5
  TB6600 Stepper controller: https://www.makerguides.com/tb6600-stepper-motor-driver-arduino-tutorial/

  To do:
  - Test main functioning of Accelstepper code
  - Make a conversion between angles and steps (1 degree = 53 steps)
  - Mapping all locations and determine the path (Python)
  - Include servo code (Already on Github)
  - Position logging to FRAM|API (Only if time left)

*/

#include <AccelStepper.h>

#define DEBUG 0

#define stepPin_a1 26
#define dirPin_a1 27

#define stepPin_a2 32
#define dirPin_a2 33

#define stepPin_z 21
#define dirPin_z 12

#define microSwitch_z 22
#define microSwitch_q1 2
#define microSwitch_q2 15


const int uStepSize_arms = 32;
const int uStepSize_z = 32;
const int stepsRevolution = 200;
const int transMission_arms = 3;
const int stepsPerDegree = 53; //make a calculation for this, instead of hardcoding it
const int stepsPerMillimeter = 800;

int val_ms_z;
int val_ms_q1;
int val_ms_q2;

int case_var = 0;

// Define some steppers and the pins the will use
AccelStepper stepper_a1(AccelStepper::DRIVER, stepPin_a1, dirPin_a1);
AccelStepper stepper_a2(AccelStepper::DRIVER, stepPin_a2, dirPin_a2);
AccelStepper stepper_z(AccelStepper::DRIVER, stepPin_z, dirPin_z);

void setup()
{
  Serial.begin(115200);
  //To do: Find out if moveTo works in amount of steps or amount of revolutions (probably steps)
  stepper_a1.setMaxSpeed(100.0);
  stepper_a1.setAcceleration(50.0);

  stepper_a2.setMaxSpeed(100.0);
  stepper_a2.setAcceleration(50.0);

  stepper_z.setMaxSpeed(100.0);
  stepper_z.setAcceleration(50.0);

  pinMode(microSwitch_z, INPUT);
  pinMode(microSwitch_q1, INPUT);
  pinMode(microSwitch_q2, INPUT);
  Serial.println(stepsPerDegree);
}

void loop()
{
  switch (case_var) {
    case 0: //Homing
      homing();
      break;
    case 1: //Arms straight
      setArmsStraight();
      break;
    case 2:
      Serial.println("It's time for some action now");
      break;
  }
}

void limitSwitches() {
  val_ms_z = digitalRead(microSwitch_z);
  val_ms_q1 = digitalRead(microSwitch_q1);
  val_ms_q2 = digitalRead(microSwitch_q2);

  if (DEBUG) {
    if (val_ms_z == 1) Serial.println("MU Z: \t1");
    else if (val_ms_z == 0) Serial.println("MU Z: \t0");

    if (val_ms_q1 == 1) Serial.println("MU q1: \t1");
    else if (val_ms_q1 == 0)Serial.println("MU q1: \t0");

    if (val_ms_q2 == 1) Serial.println("MU q2: \t1");
    else if (val_ms_q2 == 0)Serial.println("MU q2: \t0\n");
  }
}

void homing() { //Seems to be working, needs to be tested with hardware
  //Write code for homing each axis at a time
  Serial.println("Waiting for limit switches");
  while (!val_ms_z) {
    stepper_z.runSpeed();
    limitSwitches();
  }
  stepper_z.stop();
  stepper_z.setCurrentPosition(0);
  int z_check = 1;

  while (!val_ms_q1) {
    stepper_a1.runSpeed();
    limitSwitches();
  }
  stepper_a1.stop();
  stepper_a1.setCurrentPosition(-90);
  int a1_check = 1;

  while (!val_ms_q2) {
    stepper_a2.runSpeed();
    limitSwitches();
  }
  stepper_a2.stop();
  stepper_a2.setCurrentPosition(0);
  int a2_check = 1;

  if ((z_check) && (a1_check) && (a2_check)) case_var = 1;
}

void setArmsStraight(){
  stepper_a1.moveTo(90);
  stepper_a2.moveTo(90);
  stepper_a1.run();
  stepper_a2.run();
  Serial.println("Running");
}
