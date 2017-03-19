#include <Servo.h>
Servo myServo;
int pos;
int sensorPin = A0;
int sensorValue;
boolean test = false;

int const numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  pos = 1;
  myServo.attach(11);  
  myServo.write(pos);
  Serial.begin(9600);
  for(int i = 0; i  < numReadings; i++){
      readings[i] = 0;
  }
  delay(4000);
}

void loop() {
 //  myServo.write(180);
  sensorValue = analogRead(sensorPin);
  total = total - readings[readIndex];
  readings[readIndex] = sensorValue;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if(readIndex >= numReadings){
    readIndex = 0;
  }

  average = total / numReadings;
  if(average > 50){
    test = true;
  }
  if(test){
    myServo.write(179);
    delay(2000);
    myServo.detach();
  }
  Serial.println(average);
  //myServo.write(map(sensorValue,0,1023,0,180));
  delay(10);
}
