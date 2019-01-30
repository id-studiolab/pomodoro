/*
   The following demonstrate how change to use the potentiometer
   to change the color of the led, setColorHSB() function is used.

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus
*/

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

int potPin = A0;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
}

void loop() {
  float potValue = analogRead(potPin);
  float hue = potValue / 1024;

  for (float i = 0; i < .5; i += 0.01) {
    //notice that we are using (byte led, float hue, float saturation, float brightness);
    leds.setColorHSB(0, hue, 1.0, i);
    delay(10);
  }

  for (float i = .5; i > 0; i -= 0.01) {
    leds.setColorHSB(0, hue, 1.0, i);
    delay(10);
  }
}
