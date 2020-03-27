// Servo Acting Machine (SEM)
// For documentation scroll to the end of this file.
// Created 2018, modified July 2019
// By Aadjan van der Helm and Lorenzo Romagnoli

// ---------------------------------------------- Libraries
#include <Servo.h>

// ---------------------------------------------- Variables
Servo sem_object;

// Collection of states for servo machine (SEM)
const int sem_state_off = 0;
const int sem_state_moveto = 1;
const int sem_state_sweep = 2;

int sem_current_state = sem_state_off;

long sem_timer_duration = 0;
long sem_timer_mark = 0;

// Range of servo movement is [0-180] degrees
int sem_min;
int sem_max;
int sem_step_degrees = 0;
int sem_update_tempo = 0;

int sem_position = 0;
int sem_moveto_position = 0;
int sem_direction = 1;

// ---------------------------------------------- Acting Machine utility functions

void setupServoMachine(int servo_pin) {
	sem_object.attach(servo_pin);
}

void startServoSweep(int min_position, int max_position, int tempo, int steps) {
	sem_min = min_position;
	sem_max = max_position;
	sem_update_tempo = tempo / steps;
	sem_step_degrees = abs(max_position - min_position) / steps;
	sem_position = 0;
	sem_direction = 1;
	sem_current_state = sem_state_sweep;			
}

void startServoMoveto(int moveto_position, int tempo, int steps) {
	sem_moveto_position = moveto_position;
	sem_update_tempo = tempo / steps;
	sem_step_degrees = abs(moveto_position - sem_position) / steps;			
	sem_current_state = sem_state_moveto;			
}

void stopServoAnimation() {
	sem_current_state = sem_state_off;
}

// ---------------------------------------------- Acting Machine cause functions
boolean semTimerExpired() {
	if (millis() - sem_timer_mark > sem_timer_duration)
		return true;
	else
		return false;
}

// ---------------------------------------------- Acting Machine effect functions

void semTimerStart(long duration) {
	sem_timer_duration = duration;
	sem_timer_mark = millis();
}

// ---------------------------------------------- Acting Machine control flow

void updateServoMachine () {
	switch (sem_current_state) {

		// -------------------------------------- State off
		case sem_state_off :
			// Do nothing
			break;

		// -------------------------------------- State moveto
		case sem_state_moveto :
			if (semTimerExpired() == true) {
				if (((sem_direction == 1) && (sem_position > sem_moveto_position)) ||
					((sem_direction == -1) && (sem_position < sem_moveto_position))) {
					sem_position = sem_moveto_position;
					sem_current_state = sem_state_off;
					break;					
				}
				sem_object.write(sem_position);
				semTimerStart(sem_update_tempo);
			}
			break;

		// -------------------------------------- State moveto
		case sem_state_sweep :
			if (semTimerExpired() == true) {
				sem_position = sem_position + sem_step_degrees * sem_direction;
				if ((sem_position > sem_max) || (sem_position < sem_min)) {
					sem_direction = sem_direction * -1;
					sem_position = constrain(sem_position, sem_min, sem_max);
				}
				sem_object.write(sem_position);
				semTimerStart(sem_update_tempo);
			}
			break;
	}
	semDebug(); // Keep track of the machine progress in the serial monitor
} // updateSoundMachine

// Print the state name to the serial monitor only once
int sem_previous_state = sem_state_off;
void semDebug() {
	if (sem_previous_state == sem_current_state)
		return;

	sem_previous_state = sem_current_state;

	switch (sem_current_state) {
		case sem_state_off :
			Serial.println("sem_state_off");
			break;
		case sem_state_moveto :
			Serial.println("sem_state_moveto");
			break;
		case sem_state_sweep :
			Serial.println("sem_state_sweep");
			break;
		default :
			Serial.println("servo machine - unknown state");
			break;
	}
}


/* Documentation for the Servo Acting Machine

This program is written as a subsystem of a functional interactive system, eg. 
the Positive Loop device or the Pomodoro Timer.

The Sound Playback Acting Machine can be controlled by the following functions:

void setupServoMachine(int pin)
-------------------------------
Prepare the Servo Acting Machine for operations.

Parameter:

pin : the number of the pin that the servo is connected to.

void startServoSweep(int min_position, int max_position, int tempo, int steps)
------------------------------------------------------------------------------
Move the Servo continuously between the min_position and max_position in the specified
tempo (time in milliseconds), approximate the movement with a number of steps.
Tempo controls the time it takes from min_position to max_position, steps controls
the fluency of the movement, where a higher number of steps will cause smaller movements
and hence a more fluent movement patterns.

Parameters:

min_position : minimum angular position of the shaft of the servo [0-180]

max_position : maximum angular position of the shaft of the servo [0-180]

int tempo : the time in milliseconds it takes to move from min_position to max_position

int steps : the number of steps taken from min_position to max_postion.

void startServoMoveto(int moveto_position, int tempo, int steps)
----------------------------------------------------------------
Move the servo to the moveto_position in the time specified by tempo (milliseconds). The
movement will be effected in a granular fashion depending on the number specified by
steps. A steps value of 2 will make the servo move twice for this startServoMoveto
command, A steps value of 20 will make the movement much more gradual and result in
20 steps for the current startServoMoveto command. Once the moveto_position is reached
the Servo Acting Machine will stop.

Parameters:

moveto_position : the destination angular position of the shaft of the servo.

tempo : the time in milliseconds it takest to move to the specified moveto position.

steps : the number of steps taken to reach the specified position

void stopMelody()
-----------------
Stop any playback.

*/
