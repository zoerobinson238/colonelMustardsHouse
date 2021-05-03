#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(60, 6);

int potVal1;
int potPin1 = A0;

int threshold1 = 170.5;
int threshold2 = 341;
int threshold3 = 511.5;
int threshold4 = 682;
int threshold5 = 852.5;

uint32_t color1 = strip.Color(255, 100, 0);
uint32_t color2 = strip.Color(255, 220, 0);
uint32_t color3 = strip.Color(222, 4, 63);
uint32_t color4 = strip.Color(255, 182, 193);
uint32_t color5 = strip.Color(0, 255, 0);
uint32_t color6 = strip.Color(0, 0, 255);
uint32_t color7 = strip.Color(255, 0, 0);

int ledState;

int trigPin = 10;
int echoPin = 13;

const int arrayLen = 10;
float distanceArray[arrayLen];
float avgDist;

const int buzzer = 2;

void setup() {
  Serial.begin(9600);

  pinMode(potPin1, INPUT);

  strip.begin();
  strip.clear();
  strip.setBrightness(100);

  pinMode(10, OUTPUT);
  pinMode(13, INPUT);

  pinMode(buzzer, OUTPUT);

}

void loop() {

  if (abs (analogRead(potPin1) - potVal1) >= 10) {
    potVal1 = analogRead(potPin1);
  }

  //Serial.println(potVal1);

  checkState1(potVal1, threshold1, threshold2, threshold3, threshold4, threshold5);

  for (int i = 0; i < arrayLen; i++) {
    distanceArray[i] = getDistance(trigPin, echoPin);
  }

  avgDist = giveMeTheAverage(distanceArray, arrayLen);
  //Serial.println(avgDist);

  if (avgDist <= 10) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color7);
      }
    strip.show();
    Serial.println("closee");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec


  }
  if (avgDist > 5) {
    Serial.println("nothing");
  }

  //  if(buttPressed == true){
  //    ledState = 6;
  //  }
  //
  //  Serial.println(digitalRead(buttonPin));


  switch (ledState) {
    case 0:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color1);
      }
      strip.show();
      break;

    case 1:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color2);
      }
      strip.show();
      break;

    case 2:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color3);
      }
      strip.show();

      break;

    case 3:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color4);
      }
      strip.show();
      break;

    case 4:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color5);
      }
      strip.show();
      break;

    case 5:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color6);
      }
      strip.show();
      break;

      //        case 6:
      //          strip.clear();
      //          break;
  }

}

void checkState1(int aVal, int aThreshold1, int aThreshold2, int aThreshold3, int aThreshold4, int aThreshold5) {
  if (aVal <= aThreshold1) {
    ledState = 0;
  }
  else if (aVal >= aThreshold1 && aVal <= aThreshold2) {
    ledState = 1;
  }
  else if (aVal >= aThreshold2 && aVal <= aThreshold3) {
    ledState = 2;
  }
  else if (aVal >= aThreshold3 && aVal <= aThreshold4) {
    ledState = 3;
  }
  else if (aVal >= aThreshold4 && aVal <= aThreshold5) {
    ledState = 4;
  }
  else if (aVal >= aThreshold5) {
    ledState = 5;
  }
}

float giveMeTheAverage (float * anArray, int anArrayLength) {

  float average = 0;
  for (int i = 0; i < anArrayLength; i++) {
    average += anArray[i];
    average = average / anArrayLength;
  }

  return average;
}

float getDistance(int aTrigPin, int anEchoPin) {

  float duration; //return the distance that the meter is reading at
  float distance;

  digitalWrite(aTrigPin, LOW); //turn off before it starts
  delayMicroseconds(2);

  digitalWrite(aTrigPin, HIGH); //send off the signal
  delayMicroseconds(10);
  digitalWrite(aTrigPin, LOW);

  duration = pulseIn(anEchoPin, HIGH); //how long distance is read as high which will then tell you how far away the object is

  distance = duration / 2 * 0.0344; // converts it to cm as well as half it to tell how far it goes one way

  //Serial.println(distance);

  return distance;
}

//boolean debounce(int aButtonPin, boolean aPreviousState) {
//  boolean aButtonState = digitalRead(aButtonPin);
//  if (aButtonPin == HIGH & aPreviousState == LOW) {
//    delay(50);
//  }
//  return aButtonState;
//}
