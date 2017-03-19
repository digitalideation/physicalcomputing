/*
   Description:
   Flamesensor
   Sets a Value to detect "Flame".
   It needs 2 Seconds to fit with the surrounding to initialize the startValue
   Afterwards, it will detect "flame" and print it out.
*/

int sensorValue;
boolean isStartValue;
int startValue;
int startValueRange;
int yellowLED = 13;

void setup() {
  //Flamesensor
  isStartValue = true;
  startValueRange = 5;
  //LED
  pinMode(yellowLED, 13);
  Serial.begin(9600);
}

void loop() {
  //Flamesensor
  if (isStartValue) {
    delay(2000);
    isStartValue = false;
    startValue = sensorValue = analogRead(A0);
  }
  //Reads the Value from analogPin A0
  sensorValue = analogRead(A0);
  //Prints the value
  //Serial.println(sensorValue);
  if (sensorValue < (startValue - startValueRange)) {
    digitalWrite(yellowLED, HIGH);
    Serial.println("FLAME FLAME FLAME");
  } else {
    digitalWrite(yellowLED, LOW);
    Serial.println("---");
  }
  //Stability Reasons, don't ask.
  delay(1);
}

