/**
 *
 *****************************************************************
 * IOT Challenges - https://instagram.com/iotchallenges          *
 *****************************************************************
 * Evandro Fruhauf                                               *
 *  GitHub - https://github.com/evandrodp                        *
 *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
 *****************************************************************
 * This code can contain parts from other open-sources projects, *
 * whenever possible it will be quoted.                          *
 *****************************************************************
 *
 * Servo with Potentiometer
 *
 * Challenge: Use the potentiometer to move the Servo motor
 *
 * This code uses Servo library.
 *
**/
#include <Arduino.h>
#include <Servo.h>

// define if the code will run using potentiometer
const int usePotentiometer = true;
const int sayBye = false; // Works only without potentiometer

// Set Potentiometer pin
int potentiometer = A5;

//initialise a servo object
Servo servo;

// define the initial angle
int angle = 0;

void withPotentiometer();
void withoutPotentiometer();
void byeBye();
void goAndReturn();
void moveFromTo(int start, int finish, int increment);

void setup() {
  // attach the signal pin of servo to pin 3 of arduino
  servo.attach(3);
}

void loop() {
  if (usePotentiometer) {
    withPotentiometer();
  } else {
    withoutPotentiometer();
  }
}

void withPotentiometer() {
  // read the value of the potentiometer it is between 0 and 1023 (0 - 5V)
  angle = analogRead(potentiometer);
  // Apply linear interpolation between the potentiometer value (0 - 1023) and angle value for servo (0 - 179)
  angle = map(angle, 0, 1023, 0, 179);
  // Change the servo position
  servo.write(angle);
  delay(5);
}

void withoutPotentiometer() {
  if (sayBye) {
    byeBye();
  } else {
    goAndReturn();
  }
}

void byeBye() {
  moveFromTo(60, 120, 3);
  delay(100);
  moveFromTo(120, 60, 3);
  delay(100);
}

void goAndReturn() {
  // command to move from 0 degrees to 179 degrees slow (increment 1 each time)
  moveFromTo(0, 179, 1);
  delay(1000);
  // move from 179 degrees to 0 degrees quickly (increment 5 each time)
  moveFromTo(179, 0, 5);
  delay(1000);
}

void moveFromTo(int start, int finish, int increment) {
  if (start < finish) {
    for(angle = start; angle < finish; angle += increment) {
      servo.write(angle);
      delay(5);
    }
  } else {
    for(angle = start; angle>= finish; angle-= increment) {
      servo.write(angle);
      delay(5);
    }
  }
}