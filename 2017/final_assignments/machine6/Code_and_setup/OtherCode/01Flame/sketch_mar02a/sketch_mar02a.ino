/*
 * Description:
 * Flamesensor
 * Simple Setup.
 * Decreased number means that it detects "flame"
 */

int sensorValue;
void setup() {
  Serial.begin(9600);
}

void loop() {
  //Reads the Value from analogPin A0
  sensorValue = analogRead(A0);
  //Prints the value
  Serial.println(sensorValue);
  delay(1);//Stability Reasons
}
