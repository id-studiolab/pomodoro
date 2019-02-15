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

 
int brightness=0;
long lastTimeUpdate=0;

int fadeDuration=2000;
int steps=100;

int minBrightness=0;
int maxBrightness=255;

int brightnessIncrement=(maxBrightness-minBrightness)/steps;
int stepDuration=fadeDuration/steps;

int fadeDirection=1;

void setup() {
	//start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {

  if(millis()-lastTimeUpdate>stepDuration){
    brightness=brightness+brightnessIncrement*fadeDirection;

    if (brightness>maxBrightness || brightness< minBrightness){
      fadeDirection=fadeDirection*-1;
    }

    brightness=constrain(brightness,minBrightness,maxBrightness);
    lastTimeUpdate=millis();
  }
  
	float potValue = analogRead(potPin);
	int hue = map (potValue,0,1024,0,255);

	leds[0].setHue(hue);
	FastLED.setBrightness(brightness);
	FastLED.show();
	
}
