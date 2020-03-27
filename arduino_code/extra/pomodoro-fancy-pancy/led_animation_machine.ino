// Led animation Acting Machine
// For documentation scroll to the end of this file.
// Created 2018, modified July 2019
// By Aadjan van der Helm and Lorenzo Romagnoli

// ---------------------------------------------- Libraries
#include <FastLED.h>

// ---------------------------------------------- Variables
// Variable to control the Chainable LEDs attached to D7
const int lam_num_leds = 1;
CRGB leds[lam_num_leds];

// Collection of states for Led Animation Machine (lam)
const int lam_state_off = 0;
const int lam_state_on = 1;
const int lam_state_blink = 2;
const int lam_state_fade = 3;
const int lam_state_rainbow = 4;

// Remember the current state
int lam_current_state = lam_state_off;

// Make it possible to track the passing of time
long lam_timer_duration = 1000;
long lam_timer_mark = 0;

// Variable to control blinking
int lam_blink_state = 0;
int lam_blink_update_tempo = 1000;

// Variables to control fading
long lam_fade_duration = 2000;
int lam_fade_steps = 40;
int lam_fade_update_tempo = lam_fade_duration / lam_fade_steps;
int lam_fade_direction = 1;
int lam_fade_max = 255;
int lam_fade_min = 0;
int lam_fade_brightness_increment = (lam_fade_max - lam_fade_min) / lam_fade_steps;
int lam_fade_brightness = 0;

// Variable to control the color rainbow
long lam_rainbow_update_tempo = 50;
int lam_rainbow_hue_step = 10;

// Variable to control led color [0..255]
// red=0 orange=32 yellow=64 green=96 blue=160 purple=192 pink=224
int lam_led_hue = 96;

// ---------------------------------------------- Acting Machine utility functions
const int clock_pin = 7;
const int data_pin = 8;

void setupLedAnimationMachine() {
	// Setup the led library - ChainableRGB led in D7
  FastLED.addLeds<P9813, data_pin, clock_pin, RGB>(leds, lam_num_leds);
	ledOff();
}

void startLedAnimationOn(int hue) {
	lam_led_hue = hue;
	ledOn();
	lam_current_state = lam_state_on;
}

void startLedAnimationBlink(int hue, int tempo) {
	lam_led_hue = hue;
	lam_blink_update_tempo = tempo / 2;
	lam_current_state = lam_state_blink;
}

void startLedAnimationFade(int hue, int tempo) {
	lam_led_hue = hue;
	lam_fade_update_tempo = (tempo / 2) / lam_fade_steps;
	lam_current_state = lam_state_fade;
}

void startLedAnimationRainbow(int tempo) {
	lam_rainbow_update_tempo = tempo;
	lam_current_state = lam_state_rainbow;
}


void stopLedAnimation() {
	ledOff();
	lam_current_state = lam_state_off;
}

// ---------------------------------------------- Acting Machine cause functions

boolean lamTimerExpired() {
	if (millis() - lam_timer_mark > lam_timer_duration)
		return true;
	else
		return false;
}

// ---------------------------------------------- Acting Machine effect functions

void lamTimerStart(long duration) {
	lam_timer_duration = duration;
	lam_timer_mark = millis();
}

void ledOn() {
	for (int i = 0; i < lam_num_leds; i++)
		leds[i].setHSV(lam_led_hue, 255, 255);
	FastLED.show();
}

void ledOff() {
	for (int i = 0; i < lam_num_leds; i++)
		leds[i].setHSV(lam_led_hue, 255, 0);
	FastLED.show();
}

void ledBlink() {
	if (lam_blink_state == 0) {
		lam_blink_state = 1;
		ledOn();
	}
	else {
		lam_blink_state = 0;
		ledOff();
	}
}

void ledFade() {
	// Increment (or decrement) the brightness one fade step
	lam_fade_brightness = lam_fade_brightness +
		lam_fade_brightness_increment * lam_fade_direction;
	
	// Brightness now outside min and max bounds -> then adjust and change direction
	if (lam_fade_brightness > lam_fade_max || lam_fade_brightness < lam_fade_min) {
		lam_fade_brightness = constrain(lam_fade_brightness, lam_fade_min, lam_fade_max);
		lam_fade_direction = lam_fade_direction * -1;
	}
	
	for (int i = 0; i < lam_num_leds; i++)
		leds[i].setHSV(lam_led_hue, 255, lam_fade_brightness);
	FastLED.show();
}

