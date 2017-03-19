/*
   Description:
   Flamesensor
   Sets a Value to detect "Flame".
   It needs 2 Seconds to fit with the surrounding to initialize the startValue
   Afterwards, it will detect "flame" and print it out.

   If the sensor was activated once, it will play music
*/


// TONES  ==========================================
// Start by defining the relationship between
//       note, period, &  frequency.
#define  c     3830    // 261 Hz
#define  d     3400    // 294 Hz
#define  e     3038    // 329 Hz
#define  f     2864    // 349 Hz
#define  g     2550    // 392 Hz
#define  a     2272    // 440 Hz
#define  b     2028    // 493 Hz
#define  C     1912    // 523 Hz
// Define a special note, 'R', to represent a rest
#define  R     0

//Flamesensor
int sensorValue;
boolean isStartValue;
int startValue;
int startValueRange;
//LED
int yellowLED = 13;
//Speaker
int speakerOut = 11;
int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
long tempo = 10000;// Set overall tempo
int pause = 1000;// Set length of pause between notes
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

void setup() {
  //Flamesensor
  isStartValue = true;
  startValueRange = 5;
  //LED
  pinMode(yellowLED, 13);
  Serial.begin(9600);
  //Speaker
  pinMode(speakerOut, OUTPUT);
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
    for (int i = 0; i < MAX_COUNT; i++) {
      tone_ = melody[i];
      beat = beats[i];

      duration = beat * tempo; // Set up timing

      playTone();
      // A pause between notes...
      delayMicroseconds(pause);
    }
  } else {
    digitalWrite(yellowLED, LOW);
    Serial.println("---");
  }
  //Stability Reasons, don't ask.
  delay(1);
}

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}
