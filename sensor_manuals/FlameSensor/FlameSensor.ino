int sensorValue;

void setup() {
	Serial.begin(9600);
}

void loop() {
	//Reads the value from analogPin A0
	sensorValue = analogRead(A0);
	//Prints the Value
	Serial.println(sensorValue);
	delay(1); //Stability reasons

}