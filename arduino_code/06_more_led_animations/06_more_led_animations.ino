/*
   The following code demonstrates how to create beautiful
   asynchronous LED fading animations and how to switch between
   different modes of animation

   STEPS:
   -Make sure you connect your ChainableLED
   to the right pin on your Seeeduino Lotus
   -Use the potentiometer to change color
   -Press the button to change the animation
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

//how long is the animation
int animationDuration = 2000;
//keep track of last time we updated the led brightness
long lastLedUpdateTime = 0;
//how many steps has the animation
int animationSteps = 40;
//how often are we supposed to change the color of the led
float animationUpdateInterval = animationDuration/animationSteps;
//is our animation moving forward or backward
int animationDirection = 1;
//the maximum & minimum brightness, mainy needed for fade animation
int maxBrightness = 255;
int minBrightness = 0;
//how much do we change the color at every step of the animation
float incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
//the led brightness
int brightness;
int color_hue;

//button
int buttonPin = 2;
//the value that the button had in the previous loop()
boolean lastButtonPressed;

//multiple types of animation
enum animationType {
	SINGLE_COLOR,
	FADE,
	BLINK,
	RAINBOW,
	NONE,
};

//the animation currently active
animationType currentAnimation=NONE;
//how many animations do we have
int numAnimations=5;

void setup() {
	//start the led library
	FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
	//if the button is pressed we change animation
	if (readButtonA()) {
		//check that we are within the range of the the animations we programmed
		if (currentAnimation<numAnimations-1) {
			//since currentAnimation is a ENUM we cannot simply do currentAnimation++
			currentAnimation = (animationType)(currentAnimation + 1);
		}else{
			currentAnimation = 0;
		}

		// start the right animation
		switch (currentAnimation) {
		case SINGLE_COLOR:
			startSingleColor();
			break;
		case FADE:
			startFadeAnimation(2000,100);
			break;
		case BLINK:
			//we can still use the initFadeAnimation setting the number of steps to 1
			startFadeAnimation(500,1);
			break;
		case RAINBOW:
			startFadeAnimation(1000,100);
			break;
		case NONE:
			stopAnimations();
			break;
		}
	}

	//if the animation is not of type rainbox set the color using the potentiometer
	if (currentAnimation!=RAINBOW) {
		float potValue = analogRead(potPin);
		color_hue = map(potValue, 0,1024,0,255);
	}

	//timing checks and led update is done inside this function
	updateLedAnimation();
}

//this function returns true when the button is pressed
boolean readButtonA(){
	boolean buttonStatus=false;
	boolean buttonPressed=digitalRead(buttonPin);
	
  //if the button is now down and the last time through the loop() is was not
	if (buttonPressed && !lastButtonPressed) {
		buttonStatus=true;
	}
	lastButtonPressed=buttonPressed;
	return(buttonStatus);
}

void startFadeAnimation(int animationDuration, int animationSteps){
	animationSteps=animationSteps;
	animationDuration=animationDuration;

	//recall the steps and the intervals
	animationUpdateInterval=animationDuration/animationSteps;
	incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
}

void stopAnimations(){
	//turn off
	brightness=0;
}

void startSingleColor() {
	//set the brightness to the max
	brightness=maxBrightness;
}

void updateFadeAnimation() {
	//increment the value of brightness
	brightness = brightness + incrementAmountXStep * animationDirection;
	//check that we havn't reached the extreme
	if (brightness > maxBrightness || brightness < minBrightness) {
		animationDirection *= -1;
		//make sure the value falls between the desired range
		brightness = constrain(brightness,minBrightness, maxBrightness);
	}
}

void startRainbowAnimation(int rainbowDuration, int rainbowSteps){
	color_hue = 0;
	brightness = maxBrightness;
	animationSteps = rainbowSteps;
	animationDuration = rainbowDuration;

	animationUpdateInterval = animationDuration/animationSteps;
	incrementAmountXStep = 255 / animationSteps;
}

void updateRainbowAnimation() {
	//increment the hue
	color_hue += incrementAmountXStep*animationDirection;
	//set the brightness to max
	brightness = maxBrightness;
	//reset the hue to 0 when we reach 1
	if (color_hue > 255) {
		color_hue = 0;
	}
}

void updateLedAnimation() {
	if (millis() - lastLedUpdateTime > animationUpdateInterval) {
		switch (currentAnimation) {
		case NONE:
			break;
      
		case FADE:
			updateFadeAnimation();
			break;

		case BLINK:
			updateFadeAnimation();
			break;

		case RAINBOW:
			updateRainbowAnimation();
			break;
		}
		lastLedUpdateTime=millis();
	}

	//update the led color
	leds[0].setHSV(color_hue, 255, brightness);
	FastLED.show();
}
