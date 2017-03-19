int lightPin = A0;
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int average = 0;
int total = 0;

void setup()
{
  // configure the Arduino Serial interface
  Serial.begin(9600);
  pinMode(lightPin, INPUT);

  // initialize Array with 0
  for(int i = 0; i < numReadings; i++)
  {
    readings[i] = 0;
  }
}

void loop()
{
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
  if(readIndex >= numReadings)
  {
    readIndex = 0;
  }
  
  // divide the total through the number of meassures
  average = total / numReadings;
  
  //  print the Voltage going through the Resistor
  Serial.println(analogRead(lightPin));
  delay(10);
}
