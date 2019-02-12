/*
 * The following code demonstrates how to make
 * one Grove ChainableLED blink.
 *
 * STEPS:
 * -Make sure you connected your chainable LED
 * to the right pin on your Seeeduino Lotus (note that
 * a ChainableLED allocates two pins actually).
 *
 * TODO:
 * -Try to attach multiple ChainableLEDs in series
 *  and write code to control them all
 */

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
  //start the led library
  leds.init();
}

void loop() {
	leds.setColorRGB(0, 255, 255, 255);
	delay(1000);
	leds.setColorRGB(0, 0, 0, 0);
	delay(1000);
}
