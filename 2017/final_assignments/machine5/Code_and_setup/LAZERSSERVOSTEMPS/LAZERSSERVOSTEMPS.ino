#include <Servo.h>

/* servo vars */
Servo myservo;
int pos;
int loopCount = 0;
int servoPin = 1;

/* temp vars */
int analogTempPin = A0;
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int average = 0;
int total = 0;
boolean waterIsCooking = false;

/* activate singing Tree */
int digitalSinginPin = 8;

/* Laserdwarf vars */
int laserDwarfActivatePin = 13;

void setup()
{
  /* Debug setup */
  //Serial.begin(9600);
  
  /* Temperature setup */
  pinMode(analogTempPin, INPUT);
  
  /* Servo setup */
  pos = 0;
  myservo.attach(servoPin);
  myservo.write(pos);
  delay(1000);

  /* singing tree */
  pinMode(digitalSinginPin, OUTPUT);
  
  /* Laserdwarf setup */
  pinMode(laserDwarfActivatePin, OUTPUT); // Laser start
}

void loop()
{
  if(loopCount < 50)
  {
    loopCount ++;
  }
  /* Temperature input */
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(analogTempPin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if(readIndex >= numReadings)
  {
    readIndex = 0;
  }

  average = total / numReadings;
  //double temp =  Thermistor(average);
  // lower average = higher temp
  //Serial.println(average);
  // make sure the average is not checked at start that's why there is a loopCount
  if(average < 200 && loopCount > 49)
  {
    waterIsCooking = true;
  }
  //Serial.println(temp);

  /* Servo part */
  //delay(2000);
  
  if(waterIsCooking)
  {
    //Serial.println("Servo start");
    for(pos = 0; pos <= 180; pos++)
    {
      myservo.write(pos);
      delay(10);
    }
    //Serial.println("Servo end");
    
    delay(5000);
    myservo.detach();
    
    delay(15000); // wait for player to start
    /* activate singing Tree */
    digitalWrite(digitalSinginPin, HIGH);

    delay(20000); // timer to deactivate Tree
    digitalWrite(digitalSinginPin, LOW); // turn tree off
    delay(2000); // timer to activate next Group
    /* Laser Dwarf part */
    digitalWrite(laserDwarfActivatePin, HIGH);

    waterIsCooking = false;
  }
}
