// Tactile stimulation Acting Machine
// For documentation scroll to the end of the file.
// Created 2018, modified July 2019
// By Aadjan van der Helm and Lorenzo Romagnoli

// ---------------------------------------------- Libraries

// ---------------------------------------------- Variables

// Collection of states for Vibration Machine (vm)
const int vm_state_off = 0;
const int vm_state_on = 1;
const int vm_state_pulse = 2;
const int vm_state_smooth_pulse = 3;

// Remember the current state
int vm_current_state = vm_state_off;

// Variable remember the pin the vibration motor is connected to
int vm_vibration_pin = 0;

// Make it possible to track the passing of time
long vm_timer_duration = 1000;
long vm_timer_mark = 0;

// Variable to control blinking
int vm_pulse_state = 0;
int vm_pulse_update_tempo = 1000;

// Variables to control fading
long vm_smooth_pulse_duration = 2000;
int vm_smooth_pulse_steps = 40;
int vm_smooth_pulse_update_tempo = vm_smooth_pulse_duration / vm_smooth_pulse_steps;
int vm_smooth_pulse_direction = 1;
int vm_smooth_pulse_max = 255;
int vm_smooth_pulse_min = 0;
int vm_smooth_pulse_intensity_increment = (vm_smooth_pulse_max - vm_smooth_pulse_min) / vm_smooth_pulse_steps;
int vm_smooth_pulse_intensity = 0;

// ---------------------------------------------- Acting Machine utility functions

void setupVibrationMachine(int pin) {
	vm_vibration_pin = pin;
	vibrationOff();
}

void startVibrationOn() {
	vibrationOn();
	vm_current_state = vm_state_on;
}

void startVibrationPulse(int tempo) {
	vm_pulse_update_tempo = tempo / 2;
	vm_current_state = vm_state_pulse;
}

void startVibrationSmoothPulse(int tempo, int steps, int min, int max) {
	vm_smooth_pulse_min = min;
	vm_smooth_pulse_max = max;
	vm_smooth_pulse_steps = steps;
	vm_smooth_pulse_update_tempo = (tempo / 2) / steps;
	vm_current_state = vm_state_smooth_pulse;
}

void stopVibrationMachine() {
	vibrationOff();
	vm_current_state = vm_state_off;
}

// ---------------------------------------------- Acting Machine cause functions

boolean vmTimerExpired() {
	if (millis() - vm_timer_mark > vm_timer_duration)
		return true;
	else
		return false;
}

// ---------------------------------------------- Acting Machine effect functions

void vmTimerStart(long duration) {
	vm_timer_duration = duration;
	vm_timer_mark = millis();
}

void vibrationOn() {
	analogWrite(vm_vibration_pin, 255);
}

void vibrationOff() {
	analogWrite(vm_vibration_pin, 0);
}

void vibrationPulse() {
	if (vm_pulse_state == 0) {
		vm_pulse_state = 1;
		vibrationOn();
	}
	else {
		vm_pulse_state = 0;
		vibrationOff();
	}
}

void vibrationSmoothPulse() {
	// Increment (or decrement) the brightness one fade step
	vm_smooth_pulse_intensity = vm_smooth_pulse_intensity +
		vm_smooth_pulse_intensity_increment * vm_smooth_pulse_direction;
	
	// Brightness now outside min and max bounds -> then adjust and change direction
	if (vm_smooth_pulse_intensity > vm_smooth_pulse_max ||
		vm_smooth_pulse_intensity < vm_smooth_pulse_min) {
		
		vm_smooth_pulse_intensity =
			constrain(vm_smooth_pulse_intensity, vm_smooth_pulse_min, vm_smooth_pulse_max);
		vm_smooth_pulse_direction = vm_smooth_pulse_direction * -1;
	}
	
	analogWrite(vm_vibration_pin, vm_smooth_pulse_intensity);
}

// ---------------------------------------------- Acting Machine control flow

void updateVibrationMachine() {
	switch (vm_current_state) {
		// -------------------------------------- State off
		case vm_state_off :
		case vm_state_on :
			// Do nothing
			break;

		// -------------------------------------- State blink
		case vm_state_pulse :
			if (vmTimerExpired() == true) {
				vibrationPulse();
				vmTimerStart(lam_blink_update_tempo);
			}
			break;

		// -------------------------------------- State fade
		case vm_state_smooth_pulse :
			if (vmTimerExpired() == true) {
				vibrationSmoothPulse();
				vmTimerStart(vm_smooth_pulse_update_tempo);
			}
			break;


	}
	vmDebug(); // Keep track of the machine progress in the serial monitor
} // updateLedAnimationMachine

int vm_previous_state = vm_state_off;

void vmDebug() {
	if (vm_previous_state == vm_current_state)
		return;
	
	vm_previous_state = vm_current_state;
	
	switch (vm_current_state) {
		case vm_state_off :
			Serial.println("vm_state_off");
			break;
		case vm_state_on :
			Serial.println("vm_state_on");
			break;
		case vm_state_pulse :
			Serial.println("vm_state_pulse");
			break;
		case vm_state_smooth_pulse :
			Serial.println("vm_state_smooth_pulse");
			break;
		default :
			Serial.println("vibration machine - unknown state");
			break;
	} 
} // vmDebug

/* Documentation for the Vibration Acting Machine

This program is written as a subsystem of a functional interactive system, eg. 
the Positive Loop device or the Pomodoro Timer.

The vibration acting machine can be controlled by the following functions:

void setupVibrationMachine(int pin)
-----------------------------------
Prepare the Vibration Acting Machine for operations.

Parameter:
pin : the number of the pin that the vibration motor is connected to.

void startVibrationOn()
-----------------------
Switch the vibration motor to on.

void startVibrationPulse(int tempo)
-----------------------------------
Activate the pulse behaviour of the Vibration Acting Machine. This alternates the
intensity of vibration from min to max (just like the blinking of a led).

Parameter:
tempo : the duration in milliseconds of one cycle of the pulse behaviour, from on to off.

void startVibrationSmoothPulse(int tempo, int steps, int min, int max)
----------------------------------------------------------------------
Activate the smooth pulse behaviour of the vibration Acting Machine. This will
gradually increase and decrease the intensity of the vibration motor in the specified
tempo (in milliseconds).

Parameters:
tempo : the duration in milliseconds of one cycle of the smooth pulse behaviour. The
intensity of the vibration motor will be increased or decreased step-wise between the
minimum and maximum intensity value.
steps : the number of increment/decrement steps from min to max intensity.
min : the minimum intenstiy.
max : the maximum intenstiy.


void stopVibrationMachine()
-----------------------
Stop any previously started operation, switches the vibration motor to off.

*/
