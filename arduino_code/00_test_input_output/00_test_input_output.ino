/*
 * The following code can be used
 * to test the pomodoro timer components.
 *
 * STEPS:
 * -Change the variables according to your wiring;
 * -Open the serial port and check that the button is working
 * -Turn the rotation sensor and verify that the servo motor moves, 
 * the light fades and the buzzer becomes louder/quieter
 *
 */
#include <Servo.h>
#include <ChainableLED.h>

//connections
int buttonPin = 2;
int buzzerPin = 3;
int potPin = A0;
int servoPin = 6;

int ledPin1 = 4;
int ledPin2 = 5;

//create a servo object
Servo myServo;

//create a ChainableLED object
int numLeds = 1;
ChainableLED leds(ledPin1, ledPin2, numLeds);

void setup() {
  //start the led library
  leds.init();
  
  //define input/output pins
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(potPin, INPUT);

  //start the servo
  myServo.attach(servoPin);

  //start the serial port
  Serial.begin (9600);
}

void loop() {
  Serial.print("button: ");
  Serial.print(digitalRead(buttonPin));
  Serial.print(" pot: ");

  int potValue = analogRead(potPin);
  Serial.print(analogRead(potPin));
  Serial.println();

  int servoAngle = map(potValue, 0, 1024, 0, 180);
  myServo.write(servoAngle);

  int lightIntensity = map(potValue, 0, 1024, 0, 255);
  leds.setColorRGB(0, lightIntensity, lightIntensity, lightIntensity);
  
  int buzzerLoudness = map(potValue, 0, 1024, 0, 180);
  analogWrite(buzzerPin, buzzerLoudness);

  delay(10);
}
