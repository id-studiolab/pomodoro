#include "pitches.h"

int notePlaying;

int tempo=1000;
int pauseBetweenNotes=100;

long lastNotePlayed=0;

int buzzerPin=3;

int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4,0};
int melodyLength=9;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4, 1};

int happyMelody[]={NOTE_G4,NOTE_D7,NOTE_G4,NOTE_D7,0};
int happyMelodyLength=5;
int happyNoteDurations[] = { 4, 8, 4, 8, 1};

int sadMelody[]={NOTE_G4,NOTE_D4,0};
int sadMelodyLength=3;
int sadNoteDurations[] = {2,2,1};

int currentNote;
int currentNoteDuration;

boolean loopMelody=false;
boolean melodyPlaying=false;


enum melodyType {
	SONG,
	HAPPY,
	SAD,
	NOSOUND
};

melodyType currentMelody=NOSOUND;


void startSongMelody(int melody_tempo, boolean loop ){
	tempo=melody_tempo;
	loopMelody=loop;
	currentNote=0;
	currentNoteDuration=tempo/noteDurations[0];
	melodyPlaying=true;
	currentMelody=SONG;
}

void startHappyMelody(int melody_tempo, boolean loop){
	tempo=melody_tempo;
	loopMelody=loop;
	currentNote=0;
	currentNoteDuration=tempo/happyNoteDurations[0];
	melodyPlaying=true;
	currentMelody=HAPPY;
}

void startSadMelody(int melody_tempo, boolean loop){
	tempo=melody_tempo;
	loopMelody=loop;
	currentNote=0;
	currentNoteDuration=tempo/sadNoteDurations[0];
	melodyPlaying=true;
	currentMelody=SAD;
}


void stopMelody(){
	melodyPlaying=false;
	noTone(buzzerPin);
	currentMelody=NOSOUND;
}

void updateMelody(){

	if (melodyPlaying) {
		if (millis()-lastNotePlayed>currentNoteDuration) {

			switch (currentMelody) {
			case SONG:

				if (currentNote==melodyLength&&loopMelody) {
					currentNote=0;
				}else if (currentNote==melodyLength&& !loopMelody) {
					melodyPlaying=false;
					noTone(buzzerPin);
				}

				currentNoteDuration=tempo/noteDurations[currentNote];
				tone(buzzerPin, melody[currentNote], currentNoteDuration-pauseBetweenNotes);
				lastNotePlayed=millis();

				break;

			case HAPPY:
				if (currentNote==happyMelodyLength&&loopMelody) {
					currentNote=0;
				}else if (currentNote==happyMelodyLength&& !loopMelody) {
					melodyPlaying=false;
					noTone(buzzerPin);
				}

				currentNoteDuration=tempo/happyNoteDurations[currentNote];
				tone(buzzerPin, happyMelody[currentNote], currentNoteDuration-pauseBetweenNotes);
				lastNotePlayed=millis();
				break;

			case SAD:
				if (currentNote==sadMelodyLength&&loopMelody) {
					currentNote=0;
				}else if (currentNote==sadMelodyLength&& !loopMelody) {
					melodyPlaying=false;
					noTone(buzzerPin);
				}
				currentNoteDuration=tempo/sadNoteDurations[currentNote];
				tone(buzzerPin, happyMelody[currentNote], currentNoteDuration-pauseBetweenNotes);
				lastNotePlayed=millis();
				break;
				break;
			}
			currentNote++;
		}
	}
}
