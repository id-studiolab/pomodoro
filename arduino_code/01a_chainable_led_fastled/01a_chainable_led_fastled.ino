/*
 * The following demonstrate how to use make
 * one groove chainable Led blink.
 *
 * STEPS:
 * -make sure you connected your chainable LED
 * to the right pin on your seeduino Lotus
 *
 * TODO:
 * -try to attach multiple Chainable LED in series
 *  and write some code to control them
 */

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

void setup() {
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	// Turn the LED on, then pause
	leds[0].setRGB( 255, 255, 2255);
	FastLED.show();
	delay(500);
	// Now turn the LED off, then pause
	leds[0].setRGB( 0, 0, 0);
	FastLED.show();
	delay(500);
}
