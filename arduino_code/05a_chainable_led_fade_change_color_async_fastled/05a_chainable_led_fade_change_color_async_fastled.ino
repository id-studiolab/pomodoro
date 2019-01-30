/*
   The following demonstrate how change to use the potentiometer
   to change the color of the led while the led is fading.

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus
*/

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

int potPin=A0;

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];


// asincronous fading
int fadeDuration = 2000;
long lastLedUpdateTime = 0;
int fadesteps = 40;
float fadeUpdateInterval=fadeDuration/fadesteps;
int fadeDirection = 1;
int fadeMax = 255;
int fadeMin = 0;
float fadeAmountXStep = (fadeMax - fadeMin) / fadesteps;
float brightness;

void setup() {
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	float potValue = analogRead(potPin);
  int hue = map (potValue,0,1024,0,255);

	leds[0].setHue(hue);

  if (millis() - lastLedUpdateTime > fadeUpdateInterval) {
    brightness = brightness + fadeAmountXStep * fadeDirection;
    if (brightness > fadeMax || brightness < fadeMin) {
			//make sure that the value is not outside the range
			brightness = constrain(brightness, fadeMin, fadeMax);
			//invert the direction
      fadeDirection *= -1;
    }
    lastLedUpdateTime = millis();
  }
	leds[0].setHSV( hue, 255, brightness);
	FastLED.show();
}
