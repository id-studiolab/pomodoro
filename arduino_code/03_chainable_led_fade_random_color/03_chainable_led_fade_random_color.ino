/*
   The following sketch demonstrate how to make
   one groove chainable Led fade, each time with a random color.

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus
*/

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
}

void loop() {
  //generate a random color
  int r = int(random(0, 255));
  int g = int(random(0, 255));
  int b = int(random(0, 255));

/*
 * use the for loop to adjust the brightness of the led
 * mupltiplying a "brightness index" (i)
 * for each color component(r,g,b)
*/
  for (float i = 0; i < 1; i += 0.01) {
    leds.setColorRGB(0, r * i, g * i, b * i);
    delay(10);
  }
  for (float i = 1; i > 0; i -= 0.01) {
    leds.setColorRGB(0, r * i, g * i, b * i);
    delay(10);
  }
}
