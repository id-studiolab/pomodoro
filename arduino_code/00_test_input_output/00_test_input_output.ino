/*
 * The following code can be used
 * to test the pomodoro timer connections.
 *
 * STEPS:
 * -Change the variables according to your wiring;
 * -Open the serial port and check that the two buttons are working
 * -Verify that the servo motors moves and the light fades
 * when turning the potentiometer.
 *
 */
#include <Servo.h>
#include <ChainableLED.h>

//connections
int buttonAPin = 2;
int buttonBPin = 3;
int potPin = A0;
int servoPin = 6;

int ledPin1 = 4;
int ledPin2 = 5;

//create a servo object
Servo myServo;

//create a ChainableLED object
#define NUM_LEDS  1
ChainableLED leds(ledPin1, ledPin2, NUM_LEDS);

void setup() {
  //define input/output pins
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(potPin, INPUT);

  //start the servo
  myServo.attach(servoPin);

  //start the serial port
  Serial.begin (9600);
}

void loop() {
  Serial.print("btn A: ");
  Serial.print(digitalRead(buttonAPin));
  Serial.print(" btn B: ");
  Serial.print(digitalRead(buttonBPin));
  Serial.print(" pot: ");

  int potValue = analogRead(potPin);
  Serial.print(analogRead(potPin));
  Serial.println();

  int servoAngle = map(potValue, 0, 1024, 0, 180);
  myServo.write(servoAngle);

  int lightIntensity = map(potValue, 0, 1024, 0, 255);
  leds.setColorRGB(0, lightIntensity, lightIntensity, lightIntensity);

  delay(10);
}
