int servoAnimationDuration = 1000;
int servoAnimationSteps = 100;
long lastServoUpdateTime;

float servoUpdateInterval = servoAnimationDuration / servoAnimationSteps;
int servoDirection = 1;

int maxServo = 180;
int minServo = 0;

float servoIncrementAmountXStep = (maxServo - minServo) / servoAnimationSteps;

int servoPosition = 0;

void startServoSweep(int duration, int steps, int max, int min) {
  maxServo = max;
  minServo = min;
  servoAnimationDuration = duration;
  servoAnimationSteps = steps;

  servoUpdateInterval = servoAnimationDuration / servoAnimationSteps;
  servoIncrementAmountXStep = (maxServo - minServo) / servoAnimationSteps;
}

void updateServo() {
  if (millis() - lastServoUpdateTime > servoUpdateInterval) {
    servoPosition = servoPosition + (servoIncrementAmountXStep * servoDirection);

    if (servoPosition > maxServo || servoPosition < minServo) {
      servoDirection *= -1;
      //make sure the value falls between the desired range
      servoPosition = constrain(servoPosition, minServo, maxServo);

    }

    lastServoUpdateTime = millis();
    myServo.write(servoPosition);
  }
}


