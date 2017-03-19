/*
 * Description:
 * Flamesensor
 * Sets a Value to detect "Flame". 
 * It needs 2 Seconds to fit with the surrounding to initialize the startValue
 * Afterwards, it will detect "flame" and print it out.
 */

int sensorValue;
boolean isStartValue;
int startValue;
int startValueRange;

void setup() {
  isStartValue = true;
  startValueRange = 5;
  Serial.begin(9600);
}

void loop() {
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
    Serial.println("FLAME FLAME FLAME");
  }else {
    Serial.println("---");
  }
  //Stability Reasons, don't ask.
  delay(1);
}
