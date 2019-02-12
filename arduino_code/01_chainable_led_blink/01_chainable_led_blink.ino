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

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

//create a ChainableLED object
int numLeds = 1;

ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
	/*
	   depending on the version of the library which you have,
	   you might need to use leds.init()
	   to start the communication betwewn Arduino and the chainable led.
	 */
	//leds.init();
}

void loop() {
	leds.setColorRGB(0, 255, 255, 255);
	delay(1000);
	leds.setColorRGB(0, 0, 0, 0);
	delay(1000);
}