void ledRainBow(){
	// Increment the HSV angle (=hue) max is 255
	lam_led_hue = lam_led_hue + lam_rainbow_hue_step;
	if (lam_led_hue > 255)
		lam_led_hue = 0;
		
	for (int i = 0; i < lam_num_leds; i++)
		leds[i].setHSV(lam_led_hue, 255, 255);
	FastLED.show();	
}

// ---------------------------------------------- Acting Machine control flow

void updateLedAnimationMachine() {
	switch (lam_current_state) {
		// -------------------------------------- State off
		case lam_state_off :
		case lam_state_on :
			// Do nothing
			break;

		// -------------------------------------- State blink
		case lam_state_blink :
			if (lamTimerExpired() == true) {
				ledBlink();
				lamTimerStart(lam_blink_update_tempo);
			}
			break;

		// -------------------------------------- State fade
		case lam_state_fade :
			if (lamTimerExpired() == true) {
				ledFade();
				lamTimerStart(lam_fade_update_tempo);
			}
			break;

		// -------------------------------------- State rainbow
		case lam_state_rainbow :
			if (lamTimerExpired() == true) {
				ledRainBow();
				lamTimerStart(lam_rainbow_update_tempo);
			}
			break;

	}
	lamDebug(); // Keep track of the machine progress in the serial monitor
} // updateLedAnimationMachine

int lam_previous_state = lam_state_off;

void lamDebug() {
	if (lam_previous_state == lam_current_state)
		return;
	
	lam_previous_state = lam_current_state;
	
	switch (lam_current_state) {
		case lam_state_off :
			Serial.println("lam_state_off");
			break;
		case lam_state_on :
			Serial.println("lam_state_on");
			break;
		case lam_state_blink :
			Serial.println("lam_state_blink");
			break;
		case lam_state_fade :
			Serial.println("lam_state_fade");
			break;
		case lam_state_rainbow :
			Serial.println("lam_state_rainbow");
			break;
		default :
			Serial.println("led animation machine - unknown state");
			break;
	} 
} // lamDebug

/* Documentation for the led animation Acting Machine

This program is written as a subsystem of a functional interactive system, eg. 
the Positive Loop device or the Pomodoro Timer.

This Acting Machine written to control leds to and to perform a number of dynamic
effects. It can turn leds on (and off), blink at a desired tempo, performing brightness
intensity fading and display a rainbow of colors in  a specified tempo. Make sure to
regularly call the updateLedAnimationMachine function, otherwise the dynamic quality
can not be guaranteed. All behaviour will be continue until stopped or changed into a
different behaviour.

It is currently set to use the FastLED library with Grove Chainable RGB leds (P9813).
The value of lam_num_leds determines how much leds the Acting Machine will attempt to
control.

The led animation acting machine can be controlled by the following functions

void setupLedAnimation(int pin)
-------------------------------
Prepare the led animation Acting Machine to start performing any of the 5 possible 
operations (on, off, blink, fade, rainbow). Subsequent invocations to
updateLedAnimationMachine (from the loop()) will perform the necessary steps required.

Parameter:

pin : the pin the leds are connected to. Note: setup will also claim the next pin because
most leds require actually two pins (data and clock).

void startLedAnimationOn(int hue)
---------------------------------
Initiate the on behaviour of the led animation Acting Machine.

Parameter:

hue : the color hue value [0 - 255] of the light.

void startLedAnimationBlink(int hue, int tempo)
-----------------------------------------------
Initiate the blink behaviour ot the led animation Acting Machine.

Parameters:

hue : the color hue value [0 - 255] of the light.

tempo : the duration in milliseconds of one full blink cycle (on delay off delay).

void startLedAnimationFade(int hue, int tempo)
----------------------------------------------
Initiate the fade behaviour of the led animation Acting Machine.

Parameters:

hue : the color hue value [0 - 255] of the light.

tempo : the duration in milliseconds of one full fade cycle (from min to max brightness).

void startLedAnimationRainbow(int tempo)
----------------------------------------
Initiate the colorful rainbow behaviour of the led animation Acting Machine. 

Parameter:

tempo: the duration in milliseconds to go from one to the next color.

void stopLedAnimation()
-----------------------
Stop any previously started operation, switches the led to off.

*/
