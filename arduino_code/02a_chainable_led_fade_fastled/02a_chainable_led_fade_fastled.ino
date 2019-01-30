/*
   The following demonstrate how to make
   one groove chainable Led fade.

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus

   TODO:
   -try to attach multiple Chainable LED in series
    and make them all fade.
*/

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

uint16_t aquamarine=0x7FFFD4;

void setup() {
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	leds[0]=aquamarine;
}

void loop() {
  for (int i = 0; i < 255; i++) {
		FastLED.setBrightness(i);
		FastLED.show();
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
		FastLED.setBrightness(i);
		FastLED.show();
    delay(5);
  }
}
