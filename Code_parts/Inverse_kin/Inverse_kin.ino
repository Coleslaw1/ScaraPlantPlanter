#include <math.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

double deg2rad(double deg){
  double rad = deg/(180/PI);
  return rad;
}

double rad2deg(double rad){
  double angle_out = sin(rad);
  return angle_out;
}

void loop() {
  // put your main code here, to run repeatedly:
  // Enter value in rad and output value is in rad
  double deg = 90;
  double angle_rad = deg2rad(deg);
  double output = rad2deg(angle_rad);
  Serial.println(output);
}
