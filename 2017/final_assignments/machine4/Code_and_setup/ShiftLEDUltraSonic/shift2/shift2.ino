#include <ShiftOutX.h>
#include <ShiftPinNo.h>

//this are the input parameters to the class constructor
//shiftOutX(_latchPin, _dataPin, _clockPin, _bitOrder, _NofRegisters);
shiftOutX regOne(8, 11, 12, MSBFIRST, 3);
 
void setup() {
 Serial.begin(9600);
}
 
void loop() {  
  long duration, cm;

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(5);
  digitalWrite(13, LOW);
  
  pinMode(13, INPUT);
  duration = pulseIn(13, HIGH);
  cm = duration / 29 / 2;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  regOne.allOff();
if(cm >= 70 && cm<= 80){
    regOne.pinOn(shPin1);
  }else if(cm >= 67.5){
    regOne.pinOn(shPin2);
  }else if(cm >= 65){
    regOne.pinOn(shPin3);
  }else if(cm >= 62.5){
    regOne.pinOn(shPin4);
  }else if(cm >= 60){
    regOne.pinOn(shPin5);
  }else if(cm >= 57.5){
    regOne.pinOn(shPin6);
  }else if(cm >= 55){
    regOne.pinOn(shPin7);
  }else if(cm >= 52.5){
    regOne.pinOn(shPin8);
  }else if(cm >= 50){
    regOne.pinOn(shPin9);
  }else if(cm >= 47.5){
    regOne.pinOn(shPin10);
  }else if(cm >= 45){
    regOne.pinOn(shPin11);
  }else if(cm >= 42.5){
    regOne.pinOn(shPin12);
  }else if(cm >= 40){
    regOne.pinOn(shPin13);
  }else if(cm >= 35){
    regOne.pinOn(shPin14);
  }else if(cm >= 32.5){
    regOne.pinOn(shPin15);
  }else if(cm >= 30){
    regOne.pinOn(shPin16);
  }else if(cm >= 27.5){
    regOne.pinOn(shPin17);
  }else if(cm >= 25){
    regOne.pinOn(shPin18);
  }else if(cm >= 22.5){
    regOne.pinOn(shPin18);
  }else if(cm >= 20){
    regOne.pinOn(shPin19);
  }else if(cm >= 17.5){
    regOne.pinOn(shPin20);
  }else if(cm >= 15){
    regOne.pinOn(shPin21);
  }else if(cm >= 13.5){
    regOne.pinOn(shPin22);
  }else if(cm >= 11.5){
    regOne.pinOn(shPin23);
  }else if(cm >= 10){
    regOne.pinOn(shPin24);
  }
 /* regOne.pinOn(shPin1);
  regOne.pinOn(shPin2);
  
  regOne.pinOn(shPin4);
  regOne.pinOn(shPin3);
  
  regOne.pinOn(shPin21);
  regOne.pinOn(shPin22);
  
  regOne.pinOn(shPin23);
  regOne.pinOn(shPin24);
  regOne.allOff();
  if(cm >=70){
    regOne.pinOn(shPin1);
  }else if(cm <70 && cm >=65){
    regOne.pinOn(shPin2);
  }else if(cm <65 && cm >=60){
    regOne.pinOn(shPin3);
  }else if(cm <60 && cm >=55){
    regOne.pinOn(shPin4);
  }else if(cm <55 && cm >=50){
    regOne.pinOn(shPin5);
  }else if(cm <50 && cm >=45){
    regOne.pinOn(shPin6);
  }else if(cm <45 && cm >=40){
    regOne.pinOn(shPin7);
  }else if(cm <40 && cm >=35){
    regOne.pinOn(shPin8);
  }else if(cm <35 && cm >=30){
    regOne.pinOn(shPin9);
  }else if(cm <30 && cm >=25){
    regOne.pinOn(shPin10);
  }*/
  delay(100);
}
