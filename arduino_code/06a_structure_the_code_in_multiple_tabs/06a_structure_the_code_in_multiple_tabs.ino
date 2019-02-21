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
#include <Servo.h>

//connect the potentiometer to pin A0
int potPin = A0;

//connections of the ChainableLED
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

//button
int buttonPin = 2;
//the value that the button had in the previous loop()
boolean lastButtonPressed;

//how many animations do we have
int numAnimations = 5;
int activeMode = 0;


//here the code for the servo
int servoPin=6;
Servo myServo;


void setup() {
  //start the led library
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  myServo.attach(servoPin);
}

void loop() {
  //if the button is pressed we change animation
  if (readButtonA()) {
    //check that we are within the range of the the animations we programmed
    if (activeMode < numAnimations - 1) {
      activeMode++;
    } else {
      activeMode = 0;
    }
    //start the right animation
    switch (activeMode) {
      case 0: //one color to rule them all
        startSingleColor();
        break;
      case 1: //the blink
        //we can still use the initFadeAnimation setting the number of steps to 1
        startFadeAnimation(500, 1);
        
        startServoSweep(0,180,1000,100);
        break;
      case 2: //the fade
        startFadeAnimation(2000, 100);
        startServoSweep(60,120,200,1);

        break;
      case 3: //the rainbow
        startRainbowAnimation(1000, 100);
        break;
      case 4: //nothing
        stopAnimations();
        break;
    }
  }

  // if the animation is not of type rainbox set the color using the potentiometer
  if (activeMode != 3) {
    int potValue = analogRead(potPin);
    setHue(map(potValue, 0, 1024, 0, 255));
  }
  //timing checks and led update is done inside this function
  updateLedAnimation();
  updateServo();
}

// this function returns true when the button is pressed
boolean readButtonA() {
  boolean buttonStatus = false;
  boolean buttonPressed = digitalRead(buttonPin);
  
  //if the button is now down and the last time through the loop() is was not
  if (buttonPressed && !lastButtonPressed) {
    buttonStatus = true;
  }
  lastButtonPressed = buttonPressed;
  return (buttonStatus);
}
