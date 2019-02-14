/*
   The is a self-contained file that has nicely packaged functionality
   to make LEDs shine in various animation styles. You can open it as a
   tab to another Arduino program (that contains the setup and loop functions.
 */
 
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

// multiple types of animation,
enum animationType {
	SINGLE_COLOR,
	FADE,
	BLINK,
	RAINBOW,
	NONE,
};

// the animation currently active
animationType currentAnimation = NONE;

void setHue(int hue) {
	color_hue=hue;
}


void startFadeAnimation(int animationDuration, int animationSteps) {
	currentAnimation = FADE;
	animationSteps = animationSteps;
	animationDuration = animationDuration;

	//recal the steps and the indervals
	animationUpdateInterval = animationDuration/animationSteps;
	incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
}

void stopAnimations() {
	//turn off
	brightness = 0;
	currentAnimation = NONE;
}

void startSingleColor() {
	//set the brightness to the max
	brightness = maxBrightness;
	currentAnimation = SINGLE_COLOR;
}

void updateFadeAnimation() {
	//increment the value of brightness
	brightness = brightness + incrementAmountXStep * animationDirection;
	//check that we havn't reached the extreme
	if (brightness > maxBrightness || brightness < minBrightness) {
		animationDirection *= -1;
		//make sure the value falls between the desired range
		brightness=constrain(brightness,minBrightness,maxBrightness);
	}
}

void startRainbowAnimation(int rainbowDuration, int rainbowSteps) {
	currentAnimation = RAINBOW;
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
		lastLedUpdateTime = millis();
	}
	//update the led color
	leds[0].setHSV(color_hue, 255, brightness);
	FastLED.show();
}
