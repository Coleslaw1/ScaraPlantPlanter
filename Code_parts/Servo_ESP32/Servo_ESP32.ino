#include <ESP32_Servo.h>

#define DELAY 2000

#define SERVO_PIN 4
//18

Servo myservo;

void setup() {
  myservo.attach(SERVO_PIN);
}

void loop() {
  myservo.write(90);
  delay(DELAY);
  myservo.write(270);
  delay(DELAY);
}
