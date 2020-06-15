<h1>Introduction</h1>

During the COVID-19 pandemic students of the Smart Manufacturing and Robotics minor were forced to work at home.
After creating a React-native application two students from the old project team decided to go back to robotics. 
Long brainstorm sessions and much research on YouTube later the team found a perfect project:


*A SCARA (Selective Compliance Assembly Robot ARM) to pick and place cuttings from cuttingtrays to salable pots.*


With this outcome in mind, the engineering began. These engineering has been broken up into three work packages. The
mechanical engineering, electrical engineering and last but not least, the software engineering. 

For mechanical and electrical engineering, state of the art software packages have been used. For the software engineering
the team decided to work with the Arduino IDE, this decision was made with the time left for the project in mind and 
keeping the large amount of example projects in mind.

<h2>Mechanical design</h2>

The mechanical design is based on a two basic techniques.
1. 3D-printing
2. CNC laser cutting

The team decided to focus on these two techniques because they are available at home or at the university and because they
are not very expensive.

With these techniques in mind and the ability to buy some parts on the internet the project team started engineering. 
Rapidly after the start both the Z-axis (for vertical displacement) and XY-axis for horizontal movement had their initial designs.

Many iterations have been done before reaching the final design which looks like this:

IMAGES IMAGES IMAGES

The timing belts used to drive the system have been concealed within the carbon tubes which form the arms. Because of this
there are no belts visible at any time during the project. A special feature is that there is a belt from the base of 
the arm towards the end-effector, making sure that the end effector stays parallel to the base at all time.

<h2>Electrical design</h2>

For the product the team designed their own custom made PCB (Printed Circuit Board). This has been done to reduce the amount
of wires for the project and to make sure that all connections are made properly. As a nice feature the project group decided to
print the SMR-logo on the silkscreen and advertise the minor a bit.

![PCB design](/Webarticle_assets/pcb_out.png "PCB design")
![PCB 3D design](/Webarticle_assets/pcb_a.jpg "PCB 3D design")

With this PCB the SCARA robot can be operated with the help of an ESP32 microcontroller unit. The ESP32 is being used 
to drive control the three TB6600 stepper motor drivers, which in their time send the robot to the desired destination. 
For control the project team decided to go with counting steps (in stead of working with something like an encoder). Although
counting steps might not be the most accurate proces, it is for sure the cheapest. 

<h2>Software design</h2>

The software of the SCARA robot is based on the AccelStepper library that's available within the Arduino IDE. This
library is able to do (almost) anything you want with a stepper motor. For this project it was extremely useful when
sending the robot from location to location and while doing that, making use of the acceleration and braking of the motor.

![ESP32 software](/Webarticle_assets/Arduino_ide.png "ESP32 software")

After booting the system the first thing the SCARA robot wants to do is home itself. Homing of the robot gets done by physically
pressing three microswitches (one per arm and one for the z-axis) after each other. Once all three switches have been pressed the SCARA 
robot gets in position for the pick-and-place cycle. 

The pick-up and drop-down locations have been hardcoded. The angles of the arm to reach a wanted destination
were found using inverse kinematics for a double pendulum. During the project, the project team simulated the maximum reach
of the SCARA robot and placed the cuttingstray and salable pots within this reach.

![Inverse kinematics q2](/Webarticle_assets/INV_KIN_A1.png "Inverse kinematics q2")
![Inverse kinematics q1](/Webarticle_assets/INV_KIN_A2.png "Inverse kinematics q1")
![Python Simulation](/Webarticle_assets/sim.png "Python Simulation")


<h1>Conclusion</h1>

From this project we can conclude that it definitly is possible to build a low cost custom SCARA robot. To realize the design some smart thinking is possible and it's very
desirable to have acces to fast/accurate prototyping resources (e.g. waterjetting, resin printing). During the project the project team implemented the knowledge gained
during four years of Mechatronics engineering at a level that was both fun and professional.