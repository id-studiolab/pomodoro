/*
   The following demonstrate how change to use the potentiometer
   to change the color of the led

   STEPS:
   -make sure you connected your chainable LED
   to the right pin on your seeduino Lotus

   TODO:
   Now the led color changes only at the begininning of the loop,
   can you make the color change at any time when turning the pot?
*/

#include <FastLED.h>

//connections
#define DATA_PIN 5
#define CLOCK_PIN 4

//how many leds
#define NUM_LEDS 1

//an array to hold the led data
CRGB leds[NUM_LEDS];

//we can have multipla type of animations
enum animationType{
  CROSSFADE,
  BLINK,
  RAINBOW,
  NONE
};

// asincronous fading
int fadeDuration=0;
long lastLedUpdateTime = 0;
int fadeSteps = 0;
long fadeUpdateInterval=0;

int red_direction=1;
int green_direction=1;
int blue_direction=1;

int red_amount;
int green_amount;
int blue_amount;

int fadeAmount;
// int fadeMax = 255;
// int fadeMin = 0;
// float fadeAmountXStep = (fadeMax - fadeMin) / fadeSteps;
// float brightness;

animationType animation=NONE;

// placeholders to save the colors to crossfade between
CRGB currentColor;
CRGB targetColor;
CRGB color1;
CRGB color2;


void setup() {
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  initCrossFadeAnimation(CRGB::Pink,CRGB::Blue, 1000, 40);
  Serial.begin(9600);
}

void loop() {
  //initCrossFadeAnimation(CRGB::Pink,CRGB::Blue, 5000, 40);
  updateLeds();
  // Serial.print(currentColor.red);
  // Serial.print(currentColor.green);
  // Serial.println(currentColor.blue);

  //delay(100);
}

void initCrossFadeAnimation(CRGB color_1,CRGB color_2, int fadeDuration, int fadeSteps){
  animation=CROSSFADE;
  color1=color_1;
  color2=color_2;

  fadeDuration=fadeDuration;
  fadeSteps=fadeSteps;
  fadeUpdateInterval=fadeDuration/fadeSteps;
  targetColor=color_2;
  currentColor=color_1;

  red_amount=abs(color1.red-color2.red)/fadeSteps;
  green_amount=abs(color1.green-color2.green)/fadeSteps;
  blue_amount=abs(color1.blue-color2.blue)/fadeSteps;

  recalcDirections();
}


void recalcDirections(){
  if (currentColor.red-targetColor.red>0){
    red_direction=-1;
  }else{
    red_direction=1;
  }
  if (currentColor.green-targetColor.green>0){
    green_direction=-1;
  } else{
    green_direction=1;
  }
  if (currentColor.blue-targetColor.blue>0){
    blue_direction=-1;
  } else{
    blue_direction=1;
  }
}


void updateLeds(){
  if (millis() - lastLedUpdateTime > fadeUpdateInterval) {

    switch (animation) {
      case NONE:
      break;

      case CROSSFADE:
      fadeTowardColor();
      break;

    }
    lastLedUpdateTime=millis();
  }

  leds[0]=currentColor;
  FastLED.show();
}



// Blend one CRGB color toward another CRGB color by a given amount.
// Blending is linear, and done in the RGB color space.

void fadeTowardColor(){

  if (targetColor==currentColor){
    Serial.println("time to change direction");

    if (targetColor==color1){
      Serial.println("new target is color2");
      targetColor=color2;
    }else if(targetColor==color2){
      targetColor=color1;
      Serial.println("new target is color1");
    }else{
      Serial.println("dunno");
    }

    recalcDirections();

  }

  CRGB newColor;
  int newRed=currentColor.red+(red_amount*red_direction);
  int newGreen=currentColor.green+(green_amount*green_direction);
  int newBlue=currentColor.blue+(blue_amount*blue_direction);

  newRed=constrain(newRed,min(color1.red,color2.red),max(color1.red,color2.red));
  newGreen=constrain(newGreen,min(color1.green,color2.green),max(color1.green,color2.green));
  newBlue=constrain(newBlue,min(color1.blue,color2.blue),max(color1.blue,color2.blue) );

  newColor.red=newRed;
  newColor.green=newGreen;
  newColor.blue=newBlue;

  currentColor= newColor;
}


