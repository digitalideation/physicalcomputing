int brightness;
void setup() {
  pinMode(9, OUTPUT);
  brightness = 0;
}


void loop() {
  if(brightness < 255) {
    brightness++;
  }
  analogWrite(9,brightness);
  delay(50);
}

