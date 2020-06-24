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
#include <ESP32_Servo.h>

#define DEBUG 0

#define stepPin_a1 21
#define dirPin_a1 13
#define enaPin_a1 12

#define stepPin_a2 26
#define dirPin_a2 14
#define enaPin_a2 27

#define stepPin_z 32
#define dirPin_z 25
#define enaPin_z 33

#define microSwitch_z 15
#define microSwitch_q1 22
#define microSwitch_q2 2

#define leftServoPin  4
#define rightServoPin 16

const int uStepSize_arms = 32;
const int uStepSize_z = 32;
const int stepsRevolution = 200;
const int transMission_arms = 3;
const double stepsPerDegree = (uStepSize_arms*stepsRevolution*transMission_arms) / 360.0; //make a calculation for this, instead of hardcoding it
const int stepsPerMillimeter = 800;

const int motorSpeedHomingZ = 5000;
const int motorSpeedHomingArms = 1000;


int val_ms_z;
int val_ms_q1;
int val_ms_q2;

int case_var = 0;

#define motorInterfaceType 1

// Define some steppers and the pins the will use
AccelStepper stepper_a1(motorInterfaceType, stepPin_a1, dirPin_a1);
AccelStepper stepper_a2(motorInterfaceType, stepPin_a2, dirPin_a2);
AccelStepper stepper_z(motorInterfaceType, stepPin_z, dirPin_z);

// Define some servos
Servo leftServo;
Servo rightServo;

void setup()
{
  Serial.begin(115200);
  Serial.println(stepsPerDegree);
  //To do: Find out if moveTo works in amount of steps or amount of revolutions (probably steps)
  stepper_a1.setMaxSpeed(3000);
  stepper_a1.setAcceleration(1500);

  stepper_a2.setMaxSpeed(3000);
  stepper_a2.setAcceleration(1500);

  stepper_z.setMaxSpeed(10000);
  stepper_z.setAcceleration(5000);

  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

  pinMode(microSwitch_z,  INPUT_PULLUP);
  pinMode(microSwitch_q1, INPUT_PULLUP);
  pinMode(microSwitch_q2, INPUT_PULLUP);

  pinMode(enaPin_a1, OUTPUT);
  pinMode(enaPin_a2, OUTPUT);
  pinMode(enaPin_z,  OUTPUT);

  digitalWrite(enaPin_a1, HIGH);
  digitalWrite(enaPin_a2, HIGH);
  digitalWrite(enaPin_z,  HIGH);

  openGripper();
  
}

void loop() {
  switch (case_var) {
    case 0: //Homing
      homing();
      break;
    case 1: //Arms straight
      setArmsStraight();
      break;
    case 2:
      mainRoutine();
      break;
    case 3:
      goToPickupLocation();
      break;
    case 4:
      closeGripper();
      case_var = 5;
      break;
    case 5:
      goToPlaceLocation();
      break;
    case 6:
      openGripper();
      stepper_z.moveTo(10 * stepsPerMillimeter);
      case_var = 10;
      break;
    case 10:
      stepper_z.run();
    default:
      break;
  }
}

void goToPlaceLocation() {
  stepper_z.moveTo(10 * stepsPerMillimeter);
  uint32_t timestamp = millis();
  while(millis() - timestamp < 7000) {
    stepper_z.run();
  }
  stepper_a1.moveTo(120 * stepsPerDegree);
  stepper_a2.moveTo(210 * stepsPerDegree);
  stepper_z.moveTo(60 * stepsPerMillimeter);
  timestamp = millis();
  while (millis() - timestamp < 10000) {
    stepper_a1.run();
    stepper_a2.run();
  }
  timestamp = millis();
  while (millis() - timestamp < 7000) {
    stepper_z.run();
  }
  case_var = 6;
}

void goToPickupLocation() {
  stepper_a1.moveTo(60 * stepsPerDegree);
  stepper_a2.moveTo(50 * stepsPerDegree);
  stepper_z.moveTo(60 * stepsPerMillimeter);
  uint32_t timestamp = millis();
  while (millis() - timestamp < 5000) {
    stepper_a1.run();
    stepper_a2.run();
  }
  timestamp = millis();
  while (millis() - timestamp < 7000) {
    stepper_z.run();
  }
  case_var = 4;
}

