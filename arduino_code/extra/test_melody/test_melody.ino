#include "pitches.h"

void setup(){
	pinMode(3,OUTPUT);
}

void loop(){
	//happy sound
	tone(3, NOTE_G4);
	delay(100);
	tone(3, NOTE_D7);
	delay(200);
	tone(3, NOTE_G4);
	delay(100);
	tone(3, NOTE_D7);
	delay(200);
	noTone(3);
	delay(5000);

	//sad sound
	tone(3, NOTE_G4);
	delay(500);
	tone(3, NOTE_D4);
	delay(400);
	noTone(3);
	delay(5000);

}
