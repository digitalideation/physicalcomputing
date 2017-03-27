#include <Servo.h>
Servo gate;
int pos;
int servoPin;
const int pingPin = 10;
int sensorValue = 0;
boolean gateclosed;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  gateclosed = true;
  servoPin = 5;
  pinMode(A1, INPUT);
  gate.attach(servoPin);
  gate.write(0);
}

void loop() {



  
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");

  delay(100);

  sensorValue = analogRead (cm);
    
    if (cm <= 50){ 
      Serial.println("runMotor");
      runMotor();
    }

  digitalWrite(8, LOW);

    Serial.println (sensorValue, DEC);
  //Serial.println(analogRead(A1));
  
  if (analogRead(A1) >= 300 && gateclosed ){
      delay(1000);
      Serial.println("openGATE");
      gate.attach(servoPin);
      gate.write(80);
      delay(1000);
      gateclosed = false;
    }else {
        gate.detach();
    }

}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;

}

void runMotor(){
    digitalWrite(9, LOW);  //ENABLE CH A
    //digitalWrite(8, HIGH); //DISABLE CH B
    digitalWrite(12, LOW);   //Sets direction of CH A
    analogWrite(3, 255);   //Moves CH A
  
    delay(2000);
  
    digitalWrite(9, HIGH); 
}

