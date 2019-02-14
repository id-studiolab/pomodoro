/*
   The following code demonstrates how to make
   one Grove ChainableLED fade.

   STEPS:
   -Make sure you connect your ChainableLED
   to the right pin on your Seeeduino Lotus

   TODO:
   -Try to attach multiple ChainableLEDs in series
    and make them all fade.
 */

#include <FastLED.h>

//connections of the ChainableLED
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

CRGB warm_pink = 0xFF69B4;

void setup() {
	//start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	//set color of the one and only led
	leds[0]=warm_pink;
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
