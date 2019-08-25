// Main program file for the Pomodoro Timer Device
//
// Uses (check the tabs of your Arduino window):
//   pomodoro_machine.ino      - for the Acting Machine with Pomodoro behaviour
//   led_animation_machine.ino - to create various led animations
//   sound_machine.ino         - for playback of melodies
//   servo_machine.ino         - to create servo movement behaviour
//
// Created July 2019
// By Aadjan van der Helm and Lorenzo Romagnoli


// -------------------------------------- setup and loop
void setup() {	
	// Make sure all the Acting Machines are ready
	setupPomodoroMachine();
	setupLedAnimationMachine(); 	    // Check file with Led Animation Machine for pin assignment
	setupServoMachine(3);             // The servo is connected to pin 3
	setupSoundMachine(4); 			      // The buzzer is connected to pin 4
	
	// Setup printing to the console
	Serial.begin(9600);
}

void loop() {
	updatePomodoroMachine();
	updateLedAnimationMachine();
	updateSoundMachine();
	updateServoMachine();
}
