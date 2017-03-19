#include <Servo.h>

Servo myServo1;
int pos;
int pinServo1=11;

void setup() {
  pos = 0;
  myServo1.attach(pinServo1);
}

void loop() {
  for(pos = 0; pos  <= 180; pos +=1) {
    myServo1.write(pos);
    delay(30);
  }
  delay(5000);
  for(pos =180; pos >=0; pos -=1) {
    myServo1.write(pos);
    delay(30);
  }
  delay(5000);
}

