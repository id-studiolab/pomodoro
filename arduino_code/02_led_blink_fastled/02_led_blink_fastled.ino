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
  leds[0].setRGB( 10, 10, 150);

  for (int i=0; i< 255; i++){
    FastLED.setBrightness(i);
    FastLED.show();
    delay(5);
  }

  for (int i=255; i> 0; i--){
    FastLED.setBrightness(i);
    FastLED.show();
    delay(5);
  }
}
