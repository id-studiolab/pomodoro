/*
   The following code demonstrates how to create beautiful
   asynchronous LEDs fading animations and how to switch between
   the different modalities

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your Seeeduino Lotus board
   -use the potentiometer to change color
   -press the button to switch animation
 */

#include <ChainableLED.h>

//connections
int ledPin1 = 4;
int ledPin2 = 5;

int potPin = A0;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

// asincronous animation
int animationDuration;
long lastLedUpdateTime;
int animationSteps;
float animationUpdateInterval;
float incrementAmountXStep;

int animationDirection = 1;

float maxBrightness = .5;
float minBrightness = 0;
float brightness;

float color_hue;

//button
int buttonAPin = 2;
boolean lastButtonAPressed;


//we offer multiple types of animation
enum animationType {
	SINGLE_COLOR,
	FADE,
	BLINK,
	RAINBOW,
	NONE,
};
animationType currentAnimation=NONE;
int numAnimations=5;

void setup() {
}

void loop() {
	//if the button is pressed we change animation
	if (readButtonA()) {
		//check that we are within the range of the the animations we programmed
		if (currentAnimation<numAnimations-1) {
			//since currentAnimation is a ENUM we cannot simply do currentAnimation++
			currentAnimation= (animationType)(currentAnimation + 1);
		}else{
			currentAnimation=0;
		}

		// start the right animation
		switch (currentAnimation) {
		case FADE:
			initFadeAnimation(2000,100);
			break;
		case SINGLE_COLOR:
			initSINGLE_COLORColor();
			break;
		case BLINK:
			// we can still use the initFadeAnimation setting the number of steps to 1
			initFadeAnimation(500,1);
			break;
		case RAINBOW:
			initFadeAnimation(1000,100);
			break;
		case NONE:
			stopAnimations();
			break;
		}
	}

	// if the animation is not of type rainbox set the color using the potentiometer
	if (currentAnimation!=RAINBOW) {
		float potValue = analogRead(potPin);
		color_hue = potValue / 1024;
	}

	//timing checks and led update is done inside this function
	updateLedAnimation();
}

// this function returns true when the button is pressed
boolean readButtonA(){
	boolean buttonStatus=false;
	boolean buttonAPressed=digitalRead(buttonAPin);
	if (buttonAPressed&&!lastButtonAPressed) {
		buttonStatus=true;
	}
	lastButtonAPressed=buttonAPressed;
	return(buttonStatus);
}

void initFadeAnimation(int animationDuration, int animationSteps){
	animationSteps=animationSteps;
	animationDuration=animationDuration;

	//recal the steps and the indervals
	animationUpdateInterval=animationDuration/animationSteps;
	incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
}

void stopAnimations(){
	//turn off
	brightness=0;
}

void initSINGLE_COLORColor(){
	//set the brightness to the max
	brightness=maxBrightness;
}

void updateFadeAnimation(){
	//increment the value of brightness
	brightness = brightness + incrementAmountXStep * animationDirection;
	//check that we havn't reached the extreme
	if (brightness > maxBrightness || brightness < minBrightness) {
		animationDirection *= -1;
		//make sure the value falls between the desired range
		brightness=constrain(brightness,minBrightness,maxBrightness);
	}
}

void initRainbowAnimation(int rainbowDuration, int rainbowSteps){
	color_hue=0;
	brightness=maxBrightness;
	animationSteps=rainbowSteps;
	animationDuration=rainbowDuration;

	animationUpdateInterval=animationDuration/animationSteps;
	incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
}

void updateRainbowAnimation(){
	//increment the hue
	color_hue+=1.0/animationSteps;
	//set the brightness to max
	brightness=maxBrightness;
	//reset the hue to 0 when we reach 1
	if (color_hue>1) {
		color_hue=0;
	}
}


void updateLedAnimation(){
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
	leds.setColorHSB(0, color_hue, 1.0, brightness);
}
