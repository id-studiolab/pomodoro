/*
   The following code demonstrates how to make
   one Grove ChainableLED fade.

   STEPS:
 * -Make sure you connected your chainable LED
 * to the right pin on your Seeeduino Lotus (note that
 * a ChainableLED allocates two pins actually).

   TODO:
  * -Try to attach multiple ChainableLEDs in series
  * and make them all fade.
 */

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

uint16_t color=0xFF69B4;

void setup() {
  //start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	leds[0]=color;
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
