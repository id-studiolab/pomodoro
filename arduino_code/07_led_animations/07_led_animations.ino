/*
   The following demonstrate how change to use the potentiometer
   to change the color of the led

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus

   TODO:
   Now the led color changes only at the begininning of the loop,
   can you make the color change at any time when turning the pot?
*/

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

int potPin = A0;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

// animation variables
int fadeDuration = 2000;
long lastLedUpdateTime = 0;
int fadesteps = 100;
float fadeUpdateInterval=fadeDuration/fadesteps;
int fadeDirection = 1;
float fadeMax = 0.8;
float fadeMin = 0;
float fadeAmountXStep = (fadeMax - fadeMin) / fadesteps;
float brightness;


enum animationType{
	CROSSFADE,
	BLINK,
	RAINBOW
}

void setup() {
}

void loop() {
  float potValue = analogRead(potPin);
  float hue = potValue / 1024;

  if (millis() - lastLedUpdateTime > fadeUpdateInterval) {
    brightness = brightness + fadeAmountXStep * fadeDirection;
    if (brightness > fadeMax || brightness < fadeMin) {
      fadeDirection *= -1;
    }
    lastLedUpdateTime = millis();
  }
  leds.setColorHSB(0, hue, 1.0, brightness/2);
	Serial.println(brightness*180);
}

void
