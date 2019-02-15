/*
   The following code demonstrates how to use the potentiometer
   to change the color of the led during the fading.

   STEPS:
   -Make sure you connect your ChainableLED
   to the right pin on your Seeeduino Lotus

   TODO:
   - Design and code an other animation wich doesn't use delay: blink, rainbow, etc...
 */

#include <FastLED.h>

//connect the potentiometer to pin A0
int potPin = A0;

//connections of the ChainableLED
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

//how long is the fade
int fadeDuration = 2000;
//keep track of last time we updated the led brightess
long lastLedUpdateTime = 0;
//how many steps from minumum brightess to maximum brightess
int fadesteps = 40;
//how often are we supposed to change the color of the Led
float fadeUpdateInterval=fadeDuration/fadesteps;
//are we fading towards the maximum brightess (+1) or towards the minumum brightess (-1)
int fadeDirection = 1;
//the maximum brightess
int fadeMax = 255;
//the minimum brightess
int fadeMin = 0;
//how much do we increase the brightess every step
float fadeAmountXStep = (fadeMax - fadeMin) / fadesteps;
//the led brightess
float brightness;

void setup() {
	//start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	float potValue = analogRead(potPin);
	int hue = map (potValue,0,1024,0,255);

	leds[0].setHue(hue);

	//if fadeUpdateInterval has passed, we have to update the brightess of the led
	if (millis() - lastLedUpdateTime > fadeUpdateInterval) {
		//update the brightess value
		brightness = brightness + fadeAmountXStep * fadeDirection;
		//if we reach the maximum value or the minimum, we reverse the direction
		if (brightness > fadeMax || brightness < fadeMin) {
			//make sure that the value is not outside the range
			brightness = constrain(brightness, fadeMin, fadeMax);
			//invert the direction
			fadeDirection *= -1;
		}
		lastLedUpdateTime = millis();
	}

	//update the led color
	leds[0].setHSV( hue, 255, brightness);
	FastLED.show();
}
