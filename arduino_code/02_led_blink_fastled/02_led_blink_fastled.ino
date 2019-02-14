/*
 * The following code demonstrates how to make
 * one Grove ChainableLED blink using the fastled library.
 *
 * STEPS:
 * -Make sure you connected your ChainableLED
 * to the right pin on your Seeeduino Lotus (note that
 * a ChainableLED allocates two pins actually).
 *
 * TODO:
 * -Now that you know how to control one led, can you make it
 * fade in brightess?
 */

#include <FastLED.h>

//connections of the ChainableLED
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

void setup() {
	//start the led library
	//this example uses an esoteric c++ mechanism called "Templates"
	//so do not worry to much about the syntax, just make sure a line
	//such as the line below is in your setup() if you use FastLED.
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	// Turn the LED on, then pause
	leds[0].setRGB( 255, 255, 255);
	FastLED.show();
	delay(500);
	// Now turn the LED off, then pause
	leds[0].setRGB( 0, 0, 0);
	FastLED.show();
	delay(500);
}
