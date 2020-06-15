<h1>Introduction</h1>

During the COVID-19 pandemic students of the Smart Manufacturing and Robotics minor were forced to work at home.
After creating a React-native application two students from the old project team decided to go back to robotics. 
Long brainstorm sessions and much research on YouTube later the team found a perfect project:


*A SCARA (Selective Compliance Assembly Robot ARM) to pick and place cuttings from cuttingtrays to salable pots.*


With this outcome in mind, the engineering began.

<h2>Mechanical design</h2>

The mechanical design is based on a twp basic techniques.
1. 3D-printing
2. CNC laser cutting

With these techniques in mind and the ability to buy some parts on the internet the project team started engineering. 
Rapidly after the start both the Z-axis (for vertical displacement) and XY-axis for horizontal movement had their initial designs.

Many iterations have been done before reaching the final design which looks like this:

IMAGES IMAGES IMAGES

<h2>Electrical design</h2>

For the product the team designed their own custom made PCB (Printed Circuit Board).

IMAGES IMAGES IMAGES

With this PCB the SCARA robot can be operated with the help of an ESP32 microcontroller unit. The ESP32 is being used 
to drive control the three TB6600 stepper motor drivers, which in their time send the robot to the desired destination.

<h2>Software design</h2>

The software of the SCARA robot is based on the AccelStepper library that's available within the Arduino IDE. This
library is able to do (almost) anything you want with a stepper motor. For this project it was extremely useful when
sending the robot from location to location and while doing that, making use of the acceleration and braking of the motor.

In the project the pick-up and drop-down locations have been hardcoded. The angles of the arm to reach a wanted destination
were found using inverse kinematics for a double pendulum. During the project, the project team simulated the maximum reach
of the SCARA robot and placed the cuttingstray and salable pots within this reach.

IMAGES IMAGES IMAGES