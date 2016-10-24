#include "Arduino.h"
#include "dcmotor.h"

void DCMotor::attach(char forward, char reverse, char power) {
  forwardPin = forward;
  reversePin = reverse;
  powerPin = power;

  pinMode(forwardPin, OUTPUT);
  pinMode(reversePin, OUTPUT);
  pinMode(powerPin, OUTPUT);
}

boolean DCMotor::start(int power) {
  if (abs(power) < 256) {
     boolean isReverse = (power < 0);
     analogWrite(powerPin, abs(power));
     digitalWrite(forwardPin, isReverse ? LOW : HIGH);
     digitalWrite(reversePin, isReverse ? HIGH : LOW);
     return false;
  } else {
    return true;
  }
}

void DCMotor::stop() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(reversePin, LOW);
  digitalWrite(powerPin, LOW);
}