void openGripper() {
  leftServo.write(150);
  rightServo.write(40);
}

void closeGripper() {
  leftServo.write(180);
  rightServo.write(10);
}

void limitSwitches() {
  val_ms_z = digitalRead(microSwitch_z);
  val_ms_q1 = digitalRead(microSwitch_q1);
  val_ms_q2 = digitalRead(microSwitch_q2);

  if (DEBUG) {
    if (val_ms_z) Serial.println("DEBUG: MU Z: \t1");
    else if (!val_ms_z) Serial.println("DEBUG: MU Z: \t0");

    if (val_ms_q1) Serial.println("DEBUG: MU q1: \t1");
    else if (!val_ms_q1)Serial.println("DEBUG: MU q1: \t0");

    if (val_ms_q2) Serial.println("DEBUG: MU q2: \t1");
    else if (!val_ms_q2)Serial.println("DEBUG: MU q2: \t0\n");
  }
}

void homing() { //Seems to be working, needs to be tested with hardware
  if (DEBUG) Serial.println("DEBUG: Homing");
  
  //Write code for homing each axis at a time
  stepper_z.setSpeed(-motorSpeedHomingZ); //add - for opposite direction (don't forget to connect te 5V)
  stepper_a1.setSpeed(-motorSpeedHomingArms);
  stepper_a2.setSpeed(-motorSpeedHomingArms);

  limitSwitches();

  while (!val_ms_z) {
    stepper_z.runSpeed();
    limitSwitches();
  }
  stepper_z.stop();
  stepper_z.setCurrentPosition(0); //Bovenlimiet opgeven (alles wat naar beneden beweegt is dus , of bovenlimiet hoog opgeven)
  int z_check = 1;
  if (DEBUG) Serial.println("DEBUG: Z-axis switch pressed");

  while (!val_ms_q1) {
    stepper_a1.runSpeed();
    limitSwitches();
  }
  stepper_a1.stop();
  stepper_a1.setCurrentPosition(-95); //Hoek waarin de arm staat bij het indrukken van microswitch invoeren
  int a1_check = 1;
  if (DEBUG) Serial.println("DEBUG: Arm 1 switch pressed");

  uint32_t timestamp = millis();
  while ((millis() - timestamp) < 3000) {
    stepper_a1.moveTo(47.5 * stepsPerDegree);
    stepper_a1.run();
  }

  while (!val_ms_q2) {
    stepper_a2.runSpeed();
    limitSwitches();
  }
  stepper_a2.stop();
  stepper_a2.setCurrentPosition(-180); // Angle with which the arm whilest pressing the microswitch
  int a2_check = 1;
  if (DEBUG) Serial.println("DEBUG: Arm 2 switc pressed");

  if ((z_check) && (a1_check) && (a2_check)) case_var = 1;
}

void setArmsStraight() {
  if (DEBUG) Serial.println("DEBUG: Setting arms straight");
  stepper_a1.moveTo(90 * stepsPerDegree); //Add - for opposite direction dont forget to connect 5V)
  stepper_a2.moveTo(180 * stepsPerDegree);
  stepper_z.moveTo(10 * stepsPerMillimeter);

  uint32_t timestamp = millis();
  while ((millis() - timestamp) < 2000) {
    stepper_a2.run();
  }
  timestamp = millis();
  while ((millis() - timestamp) < 7000) {
    stepper_z.run();
    stepper_a1.run();
    stepper_a2.run();
  }
  case_var = 3;
}

void mainRoutine() {
  if (DEBUG) Serial.println("DEBUG: Main routine");

  digitalWrite(enaPin_a1, LOW);
  digitalWrite(enaPin_a2, LOW);
  digitalWrite(enaPin_z,  LOW);

  while (1) {
    Serial.println("Running main code");
  }
}
