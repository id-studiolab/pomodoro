//some variables to animate the servo motor.
int servoPosition;
int servoDirection;

int servoSweepStepDuration;
int servoSweepStepSize;

int lastServoUpdated;

int servomin;
int servoMax;

int NSweeps;

int init servo_sweep_animations(int min, int max, int sweeps, int duration, int steps ){
	servomin=min;
	servomax=max;
	NSweeps=sweeps;

	servoSweepStepDuration=duration/steps;
	servoSweepStepSize= abs(servoMax-servomin)/steps;
}

void
