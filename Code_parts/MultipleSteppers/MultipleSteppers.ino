
/* 
AccelStepper library: http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a73bdecf1273d98d8c5fbcb764cabeea5
TB6600 Stepper controller: https://www.makerguides.com/tb6600-stepper-motor-driver-arduino-tutorial/
 
 To do:
 - Test main functioning of Accelstepper code 
 - Make a conversion between angles and steps (1 degree = 53 steps)
 - Find out how the setCurrentPosition() function works (doesn't work in current version)
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


const int uStepSize_a1 = 32;
const int uStepSize_a2 = 32;
const int uStepSize_z = 32;
const int stepsRevolution = 200;
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

    Serial.println("Done setting up");
}

void loop()
{
    switch(case_var){
      case 0: //Homing
        homing();
        break;
      case 1: //Zeroing
        setZero();
        break;
      case 2: //Main pick and place code
        Serial.println("Running main code now");
    }
}

void limitSwitches(){
  val_ms_z = digitalRead(microSwitch_z);
  val_ms_q1 = digitalRead(microSwitch_q1);
  val_ms_q2 = digitalRead(microSwitch_q2);

  if(DEBUG){
    if(val_ms_z == 1) Serial.println("MU Z: \t1");
    else if(val_ms_z == 0) Serial.println("MU Z: \t0");
  
    if(val_ms_q1 == 1) Serial.println("MU q1: \t1");
    else if(val_ms_q1 == 0)Serial.println("MU q1: \t0");
    
    if(val_ms_q2 == 1) Serial.println("MU q2: \t1");
    else if(val_ms_q2 == 0)Serial.println("MU q2: \t0\n");
  }
}

void homing(){
  //Write code for homing each axis at a time
  limitSwitches();
  Serial.println("Waiting for limit switches");
  if(val_ms_z == 1)stepper_z.stop();
  else stepper_z.runSpeed();

  if(val_ms_q1 == 1)stepper_a1.stop();
  else stepper_a1.runSpeed();

  if(val_ms_q2 == 1)stepper_a2.stop();
  else stepper_a2.runSpeed();

  if((val_ms_z == 1) && (val_ms_q1 == 1) && (val_ms_q2 == 1)) case_var=1;
}

void setZero(){
  //Write code for the arms to be straight from the base and the Z-axis to be at its upper limit
  stepper_z.setCurrentPosition(0);
  stepper_a1.setCurrentPosition(0);
  stepper_a2.setCurrentPosition(0);
  case_var=2;
}
