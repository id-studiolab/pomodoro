#include "pitches.h"


//some variables to animate the servo motor.
int notePlaying;

int tempo=1000;
int pauseBetweenNotes=100;

long lastNotePlayed=0;

int buzzerPin=3;

int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4,0};
int melodyLength=9;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4, 1};

int currentNote;
int currentNoteDuration;

boolean loopMelody=false;
boolean melodyPlaying=false;

void startMelody(int melody_tempo, boolean loop ){
	tempo=melody_tempo;
	loopMelody=loop;
	currentNote=0;
	currentNoteDuration=tempo/noteDurations[0];
	melodyPlaying=true;
}

void stopMelody(){
	melodyPlaying=false;
	noTone(buzzerPin);
}

void updateMelody(){
	if (melodyPlaying) {
		if (millis()-lastNotePlayed>currentNoteDuration) {

			if (currentNote==melodyLength&&loopMelody) {
				currentNote=0;
			}else if (currentNote==melodyLength&& !loopMelody) {
				melodyPlaying=false;
				noTone(buzzerPin);
			}

			currentNoteDuration=tempo/noteDurations[currentNote];
			tone(buzzerPin, melody[currentNote], currentNoteDuration-pauseBetweenNotes);
			lastNotePlayed=millis();

			currentNote++;
		}
	}
}
