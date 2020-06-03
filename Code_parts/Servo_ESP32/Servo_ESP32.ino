#include <ESP32_Servo.h>

#define DELAY 300

#define SERVO_PIN 4
//18

Servo myservo;

void setup() {
  myservo.attach(SERVO_PIN);
}

void loop() {
  myservo.write(0);
  delay(DELAY);
  myservo.write(180);
  delay(DELAY);
}
