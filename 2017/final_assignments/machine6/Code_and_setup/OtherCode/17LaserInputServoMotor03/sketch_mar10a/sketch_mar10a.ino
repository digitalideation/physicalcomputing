//-----------------------------------------------
//Servo
//-----------------------------------------------
#include <Servo.h>
Servo myServo;
int pos;
int pinServo1 = 11;
boolean inputSignal;
boolean initializeStart;
//Startposition
int startPos = 65;//65
int leftPos = 155;//155
int rightPos = 40;//10
boolean wasLeft = false;
boolean wasRight = false;
int delayTimeInForLoop = 2;
int delayTimeBetweenLeftAndRight = 15000;

//-----------------------------------------------
//Infrared
//-----------------------------------------------
int lightPin = A0;
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int average = 0;
int total = 0;
//-----------------------------------------------
//StartValue
//-----------------------------------------------
boolean isStartValue;
int startValue;
int startValueRange;
boolean runServoCode = true;



void setup() {
  //-----------------------------------------------
  //StartValue
  //-----------------------------------------------
  isStartValue = true;
  startValueRange = 400;
  //-----------------------------------------------
  //Servo
  //-----------------------------------------------
  pos = 0;
  myServo.attach(pinServo1);
  inputSignal = false;
  initializeStart = true;
  //-----------------------------------------------
  //Infrared
  //-----------------------------------------------
  // configure the Arduino Serial interface
  Serial.begin(9600);
  pinMode(lightPin, INPUT);
  // initialize Array with 0
  for (int i = 0; i < numReadings; i++)
  {
    readings[i] = 0;
  }
}

void loop() {
  //-----------------------------------------------
  //StartValue
  //-----------------------------------------------
  if (isStartValue) {
    delay(10000);
    isStartValue = false;
    startValue = analogRead(lightPin);
  }
  //-----------------------------------------------
  //Infrared
  //-----------------------------------------------
  // print the Voltage going through the Resistor (1024 is 5V passing).
  // The lower the number, the lower the light and the higher the resistance.
  //  Serial.println(analogRead(lightPin));
  // delay(10);
  // remove the number in the Array that we are gonna overwrite from the total
  total = total - readings[readIndex];
  // write the new meassure into the Array
  readings[readIndex] = analogRead(lightPin);
  // add the new meassure Number to the total again
  total = total + readings[readIndex];
  // increment the array index "pointer"
  readIndex++;
  // reset the array index "pointer"
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // divide the total through the number of meassures
  average = total / numReadings;

  //  print the Voltage going through the Resistor
  //Serial.println(analogRead(lightPin));
  if (analogRead(lightPin) < (startValue - startValueRange)) {
    runServoCode = true;
  }
  //-----------------------------------------------
  //Servo
  //-----------------------------------------------
  if (initializeStart) {
    myServo.write(65);
    initializeStart = false;
    Serial.println("Init Start");
    myServo.detach();
    delay(2000);
  }
  if (runServoCode) {
    if (!wasRight) {
      //Turn Left
      if (!wasLeft) {
        myServo.attach(pinServo1);
        for (pos = startPos; pos <= leftPos; pos += 1) {
          myServo.write(pos);
          delay(delayTimeInForLoop);
        }
        Serial.println("Turned Left");
        wasLeft = true;
        myServo.detach();
      }
      //Wait 10 seconds
      delay(delayTimeBetweenLeftAndRight);
      //Then turn right
      myServo.attach(pinServo1);
      for (pos = leftPos; pos >= rightPos; pos -= 1) {
        myServo.write(pos);
        delay(delayTimeInForLoop);
      }
      Serial.println("Turned Right");
      wasRight = true;
      myServo.detach();
    }
  }
}

