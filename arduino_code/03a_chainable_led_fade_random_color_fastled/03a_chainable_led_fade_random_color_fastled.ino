/*
   The following sketch demonstrate how to make
   one groove chainable Led fade, each time with a random color.

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus
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
  //set the color of the led to random value
  leds[0].r = int(random(0, 255));
  leds[0].g = int(random(0, 255));
  leds[0].b = int(random(0, 255));

/*
 * use the for loop to adjust the brightness of the led
*/
  for (int i = 0; i < 255; i ++) {
		FastLED.setBrightness(i);
		FastLED.show();
    delay(10);
  }
  for (float i = 255; i > 0; i --) {
		FastLED.setBrightness(i);
		FastLED.show();
    delay(10);
  }
}
