/*
   The following code demonstrates how to use the potentiometer
   to change the color of the led, the setHue() function is used.

   STEPS:
   -Make sure you connected your ChainableLED
   to the right pin on your Seeeduino Lotus

   TODO:
   Whith this code, the color of the led changes only when the loop() restart.
   Can you modify the code so that the color changes whenever you are turning the
   potentiometer indipendently from the fade animation?
 */

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

int potPin=A0;

//how many leds
#define NUM_LEDS 1

//an array to store the led data
CRGB leds[NUM_LEDS];

void setup() {
	//start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	float potValue = analogRead(potPin);
	int hue = map (potValue,0,1024,0,255);

	leds[0].setHue(hue);

	for (float i = 0; i < 255; i++) {
		FastLED.setBrightness(i);
		FastLED.show();
		delay(10);
	}

	for (float i = 255; i > 0; i--) {
		FastLED.setBrightness(i);
		FastLED.show();
		delay(10);
	}
}
