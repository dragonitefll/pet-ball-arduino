#include <Servo.h>

#include "FastLED.h"
#include "dcmotor.h"

#define NUM_LEDS 10
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

DCMotor leftWheel;
DCMotor rightWheel;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  leftWheel.attach(2, 3, 9);
  rightWheel.attach(4, 5, 10);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB(255, 0, 255);
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }
  
  if (Serial.available() > 0) {
    int command = Serial.read();
    if (command == 1) {
      char args[3] = {0, 0, 0};
      Serial.readBytes(args, 3);
      driveCommand(args[0], args[1], args[2]);
    }
  }
}

void driveCommand(unsigned char mode, unsigned char speedA, unsigned char speedB) {
  if (bitRead(mode, 0)) {
    if (bitRead(mode, 1)) {
      leftWheel.start((bitRead(mode, 2) ? -1 : 1) * speedA); 
    }
  } else {
    leftWheel.stop();
  }
  if (bitRead(mode, 3)) {
    if (bitRead(mode, 4)) {
      rightWheel.start((bitRead(mode, 5) ? -1 : 1) * speedB); 
    }
  } else {
    rightWheel.stop();
  }
  sendOk();
}

void sendOk() {
  Serial.write(0);
  Serial.flush();
}

