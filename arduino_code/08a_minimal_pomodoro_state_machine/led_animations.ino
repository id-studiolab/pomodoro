//Led animations variables
int animationDuration;
long lastLedUpdateTime;
int animationSteps;
float animationUpdateInterval;
float incrementAmountXStep;

int animationDirection = 1;

float maxBrightness = .5;
float minBrightness = 0;

float color_hue;
float saturation;
float brightness;

//we offer multiple types of animation
enum animationType {
	SOLID,
	FADE,
	BLINK,
	RAINBOW,
	NONE,
};

animationType currentAnimation=NONE;
int numAnimations=5;

void setHue(float h){
	color_hue=h/255;
}
void setSaturation(float s){
	saturation=s/255;
}
void setBrightness(float b){
	brightness=b/255;
}
void setHSB(float h, float s, float b){
	setHue(h);
	setSaturation(s);
	setBrightness(b);
}

void initFadeAnimation(int animationDuration, int animationSteps){
	currentAnimation=FADE;
	animationSteps=animationSteps;
	animationDuration=animationDuration;

	//recal the steps and the indervals
	animationUpdateInterval=animationDuration/animationSteps;
	incrementAmountXStep = (maxBrightness - minBrightness) / animationSteps;
}

void stopAnimations(){
	//turn off
	brightness=0;
	currentAnimation=NONE;
}

void initSolidColor(){
	//set the brightness to the max
	brightness=maxBrightness;
	currentAnimation=SOLID;
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
	currentAnimation=RAINBOW;

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
	leds.setColorHSB(0, color_hue, saturation, brightness);
}
