#include <Servo.h>

#include "FastLED.h"
#include "dcmotor.h"

#define NUM_LEDS 10
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

DCMotor leftWheel;
DCMotor rightWheel;

int inputPin = 11; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
int dot = 0;
boolean dir = false;
int highdetected= 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  leftWheel.attach(22, 23, 9);
  rightWheel.attach(24, 25, 10);

  pinMode(DATA_PIN, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT); // declare sensor as input

  Serial.begin(9600);

}

void loop() {
  //Serial.println("Enter loop");
  // put your main code here, to run repeatedly:
  val = digitalRead(inputPin); // read input value
  if (val == HIGH) { // check if the input is HIGH
    //Serial.println("HIGH");
    highdetected++;
    if (highdetected >= 200) {
      leds[dot] = CRGB(128, 212, 255);
      FastLED.show();
      // clear this led for the next time around the loop
      leds[dot] = CRGB::Black;
      delay(20);
      if (dir == false) {
        dot++;
        if (dot >= NUM_LEDS-1){
          dot = 0; //dir = true;
        }
      } else {
          dot--;
      }
      if (dot == 0){
        dir = false;
      }
      if (pirState == LOW) {
        Serial.println("Motion detected!");
        pirState = HIGH;
      }
    }
  } else {
    highdetected = 0;
    //Serial.println("LOW");
    if (pirState == HIGH){
       Serial.println("Motion ended!");
       pirState = LOW;
    }
  }
    //Serial.println("exit loop");

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
