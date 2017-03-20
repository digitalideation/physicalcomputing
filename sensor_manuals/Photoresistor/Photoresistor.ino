int lightPin = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(lightPin));
  delay(10);
}