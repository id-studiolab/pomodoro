//some variables to animate the servo motor.
int servoPosition;
int servoDirection=1;

int servoAnimationDuration;
int servoUpdateInterval;
int servoStepSize;

long lastServoUpdated;

int servoMin;
int servoMax;

int targetPosition;

// multiple types of animation,
enum servoAnimationType {
	SWEEP,
	MOVETO,
	STOPMOTOR,
};

servoAnimationType currentServoAnimation=STOPMOTOR;


int startServoSweepAnimation(int min, int max, int duration, int steps ){
	currentServoAnimation=SWEEP;
	servoMin=min;
	servoMax=max;
	servoUpdateInterval=duration/steps;
	servoStepSize= abs(servoMax-servoMin)/steps;
}

void updateServoSweep(){
	servoPosition+=servoStepSize*servoDirection;
	if (servoPosition > servoMax || servoPosition < servoMin) {
		servoDirection *= -1;
		//make sure the value falls between the desired range
		servoPosition=constrain(servoPosition,servoMin,servoMax);
	}
}

void startServoMoveToAnimation(int target, int duration, int steps){
	currentServoAnimation=MOVETO;
	targetPosition=target;
	servoUpdateInterval=duration/steps;
	servoStepSize= abs(target-servoPosition)/steps;
}

void updateServoMoveTo(){
	servoPosition+=servoStepSize*servoDirection;
	if ((servoDirection==1 && servoPosition > targetPosition)||
	    (servoDirection==-1 && servoPosition < targetPosition)) {
		servoPosition=targetPosition;
		currentServoAnimation=STOPMOTOR;
	}
}

void stopServo(){
	currentServoAnimation=STOPMOTOR;
}

void updateServo(){
	if (millis() - lastServoUpdated > servoUpdateInterval) {
		switch (currentServoAnimation) {
		case SWEEP:
			updateServoSweep();
			break;
		case MOVETO:
			updateServoMoveTo();
			break;
		case STOPMOTOR:
			break;
		}
		lastServoUpdated=millis();
	}


	myServo.write(servoPosition);
}
