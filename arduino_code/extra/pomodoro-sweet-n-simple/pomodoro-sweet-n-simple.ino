// Pomodoro Acting Machine
// A Pomodoro timer helps a user to structure his/her work activities by mixing focussed
// work with break moments.
// Check: https://en.wikipedia.org/wiki/Pomodoro_Technique
//
// Created September 2019
// By Aadjan van der Helm, Lorenzo Romagnoli & Dieter Vandoren

// ---------------------------------------------- Libraries

#include <FastLED.h>

// ---------------------------------------------- Variables 

// Connections of the ChainableLED
#define CLOCK_PIN 7
#define DATA_PIN 8

// How many leds
#define NUM_LEDS 1

// An array to hold the led data
CRGB leds[NUM_LEDS];

// Collection of states for Pomodoro Acting Machine (pam)
const int state_idle = 0;
const int state_work = 1;
const int state_break_alarm = 2;
const int state_short_break = 3;
const int state_work_alarm = 4;
const int state_long_break = 5;

// Remember the current state
int current_state = 0;

// Make it possible to track the passing of time
unsigned long timer_duration = 1000;
unsigned long timer_mark = 0;

// Variables for state durations
unsigned long work_duration = 5000; // 5 seconds for quick testing, for real use 1200000 = 20*60*1000 = 20 minutes
unsigned long short_break_duration = 3000; // 300000 = 5*60*1000 = 5 minutes

// Variables to track button state
boolean button_status = false;
boolean button_current_state = false;
boolean last_button_state = false;
int button_pin = 2;

// Variable to remember the pin the buzzer is connected to
int buzzer_pin = 3;

// Count the number of breaks
int break_counter = 0;

// Variable for tracking state changes for debugging
int previous_state = state_idle;

// ---------------------------------------------- Setup and loop

void setup () {
  // Start serial connection
	Serial.begin(9600);

  // Initialize Chainable LED
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS); 

  leds[0].setRGB(0, 0, 0);
  FastLED.show();
}

void loop () {
	updatePomodoroMachine();
}

// ---------------------------------------------- Acting Machine cause functions

boolean timerExpired() {
	if (millis() - timer_mark > timer_duration)
		return true;
	else
		return false;
}

// Return true once when button is pressed (moves from up to down state)
boolean buttonPress() {
  button_status = false;
  button_current_state = digitalRead(button_pin);
  
	if (button_current_state && !last_button_state) {
		button_status = true;
	}
	last_button_state = button_current_state;
	return(button_status);
}

// ---------------------------------------------- Acting Machine effect functions

void timerStart(unsigned long duration) {
	timer_duration = duration;
	timer_mark = millis();
}

void setLedColor(int r, int g, int b){
  leds[0].setRGB(r, g, b);
  FastLED.show();
}

void setBuzzer(boolean i){
  if(i == 0)
    analogWrite(buzzer_pin, 0);
  else
    analogWrite(buzzer_pin, 128);
}

// ---------------------------------------------- Acting Machine control flow

void updatePomodoroMachine ()
{
	switch (current_state) {			
		// -------------------------------------- State idle
		case state_idle :
			if (buttonPress() == true) {      
        setLedColor(0, 255, 0);       
				timerStart(work_duration);
				current_state = state_work;
			}
			break;
			
		// -------------------------------------- State work
		case state_work :
			if (timerExpired() == true) {
        setLedColor(255,0,0);  
        setBuzzer(1);
				current_state = state_break_alarm;			
			}
			break;
			
		// -------------------------------------- State break alarm
		case state_break_alarm :
			if (buttonPress() == true) {
				if (break_counter < 3) {
					setBuzzer(0);
					break_counter = break_counter + 1;
          setLedColor(0, 0, 255);  
					timerStart(short_break_duration);
					current_state = state_short_break;
				}
				else {
					setBuzzer(0);
          setLedColor(255, 255, 255);  
					break_counter = 0;
					current_state = state_long_break;			
				}
			}
			break;

		// -------------------------------------- State short break
		case state_short_break :
			if (timerExpired() == true) {
        setLedColor(255, 50, 50);
				setBuzzer(1);
				current_state = state_work_alarm;
			}
			break;
			
		// -------------------------------------- State work alarm
		case state_work_alarm :
			if (buttonPress() == true) {
				setBuzzer(0);
        setLedColor(0, 255, 0);
				timerStart(work_duration);
				current_state = state_work;
			}
			break;
			
		// -------------------------------------- State long break
		case state_long_break :
			if (buttonPress() == true) {
				setBuzzer(0);
        setLedColor(0, 0, 0);
				current_state = state_idle;
			}
			break;
	}
	debugPam();
} // updatePomodoroMachine


// ------------------------------------------- Debug helper function 
// Prints state change to serial monitor. This is complete. Do not edit.
void debugPam() {
 
	if (previous_state == current_state)
		return;  // We are in the same state as last time - we don't print again and exit the function
	
	previous_state = current_state;
	
	switch (current_state) {
		case state_idle :
			Serial.println("state_idle");
			break;
		case state_work :
			Serial.println("state_work");
			break;
		case state_break_alarm :
			Serial.println("state_break_alarm");
			break;
		case state_short_break :
			Serial.println("state_short_break");
			break;
		case state_work_alarm :
			Serial.println("state_work_alarm");
			break;
		case state_long_break :
			Serial.println("state_long_break");
			break;
		default :
			Serial.println("unknown state");
			break;
	} 
} // debugPam
