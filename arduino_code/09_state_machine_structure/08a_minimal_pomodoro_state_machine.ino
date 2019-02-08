// ---------------
// -- Libraries --
// ---------------
#include <Servo.h>
#include <ChainableLED.h>


// ---------------
// -- Variables --
// ---------------

//pin Variables
const int buttonAPin = 2;
const int buttonBPin = 3;
const int potPin = A0;
const int servoPin = 6;

const int ledPin1 = 4;
const int ledPin2 = 5;

//create a servo object
Servo myServo;

//create a ChainableLED object
#define NUM_LEDS  1
ChainableLED leds(ledPin1, ledPin2, NUM_LEDS);

// State Machine Variables
const int stateIdle = 0;
const int stateWork = 1;
const int stateAlarm = 2;
const int stateShort_break = 3;
const int stateLong_break = 4;
const int stateAlarm2 = 5;

int currentState = stateIdle;

// Timer variables
unsigned long timerDuration;
unsigned long lastTimerStarted;

int preAlarmLevel = 0;
int alarmlevel = 0;

// const long focusWorkDuration=1000*60*20; //20 minutes
// const long shortBreakDuration=1000*60*5; //20 minutes
// const long longBreakDuration=1000*60*15; //20 minutes

const long focusWorkDuration=5000; //20 minutes
const long shortBreakDuration=5000; //20 minutes
const long longBreakDuration=5000; //20 minutes

//buttons Variables
boolean lastButtonAPressed;

//break Variables
int nBreaks=0;

// ------------------
// -- Setup & Loop --
// ------------------

void setup() {
	//define input/output pins
	pinMode(buttonAPin, INPUT);
	pinMode(buttonBPin, INPUT);
	pinMode(potPin, INPUT);

	//start the servo
	myServo.attach(servoPin);

	//start the serial port
	Serial.begin (9600);
}

void loop() {
	updateStateMachine();
	updateLedAnimation();
}

// ----------------
// -- Conditions --
// ----------------

boolean buttonPress() {
	boolean buttonStatus=false;
	boolean buttonAPressed=digitalRead(buttonAPin);
	if (buttonAPressed&&!lastButtonAPressed) {
		buttonStatus=true;
	}
	lastButtonAPressed=buttonAPressed;
	return(buttonStatus);
}

boolean timerExpired() {
	if (millis()-lastTimerStarted>timerDuration) {
		return true;
	}else{
		return false;
	}
}

int checkBreak(){
	return nBreaks;
}


// -------------
// -- Actions --
// -------------

void startTimer(int msec) {
	timerDuration = msec;
	lastTimerStarted = millis();
}

void updateServo(){
	int timeRemaining=lastTimerStarted+timerDuration-millis();
	int servoPosition=map(timeRemaining, 0,timerDuration,0,180);
	myServo.write(servoPosition);
}



// -------------
// -- Utility --
// -------------

void goToState(int state){
	currentState=state;
	Serial.print("going to state:");
	Serial.print('\t');
	Serial.println(currentState);
}

// --------------------
// -- State Machines --
// --------------------

void updateStateMachine() {
	switch (currentState) {

	case stateIdle:
		if (buttonPress()) {
			startTimer(focusWorkDuration);
			setHSB(255,0,255);
			initFadeAnimation(1000,100);
			goToState(stateWork);
			break;
		}
		break;

	case stateWork:
		updateServo();
		if (timerExpired()) {
			goToState(stateAlarm);
			setHSB(100,100,255);
			initFadeAnimation(500,1);
			break;
		}
		if (buttonPress()) {
			goToState(stateIdle);
			break;
		}
		break;

	case stateAlarm:
		if (buttonPress()) {
			nBreaks++;
			if (checkBreak()<4) {
				startTimer(shortBreakDuration);
				goToState(stateShort_break);
				setBrightness(100);
				initRainbowAnimation(5000,20);
				break;
			}
			if (checkBreak()==4) {
				startTimer(longBreakDuration);
				goToState(stateLong_break);
				setBrightness(255);
				initRainbowAnimation(5000,100);
				break;
			}
		}
		break;


	case stateShort_break:
		updateServo();

		if (timerExpired()) {
			goToState(stateAlarm2);
		}
		break;

	case stateLong_break:
		updateServo();

		if (timerExpired()) {
			goToState(stateAlarm2);
		}
		break;

	case stateAlarm2:
		if(buttonPress()) {
			goToState(stateWork);
			startTimer(focusWorkDuration);
			setHSB(255,0,255);
			initFadeAnimation(1000,100);
		}
		break;
	}
}
