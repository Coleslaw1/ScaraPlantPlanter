#include <math.h>

const int arm_length_1 = 265;
const int arm_length_2 = 115;

int coordinate_1[] = {120, 190};
double inverse_kin_array[2];

void setup() {
  Serial.begin(115200);
  
}

double deg2rad(double deg){
  double rad = deg/(180/PI);
  return rad;
}

double rad2deg(double rad){
  double angle_out = rad*(180/PI);
  return angle_out;
}

double inverse_kin (double pos_x, double pos_y){
   double q2 = acos((pow(pos_x,2)+pow(pos_y,2)-pow(arm_length_1,2)-pow(arm_length_2,2))/(2*arm_length_1*arm_length_2));
   double q1 = atan(pos_y/pos_x) - atan((arm_length_2*sin(q2))/(arm_length_1+arm_length_2*cos(q2)));
   double inv_kin_q1 = rad2deg(q1);
   double inv_kin_q2 = rad2deg(q2);
   inverse_kin_array[0] = inv_kin_q1;
   inverse_kin_array[1] = inv_kin_q2;
}



void loop() {

  inverse_kin(coordinate_1[0],coordinate_1[1]);
  Serial.print("Value q1: ");
  Serial.println(inverse_kin_array[0]);
  Serial.print("Value q2: ");
  Serial.println(inverse_kin_array[1]);
  Serial.println("");
  delay(1000);
}
