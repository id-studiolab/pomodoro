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
  setupSoundMachine(3);             // The buzzer is connected to pin 3
	setupServoMachine(4);             // The servo is connected to pin 4
  setupLedAnimationMachine();       // Check tab with lad_animation_machine for pin assignment
	
	// Setup printing to the console
	Serial.begin(9600);
}

void loop() {
	updatePomodoroMachine();
	updateSoundMachine();
	updateServoMachine();
  updateLedAnimationMachine();
}
