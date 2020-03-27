// Sound playback Acting Machine (SOM)
// For documentation scroll to the end of this file.
// Created 2018, modified July 2019
// By Aadjan van der Helm and Lorenzo Romagnoli
//
// Sounds are PWM approximated square waves
// See also: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

// ---------------------------------------------- Libraries
// Reference the note frequencies
#include "pitches.h"

// ---------------------------------------------- Variables
int som_buzzer_pin = 3;

// -------------------------------------- sound animation machine
const int sound_melody_sad = 0;
const int sound_melody_happy = 1;
const int sound_melody_success = 2;

int success_melody_length = 9;
int success_melody_notes[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0};
int success_melody_tempo[] = {4, 8, 8, 4, 4, 4, 4, 4, 1};

int happy_melody_length = 5;
int happy_melody_notes[] = {NOTE_G4, NOTE_D7, NOTE_G4, NOTE_D7, 0};
int happy_melody_tempo[] = {4, 8, 4, 8, 1};

int sad_melody_length = 3;
int sad_melody_notes[] = {NOTE_G4, NOTE_D4, 0};
int sad_melody_tempo[] = {2, 2, 1};

int *som_current_melody_notes = NULL;
int *som_current_melody_tempo = NULL;
int som_current_melody_length = 0;
boolean som_repeat_melody = true;

int som_current_tempo = 0;
int som_current_note = 0;
int som_current_note_duration = 0;
int som_pause_between_notes = 100;

long som_timer_duration = 0;
long som_timer_mark = 0;

// Collection of states for sound machine (SOM)
const int som_state_off = 0;
const int som_state_play = 1;

int som_current_state = som_state_off;

// ---------------------------------------------- Acting Machine utility functions

void setupSoundMachine(int pin) {
	som_buzzer_pin = pin;
}

void startMelodySuccess(int tempo, boolean repeat) {
	startMelody(sound_melody_success, tempo, repeat);
}

void startMelodySad(int tempo, boolean repeat) {
	startMelody(sound_melody_sad, tempo, repeat);
}

void startMelodyHappy(int tempo, boolean repeat) {
	startMelody(sound_melody_happy, tempo, repeat);
}

void startMelody(int melody, int tempo, boolean repeat) {
	switch (melody) {
		case sound_melody_sad :
			som_current_melody_notes = sad_melody_notes;
			som_current_melody_tempo = sad_melody_tempo;
			som_current_melody_length = sad_melody_length;
			som_current_tempo = tempo;
			som_repeat_melody = repeat;
			som_current_note = 0;
			som_current_state = som_state_play;
			somTimerStart(0);
			break;
		case sound_melody_happy :
			som_current_melody_notes = happy_melody_notes;
			som_current_melody_tempo = happy_melody_tempo;
			som_current_melody_length = happy_melody_length;
			som_current_tempo = tempo;
			som_repeat_melody = repeat;
			som_current_note = 0;
			som_current_state = som_state_play;
			somTimerStart(0);
			break;
		case sound_melody_success :
			som_current_melody_notes = success_melody_notes;
			som_current_melody_tempo = success_melody_tempo;
			som_current_melody_length = success_melody_length;
			som_current_tempo = tempo;
			som_repeat_melody = repeat;
			som_current_note = 0;
			som_current_state = som_state_play;
			somTimerStart(0);
			break;
	}
}

void stopMelody() {
	noTone(som_buzzer_pin);
	som_current_melody_notes = NULL;
	som_current_melody_tempo = NULL;
	som_current_melody_length = 0;
	som_current_note = 0;
	som_repeat_melody = true;
	som_current_state = som_state_off;
}


// ---------------------------------------------- Acting Machine cause functions

boolean somTimerExpired() {
	if (millis() - som_timer_mark > som_timer_duration)
		return true;
	else
		return false;
}

// ---------------------------------------------- Acting Machine effect functions

void somTimerStart(long duration) {
	som_timer_duration = duration;
	som_timer_mark = millis();
}

void playNote() {
	if (som_current_note == som_current_melody_length) {
		if (som_repeat_melody != true) {
			som_current_state = som_state_off;
			return;
		}
		else {
			som_current_note = 0;
		}
	}
	
	som_current_note_duration = som_current_tempo / som_current_melody_tempo[som_current_note];
	tone(som_buzzer_pin, som_current_melody_notes[som_current_note],
		som_current_note_duration - som_pause_between_notes);
	
	som_current_note = som_current_note + 1;
}

// ---------------------------------------------- Acting Machine control flow

void updateSoundMachine () {
	switch (som_current_state) {

		// -------------------------------------- State off
		case som_state_off :
			// Do nothing - silence
			break;

		// -------------------------------------- State play
		case som_state_play :
			if (somTimerExpired() == true) {
				playNote();
				somTimerStart(som_current_note_duration);
			}
			
			break;
	}
	somDebug(); // Keep track of the machine progress in the serial monitor
} // updateSoundMachine

// Print the state name to the serial monitor only once
int som_previous_state = som_state_off;

void somDebug() {
	if (som_previous_state == som_current_state)
		return;

	som_previous_state = som_current_state;

	switch (som_current_state) {
		case som_state_off :
			Serial.println("som_state_off");
			break;
		case som_state_play :
			Serial.println("som_state_play");
			break;
		default :
			Serial.println("sound machine - unknown state");
			break;
	}
}

/* Documentation for the Sound Playback Acting Machine

This program is written as a subsystem of a functional interactive system, eg. 
the Positive Loop device or the Pomodoro Timer.

The Sound Playback Acting Machine can be controlled by the following functions:

void setupSoundMachine(int pin)
-------------------------------
Prepare the Sound Playback Acting Machine for operations.

Parameter:
pin : the number of the pin that the speaker/buzzer is connected to.

void startMelody(int melody, int tempo, boolean repeat)
-------------------------------------------------------
Play the specified melody (array of notes) in the specified tempo time. The repeat
parameter determines if the melody is looped when playback reaches the end.

Parameters:

melody : a integer number identifying one of the defined melodies. In our example we
have created success (=0), happy (=1) and sad (=2). With the help of the include file
pitches.h it is possible to define your own melodies.

tempo : the duration in milliseconds of one full melody cycle. A tempo of 1000
milliseconds will play the melody twice as fast as a tempo of 2000.

repeat : If true the melody is repeated when playback reaches the end, if false melody
playback will stop once the melody is finished playing.

void stopMelody()
-----------------
Stop playback.

*/
