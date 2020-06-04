/* 
AccelStepper library: http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a73bdecf1273d98d8c5fbcb764cabeea5

 To do:
 - Test main functioning of Accelstepper code 
 - Make a conversion between angles and steps (1 degree = 53 steps)
 - Position logging to FRAM|API
 - Find out how the setCurrentPosition() function works
 - Mapping all locations and determine the path
 - Include servo code
*/

#include <AccelStepper.h>

#define stepPin_a1 26
#define dirPin_a1 27

#define stepPin_a2 32
#define dirPin_a2 33

#define stepPin_z 21
#define dirPin_z 12

const int uStepSize_a1 = 32;
const int uStepSize_a2 = 32;
const int uStepSize_z = 32;
const int stepsRevolution = 200;
const int stepsPerDegree = 53;
const int stepsPerMillimeter = 800;

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
    stepper_a1.moveTo(90*stepsPerDegree); 
    
    stepper_a2.setMaxSpeed(100.0);
    stepper_a2.setAcceleration(50.0);
    stepper_a2.moveTo(90*stepsPerDegree);
    
    stepper_z.setMaxSpeed(100.0);
    stepper_z.setAcceleration(50.0);
    stepper_z.moveTo(100*stepsPerMillimeter); 
    Serial.println("Done setting up");
}

void loop()
{
    // Change direction at the limits
    Serial.println("Running");
    stepper_a1.run();
    stepper_a2.run();
    stepper_z.run();
}
