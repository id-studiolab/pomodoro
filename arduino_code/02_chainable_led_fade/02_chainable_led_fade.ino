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

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

//create a ChainableLED object
int numLeds = 1;

ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
  leds.init();
}

void loop() {
  for (int i = 0; i < 255; i++) {
    leds.setColorRGB(0, i, i, i);
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
    leds.setColorRGB(0, i, i, i);
    delay(5);
  }
}



