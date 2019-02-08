/*
   The following demonstrate how change to use the potentiometer
   to change the color of the led, setColorHSB() function is used.

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

void setup() {
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  float potValue = analogRead(potPin);
  int hue = map (potValue,0,1024,0,255);

	leds[0].setHue(hue);

  for (float i = 0; i < 255; i ++) {
		FastLED.setBrightness(i);
		FastLED.show();
    delay(10);
  }

  for (float i = 255; i > 0; i--) {
		FastLED.setBrightness(i);
		FastLED.show();
		delay(10);
  }
}
