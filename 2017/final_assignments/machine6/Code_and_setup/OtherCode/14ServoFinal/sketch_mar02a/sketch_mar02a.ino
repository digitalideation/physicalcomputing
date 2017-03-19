#include <Servo.h>
//Servo
Servo myServo;
int pos;
int pinServo1 = 11;
boolean inputSignal;
boolean initializeStart;
//Startposition
int startPos = 65;
int leftPos = 155;
int rightPos = 10;
boolean wasLeft = false;
boolean wasRight = false;
int delayTimeInForLoop = 2;
int delayTimeBetweenLeftAndRight = 15000;


void setup() {
  pos = 0;
  inputSignal = false;
  initializeStart = true;
  myServo.attach(pinServo1);
}

void loop() {
  if (!wasRight) {
    if (initializeStart) {
      myServo.write(65);
      initializeStart = false;
      delay(10000);
    }

    //Turn Left
    if (!wasLeft) {
      for (pos = startPos; pos <= leftPos; pos += 1) {
        myServo.write(pos);
        delay(delayTimeInForLoop);
      }
      wasLeft = true;
    }
    //Wait 10 seconds
    delay(delayTimeBetweenLeftAndRight);
    //Then turn right
    for (pos = leftPos; pos >= rightPos; pos -= 1) {
      myServo.write(pos);
      delay(delayTimeInForLoop);
    }
    wasRight = true;
  }
}

