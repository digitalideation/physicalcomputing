/**
 * @Author Jony Margelist 
 * @Date 16.03.2017
 * @Version 1.0.0
 * 
 * Code which initialize a servomotor in a starting
 * Position. If an Laser input comes in, it turns left
 * to burn a rope, and turns right after some time
 * to burn another rope. 
 */

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
int startPos = 65;//First Value: 65
int leftPos = 155;//First Value: 155
int rightPos = 40;//First Value: 10
boolean wasLeft = false;
boolean wasRight = false;
int delayTimeInForLoop = 2;
int delayTimeBetweenLeftAndRight = 20000;
int delayTimeFromLaserToTurnleft = 3000;

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
boolean runServoCode = false; //false = with laser, true = without laser(for testing purposes)

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
  initializeStart = true; //to set the servo in the right position
  //-----------------------------------------------
  //Infrared
  //-----------------------------------------------
  // configure the Arduino Serial interface
  Serial.begin(9600);
  pinMode(lightPin, INPUT);
  // initialize Array with 0
  //this is needed for smoothed values
  for (int i = 0; i < numReadings; i++)
  {
    readings[i] = 0;
  }
}

void loop() {
  //-----------------------------------------------
  //StartValue
  //-----------------------------------------------
  //Gets the Value after 10 seconds from the light sensor
  //and saves it in a variable. We need this variable later
  //to actually detect the laser.
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
  //this is the smoothed value
  average = total / numReadings;

  //The below 3 lines should output something like:
  //838
  //---
  //430
  //The first number is the value from the sensor
  //The third line shows the difference from the startValue(which we 
  //initialized at the start) minus a certain range.
  Serial.println(analogRead(lightPin));
  Serial.println("---");
  Serial.println(startValue - startValueRange);
  //If the sensor value is lower than the startvalue minus the range, then set 
  //runServoCode = true to move the servomotor.
  if (analogRead(lightPin) < (startValue - startValueRange)) {
    runServoCode = true;
    //delay to see the lazors with the formachine!
    delay(delayTimeFromLaserToTurnleft);
  }
  //-----------------------------------------------
  //Servo
  //-----------------------------------------------
  //This runs only at the beginning and only once.
  if (initializeStart) {
    myServo.write(65);
    initializeStart = false;
    //Serial.println for debugging
    Serial.println("Init Start");
    //Detach the servo if we dont need it. Otherwise it could vibrate.
    myServo.detach();
    delay(2000);
  }
  //if laser was detected
  if (runServoCode) {
    //if the servomotor was not right until now
    if (!wasRight) {
      //if the servomotor was not left until now, then
      //Turn Left
      if (!wasLeft) {
        //we detached it earlier, so we need to attach it again
        myServo.attach(pinServo1);
        //change the servo motors position
        for (pos = startPos; pos <= leftPos; pos += 1) {
          myServo.write(pos);
          //delay to give the candle time to burn the rope
          delay(delayTimeInForLoop);
        }
        Serial.println("Turned Left");
        wasLeft = true;
        myServo.detach();
      }
      //Wait some seconds until it moves right
      delay(delayTimeBetweenLeftAndRight);
      //Turn right
      myServo.attach(pinServo1);
      for (pos = leftPos; pos >= rightPos; pos -= 1) {
        myServo.write(pos);
        delay(delayTimeInForLoop);
      }
      Serial.println("Turned Right");
      wasRight = true;
      myServo.detach();
      //Servomotor will stay right after this code. 
    }
  }
}
